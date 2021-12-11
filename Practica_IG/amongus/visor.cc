//
// Created by salva on 11/12/21.
//

#include <visor.h>
Visor::Visor() {
    esfera = new Esfera(20,20);
    esfera->setMaterial(Material(Tupla4f(0.64,0.82,0.98,1),Tupla4f(0.74,0.92,1,1),Tupla4f(0.64,0.82,0.98,1),128));
}

void Visor::draw(bool diferido, bool ajedrez, ModoVisualizacion modo) {
    glPushMatrix();
    glScalef(3,1.2,1.2);
    esfera->draw(diferido,ajedrez,modo,true);
    glPopMatrix();
}
