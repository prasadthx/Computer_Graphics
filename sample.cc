
// C code to illustrate using
// graphics in linux enviornment
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
  
    circle(50, 50, 30);
  
    getch();
    closegraph();
    return 0;
}