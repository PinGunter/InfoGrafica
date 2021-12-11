//
// Created by salva on 10/12/21.
//
#include <semiesfera.h>
#include <cilindro.h>
#ifndef PRACTICA_IG_PIERNA_INF_H
#define PRACTICA_IG_PIERNA_INF_H


class Pierna_inf {
private:
    ObjRevolucion * cilindro = nullptr;
    Semiesfera * semiesfera = nullptr;
public:
    Pierna_inf();
    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo);
};


#endif//PRACTICA_IG_PIERNA_INF_H
