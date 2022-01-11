//
// Created by salva on 11/1/22.
//

#include <cuadro_textura.h>
Cuadro_textura::Cuadro_textura(std::string tex, int w, int h) {
    textura = new Textura(tex);

    //vertices
    float w_v = w / 2.0;
    float h_v = h / 2.0;

    //vertices
    v.push_back(Tupla3f(-w_v,-h_v,0));
    v.push_back(Tupla3f(w_v,-h_v,0));
    v.push_back(Tupla3f(w_v,h_v,0));
    v.push_back(Tupla3f(-w_v,h_v,0));

    //caras
    f.push_back(Tupla3i(0,1,2));
    f.push_back(Tupla3i(2,3,0));


    //textura
    ct.push_back(Tupla2f(0,1));
    ct.push_back(Tupla2f(1,1));
    ct.push_back(Tupla2f(1,0));
    ct.push_back(Tupla2f(0,0));

    Tupla4f ambiente (1,1,1,1);
    Tupla4f especular (1,1,1,1);
    Tupla4f difuso (1, 1,1,1);
    inicializar(Tupla3f(1, 1,1),
                Tupla3f(1, 1,1),
                Tupla3f(1, 1,1),
                Tupla3f(1, 0.24, 0.71), ambiente, especular, difuso, 128);
}
