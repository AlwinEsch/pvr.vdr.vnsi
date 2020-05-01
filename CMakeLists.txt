cmake_minimum_required(VERSION 3.5)
project(pvr.vdr.vnsi)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

find_package(Kodi REQUIRED)
find_package(glm REQUIRED)
find_package(p8-platform REQUIRED)

if(NOT WIN32 AND (APP_RENDER_SYSTEM STREQUAL "gl" OR NOT APP_RENDER_SYSTEM))
  find_package(OpenGl REQUIRED)
  set(DEPLIBS ${OPENGL_LIBRARIES})
  set(INCLUDES ${OPENGL_INCLUDE_DIR})
  add_definitions(${OPENGL_DEFINITIONS})
else()
  find_package(OpenGLES REQUIRED)
  set(DEPLIBS ${OPENGLES_LIBRARIES})
  set(INCLUDES ${OPENGLES_INCLUDE_DIR})
  add_definitions(${OPENGLES_DEFINITIONS})
endif()

include_directories(${INCLUDES}
                    ${GLM_INCLUDE_DIR}
                    ${p8-platform_INCLUDE_DIRS}
                    ${KODI_INCLUDE_DIR}/..) # Hack way with "/..", need bigger Kodi cmake rework to match right include ways

list(APPEND DEPLIBS ${p8-platform_LIBRARIES})

list(APPEND VDR_SOURCES src/addon.cpp
                        src/requestpacket.cpp
                        src/responsepacket.cpp
                        src/tools.cpp
                        src/Settings.cpp
                        src/VNSIAdmin.cpp
                        src/VNSIChannels.cpp
                        src/VNSIChannelScan.cpp
                        src/VNSIData.cpp
                        src/VNSIDemux.cpp
                        src/VNSIRecording.cpp
                        src/VNSISession.cpp)

list(APPEND VDR_HEADERS src/addon.h
                        src/requestpacket.h
                        src/responsepacket.h
                        src/tools.h
                        src/Settings.h
                        src/VNSIAdmin.h
                        src/VNSIChannelScan.h
                        src/VNSIChannels.h
                        src/vnsicommand.h
                        src/VNSIData.h
                        src/VNSIDemux.h
                        src/VNSIRecording.h
                        src/VNSISession.h)

build_addon(pvr.vdr.vnsi VDR DEPLIBS)

include(CPack)
