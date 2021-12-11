//
// Created by salva on 11/12/21.
//

#include <mochila.h>
Mochila::Mochila() {
    cubo = new Cubo();
    cubo->setMaterial(Material(Tupla4f (1,0,0,1), Tupla4f (0.5,0,0,1), Tupla4f (1,0,0,1), 124));
}

void Mochila::draw(bool diferido, bool ajedrez, ModoVisualizacion modo) {
    glPushMatrix();
    glScalef(8,8,3.6);
    cubo->draw(diferido,ajedrez,modo);
    glPopMatrix();
}
