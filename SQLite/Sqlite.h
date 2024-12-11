#ifndef SQL_DATA_FETCHER_H
#define SQL_DATA_FETCHER_H

#include <iostream>
#include <vector>
#include <sqlite3.h>

class SqlDataFetcher {
    private :
        std::string dbPath;   // database file name
        sqlite3* db;          // SQLite database obj

    public :
        bool fetchFqdnsNames(std::vector<std::string> &fqdnsDomains, const std::string &dbPath);

};

#endif