cmake_minimum_required(VERSION 2.8)


project(3D_Adventures)
set (3D_Adventures_VERSION_MAJOR 1)
set (3D_Adventures_VERSION_MINOR 0)









include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/common")
include_directories("${PROJECT_SOURCE_DIR}/include")





     



add_subdirectory(common)
add_executable(3D_Adventures main.cpp stdafx.cpp stdafx.h)








target_link_libraries(3D_Adventures common)
target_link_libraries(3D_Adventures base)
target_link_libraries(3D_Adventures camera_implementation)
target_link_libraries(3D_Adventures components)
target_link_libraries(3D_Adventures controller)
target_link_libraries(3D_Adventures converter)
target_link_libraries(3D_Adventures crypt)
target_link_libraries(3D_Adventures entity)
target_link_libraries(3D_Adventures entity_ui)
target_link_libraries(3D_Adventures entity_palette)
target_link_libraries(3D_Adventures entity_info)
target_link_libraries(3D_Adventures entity_instance)
target_link_libraries(3D_Adventures filters)
target_link_libraries(3D_Adventures light)
target_link_libraries(3D_Adventures mesh_implementation)
target_link_libraries(3D_Adventures model_loaders)
target_link_libraries(3D_Adventures settings)
target_link_libraries(3D_Adventures shader)
target_link_libraries(3D_Adventures sky_implementation)
target_link_libraries(3D_Adventures terrain)
target_link_libraries(3D_Adventures terrain_implementation)
target_link_libraries(3D_Adventures texture)
target_link_libraries(3D_Adventures ui)
target_link_libraries(3D_Adventures ui_implementation)
target_link_libraries(3D_Adventures util)








set(BOOST_ROOT "C:/Users/Aaether/Desktop/")




   set(Boost_USE_STATIC_LIBS        ON)
   set(Boost_USE_MULTITHREADED      ON)
   set(Boost_USE_STATIC_RUNTIME    OFF)
   find_package(Boost
             1.58.0
             COMPONENTS system
                        filesystem
             REQUIRED)
   
   
   
   
      include_directories(${Boost_INCLUDE_DIRS})
      target_link_libraries(3D_Adventures ${Boost_LIBRARIES})
	  
   
   
   
  
  
   find_package(OpenGL REQUIRED)
   
   
  include_directories(${OPENGL_INCLUDE_DIRS})
  target_link_libraries(3D_Adventures ${OPENGL_LIBRARIES})
  
  
  
  
  find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
	  target_link_libraries(3D_Adventures ${GLEW_LIBRARIES})


	  if (GLEW_FOUND)
	  MESSAGE(STATUS "GLEW was found!")
	  endif(GLEW_FOUND)
  
  
  
  find_package(GLFW REQUIRED)
  
  
  
  
  
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
  find_package(CEGUI REQUIRED)
    include_directories(${CEGUI_INCLUDE_DIR})
	  target_link_libraries(3D_Adventures ${CEGUI_LIBRARY})
  
  