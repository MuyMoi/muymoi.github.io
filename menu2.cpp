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
  string id() {
    return ID;
  }

	void mostrar() {
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
    }
    for (int i = 0; i < tam; i++)
    {
      cout << "\n       ESTUDIANTE "<<i+1 << ":\n";
      V[i].mostrar();
    }
  }

  void buscar() {
    int p= buscarpos();

    if (p>=0){
      cout << "\n     Estudiante encontrado:\n";
      V[p].mostrar();
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
      cout << "   INGRESE LOS NUEVOS DATOS\n";
      V[p].pedirnombre();
      V[p].pedircarrera();
      V[p].pediredad();
      V[p].pedirnota(1);
      V[p].pedirnota(2);
      V[p].pedirnota(3);
      cout << "\n     Modificado correctamente\n\n";
    }
  }

};


int main() {
  ListaEst L(0);

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
    cout << "Numero de estudiantes: " << L.TAM() << "\n\n";

    cout << "--Digite la opcion del 1 al 7: ";
    getline(cin,opc);

    if (opc == "1") {
      L.crear();
    }
    else if (opc== "2") {
      L.mostrar();
    }
    else if (opc == "3") {
      L.buscar();
    }
    else if (opc == "4") {
      L.borrar();
    }
    else if (opc == "5") {
      L.modificar();
    }
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