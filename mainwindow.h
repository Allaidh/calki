#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QChartView>
#include <QValueAxis>
#include <QList>
#include <QLineSeries>
#include <QAreaSeries>
#include "drawer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct FunctionSeries {
    QString expression;
    QLineSeries* series;
    QAreaSeries* area;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openDrawer();
    bool eventFilter(QObject *obj, QEvent *event);
    double calculateIntegral(te_expr* expr, double a, double b, double step, double* xPtr);
    QChart *chart;


private:
    Ui::MainWindow *ui;
    drawer *drawer;
    QPushButton *button;
    QChartView *chartview;
    QList<FunctionSeries> seriesList;
    QValueAxis* axisX;
    QValueAxis* axisY;

public slots:
    void onFunctionAdded(const QString &exprStr);
    void onFunctionRemoved(const QString &exprStr);
};

#endif // MAINWINDOW_H
