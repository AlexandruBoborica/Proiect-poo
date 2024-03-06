#include <iostream>
#include <string>
#include <vector>
#include "persoana.hpp"
#include "bilet.hpp"
#include "tren.hpp"
#include "vagon.hpp"
#include <memory>

class loc_ocupat : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Locul este deja ocupat.Reincercati";
    }
};

Person :: Person(std::string nume_ , std::string prenume_)
{
    Nume = nume_;
    Prenume = prenume_;
}

student::student(std::string nume_, std::string prenume_, std::string univ) : Person(nume_, prenume_) , Universitate(univ) {}

pensionar :: pensionar(std::string nume_ , std:: string prenume_) : Person(nume_,prenume_){};

Elev::Elev(std::string nume_, std::string prenume_) : Person(nume_, prenume_) {};


void Person::cumpara_bilet(tren *t) {
    if (my_ticket != nullptr) {
        std::cout << "Persoana aceasta detine deja un bilet.\n";
    } else {
        int nr_vag, nr_loc;
        std::string plecare, sosire;

        for (int attempts = 0; attempts < 3; ++attempts) {
            try {
                std::cout << "Nr vagonului: ";
                std::cin >> nr_vag;
                std::cout << "Introduceti locul dorit: ";
                std::cin >> nr_loc;

                if (!t->get_vag(nr_vag).get_loc(nr_loc)) {
                    std::cout << "De la: ";
                    std::cin >> plecare;
                    std::cout << "Pana la: ";
                    std::cin >> sosire;
                    my_ticket = std::make_unique<bilet>(t, nr_vag, nr_loc, plecare, sosire);
                    std::cout << "Bilet selectat cu succes!" << std::endl;
                    t->get_vag(nr_vag).set_loc(nr_loc);
                    return;
                } else {
                    throw loc_ocupat();
                }
            } catch (const loc_ocupat& e) {
                std::cerr << "Eroare: " << e.what() << std::endl;
            }
        }
        std::cerr << "Numarul maxim de incercari a fost atins. Selectarea biletului a esuat.\n";
    }
}



std::unique_ptr<bilet>& Person :: get_my_ticket() 
{
        return my_ticket;
}


void Person::Biletul_meu() const
{
    if (my_ticket != nullptr)
    {
        std::cout << Nume << " " << Prenume << std::endl;
        my_ticket->afisare_detalii();
        
    }
    else
    {
        std::cout << Nume << " " << Prenume << " nu a cumparat niciun bilet." << std::endl;
    }
}


void student :: cumpara_bilet(tren *t)
{
    Person :: cumpara_bilet(t);
    if (get_my_ticket() != nullptr) {
        int newPrice = get_my_ticket()->get_pret() * (0.1);
        std::cout << "Reducere pentru student aplicata! Noul pret: " << newPrice << " roni "<<std::endl;
        get_my_ticket()->set_pret(newPrice);
    }
}



void pensionar :: cumpara_bilet(tren *t)
{
    Person ::cumpara_bilet(t);
    if(get_my_ticket()!=nullptr)
    {
        int newPrice = get_my_ticket()->get_pret() * 0.2;
        std::cout << "Reducere pentru student aplicata! Noul pret: " << newPrice << " roni "<<std::endl;
        get_my_ticket()->set_pret(newPrice);

    }

}



void Elev :: cumpara_bilet(tren *t)
{
    Person ::cumpara_bilet(t);
    if(get_my_ticket()!=nullptr)
    {
        int newPrice = get_my_ticket()->get_pret() * 0.1;
        std::cout << "Reducere pentru student aplicata! Noul pret: " << newPrice << " roni "<<std::endl;
        get_my_ticket()->set_pret(newPrice);

    }

}    


std::string Person :: get_nume() const { return Nume; }
std::string Person :: get_prenume() const { return Prenume; }