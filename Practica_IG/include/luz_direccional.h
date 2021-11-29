//
// Created by salva on 9/11/21.
//

#ifndef PRACTICA_IG_LUZ_DIRECCIONAL_H
#define PRACTICA_IG_LUZ_DIRECCIONAL_H
#include <luz.h>

class LuzDireccional : public Luz{
    float alpha;
    float beta;
public:
    LuzDireccional(const Tupla2f & direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);
    void variarAnguloAlpha(float incremento);
    void variarAnguloBeta(float incremento);
    void calcularPosicion(float a, float b);
};


#endif//PRACTICA_IG_LUZ_DIRECCIONAL_H
