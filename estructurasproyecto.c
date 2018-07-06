//tipos de datos
typedef enum MES{enero,febrero,marzo,abril,
mayo,junio,juio,agosto,septiembre,
octubre,noviembre,diciembre}month; //enum de los meses

typedef enum contrato{Fijo,Indefinido,Faena, Dia,Honorarios
}contract;

typedef enum verif_rut{0,1,2,3,4,5,6,7,8,9,k}VERIF_RUT;

typedef struct {
	int digitos[8];
	VERIF_RUT verificador;
}RUT;



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












