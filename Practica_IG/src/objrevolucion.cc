#include <aux.h>
#include <objrevolucion.h>




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
   crearVertices(perfil_original,num_instancias);
   crearMalla(perfil_original,num_instancias,(tapa_sup || tapa_inf));
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
    crearVertices(archivo,num_instancias);
    crearMalla(archivo,num_instancias,(tapa_sup || tapa_inf));
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
