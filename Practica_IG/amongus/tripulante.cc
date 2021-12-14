//
// Created by salva on 11/12/21.
//

#include <tripulante.h>
Tripulante::Tripulante() {
    pierna = new Pierna();
    cuerpo = new Cuerpo_completo();
}
void Tripulante::draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool cabeza, Tupla3f giroIzda, Tupla3f giroDcha) {
    glPushMatrix();
    glPushMatrix();
    glTranslatef(-2.9,-5.3,0);
    pierna->draw(diferido, ajedrez, modo,giroIzda(0),giroIzda(1),giroIzda(2));
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2.9,-5.3,0);
    pierna->draw(diferido, ajedrez, modo,giroDcha(0),giroDcha(1),giroDcha(2));
    glPopMatrix();
    cuerpo->draw(diferido,ajedrez,modo,cabeza);
    glPopMatrix();
}
