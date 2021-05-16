#include<iostream>
#include<graphics.h>

using namespace std;

struct Tranformation{
  int coordinates[3][3] = { 
                            {100, 200, 150},
                            {200, 200, 113},
                            {1, 1, 1}                
                          };
  
  template<typename T>
  void operator *(T transformMatrix[3][3]){
    int tempArray[3][3] = {{0,0,0}, {0,0,0} , {0,0,0}};
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          for(int k = 0; k < 3; k++){
            //cout << "The count is"<< i+j << transformMatrix[i][k] << "  " << coordinates[k][j] <<endl;
            tempArray[i][j] += round(transformMatrix[i][k] * coordinates[k][j]);
          }
        }
      }
      for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
          coordinates[i][j] = tempArray[i][j];
        }
      }
  }

};

void drawline(int coordinates[3][3]){
  line(coordinates[0][0], coordinates[1][0], coordinates[0][1], coordinates[1][1]);
  line(coordinates[0][1], coordinates[1][1], coordinates[0][2], coordinates[1][2]);
  line(coordinates[0][2], coordinates[1][2], coordinates[0][0], coordinates[1][0]);
}

void translate(int Tx, int Ty, Tranformation triangle){
  int transformMatrix[3][3] = { {1, 0 , Tx} , {0 , 1, Ty}, {0 , 0 ,1} };
  triangle * transformMatrix;
  drawline(triangle.coordinates);
}

void rotate(int degrees, Tranformation triangle){
  double radians = degrees * 3.14 / 180;
  double transformMatrix[3][3] = { 
                              {cos(radians), -sin(radians), 0}, 
                              {sin(radians), cos(radians), 0}, 
                              {0, 0, 1}
                          };
  triangle * transformMatrix;  
  drawline(triangle.coordinates);                   
}

void scale(int Sx, int Sy, Tranformation triangle){
  int transformMatrix[3][3] = { {Sx, 0 , 0} , {0 , Sy, 0}, {0 , 0 ,1} };
  triangle * transformMatrix;
  drawline(triangle.coordinates);
}


int main(){
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    setcolor(WHITE);
    // line(133, 180, 232, 162);
    // line(232, 162, 168, 85);
    // line(168, 85, 133, 180);
    Tranformation triangle;

    drawline(triangle.coordinates);



    // triangle.coordinates = 

    getch();
    
    int inputChoice, Tx, Ty, angle, Sx, Sy;
    char loop;
    while (true){
      cout << "Select the transformation: " <<endl;
      cout << "1. Translation: " <<endl;
      cout << "2. Rotation: " << endl;
      cout << "3. Scaling: " << endl;

      cin >> inputChoice;

      cleardevice();

      switch (inputChoice){
        case 1:
              {
                cout << "Enter the offset: ";
                cin >> Tx >> Ty;
                translate(Tx, Ty, triangle);
                break;
              }
        case 2:
              {
                cout << "Enter the angle: ";
                cin >> angle;
                rotate(angle, triangle);
                break;
              }     
        case 3:
              {
                cout << "Enter the scale factor: ";
                cin >> Sx >> Sy;
                scale(Sx, Sy, triangle);
                break;
              }       
      }
      cout << "Do you wish to continue? y/n";
      cin >> loop;
      if (loop == 'n'){
        break;
      }
      //break;
    }

    getch();

    closegraph();

    return 0;
}

//clang++ -o 2dTransformation 2dTransformation.cc -lgraph