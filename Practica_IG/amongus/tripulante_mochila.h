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
                        giroXPiernaDcha, giroXPiernaIzda;
    const float GiroMaximo = 30;
    float sentidoGiroIzda, sentidoGiroDcha;
    float velocidadGiroPierna, velocidadRodilla;
public:
    Tripulante_mochila();

    void draw(bool diferido, bool ajedrez, ModoVisualizacion modo, bool cabeza);

    void siguienteAnimacionPiernaIzda();
    void siguienteAnimacionPiernaDcha();

    void siguienteAnimacionRodillaIzda();
    void siguienteAnimacionRodillaDcha();

    void siguienteAnimacionMochila();

    void animacionAutomatica();

    void setVelocidadAnimacion(float velocidad);

};


#endif//PRACTICA_IG_TRIPULANTE_MOCHILA_H
