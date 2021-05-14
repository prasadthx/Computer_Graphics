#include<iostream>
#include<graphics.h>

using namespace std;

int main(){
    int edges,
        Ymax = 0;
    cout << "Enter the number of edges of Polygon: " ;
    cin >> edges;

    int (*coordinates)[2] = new int[edges + 1][2];
    float *slope = new float[edges];

    for(int i = 0; i < edges; i++){
        cout << "Enter the coordinate: " ;
        cin >> coordinates[i][0] ;
        cin >> coordinates[i][1];
        if(coordinates[i][1] > Ymax){
            Ymax = coordinates[i][1];
        }
    }

    coordinates[edges][0] = coordinates[0][0];
    coordinates[edges][1] = coordinates[0][1];

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    for (int i = 0; i < edges; i++)
    {
        line(coordinates[i][0], coordinates[i][1], coordinates[i + 1][0], coordinates[i + 1][1]);
    }

    int dy, dx;

    for(int i = 0; i < edges; i++){
        dy = coordinates[i + 1][1]  - coordinates[i][1];
        dx = coordinates[i + 1][0] - coordinates[i][0];

        if(dx == 0){
            slope[i] = 0.0;
        }
        if(dy == 0){
            slope[i] = 1.0;
        }

        if((dy != 0) && (dx != 0)){
            slope[i] = (float) dx / dy;
        }
    }

    int k, temp, Xi[20];
    for(int y = 0; y <= Ymax ; y++){
        k = 0;
        
        for(int i = 0; i < edges; i++){
            if(((coordinates[i][1] <= y) && (coordinates[i + 1][1] > y)) ||
                ((coordinates[i][1] > y) && (coordinates[i + 1][1] <= y))
            ){
                Xi[k] = (int) (coordinates[i][0] + slope[i] * (y - coordinates[i][1]));
                k++;
            }
        }

        for(int j = 0; j < k - 1; j++){
            for(int i = 0; i < k - 1; i++){
                if(Xi[i] > Xi[i + 1]){
                    temp = Xi[i];
                    Xi[i] = Xi[i + 1];
                    Xi[i + 1] = temp;
                }
            }
        }

        setcolor(WHITE);
            for(int i = 0; i < k; i += 2){
                delay(50);
                line(Xi[i], y, Xi[i + 1] + 1, y);
            }

    }

    getch();

    closegraph();

    return 0;
    
}