#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //Para usar find
#include <cstdlib> //Para usar "pause" y "cls" en system()
#include <time.h> //Para generar la seed de random
using namespace std;

//Desfile de .h
#include "Baston.h"
#include "KeyItem.h"
#include "Habitacion.h"
#include "Guerrero.h"
#include "Mago.h"
#include "Marin.h"
#include "Delfin.h"
#include "ZombieG.h"
#include "Slime.h"
#include "Ogro.h"

int indexHabitacion(vector<Habitacion*> vectorH,string nombreHabitacion){
    //Encuentra una habitacion por su nombre
    for (int i;i<vectorH.size();i++){
        if (vectorH[i]->getName()==nombreHabitacion){
            return i;
        }
    }
    return -1;
}

int indexItem(vector<Item*> vectorItems,string nombreItem){
    //Encuentra unItem por su nombre corto
    for (int i;i<vectorItems.size();i++){
        if (vectorItems[i]->getNombreCorto()==nombreItem){
            return i;
        }
    }
    return -1;
}

int hayEnemigos(vector<Personaje*> vectorP,Habitacion *habitacionActual){
    //Ve si en la habitacion se encuentra un enemigo
    for (int i;i<vectorP.size();i++){
        if (vectorP[i]->getUbicacion()==habitacionActual){
            return i;
        }
    }
    return -1;
}

//----------------------------------------------------------------------------------------------------------------------
//======================================================================================================================
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//======================================================================================================================
//----------------------------------------------------------------------------------------------------------------------


void fightSequence(Personaje *protagonista, Personaje *asistente, Personaje *enemigo){
    //SECUENCIA DE PELEA COMUN
    //variables iniciales
    string opcion = "";
    float chance = 0;
    Personaje* enemigoTarget = 0; //A quien atacara el enemigo en el turno
    bool protagonistaDefeated = false; //Bool para cada quien para ver quien ha sido derrotado
    bool asistenteDefeated = false;
    bool enemigoDefeated = false;

    while(true){ //Ciclo de pelea


        while(true){ //Ciclo turno de protagonista
            system("cls");
            cout << "====Pelea contra " << enemigo->getNombre() << "====" << endl; //Que pelea es y de quien es turno?
            cout << "====Turno de: " << protagonista->getNombre() << "====" << endl;
            if (protagonistaDefeated){ //Si ya esta derrotado
                cout << protagonista->getNombre() << " no tiene salud para pelear." << endl;
                system("pause");
                break;//Saltar turno
            }
            cout << "----------------------------------------" << endl;
            cout << protagonista->getNombre() << "->" << "Salud: " << protagonista->getSalud() << endl;
            cout << asistente->getNombre() << "->" << "Salud: " << asistente->getSalud() << endl;
            cout << enemigo->getNombre() << "->" << "Salud: " << enemigo->getSalud() << endl; //Imprimir nombre y salud
            cout << "----------------------------------------" << endl;
            cout << "Opciones: Atacar | Habilidad | Consejo" << endl; //Opciones
            cout << "Introduce tu eleccion: ";
            cin >> opcion;
            cout << endl;

            if(opcion == "Atacar"){//Ataca al enemigo
                system("cls");
                protagonista->fight(enemigo); 
                system("pause");
                break;
            }
            else if(opcion == "Habilidad"){//Usa su habilidad
                system("cls");
                protagonista->habilidad(enemigo); 
                system("pause");
                break;
            }
            else if(opcion == "Consejo"){//Pide un consejo a marin
                system("cls");
                cout << "Le pides un consejo a marin:" << endl;
                cout << "Marin dice: " << endl;
                cout << "\"" << enemigo->getHelp() << "\"" << endl;
                system("pause");
            }
            else{ //opcion incorrecta
                cout << "No entendi tu eleccion. Intentalo de nuevo." << endl;
                system("pause");
            }
        }

        enemigoDefeated = enemigo->getSalud()<=0; //Checa si el enemigo ha sido derrotado
        if (enemigoDefeated) break; //Si es asi, termina la pelea

        while (true){ //ciclo de asistente
            system("cls");
            cout << "====Pelea contra " << enemigo->getNombre() << "====" << endl;
            cout << "====Turno de: " << asistente->getNombre() << "====" << endl;
            if (asistenteDefeated){
                cout << asistente->getNombre() << " no tiene salud para pelear." << endl;
                system("pause");
                break;
            }
            cout << "----------------------------------------" << endl;
            cout << protagonista->getNombre() << "->" << "Salud: " << protagonista->getSalud() << endl;
            cout << asistente->getNombre() << "->" << "Salud: " << asistente->getSalud() << endl;
            cout << enemigo->getNombre() << "->" << "Salud: " << enemigo->getSalud() << endl;
            cout << "----------------------------------------" << endl;
            cout << "Opciones: Atacar | Habilidad" << endl;
            cout << "Introduce tu eleccion: ";
            cin >> opcion;
            cout << endl;

            if(opcion == "Atacar"){
                system("cls");
                asistente->fight(enemigo);
                system("pause");
                break;
            }
            else if(opcion == "Habilidad"){
                system("cls");
                asistente->habilidad(enemigo);
                system("pause");
                break;
            }
            //Omite consejo por que ni modo que se pidiera un consejo a si mismo.
            else{
                cout << "No entendi tu eleccion. Intentalo de nuevo." << endl;
                system("pause");
            }
        }

        enemigoDefeated = enemigo->getSalud()<=0; //Checar si derroto al enemigo
        if (enemigoDefeated) break;

        //Turno del enemigo
        system("cls");
        cout << "====Pelea contra " << enemigo->getNombre() << "====" << endl;
        cout << "====Turno de: " << enemigo->getNombre() << "====" << endl;
        if(enemigo->getStun()>0){ //Ver si esta congelado el enemigo
            cout << enemigo->getNombre() << " esta congelado y no puede atacar." << endl;
            system("pause");
            enemigo->decreaseStun();
            continue; //vuelve al principio del ciclo de pelea
        }
        chance = (rand() % 2); //Numero aleatorio 0 o 1
        if(chance==0){//Usar chance para ver si ataca al protagonista o al asistente en su turno
            enemigoTarget = protagonista;
            if (protagonistaDefeated){enemigoTarget = asistente;} //Para que ataque al otro si esta sin salud
        } 
        else{
            enemigoTarget = asistente;
            if (asistenteDefeated){enemigoTarget = protagonista;}
        }

        chance = (rand() % 2); //Numero aleatorio 0 o 1 (otra vez)
        if(chance==0){//Usa chance para ver que tipo de ataque hace
            enemigo->fight(enemigoTarget);
        } 
        else{
            enemigo->habilidad(enemigoTarget);
        }
        system("pause");

        protagonistaDefeated = protagonista->getSalud()<=0; //Checa si prota o asistente han sido derrotados
        asistenteDefeated = asistente->getSalud()<=0;
        if(protagonistaDefeated&&asistenteDefeated){ //Si ambos son derrotados, termina la pelea.
            break;
        }
    }//Fin del ciclo de pelea


    //Despues de la pelea
    system("cls");
    cout << "============FIN DE LA PELEA============" << endl;
    if(enemigoDefeated){//En caso de ganar
        cout << enemigo->getNombre() << " ha sido derrotado." << endl;
        cout << "\"" <<enemigo->getDefeat() << "\"" << endl;
        enemigo->mover(new Habitacion()); //Lo mueve a una habitacion desconocida nueva para que no aparezca en el vectorHabitaciones.
        cout << "\n" << protagonista->getNombre() << " y " << asistente->getNombre() << " recuperan su salud con magia." << endl;
        //Restaura su salud
        protagonista->setSalud(200);
        asistente->setSalud(180);
        //Restaura fuerza en caso de ataques que bajen fuerza
        protagonista->restoreFuerza();
        asistente->restoreFuerza();
        system("pause");
        system("cls");
    }
    if(protagonistaDefeated){//En caso de perder
        cout << "HAS SIDO DERROTADO" << endl;
        cout << "NO PUDISTE COMPLETAR TU MISION" << endl;
        cout << "GAME OVER." << endl;
        while (true){} //Se atora el programa aqui
    }
    
    
}

//----------------------------------------------------------------------------------------------------------------------
//======================================================================================================================
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//======================================================================================================================
//----------------------------------------------------------------------------------------------------------------------

void FinalFight(Personaje *protagonista, Personaje *enemigo){ //Modificacion de fight para 2 personajes
    string opcion = "";
    float chance = 0;
    bool protagonistaDefeated = false;
    bool enemigoDefeated = false;

    while (true)
    {
        while(true){ //Ciclo turno de protagonista
            system("cls");
            cout << "============BATALLA FINAL============" << endl;
            cout << "====Turno de: " << protagonista->getNombre() << "====" << endl;
            if(protagonista->getStun()>0){//Ver si fue congelado
                cout << protagonista->getNombre() << " esta congelado y no puede atacar." << endl;
                system("pause");
                break; //salta el turno
            }
            cout << "----------------------------------------" << endl;
            cout << protagonista->getNombre() << "->" << "Salud: " << protagonista->getSalud() << endl;
            cout << enemigo->getNombre() << "->" << "Salud: " << enemigo->getSalud() << endl;
            cout << "----------------------------------------" << endl;
            cout << "Opciones: Atacar | Habilidad | Consejo" << endl;
            cout << "Introduce tu eleccion: ";
            cin >> opcion;
            cout << endl;

            if(opcion == "Atacar"){
                system("cls");
                protagonista->fight(enemigo);
                system("pause");
                break;
            }
            else if(opcion == "Habilidad"){
                system("cls");
                protagonista->habilidad(enemigo);
                system("pause");
                break;
            }
            else if(opcion == "Consejo"){
                system("cls");
                cout << "Le pides un consejo a marin:" << endl;
                cout << "Marin dice: " << endl;
                cout << "\"" << enemigo->getHelp() << "\"" << endl;
                system("pause");
            }
            else{
                cout << "No entendi tu eleccion. Intentalo de nuevo." << endl;
                system("pause");
            }
        }

        enemigoDefeated = enemigo->getSalud()<=0;
        if (enemigoDefeated) break;

        //Turno del enemigo
        system("cls");
        cout << "============BATALLA FINAL============" << endl;
        cout << "====Turno de: " << enemigo->getNombre() << "====" << endl;


        //No decide un objetivo aqui por que es 1 versus 1
        if (indexItem(enemigo->getInventario(),"Varita")!=-1){//Si el enemigo tiene "Varita" en sus items, que solamente haga la habilidad
            enemigo->habilidad(protagonista);
            system("pause");
        }
        else{
            chance = (rand() % 2); //Numero aleatorio 0 o 1 (otra vez)
            if(chance==0){
                enemigo->fight(protagonista);
            } 
            else{
                enemigo->habilidad(protagonista);
            }
            system("pause");
        }

        protagonistaDefeated = protagonista->getSalud()<=0;
        if(protagonistaDefeated) break;
        
    }

    //FINAL MALO
    system("cls");
    if(protagonistaDefeated){
        cout << "Intentaste pelear contra Marin pero perdiste" << endl;
        cout << "ya que el tiene demasiado poder." << endl;
        system("pause");
        system("cls");
        cout << "final malo.";
        while (true){} //Se atora el programa aqui
    }
    //FINAL BUENO
    if(enemigoDefeated){
        cout << "DERROTASTE AL JEFE FINAL" << endl;
        cout << "Despues de derrotar a Marin en combate," << endl;
        cout << "el efecto de la pocima malvada se va." << endl;
        cout << "Marin despierta como era originalmente y" << endl;
        cout << "te suplicas que lo disculpes por su crimen." << endl;
        system("pause");
        system("cls");
        cout << "Tu le contestas: " << endl;
        cout << "\"Simon we pero solo si me invitas a desayunar \nal elba o algo.\"" << endl;
        system("pause");
        system("cls");
        cout << "Y asi, termina una aventura bastante ridiculesca que" << endl;
        cout << "se pudo haber resuelto desde el principio si el protagonista" << endl;
        cout << "hubiera preferido ir al super en vez de a un bosque magico." << endl;
        cout << " _______ _________ _        _______  _          ______            _______  _        _______ " << endl;
        cout << "(  ____ \\\\__   __/( (    /|(  ___  )( \\        (  ___ \\ |\\     /|(  ____ \\( (    /|(  ___  )" << endl;
        cout << "| (    \\/   ) (   |  \\  ( || (   ) || (        | (   ) )| )   ( || (    \\/|  \\  ( || (   ) |" << endl;
        cout << "| (__       | |   |   \\ | || (___) || |        | (__/ / | |   | || (__    |   \\ | || |   | |" << endl;
        cout << "|  __)      | |   | (\\ \\) ||  ___  || |        |  __ (  | |   | ||  __)   | (\\ \\) || |   | |" << endl;
        cout << "| (         | |   | | \\   || (   ) || |        | (  \\ \\ | |   | || (      | | \\   || |   | |" << endl;
        cout << "| )      ___) (___| )  \\  || )   ( || (____/\\  | )___) )| (___) || (____/\\| )  \\  || (___) |" << endl;
        cout << "|/       \\_______/|/    )_)|/     \\|(_______/  |/ \\___/ (_______)(_______/|/    )_)(_______)" << endl;
        while (true){} //Se atora el programa aqui
    }
    
}

//----------------------------------------------------------------------------------------------------------------------
//======================================================================================================================
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//======================================================================================================================
//----------------------------------------------------------------------------------------------------------------------

int main(){

    srand(time(NULL)); //Generar semilla random

    //Definicion de tooodas las instancias de objetos
    KeyItem malvaviscos("Malvaviscos magicos","Malvaviscos","Malvaviscos cargados con poder magico.","Pones los malvaviscos en un plato hondo.",false,"all");
    KeyItem trigo("Trigo de ultratumba","Trigo","Trigo cultivado por los muertos.","Conviertes el trigo de ultratumba a cereal con magia.",true,"all");
    KeyItem leche("Leche de pantano","Leche","Leche de dudosa procedencia, la preferida de los ogros.","Hechas la leche en el tazon.",true,"all");
    Item piedra("Piedra misteriosa","Piedra","Grande piedra misteriosa con letras brillantes en un idioma extraño.","...",false,"Ningun lugar");
    KeyItem hoja("Receta para el cereal magico","Receta","Encontraste la receta secreta para el cereal magico!","Lees la receta para hacer el cereal magico.",true,"all");
    Baston baston("Baston misterioso","Baston","Baston misterioso con escrituras en un lenguaje extraño grabadas.","Usas el Baston frente a la Piedra misteriosa y de repente ambos items desaparecen! Se revela que la hoja debajo de la piedra es en realidad la receta secreta para el cereal magico!",true,"Lugar misterioso");
    Item hielo("Varita de magia de hielo","Varita","La varita de magia de hielo de marin. La necesita para hacer su magia.","",true,"Ningun lugar");

    vector<Item*> nuevoVectorItem{}; //Vectores para las habitaciones y personajes
    vector<Item*> corazonItems{&malvaviscos};
    vector<Item*> sembradioItems{&trigo};
    vector<Item*> pantanoItems{&leche,&baston};
    vector<Item*> misteriosoItems{&piedra};
    vector<Item*> marinItems{&hielo};
    
    Habitacion entradaBosque("Entrada del bosque","Llegas a la entrada del bosque donde no se puede ver mas que solo arboles...","Aqui ya no hay nada que hacer, debemos entrar al bosque.","Golpeas a un arbol cerca de la entrada. \nTe cae una manzana en la cabeza y recuerdas la existencia de la fuerza de gravedad.",nuevoVectorItem,"Corazon del bosque","n","n","n","Ya derrotaste al slime, no hay nada que hacer aqui.");
    Habitacion corazonBosque("Corazon del bosque","Ahora estas en el corazon y centro del bosque, donde se encuentra un gran arbol lleno de malvaviscos. El arbol es tan grande que no puedes alcanzar los mavaviscos que necesitas","Debe haber una manera de hacer que el arbol nos de los malvaviscos...","Golpeas el gran arbol de malvaviscos y los malvaviscos caen del arbol.",
                              corazonItems,"Pantano del ogro","Entrada del bosque","Lugar misterioso","Sembradio de trigo de ultratumba","Conseguiste los malvaviscos y ahora puedes continuar para ir por los demas items.");
    Habitacion sembradio("Sembradio de trigo de ultratumba","En este lugar hay un sembradio de trigo de ultratumba, lo que es justo lo que necesitas para hacer el cereal magico.","Tres tristes tigre tlaga... ah no me salio mal","Golpeas el suave suelo del sembradio. \nTe enlodas las manos y marin te empieza a ver raro.",sembradioItems,"n","n","Corazon del bosque","n",
                         "Derrotaste al zombi de ultratumba, ahora el sembradio esta libre de muertos vivientes.");
    Habitacion lugarPiedra("Lugar misterioso","En este lugar hay una piedra misteriosa. Tiene grabadas unas letras brillantes en un idioma que no conoces. Se puede ver la esquina de una hoja que esta debajo de la piedra.","La verdad no tengo ni la menor idea de que hacer aqui...","Golpeas al aire sin razon aparente. \nLe das a una mosca por error. Pobre mosca.",misteriosoItems,"n","n","n","Corazon del bosque","En esta habitacion pudiste conseguir la receta secreta para el cereal. No hay nada mas que hacer aqui.");
    Habitacion pantano("Pantano del ogro","Aqui hay un pantano. Aqui debe de estar la leche del pantano.","Jasjasj como el shrek","Golpeas el pupitre de donde salio el ogro.\nSe cae y se derrama lo que esta dentro. Salvese quien pueda.",pantanoItems,"n","Corazon del bosque","n","n","Ya derrotaste al ogro que estaba en este pantano.");
    Habitacion ningunaHabitacion("","","","",nuevoVectorItem,"n","n","n","n","");
    
    vector<Habitacion*> vectorHabitaciones{&entradaBosque,&corazonBosque,&sembradio,&lugarPiedra,&pantano}; //Todas las habitaciones

    Slime slime("Slime pegajoso",100,20,nuevoVectorItem,&entradaBosque,0.01,"...Pero de repente, un slime salvaje aparece!","Los slimes no hablan (creo)","Sabias que este ataque es del 1% de probabilidad?","Du de harlem sheik","Este slime es el enemigo mas facil del juego. Si podemos contra el.","aughhhhhhhhhhhhhhh",false);
    ZombieG zombieGranjero("Zombie granjero",180,30,nuevoVectorItem,&sembradio,0.5,"...Pero de entre el trigo sale el zombie granjero que lo planto!","Ugh!","UGRGH!!!","ugh..........","Este zombie tiene un pico poderoso que puede lanzar ataques criticos mas facilmente.","ugh.",false);
    Ogro shrek("Ogro feroz",200,40,nuevoVectorItem,&pantano,0.2,"...Pero de un pupitre cerca del pantano sale un ogro feroz!!!","Pum te pego!","Salganse de mi pantano!!!","ROOAAAARRRR!!!!!!","Este ogro tiene la habilidad de rugirte y bajar tu fuerza de ataque de un susto.","Hola, soy shrek y estas viendo Disney channel!! *c muere*",false);
    Delfin gigense("Delfin de la dimension gigenkeska",1000,0,nuevoVectorItem,&ningunaHabitacion,0,"...","...","...","...","No hay que dejar que cargue su ataque!!!","AAAAAAAA MMLVWASDFGH!!!!",false);
    Marin marin("Marin",180,40,marinItems,&ningunaHabitacion,0.1,"...","Hiyaaaa","Pas!!!","Congelatium chistosium","...","aaaaaaaaaaa",false,0.4);

    vector<Personaje*> vectorPersonajes{&slime,&zombieGranjero,&shrek,&gigense,&marin}; //Todos los personajes
    //IMPORTANTE: el vector esta organizado para que el delfin sea [3], marin [4] y el protagonista
    //que se agregara mas tarde sera [5]

    system("cls");

    cout << "==========AVENTURA POR UN CEREAL==========" << endl;
    cout << "Bienvenido a esta aventura de texto donde" << endl;
    cout << "exploraras un bosque encantado y tendras que pelear" << endl;
    cout << "contra varios personajes para conseguir" << endl;
    cout << "el glorioso cereal magico." << endl;

    system("pause");
    system("cls");

    cout << "Selecciona un nombre para tu personaje:" << endl;
    string protaNombre;
    cin >> protaNombre;

    string protaClase;
    
    //Define las 2 clases para poder seleccionar 1
    Guerrero protagonistaGuerrero(protaNombre,200,40,nuevoVectorItem,new Habitacion(),0.2,"","Toma esto!","Toma ya!","YO TENGO EL PODER!!!!!!!!","...","Noooooooooo",true);
    Mago protagonistaMago(protaNombre,200,50,nuevoVectorItem,new Habitacion(),0.4,"","Abracadabra!","Abra-se para alla!","Fayer!","...","Noooooooooo",true);
    
    //Seleccion:
    while (true)
    {
        cout << "\nSelecciona la clase de tu personaje: " << endl; //-------------Quieres ser mago o guerrero?---------------
        cout << "Guerrero o Mago?" << endl;
        cin >> protaClase;
        if (protaClase == "Guerrero"){
            vectorPersonajes.push_back(&protagonistaGuerrero); 
            break;
        }
        if (protaClase == "Mago"){
            vectorPersonajes.push_back(&protagonistaMago);
            break;
        }
        cout << "No comprendi tu respuesta. Intenta de nuevo" << endl;//-------------------------------------------------------
    }

    //vectorPersonajes[5] ahora es el protagonista.
    
    system("cls");

    cout << "Tu aventura comienza una manana en tu casa cerca del bosque, te levantas y buscas que desayunar, pero te das cuenta de que no hay nada para hacerte desayuno. Ahi es cuando llega un joven mago de hielo y conocido tuyo, Marin, quien te cuenta una leyenda de un cereal magico que te deja sin hambre por una semana. Para hacer el cereal se necesitan 3 ingredientes: Trigo de ultratumba, Malvaviscos magicos y leche de pantano." << endl;
    cout << "Asi es como, tu y Marin, salen al bosque en una aventura en la que tendran que conseguir los 3 ingredientes para poder conseguir el cereal magico." << endl;
    
    system("pause");

    //Variables de inicialización.
    string nombreUbicacionActual = "Entrada del bosque"; //Nombre de la ubicacion
    Habitacion *ubicacionActual = vectorHabitaciones[0]; //Objeto de la ubicacion
    vector<Item*> itemsUbicacionActual = ubicacionActual->getItems(); //Items de la ubicacion
    Item* itemAUsar = 0; //Item que se quiere usar (en la parte de (Usar) item)
    int indexUbicacionActual = 0; //index de la ubicacion en vectorHabitaciones
    int indexEnemigoActual = 0; //index del enemigo en la ubicacion (si hay uno)
    Personaje *enemigoActual = vectorPersonajes[0]; //la instancia de enemigo actual
    string opcion = ""; //String de input
    int objetoATomarIndex = -1; //Index del item que se quiere tomar (en la parte de (Tomar) item)
    bool usarSucess = false; //Si se pudo usar el item




















    bool hasMalvaviscos = false; //Bool para verificar que cada objeto clave este ahi
    bool hasTrigo = false;
    bool hasLeche = false;
    bool hasReceta = false;

    //Gameloop
    while(true){
        system("cls");
        indexUbicacionActual = indexHabitacion(vectorHabitaciones,nombreUbicacionActual);
        ubicacionActual = vectorHabitaciones[indexUbicacionActual];
        cout << "========" << "Estas en: " << nombreUbicacionActual << "========" << endl;
        ubicacionActual->printDesc();

        indexEnemigoActual = hayEnemigos(vectorPersonajes,ubicacionActual);
        if (indexEnemigoActual!=-1){ //Si hay enemigos --------------------PELEAR------------------------
            enemigoActual = vectorPersonajes[indexEnemigoActual];
            cout << enemigoActual->getIntro() << endl;
            system("pause");
            fightSequence(vectorPersonajes[5],vectorPersonajes[4],vectorPersonajes[indexEnemigoActual]);
            ubicacionActual->setClear(true);
            continue;
        }
        
        ubicacionActual->printItems();
        cout << "Que haces?" << endl;
        cout << "| Moverte | (Tomar) item | (Tirar) item | (Ver) items |" << endl;
        cout << "| (Usar) item | (Golpear) algo | (Hacer) cereal | Ayuda |" << endl;

        cin >> opcion;

        if (opcion == "Moverte"){//-----------------------MOVERSE---------------------------------
            cout << "Hacia que direccion? ((n)orte,(s)ur,(e)ste,(o)este" << endl;
            cin >> opcion;
            if(ubicacionActual->getSalidas(opcion)=="n"){ //"n" es que no hay habitacion
                cout << "No hay nada hacia esa direccion" << endl;
                system("pause");
            }
            else{
            nombreUbicacionActual = ubicacionActual->getSalidas(opcion);
            }
        }

        if (opcion == "Tomar"){//----------------------TOMAR ITEMS-----------------------------
            cout << "Que objeto quieres tomar? (Solo primera palabra)" << endl;
            cin >> opcion;
            itemsUbicacionActual = ubicacionActual->getItems();
            objetoATomarIndex = indexItem(itemsUbicacionActual,opcion);
            if(objetoATomarIndex == -1){//Si no se encontro nada
                cout << "Este item no esta en la habitacion" << endl;
                cout << "o no se escribio correctamente." << endl;
            }
            else if(itemsUbicacionActual[objetoATomarIndex]->esAgarrable()){//Si es agarrable
                vectorPersonajes[5]->tomarItem(itemsUbicacionActual[objetoATomarIndex]);
                ubicacionActual->eraseItem(objetoATomarIndex);
                cout << itemsUbicacionActual[objetoATomarIndex]->getNombreCorto() << " agarrad@(s) exitosamente." << endl;
            }
            else{//No es agarrable
                cout << "Este item no es agarrable." << endl;
            }
            system("pause");
        }

        if (opcion == "Tirar"){//----------------------TIRAR ITEMS-----------------------------
            system("cls");
            vectorPersonajes[5]->printInventario(); //Protagonista
            vectorPersonajes[4]->printInventario(); //Marin

            cout << "ADVERTENCIA: TIRAR ITEMS IMPORTANTES PUEDE PERJUDICAR LA PARTIDA!" << endl;
            cout << "Que objeto quieres tirar? (Solo primera palabra)" << endl;
            cin >> opcion;

            itemsUbicacionActual = vectorPersonajes[5]->getInventario(); //Items de prota
            objetoATomarIndex = indexItem(itemsUbicacionActual,opcion);
            if(objetoATomarIndex!=-1){
                vectorPersonajes[5]->tirarItem(objetoATomarIndex);
                cout << itemsUbicacionActual[objetoATomarIndex]->getNombreCorto() << " tirad@(s) exitosamente." << endl;
                system("pause");
            }

            if(objetoATomarIndex==-1){//Si no se encontro nada en el primero
                itemsUbicacionActual = vectorPersonajes[4]->getInventario(); //Items de marin
                objetoATomarIndex = indexItem(itemsUbicacionActual,opcion);
                if(objetoATomarIndex!=-1){
                    vectorPersonajes[4]->tirarItem(objetoATomarIndex);
                    cout << itemsUbicacionActual[objetoATomarIndex]->getNombreCorto() << " tirad@(s) exitosamente." << endl;
                    system("pause");
                }

                if(objetoATomarIndex == -1){
                    cout << "El item no esta en tu inventario o" << endl;
                    cout << "esta mal escribido." << endl;
                    system("pause");
                }
            }
            
        }

        if (opcion == "Ver"){ //Ver inventario
            vectorPersonajes[5]->printInventario();
            system("pause");
        }

        if (opcion == "Usar"){ //Usar un objeto
            system("cls");
            vectorPersonajes[5]->printInventario(); //Protagonista

            cout << "Que objeto quieres utilizar? (Solo primera palabra)" << endl;
            cin >> opcion;
            itemsUbicacionActual = vectorPersonajes[5]->getInventario(); //Items de prota
            objetoATomarIndex = indexItem(itemsUbicacionActual,opcion);
            usarSucess = false;
            if(objetoATomarIndex!=-1){
                itemAUsar = itemsUbicacionActual[objetoATomarIndex];
                usarSucess = itemAUsar->Usar(nombreUbicacionActual);
                if((usarSucess)&&(itemAUsar==&baston)){
                    misteriosoItems = {&hoja}; //Remplaza la piedra por la hoja
                    ubicacionActual->setItems(misteriosoItems);
                    vectorPersonajes[5]->tirarItem(objetoATomarIndex);
                    ubicacionActual->setClear(true);
                }
                if (!usarSucess){
                    cout << "No se puede usar el objeto en esta habitacion." << endl;
                }
            }
            else{
                cout << "No se encontro ese objeto. Escriba bien, baboso." << endl;
            }
            system("pause");
        }

        if (opcion == "Golpear"){//Textos comicos y parte de malvaviscos
            ubicacionActual->printGolpear();
            if (ubicacionActual==&corazonBosque){
                malvaviscos.setAgarrable(true);
                ubicacionActual->setClear(true);
            }
            system("pause");
        }

        if (opcion == "Hacer"){ //------------------------------------HACER EL CEREAL Y ACESSO A LOS FINALES---------------------------------
            hasMalvaviscos = (indexItem(vectorPersonajes[5]->getInventario(),malvaviscos.getNombreCorto()) != -1); //Checa que el objeto este ahi
            hasTrigo = (indexItem(vectorPersonajes[5]->getInventario(),trigo.getNombreCorto()) != -1);
            hasLeche = (indexItem(vectorPersonajes[5]->getInventario(),leche.getNombreCorto()) != -1);
            hasReceta = (indexItem(vectorPersonajes[5]->getInventario(),hoja.getNombreCorto()) != -1);

            if(hasMalvaviscos&&hasLeche&&hasTrigo){
                system("cls");
                if(hasReceta){
                    hoja.printHacer();
                }
                malvaviscos.printHacer();
                trigo.printHacer();
                leche.printHacer();
                if(hasReceta){//Si tiene la receta ir hacia la batalla final verdadera
                    //final fight
                    cout << "Lograste hacer el cereal magico!!!!!....." << endl;
                    system("pause");
                    system("cls");
                    cout << "pero justo cuando estas a punto de comertelo llega" << endl;
                    cout << "Marin y te roba el cereal! Marin luego dice:" << endl;
                    cout << "\"Muajajaja, todo esto fue una mentira. Esto no es un cereal magico." << endl;
                    cout << "Es una pocima de poder maligno y te engañe para que me ayudaras a" << endl;
                    cout << "conseguir los ingredientes.\"" << endl;
                    marin.powerUP();
                    cout << "Marin despues procede a tomarse la pocima y consigue bastante poder." << endl;
                    cout << "Marin te empieza a atacar." << endl;
                    system("pause");
                    system("cls");
                    cout << "Comienza la verdadera...................................." << endl;
                    cout << "  ____        _        _ _          __ _             _ _ " << endl;
                    cout << " |  _ \\      | |      | | |        / _(_)           | | |" << endl;
                    cout << " | |_) | __ _| |_ __ _| | | __ _  | |_ _ _ __   __ _| | |" << endl;
                    cout << " |  _ < / _` | __/ _` | | |/ _` | |  _| | '_ \\ / _` | | |" << endl;
                    cout << " | |_) | (_| | || (_| | | | (_| | | | | | | | | (_| | |_|" << endl;
                    cout << " |____/ \\__,_|\\__\\__,_|_|_|\\__,_| |_| |_|_| |_|\\__,_|_(_)" << endl;
                    system("pause");
                    FinalFight(vectorPersonajes[5],vectorPersonajes[4]);
                }

                //pelea contra el delfin - final neutral - no tener la receta
                cout << "Lograste juntar los ingredientes del cereal..." << endl;
                cout << "pero por no saber como prepararlo, terminas invocando una creatura maligna por error!" << endl;
                cout << "Del tazon donde estabas intentando hacer el cereal, sale un delfin en 4 patas y te empieza a atacar!!!!" << endl;
                system("pause");
                marin.setProbCongelar(0.7); //Se le da mas prob. de congelar a Marín para la pelea
                fightSequence(vectorPersonajes[5],vectorPersonajes[4],vectorPersonajes[3]);
                system("cls");
                cout << "Derrotaste al extraño Delfin y estas a salvo..." << endl;
                cout << "pero por no haber hecho el cereal correctamente" << endl;
                cout << "te quedaste sin desayunar." << endl;
                system("pause");
                system("cls");
                cout << "===============================================" << endl;
                cout << "=================FINAL NEUTRAL=================" << endl;
                cout << "===============================================" << endl;
                while (true){} //Se atora el programa aqui


            }else{ //No tener uno de los 3 ingredientes
                cout << "Todavía quedan items para hacer el cereal por recolectar." << endl;
                cout << "Haz el cereal hasta que los encuentres todos." << endl;
                system("pause");
            }
        }


        if (opcion == "Ayuda"){
            cout << "Le pides un consejo a marin:" << endl;
            cout << "Marin dice: " << endl;
            cout << "\"" << ubicacionActual->getHelp() << "\"" << endl;
            system("pause");
        }


    }

    return 0;
}

//|`  \      //
//  ----(c^:)//
//|´  /      //

//Mono a palos oficial. Hecho por Santiago Ramirez Enriquez.
//No se cuantas lineas son por que son varios archivos.