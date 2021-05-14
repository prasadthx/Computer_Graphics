#include<iostream>
#include<graphics.h>

using namespace std;

void drawCircle(int Xc, int Yc, int x, int y){
    putpixel(Xc + x, Yc + y, WHITE);
    putpixel(Xc - x, Yc + y, WHITE);
    putpixel(Xc + x, Yc - y, WHITE);
    putpixel(Xc - x, Yc - y, WHITE);
    putpixel(Xc + y, Yc + x, WHITE);
    putpixel(Xc - y, Yc + x, WHITE);
    putpixel(Xc + y, Yc - x, WHITE);
    putpixel(Xc - y, Yc - x, WHITE);
}

void BresenhamCircle(int Xc, int Yc, int radius){
    int x = 0, y = radius , P_decision_parameter;
    P_decision_parameter = 3 - 2 * radius;
    
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    do{
        drawCircle(Xc, Yc, x, y);

        delay(50);
       
        if(P_decision_parameter < 0){
            P_decision_parameter += 4 * x + 6;
        }
        else{
            P_decision_parameter += 4 * (x - y) + 10;
            y-- ;
        }
        x = x + 1;
    }while(y >= x);

    getch();

    closegraph();
}

int main(){
    cout << "Bresenham Circle Drawing Algorithm: " << endl;

    int Xc, Yc, radius;
    cout << "Enter the center point of the circle: " << endl;
    cin >> Xc;
    cin >> Yc;

    cout << "Enter the radius: " ;
    cin >> radius;

    BresenhamCircle(Xc, Yc, radius);

    return 0;


}