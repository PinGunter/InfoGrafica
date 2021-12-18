//
// Created by salva on 11/12/21.
//

#ifndef PRACTICA_IG_TRIPULANTE_MOCHILA_H
#define PRACTICA_IG_TRIPULANTE_MOCHILA_H

#include <tripulante.h>
#include <mochila.h>

class Tripulante_mochila {
    Tripulante * tripulante = nullptr;
    Mochila * mochila = nullptr;
    float alturaMochila, giroRodillaDcha, giroRodillaIzda, giroYPiernaDcha, giroYPiernaIzda,
                        giroXPiernaDcha, giroXPiernaIzda, giroZPiernaIzda, giroZPiernaDcha;
    const float GiroMaximoX = 30;
    const float GiroMaximoY = 45;
    const float AlturaMaxima = 2;
    const float AlturaMinima = 1;
    const float velocidadBaseGiroPierna = 1.2;
    const float velocidadBaseRodilla = 1;
    const float velocidadBaseMochila = 0.02;
    float sentidoGiroPiernaIzda, sentidoGiroPiernaDcha, sentidoMovimientoMochila;
    float velocidadGiroPierna, velocidadRodilla, velocidadMochila, velocidadAnimacionGeneral;
public:
    Tripulante_mochila();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool cabeza);

    void siguienteAnimacionPiernaIzda();
    void siguienteAnimacionPiernaDcha();

    void siguienteAnimacionRodillaIzda();
    void siguienteAnimacionRodillaDcha();

    void siguienteAnimacionPiernas();

    void siguienteAnimacionMochila();

    void animacionAutomatica();

    void setVelocidadAnimacionGeneral(float velocidad);
    void setVelocidadAnimacionPierna(float velocidad);
    void setVelocidadAnimacionRodilla(float velocidad);
    void setVelocidadAnimacionMochila(float velocidad);

    //Estas animaciones son manuales
    void siguienteAnimacionEjeYPiernaIzda(float sentido);
    void siguienteAnimacionEjeYPiernaDcha(float sentido);
    void siguienteAnimacionEjeZPiernaIzda(float sentido);
    void siguienteAnimacionEjeZPiernaDcha(float sentido);

};


#endif//PRACTICA_IG_TRIPULANTE_MOCHILA_H
