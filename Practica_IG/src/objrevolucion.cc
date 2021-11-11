#include <algorithm>
#include <aux.h>
#include <fstream>
#include <iostream>
#include <objrevolucion.h>


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)


void ObjRevolucion::multMatVec(double (*m)[3], float *v, float *r) {
    for (int i = 0; i < 3; i++) {
        r[i] = 0;
        for (int j = 0; j < 3; j++) {
            r[i] += m[i][j] * v[j];
        }
    }
}
Tupla3f ObjRevolucion::rotarVertice(Eje_rotacion eje, float angulo, const Tupla3f &vertice) {
    double alpha = 0, beta = 0, phi = 0;
    switch (eje){
        case Eje_rotacion::EJE_X:
            alpha = angulo;
            break;
        case Eje_rotacion::EJE_Y:
            beta = angulo;
            break;
        case Eje_rotacion::EJE_Z:
            phi = angulo;
            break;
    }
    double rotacion[3][3]{
            cos(phi) * cos(beta), cos(phi) * sin(beta) * sin(alpha) - sin(phi) * cos(alpha), cos(phi) * sin(beta) * cos(alpha) + sin(phi) * sin(alpha),
            sin(phi) * cos(beta), sin(phi) * sin(beta) * sin(alpha) + cos(phi) * cos(alpha), sin(phi) * sin(beta) * cos(alpha) - cos(phi) * sin(alpha),
            -sin(beta), cos(beta) * sin(alpha), cos(beta) * cos(alpha)};
    float v[3] = {vertice(0), vertice(1), vertice(2)};
    float r[3] = {0};
    multMatVec(rotacion, v, r);
    return Tupla3f(r[0], r[1], r[2]);
}

bool ObjRevolucion::comparaEpsilon(float a, float b, float e) const {
    return abs(a - b) <= e;
}
bool ObjRevolucion::esEjeRotacion(Tupla3f t) const {
    bool salida;
    float epsilon = 0.01;
    switch (mi_eje) {
        case Eje_rotacion::EJE_X:
            salida = comparaEpsilon(t(1), 0, epsilon) && comparaEpsilon(t(2), 0, epsilon);
            break;

        case Eje_rotacion::EJE_Y:
            salida = comparaEpsilon(t(0), 0, epsilon) && comparaEpsilon(t(2), 0, epsilon);
            break;

        case Eje_rotacion::EJE_Z:
            salida = comparaEpsilon(t(0), 0, epsilon) && comparaEpsilon(t(1), 0, epsilon);
            break;
    }
    return salida;
}

ObjRevolucion::ObjRevolucion() {
    offset_tapas = 0;
    init();
}

ObjRevolucion::ObjRevolucion(const std::string &archivo, Eje_rotacion eje, int num_instancias, bool tapa_inf, bool tapa_sup) {
    ply::read_vertices(archivo, perfil_original);
    mi_eje = eje;
    normalizarPerfil();
    offset_tapas = 0;
    crearMalla(perfil_original, num_instancias, tapa_inf, tapa_sup);
    init();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)


ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, Eje_rotacion eje, int num_instancias, bool tapa_inf, bool tapa_sup) {
    perfil_original = archivo;
    mi_eje = eje;
    normalizarPerfil();
    offset_tapas = 0;
    crearMalla(perfil_original, num_instancias, tapa_inf, tapa_sup);
    init();
}

void ObjRevolucion::normalizarPerfil() {
    Tupla3f aux;
    bool es_descendente = false;
    Tupla3f *tapa_inf_ptr = nullptr, *tapa_sup_ptr = nullptr;
    switch (mi_eje)
    {
        case Eje_rotacion::EJE_X:
            es_descendente = (perfil_original.at(0)(0) >= perfil_original.at(perfil_original.size() - 1)(0));
            break;
        case Eje_rotacion::EJE_Y:
            es_descendente = (perfil_original.at(0)(1) >= perfil_original.at(perfil_original.size() - 1)(1));
            break;
        case Eje_rotacion::EJE_Z:
            es_descendente = (perfil_original.at(0)(2) >= perfil_original.at(perfil_original.size() - 1)(2));
            break;
    }

    if (es_descendente) {
        for (int i = 0; i < perfil_original.size() / 2; i++) {
            aux = perfil_original[i];
            perfil_original[i] = perfil_original[perfil_original.size() - 1 - i];
            perfil_original[perfil_original.size() - 1 - i] = aux;
        }
    }

    //comprobamos si hay tapas => hay vértice inicial y/o final que cumple esEjeRotacion();
    if (esEjeRotacion(*perfil_original.begin())) {//tapa inferior
        vt_inf = *perfil_original.begin();
        tapa_inf_ptr = & vt_inf;
    }
    if (esEjeRotacion(*(--perfil_original.end()))) {//tapa superior
        vt_sup = *(--perfil_original.end());
        tapa_sup_ptr = & vt_sup;
    }

    //borramos las tapas del vector, importante borrar primero la final para no cambiar los indices
    if (tapa_sup_ptr != nullptr) perfil_original.erase(--perfil_original.end());
    if (tapa_inf_ptr != nullptr) perfil_original.erase(perfil_original.begin());

    //si no habia tapas las generamos
    if (tapa_inf_ptr == nullptr) {
        switch (mi_eje) {
            case Eje_rotacion::EJE_X:
                vt_inf = Tupla3f(perfil_original.at(0)(0), 0, 0);
                break;

            case Eje_rotacion::EJE_Y:
                vt_inf = Tupla3f(0, perfil_original.at(0)(1), 0);
                break;

            case Eje_rotacion::EJE_Z:
                vt_inf = Tupla3f(0, 0, perfil_original.at(0)(2));
                break;
        }
    }

    if (tapa_sup_ptr == nullptr) {
        switch (mi_eje) {
            case Eje_rotacion::EJE_X:
                vt_sup = Tupla3f(perfil_original.at(perfil_original.size()-1)(0), 0, 0);
                break;

            case Eje_rotacion::EJE_Y:
                vt_sup = Tupla3f(0, perfil_original.at(perfil_original.size()-1)(1), 0);
                break;

            case Eje_rotacion::EJE_Z:
                vt_sup = Tupla3f(0, 0, perfil_original.at(perfil_original.size()-1)(2));
                break;
        }
    }
    std::cout << "Tapa inferior " << vt_inf << std::endl;
    std::cout << "Tapa superior " << vt_sup << std::endl;
}

void ObjRevolucion::crearVertices(const std::vector<Tupla3f> &perfil_original, const int num_instancias_perf) {
    float angulo = 0.0;
    Tupla3f vert;
    for (int i = 0; i < num_instancias_perf; i++) {
        for (int j = 0; j < perfil_original.size(); j++) {
            angulo = 2.0 * M_PI * i / num_instancias_perf;
            vert = rotarVertice(mi_eje, angulo, perfil_original[j]);
            v.push_back(vert);
        }
    }
}


void ObjRevolucion::crearMalla(const std::vector<Tupla3f> &perfil_original, const int num_instancias_perf, bool tapa_inf, bool tapa_sup) {
    crearVertices(perfil_original, num_instancias_perf);
    int a, b;
    for (int i = 0; i < num_instancias_perf; i++) {
        for (int j = 0; j < perfil_original.size() - 1; j++) {
            a = perfil_original.size() * i + j;
            b = perfil_original.size() * ((i + 1) % num_instancias_perf) + j;
            f.push_back(Tupla3i(a, b, b + 1));
            f.push_back(Tupla3i(a, b + 1, a + 1));
        }
    }
    if (tapa_inf || tapa_sup)
        crearTapas(tapa_inf, tapa_sup, num_instancias_perf);
}


void ObjRevolucion::crearTapas(bool inf, bool sup, int num_instancias) {
    int a, b;
    int n_tri_pretapa = f.size();
    if (inf) {
        v.push_back(vt_inf);
        for (int i = 0; i < num_instancias; i++) {
            a = perfil_original.size() * i;
            b = perfil_original.size() * ((i + 1) % num_instancias);
            f.push_back(Tupla3i(b, a, v.size() - 1));
        }
    }
    if (sup) {
        v.push_back(vt_sup);
        for (int i = 0; i < num_instancias; i++) {
            a = perfil_original.size() * i + perfil_original.size() - 1;
            b = perfil_original.size() * ((i + 1) % num_instancias) + perfil_original.size() - 1;
            f.push_back(Tupla3i(a, b, v.size() - 1));
        }
    }
    offset_tapas = n_tri_pretapa;
    if (offset_tapas == 0) {
        offset_tapas = f.size();
    }
}
void ObjRevolucion::init() {
    Tupla4f ambiente (1,1,0,0.5);
    Tupla4f especular (1,1,0,0.5);
    Tupla4f difuso (1,1,0,0.5);

    inicializar(Tupla3f(0, 1, 0),
                Tupla3f(1, 0, 0),
                Tupla3f(0, 0, 1),
                Tupla3f(1, 0.24, 0.71), ambiente, especular, difuso, 4);
}
bool ObjRevolucion::esObjRevolucion() {
    return true;
}


void ObjRevolucion::draw(bool dibuja_diferido, bool ajedrez, ModoVisualizacion modo, ModoLuz iluminacion, bool tapas) {
    switch (modo) {
        case ModoVisualizacion::PUNTOS:
            selector_color = &c_vert;
            selector_color_vbo = PUNTOS_c;
            break;
        case ModoVisualizacion::ALAMBRE:
            selector_color = &c_aris;
            selector_color_vbo = ALAMBRE_c;
            break;
        case ModoVisualizacion::SOLIDO:
            selector_color = &c_cara;
            selector_color_vbo = SOLIDO_c;
            break;
    }
    if (dibuja_diferido) {
        if (ajedrez) draw_AjedrezDiferido(selector_color_vbo, tapas, modo, iluminacion);
        else
            draw_ModoDiferido(selector_color_vbo, tapas, modo, iluminacion);
    } else {
        if (ajedrez) draw_AjedrezInmediato(selector_color, tapas, modo, iluminacion);
        else
            draw_ModoInmediato(selector_color, tapas, modo, iluminacion);
    }
}


void ObjRevolucion::draw_ModoInmediato(std::vector<Tupla3f> *color, bool tapas, ModoVisualizacion modo, ModoLuz iluminacion) {
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v.data());
    glPointSize(8);
    int tam = f.size() - (f.size() - offset_tapas);
    if (tapas) {
        tam = f.size();
    }
    glColorPointer(3, GL_FLOAT, 0, color->data());
    glPolygonMode(GL_FRONT, map_modo(modo));
    glDrawElements(GL_TRIANGLES, tam * 3, GL_UNSIGNED_INT, f.data());

    glDisableClientState(GL_VERTEX_ARRAY);
}

void ObjRevolucion::draw_AjedrezInmediato(std::vector<Tupla3f> *color, bool tapas, ModoVisualizacion modo, ModoLuz iluminacion) {
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v.data());
    glPointSize(8);
    int tam = f.size(), iter_tapa = 1, offset = 0, iter = 1, tam_tapas = f.size() - offset_tapas;
    std::vector<Tupla3f> *color_dibujado = color;
    if (tapas) iter_tapa = 2;
    iter = 2;
    tam -= tam_tapas;
    tam /= 2;

    // como es el modo ajedrez, en el modo solido dibujamos 2 veces
    // una con las caras pares (la primera mitad) y otra vez
    // con las caras impares (la segunda mitad)
    for (int i = 0; i < iter_tapa; i++) {
        for (int j = 0; j < iter; j++) {
            glColorPointer(3, GL_FLOAT, 0, color_dibujado->data());
            glPolygonMode(GL_FRONT, map_modo(modo));
            glDrawElements(GL_TRIANGLES, tam * 3, GL_UNSIGNED_INT, f[offset]);
            color_dibujado = &c_ajedrez;
            offset += tam;
        }
        color_dibujado = color;
        offset = offset_tapas;
        tam = tam_tapas / 2;
    }


    glDisableClientState(GL_VERTEX_ARRAY);
}
void ObjRevolucion::draw_ModoDiferido(GLuint color_id, bool tapas, ModoVisualizacion modo, ModoLuz iluminacion) {
    //Creacion de VBOs
    if (id_vbo_vertices == 0) {
        id_vbo_vertices = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * v.size(), v.data());
    }

    if (id_vbo_tri == 0) {
        id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 3 * f.size(), f.data());
    }
    //VBOs de los vectores de colores
    if (id_vbo_color_v == 0) {
        ids_colores[PUNTOS_c] = id_vbo_color_v = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_vert.size(), c_vert.data());
    }
    if (id_vbo_color_a == 0) {
        ids_colores[ALAMBRE_c] = id_vbo_color_a = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_aris.size(), c_aris.data());
    }
    if (id_vbo_color_c == 0) {
        ids_colores[SOLIDO_c] = id_vbo_color_c = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_cara.size(), c_cara.data());
    }
    if (id_vbo_color_aj == 0) {
        ids_colores[AJEDREZ_c] = id_vbo_color_aj = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_ajedrez.size(), c_ajedrez.data());
    }
    glBindBuffer(GL_ARRAY_BUFFER, id_vbo_vertices);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glPointSize(8);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
    glEnableClientState(GL_COLOR_ARRAY);

    int tam = f.size() - (f.size() - offset_tapas);

    if (tapas) {
        tam = f.size();
    }

    glBindBuffer(GL_ARRAY_BUFFER, ids_colores[color_id]);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glPolygonMode(GL_FRONT, map_modo(modo));
    glDrawElements(GL_TRIANGLES, tam * 3, GL_UNSIGNED_INT, (void *) 0);



    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
void ObjRevolucion::draw_AjedrezDiferido(GLuint color_id, bool tapas, ModoVisualizacion modo, ModoLuz iluminacion) {
    //Creacion de VBOs
    if (id_vbo_vertices == 0) {
        id_vbo_vertices = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * v.size(), v.data());
    }

    if (id_vbo_tri == 0) {
        id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 3 * f.size(), f.data());
    }
    //VBOs de los vectores de colores
    if (id_vbo_color_v == 0) {
        ids_colores[PUNTOS_c] = id_vbo_color_v = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_vert.size(), c_vert.data());
    }
    if (id_vbo_color_a == 0) {
        ids_colores[ALAMBRE_c] = id_vbo_color_a = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_aris.size(), c_aris.data());
    }
    if (id_vbo_color_c == 0) {
        ids_colores[SOLIDO_c] = id_vbo_color_c = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_cara.size(), c_cara.data());
    }
    if (id_vbo_color_aj == 0) {
        ids_colores[AJEDREZ_c] = id_vbo_color_aj = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_ajedrez.size(), c_ajedrez.data());
    }
    glBindBuffer(GL_ARRAY_BUFFER, id_vbo_vertices);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glPointSize(8);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
    glEnableClientState(GL_COLOR_ARRAY);


    int iter = 2, iter_tapa = 1, tam = f.size(), tam_tapas = f.size() - offset_tapas;
    GLuint color = ids_colores[color_id];
    if (tapas) iter_tapa = 2;
    tam = f.size() - tam_tapas;
    tam /= 2;

    unsigned long offset_ajedrez = 0;
    for (int i = 0; i < iter_tapa; i++) {
        for (int j = 0; j < iter; j++) {
            glBindBuffer(GL_ARRAY_BUFFER, color);
            glColorPointer(3, GL_FLOAT, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glPolygonMode(GL_FRONT, map_modo(modo));
            glDrawElements(GL_TRIANGLES, tam * 3, GL_UNSIGNED_INT, (void *) (sizeof(float) * 3 * offset_ajedrez));
            color = id_vbo_color_aj;
            offset_ajedrez += tam;
        }
        color = ids_colores[color_id];
        offset_ajedrez = offset_tapas;
        tam = tam_tapas / 2;
    }


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}


void ObjRevolucion::mezclaVector() {
    Tupla3i aux;
    std::vector<Tupla3i> copia_sin_tapas;
    std::vector<Tupla3i> copia_tapas;
    for (int i = 0; i < offset_tapas; i++) {
        copia_sin_tapas.push_back(f[i]);
    }
    for (int i = offset_tapas; i < f.size(); i++) {
        copia_tapas.push_back(f[i]);
    }
    //mezcla caras laterales
    for (auto i = copia_sin_tapas.begin(); i != copia_sin_tapas.end(); ++i) {
        aux = *i;
        copia_sin_tapas.erase(i);
        copia_sin_tapas.push_back(aux);
    }
    //mezcla tapas
    for (auto i = copia_tapas.begin(); i != copia_tapas.end(); ++i) {
        aux = *i;
        copia_tapas.erase(i);
        copia_tapas.push_back(aux);
    }
    f.clear();
    //las unimos en f
    for (auto e : copia_sin_tapas) {
        f.push_back(e);
    }
    for (auto e : copia_tapas) {
        f.push_back(e);
    }
}
