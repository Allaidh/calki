#ifndef DRAWER_H
#define DRAWER_H

#include <QWidget>
#include <QMessageBox>
#include <QResizeEvent>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QLabel>
extern "C" {
    #include "tinyexpr.h"
}

class drawer : public QWidget
{
    Q_OBJECT
public:
    explicit drawer(QWidget *parent = nullptr);
    QString funkcje[20];
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
    QVBoxLayout *functions;


private slots:
    void addFunction();
signals:
};

#endif // DRAWER_H
