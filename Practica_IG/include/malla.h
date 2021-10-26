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
#define PUNTOS GL_POINT
#define PUNTOS_i 0
#define ALAMBRE GL_LINE
#define ALAMBRE_i 1
#define SOLIDO GL_FILL
#define SOLIDO_i 2
#define PUNTOS_c 0
#define ALAMBRE_c 1
#define SOLIDO_c 2
#define AJEDREZ_c 3
// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
public:
   // dibuja el objeto en modo inmediato
    void draw_ModoInmediato(GLuint modo, std::vector<Tupla3f> *color);
    void draw_AjedrezInmediato(GLuint modo, std::vector<Tupla3f> *color);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(GLuint modo, GLuint color_id);
   void draw_AjedrezDiferido(GLuint modo, GLuint color_id);


    // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
    void draw(bool dibuja_diferido, bool ajedrez, GLuint modo);


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
   std::vector<Tupla3f> * selector_color = nullptr; //selector de color del modo inmediato
   GLuint selector_color_vbo; //selector de color del modo diferido
   GLuint id_vbo_vertices;
   GLuint id_vbo_tri;
   GLuint id_vbo_color_v, id_vbo_color_a, id_vbo_color_c, id_vbo_color_aj;
   GLuint ids_colores [4] = {0};

   void rellenaColores(const Tupla3f & vertices,
                       const Tupla3f & aristas,
                       const Tupla3f & solido,
                       const Tupla3f & ajedrez);

   void mezclaVector(); // metodo para mezclar un vector y conseguir el efecto ajedrez

   void inicializar(const Tupla3f &vertices, const Tupla3f &aristas, const Tupla3f &solido, const Tupla3f &ajedrez);
};

#endif
