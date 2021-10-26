//
// Created by pingo on 26/10/21.
//

#ifndef PRACTICA_IG_ESFERA_H
#define PRACTICA_IG_ESFERA_H
#include <objrevolucion.h>

class Esfera : public ObjRevolucion{
private:
    float radio;
public:
    Esfera(int num_vert_perfil = 10, int num_instancias_perf = 20, float r = 1.0);
};


#endif//PRACTICA_IG_ESFERA_H
