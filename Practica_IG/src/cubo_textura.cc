//
// Created by salva on 11/1/22.
//

#include <cubo_textura.h>
Cubo_textura::Cubo_textura(std::string archivo_tex, float l) {
    textura = new Textura(archivo_tex);
    angulo = 0;
    velocidad = 0.3;
    float arista = l/2;
    //tabla de vertices (con vertices duplicados para las texturas)
    v.push_back(Tupla3f(-arista,arista,-arista)); //0
    v.push_back(Tupla3f(-arista,-arista,-arista)); // 1
    v.push_back(Tupla3f(arista,arista,-arista)); // 2
    v.push_back(Tupla3f(arista,-arista,-arista)); // 3
    v.push_back(Tupla3f(-arista,-arista,arista)); // 4
    v.push_back(Tupla3f(arista,-arista,arista)); // 5
    v.push_back(Tupla3f(-arista,arista,arista)); // 6
    v.push_back(Tupla3f(arista,arista,arista)); // 7
    v.push_back(Tupla3f(-arista,arista,-arista)); // 8
    v.push_back(Tupla3f(arista,arista,-arista)); // 9
    v.push_back(Tupla3f(-arista,arista,-arista)); // 1-arista
    v.push_back(Tupla3f(-arista,arista,arista)); // 11
    v.push_back(Tupla3f(arista,arista,-arista)); // 12
    v.push_back(Tupla3f(arista,arista,arista)); // 13

    //tabla de caras
    f.push_back(Tupla3i(0,2,1));
    f.push_back(Tupla3i(1,2,3));
    f.push_back(Tupla3i(4,5,6));
    f.push_back(Tupla3i(5,7,6));
    f.push_back(Tupla3i(6,7,8));
    f.push_back(Tupla3i(7,9,8));
    f.push_back(Tupla3i(1,3,4));
    f.push_back(Tupla3i(3,5,4));
    f.push_back(Tupla3i(1,11,10));
    f.push_back(Tupla3i(1,4,11));
    f.push_back(Tupla3i(3,12,5));
    f.push_back(Tupla3i(5,12,13));

    //coordenadas de textura
    ct.push_back(Tupla2f(0,0.33)); // 0
    ct.push_back(Tupla2f(0.25,0.33)); // 1
    ct.push_back(Tupla2f(0,0.66)); // 2
    ct.push_back(Tupla2f(0.25,0.66)); // 3
    ct.push_back(Tupla2f(0.5,0.33)); // 4
    ct.push_back(Tupla2f(0.5,0.66)); // 5
    ct.push_back(Tupla2f(0.75,0.33)); // 6
    ct.push_back(Tupla2f(0.75,0.66)); // 7
    ct.push_back(Tupla2f(1,0.33)); // 8
    ct.push_back(Tupla2f(1,0.66)); // 9
    ct.push_back(Tupla2f(0.25,0)); // 10
    ct.push_back(Tupla2f(0.5,0)); // 11
    ct.push_back(Tupla2f(0.25,1)); // 12
    ct.push_back(Tupla2f(0.5,1)); // 13

    Tupla4f ambiente (1,1,1,1);
    Tupla4f especular (1,1,1,1);
    Tupla4f difuso (1, 1,1,1);
    inicializar(Tupla3f(1, 1,1),
                Tupla3f(1, 1,1),
                Tupla3f(1, 1,1),
                Tupla3f(1, 0.24, 0.71), ambiente, especular, difuso, 128);

}
void Cubo_textura::animar() {
    angulo += velocidad;
}

void Cubo_textura::draw(bool dibuja_diferido, bool ajedrez, ModoVisualizacion modo) {
    glPushMatrix();
    glRotatef(angulo,0,1,0);
    Malla3D::draw(dibuja_diferido,ajedrez,modo);
    glPopMatrix();
}
