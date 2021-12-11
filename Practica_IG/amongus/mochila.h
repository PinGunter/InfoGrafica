//
// Created by salva on 11/12/21.
//

#ifndef PRACTICA_IG_MOCHILA_H
#define PRACTICA_IG_MOCHILA_H

#include <cubo.h>
class Mochila {
    Cubo * cubo = nullptr;
public:
    Mochila();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo);
};


#endif//PRACTICA_IG_MOCHILA_H
