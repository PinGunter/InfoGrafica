//
// Created by salva on 11/12/21.
//

#include <cuerpo.h>
Cuerpo::Cuerpo() {
    std::vector<Tupla3f> perfil{
            Tupla3f(1, -0.5, 0),
            Tupla3f(1, 0.5, 0),
    };
    cilindro = new ObjRevolucion (perfil, Eje_rotacion::EJE_Y, 100,true,true);
}
void Cuerpo::draw(bool diferido, bool ajedrez, ModoVisualizacion modo) {
    glPushMatrix();
    glScalef(5,10,5);
    cilindro->draw(diferido,ajedrez,modo,true);
    glPopMatrix();
}
