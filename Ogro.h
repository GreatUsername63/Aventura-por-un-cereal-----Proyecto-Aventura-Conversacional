#include "Personaje.h"

class Ogro : public Personaje{
    public:
        Ogro();
        Ogro(string,float,float,vector<Item*>,Habitacion*,float,string,string,string,string,string,string,bool);
        void fight(Personaje*);
        void habilidad(Personaje*);
};

Ogro::Ogro() : Personaje::Personaje(){
    
}

Ogro::Ogro(string _nombre,float _salud, float _fuerza,vector<Item*> _inventario,
            Habitacion* _ubicacion,float _probCritico,string sayI,string sayF,string sayFC, 
            string sayHabil,string sayH,string sayD,bool _aliado) : Personaje::Personaje(_nombre,
            _salud,_fuerza,_inventario,_ubicacion,_probCritico,sayI,sayF,sayFC,sayHabil,sayH,sayD,_aliado){

}

void Ogro::fight(Personaje* enemigo){
    float chance = (float)(rand() % 101)/100;
    if (chance>probCritico){
        enemigo->setSalud(enemigo->getSalud()-fuerza);
        cout << "El ogro le da un golpe a " << enemigo->getNombre() << endl;
        cout << "\"" << sayFight << "\"" << endl;
        cout << fuerza << " puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
    } else {
        enemigo->setSalud(enemigo->getSalud()-fuerza*3);
        cout << "SMAAAAAAAAAAAAAASH!!!" << endl;
        cout << "El ogro le da un golpezote critico a " << enemigo->getNombre() << endl;
        cout << "\"" << sayFightCrit << "\"" << endl;
        cout << fuerza*3 << " devastantes puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
    }
}

void Ogro::habilidad(Personaje* enemigo){
    cout << "--HABILIDAD RUGIDO--" << endl;
    cout << "El ogro le ruge fuertemente a " << enemigo->getNombre() << endl;
    cout << "Se le reduce la fuerza de ataque a " << enemigo->getNombre() << endl;
    enemigo->setFuerza(enemigo->getFuerza()*0.75);//Reduce el ataque al 75%
}