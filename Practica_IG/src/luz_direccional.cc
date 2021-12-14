//
// Created by salva on 9/11/21.
//

#include <luz_direccional.h>
LuzDireccional::LuzDireccional(const Tupla2f & direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso) {
    id = idLuzOpenGL;
    this -> colorAmbiente = colorAmbiente;
    this -> colorEspecular = colorEspecular;
    this -> colorDifuso = colorDifuso;
    alpha = direccion(0);
    beta = direccion(1);
    calcularPosicion(alpha,beta);

}
void LuzDireccional::variarAnguloAlpha(float incremento) {
    alpha += incremento;
    calcularPosicion(alpha,beta);
}
void LuzDireccional::variarAnguloBeta(float incremento) {
    beta += incremento;
    calcularPosicion(alpha,beta);
}

void LuzDireccional::calcularPosicion(float a, float b){
    posicion(0) = sin(b)*cos(a);
    posicion(1) = sin(b)*sin(a);
    posicion(2) = cos(b);
    posicion(3) = 0;
}

void LuzDireccional::setAlpha(float a){
    alpha = a;
    calcularPosicion(alpha,beta);
}

void LuzDireccional::setBeta(float b){
    beta = b;
    calcularPosicion(alpha,beta);

}
void LuzDireccional::activar() {
    Luz::activar();
}
