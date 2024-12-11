#ifndef MALICIOUS_DOMAIN_DECTOR_H
#define MALICIOUS_DOMAIN_DECTOR_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <thread>
#include <fstream>  


#include "../SQLite/Sqlite.h"
#include "../json.hpp"

using json = nlohmann::json;

class MaliciousDomainDetector {
    private :
        std::vector<std::string> fqdnsDomains;
        std::unordered_map<std::string, bool> uniqueFqdnsDomains;

    public :
        void maliciousDomainDetectorManager();

        bool findDomainsWithKeyword();

};

#endif