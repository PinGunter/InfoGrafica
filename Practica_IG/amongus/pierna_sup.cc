//
// Created by salva on 10/12/21.
//

#include <pierna_sup.h>
Pierna_sup::Pierna_sup() {
    std::vector<Tupla3f> perfil{
            Tupla3f(1, -0.5, 0),
            Tupla3f(1, 0.5, 0),
    };
    cilindro = new ObjRevolucion (perfil, Eje_rotacion::EJE_Y, 10);
}
void Pierna_sup::draw(bool ajedrez, ModoVisualizacion modo) {
    glPushMatrix();
    glScalef(1.8,1.8,1.8);
    cilindro->draw(true,ajedrez,modo,false);
    glPopMatrix();
}
