/* 5147233 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/mapping.h"
#include "../include/cadena.h"

struct _rep_mapping {
    TCadena *tabla;
    int tam;
    int tope;
    
    //tam será la cantidad de buckets
    //tope será la cantidad de buckets usados
};
//En mi representación ordenaré según el módulo de la 
//parte natural con respecto a M

TMapping crearMap(nat M){
    TMapping map = new _rep_mapping;
    map->tam = M;
    map->tope = 0;
    map->tabla = new TCadena[M];
    for (nat i=0; i<M; i++)
    {
        map->tabla[i] = crearCadena();
    }
    return map;
}

void liberarMap(TMapping map) {
    for(int i=0; i<map->tam; i++){
        liberarCadena(map->tabla[i]);
        map->tope = map->tope-1;
    }
    delete[] map->tabla;
    delete(map);
}

TMapping asociarEnMap(nat clave, double valor, TMapping map) {
    int pos = clave % map->tam;
    
    map->tabla[pos] = insertarAlInicio(clave, valor, map->tabla[pos]);
    map->tope = map->tope+1;

    return map; 
}

TMapping desasociarEnMap(nat clave, TMapping map) { 
    //prec: esClaveEnMap
    int pos = clave % map->tam;

    map->tabla[pos] = removerPrimero(map->tabla[pos]);
    map->tope = map->tope-1;
    
    return map;
}

bool esClaveEnMap(nat clave, TMapping map) { 
    int pos = clave % map->tam;

    return estaEnCadena(clave, map->tabla[pos]); 
}

double valorEnMap(nat clave, TMapping map) { 
    int pos = clave % map->tam;

    return realInfo(infoCadena(clave, map->tabla[pos])); 
}

bool estaLlenoMap(TMapping map) { 
    return map->tam == map->tope; 
}


