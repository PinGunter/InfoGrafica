//
// Created by pingo on 19/12/21.
//

#ifndef PRACTICA_IG_PIEDRA_H
#define PRACTICA_IG_PIEDRA_H

#include <tetraedro.h>
#include <malla.h>
class Piedras {
    Tetraedro * p1 = nullptr;
    std::vector<float> rotaciones;
public:
    Piedras();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo);
};


#endif//PRACTICA_IG_PIEDRA_H
