#include<iostream>
#include<fstream>
#include<math.h>
#include<string>
#include<vector>
#include<stdio.h>
#include<iterator>
#include<ctime>
//variable que almacenara la base de datos
std::ifstream baseIMSS;
//vector que almacenara todas las entradas de la base de datos
std::vector<std::string> baseDeDatos;
//variable que almacena el id del funcionario
std::string idBusqueda;
//variable auxiliar para saber si la lista ya ha sido ordenada para realizar la busqueda binaria
int ord;
//funciones del menu, busqueda secuencial, ordenamiento, busqueda binaria y la funcion que imprime la salida
void menu();
void secuencial();
void ordenar();
void binaria();
void resultado(std::string, int, clock_t);
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	//variable que almacena la ubicacion de la base de datos
	std::string baseUbicacion;
	//variable auxiliar para la base de datos
	int opcionDeBase;
	std::cout<<"-------Bienvenido a la Actividad Complementaria 1 de la Unidad 6-------- \n";
	std::cout<<"[INSTRUCCIONES] Digite la opcion que desea utilizar \n";		
	std::cout<<"[1] Utilizar la base de datos dentro de esta misma carpeta \n";
	std::cout<<"[2] Utilizar otra base de datos similar \n";
	std::cin>>opcionDeBase;
	//si la base esta en la misma carpeta se accede solo con el nombre y su extension
	if (opcionDeBase == 1){
		baseUbicacion = "2021_04_3_AGUASCALIENTES.txt";
	}
	//se pide ingresa la ubicacion de la base 
	if (opcionDeBase == 2){
	std::cout<<"[INSTRUCCIONES] Recuerde que el formato debe ser similar a C:/Users/PC/Documents/UNAM-Lic.Informatica/Segundo Semestre/INFORMATICA II/BaseDeDatos.txt \n";
	std::cin>>baseUbicacion;
	}
	//Se abre el archivo de la base de datos
	baseIMSS.open(baseUbicacion,std::ios::in);
	//se comprueba si no hubo un error y en caso de que si se advierte del mismo
	if(!baseIMSS.is_open()){
		std::cout<<"[ADVERTENCIA] Error al abrir la base de datos";
		exit(1);
	}
	//variable auxiliar para almacenar temporalmente las entradas de la base de datos
	std::string aux;
	//ciclo que continua hasta que no haya mas datos
	while(!baseIMSS.eof()){
	//se toma cada linea de la base de datos
	std::getline(baseIMSS, aux);
	//se almacenan como entradas en nuestro vector
	baseDeDatos.push_back(aux);
	}
	
	menu();
	return 0;
}

void menu(){
	int opcionBusqueda;
	//se muestran las opciones de busqueda y hay un switch que redirecciona a las funciones adecuadas
	std::cout<<"--------------------------Menu------------------------------------------ \n";
	std::cout<<"Digite el numero de busqueda que desea realizar \n";
	std::cout<<"[1] Busqueda secuencial \n";
	std::cout<<"[2] Busqueda binaria \n";
	std::cin>>opcionBusqueda;
	switch(opcionBusqueda){
		case 1:
			secuencial(); break;
		case 2:
			ordenar(); break;
		default:
			menu(); break;
	}
}

void secuencial(){
		//se informa el tipo de busqueda
		std::cout<<"--------------------------Busqueda Secuencial------------------------------------ \n";	
		//variable que almacena la cantidad de condicionantes
		int proc;
		//variable auxiliar que almacena temporalmente un elemento del vector
		int y;
		//variable que almacena el id de los elementos del vector 
		std::string id;
		//se pide ingresar el id del funcionario
		std::cout<<"Ingrese el id del funcionario que desea encontrar \n";
		std::cin>>idBusqueda;
		//inicia el tiempo de ejecucion
		clock_t time;
		time = clock();
		//ciclo del tamanio de la base de datos excluyendo las dos entradas que no contienen funcionarios
		for (int i = 1; i<baseDeDatos.size()-1; i++){
		proc++;
		//id toma el elemento en la posicion i del vector
		id = baseDeDatos[i]; 
		//con el metodo substr extraemos solo el id de las entradas y comprobamos si es igual al buscado
		if(id.substr(0,9) ==idBusqueda){
			time = clock()-time;
			//se manda los datos del funcionario, la cantidad de condicionantes y el tiempo de ejecucion
			resultado(id,proc,time);
		
		}
		}
		//se regresa al menu
		menu();
}

void binaria(){
	//se informa el tipo de busqueda
	std::cout<<"--------------------------Busqueda Binaria-------------------------------------- \n";
	//variables de los limites y el punto medio
	int top, down, m;
	//variable que almacena la cantidad de condicionantes
	int proc;
	//variable de tipo entero que almacena el id a buscar
	int idBus;
	//variable de tipo entero que almacena el id del vector de la base de datos en la posucion m
	int enco;
	//variable auxiliar para comprobar si se estanco el bucle
	int y;
	//variable booleana para saber si el resultado se encontro 
	bool result;
	//variable del tiempo
	clock_t time;
	//el limite superior toma el valor de la posicion del ultimo funcionario
	top = baseDeDatos.size()-1;
	//el limite inferior toma el valor de la posicion del primer funcionario
	down = 1;
	m = 0;
	std::cout<<"Ingrese el id del funcionario que desea encontrar \n";
	std::cin>>idBusqueda;
	//inicia el tiempo de ejecucion
	time = clock();
	while(down<top && result == false){
		//se incrementan las condicionantes
		proc++;
		//m toma el valor del limite maximo mas el minimo y se divide entre dos
		m = (down+top)/2;
		//se usa le metodo stoi para convertir en entero los caracteres correspondientes al id de los funcionarios almacenados
		enco = stoi(baseDeDatos[m].substr(0,9));
		//se usa el metodo stoi para convertir en entero el id que se busca
		idBus = stoi(idBusqueda);
		//se comprueba si en la posicion actual esta el funcionario y si si se llama a la funcion resultado para imprimir los datos
		if (baseDeDatos[m].substr(0,9)==idBusqueda){
			time = clock()-time;
			result = true;
			resultado(baseDeDatos[m],proc,time);
		}
		//si la id actual es mayor a la buscada el limite maximo toma como valor la posicion actual
		if (enco > idBus){
			top = m;
		}
		//si la id actual es menor a la buscada el limite inferior toma como valor la posicion actual
		if (enco < idBus){
			down = m;
		}
		//si el id actual se repitio significa que el id no se encontro y se rompe el ciclo
		if (enco == y){
			break;
		}
		//se almacena en la variable auxiliar el valor actual
		y = enco;
	}
	
	menu();
}

void ordenar(){
	std::string y;
	//se comprueba si la base ya se ordeno
	if (ord == 0){
		//se informa que el ordenamiento esta en proceso
		std::cout<<"Ordenando... \n";
		for (int i = 1; i<baseDeDatos.size()-1; i++){
			for(int j = i+1; j<baseDeDatos.size()-1; j++)
			//si en la entrada en la ubicacion mas baja es mayor que la que esta en la mas alta intercambian posicion
			//se utiliza la funcion stoi y substr para comparar solo los id como valores enteros
			if (stoi(baseDeDatos[i].substr(0,9))>stoi(baseDeDatos[j].substr(0,9)))
			{
				y = baseDeDatos[i];
				baseDeDatos[i] = baseDeDatos[j];
				baseDeDatos[j] = y;
			}
		}
		
	}
	//se informa que el rodenamiento termino
	std::cout<<"Ordenamiento terminado \n\n";
	//se registra que la base ya esta ordenada y se llama a la funcion de la busqueda binaria
	ord =1;
	binaria();
}
//se reciben los datos, las condicionantes y el tiempo de ejecucion
void resultado(std::string datos, int p, clock_t t){
	printf("\n\n");	
	//se imprimen los resultados
	printf("Resultados de la busqueda: \n\n");
	std::cout<<datos<<std::endl<<std::endl;		
	std::cout<<"Numero de condicionantes: "<<p<<std::endl;
	//el tiempo se mide en clocks asi que lo convertimos a segundos
	std::cout<<"Tiempo de ejecucion: "<<float(t)/CLOCKS_PER_SEC<<" segundos \n\n";
}