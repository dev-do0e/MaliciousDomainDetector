#ifndef SQL_DATA_FETCHER_H
#define SQL_DATA_FETCHER_H

#include <iostream>
#include <vector>
#include <sqlite3.h>

class Sqlite {    
    public :

        bool selectFqdnsNames(std::vector<std::string> &fqdnsDomains);

        bool insertMaliciousDomainsNameScreenshot(const std::string& domain, const std::string& screenshot);

};

#endif