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

typedef struct
{
    cadena nombre;
    int edad;
} Persona;

///////////////////funciones/////////////////////
int cargarPersonas(Persona lista[], int *cant);
bool guardarPersonas(Persona lista[], int cant);

///////////////////////////////////////////////////

int main(void)
{
    // Persona listaPersonas[MAX_USERS] = {
    //     {nombre : "Esteban", edad : 33},
    //     {nombre : "Belen", edad : 35},
    //     {nombre : "Cleopatra", edad : 10}
    // };

    Persona listaPersonas[MAX_USERS];
    int cantidad = 3;
    
    int resultado = cargarPersonas(listaPersonas, &cantidad);

    
    if (resultado != ROTO){
        for (int i = 0; i < cantidad; i++){
            printf("%d. Nombre: %s, Edad: %d\n",i+1,listaPersonas[i].nombre,listaPersonas[i].edad);
        }

        if(!guardarPersonas(listaPersonas, cantidad)){
            puts("Error al guardar personas");
        }
    }else{
        puts("Hubo un error.");
    }
    
    return 0;
}

int cargarPersonas(Persona lista[], int *cant)
{

    int carga = ROTO;
    FILE *f = fopen("../data/personas.dat", "rb");

    if (f != NULL)
    {

        if (fread(cant, sizeof(int), 1, f) == 1 && (*cant >= MIN_USERS && *cant <= MAX_USERS))
        {
            if (fread(lista, sizeof(Persona), *cant, f) == (size_t)*cant && (fgetc(f) == EOF && !ferror(f)))
            {
                carga = EXISTE;
            }
        }
        fclose(f);
    }
    else if (errno == ENOENT)
    {
        (*cant) = MIN_USERS;
        carga = NO_EXISTE;
    }
    return carga;
}

bool guardarPersonas(Persona lista[], int cant)
{
    FILE *f = fopen("../data/personas.dat", "wb");
    bool respuesta = false;
    int cierre;

    if (f != NULL)
    {
        if (fwrite(&cant, sizeof(int), 1, f) == 1 && (cant >= 0 && cant <= 20))
        {

            respuesta = (fwrite(lista, sizeof(Persona), cant, f) == (size_t)cant);
        }
        cierre = fclose(f);
        if (cierre != 0)
        {
            respuesta = false;
        }
    }
    else
    {
        perror("Error");
    }
    return respuesta;
}