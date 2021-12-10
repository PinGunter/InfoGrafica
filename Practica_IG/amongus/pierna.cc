//
// Created by salva on 10/12/21.
//

#include <pierna.h>
Pierna::Pierna() {
    p_inf = new Pierna_inf();
    p_sup = new Pierna_sup();
    esfera = new Esfera();
}
void Pierna::draw(bool ajedrez, ModoVisualizacion modo, float alpha, float beta, float gamma) {
    glPushMatrix();
    glRotatef(gamma,0,0,1);
    glRotatef(alpha,0,1,0);
    glScalef(2,1,2);
        glPushMatrix();
        glRotatef(beta,1,0,0);
        glTranslatef(0,-0.9,0);
        p_inf->draw(ajedrez,modo);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0.9,0);
        p_sup->draw(ajedrez,modo);
        glPopMatrix();

        glPushMatrix();
        glScalef(2,0.6,2);
        esfera->draw(true,ajedrez,modo,true);
        glPopMatrix();
    glPopMatrix();
}
