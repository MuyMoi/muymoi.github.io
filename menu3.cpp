#include <iostream>
#include <ctype.h>
#include <iomanip>
#include <fstream>
using namespace std;

#define LIMPIAR system("clear");
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
  //Estudiante(string id,string n,string c,int e, float n1,float n2,float n3)
  //: ID(id), nombre(n), carrera(c), edad(e) {
  //  notas[0]=n1, notas[1]=n2, notas[2]=n3;
  //}

  string id() { return ID; }
  string NOMBRE() { return nombre; }
  string CARRERA() { return carrera; }
  int EDAD() {return edad; }
  float NOTA(int c) {return notas[c-1]; } //c : corte
  float def() { return notas[0]*0.3 + notas[1]*0.35 + notas[2]*0.35; }

  void mostrar() {
    cout << fixed << setprecision(1) << left;
    
    int tam=nombre.length();
    int pos;
    if (tam>30)
      pos=nombre.find(" ", 17);
    else
      pos=tam;
    
    cout << setw(a1) << ID << setw(a2) << nombre.substr(0,pos) << setw(a2) << carrera << setw(a3)
    << edad << setw(a3) << notas[0] << setw(a3) << notas[1] << setw(a3) << notas[2]
    << setw(a4) << def() << endl;
    
    if (tam>30) {
      cout << setw(10) << "";
      cout << nombre.substr(pos) << endl;
    }
  }

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

    ID=s;
    ID[0] = 'T';
    return true;
  }
  bool asgnrnombre(string s) {
    if (s.length() == 0) {
      cout << "No puede dejar el campo nombre vacio\n\n";
      return false;
    }
    if (s.find(",") != -1) {
      cout << "No puede introducir comas\n\n";
      return false;
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
  bool asgnredad(int n) {
    if (n <= 1 or n >= 130) { //asumiré estos limites
      cout << "Edad no valida\n\n";
      return false;
    }
    edad=n;
    return true;
  }
  bool asgnredad(string x) {
    if (x.length() == 0) {
      cout << "No puede dejar el campo edad vacio\n\n";
      return false;
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
    if (n < 0 or n > 5) {
      cout << "Nota no valida\n\n";
      return false;
    }
    notas[c-1]=n;
    return true;
  }
  bool asgnrnota(string x, int c){
    if (x.length() == 0) {
      cout << "No puede dejar el campo vacio\n\n";
      return false;
    }
    int n;
    try {
      n = stof(x);
    }
    catch(...) {
      n = -1;
    }
    return asgnrnota(n,c);
  }
  void pedirnombre() {
    string s; cout << "Digitar nombre: "; getline(cin, s);
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
    string x;
    cout << "Digite la edad: "; getline(cin,x);
    if (!asgnredad(x)) {
      pediredad();
      return;
    }
  }
  void pedirnota(int c) { // c: corte
    if (c < 1 or c >3)
      return;

    string x;
    cout << "Digite la nota del corte " << c << ": ";
    getline(cin,x);
    
    if (!asgnrnota(x,c)) {
      pedirnota(c);
      return;
    }
  }
};

class ListaEst {
private:
  Estudiante *V;
  int tam;

  void encabezado() {
    cout << left;
    cout << setw(a1) << "Codigo" << setw(a2) << "Nombre" << setw(a2) << "Carrera" << setw(a3)
    << "Edad" << setw(a3) << "N1" << setw(a3) << "N2" << setw(a3) << "N3"
    << setw(a4) << "DEF" << endl;
  }

  void guiones() {
    cout << setfill('_') << setw(ANCHO) << "" << endl << setfill(' ');
  }

  void redimensionar(int n) {
    if (n<=0) return;

    Estudiante *aux= new Estudiante[tam+n];
    for (int i = 0; i < tam; i++)
      aux[i] = V[i];

    delete[] V;
    V=aux;
    tam += n;
  }

  int buscarpos() { //retorna la posicion del ID buscado
    if (tam==0) {
      cout << "\tNo hay ningun estudiante\n\n";
      return -2;
    }

    string codigo;
    cout << "Escriba el codigo a buscar: ";
    getline(cin, codigo);

    for (int i = 0; i < tam; i++){
      if (codigo == V[i].id()) {
        return i;
      }
    }

    cout << "\tNo se encontraron coincidencias\n\n";
    return -1;
  }

public:
  int TAM() {
    return tam;
  }

  ListaEst(int t) {
    tam=t;
    V=new Estudiante[tam];
  }

  void cargarDatos() {
    ifstream a("datos.csv");
    string x;
    int i=0;

    while (getline(a,x)) {
      redimensionar(1);
      int p1,p2,p3,p4,p5,p6,p7;

      p1=x.find(',');      
      if (  V[i].asgnrID(x.substr(0,p1))  ) {
        p2 = x.find(',',p1+1);
        V[i].asgnrnombre(x.substr(p1+1,p2-p1-1));
        p3 = x.find(',',p2+1);
        V[i].asgnrcarrera(x.substr(p2+1,p3-p2-1));
        p4 = x.find(',',p3+1);
        V[i].asgnredad(x.substr(p3+1,p4-p3-1));
        p5 = x.find(',',p4+1);
        V[i].asgnrnota(x.substr(p4+1,p5-p4-1), 1);
        p6 = x.find(',',p5+1);
        V[i].asgnrnota(x.substr(p5+1,p6-p5-1), 2);
        p7 = x.find(',',p6+1);
        V[i].asgnrnota(x.substr(p6+1,p7-p6-1), 3);

        i++;
      }
      else {
        tam--;
      }
    }

    a.close();
  }

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
    V[p].pedirnota(1);
    V[p].pedirnota(2);
    V[p].pedirnota(3);

    cout << "\n     Creado correctamente\n\n";
  }

  void mostrar(){
    if (tam==0) {
      cout << "   No hay ningun estudiante\n\n";
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

    if (p>=0){
      string x=" ";

      while (x != "4") {
        LIMPIAR

        cout << "\n\n\tM E N U   D E   M O D I F I C A C I O N\n"
        "\tEstudiante " << V[p].id() <<
        "\n\n1. Modificar nombre\t"
        "[Actual: " << V[p].NOMBRE() << "]\n"
        "2. Modificar carrera\t"
        "[Actual: " << V[p].CARRERA() << "]\n"
        "3. Modificar edad\t"
        "[Actual: " << V[p].EDAD() << "]\n"
        "4. Volver al menu principal\n\n";

        cout << "--Digite la opcion que desea modificar: ";
        getline(cin, x);

        if (x.length()!=1) {
          cout << "Opcion no valida\n";
          cout << "Presione ENTER para continuar:\n"; getchar(); 
          continue;
        }

      
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
          cout << "Volviendo al menu principal...\n";
          break;
        default:
          cout << "Opcion no valida\n";
        }

        if (opc!=4) {
          cout << "Presione ENTER para continuar:\n"; getchar();   
        }
      }
    }
  }

  void guardardatos() {
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
    LIMPIAR
    cout << "\tM E N U   D E L   D O C E N T E\n"
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

    if (x.length()!=1) {
      cout << "\nIntroduzca una opcion valida\n";
      continue;
    }

    cout << setw(30) << "";

    int opc = x[0] - '0';
    switch (opc) {
    case 1:
      LIMPIAR
      cout << "C R E A R   E S T U D I A N T E\n\n";
      L.crear();
      break;
    case 2:
      LIMPIAR
      cout << "L I S T A D O\n\n";
      L.mostrar();
      break;
    case 3:
      LIMPIAR
      cout << "B U S C A R   E S T U D I A N T E\n\n";
      L.buscar();
      break;
    case 4:
      LIMPIAR
      cout << "B O R R A R   E S T U D I A N T E\n\n";
      L.borrar();
      break;
    case 5:
      LIMPIAR
      cout << "M O D I F I C A R   E S T U D I A N T E\n\n";
      L.modificar();
      break;
    case 6:
      break;
    case 7:
      cout << "Saliendo...\n";
      break;
    default:
      cout << "\nIntroduzca una opcion valida\n";

    }

    cout << "Presione ENTER para continuar:";
    getchar();
  }

  L.guardardatos();

  return 0;
}