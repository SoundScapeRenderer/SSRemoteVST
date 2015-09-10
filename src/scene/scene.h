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

#ifndef SCENE_H
#define SCENE_H

//C++ Libs
#include <memory>
#include <vector>

//Own Libs
#include <src/scene/source.h>

//JUCE Lib
#include <JUCE/JuceHeader.h>

namespace SSR
{

  /**
   * This class represents the SSR scene with all related sources.
   *
   * @since 2015-07-20
   */
  class Scene
  {

  public:

    /**
     * Creates a new Scene with the transferred scene range.
     */
    Scene(float scene_range);

    /**
     * Destructor.
     */
    ~Scene();

    /**
     * Interprets the transferred xml_message and sets all source attributes
     * to the requested parameters.
     *
     * @param   xml_message             The XML message that shall be
     *                                  interpreted.
     */
    void interpret_xml_message(std::string xml_message);

    /**
     * Changes the current selected source to the source with the transferred
     * id and returns if the selection was successful.
     *
     * @param           id              The id of the source that shall be
     *                                  selected.
     *
     * @return          true if the selection was successful, false otherwise.
     */
    bool select_source(const int id);

    /**
     * Creates a vector with the sources ids and names and
     * returns it.
     *
     * @return the sources ids and names.
     */
    std::shared_ptr< std::vector< std::pair<unsigned int, std::string> > > get_source_ids_and_names();

    /**
     * Returns the current selected source.
     *
     * @return the current selected source.
     */
    SSR::Source get_source() const;

    /**
     * Creates a new source with the transferred name. The ID will automatically
     * be computed and assigned.
     *
     * After creating the new source, the new source will be the current selected
     * source.
     *
     * The ID of the source will be returned.
     *
     * @see get_next_id()
     *
     * @param           name            The name of the source that shall be
     *                                  created.
     *
     * @return          The ID of the new created source.
     */
    unsigned int new_source(const std::string name);

    /**
     * Creates a new source with the transferred name and id.
     *
     * If the id already exists, the source will not be created and the method
     * will return false.
     *
     * If the id is available, the source will be created and also selected
     * as the current source.
     *
     * @param           name            The name of the source that shall be
     *                                  created.
     *
     * @param           id              The id of the source that shall be
     *                                  created.
     *
     * @return          True if the transferred id is available, otherwise
     *                  false.
     */
    bool new_source(const std::string name, const unsigned int id);

    /**
     * Creates a new source with the transferred name, id and jackport.
     *
     * If the id already exists, the source will not be created and the method
     * will return false.
     *
     * If the id is available, the source will be created and also selected
     * as the current source.
     *
     * @param           name            The name of the source that shall be
     *                                  created.
     *
     * @param           id              The id of the source that shall be
     *                                  created.
     *
     * @param           jackport        The jackport of the source.
     *
     * @return          True if the transferred id is available, otherwise
     *                  false.
     */
    bool new_source(const std::string name, const unsigned int id, const std::string jackport);

    /**
     * Sets the id of the current selected source to the transferred id.
     *
     * @param           id              The id that the selected source
     *                                  shall be set to.
     */
    void set_id_of_selected_source(const int id);

    /**
     * Returns the ID of the current selected source.
     *
     * @return the ID of the current selected source.
     */
    int get_id_of_selected_source() const;

    /**
     * Sets the discrete X position of the current selected source to
     * the transferred position.
     *
     * @param           position        The new discrete X position the
     *                                  current selected source shall be
     *                                  set to.
     */
    void set_x_position_discrete_of_selected_source(const float position);

    /**
     * Sets the continuous X position of the current selected source to
     * the transferred position.
     *
     * @param           position        The new continuous X position the
     *                                  current selected source shall be
     *                                  set to.
     */
    void set_x_position_continuous_of_selected_source(const float position);

    /**
     * Returns the X position of the current selected source.
     *
     * @return the X position of the current selected source.
     */
    SSR::Parameter<float, float> get_x_position_of_selected_source() const;

    /**
     * Sets the discrete Y position of the current selected source to
     * the transferred position.
     *
     * @param           position        The new discrete Y position the
     *                                  current selected source shall be
     *                                  set to.
     */
    void set_y_position_discrete_of_selected_source(const float position);

    /**
     * Sets the continuous Y position of the current selected source to
     * the transferred position.
     *
     * @param           position        The new continuous Y position the
     *                                  current selected source shall be
     *                                  set to.
     */
    void set_y_position_continuous_of_selected_source(const float position);

    /**
     * Returns the Y position of the current selected source.
     *
     * @return the Y position of the current selected source.
     */
    SSR::Parameter<float, float> get_y_position_of_selected_source() const;

    /**
     * Sets the discrete gain value of the current selected source to the
     * transferred gain. The additional transferred linear value determines
     * whether the gain value is linear (true) or not (false).
     *
     * @param           gain            The new discrete gain the current
     *                                  selected source shall be set to.
     *
     * @param           linear          Determines if the transferred gain
     *                                  value is linear (true) or not (false).
     */
    void set_gain_discrete_of_selected_source(const float gain, const bool linear);

    /**
     * Sets the continuous gain value of the current selected source to the
     * transferred gain.
     *
     * @param           gain            The new continuous gain the current
     *                                  selected source shall be set to.
     */
    void set_gain_continuous_of_selected_source(const float gain);

    /**
     * Returns the gain of the current selected source.
     *
     * @return the gain of the current selected source.
     */
    SSR::Parameter<float, float> get_gain_of_selected_source() const;

    /**
     * Sets the discrete orientation of the current selected source to the
     * transferred orientation value.
     *
     * @param           orientation     The new orientation the current
     *                                  selected source shall be set to.
     */
    void set_orientation_discrete_of_selected_source(const float orientation);

    /**
     * Sets the continuous orientation of the current selected source to the
     * transferred orientation value.
     *
     * @param           orientation     The new orientation the current
     *                                  selected source shall be set to.
     */
    void set_orientation_continuous_of_selected_source(const float orientation);

    /**
     * Returns the orientation of the current selected source.
     *
     * @return the orientation of the current selected source.
     */
    SSR::Parameter<float, float> get_orientation_of_selected_source() const;

    /**
     * Sets the discrete mute value of the current selected source to the
     * transferred mute value.
     *
     * @param           mute            The new value the current selected
     *                                  source parameter mute shall be set to.
     */
    void set_mute_discrete_of_selected_source(const bool mute);

    /**
     * Sets the continuous mute value of the current selected source to the
     * transferred mute value.
     *
     * @param           mute            The new value the current selected
     *                                  source parameter mute shall be set to.
     */
    void set_mute_continuous_of_selected_source(const float mute);

    /**
     * Returns the mute parameter of the current selected source.
     *
     * @return the mute parameter of the current selected source.
     */
    SSR::Parameter<bool, float> get_mute_of_selected_source() const;

    /**
     * Sets the discrete source model of the current selected source where the
     * transferred parameter point determines whether it is a point source
     * (true) or a plane source (false).
     *
     * @param           point           Determines whether the source is point
     *                                  (true) or plane (false).
     */
    void set_model_point_discrete_of_selected_source(const bool point);

    /**
     * Sets the continuous source model of the current selected source where the
     * transferred parameter point determines whether it is a point source
     * (1.0) or a plane source (0.0).
     *
     * @param           point           Determines whether the source is point
     *                                  (1.0) or plane (0.0).
     */
    void set_model_point_continuous_of_selected_source(const float point);

    /**
     * Returns the source model of the current selected source.
     *
     * @return the source model of the current selected source.
     */
    SSR::Parameter<bool, float> get_model_point_of_selected_source() const;

    /**
     * Sets the discrete value of the current selected source where the
     * transferred parameter fixed determines whether the source is
     * fixed (true) or movable (false).
     *
     * @param           fixed           Determines whether the source shall
     *                                  be fixed (true) or movable (false).
     */
    void set_fixed_discrete_of_selected_source(const bool fixed);

    /**
     * Sets the continuous value of the current selected source where the
     * transferred parameter fixed determines whether the source is
     * fixed (1.0) or movable (0.0).
     *
     * @param           fixed           Determines whether the source shall
     *                                  be fixed (1.0) or movable (0.0).
     */
    void set_fixed_continuous_of_selected_source(const float fixed);

    /**
     * Returns the fixed parameter of the current selected source.
     *
     * @return the fixed parameter of the current selected source.
     */
    SSR::Parameter<bool, float> get_fixed_of_selected_source() const;

    /**
     * Sets the name of the current selected source to the transferred
     * parameter name.
     *
     * @param           name            The name the current selected source
     *                                  shall be set to.
     */
    void set_name_of_selected_source(const std::string name);

    /**
     * Returns the name of the current selected source.
     *
     * @return the name of the current selected source.
     */
    std::string get_name_of_selected_source() const;

    /**
     * Sets the properties file of the current selected source to the
     * transferred parameter prop_file.
     *
     * @param           prop_file       The properties file the current
     *                                  selected source shall be set to.
     */
    void set_properties_file_of_selected_source(const std::string prop_file);

    /**
     * Returns the properties file of the current selected source.
     *
     * @return the properties file of the current selected source.
     */
    std::string get_properties_file_of_selected_source() const;

    /**
     * Sets the jackport of the current selected source to the transferred
     * parameter jackport.
     *
     * @param           jackport        The jackport the current selected
     *                                  source shall be set to.
     */
    void set_jackport_of_selected_source(const std::string jackport);

    /**
     * Returns the jackport of the current selected source.
     *
     * @return the jackport of the current selected source.
     */
    std::string get_jackport_of_selected_source() const;

  private:

    /**
     * Type definition for the source iterator.
     */
    typedef std::vector<SSR::Source>::iterator source_iterator;

    /**
     * All sources related to this scene.
     */
    std::unique_ptr< std::vector<SSR::Source> > sources;

    /**
     *
     * The currently selected source.
     */
    source_iterator current_selected_source;

    /**
     * The scenes range.
     */
    float scene_range;

    /**
     * The IDs and names of all related sources of this scene.
     */
    std::shared_ptr< std::vector< std::pair<unsigned int, std::string> > > ids_and_names;

    /**
     * Checks whether the transferred id_to_check is already in use and returns
     * true if so - false otherwise.
     *
     * @param           id_to_check     The ID which shall be checked if it is
     *                                  already in use.
     *
     * @return true if the ID is already in use, false otherwise.
     */
    bool id_already_in_use(unsigned int id_to_check);

    /**
     * Computes and returns the next and not already in use ID.
     *
     * @return the next and not already in use ID
     */
    unsigned int get_next_id();

    /**
     * Returns the source iterator for the source having the transferred id.
     *
     * @param           id              The ID of the source which iterator
     *                                  shall be returned.
     *
     * @return the source iterator for the source having the transferred id.
     *
     * @throws          runtime_error   If no source has the transferred id,
     *                                  a runtime_error exception will be
     *                                  thrown.
     */
    const source_iterator get_iterator(unsigned int id);

    /**
     * Sets the name of the source with the transferred id to the transferred
     * parameter name.
     *
     * @param           id              The ID of the source which name shall
     *                                  be set to.
     *
     * @param           name            The name the source shall be set to.
     */
    void set_name_of_source(const unsigned int id, const std::string name);

    /**
     * Sets the id of the source which has the transferred old_id to the
     * transferred new_id.
     *
     * @param           old_id          The current id of the source which
     *                                  id shall be reset.
     *
     * @param           new_id          The new_id the source shall be set to.
     */
    void set_id_of_source(const unsigned int old_id, const unsigned int new_id);

    /**
     * Manipulates the transferred source_to_manipulate by interpreting the
     * transferred element (XML message).
     *
     * @param           source_to_manipulate    The source that shall be
     *                                          manipulated.
     *
     * @param           element                 The XML message that shall be
     *                                          interpreted.
     */
    void manipulate_source(source_iterator source_to_manipulate, juce::XmlElement* element);

  };

}

#endif
