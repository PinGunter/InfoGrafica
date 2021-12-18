//
// Created by salva on 10/12/21.
//

#ifndef PRACTICA_IG_PIERNA_H
#define PRACTICA_IG_PIERNA_H

#include <pierna_inf.h>
#include <pierna_sup.h>
#include <esfera.h>
class Pierna {
    Pierna_inf * p_inf = nullptr;
    Pierna_sup * p_sup = nullptr;
    Esfera * esfera = nullptr;

public:
    Pierna();
    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo, float alpha, float beta, float gamma, float phi);
};


#endif//PRACTICA_IG_PIERNA_H
