#include <aux.h>
#include <malla.h>
#include <cubo.h>

Cubo::Cubo(float lado)
{
    // inicializar la tabla de vértices

    float arista = lado / 2;
    this->v.push_back(Tupla3f(-arista, -arista, arista));  // 0
    this->v.push_back(Tupla3f(arista, -arista, arista));   // 1
    this->v.push_back(Tupla3f(arista, arista, arista));    // 2
    this->v.push_back(Tupla3f(-arista, arista, arista));   // 3
    this->v.push_back(Tupla3f(arista, -arista, -arista));  // 4
    this->v.push_back(Tupla3f(-arista, -arista, -arista)); // 5
    this->v.push_back(Tupla3f(arista, arista, -arista));   // 6
    this->v.push_back(Tupla3f(-arista, arista, -arista));  // 7

    // inicializar la tabla de caras o triángulos:
    // en el vector insertamos primero las caras pares
    // y luego las impares, de esta manera, al dibujar en
    // modo ajedrez, podemos usar el mismo vbo y el mismo vector
    // basta con indicarle la posición donde empieza el siguiente
    // grupo (las caras impares)

    this->f.push_back(Tupla3i(0, 1, 2)); // 0
    this->f.push_back(Tupla3i(0, 2, 3)); // 1
    this->f.push_back(Tupla3i(0, 4, 1)); // 2
    this->f.push_back(Tupla3i(0, 5, 4)); // 3
    this->f.push_back(Tupla3i(1, 4, 6)); // 4
    this->f.push_back(Tupla3i(1, 6, 2)); // 5
    this->f.push_back(Tupla3i(3, 2, 6)); // 6
    this->f.push_back(Tupla3i(3, 6, 7)); // 7
    this->f.push_back(Tupla3i(5, 6, 4)); // 8
    this->f.push_back(Tupla3i(5, 7, 6)); // 9
    this->f.push_back(Tupla3i(0, 7, 5)); // 10
    this->f.push_back(Tupla3i(0, 3, 7)); // 11

    Tupla4f ambiente (1,1,1,1);
    Tupla4f especular (1,0,0,1);
    Tupla4f difuso (1,0,0,1);
    inicializar(Tupla3f(0, 1, 0),
                Tupla3f(1, 0, 0),
                Tupla3f(0, 0, 1),
                Tupla3f(1, 0.24, 0.71), ambiente, especular, difuso, 5);

    // (es importante en cada cara ordenar los vértices en sentido contrario
    //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
}