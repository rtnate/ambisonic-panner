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
	PLUGIN_NAME "AmbisonicPanner"
	BUNDLE_ID "com.rtelectronix.ambisonic_panner"
    PRODUCT_NAME "AmbisonicPanner"
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
    rtdsp
    )
    
set_target_properties(${PANNER_TARGET_NAME}
    ${COMMON_OUTPUT_DIRECTORY}
    )


#Common Sources 

set(COMMON_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../Common)

set(PANNER_COMMON_SOURCES 
    ${COMMON_SOURCE_DIR}/ActivationDialog.h
	${COMMON_SOURCE_DIR}/AdditionalWindow.h
	${COMMON_SOURCE_DIR}/AmbiDataSet.cpp
	${COMMON_SOURCE_DIR}/AmbiDataSet.h
	${COMMON_SOURCE_DIR}/AmbiGroup.cpp
	${COMMON_SOURCE_DIR}/AmbiGroup.h
	${COMMON_SOURCE_DIR}/AmbiLookAndFeel.cpp
	${COMMON_SOURCE_DIR}/AmbiLookAndFeel.h
	${COMMON_SOURCE_DIR}/AmbiPoint.cpp
	${COMMON_SOURCE_DIR}/AmbiPoint.h
	${COMMON_SOURCE_DIR}/AmbiSettings.cpp
	${COMMON_SOURCE_DIR}/AmbiSettings.h
	${COMMON_SOURCE_DIR}/AmbiSettingsCollection.cpp
	${COMMON_SOURCE_DIR}/AmbiSettingsCollection.h
	${COMMON_SOURCE_DIR}/AmbiSettingsSection.cpp
	${COMMON_SOURCE_DIR}/AmbiSettingsSection.h
	${COMMON_SOURCE_DIR}/AmbiSource.cpp
	${COMMON_SOURCE_DIR}/AmbiSource.h
	${COMMON_SOURCE_DIR}/AmbiSourceSet.cpp
	${COMMON_SOURCE_DIR}/AmbiSourceSet.h
	${COMMON_SOURCE_DIR}/AmbiSpeaker.cpp
	${COMMON_SOURCE_DIR}/AmbiSpeaker.h
	${COMMON_SOURCE_DIR}/AmbiSpeakerSet.cpp
	${COMMON_SOURCE_DIR}/AmbiSpeakerSet.h
	${COMMON_SOURCE_DIR}/AudioParameterBoolAmbi.cpp
	${COMMON_SOURCE_DIR}/AudioParameterBoolAmbi.h
	${COMMON_SOURCE_DIR}/AudioParameterBoolAmbiAbs.h
	${COMMON_SOURCE_DIR}/AudioParameterFloatAmbi.cpp
	${COMMON_SOURCE_DIR}/AudioParameterFloatAmbi.h
	${COMMON_SOURCE_DIR}/AudioParameterFloatAmbiAbs.h
	${COMMON_SOURCE_DIR}/AudioParameterSet.h
	${COMMON_SOURCE_DIR}/AudioParams.h
	${COMMON_SOURCE_DIR}/BuildInfo.h
	${COMMON_SOURCE_DIR}/ChannelLayout.cpp
	${COMMON_SOURCE_DIR}/ChannelLayout.h
	${COMMON_SOURCE_DIR}/CheckBoxCustomComponent.h
	${COMMON_SOURCE_DIR}/ColorDefinition.h
	${COMMON_SOURCE_DIR}/ColorEditorCustomComponent.h
	${COMMON_SOURCE_DIR}/ColorSelectionComponent.h
	${COMMON_SOURCE_DIR}/CommonImages.cpp
	${COMMON_SOURCE_DIR}/CommonImages.h
	${COMMON_SOURCE_DIR}/Constants.cpp
	${COMMON_SOURCE_DIR}/Constants.h
	${COMMON_SOURCE_DIR}/CsvImportExport.h
	${COMMON_SOURCE_DIR}/DawParameter.h
	${COMMON_SOURCE_DIR}/DelayBuffer.cpp
	${COMMON_SOURCE_DIR}/DelayBuffer.h
	${COMMON_SOURCE_DIR}/DelayHelper.cpp
	${COMMON_SOURCE_DIR}/DelayHelper.h
	${COMMON_SOURCE_DIR}/EditableCodeCustomComponent.h
	${COMMON_SOURCE_DIR}/EditableTextCustomComponent.h
	${COMMON_SOURCE_DIR}/EnablementCallback.h
	${COMMON_SOURCE_DIR}/EncoderConstants.cpp
	${COMMON_SOURCE_DIR}/EncoderConstants.h
	${COMMON_SOURCE_DIR}/ExternalImportExport.h
	${COMMON_SOURCE_DIR}/FFTAnalyzer.cpp
	${COMMON_SOURCE_DIR}/FFTAnalyzer.h
	${COMMON_SOURCE_DIR}/FilterBankInfo.h
	${COMMON_SOURCE_DIR}/FilterControlCallback.h
	${COMMON_SOURCE_DIR}/FilterInfo.h
	${COMMON_SOURCE_DIR}/GroupPointsSelectionComponent.h
	${COMMON_SOURCE_DIR}/HelpComponent.cpp
	${COMMON_SOURCE_DIR}/HelpComponent.h
	${COMMON_SOURCE_DIR}/HelpDialog.h
	${COMMON_SOURCE_DIR}/HelpDialogManager.h
	${COMMON_SOURCE_DIR}/HelpOscSyntax.cpp
	${COMMON_SOURCE_DIR}/HelpOscSyntax.h
	${COMMON_SOURCE_DIR}/HelpRadarInteraction.cpp
	${COMMON_SOURCE_DIR}/HelpRadarInteraction.h
	${COMMON_SOURCE_DIR}/HelpWebBrowserComponent.cpp
	${COMMON_SOURCE_DIR}/HelpWebBrowserComponent.h
	${COMMON_SOURCE_DIR}/ImportExport.h
	${COMMON_SOURCE_DIR}/JsEditorComponent.cpp
	${COMMON_SOURCE_DIR}/JsEditorComponent.h
	${COMMON_SOURCE_DIR}/LabelCreator.cpp
	${COMMON_SOURCE_DIR}/LabelCreator.h
	${COMMON_SOURCE_DIR}/MathHelper.cpp
	${COMMON_SOURCE_DIR}/MathHelper.h
	${COMMON_SOURCE_DIR}/MultiActivationDialog.h
	${COMMON_SOURCE_DIR}/MultiDecoderColors.h
	${COMMON_SOURCE_DIR}/MultiSliderControl.cpp
	${COMMON_SOURCE_DIR}/MultiSliderControl.h
	${COMMON_SOURCE_DIR}/NumericColumnCustomComponent.h
	${COMMON_SOURCE_DIR}/OSCHandler.cpp
	${COMMON_SOURCE_DIR}/OSCHandler.h
	${COMMON_SOURCE_DIR}/OSCLogComponent.cpp
	${COMMON_SOURCE_DIR}/OSCLogComponent.h
	${COMMON_SOURCE_DIR}/OSCLogDialog.h
	${COMMON_SOURCE_DIR}/OSCLogDialogManager.h
	${COMMON_SOURCE_DIR}/Point3D.h
	${COMMON_SOURCE_DIR}/PointInfoControl.cpp
	${COMMON_SOURCE_DIR}/PointInfoControl.h
	${COMMON_SOURCE_DIR}/PointSelection.cpp
	${COMMON_SOURCE_DIR}/PointSelection.h
	${COMMON_SOURCE_DIR}/PresetComparators.h
	${COMMON_SOURCE_DIR}/PresetHelper.cpp
	${COMMON_SOURCE_DIR}/PresetHelper.h
	${COMMON_SOURCE_DIR}/PresetManagerComponent.cpp
	${COMMON_SOURCE_DIR}/PresetManagerComponent.h
	${COMMON_SOURCE_DIR}/PresetManagerDialog.h
	${COMMON_SOURCE_DIR}/PresetTableModel.h
	${COMMON_SOURCE_DIR}/Radar2D.cpp
	${COMMON_SOURCE_DIR}/Radar2D.h
	${COMMON_SOURCE_DIR}/Radar3D.cpp
	${COMMON_SOURCE_DIR}/Radar3D.h
	${COMMON_SOURCE_DIR}/RadarColors.h
	${COMMON_SOURCE_DIR}/RadarComponent.cpp
	${COMMON_SOURCE_DIR}/RadarComponent.h
	${COMMON_SOURCE_DIR}/RadarOptions.cpp
	${COMMON_SOURCE_DIR}/RadarOptions.h
	${COMMON_SOURCE_DIR}/ScalingInfo.cpp
	${COMMON_SOURCE_DIR}/ScalingInfo.h
	${COMMON_SOURCE_DIR}/SimpleGraph.cpp
	${COMMON_SOURCE_DIR}/SimpleGraph.h
	${COMMON_SOURCE_DIR}/SliderColumnCustomComponent.h
	${COMMON_SOURCE_DIR}/SliderRange.h
	${COMMON_SOURCE_DIR}/SoloMuteCallback.h
	${COMMON_SOURCE_DIR}/SoloMuteCustomComponent.h
	${COMMON_SOURCE_DIR}/SpeakerSelectionComponent.h
	${COMMON_SOURCE_DIR}/StatusMessage.h
	${COMMON_SOURCE_DIR}/StatusMessageHandler.cpp
	${COMMON_SOURCE_DIR}/StatusMessageHandler.h
	${COMMON_SOURCE_DIR}/StatusMessageReceiver.h
	${COMMON_SOURCE_DIR}/TableColumnCallback.h
	${COMMON_SOURCE_DIR}/TestSoundGenerator.cpp
	${COMMON_SOURCE_DIR}/TestSoundGenerator.h
	${COMMON_SOURCE_DIR}/TrackColors.h
	${COMMON_SOURCE_DIR}/TrackColorSelector.h
	${COMMON_SOURCE_DIR}/TreeViewItemHelp.h
	${COMMON_SOURCE_DIR}/VarDelayBuffer.cpp
	${COMMON_SOURCE_DIR}/VarDelayBuffer.h
	${COMMON_SOURCE_DIR}/ZoomSettings.cpp
	${COMMON_SOURCE_DIR}/ZoomSettings.h
)

set(DECODER_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../Decoder/Source)

set(PANNER_DECODER_SOURCES 
    ${DECODER_SOURCE_DIR}/AmbiSettingsComponent.cpp
    ${DECODER_SOURCE_DIR}/AmbiSettingsComponent.h
	${DECODER_SOURCE_DIR}/CheckBoxFilterCustomComponent.h
	${DECODER_SOURCE_DIR}/DecoderSectionControlComponent.cpp
	${DECODER_SOURCE_DIR}/DecoderSectionControlComponent.h
	${DECODER_SOURCE_DIR}/DecoderSettings.cpp
	${DECODER_SOURCE_DIR}/DecoderSettings.h
	${DECODER_SOURCE_DIR}/DecodingPresetHelper.h
	${DECODER_SOURCE_DIR}/FilterPresetHelper.h
	${DECODER_SOURCE_DIR}/FilterSettingsComponent.cpp
	${DECODER_SOURCE_DIR}/FilterSettingsComponent.h
	${DECODER_SOURCE_DIR}/IIRFilterGraph.cpp
	${DECODER_SOURCE_DIR}/IIRFilterGraph.h
	${DECODER_SOURCE_DIR}/MultiDecoderComponent.cpp
	${DECODER_SOURCE_DIR}/MultiDecoderComponent.h
	${DECODER_SOURCE_DIR}/OSCHandlerDecoder.cpp
	${DECODER_SOURCE_DIR}/OSCHandlerDecoder.h
	${DECODER_SOURCE_DIR}/PluginEditor.cpp
	${DECODER_SOURCE_DIR}/PluginEditor.h
	${DECODER_SOURCE_DIR}/PluginProcessor.cpp
	${DECODER_SOURCE_DIR}/PluginProcessor.h
	${DECODER_SOURCE_DIR}/ScalingComponent.cpp
	${DECODER_SOURCE_DIR}/ScalingComponent.h
	${DECODER_SOURCE_DIR}/SingleFilterSettingsComponent.cpp
	${DECODER_SOURCE_DIR}/SingleFilterSettingsComponent.h
	${DECODER_SOURCE_DIR}/SpeakerPresetHelper.h
	${DECODER_SOURCE_DIR}/SpeakerSettingsComponent.cpp
	${DECODER_SOURCE_DIR}/SpeakerSettingsComponent.h
	${DECODER_SOURCE_DIR}/SpeakerSettingsDialog.h
	${DECODER_SOURCE_DIR}/SpeakerTestCustomComponent.cpp
	${DECODER_SOURCE_DIR}/SpeakerTestCustomComponent.h	
)

set(ENCODER_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../Encoder/Source)

set(PANNER_ENCODER_SOURCES
    ${ENCODER_SOURCE_DIR}/AirAbsorbtionFilter.cpp
	${ENCODER_SOURCE_DIR}/AirAbsorbtionFilter.h
	${ENCODER_SOURCE_DIR}/AmbiOSCSender.cpp
	${ENCODER_SOURCE_DIR}/AmbiOSCSender.h
	${ENCODER_SOURCE_DIR}/AmbiOSCSenderExt.cpp
	${ENCODER_SOURCE_DIR}/AmbiOSCSenderExt.h
	${ENCODER_SOURCE_DIR}/AnimatorAction.h
	${ENCODER_SOURCE_DIR}/AnimatorActionComponent.cpp
	${ENCODER_SOURCE_DIR}/AnimatorActionComponent.h
	${ENCODER_SOURCE_DIR}/AnimatorComponent.cpp
	${ENCODER_SOURCE_DIR}/AnimatorComponent.h
	${ENCODER_SOURCE_DIR}/AnimatorDataset.h
	${ENCODER_SOURCE_DIR}/AnimatorDialog.h
	${ENCODER_SOURCE_DIR}/AnimatorDialogManager.h
	${ENCODER_SOURCE_DIR}/AnimatorMovement.h
	${ENCODER_SOURCE_DIR}/AnimatorMovementComponent.cpp
	${ENCODER_SOURCE_DIR}/AnimatorMovementComponent.h
	${ENCODER_SOURCE_DIR}/AnimatorPresetHelper.h
	${ENCODER_SOURCE_DIR}/ComponentArguments.h
	${ENCODER_SOURCE_DIR}/CustomOscBase.cpp
	${ENCODER_SOURCE_DIR}/CustomOscBase.h
	${ENCODER_SOURCE_DIR}/CustomOscInput.cpp
	${ENCODER_SOURCE_DIR}/CustomOscInput.h
	${ENCODER_SOURCE_DIR}/CustomOscInputTableListModel.h
	${ENCODER_SOURCE_DIR}/CustomOscReceiver.cpp
	${ENCODER_SOURCE_DIR}/CustomOscReceiver.h
	${ENCODER_SOURCE_DIR}/CustomOscRxPresetHelper.h
	${ENCODER_SOURCE_DIR}/CustomOscTableListModel.h
	${ENCODER_SOURCE_DIR}/CustomOscTarget.cpp
	${ENCODER_SOURCE_DIR}/CustomOscTarget.h
	${ENCODER_SOURCE_DIR}/CustomOscTxPresetHelper.h
	${ENCODER_SOURCE_DIR}/DistanceEncodingComponent.cpp
	${ENCODER_SOURCE_DIR}/DistanceEncodingComponent.h
	${ENCODER_SOURCE_DIR}/DistanceEncodingGraph.cpp
	${ENCODER_SOURCE_DIR}/DistanceEncodingGraph.h
	${ENCODER_SOURCE_DIR}/DistanceEncodingParams.h
	${ENCODER_SOURCE_DIR}/DistanceEncodingPresetHelper.h
	${ENCODER_SOURCE_DIR}/EncoderPresetHelper.h
	${ENCODER_SOURCE_DIR}/EncoderSettings.cpp
	${ENCODER_SOURCE_DIR}/EncoderSettings.h
	${ENCODER_SOURCE_DIR}/EncoderSettingsComponent.cpp
	${ENCODER_SOURCE_DIR}/EncoderSettingsComponent.h
	${ENCODER_SOURCE_DIR}/EncoderSettingsDialog.h
	${ENCODER_SOURCE_DIR}/EncodingSettingsComponent.cpp
	${ENCODER_SOURCE_DIR}/EncodingSettingsComponent.h
	${ENCODER_SOURCE_DIR}/GroupAnimator.cpp
	${ENCODER_SOURCE_DIR}/GroupAnimator.h
	${ENCODER_SOURCE_DIR}/GroupTableListModel.h
	${ENCODER_SOURCE_DIR}/OSCHandlerEncoder.cpp
	${ENCODER_SOURCE_DIR}/OSCHandlerEncoder.h
	${ENCODER_SOURCE_DIR}/OSCRxSettingsComponent.cpp
	${ENCODER_SOURCE_DIR}/OSCRxSettingsComponent.h
	${ENCODER_SOURCE_DIR}/OSCSenderInstance.cpp
	${ENCODER_SOURCE_DIR}/OSCSenderInstance.h
	${ENCODER_SOURCE_DIR}/OSCSettingsComponent.cpp
	${ENCODER_SOURCE_DIR}/OSCSettingsComponent.h
	${ENCODER_SOURCE_DIR}/OSCTargetsComponent.cpp
	${ENCODER_SOURCE_DIR}/OSCTargetsComponent.h
	${ENCODER_SOURCE_DIR}/PluginEditor.cpp
	${ENCODER_SOURCE_DIR}/PluginEditor.h
	${ENCODER_SOURCE_DIR}/PluginProcessor.cpp
	${ENCODER_SOURCE_DIR}/PluginProcessor.h
	${ENCODER_SOURCE_DIR}/RadarSettingsComponent.cpp
	${ENCODER_SOURCE_DIR}/RadarSettingsComponent.h
	${ENCODER_SOURCE_DIR}/SourceDefinitionComponent.cpp
	${ENCODER_SOURCE_DIR}/SourceDefinitionComponent.h
	${ENCODER_SOURCE_DIR}/SourceTableListModel.h
	${ENCODER_SOURCE_DIR}/StandardOscTarget.cpp
	${ENCODER_SOURCE_DIR}/StandardOscTarget.h
	${ENCODER_SOURCE_DIR}/UserDefinedParameter.cpp
	${ENCODER_SOURCE_DIR}/UserDefinedParameter.h
)

target_sources(${PANNER_TARGET_NAME} PRIVATE 
    ${PANNER_COMMON_SOURCES}
    ${PANNER_DECODER_SOURCES}
    ${PANNER_ENCODER_SOURCES})

source_group("Common" FILES ${PANNER_COMMON_SOURCES})
source_group("Decoder" FILES ${PANNER_DECODER_SOURCES})
source_group("Encoder" FILES ${PANNER_ENCODER_SOURCES})

