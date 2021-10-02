#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float arista)
{
    float base1 = ((1/sqrt(2)) / 2) * arista;
    float arista_med = arista*0.5;
    v.push_back(Tupla3f(arista_med,0,-base1));
    v.push_back(Tupla3f(-arista_med,0,-base1));
    v.push_back(Tupla3f(0,arista_med,base1));
    v.push_back(Tupla3f(0,-arista_med,base1));
//    v.push_back(Tupla3f(arista,arista,arista));
//    v.push_back(Tupla3f(arista,-arista,-arista));
//    v.push_back(Tupla3f(-arista,arista,-arista));
//    v.push_back(Tupla3f(-arista,-arista,arista));

    f.push_back(Tupla3i(0,3,1));
    f.push_back(Tupla3i(2,0,1));
    f.push_back(Tupla3i(3,2,1));
    f.push_back(Tupla3i(3,0,2));

    c.push_back(Tupla3f(1,0,0)); //rojo
    c.push_back(Tupla3f(0,1,0)); //verde
    c.push_back(Tupla3f(0,0,1)); //azul
    c.push_back(Tupla3f(0,0,0)); //negro
    modo_dibujado = GL_LINE;
    
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

}

