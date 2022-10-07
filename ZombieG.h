#include "Personaje.h"

class ZombieG : public Personaje{
    public:
        ZombieG();
        ZombieG(string,float,float,vector<Item*>,Habitacion*,float,string,string,string,string,string,string,bool);
        void fight(Personaje*);
        void habilidad(Personaje*);
};

ZombieG::ZombieG() : Personaje::Personaje(){
    
}

ZombieG::ZombieG(string _nombre,float _salud, float _fuerza,vector<Item*> _inventario,
            Habitacion* _ubicacion,float _probCritico,string sayI,string sayF,string sayFC, 
            string sayHabil,string sayH,string sayD,bool _aliado) : Personaje::Personaje(_nombre,
            _salud,_fuerza,_inventario,_ubicacion,_probCritico,sayI,sayF,sayFC,sayHabil,sayH,sayD,_aliado){

}

void ZombieG::fight(Personaje* enemigo){
    float chance = (float)(rand() % 51)/100; //CAMBIO ahora es un numero entre 0 y 0.5 para tener mas probabilidad de hacer critoco
    if (chance>probCritico){
        cout << "El zombie le da un golpe con su pico a " << enemigo->getNombre();
        enemigo->setSalud(enemigo->getSalud()-fuerza);
        cout << "\"" << sayFight << "\"" << endl;
        cout << fuerza << " puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
    } else {
        enemigo->setSalud(enemigo->getSalud()-fuerza*3);
        cout << "SMAAAAAAAAAAAAAASH!!!" << endl;
        cout << "El zombie le da un fuerte golpe en la cabeza a " << enemigo->getNombre();
        cout << "\"" << sayFightCrit << "\"" << endl;
        cout << fuerza*3 << " devastantes puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
    }
}

void ZombieG::habilidad(Personaje* enemigo){
    cout << "--HABILIDAD ZOMBIE SUPER UTIL--" << endl;
    cout << "urg............................" << endl; //jjajaj no hace nada x2
    cout << "NO HAY EFECTO" << endl;
}