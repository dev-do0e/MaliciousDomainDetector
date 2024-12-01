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

// function that get the domain's from fqdns and saving to vector 
bool SqlDataFetcher::fetchFqdnsNames(std::vector<std::string> &fqdnsDomains) {
    sqlite3_stmt* stmt;
    const char* query = "SELECT DISTINCT name FROM fqdns ORDER BY name ASC;";

    // preparing SQL query
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // saving result of SQL query to vector
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* domain = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));  // get the first result of column
        fqdnsDomains.push_back(domain);  // add domain to vector
    }

    // 리소스 정리
    sqlite3_finalize(stmt);
    return true;
}
