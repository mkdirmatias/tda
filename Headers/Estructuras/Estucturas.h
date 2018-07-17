typedef int t_size;

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
*Estructura de persona
*/
typedef struct persona{
    RUT rut;
    char nombre[50];
    char a_paterno[50];
    char a_materno[50];
    FechaNacimiento Fecha;
}Persona;


/*
* Estructura de los empleados
*/
typedef struct Empleados
{
    Persona persona;
    char contrato[15];
    int salario;
    int cargas;
}Empleado;


/*
* Estructura de los departamentos
*/
typedef struct Departamentos
{
    int identificadorDepartamento;
    char nombreDepartamento[50];
    t_size numeroTrabajadoresDepartamento;
    Empleado *jefe_de_departamento;  //creo que a esto se refiere "trabajadores (relacion de estos)*
}Departamento;












