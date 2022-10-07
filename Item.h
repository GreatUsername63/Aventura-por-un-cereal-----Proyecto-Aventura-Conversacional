#ifndef Item_h
#define Item_h

class Item{
    protected:
        string nombre; 
        string ncorto; //nombre corto para los comandos en el gameloop
        string descripcion;
        string usarString; //string para cuando se use el Item
        bool agarrable; //Si el jugador tiene permitido tomar este objeto
        string lugarUso; //Nombre del lugar donde se debe usar
    public:
        Item();
        Item(string,string,string,string,bool,string);
        virtual bool Usar(string); //Funcion polimorfica de uso. Retorna true si si se puede usar el item.
        void ShowItem(); //Mostrar item en el inventario
        bool esAgarrable(); //getAgarrable basicamente
        void setAgarrable(bool);
        string getNombreCorto();

};

Item::Item(){
    nombre = "nada";
    ncorto = "n";
    descripcion = "nada";
    usarString = "este objeto no hace nada";
    agarrable = false;
    lugarUso = "Ningun lugar";
}

Item::Item(string n,string nc,string desc, string uS, bool ag, string lugU){
    nombre = n;
    ncorto = nc;
    descripcion = desc;
    usarString = uS;
    agarrable = ag;
    lugarUso = lugU;
}

bool Item::Usar(string lugarU){
    cout << usarString << endl;
    return true;
}

void Item::ShowItem(){
    cout << nombre << " | " << descripcion << " | ";
    if(agarrable){
        cout << "Agarrable" << endl;
    }
    else{
        cout << "No agarrable" << endl;
    }
}

bool Item::esAgarrable(){
    return agarrable;
}

void Item::setAgarrable(bool a){
    agarrable = a;
}

string Item::getNombreCorto(){
    return ncorto;
}

#endif