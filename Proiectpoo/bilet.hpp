#include <iostream>
#include <string>
#include <vector>
#include "tren.hpp"
#pragma once
class bilet
{
    tren *my_tren;
    double pret;
    int nr_vagon;
    int loc;
    std::string statie_urcare;
    std::string statie_coborare;
public:
    bilet(tren *t , int vag , int l , std::string urcare, std::string coborare);
    void afisare_detalii();
    double get_pret();
    void set_pret(int pret_nou);
    void generate_random_qr_code() const;


    
};