#include "DomainScanner.h"

DomainScanner::DomainScanner() {
    //DomainScanner 호출하면 fqdnsDomains 자동 셋업
    SqlDataFetcher sqlDataFetcher("/Lampad/apps.fqdns");
    sqlDataFetcher.fetchDomainRecords(fqdnsDomains);

    if (sqlDataFetcher.fetchDomainRecords(fqdnsDomains)) {
        std::cout << "Fetched data from the database:" << std::endl;

        int i = 0;
        for (const auto& domain : fqdnsDomains) {
            if(i == 10) break;
            std::cout << domain << std::endl;
            i++;
        }
    } else {
        std::cerr << "Failed to fetch data from the database." << std::endl;
    }

}

void DomainScanner::findDomainDifferences() {
    // findDnsDifferences 함수 구현
    std::cout << "call findDomainDifferences funcion" << std::endl;
}

void DomainScanner::containsKeywordInDns() {
    // containsKeywordInDns 함수 구현
    std::cout << "call containsKeywordInDns function" << std::endl;
}
