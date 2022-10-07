#include "Personaje.h"

class Delfin : public Personaje{
    private:
        int habilidadCarga;
    public:
        Delfin();
        Delfin(string,float,float,vector<Item*>,Habitacion*,float,string,string,string,string,string,string,bool);
        void fight(Personaje*);
        void habilidad(Personaje*);
};

Delfin::Delfin() : Personaje::Personaje(){
    
}

Delfin::Delfin(string _nombre,float _salud, float _fuerza,vector<Item*> _inventario,
            Habitacion* _ubicacion,float _probCritico,string sayI,string sayF,string sayFC, 
            string sayHabil,string sayH,string sayD,bool _aliado) : Personaje::Personaje(_nombre,
            _salud,_fuerza,_inventario,_ubicacion,_probCritico,sayI,sayF,sayFC,sayHabil,sayH,sayD,_aliado){

}

void Delfin::fight(Personaje* enemigo){ //fight y habilidad son la misma funcion
    cout << "--HABILIDAD INFLARSE DE AGUA--" << endl;
    cout << "El delfin magico se infla de agua lentamente" << endl;
    cout << "cada turno para al final lanzar una ataque devastador." << endl;
    habilidadCarga++;
    int turnosRestantes = 5 - habilidadCarga;
    cout << "\nTurnos restantes para hacer el ataque devastador: " << turnosRestantes << endl;
    cout << "......" << endl;
    if (habilidadCarga>4){ //Cuando termine de cargar
        cout << "El poderoso delfin magico lanza su ataque devastador" << endl;
        cout << "PSHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH" << endl;
        cout << "Infinita cantidad de daño hacia " << enemigo->getNombre() << endl; 
        enemigo->setSalud(0); //Derrota instantanea
    }
}

void Delfin::habilidad(Personaje* enemigo){
    cout << "--HABILIDAD INFLARSE DE AGUA--" << endl;
    cout << "El delfin magico se infla de agua lentamente" << endl;
    cout << "cada turno para al final lanzar una ataque devastador." << endl;
    habilidadCarga++;
    int turnosRestantes = 5 - habilidadCarga;
    cout << "\nTurnos restantes para hacer el ataque devastador: " << turnosRestantes << endl;
    cout << "......" << endl;
    if (habilidadCarga>4){
        cout << "El poderoso delfin magico lanza su ataque devastador" << endl;
        cout << "PSHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH" << endl;
        cout << "Infinita cantidad de daño hacia " << enemigo->getNombre() << endl; 
        enemigo->setSalud(0);
    }
}

