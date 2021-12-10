//
// Created by salva on 10/12/21.
//

#include "semiesfera.h"
void Semiesfera::generarPerfil(float radio, int n) {
    float incremento = (M_PI/2.0) / n;
    float x = 0, y = 0;
    for (int i=0; i < n; i++) {
        x = radio * cos(i * incremento);
        y = radio * sin(i * incremento);
        perfil_original.push_back(Tupla3f(x,y,0));
    }
}

Semiesfera::Semiesfera(int num_vert_perfil, int num_instancias_perf, float r, Eje_rotacion eje) {
    mi_eje = eje;
    radio = r;
    generarPerfil(radio, num_vert_perfil);
    normalizarPerfil();
    offset_tapas = 0;
    crearMalla(perfil_original, num_instancias_perf,true,true);
    init();
}
