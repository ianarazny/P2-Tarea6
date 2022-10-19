/* 5147233 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/mapping.h" 
#include <string.h>
#include <math.h>

int max(int a, int b)
{
  if (a > b){
    return a;
  }else{
    return b;
  }
}

  int prof(TAbb abb)
  {
    if (esVacioAbb(abb)){
      return 0;
    }
    else
      return 1 + max(prof(izquierdo(abb)), prof(derecho(abb)));
  }


bool esAvlAux(int &h, TAbb abb){
  if(esVacioAbb(abb)){
    return true;
  } else {
  h=0;
  int hizq=h;
  bool esAvlIzq = esAvlAux(hizq, izquierdo(abb));
  // if(!esAvlIzq)
  //   return false;

  int hder=h; 
  bool esAvlDer = esAvlAux(hder, derecho(abb));
  // if(!esAvlDer)
  //   return false;

  bool res = esAvlIzq && esAvlDer;

  //int dif = abs(hizq - hder);

  h = max(hder, hizq) + 1;
  
  if(abs(hizq - hder) >1 ){
    return false;
  } else
    return res;
  }
}

bool esAvl(TAbb abb) { 

  // if(esVacioAbb(abb)){
  //   return true;
  // } else {
  // bool res;
  // res = (esAvl(izquierdo(abb)) && esAvl(derecho(abb)));
  // int dif = abs(prof(izquierdo(abb))-prof(derecho(abb)));
  // return dif < 2 && res;
  // }
  int h=0;
  bool res = esAvlAux(h, abb);
  return res;
}

TAbb avlMinAux(nat h, nat &dato)
{
  if (h == 0){
    return NULL;
  } else {
    TAbb abb;
    TAbb izq = avlMinAux(h - 1, dato);
    TInfo info = crearInfo(dato, 0);
    dato = dato + 1;
    if (h == 1)
      abb = consAbb(info, NULL, NULL);
    else{
    TAbb der = avlMinAux(h - 2, dato);
    abb = consAbb(info, izq, der);
    }
    return abb;
  }
}

TAbb avlMin(nat h) { 
  nat dato = 1;
  TAbb res = crearAbb();
  res = avlMinAux(h, dato);
  return res; 
}

TCadena filtradaOrdenada(TCadena cad, TIterador it){
  TCadena res = crearCadena();

  if(cad!=NULL){
  int cantCad = cantidadEnCadena(cad);
  TMapping map = crearMap(cantCad);
  while(cantCad > 0){
  if(esClaveEnMap(natInfo(primeroEnCadena(cad)),map)){
    double valAct= valorEnMap(natInfo(primeroEnCadena(cad)),map);
    map = desasociarEnMap(natInfo(primeroEnCadena(cad)),map);
    map = asociarEnMap(natInfo(primeroEnCadena(cad)),valAct+realInfo(primeroEnCadena(cad)),map);
  
  }else{
    map = asociarEnMap(natInfo(primeroEnCadena(cad)),realInfo(primeroEnCadena(cad)),map);
  }
  cad = cadenaSiguiente(cad);
  cantCad = cantCad -1;
  } 
  //Salgo con el map cargado tal y como quiero.
  reiniciarIterador(it);
  while(estaDefinidaActual(it)){
    if(esClaveEnMap(actualEnIterador(it),map)){
      res = insertarAlFinal(actualEnIterador(it), valorEnMap(actualEnIterador(it), map), res);
    }
  avanzarIterador(it);
  }
  liberarMap(map);
  }
  return res;
}


  bool estaOrdenada(TCadena cad)
  {
    nat cantEnCad = cantidadEnCadena(cad);
    if (cantEnCad <= 1)
    {
      return true;
    }
    else
    {
      bool verif = true;
      while (cantEnCad > 1 && verif)
      {
        nat primero = natInfo(primeroEnCadena(cad));
        nat segundo = natInfo(primeroEnCadena(cadenaSiguiente(cad)));
        verif = primero < segundo;
        cad = cadenaSiguiente(cad);
        cantEnCad--;
      }
      return verif;
    }
  }

  TCadena mezclaCadenas(TCadena cad1, TCadena cad2)
  {
    TCadena res = crearCadena();

    nat largo1 = cantidadEnCadena(cad1);
    nat largo2 = cantidadEnCadena(cad2);

    while (largo1 > 0 && largo2 > 0)
    {
      if (natInfo(primeroEnCadena(cad1)) <= natInfo(primeroEnCadena(cad2)))
      {
        res = insertarAlFinal(natInfo(primeroEnCadena(cad1)), realInfo(primeroEnCadena(cad1)), res);
        if (natInfo(primeroEnCadena(cad1)) == natInfo(primeroEnCadena(cad2)))
        {
          largo2 = largo2 - 1;
          cad2 = cadenaSiguiente(cad2);
        }
        cad1 = cadenaSiguiente(cad1);
        largo1 = largo1 - 1;
      }
      else
      {
        res = insertarAlFinal(natInfo(primeroEnCadena(cad2)), realInfo(primeroEnCadena(cad2)), res);
        cad2 = cadenaSiguiente(cad2);
        largo2 = largo2 - 1;
      }
    }
    while (largo1 > 0)
    {
      res = insertarAlFinal(natInfo(primeroEnCadena(cad1)), realInfo(primeroEnCadena(cad1)), res);
      largo1 = largo1 - 1;
      cad1 = cadenaSiguiente(cad1);
    }
    while (largo2 > 0)
    {
      res = insertarAlFinal(natInfo(primeroEnCadena(cad2)), realInfo(primeroEnCadena(cad2)), res);
      largo2 = largo2 - 1;
      cad2 = cadenaSiguiente(cad2);
    }

    return res;
  }

  TAbb balancear(TAbb b, TInfo * arr, int ppo, int fin)
  {
    // Caso base: ppo >= fin; no hago nada en ese caso.
    TAbb res;
    if (ppo > fin)
    {
      return res = NULL;
    }
    else
    {
      int mitad = (ppo + fin) / 2;
      TInfo raiz = copiaInfo(arr[mitad]);
      res = consAbb(raiz, balancear(b, arr, ppo, mitad - 1), balancear(b, arr, mitad + 1, fin));

      return res;
    }
  }

  TAbb crearBalanceado(TInfo * arreglo, nat n)
  {
    TAbb b = crearAbb();
    b = balancear(b, arreglo, 0, n - 1);

    return b;
  }

  TAbb unionAbbs(TAbb abb1, TAbb abb2)
  {
    TCadena cad1 = linealizacion(abb1);

    TCadena cad2 = linealizacion(abb2);

    TCadena mezclados = mezclaCadenas(cad1, cad2);

    nat cantEnTotal = cantidadEnCadena(mezclados);

    TInfo *arr = new TInfo[cantEnTotal];

    for (nat i = 0; i < cantEnTotal; i++)
    {
      arr[i] = copiaInfo(primeroEnCadena(mezclados));
      mezclados = cadenaSiguiente(mezclados);
    }

    TAbb res = crearBalanceado(arr, cantEnTotal);

    liberarCadena(cad1);
    liberarCadena(cad2);
    liberarCadena(mezclados);
    for (nat j = 0; j < cantEnTotal; j++)
    {
      liberarInfo(arr[j]);
    }
    delete[] arr;

    return res;
  }

  TCola ordenadaPorModulo(nat p, TCadena cad)
  {
    TCola cola = crearCola();
    nat cantEnCad = cantidadEnCadena(cad);

    for (nat i = 0; i < p; i = i + 1)
    {
      nat j = 0;
      while (j < cantEnCad)
      {
        if (natInfo(primeroEnCadena(cad)) % p == i)
        {
          cola = encolar(primeroEnCadena(cad), cola);
        }
        cad = cadenaSiguiente(cad);
        j = j + 1;
      }
    }
    return cola;
  }

  TPila menoresQueElResto(TCadena cad, nat cantidad)
  {
    TPila pila = crearPila();
    if (cantidad > 0)
    {
      pila = apilar(primeroEnCadena(cad), pila);
      cad = cadenaSiguiente(cad);
      cantidad = cantidad - 1;

      while (cantidad > 0)
      {
        if (natInfo(primeroEnCadena(cad)) > natInfo(cima(pila)))
        {
          pila = apilar(primeroEnCadena(cad), pila);
        }
        else
        {
          while (cantidadEnPila(pila) > 0 && natInfo(primeroEnCadena(cad)) <= natInfo(cima(pila)))
            pila = desapilar(pila);
          pila = apilar(primeroEnCadena(cad), pila);
        }
        cad = cadenaSiguiente(cad);
        cantidad = cantidad - 1;
      }
    }
    return pila;
  }

  //

  void cargarCadena(TAbb abb, TCadena & cad)
  {
    if (!esVacioAbb(abb))
    {

      if (!esVacioAbb(derecho(abb)))
      {
        cargarCadena(derecho(abb), cad);
      }
      cad = insertarAlInicio(natInfo(raiz(abb)), realInfo(raiz(abb)), cad);
      if (!esVacioAbb(izquierdo(abb)))
      {
        cargarCadena(izquierdo(abb), cad);
      }
    }
  }

  TCadena linealizacion(TAbb abb)
  {
    TCadena lista = crearCadena();
    cargarCadena(abb, lista);
    return lista;
  }

  void imprimirNodoYGuion(TAbb abb, int cont)
  {
    if (!esVacioAbb(abb))
    {

      int altura = cont;
      cont++;
      if (!esVacioAbb(derecho(abb)))
      {
        imprimirNodoYGuion(derecho(abb), cont);
      }
      // lo hago con una auxiliar para que cont no quede indefinida
      for (int i = 0; i < altura; i++)
        printf("-");

      imprimirInfo(raiz(abb));
      printf("\n");

      if (!esVacioAbb(izquierdo(abb)))
      {
        imprimirNodoYGuion(izquierdo(abb), cont);
      }
    }
  }
  void imprimirAbb(TAbb abb)
  {
    // Imprimo de derecha a izquierda.
    // Tal vez debo contar la cantidad de elementos para así
    // Imprimir esa cantidad de guiones antes.
    if (!esVacioAbb(abb))
    {
      int cant = 0;
      imprimirNodoYGuion(abb, cant);
      // printf("\n");
    }
  }

  int numNodos(TAbb b)
  {
    if (esVacioAbb(b))
    {
      return 0;
    }
    else
    {
      return 1 + numNodos(derecho(b)) + numNodos(izquierdo(b));
    }
  }

  bool esPerfecto(TAbb abb)
  {
    return numNodos(abb) == pow(2, prof(abb)) - 1;
  }

  TAbb menores(double limite, TAbb abb)
  {
    TAbb res;
    if (esVacioAbb(abb))
    {
      return res = NULL;
    }
    else
    {
      TAbb izq = menores(limite, izquierdo(abb));
      TAbb der = menores(limite, derecho(abb));

      if (realInfo(raiz(abb)) < limite)
      {
        TInfo root = copiaInfo(raiz(abb));
        res = consAbb(root, izq, der);
      }
      else if (esVacioAbb(der))
      {
        res = izq;
      }
      else if (esVacioAbb(izq))
      {
        res = der;
      }
      else
      {
        TInfo mayor = copiaInfo(mayorEnAbb(izq));
        res = consAbb(mayor, izq, der);
        res = removerDeAbb(natInfo(mayor), res);
      }
    }
    return res;
  }

  void cantIterAux(TIterador iter, nat & contador)
  {
    if (estaDefinidaActual(iter))
    {
      contador++;
      avanzarIterador(iter);
      cantIterAux(iter, contador);
    }
  }
  nat cantIter(TIterador iter)
  {
    nat contador = 0;
    reiniciarIterador(iter);
    cantIterAux(iter, contador);
    return contador;
  }

  void caminoAscAux(nat clave, nat k, TAbb abb, TIterador & iter)
  {
    if (!esVacioAbb(abb))
    {
      if (clave < natInfo(raiz(abb)))
      {
        caminoAscAux(clave, k, izquierdo(abb), iter);

        if (cantIter(iter) < k)
        {

          agregarAIterador(natInfo(raiz(abb)), iter);
        }
      }
      else if (clave > natInfo(raiz(abb)))
      {
        caminoAscAux(clave, k, derecho(abb), iter);

        if (cantIter(iter) < k)
        {

          agregarAIterador(natInfo(raiz(abb)), iter);
        }
      }
      else
      {
        if (k > 0)
        {
          agregarAIterador(natInfo(raiz(abb)), iter);
        }
      }
    }
  }
  TIterador caminoAscendente(nat clave, nat k, TAbb abb)
  {
    TIterador iter = crearIterador();
    // Primero busco la clave
    // No tengo por qué chequear si es vacio desde el vamos pues prec: está la clave
    // nat rec=0;
    if (!esVacioAbb(abb) && k > 0)
    {
      caminoAscAux(clave, k, abb, iter);
    }
    return iter;
  }

  void impPalCortasAux(ArregloChars prefijo, nat largoAct, TPalabras palabras, nat lim)
  {
    // Así imprimiré todas las letras.
    // Para imprimir las de largo menor a limite chequeo que
    // el arreglo que vengo imprimiendo no tenga mas caracteres que lim

    if ((letra(palabras) == '\0'))
    {
      prefijo[largoAct] = '\0';
      printf("%s\n", prefijo);
    }
    else
    {
      if (largoAct < lim)
      {
        prefijo[largoAct] = letra(palabras);
        impPalCortasAux(prefijo, largoAct + 1, subarboles(palabras), lim);
      }
    }
    if (siguientes(palabras) != NULL)
      impPalCortasAux(prefijo, largoAct, siguientes(palabras), lim);
  }

  void imprimirPalabrasCortas(nat k, TPalabras palabras)
  {
    ArregloChars arrChars = new char[k + 1];

    impPalCortasAux(arrChars, 0, subarboles(palabras), k);

    delete[] arrChars;
  }

  void bfpaux(int largoPref, int numRecur, ArregloChars pref, TPalabras pal, TPalabras &aux)
  {
    aux = pal;
    if (letra(pal) == pref[numRecur])
    {
      if (largoPref != numRecur)
      {
        // Es porque coincidí con la letra y todavía no estoy en la última
        // posicion del pref
        bfpaux(largoPref, numRecur + 1, pref, subarboles(pal), aux);
      }
      else
      {
        // Estoy en el caso en el que coincida la letras hasta la ultima
        aux = pal;
      }
    }
    else
    {
      // Si mi letra no está en el prefijo
      // Debo seguir buscando en el resto del arbol
      // Llamo la func si: el hijo no es \0 ó siguiente es null
      if (siguientes(pal) != NULL)
      {
        bfpaux(largoPref, numRecur, pref, siguientes(pal), aux);
      }
      //  else if(siguientes(pal)!=NULL && subarboles(pal)=="\0"){}
      else
      {
        // No encontré, no está
        aux = NULL;
      }
    }
  }

  TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras)
  {
    int largoPref = strlen(prefijo) - 1;
    // Porque arranca en 0

    // palabras=subarboles(palabras);
    TPalabras aux = NULL;

    bfpaux(largoPref, 0, prefijo, subarboles(palabras), aux);

    return aux;
  }

  void reversoRec(TIterador iter, TIterador copiado)
  {
    // Yo quiero avanzar iterador si no es el último elemento

    if (estaDefinidaActual(iter))
    {
      // Creo que las sig. dos lineas sobran.
      // reiniciarIterador(iter);
      // avanzarIterador(iter);

      if (!estaDefinidaActual(iter))
      {
        // Si toy aca es porque estaba en el ultimo elem de iter
        // reiniciarIterador(iter);
        // agregarAIterador(actualEnIterador(iter),copiado);
        // avanzarIterador(iter);
      }
      else
      {
        nat aux = actualEnIterador(iter);
        avanzarIterador(iter);
        reversoRec(iter, copiado);
        agregarAIterador(aux, copiado);
      }
    }
  }

  TIterador reversoDeIterador(TIterador iter)
  {

    TIterador nuevo = crearIterador();
    reiniciarIterador(iter);
    if (estaDefinidaActual(iter))
    {
      reversoRec(iter, nuevo);
    }
    return nuevo;
  }