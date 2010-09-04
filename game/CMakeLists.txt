aux_source_directory(src/client game_client_sources)
aux_source_directory(src/common game_common_sources)
aux_source_directory(src/server game_server_sources)

include_directories(src/client src/common src/server)

add_executable(client
	${game_client_sources}
	${game_common_sources}
)

add_executable(server
	${game_common_sources}
	${game_server_sources}
)

target_link_libraries(client
	engine
)

target_link_libraries(server
	engine
)
