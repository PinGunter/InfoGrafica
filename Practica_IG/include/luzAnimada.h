//
// Created by salva on 9/1/22.
//

#ifndef PRACTICA_IG_LUZANIMADA_H
#define PRACTICA_IG_LUZANIMADA_H

#include <luz_posicional.h>
#include <esfera.h>
class LuzAnimada {
    Esfera * esfera = nullptr;
    LuzPosicional * luz = nullptr;
    float angulo;
    float velocidad;
    Tupla3f posicion;
public:
    LuzAnimada();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo);

    void animar();
};


#endif//PRACTICA_IG_LUZANIMADA_H
