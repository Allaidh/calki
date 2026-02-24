#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "drawer.h"

#include <QtCharts>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineSeries>
#include <QChartView>
#include <QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    drawer(new ::drawer(this))
{
    this->setWindowState(Qt::WindowMaximized);

    ui->setupUi(this);

    // range for series
    int zakres = 1000;

    // Chart + series
    QLineSeries *series = new QLineSeries();
    for (double x = -zakres; x <= zakres; x += 0.1)
        series->append(x, std::sin(x));

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(-zakres, zakres);
    axisX->setLabelsVisible(true);
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(-zakres, zakres);
    axisY->setLabelsVisible(true);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // axis lines
    QLineSeries *yAxisLine = new QLineSeries();
    yAxisLine->append(0, -zakres);
    yAxisLine->append(0, zakres);
    yAxisLine->setPen(QPen(Qt::black, 1));
    chart->addSeries(yAxisLine);
    yAxisLine->attachAxis(axisX);
    yAxisLine->attachAxis(axisY);

    QLineSeries *xAxisLine = new QLineSeries();
    xAxisLine->append(-zakres, 0);
    xAxisLine->append(zakres, 0);
    xAxisLine->setPen(QPen(Qt::black, 1));
    chart->addSeries(xAxisLine);
    xAxisLine->attachAxis(axisX);
    xAxisLine->attachAxis(axisY);

    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

    // Drawer widget
    drawer->setVisible(true);
    drawer->setFixedWidth(600);
    drawer->setStyleSheet("background-color: lightgray;");

    // Central widget + layout
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(drawer);

    // Chart container holds the chartview
    QWidget *chartContainer = new QWidget();
    chartContainer->setObjectName("chartContainer");
    QVBoxLayout *chartContainerLayout = new QVBoxLayout(chartContainer);
    chartContainerLayout->setContentsMargins(0,0,0,0);
    chartContainerLayout->setSpacing(0);
    chartContainerLayout->addWidget(chartview);

    mainLayout->addWidget(chartContainer);
    setCentralWidget(centralWidget);

    // Create the button and style it explicitly
    button = new QPushButton(tr("<"));
    button->setFixedSize(20, 20);
    button->setStyleSheet(
        "QPushButton { background-color: #000000; color: #ffffff; border-radius: 4px; font-size: 10px; } "
        "QPushButton:pressed { background-color: #333333; }");
    connect(button, &QPushButton::clicked, this, &MainWindow::openDrawer);

    // Parent overlay/button to the chartview's viewport so it draws above the chart
    QWidget *buttonOverlay = new QWidget(chartview->viewport());
    buttonOverlay->setAttribute(Qt::WA_TranslucentBackground);
    buttonOverlay->setFixedSize(24, 24); // slightly larger than button for padding

    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonOverlay);
    buttonLayout->setContentsMargins(2,2,2,2);
    buttonLayout->addWidget(button);
    buttonLayout->addStretch();

    // initial position inside viewport
    buttonOverlay->move(10, 10);
    buttonOverlay->raise();
    buttonOverlay->show();


    // Keep overlay positioned on chart container resize: install event filter on chartview->viewport()
    chartview->viewport()->installEventFilter(this);
}

void MainWindow::openDrawer()
{
    drawer->setVisible(!drawer->isVisible());
    if(button->text() == "<"){
        button -> setText(">");
    }
    else{
        button -> setText("<");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete drawer;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    // Reposition the overlay when the chart viewport resizes
    if (obj && event->type() == QEvent::Resize) {
        QWidget *vp = qobject_cast<QWidget*>(obj);
        if (!vp) return QMainWindow::eventFilter(obj, event);

        // find our overlay child (fixed size 40x40)
        for (QObject *child : vp->children()) {
            QWidget *w = qobject_cast<QWidget*>(child);
            if (!w) continue;
            if (w->width() == 40 && w->height() == 40) {
                // keep 10 px from top-left of viewport
                w->move(10, 10);
                w->raise();
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
