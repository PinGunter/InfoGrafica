//
// Created by salva on 11/12/21.
//

#ifndef PRACTICA_IG_CUERPO_HUESO_CABEZA_H
#define PRACTICA_IG_CUERPO_HUESO_CABEZA_H

#include <cuerpo_hueso.h>
#include <cabeza.h>
class Cuerpo_hueso_cabeza {
    Cuerpo_hueso * cuerpo_hueso = nullptr;
    Cabeza * cabeza = nullptr;

public:
    Cuerpo_hueso_cabeza();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool dibuja_cabeza);
};


#endif//PRACTICA_IG_CUERPO_HUESO_CABEZA_H
