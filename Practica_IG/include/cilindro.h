//
// Created by pingo on 26/10/21.
//

#ifndef PRACTICA_IG_CILINDRO_H
#define PRACTICA_IG_CILINDRO_H
#include <objrevolucion.h>

class Cilindro : public ObjRevolucion {
private:
    void generarPerfil(float h, float r, int n);
    float altura;
    float radio;

public:
    Cilindro(int num_vert_perfil = 2, int num_instancias_perf = 20, float h = 1.0, float r = 1.0, bool t_inf = true, bool t_sup = true, Eje_rotacion eje = Eje_rotacion::EJE_Y);
};


#endif//PRACTICA_IG_CILINDRO_H
