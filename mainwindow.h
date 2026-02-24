#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>
#include "drawer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openDrawer();
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::MainWindow *ui;
    drawer *drawer;
    QPushButton *button;
};
#endif // MAINWINDOW_H
