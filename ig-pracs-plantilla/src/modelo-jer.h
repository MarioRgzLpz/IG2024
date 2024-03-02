// Nombre: Mario, Apellidos: Rodriguez Lopez, Titulación: GIM .
// email: MarioRgzLpz@correo.ugr.es, DNI o pasaporte: 74539226K
#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

#include "grafo-escena.h"

class Nave : public NodoGrafoEscena
{
public:
    Nave();
    unsigned leerNumParametros() const;
    void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
    Textura* camuflaje = new Textura("textura-camuflaje.jpg");
    Material* materialcuerpo = new Material(camuflaje, 0.75, 0.65, 0.25, 50.0);

protected:
    glm::mat4 *rot_motor = nullptr;
    glm::mat4 *tras_fuego = nullptr;
    glm::mat4 *tras_nave = nullptr; 

};

class Fuselaje : public NodoGrafoEscena
{
public:
    Fuselaje();

};

class Ala : public NodoGrafoEscena
{
public:
    Ala();
};

class Motor : public NodoGrafoEscena
{
public:
    Motor(glm::mat4 *&movimiento);
};

class Cabeza : public NodoGrafoEscena
{
public:
    Cabeza();
};

class Cohete : public NodoGrafoEscena
{
public:
    Cohete();
};

class Fuego : public NodoGrafoEscena
{
public:
    Fuego(glm::mat4 *&movimiento);
};

#endif