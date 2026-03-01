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
    double zakresA[20];  // ✅ Początek zakresu całkowania
    double zakresB[20];  // ✅ Koniec zakresu całkowania
    double wyniki[20];   // ✅ Wyniki całek
    int ile;
    void toggle();
    void clearLayout(QVBoxLayout* layout);
    void wypisz(QVBoxLayout* layout);
    void add(const QString &exprStr);
    double calculateIntegral(te_expr* expr, double a, double b, double step, double* xPtr);
    QVBoxLayout *functions;

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    bool isOpen;
    void setupUI();
    QLineEdit *functionInput;
    QPushButton *drawButton;
    QPushButton *colorButton;
    QColor currentColor;

private slots:
    void addFunction();
    void pickColor();

signals:
    void functionAdded(const QString &exprStr, const QColor &color, double a, double b);  // ✅ Z zakresami
    void functionRemoved(const QString &exprStr);
    void integralChanged(int index, double a, double b, double result);  // ✅ Nowy signal
};

#endif // DRAWER_H
