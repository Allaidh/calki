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

    // --- KONFIGURACJA WYKRESU ---
    int zakres = 10;

    QLineSeries *series = new QLineSeries();
    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);

    // ✅ FIX: Inicjalizacja zmiennych członkowskich (bez "QValueAxis *")
    axisX = new QValueAxis();
    axisX->setRange(-zakres, zakres);
    axisX->setLabelsVisible(true);

    axisY = new QValueAxis();
    axisY->setRange(-zakres, zakres);
    axisY->setLabelsVisible(true);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // --- OSI GŁÓWNE ---
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

    // --- STRZAŁKI (GROTY OSI) ---
    double arrowSize = 0.1; // ✅ Mniejsza wartość = węższa strzałka

    // Strzałka osi X (prawa strona)
    QLineSeries *xArrow1 = new QLineSeries();
    QLineSeries *xArrow2 = new QLineSeries();

    xArrow1->append(zakres, 0);
    xArrow1->append(zakres - arrowSize, arrowSize);

    xArrow2->append(zakres, 0);
    xArrow2->append(zakres - arrowSize, -arrowSize);

    xArrow1->setPen(QPen(Qt::black, 1));
    xArrow2->setPen(QPen(Qt::black, 1));
    chart->addSeries(xArrow1);
    chart->addSeries(xArrow2);
    xArrow1->attachAxis(axisX);
    xArrow1->attachAxis(axisY);
    xArrow2->attachAxis(axisX);
    xArrow2->attachAxis(axisY);

    // Strzałka osi Y (góra)
    QLineSeries *yArrow1 = new QLineSeries();
    QLineSeries *yArrow2 = new QLineSeries();

    yArrow1->append(0, zakres);
    yArrow1->append(-arrowSize * 0.8, zakres - 0.5 - arrowSize * 0.1);

    yArrow2->append(0, zakres);
    yArrow2->append(arrowSize * 0.8, zakres - 0.5 - arrowSize * 0.1);

    yArrow1->setPen(QPen(Qt::black, 1));
    yArrow2->setPen(QPen(Qt::black, 1));
    chart->addSeries(yArrow1);
    chart->addSeries(yArrow2);
    yArrow1->attachAxis(axisX);
    yArrow1->attachAxis(axisY);
    yArrow2->attachAxis(axisX);
    yArrow2->attachAxis(axisY);

    // --- WIDOK WYKRESU ---
    chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

    // --- DRAWER (PANEL BOCZNY) ---
    drawer->setVisible(false);
    drawer->setFixedWidth(600);
    drawer->setStyleSheet("background-color: #BADAFE;");

    // Central widget + layout
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(drawer);

    QWidget *chartContainer = new QWidget();
    chartContainer->setObjectName("chartContainer");
    QVBoxLayout *chartContainerLayout = new QVBoxLayout(chartContainer);
    chartContainerLayout->setContentsMargins(0, 0, 0, 0);
    chartContainerLayout->setSpacing(0);
    chartContainerLayout->addWidget(chartview);

    mainLayout->addWidget(chartContainer);
    setCentralWidget(centralWidget);

    // --- PRZYCISK PRZEŁĄCZANIA ---
    button = new QPushButton(tr("<"));
    button->setFixedSize(20, 20);
    button->setStyleSheet(
        "QPushButton { background-color: #1D4C5B; color: #ffffff; border-radius: 4px; font-size: 14px; } "
        "QPushButton:pressed { background-color: #4E9AC5; }");
    connect(button, &QPushButton::clicked, this, &MainWindow::openDrawer);

    QWidget *buttonOverlay = new QWidget(chartview->viewport());
    buttonOverlay->setAttribute(Qt::WA_TranslucentBackground);
    buttonOverlay->setFixedSize(24, 24);

    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonOverlay);
    buttonLayout->setContentsMargins(2, 2, 2, 2);
    buttonLayout->addWidget(button);
    buttonLayout->addStretch();

    buttonOverlay->move(10, 10);
    buttonOverlay->raise();
    buttonOverlay->show();

    chartview->viewport()->installEventFilter(this);

    // --- POŁĄCZENIA SYGNAŁÓW ---
    connect(drawer, &drawer::functionAdded, this, &MainWindow::onFunctionAdded);
    connect(drawer, &drawer::functionRemoved, this, &MainWindow::onFunctionRemoved);
}

void MainWindow::openDrawer()
{
    drawer -> setVisible(!drawer -> isVisible());
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
    if (obj && event -> type() == QEvent::Resize) {
        QWidget *vp = qobject_cast<QWidget*>(obj);
        if (!vp) return QMainWindow::eventFilter(obj, event);

        // find our overlay child (fixed size 40x40)
        for (QObject *child : vp -> children()) {
            QWidget *w = qobject_cast<QWidget*>(child);
            if (!w) continue;
            if (w -> width() == 40 && w -> height() == 40) {
                // keep 10 px from top-left of viewport
                w -> move(10, 10);
                w -> raise();
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::onFunctionAdded(const QString &exprStr)
{
    double x;
    te_variable vars[] = {{"x", &x}};
    int err;

    std::string exprStd = exprStr.toStdString();
    te_expr* expr = te_compile(exprStd.c_str(), vars, 1, &err);

    if (err == 0 && expr) {
        QLineSeries *series = new QLineSeries();

        for (double xv = -10; xv <= 10; xv += 0.1) {
            x = xv;
            series->append(xv, te_eval(expr));
        }

        //dodawanie pola pod wykresem
        QLineSeries *gorna = series;  // Twoja funkcja

        QLineSeries *dolna = new QLineSeries();
        dolna->append(series->at(0).x(), 0);

        for(int i = 1; i < series->count(); i++)
        {
            dolna->append(series->at(i).x(), 0);
        }

        QAreaSeries *area = new QAreaSeries(gorna, dolna);
        QColor kolorLinii = series->pen().color();
        kolorLinii.setAlpha(100); // 0 = całkowicie przezroczysty, 255 = całkowicie kryjący
        area->setColor(kolorLinii); // półprzezroczyste wypełnienie


        double integral = calculateIntegral(expr, -10, 10, 0.1, &x);
        QMessageBox::information(this, "Całka",
                                 QString("Całka funkcji %1 od -10 do 10 wynosi %2")
                                     .arg(exprStr)
                                     .arg(integral));

        chart->addSeries(series);
        chart->addSeries(area);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
        area->attachAxis(axisX);
        area->attachAxis(axisY);
        //---------------------------

        seriesList.append({exprStr, series, area});

        drawer->funkcje[drawer->ile] = exprStr;
        drawer->ile++;

        QChart *chart = chartview->chart();
        chart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
        te_free(expr);
    } else {
        QMessageBox::warning(this, "Błąd", "Nieprawidłowe wyrażenie!");

    }
}

void MainWindow::onFunctionRemoved(const QString &exprStr)
{
    for (int i = 0; i < seriesList.size(); i++) {
        if (seriesList[i].expression == exprStr) {  // ✅ Znajdź właściwą funkcję
            QChart *chart = chartview->chart();

            chart->removeSeries(seriesList[i].series);
            delete seriesList[i].series;

            chart->removeSeries(seriesList[i].area);
            delete seriesList[i].area;

            seriesList.removeAt(i);
            break;  // ✅ Teraz break jest OK, bo znaleźliśmy właściwy element
        }
    }
}

double MainWindow::calculateIntegral(te_expr* expr, double a, double b, double step, double* xPtr)
{
    double& x = *xPtr; // tinyexpr zmienna
    double sum = 0.0;
    int n = static_cast<int>(ceil((b - a) / step));
    for(int i = 0; i < n; ++i)
    {
        double x0 = a + i * step;
        double x1 = a + (i + 1) * step;

        x = x0;
        double y0 = te_eval(expr);

        x = x1;
        double y1 = te_eval(expr);

        sum += (y0 + y1) / 2.0 * step;
    }

    double last = a + n * step;
    if(last < b)
    {
        x = last;
        double y0 = te_eval(expr);
        x = b;
        double y1 = te_eval(expr);
        sum += (y0 + y1) / 2.0 * (b - last);
    }

    if(a == -b && fabs(sum) < 1e-12) // jeśli przedział symetryczny i suma bardzo mała
    {
        sum = 0.0; // traktujemy jako dokładnie 0
    }

    return sum;
}
