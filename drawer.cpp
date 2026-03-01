#include "drawer.h"

drawer::drawer(QWidget *parent) : QWidget(parent), isOpen(false) {
    ile = 0;
    setupUI();
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

void drawer::setupUI() {

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *hlayout = new QHBoxLayout();

    //Label do inputa
    QLabel *funcLabel = new QLabel("Podaj wzór funkcji:", this);
    funcLabel -> setStyleSheet("background-color: #1e1e1e;");
    funcLabel -> setFixedWidth(100);

    //Input
    functionInput = new QLineEdit(this);
    functionInput -> setPlaceholderText("np. 3*x");
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
    functions = new QVBoxLayout();
    functions -> setContentsMargins(50, 20, 0, 0);
    layout -> addLayout(hlayout);
    layout -> addLayout(functions);
    layout -> addStretch();

    setLayout(layout);

    connect(drawButton, &QPushButton::clicked, this, &drawer::addFunction);
    this -> setStyleSheet("background-color: lightgray;");
}

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

    emit functionAdded(text);


    clearLayout(functions);
    wypisz(functions);
    functionInput -> clear();
}


void drawer::clearLayout(QVBoxLayout* layout){
    if (!layout) return;

    while (QLayoutItem* item = layout->takeAt(0))
    {
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

        QLabel* label = new QLabel(funkcje[i], this);
        label->setStyleSheet("color: white; background-color: #1e1e1e; padding: 3px;");
        label -> setFixedWidth(100);

        QPushButton* delButton = new QPushButton("❌", this);
        delButton->setStyleSheet("background-color: #810000; color: white;");
        delButton -> setFixedWidth(40);

        QString text = funkcje[i];

        connect(delButton, &QPushButton::clicked, this, [this, label, text]() {

            int idx = -1;
            for (int j = 0; j < ile; j++) {
                if (funkcje[j] == label->text()) {
                    idx = j;
                    break;
                }
            }

            if (idx == -1) return;

            for (int j = idx; j < ile - 1; j++)
                funkcje[j] = funkcje[j + 1];

            ile--;

            emit functionRemoved(text);

            clearLayout(functions);
            wypisz(functions);
        });

        hLayout->addWidget(label);
        hLayout->addWidget(delButton);
        hLayout->addStretch();
        layout->addLayout(hLayout);
    }
}
