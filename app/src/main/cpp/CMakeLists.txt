cmake_minimum_required(VERSION 3.4.1)

add_library( MainActivityJNI SHARED MainActivityJNI.cpp)
target_link_libraries( MainActivityJNI log android)