/* 5147233 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cola.h"

struct nodoLista
{
    TInfo elem;
    nodoLista *sig;
};
typedef nodoLista *cad;

struct _rep_cola
{
    nat encola;
    nodoLista *prim;
    nodoLista *ult;
};

TCola crearCola()
{
    TCola nueva = new _rep_cola;
    nueva->prim = nueva->ult = NULL;
    nueva->encola = 0;
    return nueva;
}

void liberarCola(TCola c)
{
    while (c->encola > 0)
        c = desencolar(c);
    delete (c);
}

nat cantidadEnCola(TCola c)
{
    return c->encola;
}

TCola encolar(TInfo info, TCola c)
{
    cad nuevo = new nodoLista;
    nuevo->elem = copiaInfo(info);
    c->encola = c->encola + 1;
    if (c->prim == NULL)
    {
        c->prim = nuevo;
    }
    else
    {
        c->ult->sig = nuevo;
    }
    c->ult = nuevo;
    nuevo->sig = NULL;
    return c;
}

TInfo frente(TCola c)
{
    return c->prim->elem;
}

TCola desencolar(TCola c)
{
    cad borrar = c->prim;
    c->prim = c->prim->sig;
    if (c->encola == 1)
    {
        c->ult = NULL;
    }
    c->encola = c->encola - 1;
    liberarInfo(borrar->elem);
    delete (borrar);
    return c;
}