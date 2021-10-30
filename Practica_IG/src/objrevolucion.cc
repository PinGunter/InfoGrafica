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

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   ply::read_vertices(archivo,perfil_original);
   normalizarPerfil();
   crearVertices(perfil_original,num_instancias);
   crearMalla(perfil_original,num_instancias,(tapa_sup || tapa_inf));
   std::ofstream salida ("caras_generadas.txt");
   for (auto e : perfil_original) salida << e << std::endl;
   salida << "Vertices generados: " << std::endl;
   for (auto e : v) salida << e << std::endl;
   salida << "Caras generadas: " << std::endl;
   for (auto e : f) salida << e << std::endl;
   inicializar(Tupla3f(0,1,0),
               Tupla3f(1,0,0),
               Tupla3f(0,0,1),
               Tupla3f(1, 0.24, 0.71));
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
    perfil_original = archivo;
    normalizarPerfil();
    crearVertices(archivo,num_instancias);
    crearMalla(archivo,num_instancias,(tapa_sup || tapa_inf));
}

void ObjRevolucion::normalizarPerfil(){
    int ejes = 0;
    Tupla3f aux;
    bool es_ascendente = false;
    for (auto e : perfil_original){ 
        if (e(0) == 0){
            ejes++;
            v_ejes.push_back(e);
        }
    }

    remove_if(perfil_original.begin(), perfil_original.end(), [] (Tupla3f t) {return t(0) == 0;});
    for (int i=0; i < ejes; i++) perfil_original.pop_back();

    es_ascendente = (perfil_original.at(0)(1) <= perfil_original.at(perfil_original.size()-1)(1));

    if (es_ascendente){
        for (int i=0; i < perfil_original.size()/2; i++){
            aux = perfil_original[i];
            perfil_original[i] = perfil_original[perfil_original.size()-i-1];
            perfil_original[perfil_original.size()-i-1] = aux;
        }
    }
}

void ObjRevolucion::crearVertices(const std::vector<Tupla3f> &perfil_original, const int num_instancias_perf) {
    Tupla3f vertice, actual;
    float angulo;
    for (int i=0; i < num_instancias_perf; i++){
        for (int j=0; j < perfil_original.size(); j++){
            angulo = 2*M_PI * i/num_instancias_perf;
            actual = perfil_original[j];
            vertice(0) = cos(angulo) * actual(0) + sin(angulo) * actual(2);
            vertice(1) = actual(1);
            vertice(2) = -sin(angulo) * actual(0) + cos(angulo) * actual(2);
            v.push_back(vertice);
        }
    }
}


void ObjRevolucion::crearMalla(const std::vector<Tupla3f> &perfil_original, const int num_instancias_perf, const bool conTapas) {
    int a,b;
    for (int i=0; i < num_instancias_perf; i++){
        for (int j=0; j < v.size() -1; j++){
            a = v.size() * i + j;
            b = v.size() * ((i+1) % num_instancias_perf) + j;
            f.push_back(Tupla3i(a,b,b+1));
            f.push_back(Tupla3i(a,b+1,a+1));
        }
    }
}
