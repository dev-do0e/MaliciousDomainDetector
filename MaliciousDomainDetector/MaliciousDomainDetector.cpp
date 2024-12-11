#include "MaliciousDomainDetector.h"

void MaliciousDomainDetector::maliciousDomainDetectorManager(){

    while(true){
        std::cout << "MaliciousDomainDetector executed at: " << time(nullptr) << std::endl;

        //step 1. get domain for SQLite Table (apps.fqdns)
        SqlDataFetcher sqlDataFetcher;
        if(!sqlDataFetcher.fetchFqdnsNames(fqdnsDomains, "./apps.fqdns")){
            std::cerr << "Failed to fetch data from the database." << std::endl;
            continue;
        }

        //step 2. find domains with keyword
        if(!MaliciousDomainDetector::findDomainsWithKeyword()){
            std::cerr << "Failed to open or parse the keywords.json file" << std::endl;
            continue;
        }

        //step 3. Check whether the domain containing the keyword has already taken a screenshot
        //          If you have taken a screenshot once, change the second value to false.

        //step 4. 

        std::cout << "we gonna sleep.." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }

}   

bool MaliciousDomainDetector::findDomainsWithKeyword() {

    //step 1. Remove domain duplication and change type to unordered_map
    std::unordered_set<std::string> unorderedSetForDeduplication(fqdnsDomains.begin(), fqdnsDomains.end());
    for (const auto& str : unorderedSetForDeduplication) {
        uniqueFqdnsDomains[str] = false;
    }
    unorderedSetForDeduplication.clear();


    // Step 2: JSON Parsing
    std::string filePath = "./keywords.json";
    json jsonObject;
    if (std::ifstream inputFile(filePath); !(inputFile && (inputFile >> jsonObject))) {
        std::cerr << "Failed to open or parse the file: " << filePath << std::endl;
        return false;
    }
    auto keywords = jsonObject["keywords"];

    //step 3. Check whether keyword is included
    for (auto& domain : uniqueFqdnsDomains) {
        if(domain.second == true){
            continue;
        }
        for(const auto& keyword : keywords){
            if(domain.first.find(keyword) != std::string::npos){
                domain.second = true;
            }
        }
    }

    return true;
}
