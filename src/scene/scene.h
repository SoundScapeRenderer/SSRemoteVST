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
   * @author Florian Willich
   */
  class Scene
  {

  public:

    /**
     * Creates a new Scene with a scene range of 2000.
     */
    Scene();

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
     *
     * @author Florian Willich
     */
    std::shared_ptr< std::vector< std::pair<unsigned int, std::string> > > get_source_ids_and_names();

    /**
     * Returns the current selected source.
     *
     * @return the current selected source.
     *
     * @author Florian Willich
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
     *
     * @author Florian Willich
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
     *
     * @author Florian Willich
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
     *
     * @author Florian Willich
     */
    bool new_source(const std::string name, const unsigned int id, const std::string jackport);

    /**
     * Sets the id of the current selected source to the transferred id.
     *
     * @param           id              The id that the selected source
     *                                  shall be set to.
     *
     * @author Florian Willich
     */
    void set_id_of_selected_source(const int id);

    /**
     * Returns the ID of the current selected source.
     *
     * @return the ID of the current selected source.
     *
     * @author Florian Willich
     */
    int get_id_of_selected_source() const;

    /**
     * Sets the absolute X position of the current selected source to the
     * new_position.
     *
     * @param           new_position    The new X position that the current
     *                                  selected source shall be set to.
     *
     * @author Florian Willich
     */
    void set_x_position_absolute_of_selected_source(const float new_position);

    void set_x_position_relative_of_selected_source(const float new_position);

    SSR::Parameter<float, float> get_x_position_of_selected_source() const;

    void set_y_position_absolute_of_selected_source(const float new_position);

    void set_y_position_relative_of_selected_source(const float new_position);

    SSR::Parameter<float, float> get_y_position_of_selected_source() const;

    void set_gain_absolute_of_selected_source(const float value, const bool linear);

    void set_gain_relative_of_selected_source(const float new_gain);

    SSR::Parameter<float, float> get_gain_of_selected_source() const;

    void set_orientation_absolute_of_selected_source(const float value);

    void set_orientation_relative_of_selected_source(const float value);

    SSR::Parameter<float, float> get_orientation_of_selected_source() const;

    void set_mute_absolute_of_selected_source(const bool value);

    void set_mute_relative_of_selected_source(const float value);

    SSR::Parameter<bool, float> get_mute_of_selected_source() const;

    void set_model_point_absolute_of_selected_source(const bool value);

    void set_model_point_relative_of_selected_source(const float value);

    SSR::Parameter<bool, float> get_model_point_of_selected_source() const;

    void set_fixed_absolute_of_selected_source(const bool value);

    void set_fixed_relative_of_selected_source(const float value);

    SSR::Parameter<bool, float> get_fixed_of_selected_source() const;

    void set_name_of_selected_source(const std::string value);

    std::string get_name_of_selected_source() const;

    void set_properties_file_of_selected_source(const std::string value);

    std::string get_properties_file_of_selected_source() const;

    void set_jackport_of_selected_source(const std::string value);

    std::string get_jackport_of_selected_source() const;

  private:
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
    double scene_range;

    std::shared_ptr< std::vector< std::pair<unsigned int, std::string> > > ids_and_names;

    bool id_already_in_use(unsigned int id_to_check);

    unsigned int get_next_id();

    const source_iterator get_iterator(unsigned int id);

    void set_name_of_source(const unsigned int id, const std::string name);

    void set_id_of_source(const unsigned int id, const unsigned int new_id);

    void manipulate_source(source_iterator source_to_manipulate, juce::XmlElement* element);

  };

}

#endif
