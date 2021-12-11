//
// Created by salva on 11/12/21.
//

#include <cuerpo_completo.h>
Cuerpo_completo::Cuerpo_completo() {
    cuerpo = new Cuerpo_hueso_cabeza;
    visor = new Visor();
}

void Cuerpo_completo::draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool cabeza) {
    glPushMatrix();
    cuerpo->draw(diferido,ajedrez,modo,cabeza);
    glPushMatrix();
    glTranslatef(0,3,4.4);
    glScalef(1.2,1.2,1.2);
    visor->draw(diferido,ajedrez,modo);
    glPopMatrix();
    glPopMatrix();
}
