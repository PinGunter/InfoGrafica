//
// Created by salva on 11/12/21.
//

#include "tripulante.h"
Tripulante::Tripulante() {
    pierna = new Pierna();
    cuerpo = new Cuerpo_completo();
}
void Tripulante::draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool cabeza) {
    glPushMatrix();
    glPushMatrix();
    glTranslatef(-2.9,-6.7,0);
    pierna->draw(diferido, ajedrez, modo,0, 0, 0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2.9,-6.7,0);
    pierna->draw(diferido, ajedrez, modo,0, 0, 0);
    glPopMatrix();
    cuerpo->draw(diferido,ajedrez,modo,cabeza);
    glPopMatrix();
}
