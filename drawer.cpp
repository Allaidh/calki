#include "drawer.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QLabel>
drawer::drawer(QWidget *parent) : QWidget(parent), isOpen(false) {
    setupUI();
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

    layout->setContentsMargins(20, 70, 0, 0);

    //Dodawanie inputa i labela
    hlayout->addWidget(funcLabel);
    hlayout->addWidget(functionInput);

    //Dodawanie guzika
    hlayout->addWidget(drawButton);
    layout->addLayout(hlayout);
    layout->addStretch();

    setLayout(layout);

    this->setStyleSheet("background-color: lightgray;");
}


// Użycie resizeEvent do ustawiania geometrii
void drawer::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event); // Wywołanie domyślnej metody
    this->setGeometry(0, 0, event->size().width() * 0.33, event->size().height()); // Szerokość 600, wysokość dostosowana do nowego rozmiaru
}
