#include "drawer.h"

drawer::drawer(QWidget *parent) : QWidget(parent), isOpen(false) {
    setupUI();
    ile = 0;
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

void drawer::setupUI() {

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *hlayout = new QHBoxLayout(this);

    //Label do inputa
    QLabel *funcLabel = new QLabel("Podaj wzór funkcji:", this);
    funcLabel -> setStyleSheet("background-color: #1e1e1e;");
    funcLabel -> setFixedWidth(100);

    //Input
    functionInput = new QLineEdit(this);
    functionInput -> setPlaceholderText("np. 3x");
    functionInput -> setStyleSheet("background-color: #1e1e1e;");
    functionInput -> setFixedWidth(300);

    //Button
    drawButton = new QPushButton("Dodaj wykres", this);
    drawButton -> setStyleSheet("background-color: #111111;");
    drawButton -> setFixedWidth(100);

    //Margin
    layout->setContentsMargins(0, 20, 0, 0);

    //styl
    funcLabel -> setStyleSheet("background-color: #1e1e1e; color: white; padding: 0; margin: 0;");
    functionInput -> setStyleSheet("background-color: #1e1e1e; color: white; padding: 0; margin: 0;");

    //Dodawanie inputa i labela
    hlayout -> addWidget(funcLabel);
    hlayout -> addWidget(functionInput);

    layout -> setSpacing(0);
    hlayout -> setSpacing(0);


    //Dodawanie guzika
    hlayout -> addWidget(drawButton);
    //Layout funkcji
    functions = new QVBoxLayout(this);
    functions -> setContentsMargins(50, 20, 0, 0);
    layout -> addLayout(hlayout);
    layout -> addLayout(functions);
    layout -> addStretch();

    setLayout(layout);

    connect(drawButton, &QPushButton::clicked, this, &drawer::addFunction);
    this -> setStyleSheet("background-color: lightgray;");
}


// Użycie resizeEvent do ustawiania geometrii
void drawer::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    this -> setGeometry(0, 0, event->size().width() * 0.33, event->size().height());
}

void drawer::addFunction()
{
    QString text = functionInput -> text();
    if(text.isEmpty()){
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("Nie podano żadnej funkcji.") );
        return;
    }
    if(ile >= 20) {
        functionInput -> clear();
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("Przekroczono limit ilości funkcji.") );

        return;
    }

    funkcje[ile] = text; // Zapisanie textu z inputa do tablicy
    ile++;

    // Dodanie nowego labela
    QLabel *newLabel = new QLabel(text, this);
    newLabel -> setStyleSheet("color: white; background-color: #1e1e1e; padding: 3px;");

    int stretchIndex = functions -> count();
    functions -> insertWidget(stretchIndex, newLabel);

    functionInput -> clear();
}
