//
// Created by salva on 11/12/21.
//

#ifndef PRACTICA_IG_VISOR_H
#define PRACTICA_IG_VISOR_H

#include <esfera.h>
class Visor {
    Esfera * esfera = nullptr;

public:
    Visor();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo);
};


#endif//PRACTICA_IG_VISOR_H
