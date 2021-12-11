//
// Created by salva on 11/12/21.
//

#ifndef PRACTICA_IG_TRIPULANTE_MOCHILA_H
#define PRACTICA_IG_TRIPULANTE_MOCHILA_H

#include <tripulante.h>
#include <mochila.h>

class Tripulante_mochila {
    Tripulante * tripulante = nullptr;
    Mochila * mochila = nullptr;

public:
    Tripulante_mochila();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool cabeza);
};


#endif//PRACTICA_IG_TRIPULANTE_MOCHILA_H
