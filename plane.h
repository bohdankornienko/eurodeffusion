#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <vector>

#include "country.h"
#include "constants.hpp"

class Plane
{
private:
    std::vector<Country> countries;
    int days_spend;
    balance_map_t balance_map;

    int portion_for_transfer(int initial_value);
    void complite_day();

public:
    Plane();
    ~Plane();

    void print_grid();
    void add_country(Country* country);
    int counrtyes_count();

    bool is_valid_position(int x_l, int y_l, int x_h, int y_h);
    bool is_country_complite(const int index);
    bool is_all_countryes_complite();
    void populate();
    void money_day_move();

    std::vector<Country> get_countryes_list() {return countries; }

    int get_days_spend(){ return days_spend; }

    //void erase_countries() { countries.erase(countries.begin(), countries.end()); }
};

#endif // PLANE_H
