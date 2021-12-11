//
// Created by salva on 9/11/21.
//

#include <luz.h>

void Luz::activar() {
    glEnable(id);
    glLightfv(id,GL_DIFFUSE,colorDifuso);
    glLightfv(id,GL_AMBIENT,colorAmbiente);
    glLightfv(id,GL_SPECULAR,colorEspecular);
    glLightfv(id,GL_POSITION,posicion);
    activada = true;
}
void Luz::desactivar() {
    glDisable(id);
    activada = false;
}
bool Luz::getActivada() const {
    return activada;
}