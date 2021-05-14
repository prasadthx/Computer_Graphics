#include<iostream>
#include<graphics.h>

using namespace std;

void drawDDALine(){

}

int main(){
    int x1, y1,
        x2, y2;

    cout << "DDA Line Drawing Algorithm" << endl;

    cout << "Enter the first co-ordinate: " ;
    cin >> x1;
    cin >> y1;

    cout << "Enter the second co-ordinate: ";
    cin >> x2;
    cin >> y2;

    int dx = x2 - x1,
        dy = y2 - y1,
        steps;

    if(abs(dx) > abs(dy)){
        steps = abs(dx);
    }
    else{
        steps = abs(dy);
    }    

    float Xinc = (float) dx / steps,
          Yinc = (float) dy / steps;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    for(int i = 0; i < steps; i++){
        x1 += Xinc;
        y1 += Yinc;
        putpixel(round(x1), round(y1), WHITE);
    }      

    getch();

    closegraph();

    return 0;

}