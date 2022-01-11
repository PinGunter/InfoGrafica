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
        data1.push_back(temp[i]);
    }
    data = pimg->leerPixels();

    textura_id = -1;
}

void Textura::activar() {
    glEnable(GL_TEXTURE_2D);
    if (textura_id == -1){
        glGenTextures(1,&textura_id);
    }
    glBindTexture(GL_TEXTURE_2D, textura_id);
//    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,width,height,GL_RGB,GL_UNSIGNED_BYTE,data);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}