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

    funkcje[ile] = text;
    kolory[ile] = currentColor;
    ile++;

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

            QCheckBox *check = new QCheckBox("Kocham femboyi :3");
            check->setStyleSheet("color: white;");

            QPushButton* guzior = new QPushButton("Wprowadź");
            guzior->setStyleSheet("background-color: #1D4C5B; color: white;");

            hlayout->addWidget(a);
            hlayout->addWidget(b);

            layout->addLayout(hlayout);
            layout->addWidget(check);
            layout->addStretch();
            layout->addWidget(guzior);

            window->setStyleSheet(QString("background-color: %1;")
                                      .arg(funcColor.darker(150).name()));

            window->show();
        });

        hLayout->addWidget(colorLabel);
        hLayout->addWidget(label);
        hLayout->addWidget(delButton);
        hLayout->addWidget(calka);
        hLayout->addStretch();
        layout->addLayout(hLayout);
    }
}
