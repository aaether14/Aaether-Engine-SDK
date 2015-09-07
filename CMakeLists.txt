cmake_minimum_required(VERSION 2.8)


project(3D_Adventures)
set (3D_Adventures_VERSION_MAJOR 1)
set (3D_Adventures_VERSION_MINOR 0)




link_directories("${PROJECT_SOURCE_DIR}/lib")



include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/common")
include_directories("${PROJECT_SOURCE_DIR}/include")



add_executable(3D_Adventures main.cpp stdafx.cpp stdafx.h)





add_subdirectory(common)




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




target_link_libraries(3D_Adventures CEGUICommonDialogs-0.lib)
target_link_libraries(3D_Adventures CEGUIBase-0.lib)
target_link_libraries(3D_Adventures CEGUIOpenGLRenderer-0.lib)
target_link_libraries(3D_Adventures assimpd.lib)
target_link_libraries(3D_Adventures FreeImaged.lib)
target_link_libraries(3D_Adventures freetype.lib)
target_link_libraries(3D_Adventures glfw3.lib)
target_link_libraries(3D_Adventures glew32.lib)
target_link_libraries(3D_Adventures glu32.lib)
target_link_libraries(3D_Adventures opengl32.lib)





