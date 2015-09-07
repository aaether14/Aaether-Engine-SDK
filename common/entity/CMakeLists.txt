file(GLOB Sources *.cpp *.hpp)
add_library(entity STATIC ${Sources})




add_subdirectory(ui)
add_subdirectory(palette)