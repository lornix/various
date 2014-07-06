#include <iostream>
#include <regex>

int main ()
{
    std::regex r("st|mt|tr");
    std::cerr << "st|mt|tr" << " matches st? " << std::regex_match("st", r) << std::endl;
    std::cerr << "st|mt|tr" << " matches mt? " << std::regex_match("mt", r) << std::endl;
    std::cerr << "st|mt|tr" << " matches tr? " << std::regex_match("tr", r) << std::endl;
}
