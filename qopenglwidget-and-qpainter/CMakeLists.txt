cmake_minimum_required(VERSION 3.1)

project(glpainter_ex VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_MESSAGE_LOG_LEVEL "DEBUG")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(WIN32)
	set(CMAKE_BUILD_TYPE Debug)
endif()

option(WITH_PAINTER "Use QPainter" OFF)
if(WITH_PAINTER)
   add_definitions(-DWITH_PAINTER)
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets Core OpenGLWidgets Gui OpenGL)


set(PROJECT_SOURCES
	main.cpp	
    MainWindow.cpp
    BasedOGLWidget.cpp
    SubOGLWidget.cpp
    Shaders.cpp
)
add_executable(glpainter_ex
    ${PROJECT_SOURCES}
)

if(WIN32)
	set_target_properties(glpainter_ex PROPERTIES
		WIN32_EXECUTABLE TRUE
	)
endif()

target_link_libraries(
	glpainter_ex
	PRIVATE
	Qt6::Widgets
	Qt6::Core
	Qt6::Gui
	Qt6::OpenGLWidgets
	Qt6::OpenGL
)

