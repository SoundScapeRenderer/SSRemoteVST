#ifndef SOURCE_H
#define SOURCE_H

//C++ Libs
#include <memory>
#include <string>

//Own Libs
#include <src/parameter/parameter.h>

namespace SSR
{

  class Source
  {

  public:
    explicit Source(const unsigned int id, const std::string name);

    explicit Source(const unsigned int id, const std::string name, const std::string jackport);

    Source(const Source& source);

    Source& operator=(const Source& other);

    void swap(SSR::Source& first, SSR::Source& second);

    ~Source();

    /**
     * Enum representing all parameters as integer values beginning with 0
     * and the last elemt represents the quantity of parameters.
     *
     * @author Florian Willich
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
     * Setter for the source x position parameter.
     *
     * This method automatically computes the sources relative x position.
     *
     * @param           new_position    The new position to which the source x
     *                                  position will be set.
     * @param           scene_range     The scenes range.
     *
     * @author          Florian Willich
     */
    void set_x_position_absolute(const float new_position);

    SSR::Parameter<float, float> get_x_position() const;

    /**
     * Setter for the source x relative position.
     *
     * This method automatically computes the sources absolute x position.
     *
     * @param           new_relative_position    The new relative position to which the source x
     *                                           position will be set relatively.
     * @param           scene_range              The scenes range.
     *
     * @author          Florian Willich
     *
     */
    void set_x_position_relative(const float new_relative_position);

    /**
     * Setter for the source y position parameter.
     *
     * This method automatically computes the sources relative y position.
     *
     * @param           new_position    The new position to which the source y
     *                                  position will be set.
     * @param           scene_range     The scenes range.
     *
     * @author          Florian Willich
     */
    void set_y_position_absolute(const float new_position);

    SSR::Parameter<float, float> get_y_position() const;

    /**
     * Setter for the source y relative position.
     *
     * This method automatically computes the sources absolute y position.
     *
     * @param           new_relative_position    The new relative position to which the source y
     *                                           position will be set relatively.
     * @param           scene_range              The scenes range.
     *
     * @author          Florian Willich
     *
     */
    void set_y_position_relative(const float new_relative_position);

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
     * @param           value                   The value on which the gain will
     *                                          be set. If the value is less linear
     *                                          and less than 0.0, the gain will be
     *                                          set on 0.0.
     * @param           linear                  Defines if the transfered gain value
     *                                          is linear.
     *
     * @author          Florian Willich
     */
    void set_absolute_gain(const float value, const bool linear);

    void set_relative_gain(const float value);

    SSR::Parameter<float, float> get_gain() const;

    /**
     * Setter for the source ID.
     *
     * @param           value           The value on which the source ID will
     *                                  be set.
     *
     * @author          Florian Willich
     */
    void set_id(const unsigned int new_id);

    /**
     * Getter for the source ID parameter.
     *
     * @return the source ID.
     *
     * @author          Florian Willich
     */
    unsigned int get_id() const;

    /**
     * Setter for the source orientation parameter.
     *
     * @param           value           The value on which the source orientation
     *                                  will be set.
     *
     * @author          Florian Willich
     */
    void set_absolute_orientation(const float new_absolute_orientation);

    void set_relative_orientation(const float new_relative_orientation);

    SSR::Parameter<float, float> get_orientation() const;

    /**
     * Setter for the source mute parameter.
     *
     * @param           value               The value on which the source mute
     *                                      parameter will be set.
     *
     * @author          Florian Willich
     */
    void set_absolute_mute(const bool value);

    void set_relative_mute(const float value);

    SSR::Parameter<bool, float> get_mute() const;

    /**
     * Setter for the source model parameter. If the transfered parameter is true,
     * the source model is point, otherwise its a plane model.
     *
     * @param           value               True if the source model is point or
     *                                      false if it is a plane model.
     *
     * @author          Florian Willich
     */
    void set_absolute_model_point(const bool value);

    void set_relative_model_point(const float value);

    SSR::Parameter<bool, float> get_model_point() const;

    /**
     * Setter for the source fixed parameter. If the transfered parameter is true,
     * the source model is fixed otherwise it's changeable.
     *
     * @param           value               True if the source model is fixed,
     *                                      otherwise false.
     *
     * @author          Florian Willich
     */
    void set_absolute_fixed(const bool value);

    void set_relative_fixed(const float new_relative_fixed_value);

    SSR::Parameter<bool, float> get_fixed() const;

    /**
     * Setter for the source name parameter.
     *
     * @param           value               The name on which to set the source.
     *
     * @author          Florian Willich
     */
    void set_name(const std::string value);

    /**
     * Getter for the source name.
     *
     * @return the source name.
     *
     * @author Florian Willich
     */
    std::string get_name() const;

    /**
     * Setter for the source properties file.
     *
     * @param           value               The name of the source properties file.
     *
     * @author          Florian Willich
     */
    void set_properties_file(const std::string value);

    std::string get_properties_file() const;

    /**
     * Setter for the source jackport.
     *
     * @param           value               The name of the source jackport.
     *
     * @author          Florian Willich
     */
    void set_jackport(const std::string value);

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
     *
     * @param           scene_range             The scene range.
     *
     * @author Florian Willich
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

bool operator==(const SSR::Source& rhs, const SSR::Source& lhs);
bool operator!=(const SSR::Source& rhs, const SSR::Source& lhs);

namespace std {
  void swap(SSR::Source& first, SSR::Source& second);
}

//std::ostream& operator<<(std::ostream& os, SSR::Source& source);

#endif
