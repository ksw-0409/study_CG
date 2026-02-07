cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(PROJECT_NAME lab)

find_package(nlohmann_json CONFIG REQUIRED) 
find_package(imgui CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(gl3w CONFIG REQUIRED)

# 1. 모든 소스 및 헤더 파일 수집
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.h"
)

# 2. 인클루드 경로 명시적 추가 
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source/Core")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source/Managers")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source/Objects")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source/Renderer")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source/Utils")

# 3. IDE(Visual Studio) 솔루션 탐색기 필터 자동 생성
foreach(FILE ${SOURCES}) 
    get_filename_component(FILE_PATH "${FILE}" PATH)
    file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source" "${FILE_PATH}")
    string(REPLACE "/" "\\" GROUP_NAME "${REL_PATH}")
    source_group("${GROUP_NAME}" FILES "${FILE}")
endforeach()

# 4. 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES} "source/Objects/Sprite2D.h" "source/Managers/SpriteLoader.h")

# 5. 라이브러리 연결
target_link_libraries(${PROJECT_NAME} PRIVATE 
    imgui::imgui 
    nlohmann_json::nlohmann_json
    glm::glm 
    glfw 
    unofficial::gl3w::gl3w
)