#define DEBUG

#include <QCoreApplication>

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "plane.h"
#include "country.h"
#include "constants.hpp"

const int MAX_LENGTH_OF_COUNTRY_NAME = 25;

/* На данный момент
 *
 * На данный момент программа обладает двумя недостатками:
 * 1. для стран создается трехмерный массив со структурами,
 * описывающими количество монет в определенном городе. Это приводит к тому, что
 * большое количество памяти, зарезервированной под
 * массив с информацией о деньгах может не использоваться.
 *
 * 2. Сейчас для хранения поля со старнами используется трехмерный массив std::vector.
 * Скорее всего для этого лучше было бы использовать структуру std::map. Но с таким типом еще не работал
*/

bool compare_countries(const Country& lhd, const Country& rhd)
{
    if(lhd.get_day_when_complite() < rhd.get_day_when_complite())
    {
        return true;
    }
    else if(lhd.get_day_when_complite() == rhd.get_day_when_complite())
    {
        std::string name = lhd.get_name();

        return name.compare(rhd.get_name()) < 0;
    }
    else
    {
        return false;
    }
}

int get_countries_count()
{
    int country_count = -1;
    std::string input_line = "";

    for(;;)
    {
        std::cout << "Enter countries count: ";

        std::getline(std::cin, input_line);

        try
        {
            country_count = boost::lexical_cast<int>( input_line );
        }
        catch( boost::bad_lexical_cast const& )
        {
            std::cout << "Error: input string was not valid, try again." << std::endl;
            continue;
        }

        if(country_count < 0 || country_count > MAX_NUMBER_OF_COUNTRIES)
        {
            std::cout << "Countris count is have to be between 0 and 25.\n";
            continue;
        }

        break;
    }

    return country_count;
}

void fill_countries(int countries_count, Plane& plane)
{
    int j = 0;

    while(j < countries_count)
    {
        std::string country_line = "";

        std::cout << "Enter information about country (example: \"France 1 4 4 6\"):\n";

        std::getline(std::cin, country_line);

        try
        {
            std::vector<std::string> country_parameters;

            boost::split(country_parameters, country_line, boost::is_any_of("\t "));

            //*
            std::string country_name = country_parameters[0];

            if(country_name.length() > MAX_LENGTH_OF_COUNTRY_NAME || country_name.length() == 0)
            {
                std::cout << "Country name must be 1-" <<  MAX_NUMBER_OF_COUNTRIES << " symbols.\n";
                continue;
            }

            int x_l = boost::lexical_cast<int>(country_parameters[1]);
            int y_l = boost::lexical_cast<int>(country_parameters[2]);
            int x_h = boost::lexical_cast<int>(country_parameters[3]);
            int y_h = boost::lexical_cast<int>(country_parameters[4]);

            //std::cout << country_name << x_l << y_l << x_h << y_h << std::endl;
            //*/

            if (!plane.is_valid_position(x_l, y_l, x_h, y_h))
            {
                std::cout << "Invalid position. We already have countries there. Try again.\n";
                continue;
            }

            if(x_l >= x_h && y_l >= y_h)
            {
                std::cout << "You put wrong coordinates.\n";
                continue;
            }

            if(x_h - x_l > MOST_NORTHEASTWARD_CITY || y_h - y_l > MOST_NORTHEASTWARD_CITY)
            {
                std::cout << "Most notheastward value cant be more than 10.\n";
                continue;
            }

            std::cout << "Valid poisition\n";

            Country* cntry = new Country(country_name, x_l, y_l, x_h, y_h);
            plane.add_country(cntry);
        }
        catch( boost::bad_lexical_cast const& )
        {
            std::cout << "Error: input string was not valid, try again." << std::endl;
            continue;
        }
        ++j;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int country_count = -1;

    typedef std::vector<Country> countries_vector_t;

    std::vector< countries_vector_t > results;

    while(country_count != 0)
    {
        country_count = get_countries_count();

        if (country_count == 0)
        {
            std::cin.ignore();
            break;
        }

        Plane plane;
        fill_countries(country_count, plane);
        plane.populate();

        // for debug
        //plane.print_grid();

        const int MAX_DAYS_PERIOD = 10000;
        // calculate time for deffudion
        for(;;)
        {
            if(plane.get_days_spend() == MAX_DAYS_PERIOD || plane.is_all_countryes_complite())
            {
                break;
            }
            plane.money_day_move();
        }

        std::vector<Country> countryes_list = plane.get_countryes_list();

        countries_vector_t current_result;
        current_result.assign(countryes_list.begin(), countryes_list.end());
        results.push_back(current_result);
    }

    for (unsigned int i = 0; i < results.size(); ++i)
    {
        std::sort(results[i].begin(), results[i].end(), compare_countries);
    }

    for (unsigned int i = 0; i < results.size(); ++i)
    {
        for (unsigned int j = 0; j < results[i].size(); ++j)
        {
            std::cout << results[i][j].get_name() << "\t\t"
                      << results[i][j].get_day_when_complite() << std::endl;
        }

        for (int r = 0; r < 80; ++r)
        {
            std::cout << "-";
        }
        std::cout << std::endl;
    }


    return a.exec();
}
