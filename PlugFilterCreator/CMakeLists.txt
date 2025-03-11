


add_library(PlugFilterCreator_Helper INTERFACE)
target_compile_definitions(PlugFilterCreator_Helper INTERFACE
    -DJUCE_DONT_EMIT_CREATE_PLUGIN_FILTER=1)

#juce_add_binary_data(AmbiEncoder_PlugCreator ${CMAKE_CURRENT_LIST_DIR}/PlugFilterCreator.cpp)
add_library(AmbiEncoder_PlugCreator STATIC ${CMAKE_CURRENT_LIST_DIR}/PlugFilterCreator.cpp)
#juce_generate_juce_header(AmbiEncoder_PlugCreator)
target_compile_definitions(AmbiEncoder_PlugCreator PUBLIC
    -DPLUGIN_IS_AMBI_ENCODER=1)
target_link_libraries(AmbiEncoder_PlugCreator
    ${COMMON_LINK_LIBRARIES}
)
target_include_directories(AmbiEncoder_PlugCreator PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/../)
target_include_directories(AmbiEncoder_PlugCreator PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/)
#juce_add_binary_data(AmbiDecoder_PlugCreator ${CMAKE_CURRENT_LIST_DIR}/PlugFilterCreator.cpp)
add_library(AmbiDecoder_PlugCreator STATIC ${CMAKE_CURRENT_LIST_DIR}/PlugFilterCreator.cpp)
#juce_generate_juce_header(AmbiDecoder_PlugCreator)
target_compile_definitions(AmbiDecoder_PlugCreator PUBLIC
    -DPLUGIN_IS_AMBI_DECODER=1)
target_link_libraries(AmbiDecoder_PlugCreator
    ${COMMON_LINK_LIBRARIES}
)
target_include_directories(AmbiDecoder_PlugCreator PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/../)
target_include_directories(AmbiDecoder_PlugCreator PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/)


#juce_add_binary_data(AmbiPanner_PlugCreator ${CMAKE_CURRENT_LIST_DIR}/PlugFilterCreator.cpp)
add_library(AmbiPanner_PlugCreator STATIC ${CMAKE_CURRENT_LIST_DIR}/PlugFilterCreator.cpp)
#juce_generate_juce_header(AmbiPanner_PlugCreator)
target_compile_definitions(AmbiPanner_PlugCreator PUBLIC
    -DPLUGIN_IS_AMBI_PANNER=1)
target_link_libraries(AmbiPanner_PlugCreator
    ${COMMON_LINK_LIBRARIES}
)
target_include_directories(AmbiPanner_PlugCreator PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/../)
target_include_directories(AmbiPanner_PlugCreator PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/)

target_link_libraries(AmbiEncoderMulti PUBLIC PlugFilterCreator_Helper)
target_link_libraries(AmbiEncoder_PlugCreator PRIVATE AmbiEncoderMulti)
target_link_libraries(AmbiEncoderMulti_LV2 PRIVATE AmbiEncoder_PlugCreator)
target_link_libraries(AmbiEncoderMulti_Standalone PRIVATE AmbiEncoder_PlugCreator)
target_link_libraries(AmbiEncoderMulti_VST3 PRIVATE AmbiEncoder_PlugCreator)

target_link_libraries(AmbiEncoderSolo PUBLIC PlugFilterCreator_Helper)
target_link_libraries(AmbiEncoderSolo_LV2 PRIVATE AmbiEncoder_PlugCreator)
target_link_libraries(AmbiEncoderSolo_Standalone PRIVATE AmbiEncoder_PlugCreator)
target_link_libraries(AmbiEncoderSolo_VST3 PRIVATE AmbiEncoder_PlugCreator)

target_link_libraries(AmbiDecoder PUBLIC PlugFilterCreator_Helper)
target_link_libraries(AmbiDecoder_PlugCreator PRIVATE AmbiDecoder)
target_link_libraries(AmbiDecoder_LV2 PRIVATE AmbiDecoder_PlugCreator)
target_link_libraries(AmbiDecoder_Standalone PRIVATE AmbiDecoder_PlugCreator)
target_link_libraries(AmbiDecoder_VST3 PRIVATE AmbiDecoder_PlugCreator)

#target_link_libraries(AmbiDecoder PUBLIC PlugFilterCreator_Helper)
#target_link_libraries(AmbiDecoder_LV2 PRIVATE AmbiDecoder_PlugCreator)
#target_link_libraries(AmbiDecoder_Standalone PRIVATE AmbiDecoder_PlugCreator)
#target_link_libraries(AmbiDecoder_VST3 PRIVATE AmbiDecoder_PlugCreator)
