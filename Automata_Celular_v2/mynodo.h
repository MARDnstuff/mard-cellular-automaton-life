#ifndef MYNODO_H
#define MYNODO_H
#include <string>
#include <iostream>
#include <vector>

class myNodo{
private:
    unsigned long int ID;
    unsigned long int size;
    unsigned long int l_size;
    std::vector<bool> ID_binary;
    std::vector<std::vector<bool>> matriz;
    unsigned long int nextState;
    std::vector<bool> nextSate_binary;
public:
    //Constructor
    myNodo(unsigned long int id, unsigned long int sz);

    //Regresa ID (decimal)
    unsigned long int getID();

    //Regresa el siguientes estado
    unsigned long int getNextState();

    //Regresa ID (binario)
    std::vector<bool> getID_binary();

    //Hace la matriz correspondiente a su ID binary
    void setMatrix();

    //Convierte un array de bit a su representacion decimal
    unsigned long int convertBinaryToDec(std::vector<bool> binary);

    //Aplica regla R(Smin, Smax, Nmin, Nmax)
    void applyRule(unsigned int Smin, unsigned int Smax,unsigned int Nmin, unsigned int Nmax);



};

#endif // MYNODO_H
