//
// Created by pingo on 19/12/21.
//

#include <mesa.h>
Mesa::Mesa() {
    pata = new Cubo();
    tabla = new Cilindro();
    tetraedro = new Tetraedro(1.2);
    peon = new ObjRevolucion("plys/peon",Eje_rotacion::EJE_Y,20);
    peonX = new ObjRevolucion("plys/peon_rotadoX",Eje_rotacion::EJE_X,20);
    peonZ = new ObjRevolucion("plys/peon_rotadoZ",Eje_rotacion::EJE_Z,20);
    Tupla4f ambiente(0.64,0.2,1,1);
    Tupla4f especular(0.64,0.2,1,1);
    Tupla4f difuso(0.64,0.2,1,1);


    bombilla = new ObjPLY("plys/bombilla");
    bombilla->setMaterial(Material(ambiente,especular,difuso,128));

    luz = new LuzPosicional(Tupla3f(0,0,0),GL_LIGHT0,ambiente,especular,difuso);
    Material m (Tupla4f(0.7,0.7,0.7,0.6), Tupla4f(0,0,0,0), Tupla4f(0.7,0.7,0.7,1), 20);

    Material m_peon(Tupla4f(0,1,0,1),Tupla4f(0,0.5,0,1),Tupla4f(0,1,0,1),40);
    Material m_peon2(Tupla4f(0,1,1,1),Tupla4f(0,0.5,0.5,1),Tupla4f(0,1,1,1),40);
    Material m_peon3(Tupla4f(1,1,0,1),Tupla4f(0.5,0.5,0,1),Tupla4f(1,1,0,1),40);
    Material m_tetra(Tupla4f(1,0,0,1),Tupla4f(0.5,0,0,1),Tupla4f(1,0,0,1),40);

    pata->setMaterial(m);
    tabla->setMaterial(m);
    peon->setMaterial(m_peon);
    peonX->setMaterial(m_peon2);
    peonZ->setMaterial(m_peon3);
    tetraedro->setMaterial(m_tetra);
}
void Mesa::draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool tapas) {
    glPushMatrix();
       glScalef(10,10,10);

        glPushMatrix();
            glTranslatef(0,7,0);
            glPushMatrix();
                glRotatef(180,1,0,0);
                glScalef(20,20,20);
                    bombilla->draw(diferido,ajedrez,modo);
                glPopMatrix();
            if (luz->getActivada())
                luz->activar();
        glPopMatrix();

        glPushMatrix();
            glScalef(1,5,1);
            pata->draw(diferido,ajedrez,modo);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,2.5,0);
            glScalef(5,0.4,5);
            tabla->draw(diferido,ajedrez,modo,tapas);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(4,4.35,0);
            peon->draw(diferido,ajedrez,modo,tapas);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-3.5,3.7,0);
            glRotatef(10,0,0,1);
            peonX->draw(diferido,ajedrez,modo,tapas);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,3.7,3.7);
            glRotatef(10,1,0,0);
            peonZ->draw(diferido,ajedrez,modo,tapas);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,4.3,-4);
        tetraedro->draw(diferido,ajedrez,modo);
        glPopMatrix();

    glPopMatrix();
}
