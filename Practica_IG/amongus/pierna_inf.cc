//
// Created by salva on 10/12/21.
//

#include <pierna_inf.h>

Pierna_inf::Pierna_inf() {
    std::vector<Tupla3f> perfil{
            Tupla3f(1, -0.5, 0),
            Tupla3f(1, 0.5, 0),
    };
    cilindro = new ObjRevolucion (perfil, Eje_rotacion::EJE_Y, 10);
    semiesfera = new Semiesfera();
}

void Pierna_inf::draw(bool ajedrez, ModoVisualizacion modo) {
    glPushMatrix();
        glScalef(1.8,1.8,1.8);
        cilindro->draw(true,ajedrez,modo,false);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,-0.9,0);
        glRotatef(180,1,0,0);
        glScalef(1.8,0.3,1.8);
        semiesfera->draw(true,ajedrez,modo,true);
    glPopMatrix();
}
