//
// Created by salva on 11/12/21.
//

#include <tripulante_mochila.h>
Tripulante_mochila::Tripulante_mochila() {
    tripulante = new Tripulante();
    mochila = new Mochila();
    alturaMochila = giroRodillaDcha = giroRodillaIzda = giroYPiernaDcha = giroYPiernaIzda =
            giroXPiernaDcha = giroXPiernaIzda = 0;
    velocidadGiroPierna = 5;
    velocidadRodilla = 3;
    sentidoGiroIzda = -1;
    sentidoGiroDcha = 1;

}

void Tripulante_mochila::draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool cabeza) {
    glPushMatrix();
    tripulante->draw(diferido, ajedrez, modo, cabeza, Tupla3f(giroYPiernaIzda,giroRodillaIzda,giroXPiernaIzda), Tupla3f(giroYPiernaDcha,giroRodillaDcha,giroXPiernaDcha));
    glPushMatrix();
    glTranslatef(0,1.4,-5);
    mochila->draw(diferido,ajedrez,modo);
    glPopMatrix();
    glPopMatrix();
}

void Tripulante_mochila::siguienteAnimacionPiernaIzda() {
    float giro_nuevo = (giroXPiernaIzda + sentidoGiroIzda *velocidadGiroPierna);

    if ((giro_nuevo <= GiroMaximo) && (giro_nuevo >= -GiroMaximo)){
        giroXPiernaIzda = giro_nuevo;
    } else{
        sentidoGiroIzda *= -1;
        giroXPiernaIzda = giro_nuevo;
    }
}


void Tripulante_mochila::siguienteAnimacionPiernaDcha() {
    float giro_nuevo = (giroXPiernaDcha + sentidoGiroDcha *velocidadGiroPierna);

    if ((giro_nuevo <= GiroMaximo) && (giro_nuevo >= -GiroMaximo)){
        giroXPiernaDcha = giro_nuevo;
    } else{
        sentidoGiroDcha *= -1;
        giroXPiernaDcha = giro_nuevo;
    }
}

void Tripulante_mochila::siguienteAnimacionRodillaIzda() {
    float giro_nuevo = (giroRodillaIzda + sentidoGiroIzda *velocidadRodilla);

    if ((giro_nuevo <= GiroMaximo) && (giro_nuevo >= 0)){
        giroRodillaIzda = giro_nuevo;
    } else{
        sentidoGiroIzda *= -1;
        giroRodillaIzda = giro_nuevo;
    }
}

void Tripulante_mochila::siguienteAnimacionRodillaDcha() {

}

void Tripulante_mochila::siguienteAnimacionMochila() {

}

void Tripulante_mochila::animacionAutomatica() {

}

void Tripulante_mochila::setVelocidadAnimacion(float velocidad) {
//    velocidadAnimacion = velocidad;
}
