cmake_minimum_required (VERSION 3.8)

project ("Yuki")

find_package(glfw3 CONFIG REQUIRED)
find_package(vulkan REQUIRED)
find_package(glm CONFIG REQUIRED)

file (GLOB YUKIE_SRCS "./YukiVE/Srcs/*.cpp")
file (GLOB YUKIE_HEADERS "./YukiVE/Include/*.hpp" "./YukiVE/Include/YukiCore/*.hpp")
add_library(YukiCore SHARED "${YUKIE_SRCS}")
target_include_directories(YukiCore PUBLIC "./YukiVE/Include")
target_compile_definitions(YukiCore PRIVATE YUKIE_BUILD_DLL)
target_link_libraries(YukiCore PRIVATE glfw Vulkan::Vulkan Vulkan::Headers glm::glm)

add_executable (YukiUI "YukiUI/Main.cpp")
target_include_directories(YukiUI PUBLIC "./YukiVE/Include")

target_link_libraries(YukiUI PUBLIC glfw Vulkan::Vulkan Vulkan::Headers glm::glm)