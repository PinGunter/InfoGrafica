//
// Created by salva on 9/11/21.
//

#ifndef PRACTICA_IG_LUZ_POSICIONAL_H
#define PRACTICA_IG_LUZ_POSICIONAL_H
#include <luz.h>
#include <aux.h>

class LuzPosicional: public Luz {
public:
    LuzPosicional(const Tupla3f & posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);
};


#endif//PRACTICA_IG_LUZ_POSICIONAL_H
