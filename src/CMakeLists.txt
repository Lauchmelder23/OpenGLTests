
set(VENDOR ${CMAKE_SOURCE_DIR}/vendor)

add_executable(example
	"main.cpp"
   )

file(GLOB SOURCE_FILES
	"${VENDOR}/src/*.c"
	"${VENDOR}/src/*.cpp"
	"objects/*.cpp"
	"objects/primitives/*.cpp"
)

target_sources(example PRIVATE
	${SOURCE_FILES}
)

target_include_directories(example PRIVATE
	glfw
	${VENDOR}/include
	${VENDOR}/include/imgui
	objects
	objects/primitives
)

target_link_libraries(example
	glfw
)

add_custom_command(TARGET example POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:example>/assets
)