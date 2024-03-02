// Nombre: Mario, Apellidos: Rodriguez Lopez, Titulación: GIM .
// email: MarioRgzLpz@correo.ugr.es, DNI o pasaporte: 74539226K
// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// **
// ** Gestión de grafos de escena (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de:
// **     + Clase 'NodoGrafoEscena' (derivada de 'Objeto3D')
// **     + Clase 'EntradaNGE' (una entrada de un nodo del grafo de escena)
// **     + Tipo enumerado 'TipoEntNGE' (tipo de entradas del nodo del grafo de escena)
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "grafo-escena.h"
#include "aplicacion-ig.h"
#include "seleccion.h" // para 'ColorDesdeIdent'

// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE(Objeto3D *pObjeto)
{
   assert(pObjeto != nullptr);
   tipo = TipoEntNGE::objeto;
   objeto = pObjeto;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE(const glm::mat4 &pMatriz)
{
   tipo = TipoEntNGE::transformacion;
   matriz = new glm::mat4(); // matriz en el heap, puntero propietario
   *matriz = pMatriz;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE(Material *pMaterial)
{
   assert(pMaterial != nullptr);
   tipo = TipoEntNGE::material;
   material = pMaterial;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

NodoGrafoEscena::NodoGrafoEscena()
{
}

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL()
{
   using namespace std;
   assert(apl != nullptr);
   Cauce *cauce = apl->cauce;
   assert(cauce != nullptr);
   PilaMateriales *pila_materiales = apl->pila_materiales;
   assert(pila_materiales != nullptr);

   if (apl->iluminacion)
      pila_materiales->push();
   if (tieneColor())
   {
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }

   cauce->pushMM();
   for (unsigned i = 0; i < entradas.size(); i++)
   {
      switch (entradas[i].tipo)
      {
      case TipoEntNGE::objeto:               // entrada objeto:
         entradas[i].objeto->visualizarGL(); // llamar recursivamente a visualizarGL
         break;
      case TipoEntNGE::transformacion:         // entrada transf.:
         cauce->compMM(*(entradas[i].matriz)); // componer matriz
         break;
      case TipoEntNGE::material: // si la entrada es de tipo ’material’
         if (apl->iluminacion)   // y si está activada la iluminación
            pila_materiales->activar(entradas[i].material);
         break;
      }
   }

   cauce->popMM();
   if (tieneColor())
   {
      cauce->popColor();
   }
   if (apl->iluminacion)
   {
      pila_materiales->pop();
   }
}

// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...

void NodoGrafoEscena::visualizarGeomGL()
{
   using namespace std;
   // comprobar que hay un cauce
   assert(apl != nullptr);
   Cauce *cauce = apl->cauce;
   assert(cauce != nullptr);

   // COMPLETAR: práctica 3: implementar la visualización del nodo (ignorando colores)
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', pero más simple,
   // Se dan estos pasos:
   //
   // 1. Guardar copia de la matriz de modelado (con 'pushMM'),
   cauce->pushMM();
   // 2. Para cada entrada del vector de entradas:
   //         - Si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGeomGL'.
   //         - Si la entrada es de tipo transformación: componer la matriz (con 'compMM').

   for (int i = 0; i < entradas.size(); i++)
   {
      if (entradas[i].tipo == TipoEntNGE::objeto)
      {
         entradas[i].objeto->visualizarGeomGL();
      }
      else if (entradas[i].tipo == TipoEntNGE::transformacion)
      {
         cauce->compMM(*(entradas[i].matriz));
      }
   }

   //   3. Restaurar la copia guardada de la matriz de modelado (con 'popMM')

   cauce->popMM();

   // .......
}

// -----------------------------------------------------------------------------
// Visualizar las normales de los objetos del nodo

void NodoGrafoEscena::visualizarNormalesGL()
{
   using namespace std;

   // comprobar que hay un cauce
   assert(apl != nullptr);
   Cauce *cauce = apl->cauce;
   assert(cauce != nullptr);

   // COMPLETAR: práctica 4: visualizar las normales del nodo del grafo de escena
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', teniendo
   // en cuenta estos puntos:
   //
   // - usar push/pop de la matriz de modelado al inicio/fin (al igual que en visualizatGL)
   // - recorrer las entradas, llamando recursivamente a 'visualizarNormalesGL' en los nodos u objetos hijos
   // - ignorar el color o identificador del nodo (se supone que el color ya está prefijado antes de la llamada)
   // - ignorar las entradas de tipo material, y la gestión de materiales (se usa sin iluminación)

   // .......

   cauce->pushMM();

   for (int i = 0; i < entradas.size(); i++)
   {
      if (entradas[i].tipo == TipoEntNGE::objeto)
      {
         entradas[i].objeto->visualizarNormalesGL();
      }
      else if (entradas[i].tipo == TipoEntNGE::transformacion)
      {
         cauce->compMM(*(entradas[i].matriz));
      }
   }

   cauce->popMM();
}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores
// basados en los identificadores de los objetos
void NodoGrafoEscena::visualizarModoSeleccionGL()
{
   using namespace std;
   assert(apl != nullptr);
   Cauce *cauce = apl->cauce;
   assert(cauce != nullptr);

   // COMPLETAR: práctica 5: visualizar este nodo en modo selección.
   //
   // Se debe escribir código para dar estos pasos:
   //
   // 2. Leer identificador (con 'leerIdentificador'), si el identificador no es -1
   //      + Guardar una copia del color actual del cauce (con 'pushColor')
   //      + Fijar el color del cauce de acuerdo al identificador, (usar 'ColorDesdeIdent').
   // 3. Guardar una copia de la matriz de modelado (con 'pushMM')
   // 4. Recorrer la lista de nodos y procesar las entradas transformación o subobjeto:
   //      + Para las entradas subobjeto, invocar recursivamente a 'visualizarModoSeleccionGL'
   //      + Para las entradas transformación, componer la matriz (con 'compMM')
   // 5. Restaurar la matriz de modelado original (con 'popMM')
   // 6. Si el identificador no es -1, restaurar el color previo del cauce (con 'popColor')
   //
   // ........

   int identificador = leerIdentificador();

   if (identificador != -1)
   {
      cauce->pushColor();
      cauce->fijarColor(ColorDesdeIdent(identificador));
   }

   cauce->pushMM();

   for (int i = 0; i < entradas.size(); i++)
   {
      if (entradas[i].tipo == TipoEntNGE::objeto)
      {
         entradas[i].objeto->visualizarModoSeleccionGL();
      }
      else if (entradas[i].tipo == TipoEntNGE::transformacion)
      {
         cauce->compMM(*(entradas[i].matriz));
      }
   }

   cauce->popMM();

   if (identificador != -1)
   {
      cauce->popColor();
   }
}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar(const EntradaNGE &entrada)
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   // ........
   entradas.push_back(entrada);

   return entradas.size() - 1;
   ; // sustituir por lo que corresponda ....
}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar(Objeto3D *pObjeto)
{
   return agregar(EntradaNGE(pObjeto));
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar(const glm::mat4 &pMatriz)
{
   return agregar(EntradaNGE(pMatriz));
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar(Material *pMaterial)
{
   return agregar(EntradaNGE(pMaterial));
}

// devuelve el puntero a la matriz en la i-ésima entrada
glm::mat4 *NodoGrafoEscena::leerPtrMatriz(unsigned indice)
{
   // COMPLETAR: práctica 3: leer un puntero a una matriz en una entrada de un nodo
   //
   // Devolver el puntero a la matriz en la entrada indicada por 'indice'.
   // Debe de dar error y abortar si:
   //   - el índice está fuera de rango
   //   - la entrada no es de tipo transformación
   //   - el puntero a la matriz es nulo
   //
   // Sustituir 'return nullptr' por lo que corresponda.
   //
   if (indice >= entradas.size())
   {
      std::cout << "Error: indice fuera de rango" << std::endl;
      exit(0);
   }
   else if (entradas[indice].tipo != TipoEntNGE::transformacion)
   {
      std::cout << "Error: la entrada no es de tipo transformacion" << std::endl;
      exit(0);
   }
   else if (entradas[indice].matriz == nullptr)
   {
      std::cout << "Error: el puntero a la matriz es nulo" << std::endl;
      exit(0);
   }

   return entradas[indice].matriz;
}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{
   using namespace std;
   using namespace glm;

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   // ........
   if (centro_calculado)
      return;

   int contadorCentros = 0;
   mat4 matrizModelado(1.0f);
   vec3 centroAcumulado = vec3(0.0, 0.0, 0.0);

   for (const auto &entrada : entradas)
   {
      if (entrada.tipo == TipoEntNGE::transformacion)
      {
         matrizModelado *= (*entrada.matriz);
      }
      else if (entrada.tipo == TipoEntNGE::objeto)
      {
         entrada.objeto->calcularCentroOC();
         centroAcumulado += vec3(matrizModelado * vec4(entrada.objeto->leerCentroOC(), 1.0f));
         contadorCentros++;
         matrizModelado = mat4(1.0f); // Restablecer la matriz después de cada objeto
      }
   }

   if (contadorCentros > 0)
   {
      centroAcumulado /= static_cast<float>(contadorCentros);
   }

   ponerCentroOC(centroAcumulado);
   centro_calculado = true;
}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto(
    const int ident_busc,       // identificador a buscar
    const glm::mat4 &mmodelado, // matriz de modelado
    Objeto3D **objeto,          // (salida) puntero al puntero al objeto
    glm::vec3 &centro_wc        // (salida) centro del objeto en coordenadas del mundo
)
{
   using namespace std;
   using namespace glm;

   assert(0 < ident_busc);

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   // ........

   calcularCentroOC();

   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   // ........

   if (leerIdentificador() == ident_busc)
   {
      *objeto = this;
      centro_wc = leerCentroOC();
      return true;
   }

   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   // ........

   mat4 matrizmod = mmodelado;

   for (int i = 0; i < entradas.size(); i++)
   {
      if (entradas[i].tipo == TipoEntNGE::objeto)
      {
         if (entradas[i].objeto->buscarObjeto(ident_busc, matrizmod, objeto, centro_wc))
            return true;
      }
      else if (entradas[i].tipo == TipoEntNGE::transformacion)
         matrizmod = matrizmod * (*entradas[i].matriz);
   }

   // ni este nodo ni ningún hijo es el buscado: terminar
   return false;
}

// *****************************************************************************
// Clase GrafoEstrellaX

GrafoEstrellaX::GrafoEstrellaX(unsigned n)
{
   assert(n > 1);
   ponerNombre("GrafoEstrellaX");

   unsigned ind = agregar(rotate(float(M_PI), (glm::vec3(1.0, 0.0, 0.0))));
   agregar(rotate(float(M_PI / 2), glm::vec3(0, 1, 0)));
   agregar(scale(glm::vec3(2.6, 2.6, 2.6)));
   agregar(translate(glm::vec3(-0.5, -0.5, 0)));
   agregar(new EstrellaZ(n));

   agregar(scale(glm::vec3(1 / 2.6, 1 / 2.6, 1 / 2.6)));
   agregar(translate(glm::vec3(1.3, 1.3, 0)));

   agregar(rotate(float(M_PI / 2), glm::vec3(0.0, 0.0, 1.0)));
   for (int i = 0; i < n; i++)
   {
      agregar(rotate(float(2 * M_PI / n), glm::vec3(0, 0, 1)));
      agregar(new ConoEstrellaX());
   }

   rot_estrella = leerPtrMatriz(ind);
}

unsigned GrafoEstrellaX::leerNumParametros() const
{
   return 1;
}

void GrafoEstrellaX::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
   assert(iParam < leerNumParametros());
   float v;
   switch (iParam)
   {
   case 0:
   {
      v = 0 + 2 * M_PI * 2.5 * t_sec;
      *rot_estrella = rotate(v, glm::vec3(1.0, 0.0, 0.0));
   }
   break;
   }
}

ConoEstrellaX::ConoEstrellaX()
{
   agregar(translate(glm::vec3(0.0, 1.3, 0.0)));
   agregar(scale(glm::vec3(0.14, 0.15, 0.14)));
   agregar(new Cono(8, 40));
}

// *****************************************************************************
// Clase GrafoCubos

GrafoCubos::GrafoCubos()
{
   ponerNombre("GrafoCubos");
   agregar(new CaraCubos(rot_cubo1));
   agregar(scale(glm::vec3(-1, -1, -1)));
   agregar(new CaraCubos(rot_cubo2));
   agregar(rotate(float(M_PI / 2), glm::vec3(0, 0, 1)));
   agregar(new CaraCubos(rot_cubo3));
   agregar(rotate(float(M_PI / 2), glm::vec3(1, 0, 0)));
   agregar(new CaraCubos(rot_cubo4));
   agregar(rotate(float(M_PI / 2), glm::vec3(1, 0, 0)));
   agregar(new CaraCubos(rot_cubo5));
   agregar(rotate(float(M_PI / 2), glm::vec3(1, 0, 0)));
   agregar(new CaraCubos(rot_cubo6));
}

unsigned GrafoCubos::leerNumParametros() const
{
   return 1;
}

void GrafoCubos::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
   assert(iParam < leerNumParametros());
   float v;
   switch (iParam)
   {
   case 0:
   {
      v = 0 + 2 * M_PI * 2.5 * t_sec;
      *rot_cubo1 = rotate(v, glm::vec3(0.0, 1.0, 0.0));
      *rot_cubo2 = rotate(v, glm::vec3(0.0, 1.0, 0.0));
      *rot_cubo3 = rotate(v, glm::vec3(0.0, 1.0, 0.0));
      *rot_cubo4 = rotate(v, glm::vec3(0.0, 1.0, 0.0));
      *rot_cubo5 = rotate(v, glm::vec3(0.0, 1.0, 0.0));
      *rot_cubo6 = rotate(v, glm::vec3(0.0, 1.0, 0.0));
   }
   break;
   }
}

CaraCubos::CaraCubos(glm::mat4 *&movimiento)
{
   agregar(translate(glm::vec3(-0.5, 0.5, -0.5)));
   agregar(new RejillaY(6, 6));

   agregar(translate(glm::vec3(0.5, 0.25, 0.5)));
   agregar(scale(glm::vec3(0.125, 0.5, 0.125)));
   unsigned ind = agregar(rotate(0.0f, glm::vec3(0, 1, 0)));
   agregar(new Cubo());
   movimiento = leerPtrMatriz(ind);
}

// ----------------------------- ADICIONALES P4 -------------------------

NodoDiscoP4::NodoDiscoP4()
{
   ponerNombre("Nodo ejercicio adicional 1 práctica 4, examen 27 enero");
   agregar(new Material(new Textura("cuadricula.jpg"), 1.0, 1.0, 1.0, 100.0));
   agregar(new MallaDiscoP4());
}

NodoDiscoP4_2::NodoDiscoP4_2()
{
   ponerNombre("Nodo ejercicio adicional 2  práctica 4, examen 27 enero");
   agregar(new Material(new Textura("cuadricula.jpg"), 1.0, 1.0, 1.0, 100.0));
   agregar(new MallaDiscoP4_2());
}

// --------------------------------- ADICIONALES P5 --------------------------------

MiEsferaE1::MiEsferaE1(unsigned ifila, unsigned jcolumna) : fila(ifila + 1), columna(jcolumna + 1), centro(leerCentroOC())
{
   ponerNombre("MiEsfera de la fila " + std::to_string(ifila + 1) + " y columna " + std::to_string(jcolumna + 1) + " de la práctica 5");
   agregar(new Esfera(50, 50));
}

bool MiEsferaE1::cuandoClick(const glm::vec3 &centro_wc)
{
   using namespace std;

   cout << "Se ha seleccionado la esfera número: " << columna << " de la fila " << fila << endl;

   return true;
}

GrafoEsferasP5::GrafoEsferasP5()
{

   const unsigned
       n_filas_esferas = 8,
       n_esferas_x_fila = 5;
   const float
       e = 0.4 / n_esferas_x_fila;

   agregar(scale(glm::vec3(e, e, e)));

   for (unsigned i = 0; i < n_filas_esferas; ++i)
   {
      NodoGrafoEscena *fila_esferas = new NodoGrafoEscena();

      for (unsigned j = 0; j < n_esferas_x_fila; ++j)
      {
         MiEsferaE1 *esfera = new MiEsferaE1(i, j);
         esfera->ponerIdentificador(i * n_esferas_x_fila + j + 1);
         fila_esferas->agregar(translate(glm::vec3(2.2, 0.0, 0.0)));
         fila_esferas->agregar(esfera);
      }

      agregar(fila_esferas);
      agregar(translate(glm::vec3(0.0, 0.0, 5.0)));
   }
}

MiEsferaE2::MiEsferaE2()
{
   ponerColor({1.0, 1.0, 1.0});
   agregar(new Esfera(50, 50));
}

bool MiEsferaE2::cuandoClick(const glm::vec3 &centro_wc)
{
   using namespace std;

   if (leerColor() != glm::vec3(1.0, 0.0, 0.0))
   {
      ponerColor({1.0, 0.0, 0.0});
   }
   else
   {
      ponerColor({1.0, 1.0, 1.0});
   }

   return true;
}

GrafoEsferasP5_2::GrafoEsferasP5_2()
{
   const unsigned
       n_filas_esferas = 8,
       n_esferas_x_fila = 5;

   const float
       e = 2.5 / n_esferas_x_fila;

   agregar(scale(glm::vec3(e, e, e)));

   for (unsigned i = 0; i < n_filas_esferas; ++i)
   {
      NodoGrafoEscena *fila_esferas = new NodoGrafoEscena();

      for (unsigned j = 0; j < n_esferas_x_fila; ++j)
      {
         MiEsferaE2 *esfera = new MiEsferaE2();
         esfera->ponerIdentificador(i * n_esferas_x_fila + j + 1);
         fila_esferas->agregar(translate(glm::vec3(2.5, 0.0, 0.0)));
         fila_esferas->agregar(esfera);
      }

      agregar(fila_esferas);
      agregar(rotate(float(M_PI * 2 / n_filas_esferas), glm::vec3{0.0, 1.0, 0.0}));
   }
}
