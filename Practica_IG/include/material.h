//
// Created by salva on 9/11/21.
//

#ifndef PRACTICA_IG_MATERIAL_H
#define PRACTICA_IG_MATERIAL_H
#include <aux.h>


class Material {
private:
    Tupla4f ambiente, especular, difuso;
    float brillo;
public:
    void aplicar();
    Material();
    Material(Tupla4f ambiente, Tupla4f especular, Tupla4f difuso, float brillo);
};


#endif//PRACTICA_IG_MATERIAL_H
