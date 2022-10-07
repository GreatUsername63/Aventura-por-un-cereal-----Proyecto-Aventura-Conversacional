#include "Personaje.h"

class Mago: public Personaje{
    public:
        Mago();
        Mago(string,float,float,vector<Item*>,Habitacion*,float,string,string,string,string,string,string,bool);
        void fight(Personaje*);
        void habilidad(Personaje*);
};

Mago::Mago() : Personaje::Personaje(){
    
}

Mago::Mago(string _nombre,float _salud, float _fuerza,vector<Item*> _inventario,
            Habitacion* _ubicacion,float _probCritico,string sayI,string sayF,string sayFC, 
            string sayHabil,string sayH,string sayD,bool _aliado) : Personaje::Personaje(_nombre,
            _salud,_fuerza,_inventario,_ubicacion,_probCritico,sayI,sayF,sayFC,sayHabil,sayH,sayD,_aliado){

}

void Mago::fight(Personaje* enemigo){
    float chance = (float)(rand() % 101)/100;
    if (chance>probCritico){
        enemigo->setSalud(enemigo->getSalud()-fuerza);
        cout << "Le pegas al enemigo con tu baston magico." << endl;
        cout << "\"" << sayFight << "\"" << endl;
        cout << fuerza << " puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
    } else {
        enemigo->setSalud(enemigo->getSalud()-fuerza*3);
        cout << "SMAAAAAAAAAAAAAASH!!!" << endl;
        cout << "Le diste al enemigo justo en la cabeza con tu baston" << endl;
        cout << "\"" << sayFightCrit << "\"" << endl;
        cout << fuerza*3 << " devastantes puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
    }
}

void Mago::habilidad(Personaje* enemigo){
    cout << "--HABILIDAD MAGIA DE FUEGO--" << endl;
    cout << "Atacas al enemigo con magia de fuego!" << endl;
    cout << "\"" << sayHabilidad << "\"" << endl;
    enemigo->setSalud(enemigo->getSalud()-fuerza*1.5); //1.5 veces mas de daño que el ataque normal
    cout << fuerza*1.5 << " puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
}