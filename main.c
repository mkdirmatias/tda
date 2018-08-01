#include "Headers/Tipos/definiciones.h"
#include "Headers/Estructuras/Structs.h"
#include "Headers/Tipos/tablaHash.h"
#include "Headers/Funciones/funciones.h"



int main()
{
    /*
    * Iniciamos las estructras
    */
    t_hash t_empleados;
    t_empleados.total_empleados=0;
    pair empleados[EMPLEADOS];
    Empleado employe;
    
    // Departamentos
    t_hash t_departamentos;
    t_departamentos.total_departamentos=0;
    pair departamentos[EMPLEADOS];
    Departamento depto;
    
    /*
    * Cargamos los empleados
    */
    cargar_empleados(&t_empleados, empleados, employe);
    
    /*
    * Cargamos los departamentos
    */
    cargar_departamentos(&t_departamentos, departamentos, depto);

    /*
    * Mostrar El menú
    */
   // printf("%i\n", limpiar_rut("18987638-6"));
   // return 1;
    int opcion;
    char rut_buscar[caracteres],nombre_departamento[caracteres];

    while(1)
    {
        printf(" MENU PRINCIPAL:\n 1) Listar departamentos \n 2) Ingresar un empleado \n 3) Ingresar un departamento \n 4) Mostrar información empleado \n 5) Editar un empleado \n 6) Eliminar empleado \n 7) Eliminar departamento \n 8) Mostrar total empleados \n 9) Generar liquidacion de sueldo \n 0) Para salir \n\n");
        
        /*
        * Solicitamos la opción a seleccionar 
        */
        do
        {
            printf(" Selecciona una opcion: ");
            scanf("%d",&opcion);
        }while(opcion < 0 || opcion > 11);


        /*
        * Ejecutamos la acción según la opcion que seleccione el usuario
        */
        switch(opcion)
        {
            case 1:
                listar_departamentos(t_departamentos, departamentos);
                break;
            case 2:
                agregar_empleado(&t_empleados, empleados, employe, &t_departamentos,1,'a');
                break;
            case 3:
                agregar_departamento(&t_departamentos, departamentos, depto);
                break;
            case 4:
                printf("\n RUT empleado: ");
                scanf("%s",rut_buscar);
                buscar_empleado(&t_empleados,rut_buscar,limpiar_rut(rut_buscar));
                break;
            case 5:
                printf("\n RUT empleado: ");
                scanf("%s",rut_buscar);
                editar_empleado(&t_empleados, empleados, employe, &t_departamentos,rut_buscar,limpiar_rut(rut_buscar));
                break;
            case 6:
                printf("\n Rut del empleado: ");
                scanf("%s",rut_buscar);
                eliminar_empleados(&t_empleados, h(limpiar_rut(rut_buscar)),1);
                break;
            case 7:
                printf("\n Nombre Departamento: ");
                scanf("%s",nombre_departamento);
                eliminar_departamentos(&t_departamentos, h(stringToInt(nombre_departamento)));
                break;
            case 8:
                printf("\n El total de empleados es: %i\n", t_empleados.total_empleados-1);
                break;
            case 9:
                printf("\n Rut del empleado: ");
                scanf("%s",rut_buscar);
                int limpio=limpiar_rut(rut_buscar);
                liquidacion(t_empleados,h(limpio),limpio);
                break;
            case 11:
                respaldar_empleados(t_empleados,empleados);
                respaldar_departamentos(t_departamentos,departamentos);
                exit(1);
        }
        printf("\n\n");
    }

    return 0;
}
