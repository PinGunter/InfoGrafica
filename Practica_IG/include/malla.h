// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include <aux.h>

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
public:
   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(bool puntos, bool alambre, bool solido);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(bool puntos, bool alambre, bool solido);
   void draw_AjedrezDiferido(bool puntos, bool alambre, bool solido);
   void draw_AjedrezInmediato(bool puntos, bool alambre, bool solido);


    // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(bool modo_dibujado, bool puntos, bool alambre, bool solido, bool ajedrez);


protected:
   void calcular_normales(); // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v; // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f; // una terna de 3 enteros por cada cara o triángulo

   // necesitamos varios vectores de colores para
   // poder diferencias los modos de visualizacion
   // de esta forma tendremos colores distintos
   // para puntos, aristas y las caras
   // ademas se incluye otro color que se usa
   // para el modo ajedrez en conjunto con el de caras
   std::vector<Tupla3f> c_vert; // vector con los colores a dibujar (vertices)
   std::vector<Tupla3f> c_aris; // vector con los colores a dibujar (aristas)
   std::vector<Tupla3f> c_cara; // vector con los colores a dibujar (caras)
   std::vector<Tupla3f> c_ajedrez; // vector con los colores con los que se alterna en el modo ajedrez

   GLuint id_vbo_vertices;
   GLuint id_vbo_tri;
   GLuint id_vbo_color_v, id_vbo_color_a, id_vbo_color_c, id_vbo_color_aj;


   // completar: tabla de colores, tabla de normales de vértices
};

#endif
