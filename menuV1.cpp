/*En este programa se usaron conceptos como clases, atributos privados y publicos,
manipuladores de flujo para dar formato a la salida, manejo de archivos de texto,
temporizadores, manejo de vectores dinamicos, encapsulacion y sobrecarga de
funciones que permiten el polimorfismo. El programa presenta una breve pantalla de
carga al comenzar su ejecucion.

Para guardar los datos se usó un archivo de valores separados por comas (csv),
que son archivos de tablas donde cada columna esta delimitada por comas y
cada registro es una linea del archivo. Cuando el programa se ejecuta, comienza
leyendo este archivo y extrayendo los datos, y en caso de haber algun registro
con un ID no valido se presenta una advertencia y se ignora dicho registro. Para
buscar las comas delimitadoras, se usaron los metodos find() y substr() en el
string de la linea leida. Al final del programa, cuando el usuario elige salir,
se guardan todos los cambios.
*/

//Aqui se utiliza un ancho de columna fijo en el formato de tablas

#include <iostream>
#include <ctype.h> //comprobar si un string es numerico
#include <iomanip> //manipulador de flujo o de formato
#include <fstream> //archivos
#include <thread> //para usar un temporizador
#include <chrono> //para usar un temporizador
using namespace std;

//algunas macros
//en la macro LIMPIAR, el comando es "clear" si se trata de Linux o MacOS,
//y "cls" si es Windows
#define LIMPIAR system("cls")
#define ESPERAR(tiempo) this_thread::sleep_for(tiempo)

//constantes de ancho de tablas
#define a1 10
#define a2 31
#define a3 6
#define a4 3
#define ANCHO a1+2*a2+4*a3+a4

class Estudiante {
private:
  string ID;
  string nombre;
  string carrera;
  int edad;
  float notas[3] = {0.0, 0.0, 0.0}; //nota del primer, segundo
  // y tercer corte respectivamente
public:
  Estudiante() : ID(""), nombre(""), carrera(""), edad(0) {}

  //metodos que retornan los valores de los atributos privados
  string id() { return ID; }
  string NOMBRE() { return nombre; }
  string CARRERA() { return carrera; }
  int EDAD() {return edad; }
  float NOTA(int c) {return notas[c-1]; } //c : corte
  float def() { return notas[0]*0.3 + notas[1]*0.35 + notas[2]*0.35; }

  void mostrar() {
    //para obligar a imprimir 1 solo decimal y justificar a la izquierda
    cout << fixed << setprecision(1) << left;


    //si el nombre es muy largo, partirlo en dos lineas

    int tam=nombre.length();
    int pos;       //posicion hasta donde se copiará el nombre en la primera linea
    if (tam>30)
      pos=nombre.find(" ", 17); //partir por el primer espacio despues de la mitad
    else
      pos=tam;
    
    cout << setw(a1) << ID << setw(a2) << nombre.substr(0,pos) << setw(a2) << carrera << setw(a3)
    << edad << setw(a3) << notas[0] << setw(a3) << notas[1] << setw(a3) << notas[2]
    << setw(a4) << def() << endl;
    
    //si es muy largo, imprimo la segunda linea
    if (tam>30) {
      cout << setw(10) << "";
      cout << nombre.substr(pos) << endl;
    }
  }

  //metodos de asignacion y validacion

  bool asgnrID(string s) {
    int tam=s.length(); //tamaño
    bool num=true; //saber si es numerico

    if (tam == 0) {
      cout << "No puede dejar vacio el campo ID\n\n";
      return false;
    }
    for (int i=1; i<tam; i++)
      if (!isdigit( s[i]) ) {
        num=false;
        break;
    }
    if (tam != 9 or (s[0] != 'T' and s[0] != 't') or num==false) {
      cout << "No valido.\n\n";
      return false;
    }

    //si nada salio mal, lo asigno
    ID=s;
    ID[0] = 'T';
    return true;
  }

  bool asgnrnombre(string s) {
    int tam=s.length();
    if (tam == 0) {
      cout << "No puede dejar el campo nombre vacio\n\n";
      return false;
    }
    //no permito comas porque dañaria el formato de almacenamiento
    if (s.find(",") != -1) {
      cout << "No puede introducir comas\n\n";
      return false;
    }
    //tampoco permito numeros
    for (int i=0; i < tam; i++) {
      if (isdigit(s[i])) {
        cout << "No se permiten numeros en el nombre\n\n";
        return false;
      }
    }
    nombre=s;
    return true;
  }

  bool asgnrcarrera(string s) {
    if (s.length() == 0) {
      cout << "No puede dejar el campo carrera vacio\n\n";
      return false;
    }
    if (s.length() > 30) {
      cout << "Nombre muy largo. Trate de acortar a maximo 30 caracteres\n\n";
      return false;
    }
    if (s.find(",") != -1) {
      cout << "No puede introducir comas\n\n";
      return false;
    }
    carrera=s;
    return true;
  }

  //sobrecargo las siguientes funciones para cuando reciben un valor
  //numerico o uno string
  bool asgnredad(int n) {
    if (n <= 5 or n >= 130) { //asumiré estos limites
      cout << "Edad no valida\n\n";
      return false;
    }
    edad=n;
    return true;
  }
  bool asgnredad(string x) {
    int tam = x.length();
    if (tam == 0) {
      cout << "No puede dejar el campo edad vacio\n\n";
      return false;
    }
    for (int i=0; i<tam; i++) {
      if (!isdigit(x[i])) {
        cout << "Edad no valida\n\n";
        return false;
      }
    }
    int n;
    try {
      n = stoi(x);
    }
    catch(...) {
      n = -1;
    }
    return asgnredad(n);
  }

  bool asgnrnota(float n, int c){
    if (n ==0)
      return false;

    if (n < 0.5 or n > 5) {
      cout << "Nota no valida\n\n";
      return false;
    }
    notas[c-1]=n;
    return true;
  }
  bool asgnrnota(string x, int c){
    

    int tam = x.length();
    if (tam == 0) {
      cout << "Nota vacia\n\n";
      return false;
    }
    for (int i=0; i<tam; i++) {
      if (!isdigit(x[i]) && x[i]!= '.') {
        cout << "Nota no valida\n\n";
        return false;
      }
    }
    float n;
    try {
      n = stof(x);
    }
    catch(...) {
      n = -1;
    }
    return asgnrnota(n,c);
  }

  //para pedir los datos usando las validaciones anteriores

  void pedirnombre() {
    cout << "Digitar nombre: ";
    string s; getline(cin, s);
    if (!asgnrnombre(s)) {
      pedirnombre();
      return;
    }
  }
  void pedirID() {
    cout << "Digitar ID (de la forma T12345678): ";
    string s; getline(cin, s);
    if (!asgnrID(s)) {
      pedirID();
      return;
    }
  }
  void pedircarrera() {
    cout << "Digitar la carrera: ";
    string s; getline(cin, s);
    if (!asgnrcarrera(s)) {
      pedircarrera();
      return;
    }
  }
  void pediredad() {
    cout << "Digite la edad: ";
    string s; getline(cin,s);
    if (!asgnredad(s)) {
      pediredad();
      return;
    }
  }
  void pedirnota(int c) { // c: corte
    if (c < 1 or c >3)
      return;

    cout << "Digite la nota (entre 0.5 y 5) del corte " << c << ": ";
    string s; getline(cin,s);
    
    if (s=="0") {
      cout << "Nota no valida\n\n";
      pedirnota(c);
      return;
    }
    if (!asgnrnota(s,c)) {
      pedirnota(c);
      return;
    }
  }
};

//clase que maneja una lista de estudiantes
class ListaEst {
private:
  Estudiante *V;
  int tam;

  //estas funciones son solo de uso interno

  void encabezado() { //encabezado de tabla de datos
    cout << left;
    cout << setw(a1) << "Codigo" << setw(a2) << "Nombre" << setw(a2) << "Carrera" << setw(a3)
    << "Edad" << setw(a3) << "N1" << setw(a3) << "N2" << setw(a3) << "N3"
    << setw(a4) << "DEF" << endl;
  }

  void guiones() { //guiones para separar registros de alumnos
    cout << setfill('_') << setw(ANCHO) << "" << endl << setfill(' ');
  }

  void redimensionar(int n) { //aumentar n veces el tamaño del vector. no reduce
    if (n<=0) return;

    Estudiante *aux= new Estudiante[tam+n];
    for (int i = 0; i < tam; i++)
      aux[i] = V[i];

    delete[] V;
    V=aux;
    tam += n;
  }

  int buscarpos() { //pide y retorna la posicion del ID buscado
    if (tam==0) {
      cout << "\tNo hay ningun estudiante\n\n";
      return -2; //retorna codigo de error
    }
    string codigo;
    cout << "Escriba el codigo a buscar: ";
    getline(cin, codigo);

    int r = buscarpos(codigo);
    if (r==-1)
      cout << "\tNo se encontraron coincidencias\n";
 
    return r; //retorna el resultado de la busqueda
  }

  int buscarpos(string codigo) { //retorna codigos de error si no se encuentra
    if (codigo.length()==9 && codigo[0]=='t')
      codigo[0]='T';

    for (int i = 0; i < tam; i++){
      if (codigo == V[i].id()) {
        return i; //Si se encuentra: retorna mayor o igual a 0
      }
    }

    //No se encuentra
    return -1;
  }

public:
  int TAM() { return tam; } //devuelve el tamaño

  ListaEst(int t) {
    tam=t;
    V=new Estudiante[tam];
  }

  //leer los datos de un archivo
  void cargarDatos() {
    ifstream a("datos.csv");
    string x;
    int i=0;

    while (getline(a,x)) { //se lee linea por linea
      redimensionar(1);
      string codigo;
      int p1,p2,p3,p4,p5,p6,p7; //posiciones de las comas separadoras

      p1=x.find(','); //se busca la primera coma
      codigo = x.substr(0,p1);  //se selecciona el primer pedazo
      cout << "Leyendo datos del estudiante con codigo " << codigo << "\n";
      ESPERAR(300ms);

      if (buscarpos(codigo)>=0) { //codigo repetido
        cout << "Advertencia: codigo " << codigo << " repetido. Se procede a ignorar\n\n";
        tam--;
        ESPERAR(2000ms);
        continue;
      }

      //si se asigno el codigo correctamente, se asignan los demas datos:
      if (  V[i].asgnrID(codigo)  ) { 
        p2 = x.find(',',p1+1);
        V[i].asgnrnombre(x.substr(p1+1,p2-p1-1));
        
        p3 = x.find(',',p2+1);
        V[i].asgnrcarrera(x.substr(p2+1,p3-p2-1));
        
        p4 = x.find(',',p3+1);
        V[i].asgnredad(x.substr(p3+1,p4-p3-1));
        
        p5 = x.find(',',p4+1);
        V[i].asgnrnota(x.substr(p4+1,p5-p4-1), 1);
        
        if (V[i].NOTA(1) != 0) {
          p6 = x.find(',',p5+1);
          V[i].asgnrnota(x.substr(p5+1,p6-p5-1), 2);
          
          if (V[i].NOTA(2) != 0) {
            p7 = x.find(',',p6+1);
            V[i].asgnrnota(x.substr(p6+1,p7-p6-1), 3);
          }
        }

        i++;
      }
      else {
        cout << "Advertencia: codigo " << codigo << " no valido. Se procede a ignorar\n\n";
        tam--; //se reduce el tamaño, pues el metodo redimensionar lo habia aumentado
        ESPERAR(1000ms);
      }
    }
    LIMPIAR;
    cout << "Datos cargados\nCargando interfaz del programa..";
    cout << "\n";
    a.close();
    ESPERAR(1000ms);
  }

  //metodos para usarse en el programa principal

  void crear() {
    redimensionar(1);

    int p=tam-1;

    //Verificar que el nuevo id no este repetido
    bool rep; //repetido
    do {
      V[p].pedirID();
      string nuevoid = V[p].id();

      rep=false;
      for (int i = 0; i < tam-1; i++){
        if (nuevoid == V[i].id()) {
          cout << "Error: ID repetido\n\n";
          rep=true;
          break;
        }
      } 
    } while (rep);

    //lleno los demas datos
    V[p].pedirnombre();
    V[p].pedircarrera();
    V[p].pediredad();

    cout << "\n     Creado correctamente\n\n";
  }

  void mostrar(){
    if (tam==0) {
      cout << "\tNo hay ningun estudiante\n\n";
      return;
    }
    
    encabezado();
    for (int i = 0; i < tam; i++)
    {
      guiones();
      V[i].mostrar();
    }
    cout << "\n\n";
  }

  void buscar() {
    int p= buscarpos();

    if (p>=0){
      cout << "\n     Estudiante encontrado:\n";
      encabezado();
      guiones();
      V[p].mostrar();
      guiones();
    }
  }

  void borrar() {
    int p=buscarpos();

    if (p>=0) {
      cout << "Esta a punto de borrar al siguiente estudiante: \n\n";
      encabezado();
      guiones();
      V[p].mostrar();

      cout << "\nDesea continuar (s:Si, n:No): ";
      string l; getline(cin,l);
      if (l!="s" && l!="S") {
        cout << "Operacion cancelada\n\n";
        return;
      }

      Estudiante *aux= new Estudiante[tam-1];
      for (int i=0; i<p; i++)
        aux[i] = V[i];
      for (int i=p; i < tam-1; ++i)
        aux[i] = V[i+1];
      delete[] V;
      V=aux;
      tam--;

      cout << "\n     Borrado correctamente\n\n";
    }
  }

  void modificar() {
    int p=buscarpos();

    if (p>=0) {
      string x=" ";

      while (x != "7") {
        LIMPIAR;

        cout << "\n\n\tM E N U   D E   M O D I F I C A C I O N\n"
        "\tEstudiante " << V[p].id() <<
        "\n\n1. Modificar nombre\t\t"
        "[Actual: " << V[p].NOMBRE() << "]\n"
        "2. Modificar carrera\t\t"
        "[Actual: " << V[p].CARRERA() << "]\n"
        "3. Modificar edad\t\t"
        "[Actual: " << V[p].EDAD() << "]\n"
        "4. Modificar nota corte 1\t"
        "[Actual: " << V[p].NOTA(1) << "]\n"
        "5. Modificar nota corte 2\t"
        "[Actual: " << V[p].NOTA(2) << "]\n"
        "6. Modificar nota corte 3\t"
        "[Actual: " << V[p].NOTA(3) << "]\n"
        "7. Volver al menu principal\n\n";

        cout << "--Digite la opcion que desea modificar: ";
        getline(cin, x);

        if (x.length()!=1)
          continue;

      
        int opc = x[0]-'0';
        switch (opc) {
        case 1:
          V[p].pedirnombre();
          cout << "    Modificado correctamente\n\n";
          break;
        case 2:
          V[p].pedircarrera();
          cout << "    Modificado correctamente\n\n";
          break;
        case 3:
          V[p].pediredad();
          cout << "    Modificado correctamente\n\n";
          break;
        case 4:
          if (V[p].NOTA(1) == 0)
            cout << "Aun no ha introducido esta nota. Puede hacerlo en el menu Ingresar notas\n\n";
          else {
            V[p].pedirnota(1);
            cout << "    Modificado correctamente\n\n";
          }
          break;
        case 5:
          if (V[p].NOTA(2) == 0)
            cout << "Aun no ha introducido esta nota. Puede hacerlo en el menu Ingresar notas\n\n";
          else {
            V[p].pedirnota(2);
            cout << "    Modificado correctamente\n\n";
          }
          break;
        case 6:
          if (V[p].NOTA(3) == 0)
            cout << "Aun no ha introducido esta nota. Puede hacerlo en el menu Ingresar notas\n\n";
          else {
            V[p].pedirnota(3);
            cout << "    Modificado correctamente\n\n";
          }
          break;
        case 7:
          cout << "Volviendo al menu principal...\n";
          break;
        default:
          cout << "Opcion no valida\n";
        }

        if (opc!=7) {
          cout << "Presione ENTER para continuar:\n"; getchar();   
        }
      }
    }
  }

  void intronotas() {
    int p=buscarpos();

    if (p>=0){
      cout << "Estudiante: " << V[p].NOMBRE() << "\n\n";
      string x; int c=-1;
      while (true) {
        cout << "En que corte desea la nota (escriba 0 para salir): "; getline(cin,x);
        if (x.length()==1) 
          c = x[0] - '0';
        if (c==0)
          break;
        if (c<1 or c>3) {
          cout << "Numero de corte no valido\n\n";
          continue;
        }
        
        bool asignar=true; //para permitir o no asignar la nota
  
        //verifico si existen todas las notas de cortes anteriores
        for (int t=1; t<c; t++)
          if (V[p].NOTA(t)==0) {
            cout << "No puede introducir la nota del corte " << c
                 << " porque no ha introducido la del corte " << t
                 << "\n\n";
            asignar= false;
            break;
          }
        
        if (asignar) {
          if (V[p].NOTA(c) == 0) {
            V[p].pedirnota(c);
            cout << "\tNota ingresada\n\n";
            break;
          }
          else {
            cout << "Este estudiante ya cuenta con nota para este corte."
              "Intente con otro corte o en el menu modificar\n\n";
          }
        }
      }
    }
  }

  void guardardatos() {

    cout << "Guardando datos...\n";
    ofstream o("datos.csv");

    for (int i=0; i<tam; i++) {
      o << V[i].id() << "," << V[i].NOMBRE() << ","
        << V[i].CARRERA() << "," << V[i].EDAD() << ","
        << V[i].NOTA(1) << "," << V[i].NOTA(2) << ","
        << V[i].NOTA(3) << endl;
    }

    o.close();
  }

};


int main() {
  ListaEst L(0);
  L.cargarDatos();

  string x="";
  while (x !="7") {
    LIMPIAR;
    cout << setw(30) << "" << "M E N U   D E L   D O C E N T E\n\n"
    "1.Crear estudiante\n"
    "2.Mostrar listado\n"
    "3.Buscar estudiante\n"
    "4.Borrar estudiante\n"
    "5.Modificar estudiante\n"
    "6.Ingresar notas del estudiante\n"
    "7.Salir\n\n"
    "Numero de estudiantes: " << L.TAM() << "\n\n";

    cout << "--Digite la opcion del 1 al 7: ";
    getline(cin,x);

    if (x.length()!=1)
      continue;

    int opc = x[0] - '0';
 
    if (opc >=1 && opc <=6) {
      LIMPIAR;
      cout << setw(30) << "";
    }

    switch (opc) {
    case 1:
      cout << "C R E A R   E S T U D I A N T E\n\n";
      L.crear();
      break;
    case 2:
      cout << "L I S T A D O\n\n";
      L.mostrar();
      break;
    case 3:
      cout << "B U S C A R   E S T U D I A N T E\n\n";
      L.buscar();
      break;
    case 4:
      cout << "B O R R A R   E S T U D I A N T E\n\n";
      L.borrar();
      break;
    case 5:
      cout << "M O D I F I C A R   E S T U D I A N T E\n\n";
      L.modificar();
      break;
    case 6:
      cout << "I N G R E S A R   N O T A S\n\n";
      L.intronotas();
      break;
    case 7:
      cout << "Saliendo...\n";
      break;
    default:
      cout << "\nIntroduzca una opcion valida\n";
    }

    if (opc != 7) {
      cout << "Presione ENTER para continuar:";
      getchar();
    }
  }

  L.guardardatos();
  ESPERAR(2000ms);

  return 0;
}