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

#include <material.h>
#include <aux.h>
#define PUNTOS_c 0
#define ALAMBRE_c 1
#define SOLIDO_c 2
#define AJEDREZ_c 3

enum class Eje_rotacion{EJE_X, EJE_Y, EJE_Z};
enum class ModoVisualizacion{
    PUNTOS,
    ALAMBRE,
    SOLIDO
};

enum class ModoLuz{
    SUAVE,
    NINGUNA
};
// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D {
public:
    // dibuja el objeto en modo inmediato
    void draw_ModoInmediato(ModoVisualizacion modo, std::vector<Tupla3f> *color, ModoLuz iluminacion);
    void draw_AjedrezInmediato(ModoVisualizacion modo, std::vector<Tupla3f> *color, ModoLuz iluminacion);

    // dibuja el objeto en modo diferido (usando VBOs)
    void draw_ModoDiferido(ModoVisualizacion modo, GLuint color_id, ModoLuz iluminacion);
    void draw_AjedrezDiferido(ModoVisualizacion modo, GLuint color_id, ModoLuz iluminacion);

;
    // función que redibuja el objeto
    // está función llama a 'draw_ModoInmediato' (modo inmediato)
    // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
    void draw(bool dibuja_diferido, bool ajedrez, ModoVisualizacion modo, ModoLuz iluminacion);

    void setMaterial (Material m);

    bool esObjRevolucion() const;

protected:
    GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram) ;

    GLuint map_modo(ModoVisualizacion v) const;
    GLuint map_luz(ModoLuz l) const;

    std::vector<Tupla3f> v;// tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
    std::vector<Tupla3i> f;// una terna de 3 enteros por cada cara o triángulo
    std::vector<Tupla3f> nv; // vector de normales de los vertices
    std::vector<Tupla3f> nf; // vector de normales de las caras
    Material m;
    // necesitamos varios vectores de colores para
    // poder diferencias los modos de visualizacion
    // de esta forma tendremos colores distintos
    // para puntos, aristas y las caras
    // ademas se incluye otro color que se usa
    // para el modo ajedrez en conjunto con el de caras
    std::vector<Tupla3f> c_vert;                   // vector con los colores a dibujar (vertices)
    std::vector<Tupla3f> c_aris;                   // vector con los colores a dibujar (aristas)
    std::vector<Tupla3f> c_cara;                   // vector con los colores a dibujar (caras)
    std::vector<Tupla3f> c_ajedrez;                // vector con los colores con los que se alterna en el modo ajedrez
    std::vector<Tupla3f> *selector_color = nullptr;//selector de color del modo inmediato
    GLuint selector_color_vbo;                     //selector de color del modo diferido
    GLuint id_vbo_vertices;
    GLuint id_vbo_tri;
    GLuint id_vbo_normal;
    GLuint id_vbo_color_v, id_vbo_color_a, id_vbo_color_c, id_vbo_color_aj;
    GLuint ids_colores[4] = {0};

    Tupla3f calcularNormal(Tupla3f a, Tupla3f b, Tupla3f c);
    void calcularNormales() ;
    void rellenaColores(const Tupla3f &vertices,
                        const Tupla3f &aristas,
                        const Tupla3f &solido,
                        const Tupla3f &ajedrez);

    virtual void mezclaVector();// metodo para mezclar un vector y conseguir el efecto ajedrez

    void inicializar(const Tupla3f &vertices, const Tupla3f &aristas, const Tupla3f &solido, const Tupla3f &ajedrez, const Tupla4f &ambiente, const Tupla4f &especular, const Tupla4f &difuso, float brillo);
};

#endif
