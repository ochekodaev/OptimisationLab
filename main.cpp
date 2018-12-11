#include <Windows.h>

#define opt

#define ROW 10000
#define COL 10000

unsigned int Data[ROW][COL];
unsigned int Data2[ROW][COL];

int Calculations (int i) {
    if (i % 2 == 0) {
        return COL;
    } else {
        return COL / 2;
    }
}

int main()
{
#ifdef opt
#pragma simd
#endif
    for (int j = 0; j < ROW; j++) {
#ifdef opt
#pragma novector
#endif
        for (int i = 0; i < COL; i++) {
            Data[j][i] = i * j;
            Data2[j][i] = i * j;
        }
    }

    //LoopDependencies
#ifndef opt
    for (int j = 0; j < ROW; j++) {
        for (int i = 0; i < COL - 1; i += 1) {
            Data[j][i + 1] = Data[j][i] + Data2[j][i];
        }
    }
#endif
    //

    
    //function calls
    for (int j = 0; j < ROW; j++) {
#ifdef opt
        int n = Calculations(j);
        for (int i = 0; i < n; i++) {
            Data[j][i] = i * j;
        }
#elif
        for (int i = 0; i < Calculations(j); i++) {
            Data[j][i] = i * j;
        }
#endif
    }
    //

    return 0;
};