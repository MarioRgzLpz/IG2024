// Nombre: Mario, Apellidos: Rodriguez Lopez, Titulación: GIM .
// email: MarioRgzLpz@correo.ugr.es, DNI o pasaporte: 74539226K

#include "modelo-jer.h"
#include "malla-ind.h"
#include "malla-revol.h"
using namespace glm;

Nave::Nave()
{
    ponerNombre("Nave");
    unsigned ind = agregar(translate(vec3(0.0,0.0,0.0)));
    Textura* camuflaje = new Textura("textura-camuflaje.jpg");
    Material* materialcuerpo = new Material(camuflaje, 0.75, 1.0, 0.25, 50.0);
    agregar( new Fuselaje() );
    agregar( new Cabeza() );
    agregar( new Motor(rot_motor) );
    agregar( new Cohete() );
    agregar( new Fuego(tras_fuego) );

    NodoGrafoEscena* AlaIzq = new NodoGrafoEscena();
    NodoGrafoEscena* AlaDer = new NodoGrafoEscena();
    NodoGrafoEscena* Aleron = new NodoGrafoEscena();

    AlaIzq->ponerNombre("Ala Izquierda");
    AlaIzq->ponerIdentificador(6);
    AlaIzq->agregar(materialcuerpo);
    AlaIzq->agregar( new Ala());
    agregar(AlaIzq);
    AlaDer->ponerNombre("Ala Derecha");
    AlaDer->ponerIdentificador(7);
    AlaDer->agregar(rotate(float(M_PI), glm::vec3( 1.0, 0.0, 0.0) ));
    AlaDer->agregar(translate(glm::vec3(0.0, -0.25, 0.0)));
    AlaDer->agregar(materialcuerpo);
    AlaDer->agregar( new Ala());
    agregar(AlaDer);
    Aleron->ponerNombre("Aleron");
    Aleron->ponerIdentificador(8);
    Aleron->agregar(rotate(float(M_PI/2), glm::vec3( -1.0, 0.0, 0.0) ));
    Aleron->agregar(translate(glm::vec3(2.4, -0.04, 0.3)));
    Aleron->agregar(scale(glm::vec3(0.3,0.3,0.3)));
    Aleron->agregar(materialcuerpo);
    Aleron->agregar( new Ala());
    agregar(Aleron);
    tras_nave = leerPtrMatriz(ind);



}

unsigned Nave::leerNumParametros() const
{
    return 3;
}

void Nave::actualizarEstadoParametro(const unsigned iParam, const float t_sec)
{
    assert(iParam < leerNumParametros());
    float v;
 switch(iParam)
    {
        case 0:
            {
                v = 0 + 2*sin( 2*M_PI * 0.2 * t_sec);
                *tras_nave = translate( glm::vec3( v, 0.0, 0.0));
            }
            break;
        case 1:
            {    
                v = 0 + 2*M_PI*2.5*t_sec;
                *rot_motor = rotate( v, glm::vec3( 1.0, 0.0, 0.0));
            }
            break;
        case 2:
            {
                v = 3.0 - 0.5*sin( 2*M_PI * 0.2 * t_sec);
                *tras_fuego = translate( glm::vec3( v, 0.0, 0.0));

            }
    }              
}

Fuselaje::Fuselaje()
{
    ponerNombre("Fuselaje");
    ponerIdentificador(1);
    agregar(translate(glm::vec3(2.5,0.0,0.0)));
    agregar(rotate(float(M_PI/2), glm::vec3( 0.0, 0.0, 1.0) ));   
    agregar(scale(glm::vec3(0.5,5,0.5)));
    Textura* camuflaje = new Textura("textura-camuflaje.jpg");
    Material* materialcuerpo = new Material(camuflaje, 0.75, 0.9, 0.0, 50.0);
    agregar(materialcuerpo);
    agregar(new Cilindro(20,15));
}

Ala::Ala()
{
    agregar(translate(glm::vec3(0.0,0.25,0.45)));
    agregar(rotate(float(M_PI), glm::vec3( 0.0, 0.0, 1.0) ));
    agregar(scale(glm::vec3(1.5,0.25,3.0))); 
    agregar(new BaseAla());
}

Motor::Motor(glm::mat4 *&movimiento){
    ponerNombre("Motor");
    ponerIdentificador(3);
    agregar(scale(glm::vec3(1.5,1.5,1.5)));
    unsigned ind = agregar(rotate(float(M_PI),(glm::vec3( 1.0, 0.0, 0.0) )));
    agregar(translate(glm::vec3(-2.3,-0.5,-0.5)));
    agregar(new Aspas(4));
    movimiento = leerPtrMatriz(ind);

}

Cabeza::Cabeza(){
    ponerNombre("Cabeza");
    ponerIdentificador(2);
    agregar(translate(glm::vec3(-2.5,0.0,0.0)));
    agregar(scale(glm::vec3(1.0,0.5,0.5)));
    Textura* camuflaje = new Textura("textura-camuflaje.jpg");
    Material* materialcuerpo = new Material(camuflaje, 0.75, 0.9, 0.0, 50.0);
    agregar(materialcuerpo);
    agregar(new Esfera(15,20));
}

Cohete::Cohete(){
    ponerNombre("Cohete");
    ponerIdentificador(4);
    ponerColor({0.0, 0.0, 0.0});
    agregar(translate(glm::vec3(2.55,0.0,0.0)));
    agregar(rotate(float(M_PI/2), glm::vec3( 0.0, 0.0, 1.0) ));  
    agregar(scale(glm::vec3(0.55,0.55,0.55)));
    agregar(new Cono(20,15));
}

Fuego::Fuego(glm::mat4 *&movimiento){
    ponerNombre("Fuego");
    ponerIdentificador(5);
    unsigned ind = agregar(translate(glm::vec3(3.0,0.0,0.0)));
    agregar(rotate(float(M_PI/2), glm::vec3( 0.0, 0.0, 1.0) ));   
    agregar(scale(glm::vec3(0.45,1,0.45)));
    Textura* fuego = new Textura("textura-fuego.jpg");
    Material* materialfuego = new Material(fuego, 1.0, 0.25, 1.0, 100.0);
    agregar(materialfuego);
    agregar(new Cilindro(20,15));
    movimiento = leerPtrMatriz(ind);
}

