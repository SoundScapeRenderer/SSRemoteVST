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

//C++ Libs
#include <memory>
#include <sstream>
#include <fstream>
#include <iostream>

//Own Libs
#include <src/utils/logger.h>
#include <src/utils/clock.h>

void SSR::Logger::log(Logger::Level level, std::string message, bool log_in_file) {
        sstream->str(std::string(""));

        append_current_time();
        append_log_level(level);

        *sstream << message << std::endl;

        if (log_in_file) {
            logfile << sstream->str();
        } else {
            std::cerr << sstream->str();
        }

    }


SSR::Logger::~Logger()
{
  logfile.close();
}


SSR::Logger::Logger(std::string filename)
: logfile(filename, std::fstream::out | std::fstream::trunc)
, sstream(new std::stringstream(std::string("")))
{

}

void SSR::Logger::append_current_time()
{
  *sstream << "[" << SSR::compute_current_time() << "] ";
}


void SSR::Logger::append_log_level(SSR::Logger::Level level)
{
  switch (level) {

    case INFO:
      *sstream << "[INFO] ";
      break;

    case ERROR:
      *sstream << "[ERROR] ";
      break;

    default:
      *sstream << "[UNKNOWN LOG LEVEL] ";
      break;

  }
}
