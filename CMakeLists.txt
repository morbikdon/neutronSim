cmake_minimum_required(VERSION 3.16)
project(neutronSim)

set(Geant4_DIR "/Users/berare/BL4S_Geant4/Geant4_buildFromSource_4.11.0/geant4-v11.0.0-install/lib/Geant4-11.0.0")

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()


add_definitions(-DG4UI_USE -DG4VIS_USE)

file(GLOB SOURCES "src/*.cc")

add_executable(neutronSim ${SOURCES})

target_include_directories(neutronSim PUBLIC
    ${Geant4_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(neutronSim ${Geant4_LIBRARIES})
