//
// Created by salva on 9/11/21.
//

#include <luz_direccional.h>
LuzDireccional::LuzDireccional(const Tupla2f & direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso) {
    id = idLuzOpenGL;
    this -> colorAmbiente = colorAmbiente;
    this -> colorEspecular = colorEspecular;
    this -> colorDifuso = colorDifuso;
    posicion(0) = 0;
    posicion(1) = 0;
    posicion(2) = 1;
    posicion(3) = 0;
    alpha = direccion(0);
    beta = direccion(1);
}
