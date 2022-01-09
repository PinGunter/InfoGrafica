//
// Created by salva on 9/1/22.
//

#include <luzAnimada.h>
LuzAnimada::LuzAnimada() {
    Tupla4f ambiente(0.4,0.4,0,0.4);
    Tupla4f especular(0.4,0.4,0,0.4);
    Tupla4f difuso(0.4,0.4,0,0.4);
    posicion = Tupla3f(0,0,0);
    esfera = new Esfera(30,30,20);
    esfera->setMaterial(Material(ambiente,especular,difuso,40));
    luz = new LuzPosicional(posicion,GL_LIGHT2,ambiente,especular,difuso);
    angulo = 0.0f;
    velocidad = 0.7;
}

void LuzAnimada::draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool luz_act) {
    glPushMatrix();
        glRotatef(angulo,0,1,0);
        glTranslatef(100,100,100);
        if (luz_act)
            luz->activar();
        esfera->draw(diferido,ajedrez,modo,true);
    glPopMatrix();
}

void LuzAnimada::animar() {
    angulo += velocidad;
}
