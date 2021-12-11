//
// Created by salva on 11/12/21.
//

#ifndef PRACTICA_IG_HUESO_H
#define PRACTICA_IG_HUESO_H

#include <objply.h>
class Hueso {
    ObjPLY * hueso = nullptr;

public:
    Hueso();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo);
};


#endif//PRACTICA_IG_HUESO_H
