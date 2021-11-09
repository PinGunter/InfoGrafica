#ifndef _ESCENA_H
#define _ESCENA_H

#include <cilindro.h>
#include <cono.h>
#include <cubo.h>
#include <ejes.h>
#include <esfera.h>
#include <malla.h>
#include <objply.h>
#include <objrevolucion.h>
#include <tetraedro.h>

typedef enum {
    NADA,
    SELOBJETO,
    SELVISUALIZACION,
    SELDIBUJADO
} menu;


class Escena
{

private:
    // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)

    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
    void change_projection(const float ratio_xy);
    void change_observer();

    void clear_window();

    menu modoMenu = NADA;
    // Objetos de la escena
    Ejes ejes;
    Cubo *cubo = nullptr;          // es importante inicializarlo a 'nullptr'
    Tetraedro *tetraedro = nullptr;// es importante inicializarlo a 'nullptr'
    ObjPLY *amogus = nullptr;
    ObjRevolucion *obj_rev_ply = nullptr;
    ObjRevolucion *obj_rev_vec = nullptr;
    ObjRevolucion * peon_x = nullptr;
    ObjRevolucion * peon_z = nullptr;
    Esfera *esfera = nullptr;
    Cono *cono = nullptr;
    Cilindro *cilindro = nullptr;
    bool dibuja_cubo;
    bool dibuja_tetraedro;
    bool dibuja_ply;
    bool ajedrez;
    bool dibuja_tapas;
    bool dibuja_diferido;
    bool dibuja_rev_ply;
    bool dibuja_rev_vec;
    bool dibuja_esfera;
    bool dibuja_cono;
    bool dibuja_cilindro;
    bool dibuja_peon_x;
    bool dibuja_peon_z;
    ModoVisualizacion modos [5];
    bool modo_activo[5];

public:
    Escena();
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int newWidth, int newHeight);

    // Dibujar
    void dibujar();

    // Interacción con la escena
    bool teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);
};
#endif
