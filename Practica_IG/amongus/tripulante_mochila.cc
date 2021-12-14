//
// Created by salva on 11/12/21.
//

#include <tripulante_mochila.h>
Tripulante_mochila::Tripulante_mochila() {
    tripulante = new Tripulante();
    mochila = new Mochila();
    giroRodillaIzda = giroRodillaIzda = giroYPiernaDcha = giroYPiernaIzda =
            giroXPiernaDcha = giroXPiernaIzda = 0;
    velocidadGiroPierna = velocidadBaseGiroPierna;
    velocidadRodilla = velocidadBaseRodilla;
    velocidadMochila = velocidadBaseMochila;
    sentidoGiroPiernaIzda = -1;
    sentidoGiroRodillaIzda = -1;
    sentidoGiroPiernaDcha = 1;
    sentidoGiroRodillaDcha = 1;
    sentidoMovimientoMochila = 1;
    velocidadAnimacionGeneral = 1;
    alturaMochila = 1.4;
}

void Tripulante_mochila::draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool cabeza) {
    glPushMatrix();
    tripulante->draw(diferido, ajedrez, modo, cabeza,Tupla3f(giroYPiernaDcha, giroRodillaDcha, giroXPiernaDcha),Tupla3f(giroYPiernaIzda, giroRodillaIzda, giroXPiernaIzda));
    glPushMatrix();
    glTranslatef(0, alturaMochila, -5);
    mochila->draw(diferido, ajedrez, modo);
    glPopMatrix();
    glPopMatrix();
}

void Tripulante_mochila::siguienteAnimacionPiernaIzda() {
    float giro_nuevo = (giroXPiernaIzda + sentidoGiroPiernaIzda * velocidadGiroPierna);

    if ((giro_nuevo <= GiroMaximo) && (giro_nuevo >= -GiroMaximo)) {
        giroXPiernaIzda = giro_nuevo;
    } else {
        sentidoGiroPiernaIzda *= -1;
        giroXPiernaIzda = giro_nuevo;
    }
}


void Tripulante_mochila::siguienteAnimacionPiernaDcha() {
    float giro_nuevo = (giroXPiernaDcha + sentidoGiroPiernaDcha * velocidadGiroPierna);

    if ((giro_nuevo <= GiroMaximo) && (giro_nuevo >= -GiroMaximo)) {
        giroXPiernaDcha = giro_nuevo;
    } else {
        sentidoGiroPiernaDcha *= -1;
        giroXPiernaDcha = giro_nuevo;
    }
}

void Tripulante_mochila::siguienteAnimacionRodillaIzda() {
    float giro_nuevo = (giroRodillaIzda + sentidoGiroPiernaIzda * velocidadRodilla);

    if ((giro_nuevo <= GiroMaximo) && (giro_nuevo >= 0)) {
        giroRodillaIzda = giro_nuevo;
    }
}

void Tripulante_mochila::siguienteAnimacionRodillaDcha() {
    float giro_nuevo = (giroRodillaDcha + sentidoGiroPiernaDcha * velocidadRodilla);

    if ((giro_nuevo <= GiroMaximo) && (giro_nuevo >= 0))
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

void Tripulante_mochila::animacionAutomatica() {
    siguienteAnimacionPiernas();
}

void Tripulante_mochila::setVelocidadAnimacion(float velocidad) {
        velocidadAnimacionGeneral = velocidad;
        velocidadRodilla = velocidadAnimacionGeneral * velocidadBaseRodilla;
        velocidadGiroPierna = velocidadAnimacionGeneral * velocidadBaseGiroPierna;
        velocidadMochila = velocidadAnimacionGeneral * velocidadBaseMochila;
}
