#ifndef _ESCENA_H
#define _ESCENA_H

#include <luz.h>
#include <luz_direccional.h>
#include <luz_posicional.h>
#include <cilindro.h>
#include <cono.h>
#include <cubo.h>
#include <ejes.h>
#include <esfera.h>
#include <malla.h>
#include <objply.h>
#include <objrevolucion.h>
#include <tetraedro.h>
#define N_MODOS 3
typedef enum {
    NADA,
    SELOBJETO,
    SELVISUALIZACION,
    SELDIBUJADO,
    SELILUMINACION,
    VARIACION_ALFA,
    VARIACION_BETA
} menu;

enum class Objetos_Escena{
    CUBO,
    TETRAEDRO,
    OBJPLY,
    OBJPLY_REV,
    ESFERA,
    CONO,
    CILINDRO,
    REV_VEC,
    PEON_X,
    PEON_Z
};

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
    std::vector<Malla3D*> objetos;
    std::vector<Tupla3f> traslaciones;
    std::vector<Tupla3f> escalados;
    std::vector<bool> se_dibuja;
    std::vector<Luz *> luces;
//    Cubo *cubo = nullptr;          // es importante inicializarlo a 'nullptr'
//    Tetraedro *tetraedro = nullptr;// es importante inicializarlo a 'nullptr'
//    ObjPLY *amogus = nullptr;
//    ObjRevolucion *obj_rev_ply = nullptr;
//    ObjRevolucion *obj_rev_vec = nullptr;
//    ObjRevolucion * peon_x = nullptr;
//    ObjRevolucion * peon_z = nullptr;
//    Esfera *esfera = nullptr;
//    Cono *cono = nullptr;
//    Cilindro *cilindro = nullptr;
//    bool dibuja_cubo;
//    bool dibuja_tetraedro;
//    bool dibuja_ply;

//    bool dibuja_rev_ply;
//    bool dibuja_rev_vec;
//    bool dibuja_esfera;
//    bool dibuja_cono;
//    bool dibuja_cilindro;
//    bool dibuja_peon_x;
//    bool dibuja_peon_z;

    bool ajedrez;
    bool dibuja_tapas;
    bool dibuja_diferido;
    bool modo_activo[N_MODOS];
    ModoVisualizacion modos [N_MODOS];
    ModoLuz  tipo_luz;

public:
    Escena();
    ~Escena();
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int newWidth, int newHeight);

    // Dibujar
    void dibujar();

    // Interacción con la escena
    bool teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);

    //wrapper de dibujado de objetos
    void dibujaObjeto(Malla3D *obj, const Tupla3f &tr, const Tupla3f &esc, ModoVisualizacion modo);


};
#endif
