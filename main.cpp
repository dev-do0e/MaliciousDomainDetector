#include <iostream>
#include <chrono>
#include <thread>

#include "DomainScanner/DomainScanner.h"

int main() {

    do {
        std::cout << "MaliciousDomainDetector executed at: " << time(nullptr) << std::endl;

        DomainScanner domainScanner;
        domainScanner.findDomainDifferences();

        // waiting 60sec
        std::this_thread::sleep_for(std::chrono::minutes(1));
    }while (true);

    return 0;
}
