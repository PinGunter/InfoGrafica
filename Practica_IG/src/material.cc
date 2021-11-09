//
// Created by salva on 9/11/21.
//

#include <material.h>
Material::Material(){}

Material::Material(Tupla4f ambiente, Tupla4f especular, Tupla4f difuso, float brillo) {
    this -> ambiente = ambiente;
    this -> especular = especular;
    this -> difuso = difuso;
    this -> brillo = brillo;
}
