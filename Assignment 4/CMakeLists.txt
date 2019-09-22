cmake_minimum_required(VERSION 3.13)
project(A4)

set(CMAKE_CXX_STANDARD 14)

add_executable(A4 shape_slotmachine_driver.cpp Rhombus.cpp Rhombus.h Rectangle.cpp Rectangle.h AcuteTriangle.cpp AcuteTriangle.h RightTriangle.cpp RightTriangle.h SlotMachine.cpp SlotMachine.h Shape.cpp Shape.h Triangle.cpp Triangle.h)