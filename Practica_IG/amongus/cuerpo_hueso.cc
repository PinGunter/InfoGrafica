//
// Created by salva on 11/12/21.
//

#include <cuerpo_hueso.h>
Cuerpo_hueso::Cuerpo_hueso() {
    cuerpo = new Cuerpo();
    hueso = new Hueso();
}

void Cuerpo_hueso::draw(bool diferido, bool ajedrez, ModoVisualizacion modo) {
    glPushMatrix();
    cuerpo->draw(diferido,ajedrez,modo);
    glPushMatrix();
    glTranslatef(0,3.6,0);
    hueso->draw(diferido,ajedrez,modo);
    glPopMatrix();
    glPopMatrix();
}
