#include "Personaje.h"

class Slime : public Personaje{
    public:
        Slime();
        Slime(string,float,float,vector<Item*>,Habitacion*,float,string,string,string,string,string,string,bool);
        void fight(Personaje*);
        void habilidad(Personaje*);
};


Slime::Slime() : Personaje::Personaje(){
    
}

Slime::Slime(string _nombre,float _salud, float _fuerza,vector<Item*> _inventario,
            Habitacion* _ubicacion,float _probCritico,string sayI,string sayF,string sayFC, 
            string sayHabil,string sayH,string sayD,bool _aliado) : Personaje::Personaje(_nombre,
            _salud,_fuerza,_inventario,_ubicacion,_probCritico,sayI,sayF,sayFC,sayHabil,sayH,sayD,_aliado){

}


void Slime::fight(Personaje* enemigo){
    float chance = (float)(rand() % 101)/100;
    if (chance>probCritico){
        enemigo->setSalud(enemigo->getSalud()-fuerza);
        cout << "El slime se tambalea y le da un golpe a " << enemigo->getNombre() << endl;
        cout << "\"" << sayFight << "\"" << endl;
        cout << fuerza << " puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
    } else {
        enemigo->setSalud(enemigo->getSalud()-fuerza*3);
        cout << "SMAAAAAAAAAAAAAASH!!!" << endl;
        cout << "\"" << sayFightCrit << "\"" << endl;
        cout << fuerza*3 << " devastantes puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
    }
}

void Slime::habilidad(Personaje* enemigo){
    cout << "--HABILIDAD TAMBALEO--" << endl;
    cout << "El slime se agita como gelatina" << endl; //jjajajaj no hace nada
    cout << "NO HAY EFECTO" << endl;
}