//
// Created by salva on 11/1/22.
//

#ifndef PRACTICA_IG_CUBO_TEXTURA_H
#define PRACTICA_IG_CUBO_TEXTURA_H

#include <malla.h>
class Cubo_textura : public Malla3D {
    float angulo;
    float velocidad;
public:
    Cubo_textura(std::string archivo_tex, float l);
    void animar();
    void draw(bool dibuja_diferido, bool ajedrez, ModoVisualizacion modo);
};


#endif//PRACTICA_IG_CUBO_TEXTURA_H
