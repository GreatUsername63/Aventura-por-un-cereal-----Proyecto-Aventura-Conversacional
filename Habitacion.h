#ifndef Habitacion_h
#define Habitacion_h

#include "Item.h"

class Habitacion{
    private:
        string name;
        string sayDesc; //Descripcion de la habitacion
        string sayHelp; //Consejo
        string sayGolpear; //Texto cuando golpeas algo de la habitacion
        vector<Item*> vectorItems; //Items en la habitacion
        string salidas[4]; //Vector con el nombre de las 4 salidas de la habitacion.Norte,sur,este,oeste en ese orden.
        bool clearRoom; //Si el objetivo de la habitacion ha sido completado
        string clearDesc; //Descripcion nueva para la habitacion completada
    public:
        Habitacion();
        Habitacion(string,string,string,string,vector<Item*>,string,string,string,string,string);
        string getName();
        string getSalidas(string); //Retorna salida depende de la direccion que le des
        void printDesc();
        string getHelp();
        vector<Item*> getItems(); //Retorna el vector de los items de la habitacion
        void setItems(vector<Item*>); //Remplaza el vector de los items en la habitacion
        void printItems();
        void eraseItem(int); //Borra cierto index de la lista de items
        void printGolpear(); //Imprime sayGolpear
        void setClear(bool); //Dice si la habitacion se completo o no
};

Habitacion::Habitacion(){
    name = "Ningun lugar";
    sayDesc = "Esta habitacion no existe";
    sayHelp = "Nada";
    sayGolpear = "Golpeas al aire y no pasa nada";
    clearRoom = false;
    clearDesc = "No se";
    salidas[0] = "n";
    salidas[1] = "n";
    salidas[2] = "n";
    salidas[3] = "n";
}

Habitacion::Habitacion(string n,string desc,string help,string golpear,vector<Item*> vItems,string salida1,string salida2,string salida3,string salida4,string cDesc){
    name = n;
    sayDesc = desc;
    sayHelp = help;
    sayGolpear = golpear;
    vectorItems = vItems;
    salidas[0] = salida1;
    salidas[1] = salida2;
    salidas[2] = salida3;
    salidas[3] = salida4;
    clearRoom = false;
    clearDesc = cDesc;
}

string Habitacion::getName(){
    return name;
}

string Habitacion::getSalidas(string dir){
    if (dir == "n"){//Norte es 0
        return salidas[0];
    }
    if (dir == "s"){//Sur es 1
        return salidas[1];
    }
    if (dir == "e"){//Este es 2
        return salidas[2];
    }
    if (dir == "o"){//Oeste es 3
        return salidas[3];
    }
    return "n"; //"n" quiere decir que no hay habitacion ahi
}

void Habitacion::printDesc(){
    if(clearRoom){
        cout << clearDesc << endl; //Si la habitacion esta completa imprimir la nueva descripcion
    }
    else{
        cout << sayDesc << endl;
    }
}

string Habitacion::getHelp(){
    return sayHelp;
}

vector<Item*> Habitacion::getItems(){
    return vectorItems;
}

void Habitacion::setItems(vector<Item*> nuevosItems){
    vectorItems = nuevosItems;
}

void Habitacion::printItems(){
    cout << "-----------------------" << endl;
    if(vectorItems.empty()){//Si no hay items
        cout << "En este lugar no hay ningun item." << endl;
    }
    else{
        cout << "En este lugar estan los siguientes objetos:" << endl;
        for (int i=0;i<vectorItems.size();i++){
            cout << i+1 << ". ";
            vectorItems[i]->ShowItem();
        }
    }
    cout << "-----------------------" << endl;
}

void Habitacion::eraseItem(int index){
    vectorItems.erase(vectorItems.begin()+index);
}

void Habitacion::printGolpear(){
    cout << sayGolpear << endl;
}

void Habitacion::setClear(bool newState){
    clearRoom = newState;
}

#endif