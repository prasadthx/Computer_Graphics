#include<iostream>
#include<graphics.h>

using namespace std;

static int Xmin, Ymin, Xmax, Ymax;

struct RegionCode{
    int x, y;
    int code[4] = {0, 0, 0, 0};

    bool isInside(){
        for(int i = 0; i < 4; i++){
            if(code[i] == 1){
                return false;
            }
        }
        return true;
    }

    bool passesThrough(RegionCode otherPoint){
        for(int i = 0; i < 4; i++){
            if(code[i] && otherPoint.code[i]){
                return false;
            }
        }
        return true;
    }

    int findNewX(){
        if(code[2] == 1){
            x = Xmax;
        }
        if(code[3] == 1){
            x = Xmin;
        }
    }

    int findNewY(){
        if(code[0] == 1){
            y = Ymin;
        }
        if(code[1] == 1){
            y = Ymax;
        }
    }
};

RegionCode getCode(int x, int y){
    RegionCode bitcode;

    bitcode.x = x;
    bitcode.y = y;
    
    if(x < Xmin){
        bitcode.code[3] = 1;
    }
    if(x > Xmax){
        bitcode.code[2] = 1;
    }
    if(y < Ymin){
        bitcode.code[0] = 1;
    }
    if(y > Ymax){
        bitcode.code[1] = 1;
    }

    return bitcode;
}

int main(){
    int x1, y1, x2, y2;
    
    cout << "Enter the clipping window coordinates: " ;
    cin >> Xmin >> Ymin >> Xmax >> Ymax;

    cout << " Enter the line coordinates: " ;
    cin >> x1 >> y1 >> x2 >> y2;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    
    setcolor(WHITE);
    rectangle(Xmin, Ymin, Xmax, Ymax);
    line(x1, y1, x2, y2);

    getch();
    
    RegionCode code1, code2;

    code1 = getCode(x1, y1);
    code2 = getCode(x2, y2);

    bool isInside = false;
    float slope;
    RegionCode *outsideRegion, *insideRegion;

    while (true)
    {
        if (code1.isInside() && code2.isInside()){
            outsideRegion = &code2;
            insideRegion = &code1;
            isInside = true;
            break;
        }
        else if (!(code1.passesThrough(code2))){
            break;
        }
        else if (code1.passesThrough(code2)){
            cout << "Is isInside"<<endl;
            slope = (float) (y2 - y1) / (x2 - x1);
            isInside = true;
            // while(!(code1.isInside() && code2.isInside())){
                if(code1.code[0] == 1){
                    code1.y = Ymin;
                    cout << "1. 1 y is "<<code1.y << endl;
                    code1.x = code2.x + (code1.y - code2.y) / slope;
                    cout << "1 x is "<<code1.y << endl;
                    code1.code[0] = 0;
                }
                if(code2.code[1] == 1){
                    code2.y = Ymax;
                    cout << "2. 2 y is "<<code2.y << endl;
                    code2.x = code1.x + (code2.y - code1.y) / slope;
                    cout << "2 x is "<<code2.x << endl;
                    code2.code[1] = 0;
                }
                if(code1.code[2] == 1){
                    code1.x = Xmax;
                    cout << "3. 1 x is "<<code1.x << endl;
                    code1.y = code2.y + slope * (code1.x - code2.x);
                    cout << "1 y is "<<code1.y << endl;
                    code1.code[2] = 0;
                }
                if(code1.code[3] == 1){
                    code1.x = Xmin;
                    cout << "4. 1 x is "<<code1.x << endl;
                    code1.y = code2.y + slope * (code1.x - code2.x);
                    cout << "1 y is "<<code1.y << endl;
                    code1.code[3] = 0;
                }
                if(code2.code[2] == 1){
                    code2.x = Xmax;
                    cout << "5. 2 x is "<<code2.x << endl;
                    code2.y = code1.y + slope * (code2.x - code1.x);
                    cout << "2 y is "<<code2.y << endl;
                    code2.code[2] = 0;
                }
                if(code2.code[3] == 1){
                    code2.x = Xmin;
                    cout << "6. 2 x is "<<code2.x << endl;
                    code2.y = code1.y + slope * (code2.x - code1.x);
                    cout << "2 x is "<<code2.y << endl;
                    code2.code[3] = 0;
                }
       //      }
        }
        break;
    }
    cleardevice();
    outsideRegion = &code2;
    insideRegion = &code1;
    outsideRegion->x = round(outsideRegion->x);
    outsideRegion->y = round(outsideRegion->y);
    insideRegion->x = round(insideRegion->x);
    insideRegion->y = round(insideRegion->y);
    rectangle(Xmin, Ymin, Xmax, Ymax);
    if(isInside){
        cout << "Inside" << endl;
        line(insideRegion->x, insideRegion->y, outsideRegion->x, outsideRegion->y);
    }

    getch();
    closegraph();
    return 0;
}

//clang++ -o CohenSutherland CohenSutherland.cc -lgraph