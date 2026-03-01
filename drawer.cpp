#include "drawer.h"

drawer::drawer(QWidget *parent) : QWidget(parent), isOpen(false) {
    ile = 0;
    currentColor = QColor(QRandomGenerator::global()->bounded(256),
                          QRandomGenerator::global()->bounded(256),
                          QRandomGenerator::global()->bounded(256));
    setupUI();
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

void drawer::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *hlayout = new QHBoxLayout();

    // Label do inputa
    QLabel *funcLabel = new QLabel("Podaj wzór funkcji:", this);
    funcLabel->setStyleSheet("background-color: #1e1e1e; color: white; padding: 0; margin: 0;");
    funcLabel->setFixedWidth(100);

    // Input
    functionInput = new QLineEdit(this);
    functionInput->setPlaceholderText("np. 3*x");
    functionInput->setStyleSheet("background-color: #1e1e1e; color: white; padding: 0; margin: 0;");
    functionInput->setFixedWidth(200);

    colorButton = new QPushButton(this);
    colorButton->setFixedSize(40, 25);
    colorButton->setStyleSheet(QString("background-color: %1; border: 1px solid white;")
                                   .arg(currentColor.name()));
    colorButton->setToolTip("Wybierz kolor funkcji");

    // Button dodawania
    drawButton = new QPushButton("Dodaj wykres", this);
    drawButton->setStyleSheet("background-color: #111111; color: white;");
    drawButton->setFixedWidth(100);

    // Margin
    layout->setContentsMargins(0, 20, 0, 0);
    layout->setSpacing(0);
    hlayout->setSpacing(5);

    // Dodawanie widgetów
    hlayout->addWidget(funcLabel);
    hlayout->addWidget(functionInput);
    hlayout->addWidget(colorButton);
    hlayout->addWidget(drawButton);

    // Layout funkcji
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

    emit functionAdded(text, currentColor);

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

        QLabel* colorLabel = new QLabel(this);
        colorLabel->setFixedSize(20, 20);
        colorLabel->setStyleSheet(QString("background-color: %1; border: 1px solid white;")
                                      .arg(kolory[i].name()));

        QLabel* label = new QLabel(funkcje[i], this);
        label->setStyleSheet("color: white; background-color: #1e1e1e; padding: 3px;");
        label->setFixedWidth(100);

        QPushButton* delButton = new QPushButton("❌", this);
        delButton->setStyleSheet("background-color: #810000; color: white;");
        delButton->setFixedWidth(40);

        QPushButton* calka = new QPushButton("∫", this);
        calka->setStyleSheet("background-color: #333333; color: white;");
        calka->setFixedWidth(40);

        // Usuń stąd QLabel* wynik - przeniesiemy go do okna dialogowego

        QString text = funkcje[i];
        QColor funcColor = kolory[i];

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
            }
            ile--;

            emit functionRemoved(text);

            clearLayout(functions);
            wypisz(functions);
        });

        connect(calka, &QPushButton::clicked, this, [this, text, funcColor]() {
            QWidget *window = new QWidget();
            window->setWindowTitle("Całka oznaczona");
            window->resize(400, 300);

            QVBoxLayout *layout = new QVBoxLayout(window);
            QHBoxLayout *hlayout = new QHBoxLayout();

            QLineEdit *a = new QLineEdit();
            a->setPlaceholderText("Podaj a:");

            QLineEdit *b = new QLineEdit();
            b->setPlaceholderText("Podaj b:");

            // Dodaj etykietę do wyświetlania wyniku
            QLabel *wynikLabel = new QLabel("Wynik: ");
            wynikLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
            wynikLabel->setAlignment(Qt::AlignCenter);

            QCheckBox *check = new QCheckBox("Kocham femboyi :3");
            check->setStyleSheet("color: white;");

            QPushButton* guzior = new QPushButton("Oblicz całkę");
            guzior->setStyleSheet("background-color: #1D4C5B; color: white; padding: 5px;");

            connect(guzior, &QPushButton::clicked, this, [this, text, a, b, wynikLabel]() {
                QString atext = a->text();
                QString btext = b->text();

                // Sprawdź czy pola nie są puste
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

                double integral = calculateIntegral(expr, aVal, bVal, 0.1, &x);
                wynikLabel->setText("Wynik: " + QString::number(integral, 'g', 6));

                te_free(expr);
            });

            hlayout->addWidget(a);
            hlayout->addWidget(b);

            layout->addLayout(hlayout);
            layout->addWidget(wynikLabel);
            layout->addWidget(check);
            layout->addStretch();
            layout->addWidget(guzior);

            window->setStyleSheet(QString("background-color: %1;")
                                      .arg(funcColor.darker(150).name()));

            window->show();
        });

        hLayout->addWidget(colorLabel);
        hLayout->addWidget(label);

        hLayout->addWidget(calka);
        hLayout->addStretch();
        hLayout->addWidget(delButton);
        // Usuń dodawanie wynik do hLayout
        layout->addLayout(hLayout);
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
