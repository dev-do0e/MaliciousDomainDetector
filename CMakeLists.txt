cmake_minimum_required(VERSION 3.30)

project(MaliciousDomainDetector)

set(SQLite
libs/sqlite3.h
libs/sqlite3.c
)

set(MaliciousDomainDetector
MaliciousDomainDetector/MaliciousDomainDetector.h
MaliciousDomainDetector/MaliciousDomainDetector.cpp
)

set(SqlDataFetcher
SqlDataFetcher/SqlDataFetcher.h
SqlDataFetcher/SqlDataFetcher.cpp
)

# SQLite 라이브러리 경로 설정
set(SQLITE3_LIB_DIR "${CMAKE_SOURCE_DIR}/libs")
set(SQLITE3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs")

add_executable(MaliciousDomainDetector 

${SQLite}
${MaliciousDomainDetector}
${SqlDataFetcher}

json.hpp
main.cpp

)

# SQLite 헤더 포함 디렉토리 설정
target_include_directories(MaliciousDomainDetector PRIVATE ${SQLITE3_INCLUDE_DIR})

# SQLite 정적 라이브러리 연결
target_link_libraries(MaliciousDomainDetector PRIVATE ${SQLITE3_LIB_DIR}/sqlite3.lib)