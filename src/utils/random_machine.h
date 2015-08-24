#ifndef RANDOM_MACHINE_H
#define RANDOM_MACHINE_H

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

#include <memory>
#include <random>

namespace SSR {

  /**
   * This class represents a Random machine to provide various random generated
   * values of various types.
   *
   * The class was designed regarding the singleton design pattern.
   *
   * @since 2015-06-23
   */
  class Random_machine {

  public:

      /**
       * Returns a Random_machine instance which will be instantiated once for
       * the whole runtime.
       *
       * @return a Random_machine instance.
       */
      static std::shared_ptr<Random_machine> get_instance()
      {
        static std::shared_ptr<Random_machine> instance(new Random_machine());
        return instance;
      }

      /**
       * Returns a random value between get_minimum() and get_maximum() which
       * is in general the minimum value of unsigned int (0) and the maximum
       * value of unsigned int (4294967295).
       */
      unsigned int operator()() const;

      /**
       * Returns a random value between get_minimum() and get_maximum() which
       * is in general the minimum value of unsigned int (0) and the maximum
       * value of unsigned int (4294967295).
       */
      unsigned int generate() const;

      /**
       * Returns a random value of type unsigned int between lower_bound and
       * upper_bound (including).
       *
       * @param         lower_bound     The value that determines the including lower bound of the
       *                                generated value.
       * @param         upper_bound     The value that determines the including upper bound of the
       *                                generated value.
       *
       * @return a random value of type unsigned int between lower_bound and
       * upper_bound (including).
       */
      unsigned int generate_unsigned_int(const unsigned int lower_bound, const unsigned int upper_bound) const;

      /**
       * Returns a random char between lower_bound and upper_bound (including).
       *
       * @param         lower_bound     The value that determines the including lower bound of the
       *                                character.
       * @param         upper_bound     The value that determines the including upper bound of the
       *                                character.
       *
       * @return a random char between lower_bound and upper_bound (including).
       */
      char generate_char(const char lower_bound, const char upper_bound) const;

      /**
       * Returns a random string which has the transferred length and includes characters
       * defined by the transferred lower_bound and upper_bound (including).
       *
       * @param         lower_bound     The value that determines the including lower bound of the
       *                                characters which will be concatenated.
       * @param         upper_bound     The value that determines the including upper bound of the
       *                                characters which will be concatenated.
       *
       * @return a random string which has the transferred length and includes characters
       * defined by the transferred lower_bound and upper_bound (including).
       */
      std::string generate_string(const std::size_t length, const char lower_bound, const char upper_bound) const;

      /**
       * Returns a random value of type int between lower_bound and upper_bound (including).
       *
       * @param         lower_bound     The value that determines the including lower bound of the
       *                                generated value.
       * @param         upper_bound     The value that determines the including upper bound of the
       *                                generated value.
       * @return a random value of type int between lower_bound and upper_bound (including).
       */
      int generate_int(const int lower_bound, const int upper_bound) const;


      /**
       * Returns a random value of type float between lower_bound and upper_bound (including).
       *
       * @param         lower_bound     The value that determines the including lower bound of the
       *                                generated value.
       * @param         upper_bound     The value that determines the including upper bound of the
       *                                generated value.
       *
       * @return a random value of type float between lower_bound and upper_bound (including).
       */
      float generate_float(const float lower_bound, const float upper_bound) const;

      /**
       * Returns a random value of type double between lower_bound and upper_bound (including).
       *
       *
       * @param         lower_bound     The value that determines the including lower bound of the
       *                                generated value.
       * @param         upper_bound     The value that determines the including upper bound of the
       *                                generated value.
       * @return a random value of type double between lower_bound and upper_bound (including).
       */
      double generate_double(const double lower_bound, const double upper_bound) const;

      /**
       * Returns the minimum value of the computed random values an instance
       * of this class can produce.
       */
      unsigned int get_minimum() const;

      /**
       * Returns the maximum value of the computed random values an instance
       * of this class can produce when calling generate().
       */
      unsigned int get_maximum() const;

      /**
       * Destructor.
       */
      ~Random_machine();

  private:

      /**
       * Constructs the random machine.
       */
      Random_machine();

      /**
       * A random number generator that produces non-deterministic random numbers,
       * if supported.
       *
       * @see http://www.cplusplus.com/reference/random/random_device
       */
      std::unique_ptr<std::random_device> random_device;

      /**
       * Copy constructor which is deleted.
       */
      Random_machine(const Random_machine& other) = delete;

      /**
       * Copy assignment operator which is deleted.
       */
      Random_machine& operator=(const Random_machine& rhs) = delete;

      /**
       * Move constructor which is delted.
       */
      Random_machine(Random_machine&& other) = delete;

  };

}

#endif
