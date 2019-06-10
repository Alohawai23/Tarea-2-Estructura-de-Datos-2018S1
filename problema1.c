#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registro{
  struct registro *sig;
  int grado;
  int coef;
  int mono;
}registro;
/*****
* TipoFunción NombreFunción
******
* Resumen Función
******
* Input:
*   tipoParámetro NombreParámetro : Descripción Parámetro
******
* Returns:
*   TipoRetorno, Descripción retorno
*****/
typedef struct registro Nodo;
/*****
* TipoFunción NombreFunción
******
* Resumen Función
******
* Input:
*   tipoParámetro NombreParámetro : Descripción Parámetro
******
* Returns:
*   TipoRetorno, Descripción retorno
*****/
Nodo *crear_lista(Nodo *head){
  return (head = NULL);
}
/*****
* TipoFunción NombreFunción
******
* Resumen Función
******
* Input:
*   tipoParámetro NombreParámetro : Descripción Parámetro
******
* Returns:
*   TipoRetorno, Descripción retorno
*****/
Nodo *insertar(int gra,int c, int m, Nodo *p){
  Nodo *Nregistro, *aux;
  Nregistro = (Nodo*)malloc(sizeof(Nodo));
  if(Nregistro != NULL){
    Nregistro->grado = gra;
    Nregistro->coef = c;
    Nregistro->mono = m;
    Nregistro->sig = NULL;
    if(p == NULL){ //Se ve si el puntero es la cabeza, es decir, la lista esta vacia
      p = Nregistro;
    }
    else{
      aux = p; //Se utiliza un auxiliar para n perder la cabeza de la lista
      while(aux -> sig != NULL){ //Se mueve el puntero hasta llegar al ultimo elemento
        aux = aux ->sig;
      }
      aux->sig = Nregistro;
    }
  }
  return p;
}
/*****
* TipoFunción NombreFunción
******
* Resumen Función
******
* Input:
*   tipoParámetro NombreParámetro : Descripción Parámetro
******
* Returns:
*   TipoRetorno, Descripción retorno
*****/
int grado_max(Nodo *nodo){
  Nodo *aux = nodo;
  int max = -1000, i;
  int largo = aux->mono;
  for(i = 0; i < largo;i++){
    if(aux->grado > max) max = aux->grado;
    aux = aux->sig;
  }
  return max;
}
/*****
* TipoFunción NombreFunción
******
* Resumen Función
******
* Input:
*   tipoParámetro NombreParámetro : Descripción Parámetro
******
* Returns:
*   TipoRetorno, Descripción retorno
*****/
int coeficiente2(Nodo *cabeza, float g){
  Nodo *aux = cabeza;
  while(aux != NULL){
    if(aux->grado == g){
      return aux->coef;
    }
    aux = aux ->sig;
  }
  return 0;
}
/*****
* TipoFunción NombreFunción
******
* Resumen Función
******
* Input:
*   tipoParámetro NombreParámetro : Descripción Parámetro
******
* Returns:
*   TipoRetorno, Descripción retorno
*****/
float evaluar(Nodo *cabeza,float x){
  Nodo *aux = cabeza;
  int maximo, c;
  float resultado = 0.0;
  maximo = grado_max(aux);
  while (maximo != -1) {
    c = coeficiente2(aux,maximo);
    resultado = (resultado * x) + c;
    maximo --;
  }
  return resultado;
  }
/*****
* TipoFunción NombreFunción
******
* Resumen Función
******
* Input:
*   tipoParámetro NombreParámetro : Descripción Parámetro
******
* Returns:
*   TipoRetorno, Descripción retorno
*****/
Nodo *eliminar_nodo(Nodo *nodo){
  if(nodo->sig != NULL){
    Nodo *aux = nodo->sig;
    free(nodo);
    return aux;
  }
  free(nodo);
  return NULL;
}
/*****
* TipoFunción NombreFunción
******
* Resumen Función
******
* Input:
*   tipoParámetro NombreParámetro : Descripción Parámetro
******
* Returns:
*   TipoRetorno, Descripción retorno
*****/
int main(){
  int N, i, monomios, j, gr, co, n1, c;
  float n2, evaluado;
  char operacion[20];
  FILE *fp = fopen("entradaPolinomio.txt","r");
  if(fp == NULL) printf("Existio un problema al abrir el archivo\n");
  FILE *res = fopen("salidaPolinomio.txt", "w");
  fscanf(fp, "%d", &N);
  Nodo *polignomeo[N]; //Contiene las posiciones de donde comienza cada polinomio en la lista
  Nodo *lista;
  for(i = 0; i < N;i++){
    fscanf(fp,"%d", &monomios);
    lista = crear_lista(lista);
    for(j = 0; j < monomios;j++){
      fscanf(fp,"%d %d", &gr, &co);
      lista = insertar(gr,co,monomios,lista);
    }
    polignomeo[i] = lista;
  }
  while (!feof(fp)){
    fscanf(fp,"%s %d %f",operacion, &n1, &n2);
    if(strcmp(operacion, "COEFICIENTE") == 0){
      c = coeficiente2(polignomeo[n1],n2);
      fprintf(res, "%d\n",c);
    }
    if(strcmp(operacion, "EVALUAR") == 0){
      evaluado = evaluar(polignomeo[n1],n2);
      fprintf(res, "%f\n",evaluado);
    }
  }
  fclose(fp);
  fclose(res);
  for(i =0; i < N; i++){
    while(polignomeo[i] != NULL){
      polignomeo[i] = eliminar_nodo(polignomeo[i]);
    }
  }
  return 0;
}
