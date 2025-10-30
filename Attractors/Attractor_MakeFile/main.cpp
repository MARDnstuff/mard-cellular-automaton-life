/*  PRUEBA PARA LA GENERACION DE COMBINACIONES
 *  PARA LA CREACION DE UN ATRACTOR DE 2x2, 3x3 y 4x4
*/

#include <iostream>
#include <vector>
#include <map>
#include "nodo.h"
#include <string>
#include <fstream>
#include <cmath>


using namespace std;

bool saveFile(string filename, map<unsigned int, unsigned int> Mx);

int main(){


    // Hacer combinaciones (MATRIZ)
    // Aplicar reglas de LIFE y DIFUSSION en cada combinacion
    // Guardar la tupla en un map
    int num = 5;
    int size = pow(2,pow(num,2));
    map<unsigned int, unsigned int> Mx_adyacencia;

    for(int i = 0; i < size ; i++){
        Nodo n = Nodo(i,num);
        n.setMatrix();
        n.applyRule(2,2,7,7);
        Mx_adyacencia.insert(pair<unsigned int,unsigned int>(n.getID(), n.getNextState()));
    }

    if(saveFile("/home/marco/Desktop/Basin_Attractors/Attractors/Attractor_MakeFile/Attractor_5x5Dif.txt", Mx_adyacencia)){
        cout << "END" << endl;
    }else{
        cout << "ERROR" << endl;
    }



    return 0;
}//main

bool saveFile(string filename, map<unsigned int, unsigned int> Mx){
    std::ofstream archivoNuevo(filename, std::ios::out);
    if(!archivoNuevo){
        std::cerr<<"No se puede abrir el archivo"<<std::endl;
        return false;
    }//if
    for(int i = 0; i < Mx.size(); i++){
        archivoNuevo<< i <<" "<< Mx.at(i)<<std::endl;
    }//for
    return true;
}
