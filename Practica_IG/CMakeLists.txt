cmake_minimum_required(VERSION 3.20)
project(Practica_IG)

set(CMAKE_CXX_STANDARD 14)
include_directories(include amongus)
add_executable(Practica_IG
        include/aux.h
        include/cubo.h
        include/ejes.h
        include/escena.h
        include/malla.h
        include/objply.h
        include/objrevolucion.h
        include/ply_reader.h
        include/tetraedro.h
        include/tuplasg.h
        src/cubo.cc
        src/ejes.cc
        src/escena.cc
        src/malla.cc
        src/objply.cc
        src/objrevolucion.cc
        src/ply_reader.cc
        src/practicas.cc
        src/tetraedro.cc src/cilindro.cc include/cilindro.h src/esfera.cc include/esfera.h src/cono.cc include/cono.h src/luz.cc include/luz.h src/luz_direccional.cc include/luz_direccional.h src/luz_posicional.cc include/luz_posicional.h src/material.cc include/material.h src/semiesfera.cc include/semiesfera.h amongus/pierna_inf.cc amongus/pierna_inf.h amongus/pierna_sup.cc amongus/pierna_sup.h amongus/pierna.cc amongus/pierna.h amongus/visor.cc amongus/visor.h amongus/cuerpo.cc amongus/cuerpo.h amongus/cabeza.cc amongus/cabeza.h amongus/hueso.cc amongus/hueso.h amongus/cuerpo_hueso.cc amongus/cuerpo_hueso.h amongus/cuerpo_hueso_cabeza.cc amongus/cuerpo_hueso_cabeza.h amongus/cuerpo_completo.cc amongus/cuerpo_completo.h amongus/tripulante.cc amongus/tripulante.h amongus/mochila.cc amongus/mochila.h amongus/tripulante_mochila.cc amongus/tripulante_mochila.h src/piedra.cc include/piedra.h src/mesa.cc include/mesa.h)

target_link_libraries(Practica_IG  -lm -lGL -lglut -lGLU -lGLEW)
