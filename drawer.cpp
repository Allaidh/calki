#include "drawer.h"

drawer::drawer(QWidget *parent) : QWidget(parent), isOpen(false) {
    setupUI();
    ile = 0;
    // setFixedWidth(600);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding); // Wysokość elastyczna
}

void drawer::setupUI() {

    //Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *hlayout = new QHBoxLayout(this);

    //Label inputa
    QLabel *funcLabel = new QLabel("Funkcja:", this);
    funcLabel->setStyleSheet("background-color: #1e1e1e;");
    funcLabel->setFixedWidth(50);

    //Input
    functionInput = new QLineEdit(this);
    functionInput->setPlaceholderText("np. 3x");
    functionInput->setStyleSheet("background-color: #1e1e1e;");
    functionInput->setFixedWidth(150);

    //Button
    drawButton = new QPushButton("Dodaj wykres", this);
    drawButton->setStyleSheet("background-color: #111111;");
    drawButton->setFixedWidth(150);
    //Margin
    layout->setContentsMargins(0, 70, 0, 0);

    //styl
    funcLabel->setStyleSheet("background-color: #1e1e1e; color: white; padding: 0; margin: 0;");
    functionInput->setStyleSheet("background-color: #1e1e1e; color: white; padding: 0; margin: 0;");

    //Dodawanie inputa i labela
    hlayout->addWidget(funcLabel);
    hlayout->addWidget(functionInput);

    layout->setSpacing(0);
    hlayout->setSpacing(0);


    //Dodawanie guzika
    hlayout->addWidget(drawButton);
    //Layout funkcji
    functions = new QVBoxLayout(this);
    functions->setContentsMargins(50, 20, 0, 0);
    layout->addLayout(hlayout);
    layout->addLayout(functions);
    layout->addStretch();

    setLayout(layout);

    connect(drawButton, &QPushButton::clicked, this, &drawer::addFunction);
    this->setStyleSheet("background-color: lightgray;");
}


// Użycie resizeEvent do ustawiania geometrii
void drawer::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event); // Wywołanie domyślnej metody
    this->setGeometry(0, 0, event->size().width() * 0.33, event->size().height()); // Szerokość 600, wysokość dostosowana do nowego rozmiaru
}

void drawer::addFunction()
{
    QString text = functionInput->text();
    if(text.isEmpty()) return;
    if(ile >= 20) {
        functionInput->clear();
        return;
    }

    funkcje[ile] = text; // zapis do tablicy
    ile++;

    // Dodaj nowy label **bez kasowania wcześniejszych**
    QLabel *newLabel = new QLabel(text, this);
    newLabel->setStyleSheet("color: white; background-color: #1e1e1e; padding: 3px;");

    // Dodajemy przed stretch (jeśli stretch istnieje na końcu)
    int stretchIndex = functions->count(); // jeśli nie ma stretchu na końcu
    functions->insertWidget(stretchIndex, newLabel);

    functionInput->clear();
}
