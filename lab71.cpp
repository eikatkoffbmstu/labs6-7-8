#include <iostream>
#include <thread>
#include <chrono>
#include <random>


void printFibonacci(int n, const std::string& threadName) {
    std::cout << threadName << " started" << std::endl;
    int a = 0, b = 1;
    for (int i = 0; i < n; ++i) {
        std::cout << threadName << ": " << a << std::endl;
        int temp = a;
        a = b;
        b = temp + b;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << threadName << " finished" << std::endl;
}

void printNaturalNumbers(int n, const std::string& threadName) {
    std::cout << threadName << " started" << std::endl;
    for (int i = 1; i <= n; ++i) {
        std::cout << threadName << ": " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << threadName << " finished" << std::endl;
}

void printRandomNumbers(int n, const std::string& threadName) {
    std::cout << threadName << " started" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << threadName << ": " << rand() % 100 + 1 << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << threadName << " finished" << std::endl;
}

int main() {
    int n1, n2, n3;
    std::cout << "Fibonacci";
    std::cin >> n1;
    std::cout << "Natural";
    std::cin >> n2;
    std::cout << "Random";
    std::cin >> n3;

    std::thread thread1(printFibonacci, n1, "1");
    std::thread thread2(printNaturalNumbers, n2, "2");
    std::thread thread3(printRandomNumbers, n3, "3");

    thread1.join();
    thread2.join();
    thread3.join();
    return 0;
}
