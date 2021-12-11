//
// Created by salva on 11/12/21.
//

#include <cuerpo_hueso_cabeza.h>
Cuerpo_hueso_cabeza::Cuerpo_hueso_cabeza() {
    cabeza = new Cabeza();
    cuerpo_hueso = new Cuerpo_hueso();
}

void Cuerpo_hueso_cabeza::draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool dibuja_cabeza) {
    glPushMatrix();
    cuerpo_hueso->draw(diferido,ajedrez,modo);
    if (dibuja_cabeza) {
        glPushMatrix();
        glTranslatef(0, 4.5, 0);
        cabeza->draw(diferido, ajedrez, modo);
        glPopMatrix();
    }
    glPopMatrix();
}
