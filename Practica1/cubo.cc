#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
    id_vbo_tri = id_vbo_vertices = 0;

   // inicializar la tabla de vértices
   
   float arista = lado / 2;
   this->v.push_back(Tupla3f(-arista,-arista ,arista));  // 0 
   this->v.push_back(Tupla3f(arista,-arista ,arista));   // 1
   this->v.push_back(Tupla3f(arista,arista ,arista));    // 2
   this->v.push_back(Tupla3f(-arista,arista ,arista));   // 3
   this->v.push_back(Tupla3f(arista,-arista ,-arista));  // 4
   this->v.push_back(Tupla3f(-arista,-arista ,-arista)); // 5
   this->v.push_back(Tupla3f(arista,arista ,-arista));   // 6
   this->v.push_back(Tupla3f(-arista,arista ,-arista));  // 7



   // inicializar la tabla de caras o triángulos:

   this->f.push_back(Tupla3i(0,1,2));
   this->f.push_back(Tupla3i(0,2,3));
   this->f.push_back(Tupla3i(0,4,1));
   this->f.push_back(Tupla3i(0,5,4));
   this->f.push_back(Tupla3i(1,4,6));
   this->f.push_back(Tupla3i(1,6,2));
   this->f.push_back(Tupla3i(3,2,6));
   this->f.push_back(Tupla3i(3,6,7));
   this->f.push_back(Tupla3i(5,6,4));
   this->f.push_back(Tupla3i(5,7,6));
   this->f.push_back(Tupla3i(0,7,5));
   this->f.push_back(Tupla3i(0,3,7));

   for (int i=0; i < f.size(); i++){
       c.push_back(Tupla3f(0,1,0));
   }

   modo_dibujado = GL_LINE;
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

}