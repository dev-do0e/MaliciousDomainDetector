#ifndef MALICIOUS_DOMAIN_DECTOR_H
#define MALICIOUS_DOMAIN_DECTOR_H

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>  

#include "../SqlDataFetcher/SqlDataFetcher.h"
#include "../json.hpp"

using json = nlohmann::json;

class MaliciousDomainDetector {
    private :
        std::vector<std::string> fqdnsDomains;
        std::vector<std::string> checkedDomains;

    public :
        void maliciousDomainDetectorManager();

        bool maliciousDomainDetectorinit();

        bool findKeywordInDomain(std::string domain);

        void findDomainDifferences(std::string domain);

};

#endif