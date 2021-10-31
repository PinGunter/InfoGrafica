//
// Created by pingo on 26/10/21.
//

#include "Cono.h"
Tupla3f Cono::rectaGeneradoraPerfil(const Tupla3f &a, const Tupla3f &b, const float &x) {
    float y;
    y = (((x-a(0))*(b(1)-a(1)))/(b(0)-a(0))) + a(1);
    return Tupla3f(x,y,0);
}

void Cono::generarPerfil(float h, float r, int n) {
    Tupla3f a(0,h,0),b(r,0,0);
    float distancia = r / (n-1);
    for (int i=0; i < n; i++){
        perfil_original.push_back(rectaGeneradoraPerfil(a,b,i*distancia));
    }
    for (auto e: perfil_original){
        std::cout << e << std::endl;
    }
}

Cono::Cono(int num_vert_perfil, int num_instancias_perf, float h, float r, bool t) {
    altura = h;
    radio = r;
    tapa = t;
    generarPerfil(altura,radio,num_vert_perfil);
    normalizarPerfil();
    crearVertices(perfil_original,num_instancias_perf);
    offset_tapas = 0;
    crearMalla(perfil_original,num_instancias_perf, t, true);
    init();
}
