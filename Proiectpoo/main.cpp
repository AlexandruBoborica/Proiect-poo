#include <iostream>
#include <string>
#include <vector>
#include "tren.hpp"
#include "vagon.hpp"
#include "persoana.hpp"
#include "bilet.hpp"
#include <memory>
#include <iomanip> 
#include "template.hpp"



template <typename T>
class InfoTren
{
private:
    std::vector <T> elemente;
public:
    void inserare_element(const T& element);
    void afisare_elemente();
    double calculeaza_total();
    std::size_t calculeaza_numar_elemente() const;
    const T& operator[](size_t index) const;
    void get_element(int poz);
};

template <typename T>
void InfoTren<T>::inserare_element(const T& element) {
    elemente.push_back(element);
}

template <typename T>
void InfoTren<T>::afisare_elemente() 
{
    for (size_t i = 0; i < elemente.size(); ++i) {
        const T& element = elemente[i];
        std::cout << "ID: " << i + 1 << ", Nume: " << element->get_nume() << ", Prenume: " << element->get_prenume();
        
        if (auto* calator = dynamic_cast<Person*>(element)) {
            if (calator->get_my_ticket() != nullptr) {
                std::cout << ", Bilet: ";
                calator->Biletul_meu();
            }
        }
        
        std::cout << std::endl;
    }
    std::cout << "-------------------------------------------------------------------------------------" << std::endl;
}

template <typename T>
double InfoTren<T>::calculeaza_total() {
    double total = 0.0;
    for (const auto &element : elemente) {
        total += element.get_pret();
    }
    return total;
}

template <typename T>
std::size_t InfoTren<T>::calculeaza_numar_elemente() const{
    return elemente.size();
}


template <typename T>
const T& InfoTren<T>::operator[](size_t index) const {
    return elemente[index];
}

template <typename T>
void InfoTren<T> :: get_element(int poz)
{
    return elemente[poz];
}






void printTrains(const std::vector<std::unique_ptr<tren>>& trenuri) {
    std::cout << std::left << std::setw(25) << "Traseu"
              << std::setw(5) << "ID"
              << std::setw(12) << "Plecare"
              << std::setw(12) << "Sosire"
              << std::setw(18) << "Tip tren"
              << std::setw(20) << "Tara destinatie"
              << std::endl;
    for (const auto& tren : trenuri) {
        if (tren->get_nr_statii() >= 2) {
            std::string route = tren->get_statie(0) + "-" + tren->get_statie(tren->get_nr_statii() - 1);
            std::string destinationCountry;
            std::string tipTren;
            if (auto* internationalTren = dynamic_cast<international_tren*>(tren.get())) {
                destinationCountry = internationalTren->get_tara();
                tipTren = "IR";

            }
            if (auto* highSpeedTren = dynamic_cast<high_speed_tren*>(tren.get())) {
                tipTren = "High Speed";
            }

            std::cout << std::setw(25) << route
                      << std::setw(5)  << tren->get_id()
                      << tren->get_ora_plecare() <<"       "
                      << tren->get_ora_sosire();

           
            if (!tipTren.empty()) {
                std::cout << "      " <<std::setw(18) << tipTren;
            } else {
                std::cout << std::setw(18) << ""; 
            }

            std::cout << "       "<<std::setw(20) << destinationCountry
                      << std::endl;
        }
    }
}


void printPersonDetails(const InfoTren<Person*>& Persoane)
{
    std::cout << "Detaliile persoanelor:" << std::endl;
    for (size_t i = 0; i < Persoane.calculeaza_numar_elemente(); ++i)
    {
        const Person* calator = Persoane[i];
        std::cout << "ID: " << i + 1 << ", Nume: " << calator->get_nume() << ", Prenume: " << calator->get_prenume() << std::endl;
    }
    std::cout << "-------------------------------------------------------------------------------------" << std::endl;
}



int main()
{
   
    std::vector<std::string> traseu1 = {"Craiova" , "Caracal" , "Rosiori" , "Videle", "Bucuresti"};
    std::vector<std::string> traseu2 = {"Bucuresti", "Peris", "Ploiesti-sud", "Ploiesti-nord"};
    std::vector<std::string> traseu3 = {"Craiova", "Severin" , "Herculane" ,"Lugoj", "Timisoara"};
    std::vector<std::string> traseu4 = {"Bucuresti", "Ploiesti-sud" , "Focsani" ,"Barlad", "Vaslui", "Iasi"};
    std::vector<std::string> traseu5 = {"Cluj" , "Oradea" , "Debrecen" , "Budapesta"};
    std::vector<std::string> traseu6 = {"Bucuresti" , "Braila" , "Galati" , "Chisinau"};

    std::vector<std::string> sf  = {"Wi-fi" , "Bar" , "Depozit special bagaje"};
    std::vector<std::string> Doc1 = {"Buletin"};
    std::vector<std::string> Doc2 = {"Pasaport" , "Cazier" , "Viza"};

    std::vector<std::unique_ptr<tren>> trenuri;
    
    
    std::unique_ptr<tren> tren1 = std::make_unique<tren>(traseu1, 209, ceas(9, 0), ceas(12, 35));
    vagon v1(100 , 2);
    vagon v2(80  , 2);
    vagon v3(100 , 2);
    vagon v4(75  , 1);
    tren1->inlantuire_vagoane(v1);
    tren1->inlantuire_vagoane(v2);
    tren1->inlantuire_vagoane(v3);
    tren1->inlantuire_vagoane(v4);
    trenuri.push_back(std::move(tren1));


    std::unique_ptr<tren> tren2 = std::make_unique<tren>(traseu1, 209, ceas(12 , 0), ceas(16, 0));
    vagon v5(100 , 2);
    vagon v6(80  , 2);
    vagon v7(100 , 2);
    vagon v8(75  , 1);
    tren2->inlantuire_vagoane(v5);
    tren2->inlantuire_vagoane(v6);
    tren2->inlantuire_vagoane(v7);
    tren2->inlantuire_vagoane(v8);
    trenuri.push_back(std::move(tren2));
    std::unique_ptr<high_speed_tren> tren3 = std::make_unique<high_speed_tren>(200 , sf , traseu1, 209, ceas(18 , 0), ceas(19, 50));
    vagon v9(100 , 2);
    vagon v10(50 , 1);
    tren3->inlantuire_vagoane(v9);
    tren3->inlantuire_vagoane(v10);
    trenuri.push_back(std::move(tren3));

    std::unique_ptr<tren> tren4 = std::make_unique<tren>(traseu2, 95, ceas(8 , 0), ceas(9, 30));
    vagon v11(90  , 2);
    vagon v12(90  , 2);
    vagon v13(90  , 2);
    tren4->inlantuire_vagoane(v11);
    tren4->inlantuire_vagoane(v12);
    tren4->inlantuire_vagoane(v13);
    trenuri.push_back(std::move(tren4));

    std::unique_ptr<tren> tren5 = std::make_unique<tren>(traseu3, 315, ceas(8 , 0), ceas(16, 00));
    vagon v14(100 , 2);
    vagon v15(100 , 2);
    vagon v16(75  , 1);
    vagon v17(75  , 1);
    tren5->inlantuire_vagoane(v14);
    tren5->inlantuire_vagoane(v15);
    tren5->inlantuire_vagoane(v16);
    tren5->inlantuire_vagoane(v17);
    trenuri.push_back(std::move(tren5));

    std::unique_ptr<high_speed_tren> tren6 = std::make_unique<high_speed_tren>(250,sf,traseu3, 315, ceas(14 , 0), ceas(18, 00));
    vagon v18(100 , 2);
    vagon v19(80  , 2);
    vagon v20(100 , 1);
    tren6->inlantuire_vagoane(v18);
    tren6->inlantuire_vagoane(v19);
    tren6->inlantuire_vagoane(v20);
    trenuri.push_back(std::move(tren6));


    std::unique_ptr<tren> tren7 = std::make_unique<tren>(traseu2, 95, ceas(10 , 0), ceas(11, 15));
    vagon v21(120  , 2);
    vagon v22(120  , 2);
    tren7->inlantuire_vagoane(v21);
    tren7->inlantuire_vagoane(v22);
    trenuri.push_back(std::move(tren7));

    std::unique_ptr<tren> tren8 = std::make_unique<tren>(traseu2, 95, ceas(14 , 0), ceas(15, 30));
    vagon v23(100 , 2);
    vagon v24(80  , 2);
    tren8->inlantuire_vagoane(v23);
    tren8->inlantuire_vagoane(v24);
    trenuri.push_back(std::move(tren8));

    std::unique_ptr<tren> tren9 = std::make_unique<tren>(traseu4, 290, ceas(10 , 0), ceas(20, 30));
    vagon v25(130 , 2);
    vagon v26(130 , 2);
    vagon v27(100 , 1);
    tren9->inlantuire_vagoane(v25);
    tren9->inlantuire_vagoane(v26);
    tren9->inlantuire_vagoane(v27);
    trenuri.push_back(std::move(tren9));

    std::unique_ptr<international_tren> tren10 = std::make_unique<international_tren>("Ungaria","romana-maghiara" ,Doc1,traseu5, 485, ceas(5 , 50), ceas(14,50));
    vagon v28(100 , 2);
    vagon v29(100 , 2);
    vagon v30(100 , 2);
    vagon v31(75  , 2);
    vagon v32(75  , 1);
    vagon v33(75  , 1);
    tren10->inlantuire_vagoane(v28);
    tren10->inlantuire_vagoane(v29);
    tren10->inlantuire_vagoane(v30);
    tren10->inlantuire_vagoane(v31);
    tren10->inlantuire_vagoane(v32);
    tren10->inlantuire_vagoane(v33);
    trenuri.push_back(std::move(tren10));

    std::unique_ptr<international_tren> tren11 = std::make_unique<international_tren>("Republica Moldova","romana" ,Doc2,traseu6, 466, ceas(7 , 0), ceas(16,0));
    vagon v34(100 , 2);
    vagon v35(100 , 2);
    vagon v36(100 , 2);
    vagon v37(75  , 2);
    vagon v38(75  , 1);
    vagon v39(75  , 1);
    tren11->inlantuire_vagoane(v34);
    tren11->inlantuire_vagoane(v35);
    tren11->inlantuire_vagoane(v36);
    tren11->inlantuire_vagoane(v37);
    tren11->inlantuire_vagoane(v38);
    tren11->inlantuire_vagoane(v39);
    trenuri.push_back(std::move(tren11));

    std::unique_ptr<tren> tren12 = std::make_unique<tren>(traseu4, 290, ceas(13 , 0), ceas(21, 30));
    vagon v40(90 , 2);
    vagon v41(90 , 2);
    vagon v42(90 , 2);
    tren12->inlantuire_vagoane(v40);
    tren12->inlantuire_vagoane(v41);
    tren12->inlantuire_vagoane(v42);
    trenuri.push_back(std::move(tren12));

    std::unique_ptr<high_speed_tren> tren13 = std::make_unique<high_speed_tren>(230,sf,traseu4, 290, ceas(0 , 0), ceas(4, 45));
    vagon v43(90 , 2);
    vagon v44(90 , 2);
    vagon v45(90 , 2);
    tren13->inlantuire_vagoane(v43);
    tren13->inlantuire_vagoane(v44);
    tren13->inlantuire_vagoane(v45);
    trenuri.push_back(std::move(tren13));

    std::unique_ptr<tren> tren14 = std::make_unique<tren>(traseu4, 290, ceas(15 , 0), ceas(23, 0));
    vagon v46(90 , 2);
    vagon v47(90 , 2);
    vagon v48(90 , 2);
    vagon v49(80 , 1);
    tren14->inlantuire_vagoane(v46);
    tren14->inlantuire_vagoane(v47);
    tren14->inlantuire_vagoane(v48);
    tren14->inlantuire_vagoane(v49);
    trenuri.push_back(std::move(tren14));

  
    
    InfoTren <Person*> Persoane;
    InfoTren <bilet> bilete_cumparate;
    
while (true)
{
    std::cout << "MENIU:" << std::endl;
    std::cout << "1.Cumpara bilet" << std::endl;
    std::cout << "2.Biletul meu" << std::endl;
    std::cout << "3.Exit" << std::endl;
    Person* calator = nullptr;
    int opt;
    std::cout << "Selecteaza o optiune ";
    std::cin >> opt;
    switch (opt)
    {
    case 1:
    {
        std::cout << "Lista trenurilor disponibile" << std::endl;
        printTrains(trenuri);
        std::cout << "-------------------------------------------------------------------------------------" << std::endl;

        std::cout << "Selectati un tren(Id-ul) : ";
        int trenul_meu;
        std::cin >> trenul_meu;
        std::cout << "Locurile din trenul ales : " << std::endl;
        trenuri[trenul_meu - 1]->afisare_locuri();

        int tip_calator;
        std::cout << "1.Adult" << std::endl;
        std::cout << "2.Student" << std::endl;
        std::cout << "3.Pensionar" << std::endl;
        std::cout << "Introdu optiunea ta ";

        std::cin >> tip_calator;
        switch (tip_calator)
        {
        case 1:
        {
            std::string name;
            std::string p_name;
            std::cout << "Nume: ";
            std::cin >> name;
            std::cout << "Prenume: ";
            std::cin >> p_name;
            calator = new Person(name, p_name);
            calator->cumpara_bilet(trenuri[trenul_meu - 1].get());
            Persoane.inserare_element(calator);
            break;
        }
        case 2:
        {
            std::string name;
            std::string p_name;
            std::string Uni;
            std::cout << "Nume: ";
            std::cin >> name;
            std::cout << "Prenume: ";
            std::cin >> p_name;
            std::cout << "Universitatea: ";
            std::cin >> Uni;
            calator = new student(name, p_name, Uni);
            calator->cumpara_bilet(trenuri[trenul_meu - 1].get());
            Persoane.inserare_element(calator);
            break;
        }
        case 3:
        {
            std::string name;
            std::string p_name;
            std::cout << "Nume: ";
            std::cin >> name;
            std::cout << "Prenume: ";
            std::cin >> p_name;
            calator = new pensionar(name, p_name);
            calator->cumpara_bilet(trenuri[trenul_meu - 1].get());
            Persoane.inserare_element(calator);
            break;
        }
        } 
        break;
    }
    case 2:
    {
    printPersonDetails(Persoane);
    int id_ul_tau;
    std::cout << "Introduceti id-ul dvs. : ";
    std::cin >> id_ul_tau;
    if (id_ul_tau > 0 && id_ul_tau <= Persoane.calculeaza_numar_elemente()) {
        const Person* calator = dynamic_cast<Person*>(Persoane[id_ul_tau - 1]);

        if (calator != nullptr) {
            calator->Biletul_meu();
        } else {
            std::cout << "Persoana nu este de tipul 'Person'. Nu se pot afisa detalii despre bilet." << std::endl;
        }
    } else {
        std::cout << "ID-ul introdus nu este valid." << std::endl;
    }

    break;
    }
    case 3:
        return 0;
    default:
        std::cout << "Optiune invalida. Va rugam selectati o optiune valida." << std::endl;
        break;
    }
} 


    return 0;
}