#include <iostream>

using namespace std;

class Clingons
{
 public:
     void clingForever()
     {
         cout << "Qapla" << endl;
     }
};

int main()
{
    Clingons cling;
    cling.clingForever();
    return 0;
}
