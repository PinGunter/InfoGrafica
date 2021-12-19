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
#include <semiesfera.h>


#include <tripulante_mochila.h>

#define N_MODOS 3
typedef enum {
    NADA,
    SELOBJETO,
    SELVISUALIZACION,
    SELDIBUJADO,
    SELILUMINACION,
    VARIACION_ALFA,
    VARIACION_BETA,
    ANIMACION_AUTOMATICA,
    ANIMACION_MANUAL,
    SELVELOCIDAD,
    VEL_MOCHILA,
    VEL_RODILLA,
    VEL_PIERNA,
    ANIM_2_PIERNAS,
    ANIM_PIERNA_I,
    ANIM_PIERNA_D,
    ANIM_PIERNA_I_X,
    ANIM_PIERNA_I_Y,
    ANIM_PIERNA_I_Z,
    ANIM_PIERNA_D_X,
    ANIM_PIERNA_D_Y,
    ANIM_PIERNA_D_Z,
    ANIM_RODILLA_I,
    ANIM_RODILLA_D,
    ANIM_MOCH
} menu;

enum class Objetos_Escena{
    NUM_OBJ
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

    //Among us
    Tripulante_mochila *amongus = nullptr;
    float velocidad_animacion, velocidad_mochila, velocidad_rodilla, velocidad_pierna;
    std::vector<Malla3D*> objetos;
    std::vector<Tupla3f> traslaciones;
    std::vector<Tupla3f> escalados;
    std::vector<bool> se_dibuja;
    bool luz_p_act, luz_d_act;
    LuzPosicional * luz_p = nullptr;
    LuzDireccional * luz_d = nullptr;

    bool ajedrez;
    bool dibuja_tapas;
    bool dibuja_diferido;
    bool dibuja_cabeza;
    bool animacion_automatica;
    bool modo_activo[N_MODOS];
    bool movimiento_natural;
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

    void animarModeloJerarquico();

    std::string valorMenuActual();
};
#endif
