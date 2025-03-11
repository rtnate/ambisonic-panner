#add_subdirectory(Audio)
#add_subdirectory(GUI)

set(AUDIO_SOURCE_FILES 
    ${CMAKE_CURRENT_LIST_DIR}/Audio/PanModulator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Audio/PluginProcessor.cpp)
set(AUDIO_HEADER_FILES 
    ${CMAKE_CURRENT_LIST_DIR}/Audio/PluginProcessor.h
    ${CMAKE_CURRENT_LIST_DIR}/Audio/LFO.h
    ${CMAKE_CURRENT_LIST_DIR}/Audio/PanParameters.h
    ${CMAKE_CURRENT_LIST_DIR}/Audio/PanModulator.h)
set(GUI_SOURCE_FILES 
    ${CMAKE_CURRENT_LIST_DIR}/GUI/PluginEditor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GUI/BasicModGroup.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GUI/MainPannerComponent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GUI/AutoPanComponent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GUI/LFOControlComponent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Audio/PanParameters.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GUI/ChannelMeterComponent.cpp
    ${CMAKE_CURRENT_LIST_DIR}/GUI/Panner3DGroup.cpp)
set(GUI_HEADER_FILES 
    ${CMAKE_CURRENT_LIST_DIR}/GUI/PluginEditor.h
    ${CMAKE_CURRENT_LIST_DIR}/GUI/BasicModGroup.h
    ${CMAKE_CURRENT_LIST_DIR}/GUI/MainPannerComponent.h
    ${CMAKE_CURRENT_LIST_DIR}/GUI/AutoPanComponent.h
    ${CMAKE_CURRENT_LIST_DIR}/GUI/LFOControlComponent.h
    ${CMAKE_CURRENT_LIST_DIR}/GUI/ChannelMeterComponent.h
    ${CMAKE_CURRENT_LIST_DIR}/GUI/Panner3DGroup.h)

set(SOURCE_LIST 
    ${AUDIO_SOURCE_FILES}
    ${AUDIO_HEADER_FILES}
    ${GUI_SOURCE_FILES}
    ${GUI_HEADER_FILES})

set(PANNER_SOURCES ${SOURCE_LIST} PARENT_SCOPE)
