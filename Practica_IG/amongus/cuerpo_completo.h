//
// Created by salva on 11/12/21.
//

#ifndef PRACTICA_IG_CUERPO_COMPLETO_H
#define PRACTICA_IG_CUERPO_COMPLETO_H

#include <cuerpo_hueso_cabeza.h>
#include <visor.h>
class Cuerpo_completo {
    Cuerpo_hueso_cabeza * cuerpo = nullptr;
    Visor * visor = nullptr;

public:
    Cuerpo_completo();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool cabeza);
};


#endif//PRACTICA_IG_CUERPO_COMPLETO_H
