cmake_minimum_required (VERSION 3.15)
project (Project)


if(CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(ANDROID TRUE)
endif()

#SFML SHARED LIBRARY
if (ANDROID)
    set(SFML_STATIC_LIBRARIES FALSE)
endif()



#FILES
file(GLOB_RECURSE Project_SOURCES "src/*.cpp")
if (NOT EXISTS "assets/")
    file(MAKE_DIRECTORY "assets/")
endif()
if (NOT EXISTS "versions/")
    file(MAKE_DIRECTORY "versions/")
endif()

if (ANDROID)

    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
    set(CMAKE_MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)
    set(PATH_TO_SFML ${ANDROID_NDK}/sources/third_party/sfml)
    set(SFML_DIR ${PATH_TO_SFML}/lib/${ANDROID_ABI}/cmake/SFML)
    find_package(SFML 2.6 COMPONENTS graphics audio window system network REQUIRED)

    add_library(${CMAKE_PROJECT_NAME} SHARED ${Project_SOURCES})

    add_library(openal SHARED IMPORTED)
    set_target_properties(openal PROPERTIES IMPORTED_LOCATION_RELEASE ${PATH_TO_SFML}/extlibs/lib/${ANDROID_ABI}/libopenal.so)
    set_target_properties(openal PROPERTIES IMPORTED_LOCATION_DEBUG ${PATH_TO_SFML}/extlibs/lib/${ANDROID_ABI}/libopenal.so)

endif()

#C++ version
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)

set (LINK_SFML sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

if (ANDROID)
    target_link_libraries(${CMAKE_PROJECT_NAME}
        log
        android
        ${LINK_SFML}
        -Wl,--whole-archive sfml-main -Wl,--no-whole-archive
        openal
        EGL
        GLESv1_CM
    )
endif()
