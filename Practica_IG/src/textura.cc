//
// Created by salva on 21/12/21.
//

#include <textura.h>
Textura::Textura(std::string archivo) {
    jpg::Imagen * pimg = NULL;
    pimg = new jpg::Imagen(archivo);

    width = pimg->tamX();
    height = pimg->tamY();
    unsigned char * temp = pimg->leerPixels();
    for (int i=0; i < width*height*3; i++){
        data.push_back(temp[i]);
    }

    glGenTextures(1,&textura_id);
}

void Textura::activar() {
    glBindTexture(GL_TEXTURE_2D, textura_id);

    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}