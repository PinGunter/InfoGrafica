//
// Created by salva on 9/1/22.
//

#ifndef PRACTICA_IG_LUZANIMADA_H
#define PRACTICA_IG_LUZANIMADA_H

#include <luz_posicional.h>
#include <esfera.h>
class LuzAnimada {
    Esfera * esfera = nullptr;
    float angulo;
    float velocidad;
    Tupla3f posicion;
public:
    LuzPosicional * luz = nullptr;
    LuzAnimada();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool luz_act);

    void animar();
};


#endif//PRACTICA_IG_LUZANIMADA_H
