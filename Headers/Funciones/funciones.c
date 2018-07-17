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
