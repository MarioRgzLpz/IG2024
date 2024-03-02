// Nombre: Mario, Apellidos: Rodriguez Lopez, Titulación: GIM .
// email: MarioRgzLpz@correo.ugr.es, DNI o pasaporte: 74539226K
// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de grafos de escena (declaraciones)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Declaraciones de: 
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

#ifndef GRAFO_ESCENA_HPP
#define GRAFO_ESCENA_HPP

//#include <tup_mat.h>   

#include "objeto3d.h"
#include "malla-ind.h" // para poder usar clase MallaInd
#include "materiales-luces.h"
#include "malla-revol.h"

//using namespace tup_mat ;
using namespace glm;

// *********************************************************************
// declaración adelantada de estructura para un nodo del grafo de escena

class NodoGrafoEscena ;

// *********************************************************************
// tipo enumerado con los tipos de entradas del nodo del grafo de escena

enum class TipoEntNGE { objeto, transformacion, material, noInicializado } ;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

struct EntradaNGE
{
   TipoEntNGE tipo = TipoEntNGE::noInicializado ;   // objeto, transformacion, material
   union
   {  Objeto3D  * objeto = nullptr ;  // ptr. a un objeto (no propietario)
      glm::mat4 * matriz   ;  // ptr. a matriz 4x4 transf. (propietario)
      Material  * material ; // ptr. a material (no propietario)
   } ;
   // constructores (uno por tipo)
   EntradaNGE() = delete ; // prohibe constructor sin parámetros
   EntradaNGE( Objeto3D        * pObjeto   );      // (copia solo puntero)
   EntradaNGE( const glm::mat4 & pMatriz   ); // (crea copia en el heap)
   EntradaNGE( Material        * pMaterial );    // (copia solo puntero)
   ~EntradaNGE() ;
} ;

// *********************************************************************
// Nodo del grafo de escena: es un objeto 3D parametrizado, que contiene una lista de entradas

class NodoGrafoEscena : public Objeto3D
{
   protected:
   // COMPLETAR: práctica 3: definir variables y métodos privados del nodo

   bool centro_calculado = false;

   std::vector<EntradaNGE> entradas ; // vector de entradas del nodo
   // .......

   public:

   NodoGrafoEscena() ;

   // visualiza usando OpenGL
   virtual void visualizarGL(  ) ;

   // visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...
   // (se supone que el estado de OpenGL está fijado antes de esta llamada de alguna forma adecuada)
   virtual void visualizarGeomGL(  ) ;

   // visualizar las normales de los objetos del nodo
   virtual void visualizarNormalesGL () ;

   // visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
   // basados en los identificadores de los objetos
   virtual void visualizarModoSeleccionGL()  ;

   // añadir una entrada al final, hace copia de la entrada
   // devuelve indice de la entrada dentro del vector de entradas
   unsigned agregar( const EntradaNGE & entrada );

   // construir una entrada y añadirla (al final)
   unsigned agregar( Objeto3D *        pObjeto ); // objeto (copia solo puntero)
   unsigned agregar( const glm::mat4 & pMatriz ); // matriz (copia objeto)
   unsigned agregar( Material *        pMaterial ); // material (copia solo puntero)

   // devuelve el puntero a la matriz en la i-ésima entrada
   glm::mat4 * leerPtrMatriz( unsigned iEnt );

   // método para buscar un objeto con un identificador
   virtual bool buscarObjeto( const int ident_busc, const glm::mat4 & mmodelado,
                    Objeto3D ** objeto, glm::vec3 & centro_wc )  ;

   // si 'centro_calculado' es 'false', recalcula el centro usando los centros
   // de los hijos (el punto medio de la caja englobante de los centros de hijos)
   virtual void calcularCentroOC() ;


} ;
// *********************************************************************

class GrafoEstrellaX : public NodoGrafoEscena
{
   public:
      GrafoEstrellaX(unsigned n);
      unsigned leerNumParametros() const;
      void actualizarEstadoParametro(const unsigned iParam, const float t_sec);

   protected:
      glm::mat4 *rot_estrella = nullptr;
} ;

class ConoEstrellaX : public NodoGrafoEscena
{
   public:
      ConoEstrellaX();
} ;


// *********************************************************************

class GrafoCubos : public NodoGrafoEscena
{
   protected: // punteros a matrices
      glm::mat4 *rot_cubo1 = nullptr;
      glm::mat4 *rot_cubo2 = nullptr;
      glm::mat4 *rot_cubo3 = nullptr;
      glm::mat4 *rot_cubo4 = nullptr;
      glm::mat4 *rot_cubo5 = nullptr;
      glm::mat4 *rot_cubo6 = nullptr;
   public:
      unsigned leerNumParametros() const;
      void actualizarEstadoParametro( const unsigned iParam, const float tSec );
      GrafoCubos();
};

// Pared del cubo grande consistente en una instancia de la clase RejillaY con un
// paralelepípedo en su centro
class CaraCubos : public NodoGrafoEscena
{
   public:
      CaraCubos(glm::mat4 *&movimiento);
} ;

// ------------------------------------ ADICIONALES P4 ---------------------------------

class NodoDiscoP4 : public NodoGrafoEscena
{
   public:
      NodoDiscoP4();
};

class NodoDiscoP4_2 : public NodoGrafoEscena
{
   public:
      NodoDiscoP4_2();
};


// ------------------------------------ ADICIONALES P5 ---------------------------------------

class MiEsferaE1 : public NodoGrafoEscena
{
   public:
      MiEsferaE1(unsigned ifila, unsigned jcolumna);

      virtual bool cuandoClick(const glm::vec3 &centro_wc) override;
   private:
      unsigned fila, columna;
      glm::vec3 centro;
      
};

class MiEsferaE2 : public NodoGrafoEscena
{
   public:
      MiEsferaE2();

      virtual bool cuandoClick(const glm::vec3 &centro_wc) override;
};

class GrafoEsferasP5 : public NodoGrafoEscena
{
   public:
      GrafoEsferasP5();
};


class GrafoEsferasP5_2 : public NodoGrafoEscena
{
   public:
      GrafoEsferasP5_2();

};

#endif // GRAFO_ESCENA_HPP


