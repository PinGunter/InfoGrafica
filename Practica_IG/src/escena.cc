

#include <aux.h>// includes de OpenGL/glut/glew, windows, y librería std de C++
#include <escena.h>
#include <malla.h>// objetos: Cubo y otros....
#define N_OBJ 10
#define LUZ(i) GL_LIGHTi
//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena() : se_dibuja(N_OBJ,false), traslaciones(N_OBJ,Tupla3f(0,0,0)), escalados(N_OBJ,Tupla3f(1,1,1)){
    Front_plane = 50.0;
    Back_plane = 2000.0;
    Observer_distance = 4 * Front_plane;
    Observer_angle_x = 0.0;
    Observer_angle_y = 0.0;

    modos[(int) ModoVisualizacion::PUNTOS] = ModoVisualizacion::PUNTOS;
    modos[(int) ModoVisualizacion::ALAMBRE] = ModoVisualizacion::ALAMBRE;
    modos[(int) ModoVisualizacion::SOLIDO] = ModoVisualizacion::SOLIDO;
    tipo_luz = ModoLuz::NINGUNA;


    modo_activo[(int) ModoVisualizacion::PUNTOS] = modo_activo[(int) ModoVisualizacion::ALAMBRE] = false;

    modo_activo[(int) ModoVisualizacion::SOLIDO] = true;// por defecto se dibuja en modo solido

    std::vector<Tupla3f> v_rev{
            Tupla3f(5, 0, 0),
            Tupla3f(5, 10, 0),
    };

    ejes.changeAxisSize(5000);

    objetos.reserve(N_OBJ);
    objetos[(int)Objetos_Escena::CUBO] = new Cubo(50);
//    objetos[(int)Objetos_Escena::TETRAEDRO] = new Tetraedro(25);
//    objetos[(int)Objetos_Escena::OBJPLY] = new ObjPLY("plys/amogus");
//    objetos[(int)Objetos_Escena::OBJPLY_REV] = new ObjRevolucion("plys/peon",Eje_rotacion::EJE_Y,20);
//    objetos[(int)Objetos_Escena::REV_VEC] = new ObjRevolucion(v_rev,Eje_rotacion::EJE_Y,20);
    objetos[(int)Objetos_Escena::PEON_X] = new ObjRevolucion("plys/peon",Eje_rotacion::EJE_Y,20);
    objetos[(int)Objetos_Escena::PEON_X]->setMaterial(Material(Tupla4f(0.1,0.1,0.1,1),Tupla4f(0,0,0,1),Tupla4f(1,1,1,1), 0));
    objetos[(int)Objetos_Escena::PEON_Z] = new ObjRevolucion("plys/peon",Eje_rotacion::EJE_Y,20);
    objetos[(int)Objetos_Escena::PEON_Z]->setMaterial(Material(Tupla4f(0.1,0.1,0.1,1),Tupla4f(1,1,1,1),Tupla4f(0.2,0.2,0.2,1), 50));

//    objetos[(int)Objetos_Escena::ESFERA]= new Esfera(20,20,10);
//    objetos[(int)Objetos_Escena::CONO]= new Cono(20, 20, 20, 10, true);
//    objetos[(int)Objetos_Escena::CILINDRO]= new Cilindro(3, 20, 20, 20, true, true);

    traslaciones[(int)Objetos_Escena::CUBO] = Tupla3f(-50,50,-50);
    traslaciones[(int)Objetos_Escena::PEON_X] = Tupla3f(50,50,50);
    traslaciones[(int)Objetos_Escena::PEON_Z] = Tupla3f (-50,50,50);
    escalados[(int)Objetos_Escena::PEON_Z] = escalados[(int)Objetos_Escena::PEON_X] = Tupla3f(25,25,25);


    luces.reserve(2);
    luces[0] = new LuzPosicional(Tupla3f(0,0,0),GL_LIGHT0,Tupla4f(0.1,0.1,0.1,1),Tupla4f(1,1,1,1),Tupla4f(1,1,1,1));
    luces[1] = new LuzDireccional(Tupla2f(1,1),GL_LIGHT1,Tupla4f(0,0,0,1),Tupla4f(1,1,1,1),Tupla4f(1,1,1,1));    dibuja_diferido = true;// por defecto dibuja en modo diferido
    dibuja_tapas = true;
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
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);


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
    int j = 0;
    ejes.draw();
    if (tipo_luz != ModoLuz::NINGUNA) {
        glEnable(GL_LIGHTING);
        modo_activo[(int) ModoVisualizacion::SOLIDO] = true;
        for (int j=0; j < luces.size(); j++){
            luces[j]->activar();
        }
    }

    for (int i=0; i < N_MODOS; i++){
        for (int j=0; j < N_OBJ; j++) {
            if (modo_activo[i]) {
                if (se_dibuja[j]) {
                    dibujaObjeto(objetos[j],traslaciones[j],escalados[j],modos[i]);
                }
            }
        }

    }
//
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
            } else if (modoMenu == SELVISUALIZACION){
                std::cout << "Saliendo del modo iluminación" << std::endl;
                modoMenu = SELVISUALIZACION;
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
            std::cout << "Modo selección de objeto. Pulsa:" << std::endl;
            std::cout << "\"P\" para visualizar en modo puntos" << std::endl;
            std::cout << "\"L\" para visualizar en modo líneas" << std::endl;
            std::cout << "\"S\" para visualizar en modo sólido" << std::endl;
            std::cout << "\"A\" para visualizar en modo ajedrez" << std::endl;
            std::cout << "\"I\" para visualizar con iluminación" << std::endl;
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
            if (modoMenu == SELOBJETO) {
                se_dibuja[(int)Objetos_Escena::CUBO] = !se_dibuja[(int) Objetos_Escena::CUBO];
            }
            break;

        case 'T':
            if (modoMenu == SELOBJETO) {
                se_dibuja[(int)Objetos_Escena::TETRAEDRO] = !se_dibuja[(int) Objetos_Escena::TETRAEDRO];
            }
            if (modoMenu == SELVISUALIZACION) {
                dibuja_tapas ^= 1;
            }
            break;

        case 'F':
            if (modoMenu == SELOBJETO) {
                se_dibuja[(int)Objetos_Escena::OBJPLY] = !se_dibuja[(int) Objetos_Escena::OBJPLY];
            }
            break;

        case 'S':
            if (modoMenu == SELVISUALIZACION) {
                modo_activo[(int) ModoVisualizacion::SOLIDO] ^= 1;
                tipo_luz = ModoLuz::NINGUNA;
            }
            if (modoMenu == SELILUMINACION){
                modo_activo[(int)ModoVisualizacion::SOLIDO] = true;
                tipo_luz = ModoLuz::SUAVE;
            }
            break;

        case 'A':
            if (modoMenu == SELVISUALIZACION) {
                ajedrez ^= 1;
            }
            if (modoMenu == SELOBJETO) {
                se_dibuja[(int)Objetos_Escena::REV_VEC] = !se_dibuja[(int) Objetos_Escena::REV_VEC];
            }
            if (modoMenu == SELILUMINACION){
                modoMenu = VARIACION_ALFA;
            }
            break;
        case 'B':
            if (modoMenu == SELILUMINACION){
                modoMenu = VARIACION_BETA;
            }
            break;
        case 'L':
            if (modoMenu == SELVISUALIZACION) {
                modo_activo[(int) ModoVisualizacion::ALAMBRE] ^= 1;
                tipo_luz = ModoLuz::NINGUNA;
            }
            if (modoMenu == SELOBJETO) {
                se_dibuja[(int)Objetos_Escena::CILINDRO] = !se_dibuja[(int) Objetos_Escena::CILINDRO];
            }
            break;

        case 'E':
            if (modoMenu == SELOBJETO) {
                se_dibuja[(int)Objetos_Escena::ESFERA] = !se_dibuja[(int) Objetos_Escena::ESFERA];
            }
            break;

        case 'P':
            if (modoMenu == SELVISUALIZACION) {
                modo_activo[(int) ModoVisualizacion::PUNTOS] ^= 1;
                tipo_luz = ModoLuz::NINGUNA;
            }
            if (modoMenu == SELOBJETO) {
                se_dibuja[(int)Objetos_Escena::CONO] = !se_dibuja[(int) Objetos_Escena::CONO];
            }
            break;
        case 'X':
            if (modoMenu == SELOBJETO){
                se_dibuja[(int)Objetos_Escena::PEON_X] = !se_dibuja[(int) Objetos_Escena::PEON_X];
            }
            break;
        case 'Z':
            if(modoMenu == SELOBJETO){
                se_dibuja[(int)Objetos_Escena::PEON_Z] = !se_dibuja[(int) Objetos_Escena::PEON_Z];
            }
            break;

        case 'R':
            if (modoMenu == SELOBJETO) {
                se_dibuja[(int)Objetos_Escena::OBJPLY_REV] = !se_dibuja[(int) Objetos_Escena::OBJPLY_REV];
            }
            break;
        case 'I':
            if (modoMenu == SELVISUALIZACION){
                modoMenu = SELILUMINACION;
                std::cout << "Modo iluminacion" << std::endl;
            }
            else if (modoMenu == SELILUMINACION){
                modoMenu = SELVISUALIZACION;
            }

            if (tipo_luz == ModoLuz::NINGUNA){
                tipo_luz = ModoLuz::SUAVE;
                modo_activo[(int)ModoVisualizacion::ALAMBRE] = modo_activo[(int)ModoVisualizacion::PUNTOS] = false;
            } else{
                tipo_luz = ModoLuz::NINGUNA;
            }
            break;
        case '<':

            break;
        case '>':

            break;
        case '0':
            if (modoMenu == SELILUMINACION){
                cout << "luz" << endl;
                if (luces[0]->getActivada()){
                    luces[0]->desactivar();
                } else{
                    luces[0]->activar();
                }
            }
            break;
        case '1':
            if (modoMenu == SELDIBUJADO) {
                dibuja_diferido = false;
                std::cout << "Dibujando en modo inmediato" << std::endl;
            }
            if (modoMenu == SELILUMINACION){
                if (luces[1]->getActivada()){
                    luces[1]->desactivar();
                } else{
                    luces[1]->activar();
                }
            }
            break;
        case '2':
            if (modoMenu == SELDIBUJADO) {
                std::cout << "Dibujando en modo diferido" << std::endl;
                dibuja_diferido = true;
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
void Escena::dibujaObjeto(Malla3D *obj, const Tupla3f &tr, const Tupla3f &esc, ModoVisualizacion modo) {
    glPushMatrix();
    glTranslatef(tr(0),tr(1),tr(2));
    glScalef(esc(0),esc(1),esc(2));
    ObjRevolucion * obj_rev = dynamic_cast <ObjRevolucion*>(obj);
    if (obj_rev != nullptr)
        obj_rev->draw(dibuja_diferido, ajedrez, modo, tipo_luz, dibuja_tapas);
    else
        obj->draw(dibuja_diferido,ajedrez,modo,tipo_luz);
    glPopMatrix();

}
Escena::~Escena() {
    for (int i=0; i < objetos.size(); i++){
        delete objetos[i];
    }
    for (int i=0; i < luces.size(); i++){
        delete luces[i];
    }
}
