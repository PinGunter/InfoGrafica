//
// Created by pingo on 26/10/21.
//

#include <esfera.h>

void Esfera::generarPerfil(float radio, int n) {
    float x, y;
    float angulo_base = 3*M_PI/2;
    std::cout << "perfil esfera " << std::endl;
    for (int i = 0; i < n; i++) {
        x = radio * cos(M_PI / 2 - i * M_PI / n);
        y = radio * sin(M_PI / 2 - i * M_PI / n);
        perfil_original.insert(perfil_original.begin(),Tupla3f(x, y, 0));
        std::cout << x << " " << y << " "  << 0 << std::endl;
    }
}


Esfera::Esfera(int num_vert_perfil, int num_instancias_perf, float r, Eje_rotacion eje) {
    mi_eje = eje;
    radio = r;
    generarPerfil(radio, num_vert_perfil);
//    normalizarPerfil();
    crearMalla(perfil_original, num_instancias_perf);
    init();
    offset_tapas = f.size();
}
void Esfera::crearMalla(const std::vector<Tupla3f> &perfil_original, const int num_instancias_perf) {
    ObjRevolucion::crearMalla(perfil_original, num_instancias_perf, true, true);
}
