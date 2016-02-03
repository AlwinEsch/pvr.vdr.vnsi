project(kodi-addon-sharedlibrary)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

enable_language(C CXX)

include(../dev-kit-api-level.cmake)

find_package(kodiplatform REQUIRED)
find_package(p8-platform REQUIRED)

add_definitions(-DUSE_DEMUX)

list(APPEND LIB_SOURCES src/InterProcess.cpp
                        ../shared-code/AddonLibFunc_Base_c.cpp
                        ../shared-code/AddonLibFunc_Base_cpp.cpp
                        ../shared-code/ErrorCodeNames.cpp
                        ../shared-code/LibraryVersion.cpp)

if(WIN32)
  list(APPEND DEPLIBS ${p8-platform_LIBRARIES} ws2_32)
  list(APPEND LIB_SOURCES ../include/kodi/dlfcn-win32.cpp)
else()
  list(APPEND DEPLIBS ${p8-platform_LIBRARIES})
endif()

include_directories(${INCLUDES}
                    ../include/
                    src/
                    ${kodiplatform_INCLUDE_DIRS}
                    ${p8-platform_INCLUDE_DIRS}
                    ${KODI_INCLUDE_DIR})

add_library(kodi.addon.sharedlibrary ${LIB_SOURCES})
target_link_libraries(kodi.addon.sharedlibrary ${DEPLIBS})
set_target_properties(kodi.addon.sharedlibrary PROPERTIES OUTPUT_NAME kodi.addon.sharedlibrary.api${ADDON_API_LEVEL})
