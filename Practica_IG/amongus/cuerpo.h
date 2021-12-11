//
// Created by salva on 11/12/21.
//

#ifndef PRACTICA_IG_CUERPO_H
#define PRACTICA_IG_CUERPO_H

#include <objrevolucion.h>
class Cuerpo {
    ObjRevolucion * cilindro = nullptr;

public:
    Cuerpo();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo);
};


#endif//PRACTICA_IG_CUERPO_H
