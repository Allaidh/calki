#ifndef DRAWER_H
#define DRAWER_H

#include "includer.h"

class drawer : public QWidget
{
    Q_OBJECT
public:
    explicit drawer(QWidget *parent = nullptr);
    QString funkcje[20];
    QColor kolory[20];
    int ile;
    void toggle();
    void clearLayout(QVBoxLayout* layout);
    void wypisz(QVBoxLayout* layout);
    void add(const QString &exprStr);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    bool isOpen;
    void setupUI();
    QLineEdit *functionInput;
    QPushButton *drawButton;
    QPushButton *colorButton;
    QVBoxLayout *functions;
    QColor currentColor;

private slots:
    void addFunction();
    void pickColor();

signals:
    void functionAdded(const QString &exprStr, const QColor &color);
    void functionRemoved(const QString &exprStr);
};

#endif // DRAWER_H
