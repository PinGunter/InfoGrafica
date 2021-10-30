#include <aux.h>
#include <objrevolucion.h>
#include <iostream>
#include <fstream>
#include <algorithm>



// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)


void ObjRevolucion::multMatVec(double (*m)[3], float *v, float *r) {
    for (int i=0; i < 3; i++){
        r[i] = 0;
        for (int j=0; j < 3; j++){
            r[i] += m[i][j]*v[j];
        }
    }
}
Tupla3f ObjRevolucion::rotarVertice(float alpha, float beta, float phi, const Tupla3f &vertice) {
    double rotacion[3][3]{
            cos(alpha)*cos(beta), cos(alpha)*sin(beta)*sin(phi)-sin(alpha)*cos(phi), cos(alpha)*sin(beta)*cos(phi)+sin(alpha)*sin(phi),
            sin(alpha)*cos(beta), sin(alpha)*sin(beta)*sin(phi)+cos(alpha)*cos(phi), sin(alpha)*sin(beta)*cos(phi)-cos(alpha)*sin(phi),
            -sin(beta), cos(beta)*sin(phi), cos(beta)*cos(phi)
    };
    float v [3] = {vertice(0), vertice(1), vertice(2)};
    float r[3] = {0};
    multMatVec(rotacion, v, r);
    return Tupla3f(r[0],r[1],r[2]);
}



ObjRevolucion::ObjRevolucion() {init();}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_inf, bool tapa_sup) {
    ply::read_vertices(archivo,perfil_original);
    normalizarPerfil();
    crearVertices(perfil_original,num_instancias);
    crearMalla(perfil_original,num_instancias,tapa_inf,tapa_sup);
    init();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_inf, bool tapa_sup) {
    perfil_original = archivo;
    normalizarPerfil();
    crearVertices(archivo,num_instancias);
    crearMalla(archivo,num_instancias,tapa_sup, tapa_inf);
    init();

}

void ObjRevolucion::normalizarPerfil(){
    int ejes = 0;
    Tupla3f aux;
    bool es_descendente = false;
    for (auto e : perfil_original){ 
        if (e(0) == 0){
            ejes++;
            v_ejes.push_back(e);
        }
    }

    remove_if(perfil_original.begin(), perfil_original.end(), [] (Tupla3f t) {return t(0) == 0;});
    for (int i=0; i < ejes; i++) perfil_original.pop_back();

    es_descendente = (perfil_original.at(0)(1) >= perfil_original.at(perfil_original.size()-1)(1));

    if (es_descendente){
        for (int i=0; i < perfil_original.size()/2; i++){
            aux = perfil_original[i];
            perfil_original[i] = perfil_original[perfil_original.size()-i-1];
            perfil_original[perfil_original.size()-i-1] = aux;
        }
    }
}

void ObjRevolucion::crearVertices(const std::vector<Tupla3f> &perfil_original, const int num_instancias_perf) {
    float angulo = 0.0;
    Tupla3f vert;
    for (int i=0; i < num_instancias_perf; i++){
        for (int j=0; j < perfil_original.size(); j++){
            angulo = 2.0*M_PI*i/num_instancias_perf;
            vert = rotarVertice(0,angulo,0,perfil_original[j]);
            v.push_back(vert);
        }
    }
}


void ObjRevolucion::crearMalla(const std::vector<Tupla3f> &perfil_original, const int num_instancias_perf, bool tapa_inf, bool tapa_sup) {
    int a,b;
    for (int i=0; i < num_instancias_perf; i++){
        for (int j=0; j < perfil_original.size()-1; j++){
            a = perfil_original.size()*i+j;
            b = perfil_original.size()*((i+1) % num_instancias_perf) + j;
            f.push_back(Tupla3i(a,b,b+1));
            f.push_back(Tupla3i(a,b+1,a+1));
        }
    }
    crearTapas(tapa_inf,tapa_sup);
}


void ObjRevolucion::crearTapas(bool inf, bool sup) {

}
void ObjRevolucion::init() {
    inicializar(Tupla3f(0,1,0),
                Tupla3f(1,0,0),
                Tupla3f(0,0,1),
                Tupla3f(1, 0.24, 0.71));
}
