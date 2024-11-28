#include "DomainScanner.h"

DomainScanner::DomainScanner() {
    //if calling DomainScanner, fqdnsDomains setup automatic
    SqlDataFetcher sqlDataFetcher("./apps.fqdns");
    if (sqlDataFetcher.fetchFqdnsNames(fqdnsDomains)) {
        std::cout << fqdnsDomains.size() << " data was fetched from the database. " <<  std::endl;
    } else {
        std::cerr << "Failed to fetch data from the database." << std::endl;
    }
}

void DomainScanner::findDomainDifferences() {

    int checkedDomainsIndex = 0;
    for(int fqdnsDomainsIndex = 0; fqdnsDomainsIndex < fqdnsDomains.size(); fqdnsDomainsIndex++,checkedDomainsIndex++){
        if(fqdnsDomains[fqdnsDomainsIndex] != checkedDomains[checkedDomainsIndex]){
            //call the function 'containsKeywordInDns'
            //containsKeywordInDns's parameter type is std::string
        }

    }

}

void DomainScanner::containsKeywordInDns(const std::string domain) {
    // containsKeywordInDns 함수 구현
    
}
