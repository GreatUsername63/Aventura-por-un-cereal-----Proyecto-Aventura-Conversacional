#include "Personaje.h"

class Marin : public Personaje{
    private:
        float probCongelar;
    public:
        Marin();
        Marin(string,float,float,vector<Item*>,Habitacion*,float,string,string,string,string,string,string,bool,float);
        void fight(Personaje*);
        void habilidad(Personaje*);
        void setProbCongelar(float);
        void powerUP();
};

Marin::Marin() : Personaje::Personaje(){
    probCongelar = 1;
}

Marin::Marin(string _nombre,float _salud, float _fuerza,vector<Item*> _inventario,
            Habitacion* _ubicacion,float _probCritico,string sayI,string sayF,string sayFC, 
            string sayHabil,string sayH,string sayD,bool _aliado,float probC) : Personaje::Personaje(_nombre,
            _salud,_fuerza,_inventario,_ubicacion,_probCritico,sayI,sayF,sayFC,sayHabil,sayH,sayD,_aliado){
    probCongelar = probC;
}

void Marin::fight(Personaje* enemigo){
    float chance = (float)(rand() % 101)/100;
    if (chance>probCritico){
        enemigo->setSalud(enemigo->getSalud()-fuerza);
        cout << "Marin le da una patada a " << enemigo->getNombre() << "." << endl;
        cout << "\"" << sayFight << "\"" << endl;
        cout << fuerza << " puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
    } else {
        enemigo->setSalud(enemigo->getSalud()-fuerza*3);
        cout << "SMAAAAAAAAAAAAAASH!!!" << endl;
        cout << "No sabes como ocurrio pero Marin le dio un golpe critico a " << enemigo->getNombre() << "." << endl;
        cout << "\"" << sayFightCrit << "\"" << endl;
        cout << fuerza*3 << " devastantes puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
    }
}

void Marin::habilidad(Personaje* enemigo){
    cout << "--HABILIDAD MAGIA DE HIELO--" << endl;
    cout << "Probabilidad del " << probCongelar*100 <<  "% de poder congelar a los enemigos" << endl;
    if (inventario.empty()){
        cout << "Marin no puede congelar a nadie por que tiraste su varita." << endl;
        return;
    }
    float chance = (float)(rand() % 101)/100;
    if (chance<probCongelar){
        cout << "Marin congela a " << enemigo->getNombre() << " por 1 turno." << endl;
        cout << enemigo->getNombre() << " recibe " << fuerza << " puntos de daño por el impacto de congelado" << endl;
        enemigo->setSalud(enemigo->getSalud()-fuerza);
        enemigo->setStun(1);
    }
    else{
        cout << "Marin fallo en congelar al enemigo." << endl;
    }

}

void Marin::setProbCongelar(float nuevo){
    probCongelar = nuevo;
}

void Marin::powerUP(){
    salud = 200;
    fuerza = 60;
    probCritico = 0;
    aliado = false;
    probCongelar = 80;
    sayFight = "Comete esta!!!";
    sayFightCrit = "MUERE!!!";
    sayHabilidad = "Es inutil resistirse...";
    sayHelp = "...............Es neta?";
    sayDefeat = "NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO";
}