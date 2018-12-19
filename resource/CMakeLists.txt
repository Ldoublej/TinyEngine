aux_source_directory(. SOURCES)
message(${SOURCES})
add_library(resource Resource.h ${SOURCES} )