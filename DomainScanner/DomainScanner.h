#ifndef DOMAIN_SCANNER_H
#define DOMAIN_SCANNER_H

#include <iostream>
#include <vector>

#include "../SqlDataFetcher/SqlDataFetcher.h"

class DomainScanner {
    private :
        std::vector<std::string> fqdnsDomains;
        std::vector<std::string> checkedDomains;

    public :
        DomainScanner();

        void findDomainDifferences();
        
        void containsKeywordInDns(std::string domain);

};

#endif