#ifndef _ESCENA_H
#define _ESCENA_H

#include <ejes.h>
#include <malla.h>
#include <cubo.h>
#include <tetraedro.h>
#include <objply.h>
#include <objrevolucion.h>
#include <Esfera.h>
#include <Cilindro.h>
#include <Cono.h>

typedef enum
{
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
    //    Cubo *cubo = nullptr;           // es importante inicializarlo a 'nullptr'
    //    Tetraedro *tetraedro = nullptr; // es importante inicializarlo a 'nullptr'
    //    ObjPLY * amogus = nullptr;
    //    ObjRevolucion *obj_rev_ply = nullptr;
    //    ObjRevolucion *obj_rev_vec = nullptr;
    //    Esfera * esfera = nullptr;
    //    Cono * cono = nullptr;
    //    Cilindro * cilindro = nullptr;
    std::vector<std::pair<Malla3D, bool>> objetos;
    std::vector<std::vector<float>> traslaciones;
    std::vector<std::vector<float>> escalados;
    //    bool dibuja_cubo;
    //    bool dibuja_tetraedro;
    //    bool dibuja_ply;
    //    bool dibuja_rev_ply;
    //    bool dibuja_rev_vec;
    //    bool dibuja_esfera;
    //    bool dibuja_cono;
    //    bool dibuja_cilindro;
    bool ajedrez;
    bool dibuja_tapas;
    bool dibuja_diferido;
    GLuint modos[3];
    bool modo_activo[3];

public:
    Escena();
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int newWidth, int newHeight);

    // Dibujar
    void dibujar();

    // Interacción con la escena
    bool teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);

    //wrapper de tranformaciones
    void dibujaObjeto(const std::vector<float> &tr, const std::vector<float> &sc, Malla3D &obj, int id_modo);
};
#endif
