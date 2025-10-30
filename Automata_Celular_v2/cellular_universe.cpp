#include "cellular_universe.h"
#include "QtWidgets/qwidget.h"
#include <iostream>
//mantener positivo
int positive(int n, int size){
    if(n < 0 ){
        int pos_n = n*(-1);
        int res = size - (pos_n%size);
        return res;
    }else{
        return n;
    }//if-else

}

//Establece el color de la celula viva
void Cellular_Universe::setColor_AliveCell(QRgb color){
    this->value = color;
}

//Establece el color de la celula viva
void Cellular_Universe::setColor_DeathCell(QRgb color){
    this->value2 = color;
}


Cellular_Universe::Cellular_Universe(){

}

//Construye la matriz principal con valores aleatorios
void Cellular_Universe::setRandom_Matrix(unsigned int size){
    //Vector columna vacio
    std::vector<std::vector<unsigned int>> columna;
    this->size = size;

    for(int i = 0; i < this->size; i++){
        //Vector fila vacio
        std::vector<unsigned int> fila;
        for(int j = 0; j < this->size; j++){
            //Incializamos
            std::random_device rnd;
            unsigned int state = rnd()%2;
            if(state == 1){this->aliveCells++;}
            fila.push_back(state);
        }//for
        columna.push_back(fila);
    }//for
    this->generation++;
    std::tuple<unsigned int, unsigned int> e;
    e = std::make_tuple(this->generation, this->aliveCells);
    this->Info_densidad.push_back(e);
    this->matrix = columna;
}//setRandom_Matrix

//Construye la matriz principal con los valores de una archivo.txt
bool Cellular_Universe::setMatrix_byFile(QString file_name){
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    int i = 0;
    unsigned int filas = 0, columnas  = 0, tam = 0;
    std::vector<std::vector<unsigned int>> columna;

    while (!in.atEnd()) {
        QString line = in.readLine();
        if(i == 0){ //tamaño de matriz que se desea crear
            tam = line.toInt();
        }else if(i == 1){//tamaño de filas
            filas = line.toInt();
        }else if(i == 2){// tamaño de columnas
            columnas = line.toInt();
        }else{
           std::vector<unsigned int> fila;
            for(int n = 0; n< line.size(); n++){
                if(line[n] == ',' || line[n] == ';'){
                    continue;
                }else{
                    if(line[n] == '-'){
                      fila.push_back(0);
                    }else{
                      fila.push_back(1);
                    }//if

                }//if-else
            }//for
            columna.push_back(fila);
        }//if-else
        qDebug() << line;
        i++;
    }//while
    qDebug() << "...";
    this->size = tam;

//    for(int h = 0; h< tam; h++){
//        for(int k = columnas-1 ; k< tam; k++){
//            columna.at(h).push_back(0);
//        }//for
//        if(h > filas){
//            std::vector<unsigned int> fila2;
//            columna.push_back(fila2);
//            columnas = 0;
//        }//if

//    }//for

    this->matrix = columna;


    return true;
}

//Establece la regla
void Cellular_Universe::setRule(unsigned int S_m, unsigned int S_M, unsigned int N_m, unsigned int N_M){
    qDebug() << "Smin: " << S_m << "SMax: " << S_M << "Nmin: " << N_m << "NMax: " << N_M;
    this->Smin = S_m;
    this->Smax = S_M;
    this->Nmin = N_m;
    this->Nmax = N_M;
    this->update();
}//SetRule;


//Establece el tamaño del univeros
void Cellular_Universe::setSize(unsigned int mySize){
    this->size = mySize;
}//setSize

//Regresa el tamaño del universo
unsigned int Cellular_Universe::getSize(){
   return this->size;

}//getSize

std::vector<std::vector<unsigned int>> Cellular_Universe::getMx(){
    return this->matrix;
}

//Guarda la matriz principal en un archivo txt
bool Cellular_Universe::saveMXinFile(std::string filename){
    qDebug() << QString::fromStdString(filename) ;
    std::ofstream archivoNuevo(filename, std::ios::out);
    if(!archivoNuevo){
        std::cerr<<"No se puede abrir el archivo"<<std::endl;
        return false;
    }//if
    int mx;
    char s2 = ',', s3 = ';';

    archivoNuevo << this->size;
    archivoNuevo<<std::endl;
    archivoNuevo << this->size;
    archivoNuevo<<std::endl;
    archivoNuevo << this->size;
    archivoNuevo<<std::endl;

    for(int i=0; i<this->size; i++){
        for(int j=0; j<this->size;j++){
            if(j == this->size - 1){
                if(this->matrix.at(i).at(j) == 0){
                    archivoNuevo<<'-'<<s3;
                }else{
                    archivoNuevo<<'0'<<s3;
                }

            }else{
                if(this->matrix.at(i).at(j) == 0){
                    archivoNuevo<<'-'<<s2;
                }else{
                    archivoNuevo<<'0'<<s2;
                }
            }

        }//for
        archivoNuevo<<std::endl;
    }//for
return true;
}

QRectF Cellular_Universe::boundingRect() const{
    return QRect(0,0,200,200);
}

void Cellular_Universe::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    //Inicialización de la imagen
    //this->img_matrix = QImage(this->size,this->size,QImage::Format_RGB32);

    QRectF rec = boundingRect();


    /*this->aliveCells = 0;
    //Aqui dibujamos el cuadro conforme a sus estados
    for(int i=0; i< this->size; i++){
        for(int j=0; j<this->size; j++){
            if(this->matrix.at(i).at(j) == 1){ //celula viva
                this->img_matrix.setPixel(j, i, this->value);
                this->aliveCells++;
            }else{//celula muerta
                this->img_matrix.setPixel(j, i, this->value2);
            }//if


        }//for
    }//for*/

    painter->drawImage(rec,this->img_matrix);
   //bool yes = this->img_matrix.save("/Users/mard/Desktop/Game_Of_Life/Archivos_txt/img.jpg",0,-1);
    scene()->update();

}//paint

//Modificamos para el siguientes paso
void Cellular_Universe::advance(int phase){
   // qDebug() << "[ advance begining ]: ";
    std::vector<std::vector<unsigned int>> columna;

    //IMAGEN
    this->img_matrix = QImage(this->size,this->size,QImage::Format_RGB32);


    if(!phase) return;
    unsigned int sizeMx = this->size;

    this->aliveCells = 0;
    for(int i=0; i< sizeMx; i++){
        std::vector<unsigned int> fila;
        for(int j=0; j< sizeMx; j++){
            int num_neighborhood = 0;
            if(this->matrix.at(positive(i - 1,sizeMx)%sizeMx).at(j) == 1){ num_neighborhood++; }
            if(this->matrix.at(positive(i-1,sizeMx)%sizeMx).at((j + 1)%sizeMx) == 1){ num_neighborhood++;}
            if(this->matrix.at(i).at((j + 1)%sizeMx) == 1){ num_neighborhood++;}
            if(this->matrix.at((i + 1)%sizeMx).at((j + 1)%sizeMx) == 1){num_neighborhood++;}
            if(this->matrix.at((i + 1)%sizeMx).at(j) == 1){ num_neighborhood++;}
            if(this->matrix.at((i + 1)%sizeMx).at(positive(j-1,sizeMx)%sizeMx) == 1){ num_neighborhood++;}
            if(this->matrix.at(i).at(positive(j-1,sizeMx)%sizeMx) == 1){ num_neighborhood++;}
            if(this->matrix.at((positive(i -1,sizeMx)%sizeMx)).at(positive(j -1,sizeMx)%sizeMx) == 1){ num_neighborhood++;}
            //Reglas
            //qDebug() <<"[" <<i<<"]"<<"[" <<j<<"]"<< "num_neighborhood: " << num_neighborhood;
            //qDebug() << "Smin: " << this->Smin << "SMax: " << this->Smax << "Nmin: " <<this->Nmin<< "NMax: " << this->Nmax;
            if(this->matrix.at(i).at(j) == 0 && (num_neighborhood >= this->Nmin && num_neighborhood <= this->Nmax)){
                    fila.push_back(1);
            }else if(this->matrix.at(i).at(j) == 1 && (num_neighborhood >= this->Smin && num_neighborhood <= this->Smax)){
                    fila.push_back(1);
            }else{
                fila.push_back(0);
            }

            if(this->matrix.at(i).at(j) == 1){ //celula viva
                this->img_matrix.setPixel(j, i, this->value);
                this->aliveCells++;
            }else{//celula muerta
                this->img_matrix.setPixel(j, i, this->value2);
            }//if

        }//for
        columna.push_back(fila);
    }//for
    this->generation++;
    std::tuple<unsigned int, unsigned int> e;
    e = std::make_tuple(this->generation, this->aliveCells);
    this->Info_densidad.push_back(e);
    this->matrix = columna;
    this->update();
    //qDebug() << "[ advance ending ]";

}//advance
