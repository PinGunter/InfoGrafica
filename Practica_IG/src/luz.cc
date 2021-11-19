//
// Created by salva on 9/11/21.
//

#include <luz.h>

void Luz::activar() {
    std::cout << "Luz " << id << " activada" << std::endl;
    glEnable(id);
    activada = true;
}
void Luz::desactivar() {
    glDisable(id);
    activada = false;
}
bool Luz::getActivada() const {
    return activada;
}
void Luz::draw() {
    glLightfv(id,GL_DIFFUSE,colorDifuso);
    glLightfv(id,GL_AMBIENT,colorAmbiente);
    glLightfv(id,GL_SPECULAR,colorEspecular);
    glLightfv(id,GL_POSITION,posicion);
}
