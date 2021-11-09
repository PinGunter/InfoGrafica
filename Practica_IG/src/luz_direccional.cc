//
// Created by salva on 9/11/21.
//

#include <luz_direccional.h>
LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso) {
    id = idLuzOpenGL;
    this -> colorAmbiente = colorAmbiente;
    this -> colorEspecular = colorEspecular;
    this -> colorDifuso = colorDifuso;
}
