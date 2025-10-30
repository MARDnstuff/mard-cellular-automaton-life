#include "mynodo.h"

//mantener positivo
int positive_(unsigned long int n, unsigned long int size){
    if(n < 0 ){
        int pos_n = n*(-1);
        int res = size - (pos_n%size);
        return res;
    }else{
        return n;
    }//if-else

}

//Constructor
myNodo::myNodo(unsigned long int id, unsigned long int sz){
    this->ID = id;
    this->size = sz*sz;
    this->l_size = sz;
    int i = 0;

    //Conversion a binary
    std::vector<bool> temp;
    while( id > 0){
        temp.push_back(id % 2);
        id/=2;
        i++;
    }//while

    //Padding
    std::vector<bool> temp2(this->size - temp.size(),0);


    for(int j = 1; j <= temp.size(); j++){
        temp2.push_back(temp.at(temp.size() - j));
    }//for

    this->ID_binary = temp2;

}

//Regresa ID (decimal)
unsigned long int myNodo::getID(){
    return this->ID;
}

//Regresa el siguientes estado
unsigned long int myNodo::getNextState(){
    return this->nextState;
}

//Regresa ID (binario)
std::vector<bool> myNodo::getID_binary(){
    return this->ID_binary;
}

//Hace la matriz correspondiente a su ID binary
void myNodo::setMatrix(){
    std::vector<std::vector<bool>> columna;
    unsigned long int k = 0;
    for(unsigned long int i = 0; i < this->l_size; i++){
        std::vector<bool> fila;
        for(unsigned long int j = 0; j < this->l_size; j++, k++){
            fila.push_back(this->ID_binary.at(k));
        }//for
        columna.push_back(fila);
    }//for
    this->matriz = columna;
}


//Convierte un array de bit a su representacion decimal
unsigned long int myNodo::convertBinaryToDec(std::vector<bool> binary){
        unsigned long int dec_value = 0, base = 1;
    //std::cout << binary.size() << std::endl;
        for(long int i = binary.size() - 1; i >= 0; i--) {
            //std::cout <<"i: "<< i << std::endl;
            dec_value += binary.at(i) * base;
            base = base * 2;
        }

        return dec_value;
}

//Aplica regla R(Smin, Smax, Nmin, Nmax)
void myNodo::applyRule(unsigned int Smin, unsigned int Smax, unsigned int Nmin, unsigned int Nmax){

    unsigned long int sizeMx = this->l_size;
    for(unsigned long int i = 0; i< this->l_size; i++){
        for(unsigned long int j = 0; j < this->l_size; j++){
            unsigned int num_neighborhood = 0;
            if(this->matriz.at(positive_(i - 1,sizeMx)%sizeMx).at(j) == 1){ num_neighborhood++; }
            if(this->matriz.at(positive_(i-1,sizeMx)%sizeMx).at((j + 1)%sizeMx) == 1){ num_neighborhood++;}
            if(this->matriz.at(i).at((j + 1)%sizeMx) == 1){ num_neighborhood++;}
            if(this->matriz.at((i + 1)%sizeMx).at((j + 1)%sizeMx) == 1){num_neighborhood++;}
            if(this->matriz.at((i + 1)%sizeMx).at(j) == 1){ num_neighborhood++;}
            if(this->matriz.at((i + 1)%sizeMx).at(positive_(j-1,sizeMx)%sizeMx) == 1){ num_neighborhood++;}
            if(this->matriz.at(i).at(positive_(j-1,sizeMx)%sizeMx) == 1){ num_neighborhood++;}
            if(this->matriz.at((positive_(i -1,sizeMx)%sizeMx)).at(positive_(j -1,sizeMx)%sizeMx) == 1){ num_neighborhood++;}
            //Reglas
            //std::cout <<"[" <<i<<"]"<<"[" <<j<<"]"<< "num_neighborhood: " << num_neighborhood << std::endl;
            if(this->matriz.at(i).at(j) == 0 && (num_neighborhood >= Nmin && num_neighborhood <= Nmax)){
                   this->nextSate_binary.push_back(1);
            }else if(this->matriz.at(i).at(j) == 1 && (num_neighborhood >= Smin && num_neighborhood <= Smax)){
                    this->nextSate_binary.push_back(1);
            }else{
                this->nextSate_binary.push_back(0);
            }

        }//for
    }//for
    //std::cout << "hh2"<< std::endl;
    this->nextState = convertBinaryToDec(this->nextSate_binary);
    //std::cout << this->ID << " ----> "<<this->nextState << std::endl;

}

