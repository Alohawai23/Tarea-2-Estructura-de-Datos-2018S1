#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct registro{
  int grado;
  int coef;
  int tamanio;
  struct registro *izq;
  struct registro *der;
}registro;

typedef struct registro Nodo;
/*****
* struct Nodo crear_arbol
******
* Esta funcion crea un arbol vacio, el cual contiene solamente la raiz, la cual es un puntero a NULL
******
* Input:
*   Nodo root : nodo raiz que contiene un puntero vacio
******
* Returns:
*   Nodo, raiz del arbol vacio
*****/
Nodo *crear_arbol(Nodo *root){
  return (root = NULL);
}
/*****
* Nodo insertar_nodo
******
* Esta funcion inserta un nodo cualquiera en el arbol, y lo ordena segun el grado
* del nodo, ademas de aumentar el tamanio del arbol.
******
* Input:
*   int g : grado del nodo a insertar en el arbol
*   int c: coeficiente del nodo a insertar en el arbol
*   Nodo ar: nodo a insertar en el arbol, el cual se llenara con la informacion dada
******
* Returns:
*   Nodo ar, nodo insertado en el arbol, con la informacion dada dentro del struct
*****/
Nodo *insertar_nodo(int g, int c, Nodo *ar){
  Nodo *info =(Nodo*)malloc(sizeof(Nodo));
  Nodo *aux = ar;
  int i, flag = 1;
  if(info != NULL){
    info->grado = g;
    info->coef = c;
    info->izq = NULL;
    info->der = NULL;
    if(ar == NULL){
      ar = info;
      ar->tamanio = 0;
      ar->tamanio ++;
    }
    else{
      for(i = 0; i < ar->tamanio; i++){
        if(aux->grado < g && flag == 1){
          if(aux->der == NULL){
            aux->der = info;
            flag = 0;
          }
          else aux = aux->der;
        }
        if(aux->grado > g && flag == 1){
          if(aux->izq == NULL){
            aux->izq = info;
            flag = 0;
          }
          else aux = aux->izq;
        }
      }
    }
  }
  if(flag == 0) ar->tamanio ++;
  return ar;
}
/*****
* int coeficiente
******
* funcion que determina el coeficiente de un cierto nodo del arbol, funcion que
*`se encarga de resolver la operacion Coeficiente de entrada.
******
* Input:
*   int g: grado del nodo a revisar
*   Nodo arbol: nodo a revisar, pedido en entrada
******
* Returns:
*   int c, coeficiente pedido por entrada
*****/
int coeficiente(int g, Nodo *arbol){
  Nodo *aux = arbol;
  int i, c = 0;
  for(i = 0; i < arbol->tamanio;i++){
    if(aux->grado == g) c = aux->coef;
    if(aux->grado < g && aux->der != NULL) aux = aux->der;
    if(aux->grado > g && aux->izq != NULL) aux = aux->izq;
  }
  return c;
}
/*****
* void liberar
******
* funcion que se encarga de liberar la memoria pedida para crear el arbol
******
* Input:
*   Nodo root: nodo raiz, para poder liberar sus hijos de manera recursiva
******
* Returns:
*   vacio
*****/
void liberar(Nodo *root) {
  if (root == NULL) return;
  liberar(root->izq);
  liberar(root->der);
  free((void *) root);
}
/*****
* int max_grado
******
* determina el grado maximo del arbol de manera recursiva, recorriendo todo el arbol
* hasta que no quede ningun hijo a la derecha, lo que significa que ese nodo Contiene
* el grado maximo del arbol.
******
* Input:
*   Nodo arbol: arbol a analizar, para ir recorriendo todos sus nodos y conseguir
*   el grado maximo de este.
******
* Returns:
*   int grado, valor del grado maximo del arbol.
*****/
int max_grado(Nodo *arbol){
  if(arbol->der == NULL) return arbol->grado;
  else return(max_grado(arbol->der));
}
/*****
* float evaluar
******
* funcion que se encarga de evaluar un polinomio en un valor dado y conseguir el
* valor de este polinomio para este valor x dado.
******
* Input:
*   float x: valor de x dado para evaluar el polinomio
*   Nodo arbol: arbol que contiene el polinomio a evaluar con sus grados y coeficiente
*   correspondientes.
******
* Returns:
*   float resultado, valor del polinomio completo evaluado en el x dado.
*****/
float evaluar(float x, Nodo *arbol){
  int  max, c;
  float resultado = 0.0;
  max = max_grado(arbol);
  while(max != -1){
    c = coeficiente(max,arbol);
    resultado = (resultado*x) + c;
    max--;
  }
  return resultado;
}
/*****
* int main
******
* funcion principal del programa, la cual se encarga de abrir, leer el archivo
* de entrada, para conseguir los polinomios a analizar, y cuales operaciones se
* le haran a estos polinomios, aparte de liberar la memoria en un final.
******
* Input:
*   no recibe ningun parametro de input
******
* Returns:
*   retorna 0 si la funcion compila correctamente
*****/
int main(){
  int N, i, monomios, j, gr, co, n1, c;
  float n2, evaluado;
  char operacion[20];
  FILE *fp = fopen("entradaPolinomio.txt","r");
  if(fp == NULL) printf("Existio un problema al abrir el archivo\n");
  FILE *res = fopen("salidaPolinomio.txt", "w");
  fscanf(fp, "%d", &N);
  Nodo *polignomeo[N]; 
  Nodo *arbol;
  for(i = 0; i < N;i++){
    fscanf(fp,"%d", &monomios);
    arbol = crear_arbol(arbol);
    for(j = 0; j < monomios;j++){
      fscanf(fp,"%d %d", &gr, &co);
      arbol = insertar_nodo(gr,co,arbol);
    }
    polignomeo[i] = arbol;
  }
  while (!feof(fp)){
  fscanf(fp,"%s %d %f",operacion, &n1, &n2);
  if(strcmp(operacion, "COEFICIENTE") == 0){
    c = coeficiente(n2,polignomeo[n1]);
    fprintf(res, "%d\n",c);
    }
  if(strcmp(operacion, "EVALUAR") == 0){
    evaluado = evaluar(n2,polignomeo[n1]);
    fprintf(res, "%f\n",evaluado);
    }
  }
  fclose(fp);
  fclose(res);
  for(i = 0; i < N; i++){
    liberar(polignomeo[i]);
  }
  return 0;
}
