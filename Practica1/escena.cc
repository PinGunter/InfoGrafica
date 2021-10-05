

#include "aux.h" // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane = 50.0;
    Back_plane = 2000.0;
    Observer_distance = 4 * Front_plane;
    Observer_angle_x = 0.0;
    Observer_angle_y = 0.0;

    ejes.changeAxisSize(5000);
    cubo = new Cubo(100);
    tetraedro = new Tetraedro(50);
    dibuja_cubo = false;
    dibuja_tetraedro = false;
    dibuja_diferido = true;
    // crear los objetos de la escena....
    // .......completar: ...
    // .....
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar(int UI_window_width, int UI_window_height)
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // se indica cual sera el color para limpiar la ventana	(r,v,a,al)

    glEnable(GL_DEPTH_TEST); // se habilita el z-bufer
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

void Escena::dibujar()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
    change_observer();
    if (dibuja_cubo)
    {
        cubo->draw(modo_visualizacion,dibuja_diferido);
    }
    if (dibuja_tetraedro)
    {
        tetraedro->draw(modo_visualizacion,dibuja_diferido);
    }
    ejes.draw();

    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer
    // cubo.draw()
    // o
    // tetraedro.draw()
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada(unsigned char tecla, int x, int y)
{
    using namespace std;
    cout << "Tecla pulsada: '" << tecla << "'" << endl;
    bool salir = false;
    switch (toupper(tecla))
    {
        case 'Q':
            if (modoMenu == SELOBJETO)
            {
                std::cout << "Saliendo del modo selección objeto" << std::endl;
                modoMenu = NADA;
            }

            else if (modoMenu == SELVISUALIZACION){
                std::cout << "Saliendo del modo selección visualización" << std::endl;
                modoMenu = NADA;
            }

            else if (modoMenu == SELDIBUJADO){
                std::cout << "Saliendo del modo selección de modo de dibujado" << std::endl;
                modoMenu = NADA;
            }

            else if (modoMenu != NADA)
                modoMenu = NADA;
            else
            {
                salir = true;
            }
            break;
        case 'O':
            // ESTAMOS EN MODO SELECCION DE OBJETO
            std::cout << "Modo selección de objeto. Pulsa:" << std::endl;
            std::cout << "\"C\" para dibujar cubo" << std::endl;
            std::cout << "\"T\" para dibujar tetraedro" << std::endl;
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
            // COMPLETAR con los diferentes opciones de teclado
        case 'C':
            if (modoMenu == SELOBJETO)
            {
                dibuja_cubo = true;
                dibuja_tetraedro = false;
            }
            break;
        case 'T':
            if (modoMenu == SELOBJETO)
            {
                dibuja_tetraedro = true;
                dibuja_cubo = false;
            }
            break;
        case 'P':
            if (modoMenu == SELVISUALIZACION){
                modo_visualizacion = GL_POINT;
            }
            break;
        case 'L':
            if (modoMenu == SELVISUALIZACION){
                modo_visualizacion = GL_LINE;
            }
            break;
        case 'S':
            if (modoMenu == SELVISUALIZACION){
                modo_visualizacion = GL_FILL;
            }
            break;
        case 'A':
            if (modoMenu == SELVISUALIZACION){
                modo_visualizacion = 3;
            }
            break;

        case '1':
            if (modoMenu == SELDIBUJADO){
                dibuja_diferido = false;
            }
            break;
        case '2':
            if (modoMenu == SELDIBUJADO){
                dibuja_diferido = true;
            }
    }
    return salir;
}
//**************************************************************************

void Escena::teclaEspecial(int Tecla1, int x, int y)
{
    switch (Tecla1)
    {
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

void Escena::change_projection(const float ratio_xy)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const float wx = float(Height) * ratio_xy;
    glFrustum(-wx, wx, -Height, Height, Front_plane, Back_plane);
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar(int newWidth, int newHeight)
{
    Width = newWidth / 10;
    Height = newHeight / 10;
    change_projection(float(newHeight) / float(newWidth));
    glViewport(0, 0, newWidth, newHeight);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -Observer_distance);
    glRotatef(Observer_angle_y, 0.0, 1.0, 0.0);
    glRotatef(Observer_angle_x, 1.0, 0.0, 0.0);
}
