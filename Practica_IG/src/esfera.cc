//
// Created by pingo on 26/10/21.
//

#include <esfera.h>

void esfera::generarPerfil(float radio, int n) {
    float x, y;
    for (int i = 0; i < n; i++) {
        x = radio * cos(2 * M_PI * i / n);
        y = radio * sin(2 * M_PI * i / n);
        perfil_original.push_back(Tupla3f(x, y, 0));
    }
}


esfera::esfera(int num_vert_perfil, int num_instancias_perf, float r) {
    radio = r;
    generarPerfil(radio, num_vert_perfil);
    normalizarPerfil();
    crearVertices(perfil_original, num_instancias_perf);
    crearMalla(perfil_original, num_instancias_perf);
    init();
    offset_tapas = f.size();
}
void esfera::crearMalla(const std::vector<Tupla3f> &perfil_original, const int num_instancias_perf) {
    ObjRevolucion::crearMalla(perfil_original, num_instancias_perf, false, false);
}
