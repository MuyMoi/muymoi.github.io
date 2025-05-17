#include <iostream>
#include <ctype.h>
#include <iomanip>
using namespace std;

#define LIMPIAR system("cls");
#define a1 10
#define a2 31
#define a3 5
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
    
    if (nombre.length()>30) {
      cout << setw(10) << "";
      cout << nombre.substr(pos) << endl;
    }
  }

  void pedirnombre() {
    cout << "Digitar nombre: "; getline(cin, nombre);
    if (nombre.length() == 0) {
      cout << "No puede dejar el campo nombre vacio\n\n";
      pedirnombre();
      return;
    }
  }

  void pedirID() {
    cout << "Digitar ID (de la forma T12345678): ";
    getline(cin, ID);

    int tam=ID.length(); //tamaño
    bool num=true; //saber si es numerico

    if (tam == 0) {
      cout << "No puede dejar vacio el campo ID\n\n";
      pedirID();
      return;
    }
/**/
    for (int i=1; i<tam; i++)
      if (!isdigit(ID[i])) {
        num=false;
        break;
    }
    if (tam != 9 or ID[0] != 'T' or num==false) {
      cout << "Valor erroneo.\n\n";
      pedirID();
      return;
    }
/**/
  }

  void pedircarrera() {
    cout << "Digitar la carrera: "; getline(cin, carrera);
    if (carrera.length() == 0) {
      cout << "No puede dejar el campo carrera vacio\n\n";
      pedircarrera();
      return;
    }
    if (carrera.length() > 30) {
      cout << "Nombre muy largo. Trate de acortar a maximo 30 caracteres\n\n";
      pedircarrera();
      return;
    }
  }

  void pediredad() {
    string x;
    cout << "Digite la edad: "; getline(cin,x);
    if (x.length() == 0) {
      cout << "No puede dejar el campo edad vacio\n\n";
      pediredad();
      return;
    }
    try {
      edad = stoi(x);
    }
    catch(...) {
      edad = -1;
    }
    if (edad <= 1 or edad >= 150) { //asumiré estos limites
      cout << "Edad no valida\n\n";
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
    if (x.length() == 0) {
      cout << "No puede dejar el campo vacio\n\n";
      pedirnota(c);
      return;
    }
    try {
      notas[c-1] = stof(x);
    }
    catch(...) {
      notas[c-1] = -1;
    }
    if (notas[c-1] < 0 or notas[c-1] > 5) {
      cout << "Nota no valida\n\n";
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
    cout << setfill('-') << setw(ANCHO) << "" << endl << setfill(' ');
  }

public:
  int TAM() {
    return tam;
  }

  ListaEst(int t) {
    tam=t;
    V=new Estudiante[tam];
  }

  int buscarpos() { //retorna la posicion del ID buscado
    if (tam==0) {
      cout << "   No hay ningun estudiante\n\n";
      return -2;
    }

    string codigo;
    cout << "Escriba el codigo a buscar: ";
    getline(cin, codigo);

    if (codigo.length() == 0) {
      cout << "No deje el campo vacio\n\n";
      return buscarpos();
    }

    for (int i = 0; i < tam; i++){
      if (codigo == V[i].id()) {
        return i;
      }
    }

    cout << "     No se encontraron coincidencias\n\n";
    return -1;
  }

  void crear() {
    Estudiante *aux= new Estudiante[tam+1];
    for (int i = 0; i < tam; i++)
      aux[i] = V[i];

    aux[tam] = Estudiante();
    delete[] V;
    V=aux;
    tam++;

    //Verificar que el nuevo id no este repetido
    bool rep; //repetido
    do {
      V[tam-1].pedirID();
      string nuevoid = V[tam-1].id();

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
    /**/V[tam-1].pedirnombre();
    V[tam-1].pedircarrera();
    V[tam-1].pediredad();
    V[tam-1].pedirnota(1);
    V[tam-1].pedirnota(2);
    V[tam-1].pedirnota(3);/**/

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

};


int main() {
  ListaEst L(0);

  string x="";
  while (x !="7") {
    LIMPIAR
    cout << "\tM E N U   D E L   D O C E N T E\n"
    << "1.Crear estudiante\n"
    << "2.Mostrar listado\n"
    << "3.Buscar estudiante\n"
    << "4.Borrar estudiante\n"
    << "5.Modificar estudiante\n"
    << "6.Ingresar notas del estudiante\n"
    << "7.Salir\n\n";
    cout << "Numero de estudiantes: " << L.TAM() << "\n\n";

    cout << "--Digite la opcion del 1 al 7: ";
    getline(cin,x);

    if (x.length()!=1) {
      cout << "\nIntroduzca una opcion valida\n";
      continue;
    }

    int opc = x[0] - '0';
    switch (opc) {
    case 1:
      LIMPIAR
      cout << "\tC R E A R   E S T U D I A N T E\n";
      L.crear();
      break;
    case 2:
      LIMPIAR
      cout << "\tL I S T A D O\n";
      L.mostrar();
      break;
    case 3:
      LIMPIAR
      cout << "\tB U S C A R   E S T U D I A N T E\n";
      L.buscar();
      break;
    case 4:
      LIMPIAR
      cout << "\tB O R R A R   E S T U D I A N T E\n";
      L.borrar();
      break;
    case 5:
      LIMPIAR
      cout << "\tM O D I F I C A R   E S T U D I A N T E\n";
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

  return 0;
}