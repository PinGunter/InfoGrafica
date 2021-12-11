//
// Created by salva on 11/12/21.
//

#ifndef PRACTICA_IG_CABEZA_H
#define PRACTICA_IG_CABEZA_H

#include <semiesfera.h>
class Cabeza {
    Semiesfera * semiesfera = nullptr;

public:
    Cabeza();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo);
};


#endif//PRACTICA_IG_CABEZA_H
