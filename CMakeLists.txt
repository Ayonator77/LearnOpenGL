cmake_minimum_required(VERSION 3.20)
project(LearnOpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
  add_compile_options(/W4 /permissive- /FS)
endif()

# -----------------------------
# Dependencies from vcpkg
# -----------------------------
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(assimp CONFIG REQUIRED)

# -----------------------------
# Sources
# -----------------------------
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_executable(learnopengl ${SOURCES})

target_include_directories(learnopengl PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${Stb_INCLUDE_DIR}
)

target_link_libraries(learnopengl PRIVATE
  glfw
  glad::glad
  glm::glm
  assimp::assimp
  opengl32
)

set_target_properties(learnopengl PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Copy assets next to the exe after build
add_custom_command(TARGET learnopengl POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:learnopengl>/assets"
)

# Copy any runtime DLLs (GLFW etc.) next to the exe
add_custom_command(TARGET learnopengl POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:learnopengl>
    $<TARGET_FILE_DIR:learnopengl>
  COMMAND_EXPAND_LISTS
)
