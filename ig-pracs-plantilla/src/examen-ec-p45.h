// Nombre: Mario, Apellidos: Rodriguez Lopez, Titulación: GIM .
// email: MarioRgzLpz@correo.ugr.es, DNI o pasaporte: 74539226K

#ifndef EXAMEN_EC_P45_HPP
#define EXAMEN_EC_P45_HPP

#include "malla-ind.h"
#include "grafo-escena.h"

class MallaP4 : public MallaInd
{
public:
    MallaP4();
};

class CasaUrbaP4 : public NodoGrafoEscena
{
public:
    CasaUrbaP4(unsigned numcasa);
    virtual bool cuandoClick(const glm::vec3 &centro_wc) override;

private:
    unsigned ncasa;
    mat4 *pm_rot = nullptr;
    float angle = 0.0;
};

class NodoUrbaP5 : public NodoGrafoEscena
{
public:
    NodoUrbaP5(unsigned ncasas);
};

#endif