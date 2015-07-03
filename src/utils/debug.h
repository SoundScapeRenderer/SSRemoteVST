#ifndef DEBUG_H
#define DEBUG_H

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
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>

#define ERROR_MESSAGE 1

#if ERROR_MESSAGE

#define DEBUG_TCP_OUT 1
#define DEBUG_TCP_IN 1

#endif

namespace debug
{

  namespace print
  {

    /**
     * Prints out anything you want in 'Debug' mode which
     * is printing out the following on std::cout:
     *
     * [Debug] <Call of your function invokes operator<< on return value> <end of line>
     * TODO: How to specify the return value of a templated Funtion type?
     */
    template <typename Fun>
    void print_function(Fun fun)
    {
      std::stringstream sstream;
      sstream << "[Debug] " << fun() << std::endl;
      std::cout << sstream.str();
    }

    /**
     * Prints out the object in
     */
    template <class T>
    void print_object(T object)
    {
      std::stringstream sstream;
      sstream << "[Debug] " << object << std::endl;
      std::cout << sstream.str();
    }

  }

  namespace benchmark
  {

    /**
     * This class represents a benchmark which provides the following:
     *
     * - start method
     * - stop method
     * - result method
     *
     * Use example:
     *
     * debug::benchmark::Benchmark bench;
     * bench.start()
     * ...
     * some stuff to compute
     * ...
     * bench.stop()
     *
     * double duration = bench.result()
     *
     */
    class Benchmark
    {
    public:
      typedef std::chrono::high_resolution_clock hrc;

      Benchmark();
      ~Benchmark();
      void start();
      void stop();
      double result();

    private:
      hrc::time_point begin;
      hrc::time_point end;
      bool started;
      bool ended;
    };

  }

}

#endif
