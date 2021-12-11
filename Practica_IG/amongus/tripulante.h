//
// Created by salva on 11/12/21.
//

#ifndef PRACTICA_IG_TRIPULANTE_H
#define PRACTICA_IG_TRIPULANTE_H

#include <pierna.h>
#include <cuerpo_completo.h>

class Tripulante {
    Pierna * pierna = nullptr;
    Cuerpo_completo * cuerpo = nullptr;

public:
    Tripulante();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool cabeza);
};


#endif//PRACTICA_IG_TRIPULANTE_H
