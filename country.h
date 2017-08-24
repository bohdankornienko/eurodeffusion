#ifndef COUNTRY_H
#define COUNTRY_H

#include <utility>
#include <string>
#include <iostream>

typedef struct _rect
{
    int x_l;
    int y_l;
    int x_h;
    int y_h;
} rect;

class Country
{
private:
    std::string name;
    int day_when_complite;
    rect area;

public:
    Country() : name(""), day_when_complite(0)
    {
        area.x_h = -1;
        area.x_l = -1;
        area.y_h = -1;
        area.y_l = -1;
    }

    Country(std::string name, int x_l, int y_l, int x_h, int y_h)
        : day_when_complite(0)
    {
        this->name = name;
        area.x_h = x_h;
        area.x_l = x_l;
        area.y_h = y_h;
        area.y_l = y_l;
        //area = {x_l, y_l, x_h, y_h};
    }

    ~Country()
    {
        //std::cout << "Counrtry destroy\n";
    }

    int x_l(){ return area.x_l; }
    int y_l(){ return area.y_l; }
    int x_h(){ return area.x_h; }
    int y_h(){ return area.y_h; }

    void set_name(std::string new_name) { name = new_name; }
    std::string get_name() const { return name; }

    void set_day_when_complite(int day) { day_when_complite = day; }
    int get_day_when_complite() const { return day_when_complite; }

    rect placement(){ return area; }
};

#endif // COUNTRY_H
