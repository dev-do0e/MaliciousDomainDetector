#ifndef MALICIOUS_DOMAIN_DECTOR_H
#define MALICIOUS_DOMAIN_DECTOR_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <thread>
#include <fstream>  
#include <cstdlib> 


#include "../SQLite/Sqlite.h"
#include "../json.hpp"

using json = nlohmann::json;

class MaliciousDomainDetector {
    private :
        std::vector<std::string> fqdnsDomains;
        std::unordered_map<std::string, bool> uniqueFqdnsDomains;
        Sqlite sqlite;

    public :
        void maliciousDomainDetectorManager();

        bool findDomainsWithKeyword();

        bool createScreenshotConfig(const std::string&);

        bool insertResultToDB(const std::string&);

};

#endif