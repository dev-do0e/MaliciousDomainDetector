#ifndef SQL_DATA_FETCHER_H
#define SQL_DATA_FETCHER_H

#include <iostream>
#include <vector>
#include <sqlite3.h>

class SqlDataFetcher {
    private :
        std::string dbPath;   // database file name 파일 이름
        sqlite3* db;          // SQLite database obj

    public :
        SqlDataFetcher(const std::string &dbPath);

        ~SqlDataFetcher();

        bool fetchFqdnsNames(std::vector<std::string> &fqdnsDomains);


};

#endif