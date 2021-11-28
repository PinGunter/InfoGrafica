//
// Created by salva on 9/11/21.
//

#include <luz_posicional.h>

LuzPosicional::LuzPosicional(const Tupla3f &posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso) {
    this->posicion = Tupla4f(posicion(0),posicion(1),posicion(2),1);
    id = idLuzOpenGL;
    this -> colorAmbiente = colorAmbiente;
    this -> colorEspecular = colorEspecular;
    this -> colorDifuso = colorDifuso;
}
