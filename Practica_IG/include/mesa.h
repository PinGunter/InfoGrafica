//
// Created by pingo on 19/12/21.
//

#ifndef PRACTICA_IG_MESA_H
#define PRACTICA_IG_MESA_H

#include <cubo.h>
#include <tetraedro.h>
#include <objrevolucion.h>
#include <objply.h>
#include <luz_posicional.h>
#include <cilindro.h>

class Mesa {
    Cubo * pata = nullptr;
    Cilindro * tabla = nullptr;
    ObjRevolucion * peon = nullptr;
    ObjRevolucion * peonX = nullptr;
    ObjRevolucion * peonZ = nullptr;
    Tetraedro * tetraedro = nullptr;
    ObjPLY * bombilla = nullptr;

public:
    LuzPosicional * luz = nullptr;
    Mesa();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool tapas);
};


#endif//PRACTICA_IG_MESA_H
