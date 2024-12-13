#include "MaliciousDomainDetector.h"

void MaliciousDomainDetector::maliciousDomainDetectorManager(){

    while(true){

        std::cout << "MaliciousDomainDetector executed at: " << time(nullptr) << std::endl;

        //step 1. Get domain for SQLite Table (apps.fqdns)
        if(!sqlite.selectFqdnsNames(fqdnsDomains)){
            std::cerr << "Failed to fetch data from the database." << std::endl;
            std::cout << "we gonna sleep.." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(30));
            continue;
        }

        //step 2. Find domains with keyword
        if(!MaliciousDomainDetector::findDomainsWithKeyword()){
            std::cerr << "Failed to open or parse the keywords.json file." << std::endl;
            std::cout << "we gonna sleep.." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(30));
            continue;
        }

        //step 3. Check whether the domain containing the keyword has already taken a screenshot
        //          If you have taken a screenshot once, change the second value to false.

        //step 4. Take a screenshot and save it to DB
        bool check = true;
        for(auto& domain : uniqueFqdnsDomains){

            std::string domainName = domain.first;
            bool checkDomainScreenshotSaved = domain.second;

            //4-1. Pass over domains that don’t require screenshots
            if(checkDomainScreenshotSaved == false){
                continue;
            }        

            //step 4-2. Create the json file needed to take a screenshot
            if(!MaliciousDomainDetector::createScreenshotConfig(domainName)){
                std::cerr << "occured file delete error." << std::endl;
                check = false;
                break;
            }

            //step 4-3. Take a screenshot to save success and results
            std::cout << domainName << std::endl;
            std::system("node ./wpl.js");

            //step 4-4. Save results to DB
            if(!MaliciousDomainDetector::insertResultToDB(domainName)){
                
            }


        }
        if(check == false){
            std::cout << "we gonna sleep.." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(30));
        }




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

    // Step 2. Json parsing
    std::string filePath = "./keywords.json";
    json jsonObject;
    std::ifstream inputFile(filePath);
    if (!(inputFile && (inputFile >> jsonObject))) {
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
 
bool MaliciousDomainDetector::createScreenshotConfig(const std::string& domainName) {

    //step 1. Delete file environment.json if it exists
    std::string filename = "environment.json";
    std::ifstream infile("./"+filename);
    if (infile.good()) {
        //If file is already exist, delete it.
        infile.close();
        if (std::remove(filename.c_str()) != 0) {
            //Occured file delete error
            return false;
        }
    }

    // step 2. Create file if it does not exist
    json jsonData = { 
        {"ignorelist", json::array({"http://" + domainName})},
        {"name", ""},
        {"savescreenshot", true},
        {"template", ""},
        {"timeout", 0},
        {"url", "http://" + domainName}
    }; 
    std::ofstream outfile(filename);
    outfile << jsonData.dump(4);
    outfile.close();

    return true;

}

bool MaliciousDomainDetector::insertResultToDB(const std::string& domain){

    //step 1. json parsing
    std::string filePath = "./result.json";
    json jsonObject;
    std::ifstream inputFile(filePath);
    if (!(inputFile && (inputFile >> jsonObject))) {
        std::cerr << "Failed to open or parse the file: " << filePath << std::endl;
        return false;
    }

    bool success = jsonObject["success"];
    if(success == true){
        //Insert domain, time, and screenshot to DB
        auto screenshot = jsonObject["screenshot"];
        sqlite.insertMaliciousDomainsNameScreenshot(domain, screenshot);
    }else{
        //Insert only domain and time in DB
        sqlite.insertMaliciousDomainsNameScreenshot(domain, nullptr);
    }

}