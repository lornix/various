#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include <ratio>

const int noElements = 50000;
// const int noIterations = 500;
const int noIterations = 1;

using namespace std::chrono;

void testVector()
{
    std::cout << "std::vector:" << std::endl;

    volatile unsigned long long sum = 0;

    std::vector<unsigned int> vec;
    vec.resize(noElements);

    steady_clock::time_point start = steady_clock::now();

    for(int i=0; i<noIterations; i++){

        for(int i=0; i<noElements; i++){
            vec[i] = i;
        }

        for(int i=0; i<noElements; i++){
            sum += (3 * vec[i]);
        }
    }

    steady_clock::time_point finish = steady_clock::now();

    duration<double> time_span = duration_cast<duration <double> >(finish - start);

    std::cout << "\t\t" << time_span.count() << std::endl;
}

void testRawArray()
{
    std::cout << "raw array:" << std::endl;

    volatile unsigned long long sum = 0;

    unsigned int myRawArray[noElements];

    steady_clock::time_point start = steady_clock::now();

    for(int i=0; i<noIterations; i++){

        for(int i=0; i<noElements; i++){
            myRawArray[i] = i;
        }

        for(int i=0; i<noElements; i++){
            sum += (3 * myRawArray[i]);
        }
    }

    steady_clock::time_point finish = steady_clock::now();

    duration<double> time_span = duration_cast<duration <double> >(finish - start);

    std::cout << "\t\t" << time_span.count() << std::endl;
}

void testStdArray()
{
    std::cout << "std::array:" << std::endl;

    volatile unsigned long long sum = 0;

    std::array<unsigned int, noElements> myStdArray;

    steady_clock::time_point start = steady_clock::now();

    for(int i=0; i<noIterations; i++){

        for(int i=0; i<noElements; i++){
            myStdArray[i] = i;
        }

        for(int i=0; i<noElements; i++){
            sum += (3 * myStdArray[i]);
        }
    }

    steady_clock::time_point finish = steady_clock::now();

    duration<double> time_span = duration_cast<duration <double> >(finish - start);

    std::cout << "\t\t" << time_span.count() << std::endl;
}

int main()
{
    steady_clock::time_point start = steady_clock::now();

    testVector();
    testRawArray();
    testStdArray();

    steady_clock::time_point finish = steady_clock::now();

    duration<double> time_span = duration_cast<duration <double> >(finish - start);

    std::cout << "Time elapsed:\n\t\t" << time_span.count() << std::endl;
}
