#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/**
* Verifica si existe una subcadena dentro de otra, para nuestro caso,
* la usaremos para verificar si existen puntos y guion en el rut.
* @param  cadena   String a evaluar
* @param  caracter Caracter a recorrer
* @return          Retorna 1 en caso de existir y 0 en caso contrario
*/
int verificar_caracter(char *cadena, char *caracter)
{
    char *retorno;
    retorno = strstr( cadena, caracter );
    if(retorno)
    {
        return 1;
    }

   return 0;
}



/**
* Quitar puntos y guion a un rut
* @param  rut Rut que se limpiará
* @return     Devuelve el rut sin puntos, guion y digito verificador
*/
int limpiar_rut(char *rut)
{
    int i,x=0;
    char *separado,otro[100];
    if(!verificar_caracter(rut,"-"))
    {
        return 0;
    }
    else
    {
        if(!verificar_caracter(rut,"."))
        {
            // existe guion pero no punto
            // separamos
            separado=strtok(rut,"-");
        }
        else
        {
            // existe punto y guion
            // eliminamos los puntos
            for (i=0; i < 12; ++i)
            {
                if(rut[i] != '.')
                {
                    otro[x]=rut[i];
                    x++;
                }
            }
            separado=strtok(otro,"-");
        }
    }
    return atoi(separado);
}





/**
* Convierte un string a int, mediante la suma de sus valores ascii
* @param  string Palabra a convertir
* @return        retorna la suma de los valores ascii de cada caracter
*/
int stringToInt(char *string)
{
    int i;
    int ascii=0;
    for (i=0; i<strlen(string); i++)
    {
        int letra;
        letra=toupper(string[i]);
        ascii=ascii+letra;
    }
    
    return ascii;
}





/**
* Verifica si un RUT es válido o no
* @param  rut                rut sin puntos ni digito verificador
* @param  digito_verificador digito verificador solo
* @return                    Retorna 1 si es válido y 0 si no
*/
int valida_rut(int rut, char *digito_verificador)
{
    int completo[10],i,suma=0,modulo,verificador;
    
    // convertimos el rut en array
    for (i=1; i<10; i++)
    {
        completo[i] = rut % 10;
        if(i>=1 && i<7)
        {
            suma=suma+completo[i]*(i+1);
        }
        
        if(i==7)
        {
            suma=suma+completo[i]*2;
        }
        
        if(i==8)
        {
            suma=suma+completo[i]*3;
        }
        
        rut /= 10;
    }
    
    // calculamos el modulo
    modulo=suma/11;
    modulo=modulo*11;
    modulo=suma-modulo;
    verificador=11-modulo;
    char letra = toupper(digito_verificador[0]);
    
    if(strcmp(&letra, "K") == 10)
    {
        if(verificador==10)
        {
            return 1;
        }
        else
        {
            // Mensaje
            printf("Ingresa un RUT valido\n");
            return 0;
        }
    }
    else
    {
        int new_dv=atoi(digito_verificador);
        if(verificador==11 && new_dv==0)
        {
            return 1;
        }
        else if(verificador==new_dv)
        {
            return 1;
        }
        else
        {
            // Mensaje
            printf("Ingresa un RUT valido\n");
            return 0;
        }
    }
    return 0;
}





/**
 * Valida que una fecha sea correcta
 * @param  dia  Día del mes a validar
 * @param  mes  Mes del año a validar
 * @param  year Año a validar
 * @return      Retorna 1 en caso de ser válida y 0 en caso contrario
 */
int validar_fecha(int dia,int mes,int year)
{
    // El mes debe ser entre 1 y 12
    if ( mes >= 1 && mes <= 12 )
    {
        // Validamos los dias de cada mes
        switch (mes)
        {
                // Enero, Marzo, Mayo, Julio, Agosto, Octubre y Diciembre tienen 31 días
            case  1 :
            case  3 :
            case  5 :
            case  7 :
            case  8 :
            case 10 :
            case 12 :
                if (dia >= 1 && dia <= 31)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
                break;
                
                // Abril, Junio, Septiembre y Noviembre tienen 30 días
            case  4 :
            case  6 :
            case  9 :
            case 11 :
                if (dia >= 1 && dia <= 30)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
                break;
                
                // Febrero tiene 29 días y 28 si es bisiesto
            case  2 :
                if((year%4 == 0 && year%100 != 0) || year%400 == 0)
                {
                    if ( dia >= 1 && dia <= 29 )
                    {
                        return 1;
                    }
                    else
                    {
                        if(dia >= 1 && dia <= 28)
                        {
                            return 1;
                        }
                        else
                        {
                            return 0;
                        }
                    }
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
* Agregar un empleado y guardarlo en la tabla hash, como en el archivo txt
* @param t_empleados     tabla hash empleados
* @param empleados       elemento pair empleados
* @param employe         strutct empleados
* @param t_departamentos tabla hash departamentos
* @param tipo 1 si es agregar usuario y 2 si se está editando
*/
void agregar_empleado(t_hash *t_empleados,pair empleados[caracteres],Empleado employe,t_hash *t_departamentos, int tipo, char rut_v)
{
    // Variables
    char primer_nombre[caracteres], segundo_nombre[caracteres], apellido_paterno[caracteres], apellido_materno[caracteres], contrato[caracteres], rut_completo[caracteres], solicitar_rut[caracteres], *elemento_rut, *dv = NULL, ID_departamento;
    
    int dia,mes,year,salario,cargas,rut;
    
    RUT rut_empleado;
    
    // Solicitmamos el departamento
    do
    {
        printf("Ingresa el departamento: ");
        scanf("%s",&ID_departamento);
    }while(buscar(t_departamentos, stringToInt(&ID_departamento)) != 1);

    
    // Solicitamos rut
    do
    {
        rut_completo[0]='\0';
        printf("RUT: ");
        scanf("%s",solicitar_rut);
        elemento_rut = strtok(solicitar_rut,".-");
    
        int contador_rut=0;
    
        while (elemento_rut != NULL)
        {
            if(contador_rut!=3)
            {
                strcat(rut_completo, elemento_rut);
            }
            else
            {
                dv=elemento_rut;
            }
            elemento_rut = strtok(NULL, ".-");
            contador_rut++;
        }
        rut=atoi(rut_completo);
        
    }while(valida_rut(rut,dv) != 1);
    rut_empleado.rut=rut;
    rut_empleado.verificador=atoi(dv);
    

    // Solicitamos primer nombre
    printf("Primer nombre: ");
    scanf("%s",primer_nombre);
    

    // Solicitamos segundo nombre
    printf("Segundo nombre: ");
    scanf("%s",segundo_nombre);

    
    // Solicitamos Apellido paterno
    printf("Apellido Paterno: ");
    scanf("%s",apellido_paterno);
    

    // Solicitamos Apellido materno
    printf("Apellido Materno: ");
    scanf("%s",apellido_materno);
    

    // Solicitamos Fecha de nacimiento
    do
    {
        printf("Fecha De Nacimiento (dia-mes-año): ");
        scanf("%d-%d-%d",&dia,&mes,&year);
    }while(validar_fecha(dia,mes,year) != 1);
    

    // Solicitamos tipo de contrato
    printf("Tipo de contrato: ");
    scanf("%s",contrato);
    

    // Solicitamos salario
    printf("Salario: ");
    scanf("%i",&salario);
    

    // Solicitamos las cargas
    printf("Cargas: ");
    scanf("%i",&cargas);
    
    
    // Guardamos el empleado en la tabla
    employe.rut=rut_empleado;
    strcpy(employe.primer_nombre, primer_nombre);
    strcpy(employe.segundo_nombre, segundo_nombre);
    strcpy(employe.a_paterno, apellido_paterno);
    strcpy(employe.a_materno, apellido_paterno);
    employe.dia=dia;
    employe.mes=mes;
    employe.year=year;
    strcpy(employe.contrato, contrato);
    employe.salario=salario;
    employe.cargas=cargas;
    employe.ID_departamento=stringToInt(&ID_departamento);

    empleados[t_empleados->total_empleados].key=rut_empleado.rut;
    empleados[t_empleados->total_empleados].value=employe;
    
    printf("%i\n",rut_empleado.rut);
    
    insertar(t_empleados, empleados[t_empleados->total_empleados],2);

    // Guardamos al empleado en el archivo txt
    FILE *archivo;
    archivo = fopen("Headers/Archivos/empleados.txt", "a");
    fprintf(archivo, "%s,%s,%s,%s,%s,%s,%i,%i,%i,%s,%i,%i\n",rut_completo,dv,primer_nombre,segundo_nombre,apellido_paterno,apellido_materno,dia,mes,year,contrato,salario,cargas);
    
    
    // Mensaje
    printf("Empleado Agregado");

    // cerramos el archivo
    fclose(archivo);
}




void editar_empleado(t_hash *t_empleados,pair empleados[caracteres],Empleado employe,t_hash *t_departamentos, char rut)
{
    if(buscar(t_empleados,limpiar_rut(&rut)) == 1)
    {
        agregar_empleado(t_empleados, empleados, employe, t_departamentos,2,rut);
    }
    else
    {
        printf("\n El usuario no existe\n");
    }
}



/**
* Carga los departamentos del archivo txt a la tabla hash
* @param t_departamentos Tabla hash departamentos (pasada por referencia *)
* @param departamentos   Elemento tipo pair para guardar los datos
* @param depto           struct del departamento que se guardará en el elemento pair
*/
void cargar_departamentos(t_hash *t_departamentos, pair departamentos[caracteres], Departamento depto)
{
    /*
    * Cargamos los datos
    */
    FILE *bd_deptos;
    char linea[100];
    char *linea_depto;
    
    // abrimos el archivo txt
    bd_deptos = fopen("Headers/Archivos/departamentos.txt","r");
    
    // verificamos que exista
    if (bd_deptos == NULL)
    {
        exit(1);
    }
    else
    {
        // recorremos las lineas
        while (feof(bd_deptos) == 0)
        {
            // obtenemos una linea
            fgets(linea,100,bd_deptos);

            // separamos las palabras por coma
            linea_depto = strtok(linea,",");
            int item=0,identificador;

            // recorremos las palabras
            while (linea_depto != NULL)
            {
                // si es 0, es el identificador
                if(item==0)
                {
                    identificador=atoi(linea_depto);
                    depto.identificadorDepartamento=identificador;
                }
                else
                {
                    // si no, es el nombre
                    strcpy(depto.nombreDepartamento, linea_depto);
                }
                linea_depto = strtok(NULL, ",");
                item++;
            }
            // generamos la estructura el pair
            departamentos[t_departamentos->total_departamentos].key=identificador;
            departamentos[t_departamentos->total_departamentos].depto=depto;

            // y lo guardamos en la tabla
            insertar(t_departamentos, departamentos[t_departamentos->total_departamentos],1);
        }
    }
    // cerramos el archivo
    fclose(bd_deptos);
}



/**
* Buscar los datos de un empleado
* @param empleados Tabla hash empleados
* @param key       La key será el rut del empleado
*/
void buscar_empleado(t_hash *empleados, int key)
{
    if(buscar(empleados, key) == 1)
    {
        printf("\n Información Empleado\n");
        
        printf(" RUT: %i-%i \n Nombre:  %s %s %s %s \n Fecha Nacimiento: %i-%i-%i \n Contrato: %s \n Sueldo: %i \n Cargas: %i \n ", empleados->t[h(key)].value.rut.rut,empleados->t[h(key)].value.rut.verificador,empleados->t[h(key)].value.primer_nombre,empleados->t[h(key)].value.segundo_nombre,empleados->t[h(key)].value.a_paterno,empleados->t[h(key)].value.a_materno,empleados->t[h(key)].value.dia,empleados->t[h(key)].value.mes,empleados->t[h(key)].value.year,empleados->t[h(key)].value.contrato,empleados->t[h(key)].value.salario,empleados->t[h(key)].value.cargas);
        
    }
    else
    {
        printf("\n El empleado no existe\n");
    }
}




/**
* Cargar los empleados desde el archivo txt a la tabla hash
* @param t_empleados tabla hash empleados
* @param empleados   elemento pair empleados
* @param employe     struct empleado
*/
void cargar_empleados(t_hash *t_empleados, pair empleados[caracteres], Empleado employe)
{
    /*
    * Cargamos los datos
    */
    FILE *db_empleados;
    char linea[100];
    char *linea_empleado;
    
    // abrimos el archivo txt
    db_empleados = fopen("Headers/Archivos/empleados.txt","r");
    
    // verificamos que exista
    if (db_empleados == NULL)
    {
        exit(1);
    }
    else
    {
        // recorremos las lineas
        while (feof(db_empleados) == 0)
        {
            // obtenemos una linea
            fgets(linea,100,db_empleados);

            // separamos las palabras por coma
            linea_empleado = strtok(linea,",");
            int item=0;
            
            // Generamos el RUT
            RUT rut_sindigito;
            
            // recorremos las palabras
            while (linea_empleado != NULL)
            {
                // si es 0, es el rut sin digito verificador
                switch(item)
                {
                    case 0:
                        rut_sindigito.rut=atoi(linea_empleado);
                        break;
                    case 1:
                        rut_sindigito.verificador=atoi(linea_empleado);
                    case 2:
                        strcpy(employe.primer_nombre, linea_empleado);
                    case 3:
                        strcpy(employe.segundo_nombre, linea_empleado);
                    case 4:
                        strcpy(employe.a_paterno, linea_empleado);
                    case 5:
                        strcpy(employe.a_materno, linea_empleado);
                    case 6:
                        employe.dia=atoi(linea_empleado);
                    case 7:
                        employe.mes=atoi(linea_empleado);
                    case 8:
                        employe.year=atoi(linea_empleado);
                    case 9:
                        strcpy(employe.contrato, linea_empleado);
                    case 10:
                        employe.salario=atoi(linea_empleado);
                    case 11:
                        employe.cargas=atoi(linea_empleado);
                    case 12:
                        employe.ID_departamento=stringToInt(linea_empleado);
                }
                employe.rut=rut_sindigito;
                linea_empleado = strtok(NULL, ",");
                item++;
            }
            // generamos la estructura el pair
            empleados[t_empleados->total_empleados].key=rut_sindigito.rut;
            empleados[t_empleados->total_empleados].value=employe;

            // y lo guardamos en la tabla
            insertar(t_empleados, empleados[t_empleados->total_empleados],2);
        }
    }
    // cerramos el archivo
    fclose(db_empleados);
}




/**
* Listar todos los departamentos
* @param t_departamentos Tabla hash de departamentos
* @param departamentos   elemento pair de los departamentos
*/
void listar_departamentos(t_hash t_departamentos, pair departamentos[caracteres])
{
    int i;
    printf(" \nDepartamentos: \n\n");
    for (i=0; i<t_departamentos.total_departamentos-1; i++)
    {
        if(buscar(&t_departamentos,departamentos[i].key) != 0)
        {
            printf(" - %s\n",t_departamentos.t[h(departamentos[i].key)].depto.nombreDepartamento);
        }
    }
}




/**
* ELiminar departamento, disponibilidad == 2
* @param t_departamentos Tabla hash departamentos
* @param key             el key es la suma del valor ascii de cada letra del nombre
*/
void eliminar_departamentos(t_hash *t_departamentos, int key)
{
    if(buscar(t_departamentos,key)==1)
    {
        t_departamentos->disponible[h(key)]=2;
    }
    else
    {
        printf("\n El departamento no existe\n");
    }
}




/**
* Eliminar un usuario, disponibilidad == 2
* @param t_departamentos Tabla hash de empleados
* @param key             el key es el rut del usuario
*/
void eliminar_empleados(t_hash *t_empleados, int key)
{
    printf("%d\n", key);
    if(buscar(t_empleados,key)==1)
    {
        t_empleados->disponible[h(key)]=2;
    }
    else
    {
        printf("\n El empleado no existe\n");
    }
}




/**
 * Agregar un departamento
 * @param t_departamentos tabla hash departamentos
 * @param departamentos   elemento pair departamentos
 * @param depto           struct Departamento
 */
void agregar_departamento(t_hash *t_departamentos, pair departamentos[caracteres], Departamento depto)
{
    // Variables
    char nombre;
    int identificador;
    
    // Solicitmamos el nombre
    do
    {
        printf("Nombre Departamento: ");
        scanf("%s",&nombre);
        identificador=stringToInt(&nombre);
    }while(buscar(t_departamentos, identificador) != 0);
    
    
    // Guardamos el empleado en la tabla
    strcpy(depto.nombreDepartamento, &nombre);
    depto.identificadorDepartamento=identificador;
    

    //departamentos[t_departamentos->total_departamentos].key=identificador;
    //departamentos[t_departamentos->total_departamentos].depto=depto;
    //insertar(t_departamentos, *departamentos, 1);
    
    // Guardamos al empleado en el archivo txt
    FILE *archivo;
    archivo = fopen("Headers/Archivos/departamentos.txt", "a");
    fprintf(archivo, "%i,%s\n",identificador,&nombre);
    fclose(archivo);
    
    // Mensaje
    printf("Departamento Agregado");
}
