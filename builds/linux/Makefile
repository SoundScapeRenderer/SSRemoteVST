DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.0.1" -D "JUCE_APP_VERSION_HEX=0x1" -I /usr/include -I /usr/include/freetype2 -I $(VST3_SDK) -I $(JUCE_LIB_CODE) -I $(SSREMOTE_VST)
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -fPIC -O0 -std=c++11
  CXXFLAGS += $(CFLAGS)
  # (-Wl --no-undefined) -> Checks if the linker has undefined references
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -shared -Wl,--no-undefined -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt -ljack -lboost_filesystem -lboost_system
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.0.1" -D "JUCE_APP_VERSION_HEX=0x1" -I /usr/include -I /usr/include/freetype2 -I $(VST3_SDK) -I $(JUCE_LIB_CODE) -I $(SSREMOTE_VST)
  TARGET := ssremote_vst.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.0.1" -D "JUCE_APP_VERSION_HEX=0x1" -I /usr/include -I /usr/include/freetype2 -I $(VST3_SDK) -I $(JUCE_LIB_CODE) -I $(SSREMOTE_VST)
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -fPIC -Os -std=c++11
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -shared -fvisibility=hidden -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt -ljack 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.0.1" -D "JUCE_APP_VERSION_HEX=0x1" -I /usr/include -I /usr/include/freetype2 -I $(VST3_SDK) -I $(JUCE_LIB_CODE) -I $(SSREMOTE_VST)
  TARGET := ssremote_vst.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
	$(OBJDIR)/clock.o \
	$(OBJDIR)/logger.o \
	$(OBJDIR)/random_machine.o \
	$(OBJDIR)/parameter_translation_functions.o \
	$(OBJDIR)/source.o \
	$(OBJDIR)/scene.o \
  $(OBJDIR)/scale_reference_gui_component.o \
  $(OBJDIR)/zoom_gui_component.o \
  $(OBJDIR)/update_specificator.o \
  $(OBJDIR)/head_frame_gui_component.o \
  $(OBJDIR)/source_frame_gui_component.o \
  $(OBJDIR)/ssr_colour.o \
  $(OBJDIR)/source_pad_and_controls_gui_component.o \
  $(OBJDIR)/gui_components_configurator.o \
  $(OBJDIR)/source_parameters_gui_component.o \
  $(OBJDIR)/source_gui_component.o \
  $(OBJDIR)/source_pad_gui_component.o \
  $(OBJDIR)/grid_gui_component.o \
  $(OBJDIR)/network_gui_component.o \
  $(OBJDIR)/network_config.o \
  $(OBJDIR)/config.o \
  $(OBJDIR)/debug.o \
  $(OBJDIR)/helper.o \
  $(OBJDIR)/jack_client.o \
  $(OBJDIR)/ssr_requester.o \
  $(OBJDIR)/tcp_connection.o \
  $(OBJDIR)/controller.o \
  $(OBJDIR)/main_gui_component.o \
  $(OBJDIR)/juce_audio_basics_2442e4ea.o \
  $(OBJDIR)/juce_audio_devices_a4c8a728.o \
  $(OBJDIR)/juce_audio_formats_d349f0c8.o \
  $(OBJDIR)/juce_audio_processors_44a134a2.o \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_cryptography_25c7e826.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \
  $(OBJDIR)/juce_gui_extra_7767d6a8.o \
  $(OBJDIR)/juce_opengl_c7e3506c.o \
  $(OBJDIR)/juce_PluginUtilities_e2e19a34.o \
  $(OBJDIR)/juce_VST_Wrapper_bb62e93d.o \
  $(OBJDIR)/juce_VST3_Wrapper_77e7c73b.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking SSRemoteVST
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning SSRemoteVST
	@$(CLEANCMD)

strip:
	@echo Stripping SSRemoteVST
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/clock.o: $(SSREMOTE_VST)/src/utils/clock.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling clock.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/logger.o: $(SSREMOTE_VST)/src/utils/logger.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling logger.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/random_machine.o: $(SSREMOTE_VST)/src/utils/random_machine.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling random_machine.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/parameter_translation_functions.o: $(SSREMOTE_VST)/src/scene/parameter_translation_functions.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling parameter_translation_functions.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/source.o: $(SSREMOTE_VST)/src/scene/source.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling source.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/scene.o: $(SSREMOTE_VST)/src/scene/scene.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling scene.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/scale_reference_gui_component.o: $(SSREMOTE_VST)/src/GUI/source_frame/source_pad/scale_reference_gui_component.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling scale_reference_gui_component.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/zoom_gui_component.o: $(SSREMOTE_VST)/src/GUI/source_frame/source_pad/zoom_gui_component.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling zoom_gui_component.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/update_specificator.o: $(SSREMOTE_VST)/src/utils/update_specificator.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling update_specificator.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/head_frame_gui_component.o: $(SSREMOTE_VST)/src/GUI/head_frame/head_frame_gui_component.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling head_frame_gui_component.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/source_frame_gui_component.o: $(SSREMOTE_VST)/src/GUI/source_frame/source_frame_gui_component.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling source_frame_gui_component.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	
$(OBJDIR)/ssr_colour.o: $(SSREMOTE_VST)/src/config/ssr_colour.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ssr_colour.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	
$(OBJDIR)/source_pad_and_controls_gui_component.o: $(SSREMOTE_VST)/src/GUI/source_frame/source_pad/source_pad_and_controls_gui_component.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling source_pad_and_controls_gui_component.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	
$(OBJDIR)/gui_components_configurator.o: $(SSREMOTE_VST)/src/GUI/gui_components_configurator.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling gui_components_configurator.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	
$(OBJDIR)/source_parameters_gui_component.o: $(SSREMOTE_VST)/src/GUI/source_frame/source_parameters/source_parameters_gui_component.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling source_parameters_gui_component.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	
$(OBJDIR)/source_gui_component.o: $(SSREMOTE_VST)/src/GUI/source_frame/source_pad/source_gui_component.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling source_gui_component.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"
		
$(OBJDIR)/source_pad_gui_component.o: $(SSREMOTE_VST)/src/GUI/source_frame/source_pad/source_pad_gui_component.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling source_pad_gui_component.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	
$(OBJDIR)/grid_gui_component.o: $(SSREMOTE_VST)/src/GUI/source_frame/source_pad/grid_gui_component.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling grid_gui_component.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	
$(OBJDIR)/network_gui_component.o: $(SSREMOTE_VST)/src/GUI/head_frame/network_gui_component.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling network_gui_component.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/network_config.o: $(SSREMOTE_VST)/src/config/network_config.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling network_config.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/config.o: $(SSREMOTE_VST)/src/config/config.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling config.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	
$(OBJDIR)/debug.o: $(SSREMOTE_VST)/src/utils/debug.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling debug.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/helper.o: $(SSREMOTE_VST)/src/utils/helper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling helper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/jack_client.o: $(SSREMOTE_VST)/src/utils/jack_client.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling jack_client.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ssr_requester.o: $(SSREMOTE_VST)/src/utils/ssr_requester.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ssr_requester.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/tcp_connection.o: $(SSREMOTE_VST)/src/utils/tcp_connection.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling tcp_connection.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/controller.o: $(SSREMOTE_VST)/src/controller.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling controller.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/main_gui_component.o: $(SSREMOTE_VST)/src/GUI/main_gui_component.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling main_gui_component.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_2442e4ea.o: $(JUCE_LIB_CODE)/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_a4c8a728.o: $(JUCE_LIB_CODE)/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_d349f0c8.o: $(JUCE_LIB_CODE)/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_44a134a2.o: $(JUCE_LIB_CODE)/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: $(JUCE_LIB_CODE)/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_cryptography_25c7e826.o: $(JUCE_LIB_CODE)/modules/juce_cryptography/juce_cryptography.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_bdd6d488.o: $(JUCE_LIB_CODE)/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_79b2840.o: $(JUCE_LIB_CODE)/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_c8f1e7a4.o: $(JUCE_LIB_CODE)/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_a630dd20.o: $(JUCE_LIB_CODE)/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_7767d6a8.o: $(JUCE_LIB_CODE)/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_opengl_c7e3506c.o: $(JUCE_LIB_CODE)/modules/juce_opengl/juce_opengl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_PluginUtilities_e2e19a34.o: $(JUCE_LIB_CODE)/modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_PluginUtilities.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST_Wrapper_bb62e93d.o: $(JUCE_LIB_CODE)/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST3_Wrapper_77e7c73b.o: $(JUCE_LIB_CODE)/modules/juce_audio_plugin_client/VST3/juce_VST3_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST3_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
