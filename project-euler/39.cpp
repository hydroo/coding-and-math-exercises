#include <iostream>
#include <cmath>

using namespace std;


int main(int argc, char** argv) {


    int perimeters[1000];
    memset(perimeters,0,sizeof(int)*1000);


    for (int perimeter = 2; perimeter < 1000; ++perimeter) {

        for (int a = 1; a < 501; ++a) {

            int enumerator = perimeter*perimeter*-1 + 2*perimeter*a;
            int denominator = perimeter*-2 + 2*a;

            if (denominator != 0 && enumerator % denominator == 0) {
                ++perimeters[perimeter];

                cout << perimeter << "  " << perimeters[perimeter] << endl;
            }
        }
    }


    return 0;
}

