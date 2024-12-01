#include "MaliciousDomainDetector.h"

void MaliciousDomainDetector::maliciousDomainDetectorManager(){

    while(true){
        std::cout << "MaliciousDomainDetector executed at: " << time(nullptr) << std::endl;

        //step 1. init
        if(MaliciousDomainDetector::maliciousDomainDetectorinit()){
            std::cout << fqdnsDomains.size() << " data was fetched from the database. " <<  std::endl;
        }else{
            std::cerr << "Failed to fetch data from the database." << std::endl;
            continue;
        }

        //step 2. find keyword in domain
        for(int i = 0; i < fqdnsDomains.size(); i++){
            if(MaliciousDomainDetector::findKeywordInDomain(fqdnsDomains[i])){
                std::cout << fqdnsDomains[i] << std::endl;
            }
        }

        std::cout << "we gonna sleep.." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }

}

bool MaliciousDomainDetector::maliciousDomainDetectorinit() {
    SqlDataFetcher sqlDataFetcher("./apps.fqdns");
    return sqlDataFetcher.fetchFqdnsNames(fqdnsDomains);
}

bool MaliciousDomainDetector::findKeywordInDomain(std::string domain) {

    std::string filePath = "./keywords.json";

    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) std::cerr << "Failed to open the file: " << filePath << std::endl;

    json jsonObject;
    inputFile >> jsonObject;
    inputFile.close();

    auto keywords = jsonObject["keywords"];

    for (const std::string& keyword : keywords) {
        if (domain.find(keyword) != std::string::npos) return true;
    }
    return false;
}

void MaliciousDomainDetector::findDomainDifferences(std::string domain) {
    // findDomainDifferences 함수 구현
}
