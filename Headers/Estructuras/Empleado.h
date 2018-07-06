/*
* Estructura del RUT
*/
typedef struct RUT
{
    // Eliminar puntos y dejar sólo los digitos
    int rut;
    
    // Caracter entre 0-9 o K
    char verificador;
}RUT;


/*
* Estructura fecha de nacimiento
*/
typedef struct FechaNacimiento
{
    int dia;
    int mes;
    int year;
}FechaNacimiento;


/*
* Estructura de los empleados
*/
typedef struct Empleados
{
    RUT rut;
    char nombre[50];
    char a_paterno[50];
    char a_materno[50];
    FechaNacimiento Fecha;
    char contrato[15];
    int salario;
    int cargas;
}empleado;











