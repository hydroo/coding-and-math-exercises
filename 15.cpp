#include <set>
#include <vector>
#include <map>
#include <iostream>

const int X = 21;
const int Y = 21;

using namespace std;


long long result = 0;


void printgrid(int* grid) {

    for (int x = 0; x < X; ++x) {

        for (int y = 0; y < Y; ++y) {
            cout << grid[x+y*Y] << ", ";
        }

        cout << endl;
    }
}


void visit(int x, int y, int *grid) {

    if ( grid[x+y*Y] == 1 ) return;
    else if (x == (X-1) && y == (Y-1)) {
        ++result;
        if (result % 10000000 == 0) {
            cout << result << endl;
            printgrid(grid);
        }
        return;
    }

    grid[x+y*Y] = 1;

    if ( y < (Y-1) ) {
        int *gridcp2 = (int*) malloc(sizeof(int)*X*Y);
        memcpy(gridcp2,grid,sizeof(int)*X*Y);
        visit(x,y+1,gridcp2);
        free(gridcp2);
    }
    if ( x < (X-1) ) {
        visit(x+1,y,grid);
    }

}





int main( int argc, char** argv) {

    int grid[X*Y];

    memset(grid,0,sizeof(int)*X*Y);

    visit(0,0,grid);

    cout << result << endl;

}

