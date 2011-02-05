aux_source_directory(src/client game_client_sources)
aux_source_directory(src/common game_common_sources)
aux_source_directory(src/server game_server_sources)

include_directories(src/client src/common src/server)

add_executable(editor
	${game_client_sources}
	${game_common_sources}
)

add_executable(editor_server
	${game_common_sources}
	${game_server_sources}
)

target_link_libraries(editor
	engine
)

target_link_libraries(editor_server
	engine
)
