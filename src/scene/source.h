#ifndef SOURCE_H
#define SOURCE_H

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
#include <string>

//Own Libs
#include <src/parameter/parameter.h>

namespace SSR
{

  /**
   * This class represents a source. Since this VST Plugin remotely controls
   * the SSR, this class is the equivalent to a audio source in the SSR.
   */
  class Source
  {

  public:

    /**
     * Enum representing all parameters as integer values beginning with 0
     * and the last elemt represents the quantity of parameters.
     */
    enum parameter  {
      x_position_idx = 0,
      y_position_idx,
      gain_idx,
      orientation_idx,
      mute_idx,
      model_point_idx,
      fixed_idx,
      parameter_count
    };

    /**
     * Constructor setting the source id, name and the scene_range to the
     * transferred parameters.
     *
     * The Parameter member will be set as follows:
     *
     * x_position:
     * translate_to_continuous function = SSR::translations::x_position_discrete_to_continuous
     * translate_to_discrete function = SSR::translations::x_position_continuous_to_discrete
     * name = "X Position"
     *
     * y_position:
     * translate_to_continuous function = SSR::translations::y_position_discrete_to_continuous
     * translate_to_discrete function = SSR::translations::y_position_continuous_to_discrete
     * name = "Y Position"
     *
     * gain:
     * translate_to_continuous function = SSR::translations::gain_discrete_to_continuous
     * translate_to_discrete function = SSR::translations::gain_continuous_to_discrete
     * name = "Gain"
     *
     * orientation:
     * translate_to_continuous function = SSR::translations::orientation_discrete_to_continuous
     * translate_to_discrete function = SSR::translations::orientation_continuous_to_discrete
     * name = "Orientation"
     *
     * mute:
     * translate_to_continuous function = SSR::translations::mute_discrete_to_continuous
     * translate_to_discrete function = SSR::translations::mute_continuous_to_discrete
     * name = "Mute"
     *
     * model_point:
     * translate_to_continuous function = SSR::translations::model_point_discrete_to_continuous
     * translate_to_discrete function = SSR::translations::model_point_continuous_to_discrete
     * name = "Model"
     * 
     * fixed:
     * translate_to_continuous function = SSR::translations::fixed_discrete_to_continuous
     * translate_to_discrete function = SSR::translations::fixed_continuous_to_discrete
     * name = "Fixed"
     * 
     * @see parameter_translation_functions.h
     *
     * All parameters will be set to default values.
     *
     * @see set_all_parameters_on_default()
     *
     * The X and Y position of the source will be set to a random position
     * in the range -1.0 and 1.0.
     *
     * @param           id              The ID this source shall have.
     *
     * @param           name            The name this source shall have.
     *
     * @param           scene_range     The range of the scene.
     */
    explicit Source(const unsigned int id, const std::string name, float scene_range);

    /**
     * Constructor setting the id, name, scene_range and jackport to the
     * transferred parameters.
     *
     * This constructor calls another constructor for initialization,
     * for more information read the documentation of the following
     * constructor:
     *
     * Source(const unsigned int id, const std::string name, float scene_range)
     *
     * @see Source(const unsigned int id, const std::string name, float scene_range)
     *
     * @param           id              The ID this source shall have.
     *
     * @param           name            The name this source shall have.
     *
     * @param           scene_range     The range of the scene.
     *
     * @param           jackport        The jackport this source shall connect
     *                                  to.
     */
    explicit Source(const unsigned int id, const std::string name, float scene_range, const std::string jackport);

    /**
     * Copy constructor.
     *
     * @param           other           The other source which shall be
     *                                  copied.
     */
    Source(const Source& other);

    /**
     * Copy assignment constructor.
     *
     * @param           other           The other source which shall be
     *                                  copied.
     */
    Source& operator=(const Source& other);

    /**
     * Swaps all the data of the first with the second source.
     *
     * @param           first           Source which data shall be swapped
     *                                  with the second source.
     *
     * @param           second          Source which data shall be swapped
     *                                  with the first souce.
     */
    void swap(SSR::Source& first, SSR::Source& second);

    /**
     * Destructor.
     */
    ~Source();

    /**
     * Setter for the source discrete X position parameter.
     *
     * @param           position        The new position to which the source x
     *                                  position will be set.
     */
    void set_x_position_discrete(const float position);

    /**
     * Returns the source x position.
     *
     * @return the source x position.
     */
    SSR::Parameter<float, float> get_x_position() const;

    /**
     * Setter for the source continuous X position.
     *
     * @param           position        The new relative position to which the source x
     *                                  position will be set relatively.
     */
    void set_x_position_continuous(const float position);

    /**
     * Setter for the source discrete Y position parameter.
     *
     * @param           position        The new discrete position to which the
     *                                  source Y position will be set.
     */
    void set_y_position_discrete(const float position);

    /**
     * Returns the the source Y position.
     *
     * @return the the source Y position.
     */
    SSR::Parameter<float, float> get_y_position() const;

    /**
     * Setter for the source continuous Y position.
     *
     * @param           position        The new continuous position to which
     *                                  the source Y position will be set to.
     */
    void set_y_position_continuous(const float position);

    /**
     * Setter for the source gain. The transfered parameter
     * linear defines if the transfered value is linear gain or
     * dB gain.
     *
     * The parameter gain is held as a linear value.
     * If the transfered parameter linear is set on true, no conversion
     * will be computed, otherwise the value will be converted from
     * dB to linear.
     *
     * @see Helper::dB_to_linear
     *
     * @param           gain_value              The value to which the gain will
     *                                          be set.
     *
     * @param           linear                  Defines if the transfered gain value
     *                                          is linear (true) or not (false).
     */
    void set_discrete_gain(const float gain_value, const bool linear);

    /**
     * Setter for the continuous source gain .
     *
     * @param           gain_value              The continuous gain value the gain
     *                                          shall be set to.
     */
    void set_continuous_gain(const float gain_value);

    /**
     * Returns the gain parameter of the source.
     *
     * @return the gain parameter of the source.
     */
    SSR::Parameter<float, float> get_gain() const;

    /**
     * Setter for the source ID.
     *
     * @param           new_id       The ID to which the source ID will
     *                               be set.
     */
    void set_id(const unsigned int new_id);

    /**
     * Getter for the source ID parameter.
     *
     * @return the source ID.
     */
    unsigned int get_id() const;

    /**
     * Setter for the source discrete orientation.
     *
     * @param           discrete_orientation    The value to which the source
     *                                          orientation will be set.
     */
    void set_discrete_orientation(const float discrete_orientation);

    /**
     * Setter for the source continuous orientation.
     *
     * @param           continuous_orientation  The value to which the source
     *                                          orientation will be set.
     */
    void set_continuous_orientation(const float continuous_orientation);

    /**
     * Returns the source orientation parameter.
     *
     * @return the source orientation parameter.
     */
    SSR::Parameter<float, float> get_orientation() const;

    /**
     * Setter for the source mute parameter - true mutes the source.
     *
     * @param           discrete_mute       The value on which the source mute
     *                                      parameter will be set:
     *                                      true -> mute
     *                                      false -> unmute
     */
    void set_discrete_mute(const bool discrete_mute);

    /**
     * Setter for the source mute parameter - 1.0 mutes the source and 0.0
     * unmutes it.
     *
     * @param           continuous_mute     The value to which the source mute
     *                                      parameter will be set:
     *                                      1.0 -> mute
     *                                      0.0 -> unmute
     */
    void set_continuous_mute(const float continuous_mute);

    /**
     * Returns the source mute parameter.
     *
     * @return the source mute parameter.
     */
    SSR::Parameter<bool, float> get_mute() const;

    /**
     * Sets the discrete source model point parameter where the
     * transferred parameter point determines whether it is a point source
     * (true) or a plane source (false).
     *
     * @param           point           Determines whether the source is point
     *                                  (true) or plane (false).
     */
    void set_discrete_model_point(const bool point);

    /**
     * Sets the continuous source model where the transferred parameter point
     * determines whether it is a point source (1.0) or a plane source (0.0).
     *
     * @param           point           Determines whether the source is point
     *                                  (1.0) or plane (0.0).
     */
    void set_continuous_model_point(const float point);

    /**
     * Returns the source model parameter.
     *
     * @return the source model parameter.
     */
    SSR::Parameter<bool, float> get_model_point() const;

    /**
     * Sets the discrete source fixed state, where the transferred parameter
     * fixed_value determines whether the source is fixed (true) or movable (false).
     *
     * @param           fixed_value     Determines whether the source shall
     *                                  be fixed (true) or movable (false).
     */
    void set_discrete_fixed(const bool fixed_value);

    /**
     * Sets the continuous source fixed state, where the transferred parameter
     * fixed_value determines whether the source is fixed (1.0) or movable (0.0).
     *
     * @param           fixed_value     Determines whether the source shall
     *                                  be fixed (1.0) or movable (0.0).
     */
    void set_continuous_fixed(const float fixed_value);

    /**
     * Returns the source fixed parameter.
     *
     * @return the source fixed parameter.
     */
    SSR::Parameter<bool, float> get_fixed() const;

    /**
     * Setter for the source name parameter.
     *
     * @param           new_name        The name to which the source shall be set.
     */
    void set_name(const std::string new_name);

    /**
     * Getter for the source name.
     *
     * @return the source name.
     */
    std::string get_name() const;

    /**
     * Setter for the source properties file.
     *
     * @param           name            The name of the source properties file.
     */
    void set_properties_file(const std::string name);

    /**
     * Returns the name of the properties file.
     *
     * @return the name of the properties file.
     */
    std::string get_properties_file() const;

    /**
     * Setter for the source jackport.
     *
     * @param           name               The name of the source jackport.
     */
    void set_jackport(const std::string name);

    /**
     * Returns the name of the jackport this source is connected to.
     *
     * @return the name of the jackport this source is connected to.
     */
    std::string get_jackport() const;

    /**
     * This method sets all parameters to the default values.
     *
     * Some of the current default values are not verified:
     * - ID
     * - Name
     * - Properties File
     *
     * Others are verified by the asdf.xsd (a standard xml representation
     * of a scene) from the SSR Software:
     * - Fixed
     * - Mute
     *
     * This leaves the following parameters which I set to default
     * parameters as I thought it would be the best:
     * - ID
     * - Name
     * - X Position
     * - Y Position
     * - Orientation
     * - Model
     * - Port
     * - Properties File
     */
    void set_all_parameters_on_default();

  private:

    /**
     * The source ID.
     */
    unsigned int id;

    /**
     * The source x position.
     */
    Parameter<float, float> x_position;

    /**
     * The source y position.
     */
    Parameter<float, float> y_position;

    /**
     * The source gain.
     */
    Parameter<float, float> gain;

    /**
     * The source orientation (azimuth).
     */
    Parameter<float, float> orientation;

    /**
     * The source mute, defining whether the source is muted or not.
     */
    Parameter<bool, float> mute;

    /**
     * The source model, defining whether the source is a point source
     * (true) or a plane source (false).
     */
    Parameter<bool, float> model_point;

    /**
     * Defines whether the source has a fixed position (true) or not (false).
     */
    Parameter<bool, float> fixed;

    /**
     * The source name.
     */
    std::string name;

    /**
     * The properties file of the source.
     */
    std::string properties_file;

    /**
     * The source port (Jackport).
     */
    std::string jackport;

  };

}

/**
 * Equal operator returning true if the lhs source is equal to the rhs source,
 * false otherwise.
 *
 * @param       lhs             The left hand side source.
 *
 * @param       rhs             The right hand side source.
 *
 * @return true if the lhs source is equal to the rhs source, false otherwise.
 */
bool operator==(const SSR::Source& lhs, const SSR::Source& rhs);

/**
 * Unequal operator returning true if the lhs source is unequal to the rhs source,
 * false otherwise.
 *
 * @param       lhs             The left hand side source.
 *
 * @param       rhs             The right hand side source.
 *
 * @return true if the lhs source is unequal to the rhs source, false otherwise.
 */
bool operator!=(const SSR::Source& lhs, const SSR::Source& rhs);

namespace std
{

  /**
   * Swaps the data of the first source with the date of the second source.
   *
   * @param     first           The source which data shall be swapped with the
   *                            second source.
   *
   * @param     second          The source which data shall be swapped with the
   *                            first source.
   */
  void swap(SSR::Source& first, SSR::Source& second);

}

#endif
