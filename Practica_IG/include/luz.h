//
// Created by salva on 9/11/21.
//

#ifndef PRACTICA_IG_LUZ_H
#define PRACTICA_IG_LUZ_H
#include <aux.h>

class Luz {
protected:
    Tupla4f posicion;
    GLenum id;
    Tupla4f colorAmbiente;
    Tupla4f colorDifuso;
    Tupla4f colorEspecular;
    bool activada;
public:
    void activar();
    void desactivar();
    bool getActivada() const;

};


#endif//PRACTICA_IG_LUZ_H
