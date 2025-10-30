#ifndef CELLULAR_UNIVERSE_H
#define CELLULAR_UNIVERSE_H
#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QImage>
#include <vector>
#include <random>
#include <tuple>
#include <QFile>
#include <fstream>
#include <QByteArray>
#include <QIODevice>


class Cellular_Universe: public QGraphicsItem{

private:
    unsigned int size = 3; //Tamaño de la matriz
    std::vector<std::vector<unsigned int>> matrix; //Matriz principal
    QImage img_matrix;//Imagen del universo
    unsigned int Nmax;
    unsigned int Nmin;
    unsigned int Smin;
    unsigned int Smax;
    std::vector<std::vector<unsigned int>> matrix_temp;
    QRgb value = qRgb(0, 255, 0); // verde;
    QRgb value2 = qRgb(192, 192, 192); // gris

public:
    //Contador de celulas por generación
    unsigned int aliveCells = 0;

    //Generación
    unsigned int generation = 0;

    // < generacion, celulas vivas>
    std::vector<std::tuple<unsigned int, unsigned int>> Info_densidad;

    //Establece el color de la celula viva
    void setColor_AliveCell(QRgb color);

    //Establece el color de la celula viva
    void setColor_DeathCell(QRgb color);

    //Constructor
    Cellular_Universe();


    //Construye la matriz principal con valores aleatorios
    void setRandom_Matrix(unsigned int size);

    //Construye la matriz principal con los valores de una archivo.txt
    bool setMatrix_byFile(QString file_name);

    //Establece la regla
    void setRule(unsigned int S_m, unsigned int S_M, unsigned int N_m, unsigned int N_M);

    //Establece el tamaño del univeros
    void setSize(unsigned int mySize);

    //Regresa el tamaño
    unsigned int getSize();

    //Regresa una copia de la matriz
    std::vector<std::vector<unsigned int>> getMx();

    //Guarda la matriz principal en un archivo txt
    bool saveMXinFile(std::string filename);


    /* --- OVERRIDE FUNCTIONS: QGrphicsItem ---*/

    //Regresa un rectangulo con dimensiones predefinidas por el programador
    QRectF boundingRect() const override;

    // *Da forma al objeto (CONFIRMAR DEFINICION MEDIANTE PRUEBAS)
    //QPainterPath shape() const override;

    //Se encarga de dibujar la figura en el sistema de coordenadas local (CONFIRMAR MEDIANTE PRUEBAS)
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

protected slots:
    void advance(int phase) override;

};

#endif // CELLULAR_UNIVERSE_H
