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
     * This class represents a VST parameter:
     *
     * Every VST parameter requires the following information:
     *
     * - value
     * - name
     *
     * Internally the value is stored with its discrete and continuous
     * representation. With discrete any type and value is meant. With
     * continuous a value between 0.0 and 1.0 is meant which are in
     * general of type float (floating point).
     *
     * A Parameter also provides a default discrete value.
     *
     * Storing the Parameters value discrete and continuous requires translation
     * functions. A Parameter therefore owns a translation function from the
     * discrete value to the continuous value and its correlating reverse
     * function.
     *
     * The name is represented as string.
     *
     * Example on how to use this class:
     *
     * std::function<float(bool)> to_continuous = [](bool discrete) { return discrete ? 1.0f : 0.0f; };
     * std::function<bool(float)> to_discrete = [](float continuous) { return continuous == 1.0; };
     *
     * SSR::Parameter<bool, float> p(false, false, to_continuous, to_discrete, "Mute");
     *
     * std::cout << p << std::endl;
     * p.set_discrete_value(true);
     * std::cout << p << std::endl;
     * p.set_continuous_value(0.0f);
     * std::cout << p << std::endl;
     * p.set_continuous_value(1.0f);
     * std::cout << p << std::endl;
     * p.set_to_default();
     * std::cout << p << std::endl;
     *
     * Output:
     *
     * Mute: Discrete Value -> 0 | Continuous Value -> 0
     * Mute: Discrete Value -> 1 | Continuous Value -> 1
     * Mute: Discrete Value -> 0 | Continuous Value -> 0
     * Mute: Discrete Value -> 1 | Continuous Value -> 1
     * Mute: Discrete Value -> 0 | Continuous Value -> 0
     *
     * @tparam  DiscreteType    The type of the discrete value.
     * @tparam  ContinuousType  The type of the continuous value (float in
     *                          general).
     *
     * @author Florian Willich
     */
    template<class DiscreteType, class ContinuousType>
    class Parameter {

    public:

        /**
         * Constructs a Parameter object with the transferred parameters.
         *
         * @param   discrete_value          The discrete value the parameter is
         *                                  initialised with.
         *
         * @param   default_discrete_value  The default discrete value the
         *                                  parameter can be set to.
         *
         * @param   translate_to_continuous The function that translates the
         *                                  discrete value to the continuous
         *                                  value.
         *
         * @param   translate_to_discrete   The function that translates the
         *                                  continuous value to the discrete
         *                                  value.
         *
         * @param   name                    The name of the parameter.
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
                , default_discrete_value(default_discrete_value)
                , continuous_value(translate_to_continuous(discrete_value))
                , name(name)
        {

        }

        /**
         * Copy constructor.
         *
         * @param   other   The parameter which will be copied.
         *
         * @author Florian Willich
         */
        Parameter(const Parameter<DiscreteType, ContinuousType>& other)
                : translate_to_continuous(other.translate_to_continuous)
                , translate_to_discrete(other.translate_to_discrete)
                , discrete_value(other.discrete_value)
                , default_discrete_value(other.default_discrete_value)
                , continuous_value(other.continuous_value)
                , name(other.name)
        {

        }

        /**
         * Assignment operator.
         *
         * @param             rhs             The right hand side parameter.
         *
         * @return            the new parameter equal to rhs.
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

        /**
         * Move constructor.
         *
         * @param           other       The parameter which members will be
         *                              moved.
         *
         * @author    Florian Willich
         */
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
         * Destructor.
         */
        ~Parameter() {

        }

        /**
         * Returns the discrete value.
         *
         * @return the discrete value.
         *
         * @author Florian Willich
         */
        DiscreteType get_discrete_value() const
        {
            return discrete_value;
        }

        /**
         * Returns the continuous value.
         *
         * @return the continuous value.
         *
         * @author Florian Willich
         */
        ContinuousType get_continuous_value() const
        {
            return continuous_value;
        }

        /**
         * Sets the Parameters discrete value to new_discrete_value and
         * also the continuous value by translating it.
         *
         *
         * @param    new_discrete_value       The new discrete value to
         *                                    which the Parameters value
         *                                    will be set.
         *
         * @author   Florian Willich
         */
        void set_discrete_value(const DiscreteType new_discrete_value)
        {
            discrete_value = new_discrete_value;
            continuous_value = translate_to_continuous(discrete_value);
        }

        /**
         * Sets the Parameters continuous value to new_continuous_value and
         * also the discrete value by translating it.
         *
         *
         * @param    new_continuous_value       The new continuous value to
         *                                      which the Parameters value
         *                                      will be set.
         *
         * @author   Florian Willich
         */
        void set_continuous_value(const ContinuousType new_continuous_value)
        {
            continuous_value = new_continuous_value;
            discrete_value = translate_to_discrete(continuous_value);
        }

        /**
         * Sets the Parameter to the default value which was set during
         * construction.
         *
         * @author   Florian Willich
         */
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
         * @param             new_name     The new name on which to set the name
         *                                 of the parameter
         *
         * @author    Florian Willich
         */
        void set_name(const std::string &new_name)
        {
            name = new_name;
        }

        /**
         * Swaps the lhs with the rhs Parameter. Please note that this method
         * requires the Parameters types to be swapable by using the namespace std.
         *
         * @author    Florian Willich
         */
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
         * The discrete representation of the Parameters value.
         */
        DiscreteType discrete_value;

        /**
         * The default discrete value.
         */
        DiscreteType default_discrete_value;

        /**
         * The continuous representation of the Parameters value.
         */
        ContinuousType continuous_value;

        /**
         * Function that translates the discrete to the continuous value.
         */
        std::function<ContinuousType(DiscreteType)> translate_to_continuous;

        /**
         * Function that translates the continuous to the discrete value.
         */
        std::function<DiscreteType(ContinuousType)> translate_to_discrete;

        /**
         * The name of the parameter
         */
        std::string name;

    };

}

/**
 * Returning an output stream containing the parameter data as a string as follows:
 *
 * 'name': Discrete Value -> 'discrete_value' | Continuous Value -> 'continuous_value'
 *
 * @param               os              The output stream to which the string
 *                                      representation of a Parameter will be
 *                                      added.
 * @param               parameter       The Parameter which data will be
 *                                      represented as a string.
 *
 * @return the output stream containing the Parameters representation as a string.
 *
 * @author              Florian Willich
 */
template <class DiscreteType, class ContinuousType>
std::ostream& operator<<(std::ostream& os, const SSR::Parameter<DiscreteType, ContinuousType>& parameter)
{
    os << parameter.get_name() << ": Discrete Value -> " << parameter.get_discrete_value() << " | Continuous Value -> " << parameter.get_continuous_value();
    return os;
}

/**
 * Equal operator returning true if the lhs and rhs Parameters are equal, else
 * false.
 *
 * @param       lhs         The left hand side Parameter.
 *
 * @param       rhs         The right hand side Parameter.
 *
 * @return true if the lhs and rhs Parameters are equal, else false.
 */
template <class DiscreteType, class ContinuousType>
bool operator==(const SSR::Parameter<DiscreteType, ContinuousType>& lhs, const SSR::Parameter<DiscreteType, ContinuousType>& rhs)
{
    return (lhs.get_discrete_value() == rhs.get_discrete_value()) && (lhs.get_continuous_value() == rhs.get_continuous_value());
}

/**
 * Unequal operator returning false if the lhs and rhs Parameters are equal, else
 * true.
 *
 * @param       lhs         The left hand side Parameter.
 *
 * @param       rhs         The right hand side Parameter.
 *
 * @return false if the lhs and rhs Parameters are equal, else true.
 */
template <class DiscreteType, class ContinuousType>
bool operator!=(const SSR::Parameter<DiscreteType, ContinuousType>& lhs, const SSR::Parameter<DiscreteType, ContinuousType>& rhs)
{
    return !(lhs == rhs);
}

#endif
