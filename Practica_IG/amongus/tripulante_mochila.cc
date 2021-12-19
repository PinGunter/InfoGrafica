//
// Created by salva on 11/12/21.
//

#include <tripulante_mochila.h>

void Tripulante_mochila::resetearPosicion() {
    giroRodillaIzda = giroRodillaIzda = giroYPiernaDcha = giroYPiernaIzda =
            giroXPiernaDcha = giroXPiernaIzda = giroZPiernaIzda = giroZPiernaDcha = 0;
}

void Tripulante_mochila::init() {
    resetearPosicion();
    velocidadGiroPierna = velocidadBaseGiroPierna;
    velocidadRodilla = velocidadBaseRodilla;
    velocidadMochila = velocidadBaseMochila;
    sentidoGiroPiernaIzda = -1;
    sentidoGiroPiernaDcha = 1;
    sentidoMovimientoMochila = 1;
    velocidadAnimacionGeneral = 1;
    alturaMochila = 1.4;
}

Tripulante_mochila::Tripulante_mochila() {
    tripulante = new Tripulante();
    mochila = new Mochila();
    init();
}

void Tripulante_mochila::draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool cabeza) {
    glPushMatrix();
    tripulante->draw(diferido, ajedrez, modo, cabeza,Tupla4f(giroYPiernaDcha, giroRodillaDcha, giroXPiernaDcha,giroZPiernaDcha), Tupla4f(giroYPiernaIzda, giroRodillaIzda, giroXPiernaIzda, giroZPiernaIzda));
    glPushMatrix();
    glTranslatef(0, alturaMochila, -5);
    mochila->draw(diferido, ajedrez, modo);
    glPopMatrix();
    glPopMatrix();
}

void Tripulante_mochila::siguienteAnimacionPiernaIzda() {
    float giro_nuevo = (giroXPiernaIzda + sentidoGiroPiernaIzda * velocidadGiroPierna);

    if ((giro_nuevo <= GiroMaximoX) && (giro_nuevo >= -GiroMaximoX)) {
        giroXPiernaIzda = giro_nuevo;
    } else {
        sentidoGiroPiernaIzda *= -1;
        giroXPiernaIzda = giro_nuevo;
    }
}


void Tripulante_mochila::siguienteAnimacionPiernaDcha() {
    float giro_nuevo = (giroXPiernaDcha + sentidoGiroPiernaDcha * velocidadGiroPierna);

    if ((giro_nuevo <= GiroMaximoX) && (giro_nuevo >= -GiroMaximoX)) {
        giroXPiernaDcha = giro_nuevo;
    } else {
        sentidoGiroPiernaDcha *= -1;
        giroXPiernaDcha = giro_nuevo;
    }
}

void Tripulante_mochila::siguienteAnimacionRodillaIzda() {
    float giro_nuevo = (giroRodillaIzda + sentidoGiroPiernaIzda * velocidadRodilla);

    if ((giro_nuevo <= GiroMaximoX) && (giro_nuevo >= 0)) {
        giroRodillaIzda = giro_nuevo;
    }
}

void Tripulante_mochila::siguienteAnimacionRodillaDcha() {
    float giro_nuevo = (giroRodillaDcha + sentidoGiroPiernaDcha * velocidadRodilla);

    if ((giro_nuevo <= GiroMaximoX) && (giro_nuevo >= 0))
        giroRodillaDcha = giro_nuevo;
}

void Tripulante_mochila::siguienteAnimacionPiernas() {
    siguienteAnimacionPiernaIzda();
    siguienteAnimacionRodillaIzda();
    siguienteAnimacionPiernaDcha();
    siguienteAnimacionRodillaDcha();
    siguienteAnimacionMochila();
}


void Tripulante_mochila::siguienteAnimacionMochila() {
    float nueva_posicion = alturaMochila + sentidoMovimientoMochila * velocidadMochila;

    if ((nueva_posicion <= AlturaMaxima) && (nueva_posicion >= AlturaMinima)){
        alturaMochila = nueva_posicion;
    } else{
        sentidoMovimientoMochila *= -1;
        alturaMochila = nueva_posicion;
    }

}

void Tripulante_mochila::siguienteAnimacionEjeXPiernaIzda(float sentido) {
    float giro_nuevo = (giroXPiernaIzda + sentido * velocidadGiroPierna);

    if ((giro_nuevo <= GiroMaximoX) && (giro_nuevo >= -GiroMaximoX)) {
        giroXPiernaIzda = giro_nuevo;
    }
}

void Tripulante_mochila::siguienteAnimacionEjeXPiernaDcha(float sentido) {
    float giro_nuevo = (giroXPiernaDcha + sentido * velocidadGiroPierna);

    if ((giro_nuevo <= GiroMaximoX) && (giro_nuevo >= -GiroMaximoX)) {
        giroXPiernaDcha = giro_nuevo;
    }
}

void Tripulante_mochila::siguienteAnimacionEjeYPiernaIzda(float sentido) {
    float giro_nuevo = (giroYPiernaIzda + sentido * velocidadGiroPierna);

    if ((giro_nuevo <= GiroMaximoY) && (giro_nuevo >= -GiroMaximoY)) {
        giroYPiernaIzda = giro_nuevo;
    }
}

void Tripulante_mochila::siguienteAnimacionEjeYPiernaDcha(float sentido) {
    float giro_nuevo = (giroYPiernaDcha + sentido * velocidadGiroPierna);

    if ((giro_nuevo <= GiroMaximoY) && (giro_nuevo >= -GiroMaximoY)) {
        giroYPiernaDcha = giro_nuevo;
    }
}

void Tripulante_mochila::siguienteAnimacionEjeZPiernaIzda(float sentido) {
    float giro_nuevo = (giroZPiernaIzda + sentido * velocidadGiroPierna);

    if ((giro_nuevo <= GiroMaximoZ) && (giro_nuevo >= -10)) {
        giroZPiernaIzda = giro_nuevo;
    }
}

void Tripulante_mochila::siguienteAnimacionEjeZPiernaDcha(float sentido) {
    float giro_nuevo = (giroZPiernaDcha + sentido * velocidadGiroPierna);

    if ((giro_nuevo <= GiroMaximoZ) && (giro_nuevo >= -10)) {
        giroZPiernaDcha = giro_nuevo;
    }
}

void Tripulante_mochila::siguienteAnimacionRodillaIzda(float sentido) {
    float giro_nuevo = (giroRodillaIzda + sentido * velocidadRodilla);

    if ((giro_nuevo <= GiroMaximoX) && (giro_nuevo >= 0)) {
        giroRodillaIzda = giro_nuevo;
    }
}

void Tripulante_mochila::siguienteAnimacionRodillaDcha(float sentido) {
    float giro_nuevo = (giroRodillaDcha + sentido * velocidadRodilla);

    if ((giro_nuevo <= GiroMaximoX) && (giro_nuevo >= 0))
        giroRodillaDcha = giro_nuevo;
}


void Tripulante_mochila::siguienteAnimacionMochila(float sentido) {
    float nueva_posicion = alturaMochila + sentido * velocidadMochila;

    if ((nueva_posicion <= AlturaMaxima) && (nueva_posicion >= AlturaMinima)){
        alturaMochila = nueva_posicion;
    }
}


void Tripulante_mochila::animacionAutomatica(bool natural) {
    siguienteAnimacionPiernas();
    if (!natural) {
        siguienteAnimacionEjeYPiernaDcha(sentidoGiroPiernaDcha);
        siguienteAnimacionEjeYPiernaIzda(sentidoGiroPiernaIzda);
        siguienteAnimacionEjeZPiernaIzda(sentidoGiroPiernaIzda);
        siguienteAnimacionEjeZPiernaDcha(sentidoGiroPiernaDcha);
    }
}

void Tripulante_mochila::setVelocidadAnimacionGeneral(float velocidad) {
    if (velocidad >= 0) { // no queremos animaciones en el sentido contrario
        velocidadAnimacionGeneral = velocidad;
        velocidadRodilla = velocidadAnimacionGeneral * velocidadBaseRodilla;
        velocidadGiroPierna = velocidadAnimacionGeneral * velocidadBaseGiroPierna;
        velocidadMochila = velocidadAnimacionGeneral * velocidadBaseMochila;
    }
}

void Tripulante_mochila::setVelocidadAnimacionPierna(float velocidad) {
    if (velocidad >= 0){
        velocidadGiroPierna = velocidadBaseGiroPierna * velocidadAnimacionGeneral * velocidad;
    }
}
void Tripulante_mochila::setVelocidadAnimacionRodilla(float velocidad) {
    if (velocidad >= 0){
        velocidadRodilla = velocidadBaseRodilla * velocidadAnimacionGeneral * velocidad;
    }
}
void Tripulante_mochila::setVelocidadAnimacionMochila(float velocidad) {
    if (velocidad >= 0){
        velocidadMochila = velocidadBaseMochila * velocidadAnimacionGeneral * velocidad;
    }
}

