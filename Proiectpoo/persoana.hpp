#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "bilet.hpp"
#pragma once


class Person
{
    std::string Nume;
    std::string Prenume;
    std::unique_ptr<bilet> my_ticket;
public:
    Person(std::string nume_ , std::string prenume_);
    void Biletul_meu() const;
    virtual void cumpara_bilet(tren *t);
    std::string get_nume() const;
    std::string get_prenume() const;
    std::unique_ptr<bilet>& get_my_ticket();
  
};


class student : public Person
{
    std::string Universitate;
public:
    student(std::string nume_, std::string prenume_, std::string univ);
    void cumpara_bilet(tren *t) override;
};

class pensionar : public Person
{
public:
    pensionar(std::string nume_, std::string prenume_);
    void cumpara_bilet(tren *t) override;

};


class Elev : public Person
{
public:
    Elev (std::string nume_, std::string prenume_);
    void cumpara_bilet(tren *t) override;
};