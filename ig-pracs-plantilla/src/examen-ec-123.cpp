// Nombre: Mario, Apellidos: Rodriguez Lopez, Titulación: GIM .
// email: MarioRgzLpz@correo.ugr.es, DNI o pasaporte: 74539226K
// *********************************************************************
#include "examen-ec-123.h"

using namespace std;
using namespace glm;

P1MallaCubo::P1MallaCubo() :  MallaInd( "cubo 8 vértices con colores RGB" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
         { 0.0, +1.0, 0.0 }, // 8 //Nuevos vertices
         { 0.0, -1.0, 0.0 }, // 9
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ 

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3},  // Z+ (+1)

         {0,9,1}, {0,4,9}, //Nuevos triangulos Y-
         {4,9,5}, {1,9,5},

        {8,3,7}, {7,8,6}, // Y+
         {2,3,8}, {2,8,6}, // 
      } ;

   col_ver = 
      {  {0,0,0}, 
         {0,0,1}, 
         {0,1,0}, 
         {0,1,1}, 
         {1,0,0}, 
         {1,0,1}, 
         {1,1,0}, 
         {1,1,1},
         {1,0,0}, //Nuevos colores
         {0,1,1}
      } ;

}

P2Rejilla::P2Rejilla(unsigned m, unsigned n)
   : MallaInd( "P2Rejilla" )
{
   for (int i = 0; i < m; i++){
      for (int j = 0; j < n; j++){
         vertices.push_back({(i*2.0)/(m-1), 0, (j*1.4)/(n-1)});
      }
   }


   for (int i = 0; i < m-1; i++){
      for (int j = 0; j < n-1; j++){
        if((i+j)%2==0){
            triangulos.push_back({n*i+j, n*i+j+1, n*(i+1)+j+1});
            triangulos.push_back({n*i+j, n*(i+1)+j+1, n*(i+1)+j});
        }else{
            triangulos.push_back({n*i+j, n*i+j+1, n*(i+1)+j+1});
            triangulos.push_back({n*i+j+1, n*(i+1)+j, n*(i+1)+j});
        }
      }
   }

  
}

P3Cuadrado::P3Cuadrado() : MallaInd("Cuadrado"){
   vertices =
      {  { -1.0, 0.0, -1.0 }, // 0
         { -1.0, 0.0, +1.0 }, // 1
         { +1.0, 0.0, -1.0 }, // 2
         { +1.0, 0.0, +1.0 } // 3
      };
      triangulos = {
        {0,1,3}, {0,3,2}
      };
}


P3Caja::P3Caja() 
{
    ponerNombre("Caja");
    agregar(new P3Cuadrado());
    agregar(new Bola(tras_esfera));
    agregar(scale(glm::vec3(1.0,0.5,1.0)));
    agregar(translate(glm::vec3( 1.0, 1.0, 0.0)));
    agregar(rotate(float(M_PI/2), glm::vec3( 0.0, 0.0, 1.0) )); 
    agregar(new P3Cuadrado());
    agregar(rotate(float(M_PI/2), glm::vec3( 1.0, 0.0, 0.0) )); 
    agregar(translate(glm::vec3( 0.0, 1.0, -1.0)));
    agregar(new P3Cuadrado());
    agregar(rotate(float(M_PI/2), glm::vec3( 1.0, 0.0, 0.0) ));
    agregar(translate(glm::vec3( 0.0, -1.0, 1.0)));
    agregar(new P3Cuadrado());
    agregar(rotate(float(M_PI/2), glm::vec3( 1.0, 0.0, 0.0) ));
    agregar(translate(glm::vec3( 0.0, -1.0, 1.0)));
    agregar(new P3Cuadrado());



}
unsigned P3Caja::leerNumParametros() const
{
    return 2;
}

void P3Caja::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    assert(iParam < leerNumParametros());
    float v;
 switch(iParam)
    {
        case 0:
            {
                v = 0 + 2*sin( 2*M_PI * 0.2 * t_sec);
                *tras_esfera = translate( glm::vec3( v, 0.0, 0.0));
            }
            break;
        case 1:
            {    
                v = 0 + M_PI/2*t_sec;
                *rot_cuadrado = rotate( v, glm::vec3( 0.0, 1.0, 0.0));
            }
            break;
    }              
}

Bola::Bola(glm::mat4 *&movimiento){
    unsigned ind = agregar(translate(glm::vec3(0.0,0.5,0.0)));
    agregar(scale(glm::vec3(0.45,0.45,0.45)));
    agregar(new Esfera(20,20));
    movimiento = leerPtrMatriz(ind);
}

Puertas::Puertas(glm::mat4 *&movimiento){
    unsigned ind = agregar(rotate(float(M_PI),(glm::vec3( 1.0, 0.0, 0.0) )));
    agregar(translate(glm::vec3(-2.3,-0.5,-0.5)));
}