#include "Sqlite.h"
#include <sqlite3.h>
#include <iostream>

// function that get the domain's from fqdns and saving to vector 
bool SqlDataFetcher::fetchFqdnsNames(std::vector<std::string> &fqdnsDomains, const std::string &dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
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
