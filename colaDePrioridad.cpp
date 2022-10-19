/* 5147233 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colaDePrioridad.h"
#include "../include/info.h"

// struct infos{
//   int nat;
//   double real;
// };

struct _rep_colaDePrioridad{
  TInfo *heap;
  nat *arrPos;
  int tope;
  nat maximo;
  bool invertido;
};

TColaDePrioridad crearCP(nat N){ 
  TColaDePrioridad cola = new _rep_colaDePrioridad;
  cola->heap = new TInfo[N+1];
  cola->arrPos = new nat[N+1];
  for(nat i=1; i<N+1; i++){
    //cola->heap[i] = NULL;
    cola->arrPos[i] = 0;
  }
  //N+1 pues el espacio 0 no lo utilizo
  cola->tope = 0;
  cola->maximo = N;
  cola->invertido = false;

  return cola; 
}

void filtradoAscendente(TColaDePrioridad &cp, nat pos){
  if(!cp->invertido){
    TInfo cambio = cp->heap[pos];
    while(pos != 1 && realInfo(cp->heap[pos/2]) > realInfo(cambio)){
      cp->heap[pos] = cp->heap[pos/2];
      //Actualizar la posición
      cp->arrPos[natInfo(cp->heap[pos/2])] = pos;
      pos = pos/2;
    }
    cp->heap[pos] = cambio;
    cp->arrPos[natInfo(cambio)] = pos;
  }else{
    TInfo cambio = cp->heap[pos];
    while(pos != 1 && realInfo(cp->heap[pos/2]) < realInfo(cambio)){
      cp->heap[pos] = cp->heap[pos/2];
      //Actualizar la posición
      cp->arrPos[natInfo(cp->heap[pos/2])] = pos;
      pos = pos/2;
    }
    cp->heap[pos] = cambio;
    cp->arrPos[natInfo(cambio)] = pos;
  }
}

void filtradoDescendente(TColaDePrioridad &cp, int pos){
  if(2*pos <= cp->tope){
  if(!cp->invertido){
      int hijo = pos*2;
      if((hijo+1<=cp->tope) && (realInfo(cp->heap[hijo+1])<realInfo(cp->heap[hijo]))){
        hijo=hijo+1;
      }
      if(realInfo(cp->heap[pos]) > realInfo(cp->heap[hijo])){
        TInfo cambio = cp->heap[pos];
        cp->heap[pos] = cp->heap[hijo];
  
        cp->heap[hijo] = cambio;
        
        cp->arrPos[natInfo(cp->heap[pos])] = pos;
        cp->arrPos[natInfo(cp->heap[hijo])] = hijo;
        
        pos = hijo;
        filtradoDescendente(cp, pos);
      }
  } else {
      int hijo = pos*2;
      if((hijo+1<=cp->tope) && (realInfo(cp->heap[hijo+1])>realInfo(cp->heap[hijo]))){
        hijo=hijo+1;
      }
      if(realInfo(cp->heap[pos]) < realInfo(cp->heap[hijo])){
        TInfo cambio = cp->heap[pos];
        cp->heap[pos] = cp->heap[hijo];
  
        cp->heap[hijo] = cambio;
        
        cp->arrPos[natInfo(cp->heap[pos])] = pos;
        cp->arrPos[natInfo(cp->heap[hijo])] = hijo;
        
        pos = hijo;
        filtradoDescendente(cp, pos);
      }
  }
  }
}

TColaDePrioridad invertirPrioridad(TColaDePrioridad cp){ 
  if(!cp->invertido)
    cp->invertido = true;
  else
    cp->invertido = false;
  if(cp->tope>1){
    for(int i= cp->tope/2; i>=1; i--)
      filtradoDescendente(cp, i);
  }
  return cp;
}
  
void liberarCP(TColaDePrioridad cp){
  for(nat i=1; i<cp->maximo+1; i++){
    if(cp->arrPos[i]!=0){    
      liberarInfo(cp->heap[cp->arrPos[i]]);
    }
  }
  delete[] cp->arrPos;
  delete[] cp->heap;
  delete cp;
}


TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  if(elem <= cp->maximo && elem >= 1){
    if(cp->arrPos[elem]==0){
      //Sospecho tengo problema cuando quiero sustituir un valor   
      int maximo = cp->maximo;
      if(maximo > cp->tope){
        cp->tope = cp->tope+1;
        TInfo nuevo = crearInfo(elem, valor);
        cp->heap[cp->tope] = nuevo;
        cp->arrPos[elem] = cp->tope;
       // imprimirInfo(cp->heap[cp->arrPos[elem]]);
       // printf("\n");
      filtradoAscendente(cp, cp->tope);
      }
    } else {
      double valAnt = realInfo(cp->heap[cp->arrPos[elem]]); 
      liberarInfo(cp->heap[cp->arrPos[elem]]);
      TInfo nuevo = crearInfo(elem, valor);
      cp->heap[cp->arrPos[elem]] = nuevo;

      if(valor > valAnt)
        filtradoDescendente(cp, cp->arrPos[elem]);
      else if(valor < valAnt)
        filtradoAscendente(cp, cp->arrPos[elem]);
    }
  }
  return cp;
}

bool estaVaciaCP(TColaDePrioridad cp){ 
  return cp->tope==0; 
}

nat prioritario(TColaDePrioridad cp){ 
  return natInfo(cp->heap[1]); 
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp)  { 
  if(cp->tope > 0){

    cp->arrPos[natInfo(cp->heap[1])]=0;
    liberarInfo(cp->heap[1]);

    cp->heap[1] = cp->heap[cp->tope];

    //liberarInfo(cp->heap[cp->tope]);
    
    cp->tope = cp->tope-1;
    
    
    if(cp->tope>1)
    filtradoDescendente(cp,1);
  } 

  return cp; 
}

bool estaEnCP(nat elem, TColaDePrioridad cp){ 
  
  bool res = (elem>0) &&(elem<=cp->maximo) && (cp->arrPos[elem] != 0);
  return res; 
}

double prioridad(nat elem, TColaDePrioridad cp){ 
  //if(realInfo(cp->heap[cp->arrPos[elem]])!=0)
    return realInfo(cp->heap[cp->arrPos[elem]]);
  //else 
  //  return 0; 
}

