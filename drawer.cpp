#include "drawer.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QResizeEvent>

drawer::drawer(QWidget *parent) : QWidget(parent), isOpen(false) {
    setupUI();
    // setFixedWidth(600);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding); // Wysokość elastyczna
}

void drawer::setupUI() {


    this->setStyleSheet("background-color: lightgray;");
}


// Użycie resizeEvent do ustawiania geometrii
void drawer::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event); // Wywołanie domyślnej metody
    this->setGeometry(0, 0, event->size().width() * 0.33, event->size().height()); // Szerokość 600, wysokość dostosowana do nowego rozmiaru
}
