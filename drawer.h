#ifndef DRAWER_H
#define DRAWER_H

#include <QWidget>
#include <QResizeEvent>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QLabel>

class drawer : public QWidget
{
    Q_OBJECT
public:
    explicit drawer(QWidget *parent = nullptr);
    QString funkcje[20];
    int ile;
    void toggle();

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
