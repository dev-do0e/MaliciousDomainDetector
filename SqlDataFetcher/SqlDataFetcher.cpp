#include "SqlDataFetcher.h"
#include <sqlite3.h>
#include <iostream>

// constructor: open database file and perform connection
SqlDataFetcher::SqlDataFetcher(const std::string &dbPath) : dbPath(dbPath), db(nullptr) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    }
}

// destuctor : closing database connection
SqlDataFetcher::~SqlDataFetcher() {
    if (db) {
        sqlite3_close(db);
    }
}

// 데이터베이스에서 도메인 이름을 가져와 vector에 저장하는 함수
bool SqlDataFetcher::fetchDomainRecords(std::vector<std::string> &fqdnsDomains) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT name FROM fqdns ORDER BY name ASC;";

    // SQL 쿼리 준비
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // 쿼리 결과를 vector에 저장
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* domain = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));  // 첫 번째 컬럼의 값을 가져옴
        fqdnsDomains.push_back(domain);  // vector에 도메인 이름 추가
    }

    // 리소스 정리
    sqlite3_finalize(stmt);
    return true;
}
