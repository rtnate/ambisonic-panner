SET(SRC_FILES
	../Source/AirAbsorbtionFilter.cpp
	../Source/AirAbsorbtionFilter.h
	../Source/AmbiOSCSender.cpp
	../Source/AmbiOSCSender.h
	../Source/AmbiOSCSenderExt.cpp
	../Source/AmbiOSCSenderExt.h
	../Source/AnimatorAction.h
	../Source/AnimatorActionComponent.cpp
	../Source/AnimatorActionComponent.h
	../Source/AnimatorComponent.cpp
	../Source/AnimatorComponent.h
	../Source/AnimatorDataset.h
	../Source/AnimatorDialog.h
	../Source/AnimatorDialogManager.h
	../Source/AnimatorMovement.h
	../Source/AnimatorMovementComponent.cpp
	../Source/AnimatorMovementComponent.h
	../Source/AnimatorPresetHelper.h
	../Source/ComponentArguments.h
	../Source/CustomOscBase.cpp
	../Source/CustomOscBase.h
	../Source/CustomOscInput.cpp
	../Source/CustomOscInput.h
	../Source/CustomOscInputTableListModel.h
	../Source/CustomOscReceiver.cpp
	../Source/CustomOscReceiver.h
	../Source/CustomOscRxPresetHelper.h
	../Source/CustomOscTableListModel.h
	../Source/CustomOscTarget.cpp
	../Source/CustomOscTarget.h
	../Source/CustomOscTxPresetHelper.h
	../Source/DistanceEncodingComponent.cpp
	../Source/DistanceEncodingComponent.h
	../Source/DistanceEncodingGraph.cpp
	../Source/DistanceEncodingGraph.h
	../Source/DistanceEncodingParams.h
	../Source/DistanceEncodingPresetHelper.h
	../Source/EncoderPresetHelper.h
	../Source/EncoderSettings.cpp
	../Source/EncoderSettings.h
	../Source/EncoderSettingsComponent.cpp
	../Source/EncoderSettingsComponent.h
	../Source/EncoderSettingsDialog.h
	../Source/EncodingSettingsComponent.cpp
	../Source/EncodingSettingsComponent.h
	../Source/GroupAnimator.cpp
	../Source/GroupAnimator.h
	../Source/GroupTableListModel.h
	../Source/OSCHandlerEncoder.cpp
	../Source/OSCHandlerEncoder.h
	../Source/OSCRxSettingsComponent.cpp
	../Source/OSCRxSettingsComponent.h
	../Source/OSCSenderInstance.cpp
	../Source/OSCSenderInstance.h
	../Source/OSCSettingsComponent.cpp
	../Source/OSCSettingsComponent.h
	../Source/OSCTargetsComponent.cpp
	../Source/OSCTargetsComponent.h
	../Source/PluginEditor.cpp
	../Source/PluginEditor.h
	../Source/PluginProcessor.cpp
	../Source/PluginProcessor.h
	../Source/RadarSettingsComponent.cpp
	../Source/RadarSettingsComponent.h
	../Source/SourceDefinitionComponent.cpp
	../Source/SourceDefinitionComponent.h
	../Source/SourceTableListModel.h
	../Source/StandardOscTarget.cpp
	../Source/StandardOscTarget.h
	../Source/UserDefinedParameter.cpp
	../Source/UserDefinedParameter.h
    
	../../Common/ActivationDialog.h
	../../Common/AdditionalWindow.h
	../../Common/AmbiDataSet.cpp
	../../Common/AmbiDataSet.h
	../../Common/AmbiGroup.cpp
	../../Common/AmbiGroup.h
	../../Common/AmbiLookAndFeel.cpp
	../../Common/AmbiLookAndFeel.h
	../../Common/AmbiPoint.cpp
	../../Common/AmbiPoint.h
	../../Common/AmbiSettings.cpp
	../../Common/AmbiSettings.h
	../../Common/AmbiSettingsCollection.cpp
	../../Common/AmbiSettingsCollection.h
	../../Common/AmbiSettingsSection.cpp
	../../Common/AmbiSettingsSection.h
	../../Common/AmbiSource.cpp
	../../Common/AmbiSource.h
	../../Common/AmbiSourceSet.cpp
	../../Common/AmbiSourceSet.h
	../../Common/AmbiSpeaker.cpp
	../../Common/AmbiSpeaker.h
	../../Common/AmbiSpeakerSet.cpp
	../../Common/AmbiSpeakerSet.h
	../../Common/AudioParameterBoolAmbi.cpp
	../../Common/AudioParameterBoolAmbi.h
	../../Common/AudioParameterBoolAmbiAbs.h
	../../Common/AudioParameterFloatAmbi.cpp
	../../Common/AudioParameterFloatAmbi.h
	../../Common/AudioParameterFloatAmbiAbs.h
	../../Common/AudioParameterSet.h
	../../Common/AudioParams.h
	../../Common/BuildInfo.h
	../../Common/ChannelLayout.cpp
	../../Common/ChannelLayout.h
	../../Common/CheckBoxCustomComponent.h
	../../Common/ColorDefinition.h
	../../Common/ColorEditorCustomComponent.h
	../../Common/ColorSelectionComponent.h
	../../Common/CommonImages.cpp
	../../Common/CommonImages.h
	../../Common/Constants.cpp
	../../Common/Constants.h
	../../Common/CsvImportExport.h
	../../Common/DawParameter.h
	../../Common/DelayBuffer.cpp
	../../Common/DelayBuffer.h
	../../Common/DelayHelper.cpp
	../../Common/DelayHelper.h
	../../Common/EditableCodeCustomComponent.h
	../../Common/EditableTextCustomComponent.h
	../../Common/EnablementCallback.h
	../../Common/EncoderConstants.cpp
	../../Common/EncoderConstants.h
	../../Common/ExternalImportExport.h
	../../Common/FFTAnalyzer.cpp
	../../Common/FFTAnalyzer.h
	../../Common/FilterBankInfo.h
	../../Common/FilterControlCallback.h
	../../Common/FilterInfo.h
	../../Common/GroupPointsSelectionComponent.h
	../../Common/HelpComponent.cpp
	../../Common/HelpComponent.h
	../../Common/HelpDialog.h
	../../Common/HelpDialogManager.h
	../../Common/HelpOscSyntax.cpp
	../../Common/HelpOscSyntax.h
	../../Common/HelpRadarInteraction.cpp
	../../Common/HelpRadarInteraction.h
	../../Common/HelpWebBrowserComponent.cpp
	../../Common/HelpWebBrowserComponent.h
	../../Common/ImportExport.h
	../../Common/JsEditorComponent.cpp
	../../Common/JsEditorComponent.h
	../../Common/LabelCreator.cpp
	../../Common/LabelCreator.h
	../../Common/MathHelper.cpp
	../../Common/MathHelper.h
	../../Common/MultiActivationDialog.h
	../../Common/MultiDecoderColors.h
	../../Common/MultiSliderControl.cpp
	../../Common/MultiSliderControl.h
	../../Common/NumericColumnCustomComponent.h
	../../Common/OSCHandler.cpp
	../../Common/OSCHandler.h
	../../Common/OSCLogComponent.cpp
	../../Common/OSCLogComponent.h
	../../Common/OSCLogDialog.h
	../../Common/OSCLogDialogManager.h
	../../Common/Point3D.h
	../../Common/PointInfoControl.cpp
	../../Common/PointInfoControl.h
	../../Common/PointSelection.cpp
	../../Common/PointSelection.h
	../../Common/PresetComparators.h
	../../Common/PresetHelper.cpp
	../../Common/PresetHelper.h
	../../Common/PresetManagerComponent.cpp
	../../Common/PresetManagerComponent.h
	../../Common/PresetManagerDialog.h
	../../Common/PresetTableModel.h
	../../Common/Radar2D.cpp
	../../Common/Radar2D.h
	../../Common/Radar3D.cpp
	../../Common/Radar3D.h
	../../Common/RadarColors.h
	../../Common/RadarComponent.cpp
	../../Common/RadarComponent.h
	../../Common/RadarOptions.cpp
	../../Common/RadarOptions.h
	../../Common/ScalingInfo.cpp
	../../Common/ScalingInfo.h
	../../Common/SimpleGraph.cpp
	../../Common/SimpleGraph.h
	../../Common/SliderColumnCustomComponent.h
	../../Common/SliderRange.h
	../../Common/SoloMuteCallback.h
	../../Common/SoloMuteCustomComponent.h
	../../Common/SpeakerSelectionComponent.h
	../../Common/StatusMessage.h
	../../Common/StatusMessageHandler.cpp
	../../Common/StatusMessageHandler.h
	../../Common/StatusMessageReceiver.h
	../../Common/TableColumnCallback.h
	../../Common/TestSoundGenerator.cpp
	../../Common/TestSoundGenerator.h
	../../Common/TrackColors.h
	../../Common/TrackColorSelector.h
	../../Common/TreeViewItemHelp.h
	../../Common/VarDelayBuffer.cpp
	../../Common/VarDelayBuffer.h
	../../Common/ZoomSettings.cpp
	../../Common/ZoomSettings.h
)

add_subdirectory(Solo)
add_subdirectory(Multi)