#ifndef LOGGER_H
#define LOGGER_H

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

//Own Libs
#include <src/utils/helper.h>

namespace SSR
{

  /**
   * This class represents a logger. It offers a method to log messages to
   * a file or to the std::cerr. This class was design regarding the
   * singelton design pattern.
   *
   * @since 2015-06-30
   */
  class Logger
  {

  public:

      /**
       * The log level.
       */
      enum Level {
          INFO,
          ERROR
      };

      /**
       * Returns an instance of this class. This method was designed regarding
       * the singleton design pattern.
       */
      static std::shared_ptr<Logger> get_instance()
      {
          static std::shared_ptr<Logger> instance(new Logger(SSR::helper::get_environment_variable(std::string("SSREMOTE_VST").c_str()) + "/log.txt"));
          return instance;
      }

      /**
       * Logs the transferred message with the transferred logging level (see
       * enum Level). The method will also add the current time to the logged
       * message and the resulting string will look as follows:
       *
       * [YYYY-MM-DD HH:mm:SS] [level] message
       *
       * If log_in_file is false, the logging will be streamed to std::cerr.
       *
       * CAUTION: This method will already add a linebreak at the end of the
       * message. So please do not append a linebreak at the end of the
       * message string!
       *
       * @param       level           The logging level.
       * @param       message         The message that shall be logged.
       * @param       log_in_file     Whether to log in file or not. If false
       *                              the logging message will be streamed
       *                              to std::cerr.
       */
      void log(Logger::Level level, std::string message, bool log_in_file);

      /**
       * Destructor closing the logfile.
       */
      ~Logger();

  private:

      /**
       * Constructor which transferred filename determines the filename of the
       * logfile including its path.
       *
       * The instantiated logfile will always be overwritten.
       *
       * @param   filename    The filename of the logfile including the full
       *                      path.
       */
      Logger(std::string filename);

      /**
       * Copy constructor which is deleted (explicitly not implemented).
       */
      Logger(const Logger& other) = delete;

      /**
       * Move constructor which is deleted (explicitly not implemented).
       */
      Logger(Logger&& other) = delete;

      /**
       * Assignment operator which is deleted (explicitly not implemented).
       */
      Logger& operator=(const Logger& other) = delete;

      /**
       * Appends the current time to the sstream object which will look as
       * follows (mind the blank spaces):
       *
       * ...[YYYY-MM-DD HH:mm:SS] ...
       */
      void append_current_time();

      /**
       * Appends the log level to the sstream object.
       */
      void append_log_level(Level level);

  private:

      /**
       * The logfile.
       */
      std::ofstream logfile;

      /**
       * The string stream object this class needs for string concatenation.
       */
      std::unique_ptr<std::stringstream> sstream;

  };

}

#endif
