project(MaliciousDomainDetector)

set(SQLite
SQLite/sqlite3.h
SQLite/sqlite3.c
)

add_executable(MaliciousDomainDetector 

${SQLite}

main.cpp
)