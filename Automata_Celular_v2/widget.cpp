#include "widget.h"
#include "./ui_widget.h"
#include "QtCharts/qchartview.h"
#include "mynodo.h"




//Constructor del Widget
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget) , myscene(new QGraphicsScene(this)), timer(new QTimer(this)), myItem(Cellular_Universe())
{
    ui->setupUi(this);
    ui->graphicsView->setScene(this->myscene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    //Zoom and Rotate
    connect(ui->Zoom,&QSlider::valueChanged,this,&Widget::set_vZoom_label);
    connect(ui->Rotate,&QSlider::valueChanged,this,&Widget::set_vRotate_label);
    connect(ui->Zoom, &QSlider::valueChanged, this, &Widget::setZoom);
    connect(ui->Rotate, &QSlider::valueChanged, this, &Widget::setZoom);

    //ZOOM chart
    connect(ui->Zoom_Chart, &QSlider::valueChanged, this, &Widget::ZoomChart);


    //Size
    connect(ui->pushButton_Size,&QPushButton::clicked, this, &Widget::setSize);

    //Start
    connect(ui->pushButton_Start,&QPushButton::clicked, this, &Widget::StartGame);

    //Stop
    connect(ui->pushButton_Stop,&QPushButton::clicked, this, &Widget::StopGame);

    //Pause
    ui->pushButton_Pause->setVisible(false);
    connect(ui->pushButton_Pause,&QPushButton::clicked, this, &Widget::PauseGame);

    //Color
    connect(ui->pushButton_Acolor, &QPushButton::clicked, this, &Widget::setAliveColor);
    connect(ui->pushButton_Bcolor, &QPushButton::clicked, this, &Widget::setDeathColor);

    //Rule
    connect(ui->pushButton_Rule, &QPushButton::clicked, this, &Widget::setRule);

    //Chart
    ui->pushButton_Chart->setDisabled(true);
    connect(ui->pushButton_Chart, &QPushButton::clicked, this, &Widget::displayChart);

    //Tool file
    connect(ui->tool_file, &QToolButton::clicked, this, &Widget::fileBrowser);
    connect(ui->tool_fileSave, &QToolButton::clicked, this, &Widget::saveFile);
    ui->tool_fileSave->setDisabled(true);

    //Timer
    connect(timer, &QTimer::timeout, myscene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &Widget::changeLabel);

    //Attractor
    ui->toolButton_fileSave2->setDisabled(true);
    connect(ui->pushButton_Calculate, &QPushButton::clicked, this, &Widget::CalculateAttractor);
    connect(this, &Widget::attractorComplete, this, &Widget::loadTable);
    connect(ui->toolButton_fileSave2, &QToolButton::clicked, this, &Widget::saveAttractor);



    ui->Rotate->setDisabled(true);
    ui->Zoom->setDisabled(true);
    ui->pushButton_Stop->setDisabled(true);

}

//virtual destructor
Widget::~Widget(){
    delete ui;
}

//Slot: establece el valor actual del slider a su label correspondiente
void Widget::set_vZoom_label(int value){
    ui->label_Zoom->setText(QString::number(value) + "%");
}

//Slot: establece el valor actual del slider a su label correspondiente
void Widget::set_vRotate_label(int value){
    ui->label_Rotate->setText(QString::number(value) + "°");
}

//Slot: establece el tamaño del universo
void Widget::setSize(){
    qInfo() << this << Q_FUNC_INFO << " -> size: " << ui->spinBox_Size->value();
    ui->tool_fileSave->setDisabled(false);
    this->myItem.setSize(ui->spinBox_Size->value());
    QString msg;
    if(!this->isFile){
       msg = "Se establecio el tamaño del universo: " + QString::number(ui->spinBox_Size->value());
       this->myItem.setRandom_Matrix(this->myItem.getSize());
    }else{
       msg = "Archivo cargado, reiniciar applicación para configuración aleatoria ";

    }
    this->isDefault = false;
    QMessageBox::information(this, "Info Message", msg);



}

//Slot: inicia el juego
void Widget::StartGame(){
    qInfo() << this << Q_FUNC_INFO << " -> start";
    ui->tool_fileSave->setDisabled(true);
    ui->spinBox_Size->setDisabled(true);
    ui->pushButton_Size->setDisabled(true);
    ui->pushButton_Start->setDisabled(true);
    ui->Rotate->setDisabled(false);
    ui->Zoom->setDisabled(false);
    ui->pushButton_Pause->setDisabled(false);
    ui->pushButton_Stop->setDisabled(false);

    this->myItem.aliveCells = 0;
    this->myItem.generation = 0;
    ui->label_AliveCells->setText(QString::number(this->myItem.aliveCells));
    ui->label_Generation->setText(QString::number(this->myItem.generation));

    if(this->isDefault){
       this->myItem.setRandom_Matrix(this->myItem.getSize());

    }
    //this->myItem.setRule(2,3,3,3);
    //this->myItem.setRule(2,2,7,7);

    this->myscene->addItem(&myItem);
    this->timer->start(500);
}

//Slot: termina el juego
void Widget::StopGame(){
    qInfo() << this << Q_FUNC_INFO << " -> stop";
    ui->pushButton_Start->setDisabled(false);
    ui->pushButton_Chart->setDisabled(false);
    ui->tool_fileSave->setDisabled(false);
    timer->stop();

    for(int i=0; i<myItem.Info_densidad.size(); i++){
        qDebug() << std::get<0>(myItem.Info_densidad.at(i)) << " -- "<< std::get<1>(myItem.Info_densidad.at(i)) ;
    }
}

//Slot: pause el juego
void Widget::PauseGame(){
    qInfo() << this << Q_FUNC_INFO << " -> pause";
}

void Widget::setZoom(){
    qreal scale = qPow(qreal(2), (ui->Zoom->value() - 250) / qreal(50));
    QTransform matrix;
    matrix.scale(scale, scale);
    matrix.rotate(ui->Rotate->value());
    ui->graphicsView->setTransform(matrix);
    ui->graphicsView->update();
    //setResetButtonEnabled();

}

void Widget::changeLabel(){

    ui->label_AliveCells->setText(QString::number(myItem.aliveCells));
    ui->label_Generation->setText(QString::number(myItem.generation));
}

//Establece el color de la celula viva
void Widget::setAliveColor(){
    const QColor color = QColorDialog::getColor(Qt::green, this, "Elige el color de la celula viva");

    if (color.isValid()) {
        QRgb mycolor = color.rgb();
        this->myItem.setColor_AliveCell(mycolor);
        this->myItem.update();
        ui->label_Acolor->setPalette(QPalette(color));
        ui->label_Acolor->setAutoFillBackground(true);
    }//if
}

void Widget::setDeathColor(){
    const QColor color = QColorDialog::getColor(Qt::green, this, "Elige el color de la celula viva");

    if (color.isValid()) {
        QRgb mycolor = color.rgb();
        this->myItem.setColor_DeathCell(mycolor);
        this->myItem.update();
        ui->label_Dcolor->setPalette(QPalette(color));
        ui->label_Dcolor->setAutoFillBackground(true);
    }//if

}
//Establece la Regla
void Widget::setRule(){
    this->myItem.setRule(ui->spinBox_Smin->value(), ui->spinBox_Smax->value(), ui->spinBox_Nmin->value(), ui->spinBox_Nmax->value());
    //this->myItem.update();
    QString msg = "Rule changed: R(" + QString::number(ui->spinBox_Smin->value()) + ", "
            + QString::number(ui->spinBox_Smax->value()) + ", " + QString::number(ui->spinBox_Nmin->value())
            + ", " + QString::number(ui->spinBox_Nmax->value()) + ")";

    QMessageBox::warning(this, "Info Message", msg);

}

void Widget::displayChart(){
    qInfo() << this << Q_FUNC_INFO << " -> display Chart";

    int tam = this->myItem.Info_densidad.size();

    //Creating series
    QLineSeries *series = new QLineSeries();
    series->setPointsVisible(true);

    QLineSeries *seriesLog = new QLineSeries();
    seriesLog->setPointsVisible(true);

    //Adding data
    for(int i =0; i< tam; i++){
            float x = std::get<0>(this->myItem.Info_densidad.at(i));
            float y = std::get<1>(this->myItem.Info_densidad.at(i));
            //series->append(x,y);
            qDebug() <<"Normal: " <<QPointF(x,y);
            qDebug() <<"Log10:  " <<QPointF(x,std::log10(y));
            *series << QPointF(x,y);
            *seriesLog << QPointF(x,std::log10(y));
    }//for


    this->chart = new QChart();
    this->chart_log10 = new QChart();

    chart->legend()->hide();
    chart_log10->legend()->hide();

    chart->addSeries(series);
    chart_log10->addSeries(seriesLog);



    //Themes
    chart->setTheme(QChart::ChartThemeBlueCerulean);
    chart_log10->setTheme(QChart::ChartThemeBlueNcs);

    //Axes
    //chart->createDefaultAxes();
    chart_log10->createDefaultAxes();
    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(1, std::get<0>(this->myItem.Info_densidad.at(tam-1)));
    axisX->setTickCount(tam/8);
    chart->addAxis(axisX, Qt::AlignBottom);


    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,this->myItem.getSize()*this->myItem.getSize());
    //axisX->setTickCount(myItem->getSize()*myItem->getSize()/8);
    chart->addAxis(axisY, Qt::AlignLeft);


    chart->setTitle("Density");
    chart_log10->setTitle("Log 10 - Density");


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QChartView *chartView2 = new QChartView(chart_log10);
    chartView2->setRenderHint(QPainter::Antialiasing);



    ui->dockWidget_Density->setWidget(chartView);
    ui->dockWidget_Log10->setWidget(chartView2);

}

void Widget::fileBrowser(){
    qInfo() << this << Q_FUNC_INFO << " -> file";

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "/Users/mard/Desktop/Game_Of_Life/Archivos_txt", tr("Text files (*.txt)"));
    if(fileName.isEmpty()){
       QString msg = "Archivo no especificado";
       QMessageBox::warning(this, "Info Message", msg);
        return;
    }
    qDebug() << fileName;
    if(this->myItem.setMatrix_byFile(fileName)){
        this->isFile = true;
        this->isDefault = false;
    }else{
        //Mandar mensaje en pantalla de error
        qDebug() << "ERROR";
        this->isFile = false;
        QMessageBox::warning(this, "Info Message", "ERROR");
        return;
    }

    for(int i= 0 ;i< this->myItem.getSize(); i++){
        for(int j=0; j<this->myItem.getSize(); j++){
            std::cout << this->myItem.getMx().at(i).at(j) << "";
        }
        std::cout << "\n";
    }
    QMessageBox::information(this, "Info Message", "Archivo cargado :)");

}

//Hace zoom
void Widget::ZoomChart(){
    qreal scale = ui->Zoom_Chart->value();
    this->chart->zoom(scale);
    this->chart->update();
}

//Guarda configuración actual del automata
void Widget::saveFile(){
    qInfo() << this << Q_FUNC_INFO << " -> saving file";
    QMessageBox msgBox;
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save File"), "/Users/mard/Desktop/Game_Of_Life/Archivos_txt", tr("Text files (*.txt)"));

    if(fileName.isEmpty()){
        QString msg = "Archivo no especificado";
        QMessageBox::warning(this, "Info Message", msg);
        return;
    }
    if(this->myItem.saveMXinFile(fileName.toStdString())){
        msgBox.setText("File succesfully saved");
        msgBox.exec();
    }else{
        msgBox.setText("ERROR");
        msgBox.exec();
    }//if

}


//Calcula los nodos del atractor
void Widget::CalculateAttractor(){

    qInfo() << this << Q_FUNC_INFO;
    this->Mx_adyacencia.clear();
    unsigned long int p = pow(ui->spinBox_SizeGrid->value(),2);
    unsigned long int size = pow(2,p);

    unsigned int Smin = ui->spinBox_Smin->value();
    unsigned int Smax = ui->spinBox_Smax->value();
    unsigned int Nmin = ui->spinBox_Nmin->value();
    unsigned int Nmax = ui->spinBox_Nmax->value();

    QStringList title;
    unsigned int m = ui->spinBox_SizeGrid->value();
    qDebug() << m;

    if(m <= 3){
       for(unsigned long int i = 0; i < size ; i++){
            myNodo n = myNodo(i,m);
            n.setMatrix();
            n.applyRule(Smin,Smax,Nmin,Nmax);
            this->Mx_adyacencia.insert(std::pair<unsigned long int,unsigned long  int>(n.getID(), n.getNextState()));
            title.append(QString::number(i));

        }//for

        ui->tableWidget_Nodes->setRowCount(size);
        ui->tableWidget_Nodes->setColumnCount(title.size());
        ui->tableWidget_Nodes->setVerticalHeaderLabels(title);
        ui->tableWidget_Nodes->setHorizontalHeaderLabels(title);

        emit attractorComplete();
        QMessageBox::information(this, "Info Message", "Caluclo completado");
    }else{
        for(unsigned long int i = 0; i < size ; i++){
             myNodo n = myNodo(i,m);
             n.setMatrix();
             n.applyRule(Smin,Smax,Nmin,Nmax);
             this->Mx_adyacencia.insert(std::pair<unsigned long int,unsigned long int>(n.getID(), n.getNextState()));
         }//for
        qDebug() << "Calculo completado";
        QMessageBox::information(this, "Info Message", "Caluclo completado (file)");
    }//if-else
    ui->toolButton_fileSave2->setDisabled(false);
}

//Slot: carga tabla cuando se emite attractorComplete()
void Widget::loadTable(){
    qInfo() << this << Q_FUNC_INFO;
    unsigned long int tam = this->Mx_adyacencia.size();


    for(unsigned long int i = 0; i< tam; i++){
        QString s = QString::number(1);
        QTableWidgetItem *newItem = new QTableWidgetItem(s);
        newItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_Nodes->setItem(i,this->Mx_adyacencia.at(i),newItem);
    }//for
}

//Slot: guarda el map actual en un txt
void Widget::saveAttractor(){
    qInfo() << this << Q_FUNC_INFO;
    QMessageBox msgBox;
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save File"), "/Users/mard/Desktop/Game_Of_Life/Archivos_txt", tr("Text files (*.txt)"));

    if(fileName.isEmpty()){
        QString msg = "Archivo no especificado";
        QMessageBox::warning(this, "Info Message", msg);
        return;
    }

    if(this->saveAttractor_File(fileName)){
        msgBox.setText("File succesfully saved");
        msgBox.exec();
    }else{
        msgBox.setText("ERROR");
        msgBox.exec();
    }//if

}

//Slot: respuesta de la acción del Thread
void Widget::updateView(){
    qInfo() << this << Q_FUNC_INFO;
    qDebug() << "[-- Signal recived -- ]";
}

//Guarda map acutal en txt
bool Widget::saveAttractor_File(QString filename){
    qInfo() << this << Q_FUNC_INFO;
    qDebug() << filename ;
    std::ofstream archivoNuevo(filename.toStdString(), std::ios::out);
    if(!archivoNuevo){
        std::cerr<<"No se puede abrir el archivo"<<std::endl;
        return false;
    }//if
    for(unsigned long int i = 0; i < this->Mx_adyacencia.size(); i++){
        archivoNuevo<< i <<" "<< this->Mx_adyacencia.at(i)<<std::endl;
    }//for
return true;

}

