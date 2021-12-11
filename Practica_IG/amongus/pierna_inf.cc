//
// Created by salva on 10/12/21.
//

#include <pierna_inf.h>

Pierna_inf::Pierna_inf() {
    std::vector<Tupla3f> perfil{
            Tupla3f(0.5, -0.5, 0),
            Tupla3f(0.5, 0.5, 0),
    };
    cilindro = new ObjRevolucion (perfil, Eje_rotacion::EJE_Y, 100);
    semiesfera = new Semiesfera(100,100);
}

void Pierna_inf::draw(bool diferido, bool ajedrez, ModoVisualizacion modo) {
    glPushMatrix();
        glScalef(1.8,1.8,1.8);
        cilindro->draw(diferido,ajedrez,modo,false);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,-0.89,0);
        glRotatef(180,1,0,0);
        glScalef(0.9,0.3,0.9);
        semiesfera->draw(diferido,ajedrez,modo,true);
    glPopMatrix();
}
