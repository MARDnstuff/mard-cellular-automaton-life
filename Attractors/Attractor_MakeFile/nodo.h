#ifndef NODO_H
#define NODO_H
#include <string>
#include <iostream>
#include <vector>

class Nodo{

private:
    unsigned int ID;
    unsigned int size;
    unsigned int l_size;
    std::vector<bool> ID_binary;
    std::vector<std::vector<bool>> matriz;
    unsigned int nextState;
    std::vector<bool> nextSate_binary;
public:
    //Constructor
    Nodo(unsigned int id, unsigned int sz);

    //Regresa ID (decimal)
    unsigned int getID();

    //Regresa el siguientes estado
    unsigned int getNextState();

    //Regresa ID (binario)
    std::vector<bool> getID_binary();

    //Hace la matriz correspondiente a su ID binary
    void setMatrix();

    //Convierte un array de bit a su representacion decimal
    unsigned int convertBinaryToDec(std::vector<bool> binary);

    //Aplica regla R(Smin, Smax, Nmin, Nmax)
    void applyRule(unsigned int Smin, unsigned int Smax,unsigned int Nmin, unsigned int Nmax);


};


#endif // NODO_H
