#ifndef Personaje_h
#define Personaje_h

#include "Item.h"
#include "Habitacion.h"

class Personaje{
    protected:
        string nombre;
        float salud;
        float fuerza; //Para los ataques, remplazo de puntaje
        float fuerzaDefault; //valor de Fuerza inicial para cuando se quiera restaurar el valor
        vector<Item*> inventario;
        Habitacion* ubicacion;
        float probCritico; //Probabilidad de acertar un ataque critico que de el triple de daño
        string sayIntro; //Decir al empezar la pelea
        string sayFight; //Al atacar
        string sayFightCrit; //Al lograr un ataque critico
        string sayHabilidad; //Al usar la habilidad
        string sayHelp; //El consejo que te da cuando pides un consejo en la pelea
        string sayDefeat; //Al ser derrotado
        bool aliado; //Si es de los buenos o los malos
        int stun; //Turnos por los que esta conjelado
    public:
        Personaje();
        Personaje(string,float,float,vector<Item*>,Habitacion*,float,string,string,string,string,string,string,bool);
        string getNombre();
        float getSalud();
        void setSalud(float);
        void printInventario();
        vector<Item*> getInventario();
        Habitacion* getUbicacion();
        float getProbCritico();
        void mover(Habitacion*); //setUbicacion basicamente
        void tomarItem(Item*); //Agregar Item al inventario del personaje
        void tirarItem(int); //Eliminar Item del inventario del personaje
        void setStun(int);
        int getStun();
        virtual void fight(Personaje*); //Ataque normal
        virtual void habilidad(Personaje*); //Habilidad especial
        string getHelp();
        string getDefeat();
        string getIntro();
        float getFuerza();
        void setFuerza(float);
        void restoreFuerza(); //Restaurar el valor de fuerza al valor fuerzaDefault
        void decreaseStun(); //Reducir el stun por uno
};

Personaje::Personaje(){
    nombre = "nadie";
    salud = 0;
    fuerza = 0;
    fuerzaDefault = 0;
    probCritico = 0;
    sayIntro = "";
    sayFight = "";
    sayFightCrit = "";
    sayHabilidad = "";
    sayHelp = "";
    sayDefeat = "";
    aliado = false;
    stun = 0;
}

Personaje::Personaje(string _nombre,float _salud, float _fuerza,vector<Item*> _inventario,
                     Habitacion* _ubicacion,float _probCritico,string sayI,string sayF,string sayFC, 
                     string sayHabil,string sayH,string sayD,bool _aliado){

    nombre = _nombre;
    salud = _salud;
    fuerza = _fuerza;
    fuerzaDefault = _fuerza;
    inventario = _inventario;
    ubicacion = _ubicacion;
    probCritico = _probCritico;
    sayIntro = sayI;
    sayFight = sayF;
    sayFightCrit = sayFC;
    sayHabilidad = sayHabil;
    sayHelp = sayH;
    sayDefeat = sayD;
    aliado = _aliado;
    stun = 0;

}

string Personaje::getNombre(){
    return nombre;
}

float Personaje::getSalud(){
    return salud;
}

void Personaje::setSalud(float s){
    salud = s;
}

void Personaje::printInventario(){
    cout << "--------------------------------" << endl;
    cout << "Items de " << nombre << ":" << endl;
    for (int i=0;i<inventario.size();i++){
        inventario[i]->ShowItem();
    }
    cout << "--------------------------------" << endl;
}

vector<Item*> Personaje::getInventario(){
    return inventario;
}

Habitacion* Personaje::getUbicacion(){
    return ubicacion;
}

float Personaje::getProbCritico(){
    return probCritico;
}

void Personaje::mover(Habitacion* newUbicacion){
    ubicacion = newUbicacion;
}

void Personaje::tomarItem(Item* itemNuevo){
    inventario.push_back(itemNuevo);
}

void Personaje::tirarItem(int index){
    inventario.erase(inventario.begin()+index); //Se suma el begin() para que empieze por donde empieza el inventario en la memoria
}

void Personaje::setStun(int s){
    stun = s;
}

int Personaje::getStun(){
    return stun;
}

void Personaje::fight(Personaje* enemigo){
    float chance = (float)(rand() % 101)/100; //numero decimal al azar del 0 al 1
    if (chance>probCritico){ //Hacer un ataque normal
        enemigo->setSalud(enemigo->getSalud()-fuerza);
         cout << "\"" << sayFight << "\"" << endl;
        cout << fuerza << " puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
    } else { //Hacer un ataque especial
        enemigo->setSalud(enemigo->getSalud()-fuerza*3);
        cout << "SMAAAAAAAAAAAAAASH!!!" << endl;
        cout << "\"" << sayFightCrit << "\"" << endl;
        cout << fuerza*3 << " devastantes puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
    }
}

void Personaje::habilidad(Personaje* enemigo){
    enemigo->setSalud(enemigo->getSalud()-fuerza);
    cout << "\"" << sayHabilidad << "\"" << endl; //Aqui no pasa nada aun asi que nomas ataca normalmente
    cout << fuerza << " puntos de daño son inflijidos a " << enemigo->getNombre() << "." << endl;
}

string Personaje::getDefeat(){
    return sayDefeat;
}

string Personaje::getHelp(){
    return sayHelp;
}

string Personaje::getIntro(){
    return sayIntro;
}

float Personaje::getFuerza(){
    return fuerza;
}

void Personaje::setFuerza(float newFuerza){
    fuerza = newFuerza;
}

void Personaje::restoreFuerza(){
    fuerza = fuerzaDefault;
}

void Personaje::decreaseStun(){
    stun--;
}

#endif