// Nombre: Mario, Apellidos: Rodriguez Lopez, Titulación: GIM .
// email: MarioRgzLpz@correo.ugr.es, DNI o pasaporte: 74539226K
#ifndef EXAMEN_EC_123_HPP
#define EXAMEN_EC_123_HPP

#include "malla-ind.h" 
#include "grafo-escena.h"

class P1MallaCubo : public MallaInd
{
   public:
      P1MallaCubo();
};

class P2Rejilla: public MallaInd
{
   public:
      P2Rejilla(unsigned int n, unsigned m);
};

class P3Cuadrado : public MallaInd
{
public:
    P3Cuadrado();

};

class P3Caja: public NodoGrafoEscena
{
    public:
    P3Caja();
    unsigned leerNumParametros() const;
    void actualizarEstadoParametro(const unsigned iParam, const float t_sec);

protected:
    glm::mat4 *rot_cuadrado = nullptr;
    glm::mat4 *tras_esfera = nullptr;
};


class Bola : public NodoGrafoEscena
{
public:
    Bola(glm::mat4 *&movimiento);
};

class Puertas : public NodoGrafoEscena
{
public:
    Puertas(glm::mat4 *&movimiento);
};

#endif