/* 5147233 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cadena.h"

struct _rep_cadena
{
    TInfo elem;
    _rep_cadena *sig;
};

TCadena crearCadena()
{
    TCadena cadNueva = NULL;
    return cadNueva;
}

void liberarCadena(TCadena cad)
{
    if (cad != NULL)
    {
        TCadena l = cad->sig;
        while (l != cad)
        {
            TCadena borrar = l;
            l = l->sig;
            cad->sig = l;
            liberarInfo(borrar->elem);
            delete (borrar);
        }
        liberarInfo(l->elem);
        delete (l);
    }
}

nat cantidadEnCadena(TCadena cad)
{
    nat cont = 0;
    if (cad != NULL)
    {
        cont++;
        TCadena l = cad->sig;
        while (l != cad)
        {
            cont++;
            l = l->sig;
        }
    }
    return cont;
}

bool estaEnCadena(nat natural, TCadena cad)
{
    if (cad != NULL)
    {
        TCadena l = cad->sig;
        if (natInfo(cad->elem) == natural)
        {
            return true;
        }
        else
        {
            while (l != cad && natInfo(l->elem) != natural)
                l = l->sig;
            // Salgo si volvi al último elemento(no estaba natural en la lista)
            //ó encontré al elem (salí antes)
            // Qué pasa si el natural está en el último? Entré al if.
            return l != cad;
        }
    }
    else
        return false;
}

TCadena insertarAlInicio(nat natural, double real, TCadena cad)
{
    TCadena l = new (_rep_cadena);
    l->elem = crearInfo(natural, real);
    if (cad != NULL)
    {
        l->sig = cad->sig;
        cad->sig = l;
    }
    else
    {
        l->sig = l;
        cad = l;
    }
    return cad;
}

TInfo infoCadena(nat natural, TCadena cad)
{
    cad = cad->sig;
    while (natInfo(cad->elem) != natural)
        cad = cad->sig;
    return cad->elem;
}

//------

TInfo primeroEnCadena(TCadena cad)
{
    // TCadena l = cad->sig;
    // return l->elem;
    return cad->sig->elem;
}

TCadena cadenaSiguiente(TCadena cad)
{
    if (cad != NULL)
    {
        TCadena l = cad->sig;
        return l;
    }
    else
    {
        return cad;
    }
}

TCadena removerDeCadena(nat natural, TCadena cad)
{
    TCadena l = cad->sig;
    TCadena conector = cad;
    // if (cantidadEnCadena(cad) != 1){
    if (cad->sig != cad)
    {
        while (natInfo(l->elem) != natural)
        {
            l = l->sig;
            conector = conector->sig;
        } // Salgo apuntando al que quiero borrar
        TCadena borrar = l;

        if (l != cad)
        {
            l = l->sig;
            liberarInfo(borrar->elem);
            delete (borrar);
            conector->sig = l;

            return cad;
        }
        else
        {
            conector->sig = l->sig;
            liberarInfo(borrar->elem);
            delete (borrar);
            cad = conector;
            return cad;
        }
    }
    else
    {
        liberarInfo(cad->elem);
        delete (cad);
        cad = NULL;
        return cad;
    }
}

void imprimirCadena(TCadena cad)
{
    if (cad != NULL)
    {
        TCadena l = cad->sig;
        int cantidad = cantidadEnCadena(cad);
        for (int i = 0; i < cantidad; i++)
        {
            // printf("(%d,%.2f)", natInfo(l->elem), realInfo(l->elem));
            imprimirInfo(l->elem);
            l = l->sig;
        }
    }
    printf("\n");
}

TCadena insertarAlFinal(nat natural, double real, TCadena cad)
{
    // TCadena nuevo = new _rep_cadena;
    // // natInfo(nuevo->elem) = natural;
    // // realInfo(nuevo->elem) = real;
    // nuevo->elem = crearInfo(natural, real);
    // if(cad!=NULL){
    //     nuevo->sig = cad->sig;
    //     cad->sig = nuevo;
    //     cad = cad->sig;
    // //Por ahora devuelvo el primer elem
    // } else {
    //     nuevo->sig=nuevo;
    //     cad = nuevo;
    // }

    // return cad;

    cad = insertarAlInicio(natural, real, cad);
    return cadenaSiguiente(cad);
}

TCadena removerPrimero(TCadena cad)
{
    // TCadena borrar = cad->sig;
    // cad->sig = borrar->sig;
    // liberarInfo(borrar->elem);
    // delete(borrar);
    // cad=cad->sig;
    // return cad;

    cad = removerDeCadena(natInfo(primeroEnCadena(cad)), cad);

    return cad;
}

TCadena copiaCadena(TCadena cad)
{
    TCadena ult = NULL;

    for (nat i = 0; i < cantidadEnCadena(cad); i++)
    {
        ult = insertarAlFinal(natInfo(primeroEnCadena(cad)), realInfo(primeroEnCadena(cad)), ult);
        cad = cadenaSiguiente(cad);
    }
    return ult;
}