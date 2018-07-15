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
#define max 100
typedef int t_key;
typedef int t_value;
t_key key;
t_value value;


/*
* Estructura del elemento
*/
typedef struct pair{
    t_key key;//clave
    t_value value;//valor
}pair ;


/*
* Estructura de la tabla hash
*/
typedef struct t_hash
{
    pair t[max];
    int disponible[max];
}t_hash;


/**
* Obtiene el modulo
* @param  key clave que se usará
* @return     retorna el modulo entre la clave y el maximo de elementos de la tabla
*/
t_key h(t_key key)
{
    return key%max;
}


/**
* Inserta elemento en tabla hash
* @param tabla    Tabla Hash
* @param elemento Elemento a insertar, de tipo pair (clave-valor)
*/
void insertar( t_hash * tabla , pair elemento )
{
    tabla->t[h(elemento.key)]=elemento;
    tabla->disponible[h(elemento.key)]=1;
}


/**
* Busca un elemento en la tabla
* @param  tabla Tabla Hash
* @param  clave Clave a buscar
* @return       Retorna el elemento
*/
t_value buscar(t_hash* tabla,t_key clave)
{
    if((tabla->disponible[h(clave)]=1))
    {
        return tabla->disponible[h(clave)]=2;
    }
    return 0;
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
