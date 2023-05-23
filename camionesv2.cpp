/*
	
	Samuel Esteban Campos
	Tomas Ospina Ulloa
	Camilo Rodriguez Muete
	
*/

//Librerias
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <windows.h>

using namespace std;

//Estructura que define a un camion
struct Camion {
	string matricula;
	float capacidadCarga; //En kilogramos
	float consumoGasolina; //Galones por kilometro
	float cargaActual; //Kilogramos
	int transportando; //1 para verdadero, 0 para falso
	float kilometrosRecorridos;
	float kilometros_a_recorrer;
	float consumoGasolinaTotal; 
	float cargasTransportadas;
	int diasUso;
};

//Funciones - Procedimientos
void pantallaInicial();
void ingresarCamiones();
bool cargarInformacion();
void guardarInformacion();
void autoguardadoFuncion();
void menuOpciones();
void consultarCamiones();
void consultarCamion();
void cargarCamion();
void descargarCamion();
void buscarCamionOptimo();
void agregarCamion();
void eliminarCamion();
void transportarCargas();
void transportarCarga();
void imprimirMatriculas();

//Funciones - con valor de retorno
int buscarMatricula(string matricula);
int buscarEficiente(float carga, float distancia);
int cargasPendientes();
int cargasTransportandose();

//Variables utilizadas a nivel global
int numeroCamiones, diasOperacion = 0, autoguardado = 0;
Camion camiones[10];
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
float capacidadCombustible;

//Funcion Principal
int main() { 	
	pantallaInicial();
	system("pause");
}

//Funcion pantalla inicial
void pantallaInicial() {
	bool ciclo = false;
	
	do {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout<<"\t*Bienvenido al programa administrador de la flota de camiones*\n\n";
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		cout << "   .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                            " << endl;
		cout << "   .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                            " << endl;
		cout << "   .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                            " << endl;
		cout << "   .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    @@@@@@@@@@              " << endl;
    	cout << "   .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@            " << endl;
    	cout << "   .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@. . . . .@@@@          " << endl;
    	cout << "   .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@.        .@@@@         " << endl;
    	cout << "   .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@.          .@@@@       " << endl;
    	cout << "   .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@. . . . . . .@@@@      " << endl;
    	cout << "   .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@    " << endl;
    	cout << "   .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@    " << endl;
    	cout << "   -------------------------------------------------- @@@@@@@@@@@@@@@@@@@@@@    " << endl;
    	cout << "   .@@@@@@@@@@@.      .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.        .@@@@@@@@    " << endl;
    	cout << "   .@@@@@@@@. @@@@@@@@@ .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@. @@@@@@@@@ .@@@@@@@    " << endl;
    	cout << "   .@@@@@@@. @@@@@@@@@@@ .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@. @@@@@@@@@@@  .@@@@@    " << endl;
    	cout << "             @@@@@@@@@@@                                 @@@@@@@@@@@            " << endl;
    	cout << "              @@@@@@@@@                                   @@@@@@@@@             " << endl<<endl<<endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		int opcion = 0;
	
		cout<<"1. Ingresar camiones";
		cout<<"\n2. Cargar datos";
		cout<<"\nOpcion: ";
		cin>>opcion;
	
		switch(opcion) {
			case 1:
				ciclo = true;
				ingresarCamiones();
				menuOpciones();
				break;
			case 2:
				ciclo = true;
				if(cargarInformacion() == true) {
					cargarInformacion();
					menuOpciones();	
				} else {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					system("cls");
					cout<<"No hay datos que cargar o no se concedieron permisos\n";
					ciclo = false;
				}
				
			break;
			default:
				ciclo = false;
				system("cls");
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				cout<<"Opcion invalida\n";
		}
		cout<<endl;
	} while(ciclo == false);
}

//Funcion ingreso de camiones
void ingresarCamiones() {    	
	bool ciclo = false;
	string matricula;	
	system("cls");
	
	do {
		cout<<"Cuantos camiones desea ingresar para iniciar? (min 5, max 10): ";
		cin>>numeroCamiones;
	
		if(numeroCamiones < 5 || numeroCamiones > 10) {
			system("cls");
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			cout<<"numero invalido de camiones, vuelva a intentar\n";
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			ciclo = false;
		} else {
			bool ingresoCamion = false;
			string matriculaAux;
			for(int i=0; i<numeroCamiones; i++) {	
			system("cls");
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
			cout<<"\tIngreso de camiones...\n";
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			
				cin.ignore();
				do {
					if(i == 0) {
						cout<<"Ingrese la matricula del camion #"<<i+1<<":  ";
						getline(cin,camiones[i].matricula);
						cout<<"Ingrese la capacidad de carga del camion #"<<i+1<<" (kilogramos): ";
						cin>>camiones[i].capacidadCarga;
						cout<<"Ingrese el consumo de gasolina del camion #"<<i+1<<" (Galones por kilometro): ";
						cin>>camiones[i].consumoGasolina;
						camiones[i].cargaActual = 0;
						camiones[i].transportando = 0;
						camiones[i].kilometrosRecorridos = 0;
						camiones[i].kilometros_a_recorrer = 0;
						camiones[i].consumoGasolinaTotal = 0;
						camiones[i].cargasTransportadas = 0;
						camiones[i].diasUso = 0;
						cout<<endl;	
						ingresoCamion = true;
						system("cls");
					} else {
						cout<<"Ingrese la matricula del camion #"<<i+1<<":  ";
						getline(cin, matriculaAux);
						int indice = buscarMatricula(matriculaAux);
						if(indice == -1) {
							camiones[i].matricula = matriculaAux;
							cout<<"Ingrese la capacidad de carga del camion #"<<i+1<<" (kilogramos): ";
							cin>>camiones[i].capacidadCarga;
							cout<<"Ingrese el consumo de gasolina del camion #"<<i+1<<" (Galones por kilometro): ";
							cin>>camiones[i].consumoGasolina;
							camiones[i].cargaActual = 0;
							camiones[i].transportando = 0;
							camiones[i].kilometrosRecorridos = 0;
							camiones[i].kilometros_a_recorrer = 0;
							camiones[i].consumoGasolinaTotal = 0;
							camiones[i].cargasTransportadas = 0;
							camiones[i].diasUso = 0;
							cout<<endl;	
							ingresoCamion = true;
							system("cls");
						} else {
							system("cls");
							cout<<"Esa matricula ya existe, vuelva a intentar\n";
							ingresoCamion = false;
						}
					}
				} while(ingresoCamion == false);
			}
			ciclo = true;
			system("cls");
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
			cout<<"Camiones ingresados y rellenados de combustible...\n\n";
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
	} while(ciclo == false);
}

//Funcion que carga la informacion
bool cargarInformacion() { 

	ifstream archivo;
	
	archivo.open("camiones.txt", ios::in);
	
	if(archivo.fail()) {
		return false;
	}
	
	char texto[100];
	archivo.getline(texto, 100, '\n');
	numeroCamiones = atoi(texto);
	archivo.getline(texto, 100, '\n');
	diasOperacion = atoi(texto);
	archivo.getline(texto, 100, '\n');
	autoguardado = atoi(texto);
	
	int contador = 0;
	
//	struct Camion {
//	string matricula;
//	float capacidadCarga; //En kilogramos
//	float consumoGasolina; //Galones por kilometro
//	float cargaActual; //Kilogramos
//	int transportando; //1 para verdadero, 0 para falso
//	float kilometrosRecorridos;
//	float kilometros_a_recorrer;
//	float consumoGasolinaTotal; 
//	float cargasTransportadas;
//	int diasUso;
//};
	
	while(!archivo.eof()) {
		archivo.getline(texto, 100, ';');
		camiones[contador].matricula = texto;
		archivo.getline(texto, 100, ';');
		camiones[contador].capacidadCarga = atof(texto);
		archivo.getline(texto, 100, ';');
		camiones[contador].consumoGasolina = atof(texto);
		archivo.getline(texto, 100, ';');
		camiones[contador].cargaActual = atof(texto);
		archivo.getline(texto, 100, ';');
		camiones[contador].transportando = atoi(texto);
		archivo.getline(texto, 100, ';');
		camiones[contador].kilometrosRecorridos = atof(texto);
		archivo.getline(texto, 100, ';');
		camiones[contador].kilometros_a_recorrer = atof(texto);
		archivo.getline(texto, 100, ';');
		camiones[contador].consumoGasolinaTotal = atof(texto);
		archivo.getline(texto, 100, ';');
		camiones[contador].cargasTransportadas = atof(texto);
		archivo.getline(texto, 100, '\n');
		camiones[contador].diasUso = atoi(texto);
		contador++;
	}
	
	archivo.close();
	
	system("cls");
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout<<"Datos cargados correctamente \n\n";
}

//Funcion que guarda la informacion
void guardarInformacion() {
	ofstream archivo;
	
	archivo.open("camiones.txt", ios::out);
	
	if(archivo.fail()) {
		system("cls");
		cout<<"No se pudo acceder al archivo";
		exit(1);
	} 
	
	archivo << numeroCamiones << '\n';
	archivo << diasOperacion << '\n';
	archivo << autoguardado << '\n'; 
	
	for(int i=0; i<numeroCamiones; i++) {
		archivo << camiones[i].matricula << ';';
		archivo << camiones[i].capacidadCarga << ';';
		archivo << camiones[i].consumoGasolina << ';';
		archivo << camiones[i].cargaActual << ';';
		archivo << camiones[i].transportando << ';';
		archivo << camiones[i].kilometrosRecorridos << ';'; 
		archivo << camiones[i].kilometros_a_recorrer << ';';
		archivo << camiones[i].consumoGasolinaTotal << ';';
		archivo << camiones[i].cargasTransportadas << ';';
		archivo << camiones[i].diasUso << '\n';  
	}
	
	archivo.close(); 
	
	system("cls");
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	cout<<"Datos guardados correctamente \n\n";
}

void autoguardadoFuncion() {
	if(autoguardado == 1) {
		autoguardado = 0;
	} else {
		autoguardado = 1;
	}
	system("cls");	
}

//Menu de opciones
void menuOpciones() {
	bool bandera = false;
	int opcion = 0;
	do {	
		if(autoguardado == 1) {
			guardarInformacion();
		}
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout<<"\t*Menu de opciones*\n";
		cout<<"\nNumero de camiones: "<<numeroCamiones;
		cout<<"\nDia: "<<diasOperacion;
		if(cargasPendientes() != 0) {
			cout<<"\nTienes ("<<cargasPendientes()<<") cargas pendientes que no has transportado";
		}
		
		if(cargasTransportandose() != 0) {
			cout<<"\nTienes ("<<cargasTransportandose()<<") cargas transportandose";
		}
		
		cout<<endl;
		if(diasOperacion < 5) {
			cout<<"\n1. Consultar estadisticas de uso y consumo (Disponible a partir del dia 5)";
		} else {
			cout<<"\n1. mostrar la informacion de todos los camiones (Ya disponible) ";
		}
		cout<<"\n2. consultar un camion";
		cout<<"\n3. Cargar un camion";
		cout<<"\n4. Descargar un camion";
		cout<<"\n5. Buscar el camion mas optimo";
		cout<<"\n6. Agregar camion a la flota";
		cout<<"\n7. Eliminar camion de la flota";
		cout<<"\n8. Transportar todas las cargas";
		cout<<"\n9. Transportar una carga";
		cout<<"\n10. Guardar informacion";
		cout<<"\n11. Imprimir matriculas";
		if(autoguardado == 1) {
			cout<<"\n12. Autoguardado (el autoguardado esta activo)";
		} else {
			cout<<"\n12. Autoguardado (Autoguardado desactivado)";
		}
		cout<<"\n13. Salir";
		cout<<"\nOpcion: ";
		cin>>opcion;
		
		switch(opcion) {
			case 1:
				consultarCamiones();
				break;
			case 2:
				consultarCamion();
				break;
			case 3:
				cargarCamion();
				break;
			case 4:
				descargarCamion();
				break;
			case 5:
				buscarCamionOptimo();
				break;
			case 6:
				agregarCamion();
				break;
			case 7:
				eliminarCamion();
				break;
			case 8:
				transportarCargas();
				break;
			case 9:
				transportarCarga();
				break;
			case 10:
				guardarInformacion();
				break;
			case 11:
				imprimirMatriculas();
				break;
			case 12:
				autoguardadoFuncion();
				break;		
			case 13:
				exit(1);
			default: 
				system("cls");
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				cout<<"Opcion invalida, vuelva a intentar\n";
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				break;
		}
	} while(bandera == false);
}

//Funcion standby
void consultarCamiones(){
	if(diasOperacion < 5) {
		system("cls");
		cout<<"Aun no puedes usar esa función\n";
	} else {
		system("cls");
		cout<<"Informacion de todos los camiones\n";
		for(int i=0; i<numeroCamiones; i++) {
			cout<<"\nCamion #"<<i+1;
			cout<<"\nMatricula: "<<camiones[i].matricula;
			cout<<"\nCapacidad de carga: "<<camiones[i].capacidadCarga;
			cout<<"\nConsumo de gasolina: "<<camiones[i].consumoGasolina;
			cout<<"\nCarga actual: "<<camiones[i].cargaActual;
			if(camiones[i].transportando == 0) {
				cout<<"\nSe encuentra transportando?: No";
			} else {
				cout<<"\nSe encuentra transportando?: Si";
			}
			cout<<"\nKilometros recorridos: "<<camiones[i].kilometrosRecorridos;
			cout<<"\nKilometros a recorrer: "<<camiones[i].kilometros_a_recorrer;
			cout<<"\nConsumo de gasolina total: "<<camiones[i].consumoGasolinaTotal;
			cout<<"\nCargas transportadas: "<<camiones[i].cargasTransportadas;
			cout<<"\nDias de operacion del camion: "<<camiones[i].diasUso;
			cout<<endl;
		}
	}
	cout<<endl;
	system("pause");
	system("cls");
}

//Funcion completa
void consultarCamion(){
	system("cls");
	cin.ignore();
	string matricula;
	int indice;
	
	cout<<"Ingrese la matricula del camion que desea consultar: ";
	getline(cin, matricula);
	
	indice = buscarMatricula(matricula);
	
	if(indice != -1) {
		cout<<"\nCamion #"<<indice+1;
		cout<<"\nMatricula: "<<camiones[indice].matricula;
		cout<<"\nCapacidad de carga: "<<camiones[indice].capacidadCarga;
		cout<<"\nConsumo de gasolina: "<<camiones[indice].consumoGasolina;
		cout<<"\nCarga actual: "<<camiones[indice].cargaActual;
		cout<<"\nTransportando?: "<<camiones[indice].transportando;
		cout<<endl<<endl;
		system("pause");
		system("cls");
	} else {
		system("cls");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		cout<<"No se encontro ese camion\n\n"<<endl;
	}
	
}

void cargarCamion(){
	cin.ignore();
	system("cls");
	string matricula;
	int indice;
	float carga;
	
	cout<<"Ingrese la matricula del camion que desea cargar: ";
	getline(cin, matricula);
	
	indice = buscarMatricula(matricula);
	
	if(indice != -1) {
		cout<<"Ingrese la carga que desea asignar al camion "<<matricula<<": ";
		cin>>carga;
		if(carga > camiones[indice].capacidadCarga || (camiones[indice].cargaActual + carga) > camiones[indice].capacidadCarga || camiones[indice].transportando == 1) {
			system("cls");
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			cout<<"No se puede asignar tal carga a ese camion\n\n";
		} else {
			if(camiones[indice].cargaActual > 0) {
				camiones[indice].cargaActual += carga;
			} else {
				camiones[indice].cargaActual = carga;	
			}
			system("cls");
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
			cout<<"Se asigno la carga correctamente...\n\n";
		}
	} else {
		system("cls");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		cout<<"No se encontro el camion con esa matricula\n\n";
	}
}

//Funcion completa
void descargarCamion(){
	system("cls");
	string matricula;
	int indice;
	
	cin.ignore();
	cout<<"Ingrese la matricula del camion que desea descargar: ";
	getline(cin, matricula);
	
	indice = buscarMatricula(matricula);
	
	system("cls");
	
	if(indice != -1) {
		if(camiones[indice].transportando == 1 && camiones[indice].cargaActual != 0) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
			camiones[indice].cargasTransportadas += camiones[indice].cargaActual;
			camiones[indice].cargaActual = 0;
			camiones[indice].transportando = 0;
			camiones[indice].kilometrosRecorridos += camiones[indice].kilometros_a_recorrer;
			float consumoGasolina = camiones[indice].kilometros_a_recorrer * camiones[indice].consumoGasolina;
			camiones[indice].kilometros_a_recorrer = 0;
			camiones[indice].consumoGasolinaTotal += consumoGasolina;
			camiones[indice].diasUso++;
			cout<<"Camion #"<<indice+1<<", carga transportada y camion descargado exitosamente\n\n";
//			
		} else if(camiones[indice].transportando == 0 && camiones[indice].cargaActual != 0) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
			camiones[indice].cargasTransportadas += camiones[indice].cargaActual;
			camiones[indice].cargaActual = 0;
			camiones[indice].transportando = 0;
			camiones[indice].kilometrosRecorridos += camiones[indice].kilometros_a_recorrer;
			float consumoGasolina = camiones[indice].kilometros_a_recorrer * camiones[indice].consumoGasolina;
			camiones[indice].kilometros_a_recorrer = 0;
			camiones[indice].consumoGasolinaTotal += consumoGasolina;
			camiones[indice].diasUso++;
			cout<<"Camion #"<<indice+1<<" descargado exitosamente\n\n";
//			diasOperacion++;
		} else if(camiones[indice].cargaActual) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			cout<<"El camion no tiene ninguna carga para descargar\n\n";
		}
		
		
	} else {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		cout<<"No se encontro ese camion\n\n";
	}
}

//Funcion completa
void buscarCamionOptimo(){
	system("cls");
	float carga, distancia;
	cout<<"Ingrese la carga que desea transportar: ";
	cin>>carga;
	cout<<"Ingrese la distancia que debe recorrer: ";
	cin>>distancia;
	
	int indice = buscarEficiente(carga, distancia);
	
	if(indice != -1) {
		cout<<"\nEl camion mas optimo para transportar la carga es el camion #"<<indice+1<<endl;
		cout<<"\nMatricula: "<<camiones[indice].matricula;
		cout<<"\nCapacidad de carga: "<<camiones[indice].capacidadCarga;
		cout<<"\nConsumo de combustible: "<<camiones[indice].consumoGasolina;
		cout<<endl<<endl;
		system("pause");
		system("cls");
	} else {
		cout<<"\nNingun camion es capaz de transportar la carga que se solicita\n\n";
		system("pause");
		system("cls");
	}
	
}

//Funcion completa
void agregarCamion(){
	bool ingresoCamion = false;
	string matriculaAux;
	
	cin.ignore();
	system("cls");
	if(numeroCamiones<10) {
		numeroCamiones++;
		do {
			cout<<"Ingrese los datos del nuevo camion\n";
			cout<<"Ingrese la matricula del camion:  ";
			getline(cin, matriculaAux);
			int indice = buscarMatricula(matriculaAux);
			if(indice == -1) {
				camiones[numeroCamiones-1].matricula = matriculaAux;
				cout<<"Ingrese la capacidad de carga del nuevo camion (kilogramos): ";
				cin>>camiones[numeroCamiones-1].capacidadCarga;
				cout<<"Ingrese el consumo de combustible del nuevo camion: ";
				cin>>camiones[numeroCamiones-1].consumoGasolina;
				camiones[numeroCamiones-1].cargaActual = 0;
				camiones[numeroCamiones-1].transportando = 0;
				camiones[numeroCamiones-1].kilometrosRecorridos = 0;
				camiones[numeroCamiones-1].kilometros_a_recorrer = 0;
				camiones[numeroCamiones-1].consumoGasolinaTotal = 0;
				cout<<endl;	
				ingresoCamion = true;
				system("cls");
			} else {
				system("cls");
				cout<<"Esa matricula ya existe, vuelva a intentar\n";
				ingresoCamion = false;
			}
		}  while(ingresoCamion == false);
		/*
		numeroCamiones++;
		cout<<"Ingrese los datos del nuevo camion\n";
		cout<<"Matricula: ";
		getline(cin, camiones[numeroCamiones-1].matricula);
		cout<<"Capacidad de carga: ";
		cin>>camiones[numeroCamiones-1].capacidadCarga;
		cout<<"Consumo de combustible: ";
		cin>>camiones[numeroCamiones-1].consumoGasolina;
		system("cls");
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		cout<<"Camion agregado exitosamente\n\n";
		*/
	} else {
		system("cls");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		cout<<"No se puede agregar un camion a la flota en este momento\n\n";
	}
}

//funcion completa
void eliminarCamion(){
	system("cls");
	if(numeroCamiones <= 5) {
		cout<<"No puede eliminar ningun camion en este momento\n";
	} else {
		string matricula;
		int indice;
	
		cin.ignore();
		cout<<"Ingrese la matricula del camion que desea eliminar: ";
		getline(cin, matricula);
	
		indice = buscarMatricula(matricula);
		
		if(indice != -1) {
			for(int i=indice; i<numeroCamiones-1; i++) {
				camiones[i] = camiones[i+1];
			}
			numeroCamiones--;
			system("cls");
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
			cout<<"Camion eliminado exitosamente\n\n";
		} else {
			system("cls");
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			cout<<"No se encontro ese camion\n\n";
		}
 	}
	
}

void transportarCargas() {
	system("cls");
	
	if(cargasPendientes() == 0) {
		system("cls");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		cout<<"Actualmente no hay cargas para transportar...\n\n";
	} else {
		system("cls");
		for(int i=0; i<numeroCamiones; i++) {
			if(camiones[i].cargaActual > 0 && camiones[i].transportando == 0) {
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
				cout<<"Transporte de cargas...\n\n";
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				cout<<"Ingrese la distancia que recorrera el camion "<<camiones[i].matricula<<" (kilometros): ";
				cin>>camiones[i].kilometros_a_recorrer;
				camiones[i].transportando = 1;
				system("cls");
			} 
		} 
		
		diasOperacion++;

		system("cls");
		
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		cout<<"Cargas transportadas correctamente\n\n";
	}
}

void transportarCarga() {
	system("cls");
	
	int indice = 0;
	cin.ignore();
	string matricula;
	cout<<"Ingrese la matricula del camion que empieza proceso de transporte: ";
	getline(cin, matricula);
	
	indice = buscarMatricula(matricula);
	
	if(indice != -1) {
		if(camiones[indice].cargaActual > 0 && camiones[indice].transportando == 0) {
			system("cls");
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
			cout<<"Transporte de cargas...\n\n";
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout<<"Ingrese la distancia que recorrera el camion "<<camiones[indice].matricula<<" (kilometros): ";
			cin>>camiones[indice].kilometros_a_recorrer;
			camiones[indice].transportando = 1;
			system("cls");
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
			cout<<"Cargas transportadas correctamente\n\n";
			diasOperacion++;
		} else if(camiones[indice].transportando == 1) {
			system("cls");
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			cout<<"El camion ya se encuentra transportando\n\n";
		}else {
			system("cls");	
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			cout<<"El camion no tiene una carga para transportar\n\n";		
		}
		
	} else {
		system("cls");
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		cout<<"No se encontro ese camión\n\n";
	}
}

void imprimirMatriculas() {
	system("cls");
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	cout<<"Listado de matriculas\n\n";
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	for(int i=0; i<numeroCamiones; i++) {
		cout<<"Matricula: "<<camiones[i].matricula<<endl;;
	}
	
	cout<<endl;
	system("pause");
	system("cls");
}

//Funcion completa
int buscarMatricula(string matricula) {
	
	int indice;
		
	for(int i=0; i<numeroCamiones; i++) {
		if(camiones[i].matricula == matricula) {
			indice = i;
			return indice;
		}
	}
	
	indice = -1;
	return indice;
}

/*
	Funcion completa, la funcion hace uso de la formula eficiencia
	eficiencia = capacidad de carga / consumo de gasolina * distancia
*/
int buscarEficiente(float carga, float distancia) {
	
	float eficienciaMaxima = 0;
	int indice = -1;
	
	for(int i=0; i<numeroCamiones; i++) {
		if(camiones[i].capacidadCarga >= carga) {
			float eficiencia = camiones[i].capacidadCarga / camiones[i].consumoGasolina * distancia;
			if(eficiencia > eficienciaMaxima && camiones[i].cargaActual == 0) {
				eficienciaMaxima = eficiencia;
				indice = i;
			}
		}
	}
		
	return indice;
}

int cargasPendientes() {
	
	int cargasPendientes = 0;
	
	for(int i=0; i<numeroCamiones; i++) {
		if(camiones[i].cargaActual != 0 && camiones[i].transportando == 0) {
			cargasPendientes++;
		}
	}
	
	return cargasPendientes;
}

int cargasTransportandose() {
 	int cargasTransportandose = 0;
 	
 	for(int i=0; i<numeroCamiones; i++) {
 		if(camiones[i].transportando == 1) {
 			cargasTransportandose++;
		 }
	 }
	 
	 return cargasTransportandose;
}
