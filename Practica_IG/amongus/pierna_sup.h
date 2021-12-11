//
// Created by salva on 10/12/21.
//

#ifndef PRACTICA_IG_PIERNA_SUP_H
#define PRACTICA_IG_PIERNA_SUP_H
#include <objrevolucion.h>

class Pierna_sup {
    ObjRevolucion * cilindro = nullptr;

public:
    Pierna_sup();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo);
};


#endif//PRACTICA_IG_PIERNA_SUP_H
