

#include <aux.h>// includes de OpenGL/glut/glew, windows, y librería std de C++
#include <escena.h>
#include <malla.h>// objetos: Cubo y otros....

#define CUBO 0
#define TETRAEDRO 1
#define OBJ_PLY 2
#define OBJ_PLY_REV 3
#define ESFERA 4
#define CONO 5
#define CILINDRO 6
#define REV_VEC 7
//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena() : objetos{{Cubo(100), false},
                           {Tetraedro(10), false},
                           {ObjPLY("plys/amogus"), false},
                           {ObjRevolucion("plys/peon", 20), false},
                           {Esfera(100, 100, 10), false},
                           {Cono(20, 20, 20, 10, true), false},
                           {Cilindro(3, 20, 20, 20, true, true), false}

                   } {
    Front_plane = 50.0;
    Back_plane = 2000.0;
    Observer_distance = 4 * Front_plane;
    Observer_angle_x = 0.0;
    Observer_angle_y = 0.0;

    modos[PUNTOS_i] = PUNTOS;
    modos[ALAMBRE_i] = ALAMBRE;
    modos[SOLIDO_i] = SOLIDO;

    modo_activo[PUNTOS_i] = modo_activo[ALAMBRE_i] = false;
    modo_activo[SOLIDO_i] = true;// por defecto se dibuja en modo solido
    ejes.changeAxisSize(5000);
    //    cubo = new Cubo(100);
    //    tetraedro = new Tetraedro(50);

    std::vector<Tupla3f> v_rev{
            Tupla3f(0, 0, 0),
            Tupla3f(5, 0, 0),
            Tupla3f(5, 10, 0),
            Tupla3f(0, 10, 0)};
    objetos.push_back({ObjRevolucion(v_rev, 20), false});

    float angulo = 2 * M_PI / objetos.size();
    for (int i = 0; i < objetos.size(); i++) {
        traslaciones.push_back({(float) cos(angulo * i), 0, (float) sin(angulo * i)});
        escalados.push_back({1, 1, 1});
    }
    //    obj_rev_vec = new ObjRevolucion(v_rev,20);
    //    obj_rev_ply = new ObjRevolucion("plys/peon",20);
    //    esfera = new Esfera(100,100,10);
    //    cono = new Cono(20,20,20,10,true);
    //    cilindro = new Cilindro(3,20,20,20, true, true);
    //    amogus = new ObjPLY("plys/amogus");
    //    dibuja_cubo = false;
    //    dibuja_tetraedro = false;
    //    dibuja_ply = false;
    //    dibuja_rev_ply = false;
    //    dibuja_rev_vec = false;
    //    dibuja_esfera = false;
    //    dibuja_cono = false;
    //    dibuja_cilindro = true;
    dibuja_diferido = true;// por defecto dibuja en modo diferido
    dibuja_tapas = false;
    ajedrez = false;
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

    Width = UI_window_width / 10;
    Height = UI_window_height / 10;
    change_projection(float(UI_window_width) / float(UI_window_height));
    glViewport(0, 0, UI_window_width, UI_window_height);

    std::cout << "MENÚ: " << std::endl;
    std::cout << "\"O\" para selección de objeto" << std::endl;
    std::cout << "\"V\" para selección de modo de visualización" << std::endl;
    std::cout << "\"D\" para selección de modo de dibujado" << std::endl;
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
    change_observer();
    ejes.draw();
    for (int k = 0; k < objetos.size(); k++) {
        for (int i = 0; i < 3; i++) {
            if (modo_activo[i]) {
                if (objetos[k].second)
                    dibujaObjeto(traslaciones[k], escalados[k], objetos[k].first, modos[k]);
            }
        }
    }
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
            if (modoMenu == SELOBJETO) {
                std::cout << "Saliendo del modo selección objeto" << std::endl;
                modoMenu = NADA;
            }

            else if (modoMenu == SELVISUALIZACION) {
                std::cout << "Saliendo del modo selección visualización" << std::endl;
                modoMenu = NADA;
            }

            else if (modoMenu == SELDIBUJADO) {
                std::cout << "Saliendo del modo selección de modo de dibujado" << std::endl;
                modoMenu = NADA;
            }

            else if (modoMenu != NADA)
                modoMenu = NADA;
            else {
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
            std::cout << "\"L\" para dibujar cilindro" << std::endl;
            std::cout << "\"E\" para dibujar esfera" << std::endl;
            std::cout << "\"P\" para dibujar cono" << std::endl;
            std::cout << "\"Q\" para salir del modo objeto" << std::endl;
            modoMenu = SELOBJETO;
            break;
        case 'V':
            // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
            std::cout << "Modo selección de objeto. Pulsa:" << std::endl;
            std::cout << "\"P\" para visualizar en modo puntos" << std::endl;
            std::cout << "\"L\" para visualizar en modo líneas" << std::endl;
            std::cout << "\"S\" para visualizar en modo sólido" << std::endl;
            std::cout << "\"A\" para visualizar en modo ajedrez" << std::endl;
            std::cout << "\"Q\" para salir del modo selección visualización" << std::endl;
            modoMenu = SELVISUALIZACION;
            break;
        case 'D':
            // ESTAMOS EN MODO SELECCION DE DIBUJADO
            std::cout << "Modo selección de dibujado. Pulsa:" << std::endl;
            std::cout << "\"1\" para visualizar en modo inmediato (glDrawElements)" << std::endl;
            std::cout << "\"2\" para visualizar en modo diferido (VBO)" << std::endl;
            std::cout << "\"Q\" para salir del modo selección de dibujado" << std::endl;

            modoMenu = SELDIBUJADO;
            break;

        case 'C':
            if (modoMenu == SELOBJETO) {
                objetos[CUBO].second ^= 1;
            }
            break;

        case 'T':
            if (modoMenu == SELOBJETO) {
                objetos[TETRAEDRO].second ^= 1;
            }
            if (modoMenu == SELVISUALIZACION) {
                dibuja_tapas ^= 1;
            }
            break;

        case 'F':
            if (modoMenu == SELOBJETO) {
                objetos[OBJ_PLY].second ^= 1;
            }
            break;

        case 'R':
            if (modoMenu == SELOBJETO) {
                objetos[OBJ_PLY_REV].second ^= 1;
            }
            break;

        case 'A':
            if (modoMenu == SELVISUALIZACION) {
                ajedrez ^= 1;
            }
            if (modoMenu == SELOBJETO) {
                objetos[REV_VEC].second ^= 1;
            }
            break;

        case 'L':
            if (modoMenu == SELVISUALIZACION) {
                modo_activo[ALAMBRE_i] ^= 1;
            }
            if (modoMenu == SELOBJETO) {
                objetos[CILINDRO].second ^= 1;
            }
            break;

        case 'E':
            if (modoMenu == SELOBJETO) {
                objetos[ESFERA].second ^= 1;
            }
            break;

        case 'P':
            if (modoMenu == SELVISUALIZACION) {
                modo_activo[PUNTOS_i] ^= 1;
            }
            if (modoMenu == SELOBJETO) {
                objetos[CONO].second ^= 1;
            }
            break;

        case 'S':
            if (modoMenu == SELVISUALIZACION) {
                modo_activo[SOLIDO_i] ^= 1;
            }
            break;


        case '1':
            if (modoMenu == SELDIBUJADO) {
                dibuja_diferido = false;
                std::cout << "Dibujando en modo inmediato" << std::endl;
            }
            break;
        case '2':
            if (modoMenu == SELDIBUJADO) {
                std::cout << "Dibujando en modo diferido" << std::endl;
                dibuja_diferido = true;
            }
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
    change_projection(float(newHeight) / float(newWidth));
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
void Escena::dibujaObjeto(const std::vector<float> &tr, const std::vector<float> &sc, Malla3D &obj, int id_modo) {
    glPushMatrix();
    glTranslatef(tr[0], tr[1], tr[2]);
    glScalef(sc[0], sc[1], sc[2]);
    obj.draw(dibuja_diferido, ajedrez, modos[id_modo], dibuja_tapas);
    glPopMatrix();
}
