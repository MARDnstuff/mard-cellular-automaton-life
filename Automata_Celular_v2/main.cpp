#include "widget.h"

#include <QApplication>

/* ***************************************
 *  PROYECTO: Automata Celular           *
 *  Autor: Marco Antonio Reséndiz Díaz   *
 *  version: 2.0                         *
 *  Fecha: 26/10/2022                    *
 * ***************************************
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
