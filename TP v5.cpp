// El siguiente programa es del ejercicio dos de la segunda parte.
// del grupo D12.

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
using namespace std;


//El archivo es del tipo Candidatos. y se llama "Candidatos.bin"
//El archivo que contiene a los candidatos que deben ser eliminados se llama "NoEntran.bin"


struct Candidatos{
	char nombreagrupacion[20];
	int nrolista;
	char candidato[20];
	int cantvotos;
	bool DiputadoOSenador;
};

struct Nodo {
    Candidatos info;
    Nodo *sgte;
};


// Recibe un nodo y un dato del tipo Candidatos para cargarlo completamente. (Solo lo carga y deja su siguientes en NULL)
void CargaDeNodo(Nodo*&nodito, Candidatos info){
        nodito->info.nrolista = info.nrolista;
        strcpy(nodito->info.candidato,info.candidato);
        nodito->info.cantvotos = info.cantvotos;
        strcpy(nodito->info.nombreagrupacion,info.nombreagrupacion);
        nodito->info.DiputadoOSenador = info.DiputadoOSenador;
        nodito->sgte = NULL;
        return;
}

// Recibe una lista, un puntero auxiliar y el dato de tipo candidatos para cargar en la lista.
void PonerEnLista(Nodo*&Lista, Nodo*&ptr, Candidatos info){
        Nodo*nuevo = new(Nodo);
        if(Lista==NULL){
        CargaDeNodo(nuevo,info);
        Lista = nuevo;
        ptr = nuevo;
        }else{
            CargaDeNodo(nuevo,info);
            ptr->sgte = nuevo;
            ptr = nuevo;
        };
        return;
}

// Recibe la lista y la direccion del nodo que debe ser eliminado sin desarmar la lista. (Es decir que lo enlaza al proximo antes de eliminarlo)
void BuscarYDestruir(Nodo *&Lista,Nodo *NodoAEliminar){
    Nodo *Auxiliar;
    Auxiliar = Lista;
    if(Lista == NodoAEliminar){
        Auxiliar = Lista->sgte;
        delete NodoAEliminar;
    }else{
    while(Auxiliar->sgte != NodoAEliminar){
        Auxiliar = Auxiliar->sgte;
        }
        Auxiliar->sgte = NodoAEliminar->sgte;
        delete NodoAEliminar;
    }
}

// Recibe una lista y un dato del tipo char para buscar al candidato en la lista. Retorna la dirección del nodo y si no existe retorna NULL.
Nodo *Searching(Nodo *Lista,char info[20]){
    Nodo *Buscar = new Nodo;
    Buscar = Lista;
    while(strncmp(Buscar->info.candidato,info,20)!=0 && Buscar){
        Buscar = Buscar->sgte;
    }
    return Buscar;
}


// Recibe una lista,lee uno de los archivos (El que contiene a todos los candidatos) y carga la lista, luego
// lee el archivo que contiene los candidatos a eliminar y los saca de la lista.
void LecturaYCarga (Nodo*&Lista){
    FILE*archivo;
    FILE*noentran;
	Nodo*ptr;
    Candidatos Info;
    char Aux[20];
    noentran = fopen("NoEntran.bin", "rb");
    archivo = fopen("Candidatos.bin","rb");
    fread(&Info,sizeof(Info),1,archivo);
    while(!feof(archivo))
	{
        PonerEnLista(Lista,ptr,Info);
        fread(&Info,sizeof(Info),1,archivo);
    };
    fclose(archivo);
    fread(&Aux,sizeof(Aux),1,noentran);
    while(!feof(noentran)){
        ptr = Searching(Lista,Aux);
        BuscarYDestruir(Lista,ptr);
        fread(&Aux,sizeof(Aux),1,noentran);
    }
    fclose(noentran);
    return;
}

// Recibe una lista y la muestra.
void Muestra (Nodo*paraMuestra){
    cout << setw ( 10 ) << "Agrupacion" << "        " << setw ( 10 )<< "Lista" << "       "<< setw ( 10 ) << "Candidato" << "          " << setw ( 10 )<< "Votos" <<  "       "<< endl;
    while(paraMuestra!=NULL){
        cout << setw ( 10 ) << paraMuestra->info.nombreagrupacion << "       "
        << setw ( 10 ) <<paraMuestra->info.nrolista << "       "
        << setw ( 10 ) <<paraMuestra->info.candidato << "       "
        << setw ( 10 ) <<paraMuestra->info.cantvotos << endl;
        paraMuestra = paraMuestra->sgte;
    }
}

// Recibe una lista y la ordena por votos con el metodo burbuja.
void OrdenarPorVotos(Nodo *&PorVotos){
    Nodo *Aux = new Nodo;
    Nodo *ptr;
    Nodo *Sig;
    ptr = PorVotos;

    while(ptr->sgte != NULL){
        Sig = ptr->sgte;
        while(Sig != NULL){
            if(ptr->info.cantvotos < Sig->info.cantvotos){

                Aux->info = Sig->info;

                Sig->info = ptr->info;

                ptr->info = Aux->info;

            }else{}
            Sig = Sig->sgte;
        }
    ptr = ptr->sgte;
    Sig = ptr->sgte;
    }
}

// Recibe la lista y la ordena por el numero de lista con el metodo seleccion.
void OrdenarPorLista(Nodo *&PorLista){
    Nodo *Aux = new Nodo;
    Nodo *Min;
    Nodo *ptr;
    Nodo *Siguiente;
    ptr = PorLista;
    while(ptr != NULL){
            Min = ptr;
            Siguiente = ptr->sgte;
        while(Siguiente != NULL){
            if(Siguiente->info.nrolista < Min->info.nrolista){
                Min = Siguiente;
            }
            Siguiente = Siguiente->sgte;
        }
        Aux->info = ptr->info;
        ptr->info = Min->info;
        Min->info = Aux->info;
        ptr = ptr->sgte;
    }
}

// Recibe la lista y la ordena por nombre.
void OrdenarPorNombre(Nodo *&PorNombre){
    Nodo *Aux = new Nodo;
    Nodo *Min;
    Nodo *ptr;
    Nodo *Siguiente;
    ptr = PorNombre;
    while(ptr != NULL){
            Min = ptr;
            Siguiente = ptr->sgte;
        while(Siguiente != NULL){
            if(strncmp(Siguiente->info.candidato,Min->info.candidato,20) < 0){
                Min = Siguiente;
            }
            Siguiente = Siguiente->sgte;
        }
        Aux->info = ptr->info;
        ptr->info = Min->info;
        Min->info = Aux->info;
        ptr = ptr->sgte;
    }
}

// Recibe la lista y la ordena por partido.
void OrdenarPorPartido(Nodo *&PorPartido){
    Nodo *Aux = new Nodo;
    Nodo *ptr;
    Nodo *Sig;
    ptr = PorPartido;

    while(ptr->sgte != NULL){
        Sig = ptr->sgte;
        while(Sig != NULL){
            if(strncmp(ptr->info.nombreagrupacion,Sig->info.nombreagrupacion,20) > 0){

                Aux->info = Sig->info;

                Sig->info = ptr->info;

                ptr->info = Aux->info;

            }else{}
            Sig = Sig->sgte;
        }
    ptr = ptr->sgte;
    Sig = ptr->sgte;
    }
}

//Recibe una lista y muestra los diputados

void MostrarDiputados(Nodo *Diputados){
    Nodo *Aux;
    Aux = Diputados;
        cout << setw ( 10 ) << "Agrupacion" << "        " << setw ( 10 )<< "Lista" << "       "<< setw ( 10 ) << "Candidato" << "          " << setw ( 10 )<< "Votos" <<  "       "<< endl;
    while(Aux!=NULL){
        if(Aux->info.DiputadoOSenador == 1){
        cout << setw ( 10 ) << Aux->info.nombreagrupacion << "       "
        << setw ( 10 ) <<Aux->info.nrolista << "       "
        << setw ( 10 ) <<Aux->info.candidato << "       "
        << setw ( 10 ) <<Aux->info.cantvotos << endl;
        }else{}
        Aux = Aux->sgte;
    }
}

// Recibe una lista y muestra los senadores

void MostrarSenadores(Nodo *Senadores){
    Nodo *Aux;
    Aux = Senadores;
        cout << setw ( 10 ) << "Agrupacion" << "        " << setw ( 10 )<< "Lista" << "       "<< setw ( 10 ) << "Candidato" << "          " << setw ( 10 )<< "Votos" <<  "       "<< endl;
    while(Aux!=NULL){
        if(Aux->info.DiputadoOSenador){
        cout << setw ( 10 ) << Aux->info.nombreagrupacion << "       "
        << setw ( 10 ) <<Aux->info.nrolista << "       "
        << setw ( 10 ) <<Aux->info.candidato << "       "
        << setw ( 10 ) <<Aux->info.cantvotos << endl;
        }else{}
        Aux = Aux->sgte;
    }

}

// Recibe lista y el usuario ingresa un nombre para que sea buscado en dicha lista.
// Luego muestra la informacion del buscado, si es que no esta dice que no existe un candidato con ese nombre.

void BuscarCandidato (Nodo*Nodito){
    Nodo*Mostrar;
    Nodo *Aux = new Nodo;
    bool  Encontrado;
    Encontrado = false;
    Mostrar = Nodito;
    char Candidato[20];
    cout << "Por favor, ingrese el candidato que desea obtener su informacion: ";
    cin >> Candidato;

    while(Mostrar!=NULL){
        if(strncmp(Mostrar->info.candidato,Candidato,20)== 0){
            cout << "" << endl;
            cout << "Candidato Encontrado: " << endl;
            Aux->info = Mostrar->info;
            Muestra(Aux);
            cout << "------------------" << endl;
            cout << "" << endl;
            Encontrado = true;
        }else{}
        Mostrar  = Mostrar->sgte;
    }
    if(!Encontrado){
        cout << "No se ha encontrado un candidato con ese nombre." << endl;
        cout << "" << endl;
    }else{}
    getchar();
}


// Juntan las funciones de Mostrar senadores y diputados para mostrarlos en conjunto. Recibe la lista y muestra senadores y diputados.
void DiputadosYSenadores(Nodo *Nodito){
    cout << "Los postulados para diputado son " << endl;
    MostrarDiputados(Nodito);
    cout << "" << endl;
    cout << "Los postulados para senador son " << endl;
    MostrarSenadores(Nodito);
    cout << "" << endl;

}


// Archivo creado para quitar a candidatos de la lista.
void precargaArchivosNoEntran()
{
	FILE*f=fopen("NoEntran.bin", "wb");
	//RIP Pedro, Konrag y Gaga
	char rip1[20] = "Pedro";
	char rip2[20] = "Konrad";
	char rip3[20] = "Gaga";
	fwrite(&rip1, sizeof(rip1), 1, f);
	fwrite(&rip2, sizeof(rip2), 1, f);
	fwrite(&rip3, sizeof(rip3), 1, f);
	fclose(f);
	return;
}


// Menues solos son couts

void MenuDeOrden(){
    cout << "Como desea verlo?" << endl;
    cout << "1. Por Nombre de Candidato." << endl;
    cout << "2. Por Cantidad de Votos." << endl;
    cout << "3. Por Numero de Lista." << endl;
    cout << "4. Por Partido" << endl;
    cout << "5. Por Diputados Y Senadores." << endl;
    cout << "6. Por votos Diputados y Senadores" << endl;
    cout << "7. Volver." << endl;
}

void MenuPrincipal(){
    cout << "1. Cargar el archivo en una Lista" << endl;
    cout << "2. Mostrar Lista" << endl;
    cout << "3. Buscar informacion de candidato" << endl;
    cout << "4. Salir" << endl;

}

// Submenu del menu principal, trabaja con la lista creada. Solo se tiene acceso si la lista fue creada previamente.

void MenuDeOrdenamiento(Nodo *&partidos){
    char op;
    MenuDeOrden();
    op = getch();
        switch(op)

        do{
            case '1':
                system("cls");
                OrdenarPorNombre(partidos);
                Muestra(partidos);
                cout << "Pulse enter para volver al menu." << endl;
                getchar();
                break;
            case '2':
                system("cls");
                OrdenarPorVotos(partidos);
                Muestra(partidos);
                cout << "Pulse enter para volver al menu." << endl;
                getchar();
                break;
            case '3':
                system("cls");
                OrdenarPorLista(partidos);
                Muestra(partidos);
                cout << "Pulse enter para volver al menu." << endl;
                getchar();
                break;
            case '4':
                system("cls");
                OrdenarPorPartido(partidos);
                Muestra(partidos);
                cout << "Pulse enter para volver al menu." << endl;
                getchar();
                break;
            case '5':
                system("cls");
                DiputadosYSenadores(partidos);
                cout << "Pulse enter para volver al menu." << endl;
                getchar();
                break;
            case '6':
                system("cls");
                OrdenarPorVotos(partidos);
                DiputadosYSenadores(partidos);
                cout << "Pulse enter para volver al menu." << endl;
                getchar();
                break;
            case '7':
                system("cls");
                cout << "Que desea hacer?" << endl;
                MenuPrincipal();
                break;
            default:
                system("cls");
                cout << "Opcion no valida, por favor ingrese un digito valido."<<endl;
                MenuDeOrdenamiento(partidos);
                break;
        }while(op!='7');
}


// Menu principal divididos en subopciones, se sale del programa con el boton "4".
// Si no se carga el archivo y se crea la lista no se puede acceder a las otras opciones.
int main(){
    char opcion;
    Nodo*partidos = NULL;
    bool ExisteLista;
    ExisteLista = false;
    cout << "Bienvenido a la segunda parte del trabajo." << endl;
    cout << "Que desea hacer?" << endl;
    MenuPrincipal();
    do{
        opcion = getch();
            switch(opcion){
                case '1':
                    system("cls");
                    if(partidos==NULL){
                    LecturaYCarga(partidos);
                    ExisteLista = true;
                    cout << "Se cargo la lista con los postulantes que superaron la anterior etapa." << endl;
                    cout << "---------------------------" << endl;
                    cout << "Que desea hacer?" << endl;
                    }else{
                    cout << "Ya se cargo el archivo en la lista." << endl;
                    cout << "---------------------------" << endl;
                    cout << "Que desea hacer?" << endl;
                    }
                    MenuPrincipal();
                    break;
                case '2':
                    system("cls");
                    if(ExisteLista){
                        MenuDeOrdenamiento(partidos);
                        system("cls");
                    }else{
                    system("cls");
                    cout << "No existe ninguna lista cargada." << endl;
                    }
                    cout << "Que desea hacer?" << endl;
                    MenuPrincipal();
                    break;
                case '3':
                    system("cls");
                    if(ExisteLista){
                        BuscarCandidato(partidos);
                    }else{
                    system("cls");
                    cout << "No existe ninguna lista cargada." << endl;
                    }
                    cout << "Que desea hacer?" << endl;
                    MenuPrincipal();
                    break;
                case '4':
                    system("cls");
                    cout<<"Muchas gracias por probar nuestro programa, hasta luego!"<<endl;
                    break;
                default:
                    cout << "Opcion no valida, por favor ingrese un digito valido."<<endl;
                    break;




            }
    }while(opcion!='4');

}
