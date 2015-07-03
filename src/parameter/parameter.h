#ifndef PARAMETER_H
#define PARAMETER_H

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
#include <ostream>
#include <memory>
#include <string>
#include <functional>
#include <mutex>

namespace SSR {

  /**
   * This template class represents a mutable parameter.
   * A parameter got a value and a name.
   *
   * This class provides:
   * - several constructors
   * - several assignment operators
   * - several getter and setter methods
   * - swap method
   *
   * The motivation was to have one object representing a parameter, for
   * example a gain parameter having a float value for the gain value and
   * a representative name. Since there could be infinite types of parameter
   * values we made this a template class.
   *
   * Example:
   *
   * ...
   * SSR::Parameter<float> gain(1.0f, "Gain");
   * gain = 1.001f;
   * std::cout << gain << std::endl;
   * ...
   *
   * Output:
   * Gain: 1.001
   *
   * @author Florian Willich
   */
   template<class DiscreteType, class ContinuousType>
   class Parameter {

   public:

     /**
      * Default constructor initialises value with its default constructor
      * and name with "No Name Specified".
      *
      * @author   Florian Willich
      */
     explicit Parameter(        DiscreteType discrete_value,
                                DiscreteType default_discrete_value,
                                std::function<ContinuousType(DiscreteType)> translate_to_continuous,
                                std::function<DiscreteType(ContinuousType)> translate_to_discrete,
                                std::string name)
     : translate_to_continuous(translate_to_continuous)
     , translate_to_discrete(translate_to_discrete)
     , discrete_value(discrete_value)
     , continuous_value(translate_to_continuous(discrete_value))
     , name(name)
     {

     }

     /**
      * Copy constructor.
      *
      * @author Florian Willich
      */
      Parameter(const Parameter<DiscreteType, ContinuousType> &other)
      : translate_to_continuous(other.translate_to_continuous)
      , translate_to_discrete(other.translate_to_discrete)
      , discrete_value(other.discrete_value)
      , default_discrete_value(other.default_discrete_value)
      , continuous_value(other.continuous_value)
      , name(other.name)
      {

      }

      /**
       * Assignment operator for the parameter taking a Parameter<T>
       * as the right hand side object.
       *
       * @param             rhs             The right hand side parameter.
       *
       * @return            the newly assigned parameter equal to rhs.
       *
       * @author    Florian Willich
       */
      Parameter<DiscreteType, ContinuousType> &operator=(const Parameter<DiscreteType, ContinuousType> &rhs)
      {

        if (*this != rhs) {
          Parameter<DiscreteType, ContinuousType> tmp(rhs);
          swap(*this, tmp);
        }

        return *this;
      }

      Parameter(Parameter<DiscreteType, ContinuousType>&& other)
      : translate_to_continuous(std::move(other.translate_to_continuous))
      , translate_to_discrete(std::move(other.translate_to_discrete))
      , discrete_value(std::move(other.discrete_value))
      , default_discrete_value(std::move(other.default_discrete_value))
      , continuous_value(std::move(other.continuous_value))
      , name(std::move(other.name))
      {

      }

      /**
       * Deconstructor.
       */
      ~Parameter() {

      }

      /**
       * This method returns the parameters value.
       *
       * @return the parameters value.
       *
       * @author Florian Willich
       */
      DiscreteType get_discrete_value() const
      {
        return discrete_value;
      }

      ContinuousType get_continuous_value() const
      {
        return continuous_value;
      }

      /**
       * This method sets the parameters value with the transfered new_value.
       *
       * @param    new_value       The new value on which the current
       *                           parameters value will be set on.
       *
       * @author   Florian Willich
       */
      void set_discrete_value(const DiscreteType new_discrete_value)
      {
        discrete_value = new_discrete_value;
        continuous_value = translate_to_continuous(discrete_value);
      }

      void set_continuous_value(const ContinuousType new_continuous_value)
      {
        continuous_value = new_continuous_value;
        discrete_value = translate_to_discrete(continuous_value);
      }

      void set_to_default()
      {
        discrete_value = default_discrete_value;
        continuous_value = translate_to_continuous(discrete_value);
      }

      /**
       * This method returns the name of the parameter.
       *
       * @return the name of the parameter.
       *
       * @author    Florian Willich
       */
      std::string get_name() const
      {
        return name;
      }

      /**
       * This method sets the name of the parameter with the transfered
       * parameter new_name.
       *
       * @param             new_name                The new name on which to set the name
       *                                                    of the parameter
       *
       * @author    Florian Willich
       */
      void set_name(const std::string &new_name)
      {
        name = new_name;
      }

      friend void swap(Parameter<DiscreteType, ContinuousType> &lhs, Parameter<DiscreteType, ContinuousType> &rhs)
      {
        using namespace std;
        swap(lhs.discrete_value, rhs.discrete_value);
        swap(lhs.default_discrete_value, rhs.default_discrete_value);
        swap(lhs.continuous_value, rhs.continuous_value);
        swap(lhs.translate_to_discrete, rhs.translate_to_discrete);
        swap(lhs.translate_to_continuous, rhs.translate_to_continuous);
        swap(lhs.name, rhs.name);
      }

    private:

      /**
       * The value of the parameter.
       */
      DiscreteType discrete_value;

      DiscreteType default_discrete_value;

      ContinuousType continuous_value;

      std::function<ContinuousType(DiscreteType)> translate_to_continuous;

      std::function<DiscreteType(ContinuousType)> translate_to_discrete;

      /**
       * The name of the parameter
       */
      std::string name;

      std::mutex mutex;

    };

}

/**
 * Shift left operator for the SSR::Parameter class returning an output stream containing
 * the parameter data as a string as follows:
 *
 * <Parameter Name>: <Parameter Value>
 *
 * Example:
 * Parameter<float> a(1.0f, "X Position");
 * std::cout << a << std::endl;
 *
 * Result:
 * "X Position: 1.0f"
 *
 * @param               os                      The output stream which will be manipulated and returned.
 * @param               parameter       The parameter which data will be represented as a string.
 *
 * @return              the output stream containing the data of the parameter represented as a
 *                              string.
 *
 * @author              Florian Willich
 */
template <class DiscreteType, class ContinuousType>
std::ostream& operator<<(std::ostream& os, const SSR::Parameter<DiscreteType, ContinuousType>& parameter)
{
  os << parameter.get_name() << ": Absolute Value -> " << parameter.get_discrete_value() << " | Relative Value -> " << parameter.get_continuous_value() << std::endl;
  return os;
}

template <class DiscreteType, class ContinuousType>
bool operator==(const SSR::Parameter<DiscreteType, ContinuousType>& lhs, const SSR::Parameter<DiscreteType, ContinuousType>& rhs)
{
  return (lhs.get_discrete_value() == rhs.get_discrete_value()) && (lhs.get_continuous_value() == rhs.get_continuous_value());
}

template <class DiscreteType, class ContinuousType>
bool operator!=(const SSR::Parameter<DiscreteType, ContinuousType>& lhs, const SSR::Parameter<DiscreteType, ContinuousType>& rhs)
{
  return !(lhs == rhs);
}

namespace std
{

    /**
     * This method swaps the data of the first parameter with the second parameter.
     *
     * @param           first           The first parameter which data will be swapped with the second.
     * @param           second          The second parameter which data will be swapped with the first.
     *
     * @author  Florian Willich
     */
    template<class DiscreteType, class ContinuousType>
    void swap(SSR::Parameter<DiscreteType, ContinuousType>& first, SSR::Parameter<DiscreteType, ContinuousType>& second)
    {
      SSR::Parameter<DiscreteType, ContinuousType> tmp(first);
      first = second;
      second = tmp;
    }

}

#endif
