//
// Created by salva on 11/12/21.
//

#include <hueso.h>

Hueso::Hueso() {
    hueso = new ObjPLY("plys/hueso");
    hueso->setMaterial(Material(Tupla4f(1,1,1,1), Tupla4f(0.2,0.2,0.2,1), Tupla4f(1,1,1,1), 100));
}

void Hueso::draw(bool diferido, bool ajedrez, ModoVisualizacion modo) {
    glPushMatrix();
    glScalef(5,5,5);
    glScalef(0.33,0.29,0.33);
    hueso->draw(diferido,ajedrez,modo);
    glPopMatrix();
}
