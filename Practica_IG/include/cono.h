//
// Created by pingo on 26/10/21.
//

#ifndef PRACTICA_IG_CONO_H
#define PRACTICA_IG_CONO_H
#include <objrevolucion.h>

class Cono : public ObjRevolucion {
private:
    Tupla3f rectaGeneradoraPerfil(const Tupla3f &a, const Tupla3f &b, const float &x);
    void generarPerfil(float h, float r, int n);
    void crearTapas(bool inf, bool sup, int num_instancias) override;

    float altura;
    float radio;
    bool tapa;

public:
    Cono(int num_vert_perfil = 2, int num_instancias_perf = 20, float h = 1.0, float r = 1.0, bool t = true);
};


#endif//PRACTICA_IG_CONO_H
