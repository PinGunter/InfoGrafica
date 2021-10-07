#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float arista)
{
    id_vbo_tri = id_vbo_vertices = id_vbo_color_v = id_vbo_color_a = id_vbo_color_c = id_vbo_color_aj = 0;
    float base1 = ((1 / sqrt(2)) / 2) * arista;
    float arista_med = arista * 0.5;
    //    v.push_back(Tupla3f(arista_med,0,-base1));
    //    v.push_back(Tupla3f(-arista_med,0,-base1));
    //    v.push_back(Tupla3f(0,arista_med,base1));
    //    v.push_back(Tupla3f(0,-arista_med,base1));
    v.push_back(Tupla3f(arista, arista, arista));
    v.push_back(Tupla3f(arista, -arista, -arista));
    v.push_back(Tupla3f(-arista, arista, -arista));
    v.push_back(Tupla3f(-arista, -arista, arista));


    // inicializar la tabla de caras o triángulos:
    // en el vector insertamos primero las caras pares
    // y luego las impares, de esta manera, al dibujar en
    // modo ajedrez, podemos usar el mismo vbo y el mismo vector
    // basta con indicarle la posición donde empieza el siguiente
    // grupo (las caras impares)

    f.push_back(Tupla3i(0, 3, 1)); // 0
    f.push_back(Tupla3i(3, 2, 1)); // 2

    f.push_back(Tupla3i(2, 0, 1)); // 1
    f.push_back(Tupla3i(3, 0, 2)); // 3

    for (int i = 0; i < v.size(); i++) {
        c_vert.push_back(Tupla3f(1, 0, 0));
        c_aris.push_back(Tupla3f(0, 1, 1));
        c_cara.push_back(Tupla3f(0, 0, 0));
        c_ajedrez.push_back(Tupla3f(1, 0.24, 0.71));
    }


    // inicializar la tabla de caras o triángulos:
    // (es importante en cada cara ordenar los vértices en sentido contrario
    //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
}
