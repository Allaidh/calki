#include "drawer.h"

drawer::drawer(QWidget *parent) : QWidget(parent), isOpen(false) {
    ile = 0;
    // Inicjalizacja tablic
    for(int i = 0; i < 20; i++) {
        zakresA[i] = -10.0;  // ✅ Domyślny zakres
        zakresB[i] = 10.0;
        wyniki[i] = 0.0;
    }
    currentColor = QColor(QRandomGenerator::global()->bounded(256),
                          QRandomGenerator::global()->bounded(256),
                          QRandomGenerator::global()->bounded(256));
    setupUI();
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

void drawer::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *hlayout = new QHBoxLayout();

    QLabel *funcLabel = new QLabel("Podaj wzór funkcji:", this);
    funcLabel->setStyleSheet("background-color: #1e1e1e; color: white; padding: 0; margin: 0;");
    funcLabel->setFixedWidth(100);

    functionInput = new QLineEdit(this);
    functionInput->setPlaceholderText("np. 3*x");
    functionInput->setStyleSheet("background-color: #1e1e1e; color: white; padding: 0; margin: 0;");
    functionInput->setFixedWidth(180);

    colorButton = new QPushButton(this);
    colorButton->setFixedSize(40, 25);
    colorButton->setStyleSheet(QString("background-color: %1; border: 1px solid white;")
                                   .arg(currentColor.name()));
    colorButton->setToolTip("Wybierz kolor funkcji");

    drawButton = new QPushButton("Dodaj wykres", this);
    drawButton->setStyleSheet("background-color: #111111; color: white;");
    drawButton->setFixedWidth(100);

    layout->setContentsMargins(0, 20, 0, 0);
    layout->setSpacing(0);
    hlayout->setSpacing(5);

    hlayout->addWidget(funcLabel);
    hlayout->addWidget(functionInput);
    hlayout->addWidget(colorButton);
    hlayout->addWidget(drawButton);

    functions = new QVBoxLayout();
    functions->setContentsMargins(50, 20, 0, 0);
    layout->addLayout(hlayout);
    layout->addLayout(functions);
    layout->addStretch();

    setLayout(layout);

    connect(drawButton, &QPushButton::clicked, this, &drawer::addFunction);
    connect(colorButton, &QPushButton::clicked, this, &drawer::pickColor);

    this->setStyleSheet("background-color: lightgray;");
}

void drawer::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    this->setGeometry(0, 0, event->size().width() * 0.33, event->size().height());
}

void drawer::pickColor() {
    QColor color = QColorDialog::getColor(currentColor, this, "Wybierz kolor funkcji");
    if (color.isValid()) {
        currentColor = color;
        colorButton->setStyleSheet(QString("background-color: %1; border: 1px solid white;")
                                       .arg(color.name()));
    }
}

void drawer::addFunction()
{
    QString text = functionInput->text();
    if(text.isEmpty()){
        QMessageBox::critical(this, tr("Error"), tr("Nie podano żadnej funkcji."));
        return;
    }
    if(ile >= 20) {
        functionInput->clear();
        QMessageBox::critical(this, tr("Error"), tr("Przekroczono limit ilości funkcji."));
        return;
    }

    kolory[ile] = currentColor;
    zakresA[ile] = -10.0;  // ✅ Domyślny zakres
    zakresB[ile] = 10.0;

    // ✅ Emituj signal z zakresami
    emit functionAdded(text, currentColor, zakresA[ile], zakresB[ile]);

    currentColor = QColor(QRandomGenerator::global()->bounded(256),
                          QRandomGenerator::global()->bounded(256),
                          QRandomGenerator::global()->bounded(256));
    colorButton->setStyleSheet(QString("background-color: %1; border: 1px solid white;")
                                   .arg(currentColor.name()));

    clearLayout(functions);
    wypisz(functions);
    functionInput->clear();
}

void drawer::clearLayout(QVBoxLayout* layout){
    if (!layout) return;
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QWidget* widget = item->widget())
            widget->deleteLater();
        if (item->layout())
            clearLayout((QVBoxLayout*)item->layout());
        delete item;
    }
}

void drawer::wypisz(QVBoxLayout* layout) {
    for (int i = 0; i < ile; i++) {
        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->setSpacing(3);

        // ✅ Kolor
        QLabel* colorLabel = new QLabel(this);
        colorLabel->setFixedSize(15, 15);
        colorLabel->setStyleSheet(QString("background-color: %1; border: 1px solid white;")
                                      .arg(kolory[i].name()));

        // ✅ Wzór funkcji
        QLabel* label = new QLabel(funkcje[i], this);
        label->setStyleSheet("color: white; background-color: #1e1e1e; padding: 3px;");
        label->setFixedWidth(90);

        // ✅ Input a
        QLineEdit *inputA = new QLineEdit();
        inputA->setPlaceholderText("a");
        inputA->setFixedWidth(40);
        inputA->setStyleSheet("background-color: #1e1e1e; color: white;");
        inputA->setText(QString::number(zakresA[i]));

        // ✅ Input b
        QLineEdit *inputB = new QLineEdit();
        inputB->setPlaceholderText("b");
        inputB->setFixedWidth(40);
        inputB->setStyleSheet("background-color: #1e1e1e; color: white;");
        inputB->setText(QString::number(zakresB[i]));

        // ✅ Przycisk całki
        QPushButton* calka = new QPushButton("∫", this);
        calka->setStyleSheet("background-color: #333333; color: white;");
        calka->setFixedWidth(30);

        // ✅ Wynik
        QLabel* wynik = new QLabel(QString("P=%1").arg(wyniki[i], 0, 'f', 2), this);
        wynik->setStyleSheet("color: white; background-color: #1e1e1e; padding: 3px;");
        wynik->setFixedWidth(70);
        wynik->setAlignment(Qt::AlignCenter);

        // ✅ Przycisk usuwania
        QPushButton* delButton = new QPushButton("❌", this);
        delButton->setStyleSheet("background-color: #810000; color: white;");
        delButton->setFixedWidth(30);

        QString text = funkcje[i];
        QColor funcColor = kolory[i];
        int index = i;

        // ✅ POŁĄCZENIA (bez zmian)
        connect(delButton, &QPushButton::clicked, this, [this, text]() {
            int idx = -1;
            for (int j = 0; j < ile; j++) {
                if (funkcje[j] == text) {
                    idx = j;
                    break;
                }
            }
            if (idx == -1) return;

            for (int j = idx; j < ile - 1; j++) {
                funkcje[j] = funkcje[j + 1];
                kolory[j] = kolory[j + 1];
                zakresA[j] = zakresA[j + 1];
                zakresB[j] = zakresB[j + 1];
                wyniki[j] = wyniki[j + 1];
            }
            ile--;

            emit functionRemoved(text);

            clearLayout(functions);
            wypisz(functions);
        });

        connect(calka, &QPushButton::clicked, this, [this, text, inputA, inputB, wynik, index, funcColor]() {
            QString atext = inputA->text();
            QString btext = inputB->text();

            if(atext.isEmpty() || btext.isEmpty()) {
                QMessageBox::critical(nullptr, "Błąd", "Podaj granice całkowania a i b");
                return;
            }

            bool aOk, bOk;
            double aVal = atext.toDouble(&aOk);
            double bVal = btext.toDouble(&bOk);

            if(!aOk || !bOk) {
                QMessageBox::critical(nullptr, "Błąd", "Granice całkowania muszą być liczbami");
                return;
            }

            double x;
            te_variable vars[] = {{"x", &x}};
            int err;

            std::string f = text.toStdString();
            te_expr* expr = te_compile(f.c_str(), vars, 1, &err);

            if(!expr) {
                QMessageBox::critical(nullptr, "Błąd", "Nieprawidłowe wyrażenie matematyczne");
                return;
            }

            double integral = calculateIntegral(expr, aVal, bVal, 0.01, &x);
            wynik->setText(QString("P=%1").arg(integral, 0, 'f', 3));

            wyniki[index] = integral;
            zakresA[index] = aVal;
            zakresB[index] = bVal;

            emit integralChanged(index, aVal, bVal, integral);

            te_free(expr);
        });

        // ✅ Dodawanie do layoutu
        hLayout->addWidget(colorLabel);
        hLayout->addWidget(label);
        hLayout->addWidget(inputA);
        hLayout->addWidget(inputB);
        hLayout->addWidget(calka);
        hLayout->addWidget(wynik);
        hLayout->addStretch();
        hLayout->addWidget(delButton);

        layout->addLayout(hLayout);

        // ✅ USTAWIANIE KOLEJNOŚCI TAB - TO JEST KLUCZOWE!
        if (i == 0) {
            // Pierwszy wiersz - zaczynamy od inputA
            setTabOrder(inputA, inputB);
            setTabOrder(inputB, calka);
            setTabOrder(calka, delButton);
        } else {
            // Kolejne wiersze - łączymy z poprzednim
            // Musimy znaleźć widgety z poprzedniego wiersza
            QWidget *prevInputB = nullptr;
            QWidget *prevDelButton = nullptr;

            // Szukamy widgetów w layoutach
            QLayoutItem *prevItem = layout->itemAt(i - 1);
            if (prevItem && prevItem->layout()) {
                QHBoxLayout *prevHLayout = qobject_cast<QHBoxLayout*>(prevItem->layout());
                if (prevHLayout) {
                    // InputB jest na indeksie 3, delButton na końcu
                    prevInputB = prevHLayout->itemAt(3)->widget();
                    prevDelButton = prevHLayout->itemAt(prevHLayout->count() - 1)->widget();
                }
            }

            if (prevDelButton) {
                setTabOrder(prevDelButton, inputA);  // Poprzedni ❌ -> obecny a
            }
            setTabOrder(inputA, inputB);  // a -> b
            setTabOrder(inputB, calka);   // b -> ∫
            setTabOrder(calka, delButton); // ∫ -> ❌
        }
    }
}
double drawer::calculateIntegral(te_expr* expr, double a, double b, double step, double* xPtr)
{
    double& x = *xPtr;
    double sum = 0.0;
    int n = static_cast<int>(ceil((b - a) / step));
    for(int i = 0; i < n; ++i)
    {
        double x0 = a + i * step;
        double x1 = a + (i + 1) * step;

        x = x0;
        double y0 = te_eval(expr);

        x = x1;
        double y1 = te_eval(expr);

        sum += (y0 + y1) / 2.0 * step;
    }

    double last = a + n * step;
    if(last < b)
    {
        x = last;
        double y0 = te_eval(expr);
        x = b;
        double y1 = te_eval(expr);
        sum += (y0 + y1) / 2.0 * (b - last);
    }

    if(a == -b && fabs(sum) < 1e-12)
    {
        sum = 0.0;
    }

    return sum;
}
