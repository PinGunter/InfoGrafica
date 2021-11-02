//
// Created by pingo on 26/10/21.
//

#include "cono.h"
Tupla3f Cono::rectaGeneradoraPerfil(const Tupla3f &a, const Tupla3f &b, const float &x) {
    float y;
    y = (((x - a(0)) * (b(1) - a(1))) / (b(0) - a(0))) + a(1);
    return Tupla3f(x, y, 0);
}

void Cono::generarPerfil(float h, float r, int n) {
    Tupla3f a(0, h, 0), b(r, 0, 0);
    float distancia = r / (n - 1);
    for (int i = 0; i < n; i++) {
        perfil_original.push_back(rectaGeneradoraPerfil(a, b, i * distancia));
    }
}

Cono::Cono(int num_vert_perfil, int num_instancias_perf, float h, float r, bool t, Eje_rotacion eje) {
    std::cout << "Soy cono " << std::endl;
    mi_eje = eje;
    altura = h;
    radio = r;
    tapa = t;
    generarPerfil(altura, radio, num_vert_perfil);
    normalizarPerfil();
    crearMalla(perfil_original, num_instancias_perf, t, true);
    init();
}
void Cono::crearTapas(bool inf, bool sup, int num_instancias) {
    int a, b;
    int n_tri_pretapa;

    v.push_back(vt_sup);
    for (int i = 0; i < num_instancias; i++) {
        a = perfil_original.size() * i + perfil_original.size() - 1;
        b = perfil_original.size() * ((i + 1) % num_instancias) + perfil_original.size() - 1;
        f.push_back(Tupla3i(a, b, v.size() - 1));
    }
    n_tri_pretapa = f.size();

    if (inf){
        v.push_back(vt_inf);
        for (int i=0; i < num_instancias; i++){
            a = perfil_original.size()*i;
            b = perfil_original.size()*((i+1) % num_instancias);
            f.push_back(Tupla3i(b,a,v.size()-1));

        }
    }
    offset_tapas = n_tri_pretapa;
}
