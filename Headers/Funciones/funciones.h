#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



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
    retorno = strstr(cadena, caracter);
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
            separado = strtok(rut,"-");
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
void agregar_empleado(t_hash *t_empleados,pair empleados[caracteres],Empleado employe,t_hash *t_departamentos, int tipo, int rut_v)
{
    // Variables
    char primer_nombre[caracteres], segundo_nombre[caracteres], apellido_paterno[caracteres], apellido_materno[caracteres], contrato[caracteres], rut_completo[caracteres], solicitar_rut[caracteres], *elemento_rut, *dv = NULL, ID_departamento;
    
    int dia,mes,year,salario,cargas,rut;
    
    RUT rut_empleado;
    
    // Solicitmamos el departamento
    do
    {
        printf("\n Ingresa el departamento: ");
        scanf("%s",&ID_departamento);
    }while(buscar(t_departamentos, h(stringToInt(&ID_departamento))+1,1) != 1);

    // Solicitamos rut
    if(tipo == 1)
    {
        do
        {
            rut_completo[0]='\0';
            printf(" RUT: ");
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
                    if(elemento_rut==0)
                    {
                        dv="0";
                    }
                    else
                    {
                        dv=elemento_rut;
                    }
                }
                elemento_rut = strtok(NULL, ".-");
                contador_rut++;
            }
            rut=atoi(rut_completo);
            
        }while(valida_rut(rut,dv) != 1);
        rut_empleado.rut=rut;
        rut_empleado.verificador=atoi(dv);
    }
    else
    {
        rut_empleado.rut=t_empleados->t[h(rut_v)+1].value.rut.rut;
        rut_empleado.verificador=t_empleados->t[h(rut_v)+1].value.rut.verificador;
    }
    

    // Solicitamos primer nombre
    printf(" Primer nombre: ");
    scanf("%s",primer_nombre);
    

    // Solicitamos segundo nombre
    printf(" Segundo nombre: ");
    scanf("%s",segundo_nombre);

    
    // Solicitamos Apellido paterno
    printf(" Apellido Paterno: ");
    scanf("%s",apellido_paterno);
    

    // Solicitamos Apellido materno
    printf(" Apellido Materno: ");
    scanf("%s",apellido_materno);
    

    // Solicitamos Fecha de nacimiento
    do
    {
        printf(" Fecha De Nacimiento (dia-mes-año): ");
        scanf("%d-%d-%d",&dia,&mes,&year);
    }while(validar_fecha(dia,mes,year) != 1);
    

    // Solicitamos tipo de contrato
    printf(" Tipo de contrato: ");
    scanf("%s",contrato);
    

    // Solicitamos salario
    printf(" Salario: ");
    scanf("%i",&salario);
    

    // Solicitamos las cargas
    printf(" Cargas: ");
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
    
    insertar(t_empleados, empleados[t_empleados->total_empleados],2);

    // Guardamos al empleado en el archivo txt
    FILE *archivo;
    archivo = fopen("Headers/Archivos/empleados.txt", "a");
    
    if(tipo==1)
    {
        fprintf(archivo, "%s,%s,%s,%s,%s,%s,%i,%i,%i,%s,%i,%i\n",rut_completo,dv,primer_nombre,segundo_nombre,apellido_paterno,apellido_materno,dia,mes,year,contrato,salario,cargas);
    }
    else
    {
        fprintf(archivo, "%i,%i,%s,%s,%s,%s,%i,%i,%i,%s,%i,%i\n",rut_empleado.rut,rut_empleado.verificador,primer_nombre,segundo_nombre,apellido_paterno,apellido_materno,dia,mes,year,contrato,salario,cargas);
    }
    
    
    // Mensaje
    if(tipo==1)
    {
        printf("\n Empleado Agregado");
    }
    else
    {
        printf("\n Empleado Editado");
    }

    // cerramos el archivo
    fclose(archivo);
}




/**
* Eliminar un usuario, disponibilidad == 2
* @param t_empleados Tabla hash de empleados
* @param key         el key es el rut del usuario
* @param mensaje     1 para mostrar y 2 para no mostrar 
*/
void eliminar_empleados(t_hash *t_empleados, int key, int mensaje)
{
    if(buscar(t_empleados,key+1,2)==1)
    {
        if(mensaje==1)
        {
            printf("\n Empleado eliminado");
        }

        t_empleados->disponible[key+1]=2;
        t_empleados->total_empleados--;
    }
    else
    {
        printf("\n El empleado no existe\n");
    }
}



/**
* Editar información de un empleado
* @param t_empleados     Tabla hash empleados
* @param empleados       elemento pair empleados
* @param employe         struct empleado
* @param t_departamentos Tabla hash departamentos
* @param rut             Rut del empleado (identificador)
*/
void editar_empleado(t_hash *t_empleados,pair empleados[caracteres],Empleado employe,t_hash *t_departamentos, char rut, int limpio)
{
    int newKey=h(limpio);

    if(buscar(t_empleados,newKey+1,2) == 1)
    {
        eliminar_empleados(t_empleados,newKey,2);
        agregar_empleado(t_empleados, empleados, employe, t_departamentos,2,limpio);
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
void buscar_empleado(t_hash *empleados, char *key, int rut_limpio)
{
    int newKey=h(rut_limpio);

    if(buscar(empleados, newKey+1,2) == 1)
    {
        do
        {
            newKey++;
        }
        while(empleados->t[newKey].value.rut.rut != rut_limpio);

        printf("\n Información Empleado\n");
        
        printf(" RUT: %i-%i \n Nombre:  %s %s %s %s \n Fecha Nacimiento: %i-%i-%i \n Contrato: %s \n Sueldo: %i \n Cargas: %i \n ", empleados->t[newKey].value.rut.rut,empleados->t[newKey].value.rut.verificador,empleados->t[newKey].value.primer_nombre,empleados->t[newKey].value.segundo_nombre,empleados->t[newKey].value.a_paterno,empleados->t[newKey].value.a_materno,empleados->t[newKey].value.dia,empleados->t[newKey].value.mes,empleados->t[newKey].value.year,empleados->t[newKey].value.contrato,empleados->t[newKey].value.salario,empleados->t[newKey].value.cargas);
        
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
        if(buscar(&t_departamentos,h(departamentos[i].key)+1,1) == 1)
        {
            printf(" - %s\n",t_departamentos.t[h(departamentos[i].key)+1].depto.nombreDepartamento);
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
    if(buscar(t_departamentos,key+1,1)==1)
    {
        printf("\n Departamento eliminado");
        t_departamentos->disponible[key+1]=2;
    }
    else
    {
        printf("\n El departamento no existe\n");
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
    char *nombre;
    int identificador;
    
    // Solicitmamos el nombre
    do
    {
        printf("\n Nombre Departamento: ");
        scanf("%s",&nombre);
        identificador=stringToInt(&nombre);
    }while(buscar(t_departamentos, h(identificador),1) != 0);
    
    
    // Guardamos el empleado en la tabla
    strcpy(depto.nombreDepartamento, &nombre);
    depto.identificadorDepartamento=identificador;
    
    
    // Esto no funciona
    // departamentos[t_departamentos->total_departamentos].key=identificador;
    // departamentos[t_departamentos->total_departamentos].depto=depto;
    // insertar(t_departamentos, *departamentos, 1);
    
    // Guardamos al empleado en el archivo txt
    FILE *archivo;
    archivo = fopen("Headers/Archivos/departamentos.txt", "a");
    fprintf(archivo, "%i,%s\n",identificador,&nombre);
    fclose(archivo);
    
    // Mensaje
    printf("\n Departamento Agregado");
}



/**
* Convertir un string a mayusculas (Funcion sacada de internet)
* @param string String a convertir
*/
void MinToMay(char string[])
{
    int i=0;
    int desp='a'-'A';
    for (i=0;string[i]!='\0';++i)
    {
        if(string[i]>='a'&&string[i]<='z')
        {
            string[i]=string[i]-desp;
        }
    }
}



/**
* Calcular el familiar segun las cargas del empleado
* @param  sueldo_mes sueldo total mes
* @param  cargas     cargas del empleado
* @return            retorna la cantidad del familiar 
*/
int calcular_familiar(int sueldo_mes,int cargas)
{
    int familiar;

    if(sueldo_mes<289608)
    {
        familiar=cargas*11337;
    }
    else if (sueldo_mes>289608 || sueldo_mes<423004)
    {
        familiar=cargas*6957;
    }
    else if(sueldo_mes>423004 || sueldo_mes<659743)
    {
        familiar=cargas*2199;
    }
    else
    {
        familiar=0;
    }

    return familiar;
}




/**
* Obtener liquidacion de sueldo empleado
* @param t_empleados Tabla hash empleados
* @param key         key del empleado h(rut)
* @param rut_limpio        rut sin digito verificador ni puntos
*/
void liquidacion(t_hash t_empleados, int key, int rut_limpio)
{
    int newKey=key;

    if(buscar(&t_empleados, newKey+1,2) == 1)
    {
        do
        {
            newKey++;
        }
        while(t_empleados.t[newKey].value.rut.rut != rut_limpio);
        char *contrato;
        // dias
        int dias_laborables,dias_mes;
        // sueldos
        int sueldo_hora,sueldo_mes,sueldo_liquido, sueldo_imponible;
        // descuentos
        int prevision,afp;
        // beneificios
        int gratificacion,pasajes=30000,familiar;
    
        // Información
        contrato=t_empleados.t[newKey].value.contrato;
        
        MinToMay(contrato);
        sueldo_hora=t_empleados.t[newKey].value.salario;
    
        // numeros de dias del mes
        time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char dias[3];
        strftime(dias,3,"%d",tlocal);
        dias_mes=atoi(dias);
    
        // dias laborables (lunes-viernes)
        switch (dias_mes)
        {
            case 31:
                dias_laborables=23;
                break;
            case 30:
                dias_laborables=21;
                break;
            case 28:
                dias_laborables=20;
        }
    
        if(strcmp(contrato, "FIJO") == 0 || strcmp(contrato, "INDEFINIDO") == 0)
        {
            // sueldo mes
            sueldo_mes=(sueldo_hora*8)*dias_laborables;
            // familiar
            familiar=calcular_familiar(sueldo_mes,t_empleados.t[newKey].value.cargas);
            // beneficios
            gratificacion=sueldo_mes*0.25;
            // final
            sueldo_imponible=sueldo_mes+gratificacion+pasajes;
            // descuentos
            prevision=sueldo_imponible*0.07;
            afp=sueldo_imponible*0.1;

            sueldo_liquido=sueldo_imponible-prevision-afp+familiar;
            
            printf("\n HABERES: \n Liquidacion Empleado: \n Sueldo Base: %i \n Gratificacion Legal: %i \n Pasajes: 30.000 \n Familiar: %i \n\n DESCUENTOS: \n AFP: %i \n Prevision: %i \n\n SUELDO LIQUIDO: %i",sueldo_mes,gratificacion,familiar,afp,prevision,sueldo_liquido);
        }
        else if (strcmp(contrato, "DIA") == 0)
        {
            // sueldo mes
            sueldo_mes=(sueldo_hora*8);
            
            printf("\n HABERES: \n Liquidacion Empleado: \n Sueldo Base: %i ",sueldo_mes);
        }
        else if(strcmp(contrato, "FAENA") == 0)
        {
            int dias_trabajo;
            printf("\n Cantidad de dias:");
            scanf("%d",&dias_trabajo);
            
            // sueldo mes
            sueldo_mes=(sueldo_hora*8)*dias_trabajo;
            // familiar
            familiar=calcular_familiar(sueldo_mes,t_empleados.t[newKey].value.cargas);
            // beneficios
            gratificacion=sueldo_mes*0.25;
            // final
            sueldo_imponible=sueldo_mes+gratificacion+pasajes;
            // descuentos
            prevision=sueldo_imponible*0.07;
            afp=sueldo_imponible*0.1;
            
            sueldo_liquido=sueldo_imponible-prevision-afp+familiar;
            
            printf("\n HABERES: \n Liquidacion Empleado: \n Sueldo Base: %i \n Gratificacion Legal: %i \n Pasajes: 30.000 \n Familiar: %i \n\n DESCUENTOS: \n AFP: %i \n Prevision: %i \n\n SUELDO LIQUIDO: %i",sueldo_mes,gratificacion,familiar,afp,prevision,sueldo_liquido);
        }
        else if(strcmp(contrato, "HONORARIOS") == 0)
        {
            int horas_trabajo;
            printf("\n Cantidad de horas:");
            scanf("%d",&horas_trabajo);

            // sueldo mes
            sueldo_mes=(sueldo_hora*8);
            
            printf("\n HABERES: \n Liquidacion Empleado: \n Sueldo: %i ",sueldo_mes);
        }
    }
    else
    {
        printf("\n Empleado no existe\n");
    }
}



/**
* Respaldar los empleados en el archivo txt
* @param t_empleados Tabla hash empleados
* @param empleados   elemento pair empleados
*/
void respaldar_empleados(t_hash t_empleados, pair empleados[caracteres])
{
    int i;
    // abrimos el archivo para sobre-escritura
    FILE *archivo;
    archivo = fopen("Headers/Archivos/empleados.txt", "w");
    
    for (i=0; i<t_empleados.total_empleados-1; i++)
    {
        if(buscar(&t_empleados,h(empleados[i].key)+1,2) == 1)
        {
            fprintf(archivo, "%i,%d,%s,%s,%s,%s,%i,%i,%d,%s,%i,%i\n",
            t_empleados.t[h(empleados[i].key)+1].value.rut.rut,
            t_empleados.t[h(empleados[i].key)+1].value.rut.verificador,
            t_empleados.t[h(empleados[i].key)+1].value.primer_nombre,
            t_empleados.t[h(empleados[i].key)+1].value.segundo_nombre,
            t_empleados.t[h(empleados[i].key)+1].value.a_paterno,
            t_empleados.t[h(empleados[i].key)+1].value.a_materno,
            t_empleados.t[h(empleados[i].key)+1].value.dia,
            t_empleados.t[h(empleados[i].key)+1].value.mes,
            t_empleados.t[h(empleados[i].key)+1].value.year,
            t_empleados.t[h(empleados[i].key)+1].value.contrato,
            t_empleados.t[h(empleados[i].key)+1].value.salario,
            t_empleados.t[h(empleados[i].key)+1].value.cargas);
        }
    }

    // cerramos el archivo
    fclose(archivo);
}



/**
* Respaldar los empleados en el archivo txt
* @param t_departamentos Tabla hash departamentos
* @param departamentos   elemento pair departamentos
*/
void respaldar_departamentos(t_hash t_departamentos, pair departamentos[caracteres])
{
    int i;
    // abrimos el archivo para sobre-escritura
    FILE *archivo;
    archivo = fopen("Headers/Archivos/departamentos.txt", "w");

    for (i=0; i<t_departamentos.total_departamentos-1; i++)
    {
        if(buscar(&t_departamentos,h(departamentos[i].key)+1,1) == 1)
        {
            fprintf(archivo, "%i,%s",
            t_departamentos.t[h(departamentos[i].key)+1].depto.identificadorDepartamento,
            t_departamentos.t[h(departamentos[i].key)+1].depto.nombreDepartamento);
        }
    }

    // cerramos el archivo
    fclose(archivo);
}
