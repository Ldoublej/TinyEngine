aux_source_directory(. SOURCES)

add_library(scene ${SOURCES} SkyBox.h SkyBox.cpp)
target_link_libraries(scene graph assimp resource)