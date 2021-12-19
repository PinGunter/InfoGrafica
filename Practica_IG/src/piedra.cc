//
// Created by pingo on 19/12/21.
//

#include <piedra.h>
Piedras::Piedras() {
    p1 = new Tetraedro(20);
    Material m (Tupla4f(0.7,0.7,0.7,0.6), Tupla4f(0,0,0,0), Tupla4f(0.7,0.7,0.7,1), 20);
    p1->setMaterial(m);
    srand(1);
    for (int i=0; i < 9; i++){
        rotaciones.push_back(random() % 360);
    }
}

void Piedras::draw(bool diferido, bool ajedrez, ModoVisualizacion modo) {
    glPushMatrix();
    glRotatef(90,1,0,0);
        glPushMatrix();
        glRotatef(rotaciones[0],1,0,0);
        glRotatef(rotaciones[1],0,1,0);
        glRotatef(rotaciones[2],0,0,1);
        glScalef(1,1,1);
        p1->draw(diferido,ajedrez,modo);
        glPopMatrix();

        glPushMatrix();
        glRotatef(rotaciones[3],1,0,0);
        glRotatef(rotaciones[4],0,1,0);
        glRotatef(rotaciones[5],0,0,1);
        glTranslatef(30,10,0);
        glScalef(1.3,1,0.4);
        p1->draw(diferido,ajedrez,modo);
        glPopMatrix();

        glPushMatrix();
        glRotatef(rotaciones[6],1,0,0);
        glRotatef(rotaciones[7],0,1,0);
        glRotatef(rotaciones[8],0,0,1);
        glTranslatef(10,30,0);
        glScalef(0.5,1,1.2);
        p1->draw(diferido,ajedrez,modo);
        glPopMatrix();
    glPopMatrix();
}
