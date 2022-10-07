#include "Personaje.h"

class Guerrero : public Personaje{
    private:
        float ataqueExtra; //Puntos de fuerza extra que se cargan con la habilidad
    public:
        Guerrero();
        Guerrero(string,float,float,vector<Item*>,Habitacion*,float,string,string,string,string,string,string,bool);
        void fight(Personaje*);
        void habilidad(Personaje*);
};

Guerrero::Guerrero() : Personaje::Personaje(){
    ataqueExtra = 0;
}

Guerrero::Guerrero(string _nombre,float _salud, float _fuerza,vector<Item*> _inventario,
                     Habitacion* _ubicacion,float _probCritico,string sayI,string sayF,string sayFC, 
                     string sayHabil,string sayH,string sayD,bool _aliado) : Personaje::Personaje(_nombre,
                     _salud,_fuerza,_inventario,_ubicacion,_probCritico,sayI,sayF,sayFC,sayHabil,sayH,sayD,_aliado){
    ataqueExtra = 0;
}

void Guerrero::fight(Personaje* enemigo){
    float chance = (float)(rand() % 101)/100;
    if (chance>probCritico){
        enemigo->setSalud(enemigo->getSalud()-(fuerza+ataqueExtra));
        cout << "Le das un espadazo a " << enemigo->getNombre() << "." << endl;
        cout << "\"" << sayFight << "\"" << endl;
        cout << fuerza+ataqueExtra << " puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl; //CAMBIO para sumar ataque extra
    } else { 
        enemigo->setSalud(enemigo->getSalud()-(fuerza*3+ataqueExtra));
        cout << "SMAAAAAAAAAAAAAASH!!!" << endl;
        cout << "Consigues dar un golpe critico al enemigo!" << endl;
        cout << "\"" << sayFightCrit << "\"" << endl;
        cout << fuerza*3+ataqueExtra << " devastantes puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
    }
    ataqueExtra = 0;
}

void Guerrero::habilidad(Personaje* enemigo){
    cout << "--HABILIDAD ESPADA MAGICA--" << endl;
    cout << "Usas el poder de tu espada para conseguir mas fuerza de ataque." << endl;
    cout << "\"" << sayHabilidad << "\"" << endl;
    ataqueExtra += 50; //Da 50 puntos de ataque extra
    cout << "Conseguiste 50 puntos de fuerza extra para el proximo ataque" << endl;
}