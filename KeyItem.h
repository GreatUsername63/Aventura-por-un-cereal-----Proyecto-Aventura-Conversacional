#include "Item.h"

class KeyItem : public Item{//Items clave para hacer el cereal
    public:
        KeyItem();
        KeyItem(string,string,string,string,bool,string);
        bool Usar(string);
        void printHacer();
};

KeyItem::KeyItem() : Item::Item(){

}

KeyItem::KeyItem(string n,string nc,string desc, string uS, bool ag, string lugU) : Item::Item(n,nc,desc,uS,ag,lugU){
    
}

bool KeyItem::Usar(string lugarU){
    cout << "No puedes usar este item hasta que hagas el cereal." << endl;
    cout << "Cuando tengas todos los ingredientes, selecciona la accion en el menu." << endl;
    return true; //No se puede usar este item con la funcion Usar normal.
}

void KeyItem::printHacer(){ //Imprime los resultados en la parte de (Hacer) cereal
    cout << usarString << endl;
}