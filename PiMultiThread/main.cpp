#include <iostream> 
#include <thread> 
#include <mutex> 
#include <cstdint>
#include <iomanip> 
#include <cmath> 
#include <future> 
#include <exception> 
#include <vector> 
#include <chrono>

using std::cin;
using std::cout;
using std::endl; 

const int CPUthread = std::thread::hardware_concurrency();

long double piMaker(const long double& limit, int start, int skip) {
    if (limit <= 1E4) {
        throw std::runtime_error("There limit input number is below 10000!");
    } else {
    long double sum{0}; 
    for(auto i = start; i < limit; i+=skip) {
        int64_t sign = std::pow(-1, i); 
        long double term = 1.0/((1 * 2 * i) + 1);
        sum += sign * term; 
    }
    return sum * 4; 
    }
}

int main () {
    std::vector<std::future<long double>> vecPi; 
    const long double limit{1E8};
    long double sumPi{0.0}; //this is the final pi value
    
    auto timeStart = std::chrono::steady_clock::now(); 
    for (auto i = 0; i < CPUthread; i++) {
        try {
            std::future<long double> pi = std::async(std::launch::async, piMaker, limit, i, CPUthread);
            vecPi.push_back(std::move(pi));
        }
        catch(std::runtime_error& e) {
            std::cerr << e.what() << endl; 
        }
    }
    for (auto& i : vecPi) {
        sumPi +=i.get();
    }
    auto timeEnd = std::chrono::steady_clock::now(); 
    auto durationTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd-timeStart).count();
    
    cout << std::setprecision(15) << std::setw(32) << std::left << "The STL M_PI is: "<< M_PI << endl;
    cout << std::setprecision(15) << std::setw(32) << std::left <<"The calculated PI is: " << sumPi << endl;
    cout <<std::setw(32) << std::left << "Milliseconds to calculate PI: " << durationTime << endl;
    return 0; 
}