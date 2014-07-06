#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

const double C1   =     1.0f;
const double C2   =     2.0f;
const double C10  =    10.0f;
const double C11  =    11.0f;
const double C10k = 10000.0f;

int main(int argc, char* argv[])
{
    if (argc<2) {
        puts("need a number to calculate square root");
        exit(1);
    }

    setlocale(LC_NUMERIC,"");
    setvbuf(stdout,0,_IONBF,0);

    int counter=0;
    double value=strtod(argv[1],0);
    double startvalue=value;
    double pt=C1;
    int p=0;
    while (p<8) {
        pt=pt*C10;
        p++;
    }
    double denom=C1*pt;
    while (p>=0) {
        while (value>=0) {
            value-=denom;
            denom+=C2*pt;
            counter++;
        }
        p--;
        pt=pt/C10;
        value*=C10;
        denom-=C11*pt;
        while (value<0) {
            value+=denom;
            denom-=C2*pt;
            counter++;
        }
        p--;
        pt=pt/C10;
        value*=C10;
        denom+=C11*pt;
    }
    double result=denom/C2/C10k;
    double square=result*result;
    printf("StartValue: %'.12f\n",startvalue);
    printf("Result^2:   %'.12f\n",square);
    printf("Result:     %'.12f\n",result);
    printf("Counter:    %d\n",counter);

    return 0;
}
