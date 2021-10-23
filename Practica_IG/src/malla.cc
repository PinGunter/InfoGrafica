#include <aux.h>
#include <malla.h>

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid *puntero_ram)
{
    GLuint id_vbo;
    glGenBuffers(1, &id_vbo);
    glBindBuffer(tipo_vbo, id_vbo);

    glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);
        glBindBuffer(tipo_vbo,0);
    return id_vbo;
}

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(GLuint modo, std::vector<Tupla3f> *color) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v.data());
    glPointSize(8);
    glLineWidth(5);
    glColorPointer(3, GL_FLOAT, 0, color->data());
    glPolygonMode(GL_FRONT, modo);
    glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, f.data());
    //volvemos al tamaño de linea predeterminado para que los ejes no se vean muy anchos
    glLineWidth(1);
    glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(GLuint modo, int color_id) {
    //Creacion de VBOs
    if (id_vbo_vertices == 0)
    {
        id_vbo_vertices = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * v.size(), v.data());
    }

    if (id_vbo_tri == 0)
    {
        id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 3 * f.size(), f.data());
    }
    //VBOs de los vectores de colores
    if (id_vbo_color_v == 0)
    {
        id_vbo_color_v = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_vert.size(), c_vert.data());
    }
    if (id_vbo_color_a== 0)
    {
        id_vbo_color_a = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_aris.size(), c_aris.data());
    }
    if (id_vbo_color_c == 0)
    {
        id_vbo_color_c = CrearVBO(GL_ARRAY_BUFFER, sizeof(float) * 3 * c_cara.size(), c_cara.data());
    }
    if (id_vbo_color_aj == 0)
    {
        id_vbo_color_aj = CrearVBO(GL_ARRAY_BUFFER,sizeof(float) * 3 * c_ajedrez.size(), c_ajedrez.data());
    }

    glBindBuffer(GL_ARRAY_BUFFER, id_vbo_vertices);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glPointSize(8);
//    glLineWidth(5);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, color_id);
    glColorPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glPolygonMode(GL_FRONT, modo);
    glDrawElements(GL_TRIANGLES, f.size() * 3, GL_UNSIGNED_INT, 0);

    //volvemos al tamaño de linea predeterminado para que los ejes no se vean muy anchos
    glLineWidth(1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(bool dibuja_diferido, bool ajedrez, GLuint modo)
{
//    glScalef(1.5,1.5,1.5);
    switch (modo){
        case PUNTOS:
            selector_color = &c_vert;
            selector_color_vbo = id_vbo_color_v;
            break;
        case ALAMBRE:
            selector_color = &c_aris;
            selector_color_vbo = id_vbo_color_a;
            break;
        case SOLIDO:
            selector_color = &c_cara;
            selector_color_vbo = id_vbo_color_c;
            break;
    }
    if (dibuja_diferido)
    {
        if (ajedrez) draw_AjedrezDiferido(modo, selector_color_vbo);
        else
            draw_ModoDiferido(modo, selector_color_vbo);
    } else
    {
        if (ajedrez) draw_AjedrezInmediato(modo, selector_color);
        else
            draw_ModoInmediato(modo, selector_color);
    }
}

void Malla3D::draw_AjedrezDiferido(GLuint modo, int color_id) {
    draw_ModoDiferido(modo,color_id);
    if (modo == SOLIDO)
        draw_ModoDiferido(modo,id_vbo_color_aj);
}

void Malla3D::draw_AjedrezInmediato(GLuint modo, std::vector<Tupla3f> *color) {
    draw_ModoInmediato(modo,color);
    if (modo == SOLIDO)
        draw_ModoInmediato(modo,&c_ajedrez);
}
void Malla3D::rellenaColores(const Tupla3f &vertices, const Tupla3f &aristas, const Tupla3f &solido, const Tupla3f &ajedrez) {
    for (int i = 0; i < v.size(); i++)
    {
        c_vert.push_back(solido);
        c_aris.push_back(aristas);
        c_cara.push_back(vertices);
        c_ajedrez.push_back(ajedrez);
    }
}
