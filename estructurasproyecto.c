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












