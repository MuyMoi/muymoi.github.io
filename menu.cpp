#include <iostream>
#include <ctype.h>
using namespace std;

class Estudiante {
private:
  string ID;
  string nombre;
  string carrera;
  int edad;
  float notas[3] = {0.0, 0.0, 0.0}; //nota del primer, segundo
  // y tercer corte respectivamente
public:
  void mostrar() {
    cout << "  -- DATOS DEL ESTUDIANTE: --\n";
    cout << "ID: " << ID << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Carrera: " << carrera << endl;
    cout << "Edad: " << edad << endl;
    cout << "Nota corte 1: " << notas[0] << endl;
    cout << "Nota corte 2: " << notas[1] << endl;
    cout << "Nota corte 3: " << notas[2] << endl;
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
  }

  void pedircarrera() {
    cout << "Digitar la carrera: "; getline(cin, carrera);
    if (carrera.length() == 0) {
      cout << "No puede dejar el campo carrera vacio\n\n";
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

  void llenar() {
    pedirID();
    pedirnombre();
    pedircarrera();
    pediredad();
    pedirnota(1);
    pedirnota(2);
    pedirnota(3);
  }
};

int main() {
  Estudiante est;

  est.llenar();
  getchar();

  string opc;
  while (opc !="7") {
    system("clear");
    cout << "    ---MENU DEL DOCENTE---\n"
    << "1.Crear\n"
    << "2.Mostrar\n"
    << "3.Buscar\n"
    << "4.Borrar\n"
    << "5.Modificar\n"
    << "6.Notas\n"
    << "7.Salir\n\n";

    cout << "--Digite la opcion del 1 al 7: ";
    getline(cin,opc);

    if (opc == "1") {
    }
    else if (opc== "2") {
    }
    else if (opc == "3") {}
    else if (opc == "4") {}
    else if (opc == "5") {}
    else if (opc == "6") {}

    else if (opc == "7")
      cout << "Saliendo...\n";

    else
      cout << "\nIntroduzca una opcion valida\n";

    cout << "Presione ENTER para continuar:\n";
    getchar();
  }

  return 0;
}
