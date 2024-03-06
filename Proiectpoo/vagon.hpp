#include <iostream>
#include <string>
#include <vector>
#pragma once
class vagon
{
    bool *locuri;//1-ocupat , 0 - liber
    int nr_locuri;
    int clasa;
public:
    vagon(int nr_loc , int tip_clasa);
    void afisare_locuri();
    int get_nr_locuri();
    bool get_loc(int nr_loc);
    int get_clasa();
    int get_nr_vagon() const;
    bool set_loc(int nr_loc);
    vagon& operator=(const vagon& other);
    ~vagon();
 
};
