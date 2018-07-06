//tipos de datos

typedef enum MES{enero,febrero,marzo,abril,
mayo,junio,juio,agosto,septiembre,
octubre,noviembre,diciembre}month; //enum de los meses

typedef enum contrato{Fijo,Indefinido,Faena, Dia,Honorarios
}contract;

typedef struct {
	int digitos[8];
	char verificador;//hay que limitarlo para usar numeros 0-9 y k
}RUT;

/*typedef struct{
	int dia;
	MES mes;
	int año;
}birth;*/ //cambiarlo por time.h

typedef struct{
	RUT rut;
	char nombre[50];
	char A_paterno[50];
	char A_materno[50];
	fecha_de_nacimiento		;
	contract contrato; 
	int salario;
	int carga;			//carga familiar
	
}employee;

typedef struct{
	
	
}apartment;

/*tabla hash simple no considera colisiones.
0=la direccion esta libre
1=la direccion esta ocupada
2=la direccion esta libre pero estuvo ocupada en algun momento.
*/

#include <stdio.h>
#include <stdlib.h>
#define max 100
typedef int t_key;
typedef int t_value;
t_key key;

t_value value;


t_key h(t_key);

typedef struct pair{
	t_key key;
	t_value value;
}pair ;

typedef struct t_hash{
	pair t[max];
	int disponible[max];
}t_hash;


t_key h(t_key key){  //funcion modular
	return key%max;
}

void insertar( t_hash * tabla , pair elemento );
void buscar( t_hash * tabla , t_key clave );
void eliminar( t_hash * tabla , t_key clave );

int main(){

	
	return 0;
}

void insertar( t_hash * tabla , pair elemento ){//elemento tipo pair (valor y key)
	tabla->t[h(elemento.key)]=elemento;
	tabla->disponible[h(elemento.key)]=1;
	return tabla;
}
void buscar(t_hash* tabla,t_key clave){
	if(tabla->disponible[h(clave)]=1){
		return tabla->disponible[h(clave)]=2;
	}
}
void eliminar(t_hash*tabla,t_key clave){
	tabla ->disponible[h(clave)]=2;
}











