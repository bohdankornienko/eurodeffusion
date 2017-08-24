#include "plane.h"
#include "constants.hpp"

#define DEBUG
#undef DEBUG

#define STRUCT_TYPE

Plane::Plane() : days_spend(0)
{
}

Plane::~Plane()
{
    countries.erase(countries.begin(), countries.end());
    balance_map.erase(balance_map.begin(), balance_map.end());
}

int Plane::portion_for_transfer(int initial_value)
{
    int reminder = initial_value % PORTION_OF_COINS;
    return (initial_value - reminder) / PORTION_OF_COINS;
}

void Plane::complite_day()
{
    int map_size = MAX_NUMBER_OF_COUNTRIES * MOST_NORTHEASTWARD_CITY;
    for (int i = 0; i < map_size; ++i)
    {
        for (int j = 0; j < map_size; ++j)
        {
            for (unsigned int k = 0; k < countries.size(); ++k)
            {
                if(balance_map[i][j][k].income > 0)
                {
                    balance_map[i][j][k].balance += balance_map[i][j][k].income;
                    balance_map[i][j][k].income = 0;
                }
            }
        }
    }
}

void Plane::print_grid()
{
    int map_size = MAX_NUMBER_OF_COUNTRIES * MOST_NORTHEASTWARD_CITY;
    int cntr_count = counrtyes_count();

    for(int i = 0; i < map_size; ++i)
    {
        for(int k = 0; k < cntr_count; ++k)
        {
            for(int j = 0; j < map_size; ++j)
            {
                std::cout << balance_map[i][j][k].balance << "\t";
            }
            std::cout << std::endl;

            /*
            for(int j = 0; j < map_size; ++j)
            {
                std::cout << balance_map[i][j][k].income << "\t";
            }
            std::cout << std::endl;
            */
        }
        std::cout << std::endl;
    }
}

void Plane::add_country(Country *country)
{
    countries.push_back(*country);
}

int Plane::counrtyes_count()
{
    return countries.size();
}

bool Plane::is_valid_position(int x_l, int y_l, int x_h, int y_h)
{
    for(std::vector<Country>::iterator it = countries.begin(); it != countries.end(); ++it)
    {
        if(x_l >= it->x_l() && x_l <= it->x_h() &&
                y_l >= it->y_l() && y_l <= it->y_h() &&
                x_h >= it->x_l() && x_h <= it->x_h() &&
                y_h >= it->y_l() && y_h <= it->y_h())
        {
            return false;
        }
    }

    return true;
}

bool Plane::is_country_complite(const int index)
{
    for(int x = countries[index].x_l() - 1; x < countries[index].x_h(); ++x)
    {
        for(int y = countries[index].y_l() - 1; y < countries[index].y_h(); ++y)
        {
            for(int j = 0; j < counrtyes_count(); ++j)
            {
                if(balance_map[x][y][j].balance == 0)
                    return false;
            }
        }
    }

    return true;
}

bool Plane::is_all_countryes_complite()
{
    for (unsigned int i = 0; i < countries.size(); ++i)
    {
        if(!is_country_complite(i))
            return false;
    }
    return true;
}

void Plane::populate()
{
    // assign plane
    balance_onfo_t balance;
    balance.balance = -1;
    balance.income = -1;

    int map_size = MOST_NORTHEASTWARD_CITY * MAX_NUMBER_OF_COUNTRIES;

    // assign balances of countryes
    balance_info_vec_t balance_of_countryes;
    balance_of_countryes.assign(countries.size(), balance);

    // assign line of balances
    balance_line_t balance_line;
    balance_line.assign(map_size, balance_of_countryes);

    // assign columns of balances - finally map
    balance_map.assign(map_size, balance_line);
    // ---

    for(unsigned int k = 0; k < countries.size(); ++k)
    {
        for(int x = countries[k].x_l() - 1; x < countries[k].x_h(); ++x)
        {
            for(int y = countries[k].y_l() - 1; y < countries[k].y_h(); ++y)
            {
                for(unsigned int j = 0; j < countries.size(); ++j)
                {
                    balance_map[x][y][j].balance = (j == k) ? START_CAPITAL : 0;
                    balance_map[x][y][j].income = 0;
                }
            }
        }
    }
}

void Plane::money_day_move()
{
    // money move 1 coin from 1000
    int size = MAX_NUMBER_OF_COUNTRIES * MOST_NORTHEASTWARD_CITY;
    int country_count = countries.size();
    int portion = 0;

    ++days_spend;

    for(int x = 0; x < size; ++x)
    {
        for(int y = 0; y < size; ++y)
        {
            for(int k = 0; k < country_count; ++k)
            {
                portion = portion_for_transfer(balance_map[x][y][k].balance);

                if(x - 1 >= 0)
                {
                    if(balance_map[x][y][k].balance > 0 && balance_map[x - 1][y][k].balance >= 0)
                    {
                        balance_map[x - 1][y][k].income += portion;
                        balance_map[x][y][k].balance -= portion;
                    }
                }

                if(x + 1 >= 0 && x < size)
                {
                    if(balance_map[x][y][k].balance > 0 && balance_map[x + 1][y][k].balance >= 0)
                    {
                        balance_map[x + 1][y][k].income += portion;
                        balance_map[x][y][k].balance -= portion;
                    }
                }

                if(y - 1 >= 0)
                {
                    if(balance_map[x][y][k].balance > 0 && balance_map[x][y - 1][k].balance >= 0)
                    {
                        balance_map[x][y - 1][k].income += portion;
                        balance_map[x][y][k].balance -= portion;
                    }
                }

                if(y + 1 >= 0)
                {
                    if(balance_map[x][y][k].balance > 0 && balance_map[x][y + 1][k].balance >= 0)
                    {
                        balance_map[x][y + 1][k].income += portion;
                        balance_map[x][y][k].balance -= portion;
                    }
                }
            }
        }
    }
    complite_day();

    for(int i = 0; i < country_count; ++i)
    {
        if(countries[i].get_day_when_complite() <= 0)
        {
            if(is_country_complite(i))
            {
                countries[i].set_day_when_complite(days_spend);
            }
        }
    }
}
