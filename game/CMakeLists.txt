aux_source_directory(src/ game_sources)

add_executable(game
	${game_sources}
)

target_link_libraries(game
	engine
)
