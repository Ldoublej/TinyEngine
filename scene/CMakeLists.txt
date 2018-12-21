aux_source_directory(. SOURCES)

add_library(scene ${SOURCES} )
target_link_libraries(scene graph assimp resource)