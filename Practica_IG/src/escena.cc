#include <aux.h>// includes de OpenGL/glut/glew, windows, y librería std de C++
#include <escena.h>
#include <malla.h>// objetos: Cubo y otros....
#define N_OBJ (int) Objetos_Escena::NUM_OBJ
#define LUZ(i) GL_LIGHTi
#define ALPHA_INICIAL 12.5
#define BETA_INICIAL 9.27
#define AUMENTO_VELOCIDAD 0.05
//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena() : objetos(N_OBJ, nullptr), se_dibuja(N_OBJ, false), traslaciones(N_OBJ, Tupla3f(0, 0, 0)), escalados(N_OBJ, Tupla3f(1, 1, 1)) {
    Front_plane = 50.0;
    Back_plane = 2000.0;
    Observer_distance = 4 * Front_plane;
    Observer_angle_x = 0.0;
    Observer_angle_y = 0.0;

    modos[(int) ModoVisualizacion::PUNTOS] = ModoVisualizacion::PUNTOS;
    modos[(int) ModoVisualizacion::ALAMBRE] = ModoVisualizacion::ALAMBRE;
    modos[(int) ModoVisualizacion::SOLIDO] = ModoVisualizacion::SOLIDO;


    modo_activo[(int) ModoVisualizacion::PUNTOS] = modo_activo[(int) ModoVisualizacion::ALAMBRE] = false;

    modo_activo[(int) ModoVisualizacion::SOLIDO] = true;// por defecto se dibuja en modo solido

    velocidad_animacion = velocidad_mochila = velocidad_pierna = velocidad_rodilla = 1;
    luz_d = new LuzDireccional(Tupla2f(ALPHA_INICIAL, BETA_INICIAL), GL_LIGHT1, Tupla4f(0, 0, 0, 1), Tupla4f(1, 1, 1, 1), Tupla4f(1, 1, 1, 1));
    luz_a = new LuzAnimada();

    cuadro = new Cuadro_textura("textures/cuadro.jpg",100,100);
    suelo = new Cuadro_textura("textures/suelo.jpg",1000,1000);
    dado = new Cubo_textura("textures/dice.jpg", 100);
    dibuja_diferido = true;// por defecto dibuja en modo diferido
    luz_d_act = true;
    dibuja_tapas = true;
    dibuja_cabeza = true;
    tipo_luz = ModoLuz::SUAVE;
    modoMenu = NADA;
    ajedrez = false;
    animacion_automatica = false;
    movimiento_natural = true;

    ejes.changeAxisSize(5000);
    //objetos
    amongus = new Tripulante_mochila();
    mesa = new Mesa();
    luz_animada_act = true;
    luz_mesa_act = true;
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar(int UI_window_width, int UI_window_height) {
    glClearColor(1.0, 1.0, 1.0, 1.0);// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

    glEnable(GL_DEPTH_TEST);// se habilita el z-bufer
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);


    Width = UI_window_width / 10;
    Height = UI_window_height / 10;
    change_projection(float(UI_window_width) / float(UI_window_height));
    glViewport(0, 0, UI_window_width, UI_window_height);

    std::cout << "MENÚ: " << std::endl;
    std::cout << "\"O\" para selección de objeto" << std::endl;
    std::cout << "\"V\" para selección de modo de visualización" << std::endl;
    std::cout << "\"D\" para selección de modo de dibujado" << std::endl;
    std::cout << "\"A\" para activar/desactivar animacion automatica" << std::endl;
    std::cout << "\"S\" para el menu de velocidades" << std::endl;
    std::cout << "\"M\" para animacion manual" << std::endl;
    std::cout << "\"Q\" para salir del modo angulo" << std::endl;
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar() {
    glScalef(1.5, 1.5, 1.5);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Limpiar la pantalla
    int j = 0;
    change_observer();
    ejes.draw();

    if (tipo_luz != ModoLuz::NINGUNA) {
        glEnable(GL_LIGHTING);
        modo_activo[(int) ModoVisualizacion::SOLIDO] = true;
    }


    for (int i = 0; i < N_MODOS; i++) {
        if (modo_activo[i]) {
            glPushMatrix();
            glScalef(10, 10, 10);
            amongus->draw(dibuja_diferido, ajedrez, modos[i], dibuja_cabeza);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-100, -50, -100);
            mesa->draw(dibuja_diferido, ajedrez, modos[i], dibuja_tapas);
            glPopMatrix();

            luz_a->draw(dibuja_diferido, ajedrez, modos[i], luz_animada_act);


            glPushMatrix();
            glTranslatef(150,70,-50);
            cuadro->draw(dibuja_diferido,ajedrez,modos[i]);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,-90,-100);
            glRotatef(-90,1,0,0);
            suelo->draw(dibuja_diferido,ajedrez,modos[i]);
            glPopMatrix();

            glPushMatrix();
            glScalef(0.34,0.34,0.34);
            glTranslatef(-300,-90,250);
            dado->draw(dibuja_diferido,ajedrez,modos[i]);
            glPopMatrix();

            if (luz_d_act) {
                luz_d->activar();
            } else luz_d->desactivar();
            if (luz_mesa_act){
                mesa->luz->activar();
            } else mesa->luz->desactivar();
        }
    }
    luz_a->animar();
    dado->animar();
    //velocidades de animacion
    amongus->setVelocidadAnimacionGeneral(velocidad_animacion);
    amongus->setVelocidadAnimacionMochila(velocidad_mochila);
    amongus->setVelocidadAnimacionPierna(velocidad_pierna);
    amongus->setVelocidadAnimacionRodilla(velocidad_rodilla);
    glDisable(GL_LIGHTING);
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada(unsigned char tecla, int x, int y) {
    using namespace std;
    cout << "Tecla pulsada: '" << tecla << "'" << endl;
    bool salir = false;
    switch (toupper(tecla)) {
        case 'Q':
            if (modoMenu != NADA) {
                modoMenu = NADA;
                std::cout << "Saliendo del modo " << valorMenuActual() << std::endl;
            } else {
                salir = true;
            }
            break;
        case 'O':
            // ESTAMOS EN MODO SELECCION DE OBJETO
            std::cout << "Modo selección de objeto. Pulsa:" << std::endl;
            std::cout << "\"C\" para dibujar cubo" << std::endl;
            std::cout << "\"T\" para dibujar tetraedro" << std::endl;
            std::cout << "\"F\" para dibujar obj_ply" << std::endl;
            std::cout << "\"R\" para dibujar obj_ply_revolucion" << std::endl;
            std::cout << "\"A\" para dibujar obj_revolucion_vector" << std::endl;
            std::cout << "\"L\" para dibujar Cilindro" << std::endl;
            std::cout << "\"E\" para dibujar Esfera" << std::endl;
            std::cout << "\"P\" para dibujar Cono" << std::endl;
            std::cout << "\"X\" para dibujar Peon Rotado sobre el eje X" << std::endl;
            std::cout << "\"Z\" para dibujar Peon Rotado sobre el eje Z" << std::endl;
            std::cout << "\"Q\" para salir del modo objeto" << std::endl;
            modoMenu = SELOBJETO;
            break;
        case 'V':
            // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
            std::cout << "Modo selección de visualizacion. Pulsa:" << std::endl;
            std::cout << "\"P\" para visualizar en modo puntos" << std::endl;
            std::cout << "\"L\" para visualizar en modo líneas" << std::endl;
            std::cout << "\"S\" para visualizar en modo sólido" << std::endl;
            std::cout << "\"A\" para visualizar en modo ajedrez" << std::endl;
            std::cout << "\"I\" para visualizar con iluminación" << std::endl;
            std::cout << "\"Q\" para salir del modo selección visualización" << std::endl;
            modoMenu = SELVISUALIZACION;
            break;
        case 'D':
            if (modoMenu == NADA) {
                // ESTAMOS EN MODO SELECCION DE DIBUJADO
                std::cout << "Modo selección de dibujado. Pulsa:" << std::endl;
                std::cout << "\"1\" para visualizar en modo inmediato (glDrawElements)" << std::endl;
                std::cout << "\"2\" para visualizar en modo diferido (VBO)" << std::endl;
                std::cout << "\"Q\" para salir del modo selección de dibujado" << std::endl;
                modoMenu = SELDIBUJADO;
            }
            if (modoMenu == ANIMACION_MANUAL) {
                modoMenu = ANIM_PIERNA_D;
                std::cout << "Menú de animacion de la pierna derecha:" << std::endl;
                std::cout << "Pulsa: " << std::endl;
                std::cout << "0 para rotar la pierna en el eje X" << std::endl;
                std::cout << "1 para rotar la pierna en el eje Y" << std::endl;
                std::cout << "2 para rotar la pierna en el eje Z" << std::endl;
            }
            break;
            // COMPLETAR con los diferentes opciones de teclado
        case 'C':
            if (modoMenu == SELOBJETO) {
                //                se_dibuja[(int)Objetos_Escena::CUBO] = !se_dibuja[(int) Objetos_Escena::CUBO];
            }
            dibuja_cabeza ^= 1;
            break;

        case 'T':
            if (modoMenu == SELOBJETO) {
                //                se_dibuja[(int)Objetos_Escena::TETRAEDRO] = !se_dibuja[(int) Objetos_Escena::TETRAEDRO];
            }
            if (modoMenu == SELVISUALIZACION) {
                dibuja_tapas ^= 1;
            }
            break;

        case 'F':
            if (modoMenu == SELOBJETO) {
                //                se_dibuja[(int)Objetos_Escena::OBJPLY] = !se_dibuja[(int) Objetos_Escena::OBJPLY];
            }
            break;

        case 'S':
            if (modoMenu == SELVISUALIZACION) {
                modo_activo[(int) ModoVisualizacion::SOLIDO] ^= 1;
                tipo_luz = ModoLuz::NINGUNA;
            }
            if (modoMenu == SELILUMINACION) {
                modo_activo[(int) ModoVisualizacion::SOLIDO] = true;
                tipo_luz = ModoLuz::SUAVE;
            }

            if (modoMenu == NADA) {
                modoMenu = SELVELOCIDAD;
                std::cout << "Menú de seleccion de velocidades de animación. Pulsa: " << std::endl;
                std::cout << "Piernas : P" << std::endl;
                std::cout << "Rodillas: R" << std::endl;
                std::cout << "Mochila: B" << std::endl;
            }
            break;

        case 'A':
            if (modoMenu == NADA) {
                animacion_automatica ^= 1;
                modoMenu = (animacion_automatica) ? ANIMACION_AUTOMATICA : NADA;
                if (animacion_automatica) {
                    std::cout << "Estamos en modo Animacion Automatica. Pulsa: " << std::endl;
                    std::cout << "\"+\"+ para aumentar la velocidad de animación general" << std::endl;
                    std::cout << "\"-\" para disminuir la velocidad de animación general" << std::endl;
                }
            } else if (modoMenu == SELILUMINACION) {
                modoMenu = VARIACION_ALFA;
                std::cout << "cambia a variacion alfa" << std::endl;
            } else if (modoMenu == VARIACION_ALFA) {
                modoMenu = SELILUMINACION;
                std::cout << "cambia a modo iluminacion" << std::endl;
            }
            if (modoMenu == SELVISUALIZACION) {
                tipo_luz = ModoLuz::NINGUNA;
                ajedrez ^= 1;
                std::cout << "cambia modo ajedrez" << std::endl;
            }

            break;
        case 'N':
            if (modoMenu == ANIMACION_AUTOMATICA) {
                movimiento_natural ^= 1;
                amongus->resetearPosicion();
            }
            break;
        case 'M':
            if (modoMenu == ANIMACION_AUTOMATICA || modoMenu == NADA) {
                modoMenu = ANIMACION_MANUAL;
                animacion_automatica = false;
                std::cout << "Animación Manual activada" << std::endl;
                std::cout << "Selecciona la parte a animar: " << std::endl;
                std::cout << "Pierna Izquierda: I" << std::endl;
                std::cout << "Pierna Derecha: D" << std::endl;
                std::cout << "Rodilla Izquierda: H" << std::endl;
                std::cout << "Rodilla Derecha: K" << std::endl;
                std::cout << "Ambas piernas (animación de andar): P" << std::endl;
                std::cout << "Mochila: B" << std::endl;
            }
            break;
        case 'H':
            if (modoMenu == ANIMACION_MANUAL) {
                modoMenu = ANIM_RODILLA_I;
                std::cout << "Menú de animacion de la rodilla izquierda:" << std::endl;
                std::cout << "Pulsa: " << std::endl;
                std::cout << "+ para estirar la rodilla" << std::endl;
                std::cout << "- para contraer la rodilla" << std::endl;
            }
            break;
        case 'K':
            if (modoMenu == ANIMACION_MANUAL) {
                modoMenu = ANIM_RODILLA_D;
                std::cout << "Menú de animacion de la rodilla derecha:" << std::endl;
                std::cout << "Pulsa: " << std::endl;
                std::cout << "+ para estirar la rodilla" << std::endl;
                std::cout << "- para contraer la rodilla" << std::endl;
            }
            break;
        case 'B':
            if (modoMenu == SELILUMINACION) {
                modoMenu = VARIACION_BETA;
            } else if (modoMenu == VARIACION_BETA) {
                modoMenu = SELILUMINACION;
            }
            if (modoMenu == ANIMACION_MANUAL) {
                modoMenu = ANIM_MOCH;
                std::cout << "Menú de animacion de la mochila:" << std::endl;
                std::cout << "Pulsa: " << std::endl;
                std::cout << "+ para subir la mochila" << std::endl;
                std::cout << "- para bajar la mochila" << std::endl;
            }
            if (modoMenu == SELVELOCIDAD) {
                modoMenu = VEL_MOCHILA;
                std::cout << "Pulsa - para disminuir la velocidad de la mochila o + para aumentarla" << std::endl;
            }
            break;
        case 'L':
            if (modoMenu == SELVISUALIZACION) {
                modo_activo[(int) ModoVisualizacion::ALAMBRE] ^= 1;
                tipo_luz = ModoLuz::NINGUNA;
            }
            if (modoMenu == SELOBJETO) {
                //                se_dibuja[(int)Objetos_Escena::CILINDRO] = !se_dibuja[(int) Objetos_Escena::CILINDRO];
            }
            break;

        case 'E':
            if (modoMenu == SELOBJETO) {
                //                se_dibuja[(int)Objetos_Escena::ESFERA] = !se_dibuja[(int) Objetos_Escena::ESFERA];
            }
            break;

        case 'P':
            if (modoMenu == SELVISUALIZACION) {
                modo_activo[(int) ModoVisualizacion::PUNTOS] ^= 1;
                tipo_luz = ModoLuz::NINGUNA;
            }
            if (modoMenu == SELOBJETO) {
                //                se_dibuja[(int)Objetos_Escena::CONO] = !se_dibuja[(int) Objetos_Escena::CONO];
            }
            if (modoMenu == SELVELOCIDAD) {
                modoMenu = VEL_PIERNA;
                std::cout << "Pulsa - para disminuir la velocidad de las piernas o + para aumentarla" << std::endl;
            }

            if (modoMenu == ANIMACION_MANUAL) {
                modoMenu = ANIM_2_PIERNAS;
                std::cout << "Menú de animacion de las piernas:" << std::endl;
                std::cout << "Pulsa: " << std::endl;
                std::cout << "+ para avanzar la animación" << std::endl;
            }
            break;
        case 'X':
            if (modoMenu == SELOBJETO) {
                //                se_dibuja[(int)Objetos_Escena::PEON_X] = !se_dibuja[(int) Objetos_Escena::PEON_X];
            }
            break;
        case 'Z':
            if (modoMenu == SELOBJETO) {
                //                se_dibuja[(int)Objetos_Escena::PEON_Z] = !se_dibuja[(int) Objetos_Escena::PEON_Z];
            }
            break;

        case 'R':
            if (modoMenu == SELOBJETO) {
                //                se_dibuja[(int)Objetos_Escena::OBJPLY_REV] = !se_dibuja[(int) Objetos_Escena::OBJPLY_REV];
            }
            if (modoMenu == SELVELOCIDAD) {
                modoMenu = VEL_RODILLA;
                std::cout << "Pulsa - para disminuir la velocidad de las rodillas o + para aumentarla" << std::endl;
            }
            break;
        case 'I':
            if (modoMenu == SELVISUALIZACION) {
                modoMenu = SELILUMINACION;
                std::cout << "Modo iluminacion" << std::endl;
                if (tipo_luz == ModoLuz::NINGUNA) {
                    tipo_luz = ModoLuz::SUAVE;
                    modo_activo[(int) ModoVisualizacion::ALAMBRE] = modo_activo[(int) ModoVisualizacion::PUNTOS] = false;
                } else {
                    tipo_luz = ModoLuz::NINGUNA;
                }
            }

            if (modoMenu == ANIMACION_MANUAL) {
                modoMenu = ANIM_PIERNA_I;
                std::cout << "Menú de animacion de la pierna izquierda:" << std::endl;
                std::cout << "Pulsa: " << std::endl;
                std::cout << "0 para rotar la pierna en el eje X" << std::endl;
                std::cout << "1 para rotar la pierna en el eje Y" << std::endl;
                std::cout << "2 para rotar la pierna en el eje Z" << std::endl;
            }

            break;
        case '<':

            if (modoMenu == VARIACION_ALFA) {
                luz_d->variarAnguloAlpha(M_PI / 30.0);
            } else if (modoMenu == VARIACION_BETA) {
                luz_d->variarAnguloBeta(M_PI / 30.0);
            }

            break;
        case '>':

            if (modoMenu == VARIACION_ALFA) {
                luz_d->variarAnguloAlpha(-M_PI / 30.0);
            } else if (modoMenu == VARIACION_BETA) {
                luz_d->variarAnguloBeta(-M_PI / 30.0);
            }
            break;

        case '+':
            if (modoMenu == VEL_MOCHILA) {
                velocidad_mochila += AUMENTO_VELOCIDAD;
            }
            if (modoMenu == VEL_PIERNA) {
                velocidad_pierna += AUMENTO_VELOCIDAD;
            }
            if (modoMenu == VEL_RODILLA) {
                velocidad_pierna += AUMENTO_VELOCIDAD;
            }

            if (modoMenu == ANIMACION_AUTOMATICA) {
                velocidad_animacion += AUMENTO_VELOCIDAD;
            }

            if (modoMenu == ANIM_MOCH) {
                amongus->siguienteAnimacionMochila(1);
            }

            if (modoMenu == ANIM_2_PIERNAS) {
                amongus->siguienteAnimacionPiernas();
            }

            if (modoMenu == ANIM_PIERNA_I_X) {
                amongus->siguienteAnimacionEjeXPiernaIzda(1);
            }
            if (modoMenu == ANIM_PIERNA_I_Y) {
                amongus->siguienteAnimacionEjeYPiernaIzda(1);
            }
            if (modoMenu == ANIM_PIERNA_I_Z) {
                amongus->siguienteAnimacionEjeZPiernaIzda(1);
            }

            if (modoMenu == ANIM_PIERNA_D_X) {
                amongus->siguienteAnimacionEjeXPiernaDcha(1);
            }
            if (modoMenu == ANIM_PIERNA_D_Y) {
                amongus->siguienteAnimacionEjeYPiernaDcha(1);
            }
            if (modoMenu == ANIM_PIERNA_D_Z) {
                amongus->siguienteAnimacionEjeZPiernaDcha(1);
            }

            if (modoMenu == ANIM_RODILLA_D) {
                amongus->siguienteAnimacionRodillaDcha(1);
            }

            if (modoMenu == ANIM_RODILLA_I) {
                amongus->siguienteAnimacionRodillaIzda(1);
            }

            break;
        case '-':

            if (modoMenu == VEL_MOCHILA) {
                velocidad_mochila -= AUMENTO_VELOCIDAD;
            }
            if (modoMenu == VEL_PIERNA) {
                velocidad_pierna -= AUMENTO_VELOCIDAD;
            }
            if (modoMenu == VEL_RODILLA) {
                velocidad_pierna -= AUMENTO_VELOCIDAD;
            }

            if (modoMenu == ANIMACION_AUTOMATICA) {
                velocidad_animacion -= AUMENTO_VELOCIDAD;
            }

            if (modoMenu == ANIM_MOCH) {
                amongus->siguienteAnimacionMochila(-1);
            }

            if (modoMenu == ANIM_PIERNA_I_X) {
                amongus->siguienteAnimacionEjeXPiernaIzda(-1);
            }
            if (modoMenu == ANIM_PIERNA_I_Y) {
                amongus->siguienteAnimacionEjeYPiernaIzda(-1);
            }
            if (modoMenu == ANIM_PIERNA_I_Z) {
                amongus->siguienteAnimacionEjeZPiernaIzda(-1);
            }

            if (modoMenu == ANIM_PIERNA_D_X) {
                amongus->siguienteAnimacionEjeXPiernaDcha(-1);
            }
            if (modoMenu == ANIM_PIERNA_D_Y) {
                amongus->siguienteAnimacionEjeYPiernaDcha(-1);
            }
            if (modoMenu == ANIM_PIERNA_D_Z) {
                amongus->siguienteAnimacionEjeZPiernaDcha(-1);
            }

            if (modoMenu == ANIM_RODILLA_D) {
                amongus->siguienteAnimacionRodillaDcha(-1);
            }

            if (modoMenu == ANIM_RODILLA_I) {
                amongus->siguienteAnimacionRodillaIzda(-1);
            }

            break;
        case '0':
            if (modoMenu == SELILUMINACION) {
                luz_mesa_act ^= 1;
            }

            if (modoMenu == ANIM_PIERNA_D) {
                modoMenu = ANIM_PIERNA_D_X;
                std::cout << "Rotacion Pierna Derecha EJE X" << std::endl;
                std::cout << "+ para aumentar grado de rotación eje X" << std::endl;
                std::cout << "- para disminuir grado de rotación eje X" << std::endl;
            }

            if (modoMenu == ANIM_PIERNA_I) {
                modoMenu = ANIM_PIERNA_I_X;
                std::cout << "Rotacion Pierna Izquierda EJE X" << std::endl;
                std::cout << "+ para aumentar grado de rotación eje X" << std::endl;
                std::cout << "- para disminuir grado de rotación eje X" << std::endl;
            }

            break;
        case '1':
            if (modoMenu == SELDIBUJADO) {
                dibuja_diferido = false;
                std::cout << "Dibujando en modo inmediato" << std::endl;
            }
            if (modoMenu == SELILUMINACION) {
                luz_d_act ^= 1;
            }

            if (modoMenu == ANIM_PIERNA_D) {
                modoMenu = ANIM_PIERNA_D_Y;
                std::cout << "Rotacion Pierna Derecha EJE Y" << std::endl;
                std::cout << "+ para aumentar grado de rotación eje Y" << std::endl;
                std::cout << "- para disminuir grado de rotación eje Y" << std::endl;
            }

            if (modoMenu == ANIM_PIERNA_I) {
                modoMenu = ANIM_PIERNA_I_Y;
                std::cout << "Rotacion Pierna Izquierda EJE Y" << std::endl;
                std::cout << "+ para aumentar grado de rotación eje Y" << std::endl;
                std::cout << "- para disminuir grado de rotación eje Y" << std::endl;
            }

            break;
        case '2':
            if (modoMenu == SELILUMINACION) {
                luz_animada_act ^= 1;
            }

            if (modoMenu == SELDIBUJADO) {
                std::cout << "Dibujando en modo diferido" << std::endl;
                dibuja_diferido = true;
            }

            if (modoMenu == ANIM_PIERNA_D) {
                modoMenu = ANIM_PIERNA_D_Z;
                std::cout << "Rotacion Pierna Derecha EJE Z" << std::endl;
                std::cout << "+ para aumentar grado de rotación eje Z" << std::endl;
                std::cout << "- para disminuir grado de rotación eje Z" << std::endl;
            }

            if (modoMenu == ANIM_PIERNA_I) {
                modoMenu = ANIM_PIERNA_I_Z;
                std::cout << "Rotacion Pierna Izquierda EJE Z" << std::endl;
                std::cout << "+ para aumentar grado de rotación eje Z" << std::endl;
                std::cout << "- para disminuir grado de rotación eje Z" << std::endl;
            }
            break;
    }
    return salir;
}
//**************************************************************************

void Escena::teclaEspecial(int Tecla1, int x, int y) {
    switch (Tecla1) {
        case GLUT_KEY_LEFT:
            Observer_angle_y--;
            break;
        case GLUT_KEY_RIGHT:
            Observer_angle_y++;
            break;
        case GLUT_KEY_UP:
            Observer_angle_x--;
            break;
        case GLUT_KEY_DOWN:
            Observer_angle_x++;
            break;
        case GLUT_KEY_PAGE_UP:
            Observer_distance *= 1.2;
            break;
        case GLUT_KEY_PAGE_DOWN:
            Observer_distance /= 1.2;
            change_observer();

            break;
    }

    //std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection(const float ratio_xy) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const float wx = float(Height) * ratio_xy;
    glFrustum(-wx, wx, -Height, Height, Front_plane, Back_plane);
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar(int newWidth, int newHeight) {
    Width = newWidth / 10;
    Height = newHeight / 10;
    change_projection(1/(float(newHeight) / float(newWidth)));
    glViewport(0, 0, newWidth, newHeight);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer() {
    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -Observer_distance);
    glRotatef(Observer_angle_y, 0.0, 1.0, 0.0);
    glRotatef(Observer_angle_x, 1.0, 0.0, 0.0);
}
void Escena::dibujaObjeto(Malla3D *obj, const Tupla3f &tr, const Tupla3f &esc, ModoVisualizacion modo) {
    glPushMatrix();
    glTranslatef(tr(0), tr(1), tr(2));
    glScalef(esc(0), esc(1), esc(2));
    ObjRevolucion *obj_rev = dynamic_cast<ObjRevolucion *>(obj);
    if (obj_rev != nullptr)
        obj_rev->draw(dibuja_diferido, ajedrez, modo, dibuja_tapas);
    else
        obj->draw(dibuja_diferido, ajedrez, modo);
    glPopMatrix();
}
Escena::~Escena() {
    for (int i = 0; i < objetos.size(); i++) {
        delete objetos[i];
    }
}
void Escena::animarModeloJerarquico() {
    if (animacion_automatica)
        amongus->animacionAutomatica(movimiento_natural);
}

std::string Escena::valorMenuActual() {
    std::string valor;
    switch (modoMenu) {
        case NADA:
            valor = "NADA";
            break;
        case SELOBJETO:
            valor = "SELECCION OBJETO";
            break;
        case SELVISUALIZACION:
            valor = "SELECCICON VISUALIZACION";
            break;
        case SELDIBUJADO:
            valor = "SELECCION DIBUJADO";
            break;
        case SELILUMINACION:
            valor = "SELECCION ILUMINACION";
            break;
        case VARIACION_ALFA:
            valor = "VARIACION ALFA";
            break;
        case VARIACION_BETA:
            valor = "VARIACION BETA";
            break;
        case ANIMACION_AUTOMATICA:
            valor = "ANIMACION AUTOMATICA";
            break;
        case ANIMACION_MANUAL:
            valor = "ANIMACION MANUAL";
            break;
        case ANIM_MOCH:
            valor = "ANIMACION MOCHILA";
            break;

        case SELVELOCIDAD:
            valor = "SELECCION DE VELOCIDAD";
            break;
        default:
            valor = "[]";
            break;
    }
    return valor;
}
