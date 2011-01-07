aux_source_directory(src/client pong_client_sources)
aux_source_directory(src/common pong_common_sources)
aux_source_directory(src/server pong_server_sources)

include_directories(src/client src/common src/server)

add_executable(pong_client
	${pong_client_sources}
	${pong_common_sources}
)

add_executable(pong_server
	${pong_common_sources}
	${pong_server_sources}
)

target_link_libraries(pong_client
	engine
)

target_link_libraries(pong_server
	engine
)
