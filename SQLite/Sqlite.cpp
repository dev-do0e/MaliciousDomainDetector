#include "Sqlite.h"
#include <sqlite3.h>
#include <iostream>

// function that get the domain's from fqdns and saving to vector 
bool Sqlite::selectFqdnsNames(std::vector<std::string> &fqdnsDomains) {

    // database file name and SQLite database obj
    sqlite3* db;

    if (sqlite3_open("apps.fqdns", &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_stmt* stmt;
    const char* query = "SELECT name FROM fqdns;";
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

    //resource cleanup
    sqlite3_finalize(stmt);

    //closing database connection
    if(db){
        sqlite3_close(db);
    }
    
    return true;

}

bool Sqlite::insertMaliciousDomainsNameScreenshot(const std::string& domain){
    // database file name and SQLite database obj
    sqlite3* db; 
    char* errorMessage = nullptr;

    //open database file (if does not exist, create it)
    if (sqlite3_open("maliciousDomain.db", &db) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // create table SQL
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS maliciousDomains (
            name TEXT NOT NULL UNIQUE,
            saved_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            screenshot TEXT
        );
    )";
    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errorMessage)) {
        std::cerr << "Error creating table: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return false;
    }

    //insert data
    sqlite3_stmt* stmt;
    const char* insertSQL = "INSERT INTO maliciousDomains (name, screenshot) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }
    // 데이터 바인딩
    sqlite3_bind_text(stmt, 1, domain.c_str(), -1, SQLITE_STATIC); // name
    sqlite3_bind_blob(stmt, 2, screenshot.data(), screenshot.size(), SQLITE_STATIC); // screenshot

    // SQL 실행
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error inserting data: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Data inserted successfully!" << std::endl;
    }
}
