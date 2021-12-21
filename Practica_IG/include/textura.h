//
// Created by salva on 21/12/21.
//

#ifndef PRACTICA_IG_TEXTURA_H
#define PRACTICA_IG_TEXTURA_H

#include <aux.h>
#include <jpg_imagen.hpp>
class Textura {
    GLuint textura_id = 0;
    std::vector<unsigned char> data;
    int width, height;

public:
    Textura(std::string archivo);

    void activar();
};


#endif//PRACTICA_IG_TEXTURA_H
