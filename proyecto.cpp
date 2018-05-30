#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <fstream>
int cant=0;
void gotoxy(int x, int y) {		//Gotoxy para configurar le movimiento en la pantalla
	HANDLE hConsoleOutput;		//Propiedades de la terminal
	COORD Cursor_Pos = { x,y };	//Posicionamiento del cursor
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}
using namespace std;
/*---------  Estructura del arbol  -------*/
typedef struct nodo {	
	int nro;
	struct nodo *izq, *der;
}*ABB;
int numNodos = 0; // nummero de nodos del arbol ABB
int auxx = 0;	
/* ---------- Estructura de la cola ---------*/
struct nodoCola {
	ABB ptr;
	struct nodoCola *sgte;
};
struct cola {		
	struct nodoCola *delante;
	struct nodoCola *atras;
};
void inicializaCola(struct cola &q)
{
	q.delante = NULL;
	q.atras = NULL;
}
void encola(struct cola &q, ABB n)
{
	struct nodoCola *p;
	p = new(struct nodoCola);
	p->ptr = n;
	p->sgte = NULL;
	if (q.delante == NULL)
		q.delante = p;
	else
		(q.atras)->sgte = p;
	q.atras = p;
}

ABB desencola(struct cola &q)
{
	struct nodoCola *p;
	p = q.delante;
	ABB n = p->ptr;
	q.delante = (q.delante)->sgte;
	delete(p);
	return n;
}
//Creacion de un nuevo nodo singular
ABB crearNodo(int x)
{
	ABB nuevoNodo = new(struct nodo);
	nuevoNodo->nro = x;
	nuevoNodo->izq = NULL;
	nuevoNodo->der = NULL;
	cant=cant+1;
	return nuevoNodo;
}
//Inserción del nodo singular
void insertar(ABB &arbol, int x)
{
	if (arbol == NULL)
	{
		arbol = crearNodo(x);
		cout << "\n\t  Insertado..!" << endl << endl;
	}
	else if (x < arbol->nro)
		insertar(arbol->izq, x);
	else if (x > arbol->nro)
		insertar(arbol->der, x);
}
void preOrden(ABB arbol)
{
	if (arbol != NULL)
	{
		cout << arbol->nro << " ";
		preOrden(arbol->izq);
		preOrden(arbol->der);
	}
}
void enOrden(ABB arbol)
{
	if (arbol != NULL)
	{
		enOrden(arbol->izq);
		cout << arbol->nro << " ";
		enOrden(arbol->der);
	}
}
void postOrden(ABB arbol)
{
	if (arbol != NULL)
	{
		enOrden(arbol->izq);
		enOrden(arbol->der);
		cout << arbol->nro << " ";
	}
}
void verArbol(ABB arbol, int auxy = 0)
{	
	if (arbol == NULL) //arbol vacio
	{
		return;
	}
	else {
		auxx += 2; //posicion eje x
		verArbol(arbol->izq, auxy + 2); // para en el nodo que esta mas a la izquierda
		gotoxy(30 + auxx - auxy, 5 + auxy);// posiciona el nodo segun sus posiciones x & y
		cout << arbol->nro << endl << endl; // muestra el dato del nodo
		verArbol(arbol->der, auxy + 2 ); //  se para hasta el nodo mas a la derecha
	}
}
bool busquedaRec(ABB arbol, int dato)
{
	int r = 0;   // 0 indica que lo encontre
	if (arbol == NULL)
		return r;
	if (dato<arbol->nro)
		r = busquedaRec(arbol->izq, dato);
	else if (dato> arbol->nro)
		r = busquedaRec(arbol->der, dato);
	else
		r = 1;   // son iguales, lo encontre
	return r;
}
//-----------Opciones de los nodos en los arboles
ABB unirABB(ABB izq, ABB der)
{
	if (izq == NULL) return der;
	if (der == NULL) return izq;
	ABB centro = unirABB(izq->der, der->izq);
	izq->der = centro;
	der->izq = izq;
	return der;
}
void elimina(ABB &arbol, int x)
{
	if (arbol == NULL) return;
	if (x<arbol->nro)
		elimina(arbol->izq, x);
	else if (x>arbol->nro)
		elimina(arbol->der, x);
	else
	{
		ABB p = arbol;
		arbol = unirABB(arbol->izq, arbol->der);
		delete p;
	}
}
int alturaAB(ABB arbol)
{
	int AltIzq, AltDer;
	if (arbol == NULL)
		return -1;
	else
	{
		AltIzq = alturaAB(arbol->izq);
		AltDer = alturaAB(arbol->der);

		if (AltIzq>AltDer)
			return AltIzq + 1;
		else
			return AltDer + 1;
	}
}
//Niveles recorridos
void recorrerxNivel(ABB arbol)
{
	struct cola q;		//se crea una cola
	inicializaCola(q);	//se Inicializa la cola 
	cout << "\t";

	if (arbol != NULL)
	{
		encola(q, arbol);
	
		while (q.delante != NULL)
		{
			arbol = desencola(q);
			cout << arbol->nro << ' ';

			if (arbol->izq != NULL)
				encola(q, arbol->izq);
			if (arbol->der != NULL)
				encola(q, arbol->der);
		}
	}
}
int menu()
{
	int opc=1; char cTecla;
	do{
	system("cls");
	cout << "\n\n";
cout<<"\t\t\t\t	             ( ( (                   "<<endl;		//Dibujo de la pantalla Principal
cout<<"\t\t\t\t                    ) ) )         "<<endl;        
cout<<"\t\t\t\t                    ( ( (          "<<endl;
cout<<"\t\t\t\t                  '. ___ .'       "<<endl;
cout<<"\t\t\t\t                 '  (> <) '        "<<endl;
cout<<"\t\t\t\t         --------ooO-(_)-Ooo----------"<<endl;
cout<<"\t\t\t\t      ..[ ARBOOOOOOOOOOOOOOOOOOOOOOOOOL ]..	"<<endl;
	cout << "\n\n";
	// Color, Almoadilla, tabulador opcional dependiendo de la opción requerida, tabulador, texto de opción
	if(opc==1){system("color C7"); cout<<"\t###";} cout << "\t[1]  Insertar elemento                  \n"; 
	if(opc==2){system("color 27"); cout<<"\t###";} cout << "\t[2]  Mostrar arbol                      \n";
	if(opc==3){system("color 07"); cout<<"\t###";} cout << "\t[3]  Recorridos de profundiad           \n";
	if(opc==4){system("color 17"); cout<<"\t###";} cout << "\t[4]  Buscar elemento                    \n";
	if(opc==5){system("color 57"); cout<<"\t###";} cout << "\t[5]  Eliminar elemento                  \n";
	if(opc==6){system("color 47"); cout<<"\t###";} cout << "\t[6]  Altura del arbol                   \n";
	if(opc==7){system("color 37"); cout<<"\t###";} cout << "\t[7]  Contar nodos                       \n";
	if(opc==8){system("color CF"); cout<<"\t###";} cout << "\t[8]  SALIR                              \n";
	cout<<"\n\n\n\n\t\t\t\t\t\t\t\t\t\t Isis Diaz y Alejandro Cordova"<<endl;
	cTecla=getch();		//Tecla solicitada
	if(cTecla==80) opc++;	//80=tecla abajo
	if(cTecla==72) opc--; //72 = tecla arriba
	if(cTecla==13) break;	//13= ENTER
	if(opc==0)opc=8;	//Configuraciónes parametráles del movimiento del menú
	if(opc==9)opc=1;
	}while(cTecla != 72 || cTecla != 80 || cTecla != 13);	//Mientras la tecla que se pulse sea arriba, abajo o enter.
	system("cls");
	return opc;	//Retornar la opción seleccionada
}
//Menú de los recorridos, Misma configuración del menú principal
int menu2()
{
	int opc=1; char cTecla;
	do{
	system("cls");
	cout << "\n\t\t  ..[ ARBOOOOOOOOOOOOOOOOOOOOOOOOOL ]..  \n\n";
	if(opc==1){system("color 67"); cout<<"\t###";} cout << "\t [1] En Orden     \n";
	if(opc==2){system("color 57"); cout<<"\t###";} cout << "\t [2] Pre Orden    \n";
	if(opc==3){system("color 07"); cout<<"\t###";} cout << "\t [3] Post Orden   \n";
	cTecla=getch();	
	if(cTecla==80) opc++;
	if(cTecla==72) opc--;
	if(cTecla==13) break;
	if(opc==0)opc=3;
	if(opc==4)opc=1;
	}while(cTecla != 72 || cTecla != 80 || cTecla != 13);	
	system("cls");
	return opc;
}
void leerTexto(ABB &arbol){
	string nombre="data";		//Inicialización del nombre del archivo
	char dato[100];
	fstream ficheroEntrada;		//fstream para manejo del archivo
	cout<<"\tIngresa el nombre del archivo"<<endl; cin>>nombre;
	nombre=nombre+".txt";
	ficheroEntrada.open(nombre.c_str(), ios::in | ios::out);		//.c_str permite comvertir el texto en un texto "xxxxx" para colocarlo dentro de los parámetros necesarios
    if (ficheroEntrada.is_open()) {			//Si el archivo está abierto
	cout<<"\tArchivo Abierto"<<endl; _sleep(600);			
        while (!ficheroEntrada.eof() ) {
          ficheroEntrada.getline(dato, 40, ','); 							// getline (ficheroEntrada,frase);
            cout << "\tLeido: " << dato<<endl;;
            int x= atoi(dato);	//Converción del char al int
             insertar(arbol, x);	
        }
        _sleep(1000);
        system("cls");
		cout<<"	\tDatos Insertados"<<endl;
		_sleep(990);
        ficheroEntrada.close();
    }else{
    	cout<<"\tFallos al abrir el archivo, Archivo Inexistente"<<endl;
    	_sleep(1000);	
    }
}
void SubMenuInsertar(ABB &arbol){
	int x=100;
	system("cls");
	cout<<"					INSERTAR		"<<endl;
	cout<<"################################################################################"<<endl;
	int opc=1; char cTecla;
	do{
	system("cls");
	cout << "\n\t\t  ..[ ARBOOOOOOOOOOOOOOOOOOOOOOOOOL ]..  \n\n";
	if(opc==1){system("color 87"); cout<<"\t###";} cout<<"\t 1.- Insertar Manualmente"<<endl;
	if(opc==2){system("color 17"); cout<<"\t###";} cout<<"\t 2.- Insertar desde un arhivo de texto"<<endl;
	if(opc==3){system("color 67"); cout<<"\t###";} cout<<"\t 3.- Regresar"<<endl;
	cTecla=getch();	
	if(cTecla==80) opc++;
	if(cTecla==72) opc--;
	if(cTecla==13) break;
	if(opc==0)opc=3;
	if(opc==4)opc=1;
	}while(cTecla != 72 || cTecla != 80 || cTecla != 13);
	switch(opc){
	case 1:
		  cout << "\tIngrese valor o 0 para salir: "; cin>>x;
		while(x !=0){
			system("cls");
			insertar(arbol, x);
			cout << "\tIngrese valor o 0 para salir: ";  cin >> x;
			system("cls");
			}
			break;
	case 2:
		leerTexto(arbol);
		 break;
	case 3:
		break;
	default:
		cout<<"\tOpcion Inválida"<<endl;
		break;
	}
	
}
int main()
{
	ABB arbol = NULL;
	int x;
	int op, op2;
	//system("color f9");   // poner color a la consola
	do
	{
		op=menu(); 

		switch (op)
		{
		case 1:
			SubMenuInsertar(arbol);
			break;
		case 2:
			system("cls");
			auxx=0;
			verArbol(arbol, 0);
			cout << "   " << endl;
			gotoxy(1, 2);system("pause");
			break;
		case 3:
			op2=menu2();
			if (arbol != NULL)
			{
				switch (op2)
				{
				case 1:
					enOrden(arbol); system("pause");  break;
				case 2:
					preOrden(arbol); system("pause"); break;
				case 3:
					postOrden(arbol); system("pause"); break;
					system("pause");
				}
			}
			else
				cout << "\n\t Arbol vacio..!";
			break;

		case 4:
			bool band;
			cout << "\t Valor a buscar: "; cin >> x;
			band = busquedaRec(arbol, x);
			if (band == 1)
				cout << "\n\tEncontrado...";
			else
				cout << "\n\tNo encontrado...";
			system("pause");
			break;
		case 5:
			cout << "\t Valor a eliminar: "; cin >> x;
			elimina(arbol, x);
			cout << "\n\tEliminado..!";
			system("pause");
			break;

		case 6:
			int h;
			h = alturaAB(arbol);
			cout << "\t La altura es : " << h << endl;
			system("pause");
			break;
		case 7:
			system("cls")
;			verArbol(arbol, 0);
			gotoxy(5, 2);
			cout << "\n\n \tEl numero de nodos es: ";
			cout << cant;
			_sleep(2000);
			break;
		case 8:
			exit(0);
		}
		cout << "\n\n\n";
		//system("pause");  // hacer pausa y presionar una tecla para continuar
	} while (op != 11);

}
