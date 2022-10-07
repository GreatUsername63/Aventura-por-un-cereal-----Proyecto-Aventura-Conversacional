#include "Item.h"

class Baston : public Item{//El baston para la secuencia de la roca
    public:
        Baston();
        Baston(string,string,string,string,bool,string);
        bool Usar(string);
};

Baston::Baston() : Item::Item(){

}

Baston::Baston(string n,string nc,string desc, string uS, bool ag, string lugU) : Item::Item(n,nc,desc,uS,ag,lugU){
    
}

bool Baston::Usar(string lugarU){
    if(lugarU == lugarUso){//Si es el lugar correcto
        cout << usarString << endl;
        return true;
    }
    return false;
}