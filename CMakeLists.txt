cmake_minimum_required(VERSION 3.16)
project(neutronSim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Geant4 install path
set(Geant4_DIR "/Users/berare/BL4S_Geant4/Geant4_buildFromSource_4.11.0/geant4-v11.0.0-install/lib/Geant4-11.0.0")

# UI/Visualization drivers
option(WITH_GEANT4_UIVIS "Build with UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})

# ------------------------------------------------------------------------------
# Source and header files
# ------------------------------------------------------------------------------

set(SOURCES
    src/main.cc
    src/DetectorConstruction.cc
    src/PrimaryGeneratorAction.cc
    src/ActionInitialization.cc
    src/RunAction.cc
    src/SteppingAction.cc
    src/neutronGlobals.cc
)

set(HEADERS
    include/DetectorConstruction.hh
    include/PrimaryGeneratorAction.hh
    include/ActionInitialization.hh
    include/RunAction.hh
    include/SteppingAction.hh
    include/neutronGlobals.hh
)

# ------------------------------------------------------------------------------
# Executable and linking
# ------------------------------------------------------------------------------

add_executable(neutronSim ${SOURCES} ${HEADERS})

target_include_directories(neutronSim PUBLIC
    ${Geant4_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(neutronSim ${Geant4_LIBRARIES})
