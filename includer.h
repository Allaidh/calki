#ifndef INCLUDER_H
#define INCLUDER_H

// ============================================
// GLOBAL VARIABLES
// ============================================
#include "zakres.h"
#include "ui_mainwindow.h"
// ============================================
// QT CORE
// ============================================
#include <QEvent>
#include <QObject>
#include <QWidget>

// ============================================
// QT WIDGETS
// ============================================
#include <QCheckBox>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

// ============================================
// QT GUI
// ============================================
#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QResizeEvent>

// ============================================
// QT CHARTS
// ============================================
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>
#include <QAreaSeries>
#include <QtCharts>

// ============================================
// QT CONTAINERS & UTILS
// ============================================
#include <QList>
#include <QRandomGenerator>

// ============================================
// EXTERNAL LIBRARIES
// ============================================
extern "C" {
#include "tinyexpr.h"
}

// ============================================
// PROJECT HEADERS
// ============================================
// ⚠️ UWAGA: Nie dołączaj drawer.h i mainwindow.h tutaj!
// To powoduje cykliczne zależnośći. Dołączaj je bezpośrednio
// w plikach .cpp gdzie są potrzebne.
//
// Przykład w mainwindow.cpp:
//   #include "mainwindow.h"
//   #include "drawer.h"
//
// Przykład w drawer.cpp:
//   #include "drawer.h"



#endif // INCLUDER_H
