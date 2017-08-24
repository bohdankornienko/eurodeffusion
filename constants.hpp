#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

const int MAX_NUMBER_OF_COUNTRIES = 25;
const int MOST_NORTHEASTWARD_CITY = 10;

const int START_CAPITAL = 1000000;
const int PORTION_OF_COINS = 1000;

typedef struct _country_days_info
{
    std::string name;
    int complite_after_days;
} country_days_info_t;

// -- balance field types -- //
typedef struct _balance_info
{
    int balance;
    int income;
} balance_onfo_t;

typedef std::vector< balance_onfo_t > balance_info_vec_t;
typedef std::vector< balance_info_vec_t > balance_line_t;
typedef std::vector< balance_line_t > balance_map_t;

#endif // CONSTANTS_HPP
