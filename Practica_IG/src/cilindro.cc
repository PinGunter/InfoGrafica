//
// Created by pingo on 26/10/21.
//

#include <cilindro.h>
void cilindro::generarPerfil(float h, float r, int n) {
    float distancia = h / (n - 1);
    for (int i = 0; i < n; i++) {
        perfil_original.push_back(Tupla3f(r, i * distancia, 0));
    }
}

cilindro::cilindro(int num_vert_perfil, int num_instancias_perf, float h, float r, bool t_inf, bool t_sup) {
    altura = h;
    radio = r;
    generarPerfil(altura, radio, num_vert_perfil);
    normalizarPerfil();
    crearVertices(perfil_original, num_instancias_perf);
    crearMalla(perfil_original, num_instancias_perf, t_inf, t_sup);

    init();
}