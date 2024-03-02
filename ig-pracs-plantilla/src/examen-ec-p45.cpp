// Nombre: Mario, Apellidos: Rodriguez Lopez, Titulación: GIM .
// email: MarioRgzLpz@correo.ugr.es, DNI o pasaporte: 74539226K
// *********************************************************************
#include "examen-ec-p45.h"

using namespace std;
using namespace glm;

MallaP4::MallaP4()
{
    vertices =
        {
            {+1.0, -1.0, +1.0}, // 0
            {+1.0, +1.0, +1.0}, // 1
            {+1.0, +1.0, -1.0}, // 2
            {+1.0, -1.0, -1.0}, // 3

            {-1.0, -1.0, +1.0}, // 4
            {-1.0, +1.0, +1.0}, // 5
            {+1.0, +1.0, +1.0}, // 6
            {+1.0, -1.0, +1.0}, // 7

            {-1.0, -1.0, -1.0}, // 8
            {-1.0, +1.0, -1.0}, // 9
            {-1.0, +1.0, +1.0}, // 10
            {-1.0, -1.0, +1.0}, // 11

            {+1.0, -1.0, -1.0}, // 12
            {+1.0, +1.0, -1.0}, // 13
            {-1.0, +1.0, -1.0}, // 14
            {-1.0, -1.0, -1.0}, // 15

            {+1.0, +1.0, +1.0}, // 16
            {-1.0, +1.0, +1.0}, // 17
            {-1.0, +1.0, -1.0}, // 18
            {+1.0, +1.0, -1.0}, // 19

            {+1.0, -1.0, +1.0}, // 20
            {-1.0, -1.0, +1.0}, // 21
            {-1.0, -1.0, -1.0}, // 22
            {+1.0, -1.0, -1.0}, // 23

            {+1.0, +1.0, +1.0}, // 24
            {-1.0, +1.0, +1.0}, // 25
            {-1.0, +1.0, -1.0}, // 26
            {+1.0, +1.0, -1.0},  // 27

            {0.0, +2.0, 0.0}, // 28
            {0.0, +2.0, 0.0}, // 29
            {0.0, +2.0, 0.0}, // 30
            {0.0, +2.0, 0.0},  // 31
        };

    triangulos =
        {
            {0, 3, 2},
            {0, 2, 1},

            {4, 7, 6},
            {4, 6, 5},

            {8, 11, 10},
            {8, 10, 9},

            {12, 15, 14},
            {12, 14, 13},

            //nuevos triangulos para formar la piramide, hemos eliminado los que formaban el techo del cubo

            {29, 19, 18}, 
            {16, 28, 17}, 

            {24, 27, 30}, 
            {25, 26, 31}, 

            //

            {20, 23, 22},
            {20, 22, 21}};

    cc_tt_ver = {  //No me da tiempo a colocar correctamente cada vertice de textura pero seria ir colocando en funcion del dibujo
        {0.0, 0.5 }, //0
        {0.0, 0},
        {0.5, 0.0},
        {0.5, 0.5},

        {0.0, 0.5 }, //0
        {0.0, 0},
        {0.5, 0.0},
        {0.5, 0.5},

        {0.5, 1.0 },
        {0.5, 1.0},
        {1.0, 0.5},
        {1.0, 0.5},

        {0.0, 1.0 - 0.0},
        {0.0, 1.0 - 1.0},
        {1.0, 1.0 - 1.0},
        {1.0, 1.0 - 0.0},  //Coloco solo las del tejado no me da tiempo

        {0.25, 0.5},
        {0.0, 0.5},
        {0.0, 0.0},
        {0.25,0},

        {0.0, 1.0 - 0.0},
        {0.0, 1.0 - 1.0},
        {1.0, 1.0 - 1.0},
        {1.0, 1.0 - 0.0},
        
        {0.25, 0.5},
        {0.0, 0.5},
        {0.0, 0.0},
        {0.25,0},

        {0.125, 0.25},
        {0.125, 0.25},
        {0.125, 0.25},
        {0.125, 0.25},};
}

CasaUrbaP4::CasaUrbaP4(unsigned numcasa) : ncasa(numcasa + 1)
{
    ponerNombre("Nodo examen 19 enero");
    pm_rot = leerPtrMatriz(agregar(rotate(float(2*M_PI),(glm::vec3( 1.0, 0.0, 0.0) ))));
    angle = 0.0;
    agregar(new Material(new Textura("ventanas-tejado-2048x1024.jpg"), 0.6, 0.8, 0.1, 15.0));
    agregar(new MallaP4());
}

bool CasaUrbaP4::cuandoClick(const glm::vec3 &centro_wc)
{
    using namespace std;

    cout << "Se ha seleccionado la casa número: " << ncasa << endl;

    
    *pm_rot = rotate(angle + float(M_PI / 6), glm::vec3(0.0, 1.0, 0.0));
    angle += float(M_PI / 6);

    return true;
}

NodoUrbaP5::NodoUrbaP5(unsigned int ncasas)
{
    for (unsigned i = 0; i < ncasas; ++i)
    {
        NodoGrafoEscena *fila_casas = new NodoGrafoEscena();

        CasaUrbaP4 *casa = new CasaUrbaP4(i);
        casa->ponerIdentificador(i + 1);
        fila_casas->agregar(casa);

        agregar(fila_casas);
        agregar(translate(glm::vec3(0.0, 0.0, 2.0)));
    }
}
