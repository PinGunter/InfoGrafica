//
// Created by salva on 10/12/21.
//
#include <objrevolucion.h>
#ifndef PRACTICA_IG_SEMIESFERA_H
#define PRACTICA_IG_SEMIESFERA_H


class Semiesfera : public ObjRevolucion {
    float radio;
    void generarPerfil(float radio, int n);
public:
    Semiesfera(int num_vert_perfil = 10, int num_instancias_perf = 20, float r = 1.0, Eje_rotacion eje = Eje_rotacion::EJE_Y);

};


#endif//PRACTICA_IG_SEMIESFERA_H
