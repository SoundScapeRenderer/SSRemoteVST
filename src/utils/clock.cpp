/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * Copyright © 2015
 * Quality and Usability Lab
 * Berlin Institute of Technology
 * http://www.qu.tu-berlin.de
 *
 * For more detailed information, please read the license.txt in the root directory.
 */

//Own Libs
#include <src/utils/clock.h>

//C++ Libs
#include <chrono>
#include <sstream>
#include <iostream>
#include <memory>
#include <iomanip>

std::string SSR::compute_current_time()
{
    std::time_t now_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    struct tm* parts = std::localtime(&now_c);

    std::unique_ptr<std::stringstream> ss(new std::stringstream(std::string("")));

    int year    = 1900 + parts->tm_year;
    int month   = 1    + parts->tm_mon;
    int day     = parts->tm_mday;
    int hour    = parts->tm_hour;
    int min     = parts->tm_min;
    int sec     = parts->tm_sec;

    *ss << year                 << "-";
    *ss << std::setfill('0')    << std::setw(2);
    *ss << month                << "-";
    *ss << std::setfill('0')    << std::setw(2);
    *ss << day << " ";
    *ss << std::setfill('0')    << std::setw(2);
    *ss << hour                 << ":";
    *ss << std::setfill('0')    << std::setw(2);
    *ss << min                  << ":";
    *ss << std::setfill('0')    << std::setw(2);
    *ss << sec;

    return ss->str();
}
