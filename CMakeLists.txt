cmake_minimum_required(VERSION 3.10)
find_package(JNI REQUIRED)
set(TARGET_NAME "jni_processing")
add_executable(${TARGET_NAME} 
    jni_processing.cpp
    submodules/TypedJNI/typedjni.hpp
    submodules/TypedJNI/typedjni.cpp
)
target_include_directories(${TARGET_NAME} PRIVATE ${JNI_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} ${JNI_LIBRARIES})
