#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices
   
   float arista = lado / 2;
   this->v.push_back(Tupla3f(-arista,-arista ,arista));  // 0 
   this->v.push_back(Tupla3f(arista,-arista ,arista));   // 1
   this->v.push_back(Tupla3f(arista,arista ,arista));    // 2
   this->v.push_back(Tupla3f(-arista,arista ,arista));   // 3
   this->v.push_back(Tupla3f(arista,-arista ,-arista));  // 4
   this->v.push_back(Tupla3f(-arista,-arista ,-arista)); // 5
   this->v.push_back(Tupla3f(arista,arista ,-arista));   // 6
   this->v.push_back(Tupla3f(-arista,arista ,-arista)); // 7



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

   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

}

void Cubo::dibujar() const {
   float * vertices = new float[12*9];
   int i=0;
   for (auto t : this->f){
      for (int j = 0; j < 3; j++){
         for (int k=0; k < 3; k++)
         vertices[i++] = v.at(t(j))(k);
      }
   }

   float * colores = new float [12*9];
   
   for (int j=0; j < this->v.size(); j+=3){
      colores[j] = 0;
      colores[j+1] = 0;
      colores[j+2] = 1;
   }

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer(3,GL_FLOAT,0,vertices);
   glVertexPointer(3, GL_FLOAT, 0, vertices);

   glLineWidth(3);

   glPolygonMode(GL_FRONT, GL_LINE);
   glDrawArrays(GL_TRIANGLES,0, 36);
   printf("%i",i);

   delete [] vertices;   
   delete [] colores;
}