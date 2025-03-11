set(PANNER_TARGET_NAME AmbisonicPanner)

juce_add_plugin(${PANNER_TARGET_NAME}
    ${COMMON_PLUGIN_SETTINGS}

    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME "RT ElecTRonix"                          
	COMPANY_WEBSITE "https://www.rtelectronix.com"
	COMPANY_COPYRIGHT "© 2024"
    IS_SYNTH FALSE                       # Is this a synth or an effect?
    NEEDS_MIDI_INPUT FALSE               # Does the plugin need midi input?
    NEEDS_MIDI_OUTPUT FALSE              # Does the plugin need midi output?
    IS_MIDI_EFFECT FALSE                 # Is this plugin a MIDI effect?
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    # Does the editor need keyboard focus?
    # COPY_PLUGIN_AFTER_BUILD TRUE/FALSE        # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE "RTEX"               # A four-character manufacturer id with at least one upper-case character
    FORMATS Standalone AU VST3 LV2                # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    AU_MAIN_TYPE kAudioUnitType_Effect
    NEEDS_WEB_BROWSER TRUE
	PLUGIN_CODE "RTAP"                            # A unique four-character plugin id with exactly one upper-case character                                      # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
	PLUGIN_NAME "Ambisonic Panner"
	BUNDLE_ID "com.rtelectronix.ambisonic_panner"
    PRODUCT_NAME "Ambisonic Panner"
	DESCRIPTION "1st-7th Order Ambisonic Panner, Mono/Stereo Input"
	AU_EXPORT_PREFIX "AmbisonicPannerAU"
)

juce_generate_juce_header(${PANNER_TARGET_NAME})

add_subdirectory(Source)
target_sources(${PANNER_TARGET_NAME} PRIVATE ${PANNER_SOURCES})
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}\\Source" PREFIX "${PANNER_TARGET_NAME}" FILES ${PANNER_SOURCES})
#
set(RT_JUCE_GUI_DIR ${CMAKE_CURRENT_LIST_DIR}/../Libraries/RTJuceGUI/Source)
add_subdirectory(${RT_JUCE_GUI_DIR} RTJuceGUI/Source)
target_sources(${PANNER_TARGET_NAME} PRIVATE ${RT_JUCE_GUI_SOURCES})
source_group(TREE "${RT_JUCE_GUI_DIR}" PREFIX "RTJuceGUI" FILES ${RT_JUCE_GUI_SOURCES})

target_include_directories(${PANNER_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Source)
target_include_directories(${PANNER_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../)
target_include_directories(${PANNER_TARGET_NAME} PUBLIC ${RT_JUCE_GUI_DIR})
target_compile_definitions(${PANNER_TARGET_NAME}
    PUBLIC
    # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
    JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
    JUCE_VST3_CAN_REPLACE_VST2=0
	JUCE_MODAL_LOOPS_PERMITTED=1
	MAX_NUM_INPUT=2
    JUCE_SILENCE_XCODE_15_LINKER_WARNING=1
	)

target_link_libraries(${PANNER_TARGET_NAME}
    ${COMMON_LINK_LIBRARIES}
    )

target_link_libraries(${PANNER_TARGET_NAME}
    PRIVATE 
    AmbiEncoderSolo
    AmbiDecoder
    rtdsp
    )
    
set_target_properties(${PANNER_TARGET_NAME}
    ${COMMON_OUTPUT_DIRECTORY}
    )