#include <iostream>
#include <string>
#include <vector>
#include "tren.hpp"
#include "bilet.hpp"
#include <cstdlib>
#include <ctime>


bilet :: bilet(tren *t , int vag , int l , std::string urcare, std::string coborare): my_tren(t), nr_vagon(vag), loc(l), statie_urcare(urcare), statie_coborare(coborare)
{
    int clasa = my_tren->get_vag(vag).get_clasa();
    int nr_statii = my_tren->get_nr_statii_parcurse(statie_urcare, statie_coborare);
    pret = 0.0;
    if(dynamic_cast<high_speed_tren*>(my_tren)!=nullptr)
    {
        if(clasa == 1)
            pret = 30.0+nr_statii*20+50.0;
        else
            if(clasa == 2)
                pret = 10.0+nr_statii*20.0+50.0;

    }
    else
        if(dynamic_cast<international_tren*>(my_tren)!=nullptr)
        {
            if(clasa == 1)
                pret = 30.0+nr_statii*20+30.0;
            else
                if(clasa == 2)
                    pret = 10.0+nr_statii*20.0+30.0;

        }
    else
    {
         if(clasa == 1)
                pret = 30.0+nr_statii*20;
            else
                if(clasa == 2)
                    pret = nr_statii*20.0;

    }
}

double bilet :: get_pret()
{
    return pret;
}

void bilet :: set_pret(int pret_nou)
{
    this->pret = pret_nou;
}

void bilet :: afisare_detalii()
{
    std::cout<<"Trenul "<<my_tren->get_id()<<std::endl;
    std::cout<<"Pret bilet: "<<pret<<std::endl;
    std::cout<<"Vagonul "<<nr_vagon<<" Clasa "<<my_tren->get_vag(nr_vagon).get_clasa()<<std::endl;
    std::cout<<"Locul "<<loc<<std::endl;
    std::cout<<statie_urcare<<" - "<<statie_coborare<<std::endl;
    generate_random_qr_code();
}


void bilet::generate_random_qr_code() const
{
   
    std::srand(std::time(0));

    const int qrCodeSize = 5;


    for (int y = 0; y < qrCodeSize; y++)
    {
        for (int x = 0; x < qrCodeSize; x++)
        {
           
            char dot = (std::rand() % 2 == 0) ? '*' : ' ';
            std::cout << dot;
        }
        std::cout << std::endl;
    }
}