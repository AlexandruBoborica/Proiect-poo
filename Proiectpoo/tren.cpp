#include <iostream>
#include <string>
#include <vector>
#include "tren.hpp"
#include "vagon.hpp"
#include "persoana.hpp"
#include "bilet.hpp"
#include <iomanip>


int tren:: id_cnt = 1;



ceas :: ceas(int h, int min) : ora(h) , minute(min)
{
    if (h < 0 || h > 23 || min < 0 || min > 59) 
        throw timp_invalid();

}

tren :: tren(const std::vector<std::string> & lista_statii , int distanta, ceas plecare, ceas sosire) : id(id_cnt++) , nr_km(distanta) , ora_plecare(plecare), ora_sosire(sosire)
{
   statii = lista_statii;
}

high_speed_tren :: high_speed_tren(float s , std::vector<std::string> sf ,const std::vector<std::string> & lista_statii , int distanta, ceas plecare, ceas sosire ):tren(lista_statii, distanta , plecare , sosire),max_speed(s) ,special_facility(sf){}

international_tren::international_tren(std::string tara, std::string lang, std::vector<std::string> docs, const std::vector<std::string> &lista_statii, int distanta, ceas plecare, ceas sosire)
    : tren(lista_statii, distanta, plecare, sosire), tara_destinatie(tara), language(lang), Documente_necesare(docs) {}

tren :: ~tren(){};

int tren :: get_id()
{
    return this->id;
}

std::string tren :: get_statie(int nr_statie)
{
    return statii[nr_statie];
}

void tren :: set_orar(ceas plecare, ceas sosire)
{
    ora_plecare = plecare;
    ora_sosire = sosire;
}

int tren :: get_nr_vag()
{
    return vagoane.size();
}

void tren :: afisare_locuri()
{
    for(int i=0; i<this->vagoane.size(); i++)
    {
        vagoane[i].afisare_locuri();
        std::cout<<std::endl;
        std :: cout<<"-----------------------"<<std::endl;

    }
    
}
vagon& tren::get_vag(int nr)
{
    if (nr <= 0 || nr > vagoane.size()) {
        throw std::out_of_range("Invalid wagon number");
    }

    return vagoane[nr - 1];
}

int tren :: get_distanta()
{
    return nr_km;
}

void tren :: inlantuire_vagoane(const vagon & vag_adaugat)
{
    vagoane.push_back(vag_adaugat);
}

int tren :: get_nr_statii()
{
    return statii.size();
} 

std::string international_tren :: get_tara()
{
    return tara_destinatie;
}

int tren ::  get_nr_statii_parcurse(std::string statie1 , std::string statie2)
{
    int i=0;
    int j=this->get_nr_statii();
    for(int i = 0 ; i<j;i++)
    {
        if(this->statii[i]==statie1)
        break;
    }
    while(j>=0)
    {
        if(this->statii[j]==statie2)
        break;
        j--;
    }
    return j-i+1;

}



ceas tren :: get_ora_plecare()
{
    return ora_plecare;
}

ceas tren :: get_ora_sosire()
{
    return ora_sosire;
}


std::ostream& operator<<(std::ostream& os, const ceas& c) 
{
    std::string ora_s;
    std::string minute_s;
    if(c.ora<10){
        ora_s = std::to_string(c.ora);
        ora_s = '0'+ora_s;
    }
    else
    {
        ora_s = std::to_string(c.ora);
    }
    if(c.minute<10){
        minute_s = std::to_string(c.minute);
        minute_s = '0'+minute_s;
    }
    else
    {
        minute_s = std::to_string(c.minute);
    }

    os << ora_s << ":" << minute_s;
    
    return os;
}
