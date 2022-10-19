/* 5147233 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/pila.h"

struct nodoLista
{
    TInfo elem;
    nodoLista *sig;
};
typedef nodoLista *cad;

struct _rep_pila
{
    nat apilados;
    nodoLista *cabeza;
};

TPila crearPila()
{
    TPila nuevo = new _rep_pila;
    nuevo->cabeza = NULL;
    nuevo->apilados = 0;
    return nuevo;
}

void liberarPila(TPila p)
{
    while (p->apilados > 0)
        p = desapilar(p);
    delete (p);
}

nat cantidadEnPila(TPila p)
{
    return p->apilados;
}

TPila apilar(TInfo info, TPila p)
{
    cad nuevo = new nodoLista;
    nuevo->elem = copiaInfo(info);
    if (p->apilados == 0)
    {
        nuevo->sig = NULL;
    }
    else
    {
        nuevo->sig = p->cabeza;
    }
    p->cabeza = nuevo;
    p->apilados = p->apilados + 1;
    return p;
}

TInfo cima(TPila p)
{
    return p->cabeza->elem;
}

TPila desapilar(TPila p)
{
    cad borrar = p->cabeza;
    p->cabeza = p->cabeza->sig;
    liberarInfo(borrar->elem);
    delete (borrar);
    p->apilados = p->apilados - 1;
    return p;
}