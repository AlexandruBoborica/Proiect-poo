#include <iostream>
#include <string>
#include <vector>
#include "vagon.hpp"
#pragma once

class timp_invalid : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Orar introdus gresit";
    }
};


class ceas{
    int ora;
    int minute;
public:
    ceas(int h, int min);
    friend std::ostream& operator<<(std::ostream& os, const ceas& c);
};

class tren
{
    static int id_cnt;
    int id;
    std::vector<std::string> statii;
    std::vector<vagon> vagoane;
    int nr_km;
    ceas ora_plecare;
    ceas ora_sosire;   
public:
    tren();
    tren(const std::vector<std::string> & lista_statii , int distanta, ceas plecare, ceas sosire);
    virtual ~tren();
    int get_nr_statii_parcurse(std::string statie1 , std::string statie2);
    int get_id();
    std::string get_statie(int nr_statie);
    void inlantuire_vagoane(const vagon & vag_adaugat);
    void set_orar(ceas ora_plecare, ceas ora_sosire);
    void afisare_locuri();
    int get_nr_vag();
    int get_distanta();
    int get_nr_statii();
    vagon& get_vag(int nr);
    ceas get_ora_plecare();
    ceas get_ora_sosire();
   
};


class high_speed_tren : public tren
{
    float max_speed;
    std::vector<std::string> special_facility;
public:
    high_speed_tren(float s, std::vector<std::string> sf, const std::vector<std::string> &lista_statii, int distanta, ceas plecare, ceas sosire);

};

class international_tren : public tren
{
    std::string tara_destinatie;
    std::string language;
    std::vector<std::string> Documente_necesare;
public:
    international_tren(std::string tara, std::string lang, std::vector<std::string> docs, const std::vector<std::string> &lista_statii, int distanta, ceas plecare, ceas sosire);
    std::string get_tara();
};

