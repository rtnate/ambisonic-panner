
add_subdirectory(RT-CorePlatform)
add_subdirectory(RT-DSP)
target_link_libraries(rtdsp PUBLIC rtcoreplatform)