aux_source_directory(src/ engine_sources)

include_directories(src/)

add_library(engine STATIC
	${engine_sources}
)

target_link_libraries(engine
	${Boost_LIBRARIES}
	${SFML_LIBRARIES}
    ${BULLET_LIBRARIES}
	${ImageMagick_LIBRARIES}
)
