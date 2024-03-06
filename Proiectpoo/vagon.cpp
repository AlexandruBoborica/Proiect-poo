#include <iostream>
#include <string>
#include <vector>
#include "vagon.hpp"

vagon::vagon(int nr_loc, int tip_clasa) : nr_locuri(nr_loc), clasa(tip_clasa) 
{
    locuri = new bool[nr_locuri];
    for (int i = 0; i < nr_loc; i++)
        locuri[i] = false;
}


void vagon::afisare_locuri() {
    for (int i = 0; i < nr_locuri; i++) {
        if (locuri[i] == false)
            std::cout << i + 1 << "d" << " ";
        else
            std::cout << i + 1 << "o" << " ";
        if ((i + 1) % 3 == 0)
            std::cout << std::endl;
    }
}


vagon& vagon :: operator=(const vagon& other)
{
    if(this == &other)
    {
        return *this;      
    }
    nr_locuri = other.nr_locuri;
    clasa = other.clasa;
    delete[] locuri;
    locuri = new bool[nr_locuri];

    for(int i=0;i<nr_locuri;i++)
    {
        locuri[i] = other.locuri[i];
    }
    return *this;

}


bool vagon :: get_loc(int nr_loc)
{
    return locuri[nr_loc-1];
}

bool vagon::set_loc(int nr_loc)
{
    locuri[nr_loc-1] = true;
}

int vagon :: get_nr_locuri()
{
    return nr_locuri;
}
int vagon :: get_clasa()
{
    return clasa;
}

vagon:: ~vagon()
{
    delete[] locuri;
}