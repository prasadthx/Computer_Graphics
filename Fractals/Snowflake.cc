#include<iostream>
#include<graphics.h>

using namespace std;

void snowflake(int x1, int y1, int x2, int y2, int it){
    float angle = -60 * M_PI / 180;
    
    int x3 = (2 * x1 + x2) / 3,
        y3 = (2 * y1 + y2) / 3;

    int x4 = (2 * x2 + x1) / 3,
        y4 = (2 * y2 + y1) / 3;

    int x = x3 + (x4 - x3) * cos(angle) + (y4 - y3) * sin(angle);    
    int y = y3 + (y4 - y3) * cos(angle) - (x4 - x3) * sin(angle);

    if(it > 0){
        snowflake(x1, y1, x3, y3, it - 1);
        snowflake(x3, y3, x, y, it - 1);
        snowflake(x, y, x4, y4, it - 1);
        snowflake(x4, y4, x2, y2, it - 1);
    }
    else{
        line(x1, y1, x3, y3);
        line(x3, y3, x, y);
        line(x, y, x4, y4);
        line(x4, y4, x2, y2);
    }
}

int main(){
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    int x1 = 100, y1= 200, x2 = 200, y2 = 200, x3 = 150, y3 = 113;
    snowflake(x1, y1, x2, y2, 1);
    snowflake(x2, y2, x3, y3, 1);
    snowflake(x3, y3, x1, y1, 1);
    getch();
    closegraph();
    return 0;
}

//clang++ -o Snowflake Snowflake.cc -lgraph