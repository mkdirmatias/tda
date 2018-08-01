#include <stdio.h>
#include <stdlib.h>

/*observacion. 
0=la posicion esta libre
1=significa que la posicion ya tiene un elemento.
2=la posicion esta libre pero estuvo ocupada.
*/

/*
* Constantes y variables
*/
typedef int t_key;
typedef int t_value;
t_key key;
t_value value;


/*
* Estructura del elemento
*/
typedef struct pair
{
    // clave
    t_key key;
    // valor
    Empleado value;
    Departamento depto;
}pair ;


/*
* Estructura de la tabla hash
*/
typedef struct t_hash
{
    pair t[EMPLEADOS];
    int disponible[EMPLEADOS];
    int total_empleados;
    int total_departamentos;
}t_hash;


/**
* Obtiene el modulo
* @param  key clave que se usará
* @return     retorna el modulo entre la clave y el maximo de elementos de la tabla
*/
t_key h(t_key key)
{
    int modulo = key%EMPLEADOS;
    
    if(modulo==0)
    {
        modulo++;
    }
    
    return modulo;
}


/**
* Busca un elemento en la tabla
* @param  tabla Tabla Hash
* @param  clave Clave a buscar
* @param  tipo 1 para departamento y 2 para empleados
* @return       Retorna el elemento
*/
int buscar(t_hash *tabla, t_key clave, int tipo)
{
    if(tabla->disponible[clave]==1)
    {
        if(tipo==2)
        {
            if(h(tabla->t[clave].value.rut.rut)+1==clave)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if (h(tabla->t[clave].depto.identificadorDepartamento)+1==clave)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
    return 0;
}


/**
* Inserta elemento en tabla hash
* @param tabla    Tabla Hash
* @param tipo    1 para departamentos y 2 para empleados
* @param elemento Elemento a insertar, de tipo pair (clave-valor)
*/
void insertar(t_hash *tabla , pair elemento, int tipo)
{
    int newKey=h(elemento.key);
    
    do
    {
        newKey++;
    }while(buscar(tabla,newKey,tipo)==1);

    tabla->t[newKey]=elemento;
    tabla->disponible[newKey]=1;

    // aumentamos la cantidad de registros, para departamentos
    if(tipo==1)
    {
        tabla->total_departamentos++;
    }
    else
    {
        // y para empleados
        tabla->total_empleados++;
    }
}


/**
* Eliminar elemento en tabla hash
* @param tabla Tabla Hash
* @param clave Clave del elemento a eliminar
*/
void eliminar(t_hash*tabla,t_key clave)
{
    tabla->disponible[h(clave)]=2;
}
