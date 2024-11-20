cmake_minimum_required(VERSION 3.8)
project(MyGeant4Simulation)

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

add_executable(MySimulation MySimulation.cc MyDetectorConstruction.cc MyPrimaryGeneratorAction.cc MySensitiveDetector.cc MyEventAction.cc MyHit.cc)
target_link_libraries(MySimulation ${Geant4_LIBRARIES})
