#include <iostream>
#include <chrono>
#include <thread>

#include "DomainScanner/DomainScanner.h"

int main() {

    do {
        // 실행할 작업
        std::cout << "MaliciousDomainDetector executed at: " << time(nullptr) << std::endl;

        // 60초 대기 (1분)
        std::this_thread::sleep_for(std::chrono::minutes(1));
    } while (true);

    return 0;
}
