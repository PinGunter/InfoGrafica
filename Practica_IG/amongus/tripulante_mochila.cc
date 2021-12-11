//
// Created by salva on 11/12/21.
//

#include <tripulante_mochila.h>
Tripulante_mochila::Tripulante_mochila() {
    tripulante = new Tripulante();
    mochila = new Mochila();
}

void Tripulante_mochila::draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool cabeza) {
    glPushMatrix();
    tripulante->draw(diferido,ajedrez,modo,cabeza);
    glPushMatrix();
    glTranslatef(0,1.4,-5);
    mochila->draw(diferido,ajedrez,modo);
    glPopMatrix();
    glPopMatrix();
}
