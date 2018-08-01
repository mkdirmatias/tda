/*
* Estructura de los departamentos
*/
typedef struct Departamentos
{
    int identificadorDepartamento;
    char nombreDepartamento[50];
    int empleados[EMPLEADOS];
}Departamento;


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
* Estructura de los empleados
*/
typedef struct Empleados
{
    struct Empleados *next;
    RUT rut;
    char primer_nombre[50];
    char segundo_nombre[50];
    char a_paterno[25];
    char a_materno[25];
    int dia;
    int mes;
    int year;
    char contrato[15];
    int salario;
    int cargas;
    int ID_departamento;
}Empleado;
