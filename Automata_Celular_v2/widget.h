#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>
#include "cellular_universe.h"
//#include "mynodo.h"
#include <QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QEasingCurve>
#include <QFileDialog>
#include <tuple>
#include <map>
#include <iostream>
#include <cmath>
//#include "gamethread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget{

    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    void set_vZoom_label(int value);
    void set_vRotate_label(int value);
    void setSize();
    void StartGame();
    void StopGame();
    void PauseGame();
    void setZoom();
    void changeLabel();
    void setAliveColor();
    void setDeathColor();
    void setRule();
    void displayChart();
    void fileBrowser();
    void ZoomChart();
    void saveFile();
    void CalculateAttractor();
    void loadTable();
    void saveAttractor();

    //Thread slots
    void updateView();

signals:
    void attractorComplete();

private:
    Ui::Widget *ui;
    Cellular_Universe myItem;
    QGraphicsScene *myscene; //Se debe inicializar en el constructor
    QTimer *timer;
    QChart *chart;
    QChart *chart_log10;
    std::map<unsigned long int, unsigned long int> Mx_adyacencia;
    bool isFile = false;
    bool isDefault = true;
    bool saveAttractor_File(QString filename);

};
#endif // WIDGET_H
