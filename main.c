#include "utils.h"
#include <errno.h>
#include <direct.h>
#include <windows.h>

#define EXISTE 0
#define NO_EXISTE 1
#define ROTO -1
#define SIN_CARGA -1

#define MIN_USERS 0
#define MAX_USERS 20

#define VACIO 0

typedef struct
{
    cadena nombre;
    int edad;
} Persona;

///////////////////funciones/////////////////////
int cargarPersonas(Persona lista[], int *cant);
void guardarPersonas(Persona lista[], int cant);
void limpiarPantalla(void);

///////crud/////
void inicio();
void verLista(Persona lista[], int cant);
void agregarALista(Persona lista[], int *cant);
void elegirOpcion(Persona lista[], int *cant);
///////////////////////////////////////////////////

int main(void)
{
    // Persona listaPersonas[MAX_USERS] = {
    //     {.nombre = "Esteban", .edad = 33},
    //     {.nombre = "Belen", .edad = 35},
    //     {.nombre = "Cleopatra", .edad = 10},
    //     {.nombre = "Thelma", .edad = 6}
    // };
    Persona listaPersonas[MAX_USERS];
    int cantidadPersonas = 0;
    int cantidadLeida = cargarPersonas(listaPersonas, &cantidadPersonas);
    
    if(cantidadLeida >=0){
        cantidadPersonas = cantidadLeida;
    }else{
        puts("No se pudo cargar usuarios");
    }

    elegirOpcion(listaPersonas, &cantidadPersonas);
    return 0;
}

int cargarPersonas(Persona lista[], int *cant)
{

    int cantidad = -1;
    FILE *f = fopen("../data/personas.dat", "rb");

    if (f != NULL)
    {

        if (fread(cant, sizeof(int), 1, f) == 1 && (*cant >= MIN_USERS && *cant <= MAX_USERS))
        {
            if (fread(lista, sizeof(Persona), *cant, f) == (size_t)*cant && (fgetc(f) == EOF && !ferror(f)))
            {
                puts("Usuarios leidos correctamente");
            }else{
                puts("Error en lectura de usuarios");
            }
        }
        fclose(f);
    }
    else if (errno == ENOENT)
    {
        (*cant) = MIN_USERS;
    }
    return cantidad;
}

void guardarPersonas(Persona lista[], int cant)
{
    FILE *f = fopen("../data/personas.dat", "wb");

    if (f != NULL)
    {
        if (fwrite(&cant, sizeof(int), 1, f) == 1 && (cant >= 0 && cant <= 20))
        {

           (fwrite(lista, sizeof(Persona), cant, f) == (size_t)cant)? "Todo ok" : "Error al guardar";
        }

        fclose(f);

    }
    else
    {
        perror("Error");
    }
}


void inicio(){
    puts("\n1. Agregar a la lista\n2. Ver lista\n0. Salir");
}

void elegirOpcion(Persona lista[], int *cant){
    int opc;
    do {
        system("cls");
        inicio();
        opc = leerEnteroEntre(0, 2, "Elija una opcion: ");
        switch(opc){
            case 1:
                agregarALista(lista, cant);
                break;
            case 2:
                verLista(lista, *cant);
                break;
        }
    } while(opc != 0);

    guardarPersonas(lista, *cant);
}

void agregarALista(Persona lista[], int *cant){
    system("cls");
    if (*cant < MAX_USERS){
        cadena nombre;
        getchar();
        leerCadena("Ingrese un nombre: ", nombre);
        int edad = leerEnteroEntre(1, 99, "Ingrese una edad: ");
        bool confirma = confirmaUsuario("Desea confirmar datos?");
        if(confirma){
            strcpy(lista[*cant].nombre, nombre);
            lista[*cant].edad = edad;
            (*cant)++;
            puts("Usuario agregado con exito.");
        }else{
            puts("Operacion cancelada");
        }
    }else{
        puts("La lista esta completa.");
    }
    system("pause");
}

void verLista(Persona lista[], int cant){
    system("cls");
    if (cant != VACIO){
        puts("Lista de usuarios:");
        for (int i = 0; i < cant; i++){
            printf("%d. Nombre: %s, Edad: %d\n", i + 1, lista[i].nombre, lista[i].edad);
        }
    }else{
        puts("---La lista esta vacia.---");
    }
    system("pause");
}