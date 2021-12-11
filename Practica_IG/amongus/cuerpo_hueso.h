//
// Created by salva on 11/12/21.
//

#ifndef PRACTICA_IG_CUERPO_HUESO_H
#define PRACTICA_IG_CUERPO_HUESO_H

#include <cuerpo.h>
#include <hueso.h>
class Cuerpo_hueso {
    Cuerpo * cuerpo = nullptr;
    Hueso * hueso = nullptr;

public:
    Cuerpo_hueso();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo);
};


#endif//PRACTICA_IG_CUERPO_HUESO_H
