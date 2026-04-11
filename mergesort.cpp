/**
   @file Ordenaci�n por mezcla
*/

   
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>






/* ************************************************************ */ 
/*  M�todo de ordenaci�n por mezcla  */

/**
   @brief Ordena un vector por el m�todo de mezcla.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de mezcla.
*/
inline static 
void mergesort(string T[], int num_elem);



/**
   @brief Ordena parte de un vector por el m�todo de mezcla.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la mezcla.
*/
static void mergesort_lims(string T[], int inicial, int final);


/**
   @brief Ordena un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
inline static 
void insercion(string T[], int num_elem);


/**
   @brief Ordena parte de un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de la inserci�n.
*/
static void insercion_lims(string T[], int inicial, int final);


/**
   @brief Mezcla dos vectores ordenados sobre otro.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a escribir.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a escribir
		   inicial < final.
   @param U: Vector con los elementos ordenados.
   @param V: Vector con los elementos ordenados.
             El n�mero de elementos de U y V sumados debe coincidir
             con final - inicial.

   En los elementos de T entre las posiciones inicial y final - 1
   pone ordenados en sentido creciente, de menor a mayor, los
   elementos de los vectores U y V.
*/
static void fusion(string T[], int inicial, int final, string U[], string V[]);



/**
   Implementaci�n de las funciones
**/


inline static void insercion(string T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
}


static void insercion_lims(string T[], int inicial, int final)
{
  int i, j;
  string aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((j>0) && (T[j]< T[j-1])) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}


int UMBRAL_MS = 256;

void mergesort(string T[], int num_elem)
{
  mergesort_lims(T, 0, num_elem);
}

static void mergesort_lims(string T[], int inicial, int final)
{
  if (final - inicial < UMBRAL_MS)
    {
      insercion_lims(T, inicial, final);
    } else {
      int k = (final - inicial)/2;

      string * U = new string [k - inicial + 1];
      assert(U);
      int l, l2;
      for (l = 0, l2 = inicial; l < k; l++, l2++)
	U[l] = T[l2];
      U[l] = "~";

      string * V = new string [final - k + 1];
      assert(V);
      for (l = 0, l2 = k; l < final - k; l++, l2++)
	V[l] = T[l2];
      V[l] = "~";

      mergesort_lims(U, 0, k);
      mergesort_lims(V, 0, final - k);
      fusion(T, inicial, final, U, V);
      delete [] U;
      delete [] V;
    };
}
  

static void fusion(string T[], int inicial, int final, string U[], string V[])
{
  int j = 0;
  int k = 0;
  for (int i = inicial; i < final; i++)
    {
      if (U[j] < V[k]) {
	T[i] = U[j];
	j++;
      } else{
	T[i] = V[k];
	k++;
      };
    };
}


//FUNCIONES PARA STRING FIJO, VARIABLE Y CON PREFIJO
string StringFijo(int longitud){
  string caracteres = "abcdefghijklmnopqrstuvwxyz";
  string resultado;
  resultado.reserve(longitud);

  for(int i = 0; i < longitud; i++){
    resultado += caracteres[rand() % 26];
  }

  return resultado;
}


string StringVariable(int longitud_minima, int longitud_maxima){
  assert(longitud_maxima >= longitud_minima);
  string caracteres = "abcdefghijklmnopqrstuvwxyz";
  string resultado;
  resultado.reserve(longitud_maxima);
  int longitud = longitud_minima + rand() % (longitud_maxima - longitud_minima + 1);

  for(int i = 0; i < longitud; i++){
    resultado += caracteres[rand() % 26];
  }
  return resultado;
}

string StringPrefijo(string prefijo, int longitud_anadida){
  string caracteres = "abcdefghijklmnopqrstuvwxyz";
  string resultado = prefijo;
  resultado.reserve(resultado.length() + longitud_anadida);

  for(int i = 0; i < longitud_anadida; i++) {
    resultado += caracteres[rand() % 26];
  }

  return resultado;
}


int main(int argc, char * argv[]){
  
  //Hemos de pasarle 5 argumentos
  if(argc != 5){
    cerr << "\nUso: " << argv[0] << " <tamanio> <umbral> <tipo_string (1=Fijo, 2=Var, 3=Prefijo)> <algoritmo (0=MergeSort, 1=Insercion)>" << endl;
    return -1;
  }

  int a = atoi(argv[1]);
  UMBRAL_MS = atoi(argv[2]);
  int tipo_string = atoi(argv[3]);
  int algoritmo = atoi(argv[4]);

  assert(tipo_string == 1 || tipo_string == 2 || tipo_string == 3);
  assert(algoritmo == 0 || algoritmo == 1);

  string * V = new string[a];
  assert(V);

  srand(time(0)); //semilla
  string prefijo = "prefijo_largo_para_prueba";

for(int i = 0; i < a; i++)
  switch (tipo_string) {
    case 1:
      V[i] = StringFijo(50);
      break;
    case 2:
      V[i] = StringVariable(10,100);
      break;
    case 3:
      V[i] = StringPrefijo(prefijo,10);

  }

 //Calculamos el tiempo
  auto start = chrono::high_resolution_clock::now();

  if (algoritmo)
    insercion(V,a);
  else
    mergesort(V,a);

  //Tiempo final
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double,std::milli> duration = end - start; //Calculamos el tiempo que tarda

  //Resultados:
  string nombre_algoritmo = (algoritmo == 1) ? "Insercion" : "MergeSort";
  string nombre_string;
  if (tipo_string == 1) nombre_string = "Fijo";
  else if (tipo_string == 2) nombre_string = "Variable";
  else nombre_string = "Prefijo";

  // Resultados impresos en una sola línea (ideal para scripts y Excel)
  // Formato: Algoritmo | Tamaño | Umbral | TipoString | Tiempo
  cout << "Algoritmo: " << nombre_algoritmo
       << " | Tamaño: " << a
       << " | Umbral: " << UMBRAL_MS
       << " | TipoString: " << nombre_string
       << " | Tiempo: " << duration.count() << endl;

  //Liberamos memoria
  delete [] V;

  return 0;

}