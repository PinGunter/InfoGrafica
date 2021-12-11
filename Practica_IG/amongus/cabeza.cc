//
// Created by salva on 11/12/21.
//

#include <cabeza.h>
Cabeza::Cabeza() {
    semiesfera = new Semiesfera(100,100);
}

void Cabeza::draw(bool diferido, bool ajedrez, ModoVisualizacion modo) {
    glPushMatrix();
    glScalef(5,3.6,5);
    semiesfera->draw(diferido,ajedrez,modo,true);
    glPopMatrix();
}
