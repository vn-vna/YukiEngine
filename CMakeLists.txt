cmake_minimum_required(VERSION 3.20)

project(yuki-engine)

# ----- Configurations variables
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_C_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# ----- Global variables
set(VERBOSE_CONFIGURATION ON)
set(YUKI_BUILD_LIBRARY ON)
set(YUKI_BUILD_SANDBOX ON)
set(YUKI_BUILD_PLAYGROUND OFF)
set(CPP_FILE_EXTENSIONS "cpp" "hpp" "cx" "cxx" "hxx" "h")
set(GLSL_FILE_EXTENSIONS "glsl" "vert" "geom" "frag")

# ----- Shader files
set(SHADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/YukiShader")

# ----- Core library
set(YUKICORE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/YukiCore")
set(YUKICORE_INCLUDE_DIR "${YUKICORE_DIR}/Include")
set(YUKICORE_SOURCES_DIR "${YUKICORE_DIR}/Srcs")

####
####

foreach(_CPP_FILE_EXTENSION IN LISTS CPP_FILE_EXTENSIONS) 
  file(GLOB _SOURCE_FILE_FOUND "${YUKICORE_SOURCES_DIR}/*.${_CPP_FILE_EXTENSION}")
  list(LENGTH _SOURCE_FILE_FOUND _SOURCE_FILE_FOUND_LENGTH)
  if(NOT (_SOURCE_FILE_FOUND_LENGTH EQUAL 0))
    list(APPEND YUKICORE_SOURCE_FILES "${_SOURCE_FILE_FOUND}")
  endif()
endforeach()

list(REMOVE_DUPLICATES YUKICORE_SOURCE_FILES)

if(VERBOSE_CONFIGURATION)
  message("[YUKICORE] Source file(s) found:")
  foreach(_SOURCE_FILE_FOUND IN LISTS YUKICORE_SOURCE_FILES)
    message("File: ${_SOURCE_FILE_FOUND}") 
  endforeach()
endif()

# ----- Sandbox program
set(SANDBOX_DIR "${CMAKE_CURRENT_SOURCE_DIR}/YukiSandbox")
set(SANDBOX_INCLUDE_DIR "${SANDBOX_DIR}/Include")
set(SANDBOX_SOURCES_DIR "${SANDBOX_DIR}/Srcs")

foreach(_CPP_FILE_EXTENSION IN LISTS CPP_FILE_EXTENSIONS)
  file(GLOB _SOURCE_FILE_FOUND "${SANDBOX_SOURCES_DIR}/*.${_CPP_FILE_EXTENSION}")
  list(LENGTH _SOURCE_FILE_FOUND _SOURCE_FILE_FOUND_LENGTH)
  if(NOT (_SOURCE_FILE_FOUND_LENGTH EQUAL 0))
    list(APPEND SANDBOX_SOURCE_FILES "${_SOURCE_FILE_FOUND}")
  endif()
endforeach()

list(REMOVE_DUPLICATES SANDBOX_SOURCE_FILES)

if(VERBOSE_CONFIGURATION)
  message("[SANDBOX] Source file(s) found:")
  foreach(_SOURCE_FILE_FOUND IN LISTS SANDBOX_SOURCE_FILES)
    message("File: ${_SOURCE_FILE_FOUND}")
  endforeach()
endif()

# ----- Dependencies

if(WIN32)
  file(GLOB YUKIDEPS_DLL_FILES "${YUKIDEPS_BINARIES_DIR}/*.dll" "${YUKIDEPS_BINARIES_DIR}/*.pdb")
  if(VERBOSE_CONFIGURATION)
    message("Dll file(s) found:")
    foreach(_DLL_FILE_FOUND IN LISTS YUKIDEPS_DLL_FILES)
      message("File: ${_DLL_FILE_FOUND}")
    endforeach()
  endif()
  foreach(_DLL_FILE IN LISTS YUKIDEPS_DLL_FILES)
    file(COPY "${_DLL_FILE}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
  endforeach()
endif()

# ----- Build targets
add_library(yuki-core SHARED "${YUKICORE_SOURCE_FILES}")
target_include_directories(
  yuki-core
  PUBLIC "${YUKICORE_INCLUDE_DIR}"
  PUBLIC "${YUKIDEPS_INCLUDE_DIR}"
)
target_compile_definitions(
  yuki-core
  PRIVATE "YUKICORE_EXPORTS"
)
target_link_directories(
  yuki-core
  PUBLIC "${YUKIDEPS_STATICLIB_DIR}"
)
target_precompile_headers(
  yuki-core
  PUBLIC "${YUKICORE_INCLUDE_DIR}/YukiCore/YukiPCH.hpp"
)

find_package(assimp CONFIG REQUIRED)
find_package(freetype CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_link_libraries(yuki-core 
  PUBLIC assimp::assimp 
  PUBLIC freetype 
  PUBLIC glad::glad 
  PUBLIC glfw 
  PUBLIC fmt::fmt)

if (WIN32)
  target_link_libraries(yuki-core
    PUBLIC pdh)
endif()
find_path(STB_INCLUDE_DIRS "stb_image.h")
target_include_directories(yuki-core PUBLIC ${STB_INCLUDE_DIRS})

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  target_compile_definitions(
    yuki-core
    PRIVATE "_DEBUG"
    PRIVATE "DEBUG"
  )
endif()

add_executable(yuki-sandbox "${SANDBOX_SOURCE_FILES}")
target_link_libraries(yuki-sandbox yuki-core)
target_include_directories(yuki-sandbox PRIVATE "${SANDBOX_INCLUDE_DIR}")

# ----- Resources files / External files / Other stuffs
set(STUFFS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Stuffs")

file(GLOB STUFFS_FILES "${STUFFS_DIR}/*.*")

foreach(_STUFF_FILE IN LISTS STUFFS_FILES)
  get_filename_component(_STUFF_FILENAME "${_STUFF_FILE}" NAME)
  list(APPEND _STUFF_FILE_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${_STUFF_FILENAME}")
  add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${_STUFF_FILENAME}"
    DEPENDS "${_STUFF_FILE}"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
    "${_STUFF_FILE}"
    "${CMAKE_CURRENT_BINARY_DIR}/${_STUFF_FILENAME}"
  )
endforeach()

add_custom_target(sandbox-stuffs DEPENDS "${_STUFF_FILE_OUTPUT}")
add_dependencies(yuki-sandbox sandbox-stuffs)


# ----- Shader files

foreach(_GLSL_FILE_EXTENSION IN LISTS GLSL_FILE_EXTENSIONS)
  file(GLOB _SHADER_FILE_FOUND "${SHADERS_DIR}/*.${_GLSL_FILE_EXTENSION}")
  list(LENGTH _SHADER_FILE_FOUND _SHADER_FILE_FOUND_LENGTH)
  if(NOT (_SHADER_FILE_FOUND_LENGTH EQUAL 0))
    list(APPEND SHADER_FILES_FOUND "${_SHADER_FILE_FOUND}")
  endif()
endforeach()

list(REMOVE_DUPLICATES _SHADER_FILE_FOUND)

if(VERBOSE_CONFIGURATION)
  message("Shader file(s) found:")
  foreach(_SHADER_FILE_FOUND IN LISTS SHADER_FILES_FOUND)
    message("File: ${_SHADER_FILE_FOUND}")
  endforeach()
endif()

foreach(_SHADER_FILE_FOUND IN LISTS SHADER_FILES_FOUND)
  get_filename_component(_SHADER_FILENAME "${_SHADER_FILE_FOUND}" NAME)
  list(APPEND _SHADER_FILE_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${_SHADER_FILENAME}")
  add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${_SHADER_FILENAME}"
    DEPENDS "${_SHADER_FILE_FOUND}"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
    "${_SHADER_FILE_FOUND}"
    "${CMAKE_CURRENT_BINARY_DIR}/${_SHADER_FILENAME}"
  )
endforeach()

add_custom_target(shaders DEPENDS "${_SHADER_FILE_OUTPUT}")
add_dependencies(yuki-core shaders)

# # ----- For windows build
# if(WIN32)
#   if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
#     target_link_libraries(
#       yuki-core
#       GLU32
#       OpenGL32
#       assimp-vc143-mtd
#       freetyped
#       glad
#       glfw3dll
#       fmtd
#       pdh
#     )
#   else()
#     target_link_libraries(
#       yuki-core
#       GLU32
#       OpenGL32
#       assimp-vc143-mt
#       freetype
#       glad
#       glfw3dll
#       fmt
#       pdh
#     )
#   endif()
# endif()

# if(UNIX AND NOT APPLE)
#   if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
#     target_link_libraries(
#       yuki-core
#       GL GLU X11 assimpd minizip jpeg turbojpeg
#       freetype glad glfw3 fmtd z poly2tri Irrlicht
#       png Xxf86vm bz2d
#     )
#   else()
#     target_link_libraries(
#       yuki-core
#       GL GLU X11 assimp minizip jpeg turbojpeg
#       freetype glad glfw3 fmt z poly2tri Irrlicht
#       png Xxf86vm bz2
#     )
#   endif()
# endif()

# ----- Playground projects
if(YUKI_BUILD_PLAYGROUND)
  add_executable(OpenGLMultithreadTest "Playground/OpenGLMultithreadTest.cpp")
  target_link_libraries(OpenGLMultithreadTest yuki-core)

  add_executable(PdhQueryTest "Playground/PdhQueryTest.cpp")
  target_link_libraries(PdhQueryTest pdh)
endif()
