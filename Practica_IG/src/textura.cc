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
    for (int i=0; i < width*height; i++){
        data.push_back(temp[i]);
    }
    delete temp;

    glGenTextures(1,&textura_id);
    glBindTexture(GL_TEXTURE_2D,textura_id);
}
