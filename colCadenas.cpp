/* 5147233 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colCadenas.h"
#include "../include/cadena.h"

struct _rep_colCadenas
{
  nat tam;
  TCadena *colCad;
};

TColCadenas crearColCadenas(nat tamanio)
{
  TColCadenas colCadsNueva = new _rep_colCadenas;
  colCadsNueva->tam = tamanio;
  colCadsNueva->colCad = new TCadena[tamanio];

  for (nat i = 0; i < (tamanio); i++)
  {
    colCadsNueva->colCad[i] = crearCadena();
  }
  return colCadsNueva;
}

void liberarColCadenas(TColCadenas col)
{
  for (nat i = 0; i < col->tam; i++)
  {
    liberarCadena(col->colCad[i]);
  }
  delete[] col->colCad;
  delete (col);
}

nat tamanioColCadenas(TColCadenas col)
{
  return col->tam;
}

TCadena cadenaDeColCadenas(nat pos, TColCadenas col)
{
  return col->colCad[pos];
}

nat cantidadColCadenas(nat pos, TColCadenas col)
{
  nat numElems = cantidadEnCadena(col->colCad[pos]);
  return numElems;
}

bool estaEnColCadenas(nat natural, nat pos, TColCadenas col)
{
  bool aux = estaEnCadena(natural, col->colCad[pos]);
  return aux;
}

TColCadenas insertarEnColCadenas(nat natural, double real, nat pos,
                                 TColCadenas col)
{
  col->colCad[pos] = insertarAlInicio(natural, real, col->colCad[pos]);
  return col;
}

TInfo infoEnColCadenas(nat natural, nat pos, TColCadenas col)
{
  // Tengo que buscar dentro de la colección,
  // dentro de la posición pos el primer elemento del tipo TInfo
  // Cuya parte natural es natural.
  //  natInfo((*col).colCad[pos]), (*col).colCad[pos] es una cadena
  // dentro de la cadena tengo que acceder a los TInfo

  // infoCadena hace literalmente eso.

  return infoCadena(natural, (*col).colCad[pos]);
}

TColCadenas removerDeColCadenas(nat natural, nat pos, TColCadenas col)
{
  col->colCad[pos] = removerDeCadena(natural, (*col).colCad[pos]);

  return col;
}