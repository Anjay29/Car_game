#include <windows.h>  
  #include <iostream>  
  #include <thread>  
  using namespace std;  
    
  void gotoXY(int x, int y)  
 {  
  COORD coord;  
  coord.X = x;  
   coord.Y = y;  
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);  
  }  
    
  int matrix[8][20];  
  void drawPoint(int x, int y){  
    if(y<20 & y>=-0){  
      matrix[x][y]=1;  
    }  
  }  
  void resetBoard(){  
    for(int j=0;j<20;j++){  
      for(int i=1;i<7;i++){  
        matrix[i][j]=0;  
      }  
    }  
  }  
    
  /*  
  SOME IMPORTANT CLASSES (GAME ELEMENTS)  
  */  
  class EnemiesCar{  
  public:  
  EnemiesCar(){  
    xPos=5;  
    yPos=-3;  
  }  
  int xPos;  
  int yPos;  
  void appear(){  
   if(yPos==20){  
    int randomNo=rand()%2;  
    if(randomNo==0){  
      xPos=2;  
    }  
    else {  
      xPos=5;  
    }  
    yPos=-3;  
    }  
  }  
  void draw(){  
    drawPoint(xPos,yPos);  
    drawPoint(xPos-1,yPos+1);  
    drawPoint(xPos+1,yPos+1);  
    drawPoint(xPos,yPos+1);  
    drawPoint(xPos,yPos+2);  
    drawPoint(xPos-1,yPos+3);  
    drawPoint(xPos+1,yPos+3);  
    drawPoint(xPos,yPos+3);  
  }  
  void move(){  
    yPos++;  
  }  
    
  };  
    
  /////////////////////////////////////////  
  class car{  
  public:  
  int xPos;  
  int yPos;  
  car(){  
    xPos=2;  
    yPos=16;  
  }  
  void draw(){  
    drawPoint(xPos,yPos);  
   drawPoint(xPos-1,yPos+1);  
   drawPoint(xPos+1,yPos+1);  
   drawPoint(xPos,yPos+1);  
   drawPoint(xPos,yPos+2);  
   drawPoint(xPos-1,yPos+3);  
   drawPoint(xPos+1,yPos+3);  
   drawPoint(xPos,yPos+3);  
 }  
 void moveLeft(){  
   xPos=2;  
 }  
 void moveRight(){  
   xPos=5;  
 }  
 void checkCollusion(EnemiesCar *EC, bool *running){  
   if(EC->xPos==xPos & EC->yPos>13){  
     *running=false;  
   }  
 }  
 };  
 //////////////////////////////////////  
 //Listens to keyboard inputs  
  void myListener(car *c){  
    while(1){  
       if (GetAsyncKeyState(VK_LEFT) & (0x8000 != 0)){  
           c->moveLeft();  
         }  
       else if (GetAsyncKeyState(VK_RIGHT) & (0x8000 != 0)){  
           c->moveRight();  
         }  
   }  
 }  
   
 /////////////////////////////  
 void startGame(){  
   car mycar=car();  
   EnemiesCar myEnmCar=EnemiesCar();  
   // starts the second thread (The input listener )  
   thread mySecondThread(myListener, &mycar);  
   // This is the game engine/game loop  
   bool running=true;  
   while(running){  
     resetBoard();  
     myEnmCar.appear();  
     myEnmCar.draw();  
     myEnmCar.move();  
     mycar.draw();  
     mycar.checkCollusion(&myEnmCar,&running);  
   
     for(int j=0;j<20;j++){  
       for(int i=0;i<8;i++){  
         if(i==0 | i==7){  
             gotoXY(i,j);  
             cout<<"0";  
                 }  
         else if(matrix[i][j]==1){  
             gotoXY(i,j);  
             cout<<"0";  
                 }  
         else {  
           gotoXY(i,j);  
           cout<<" ";  
             }  
           }  
         }  
   
     Sleep(50);  
   }  
   //The game ended  
   
    //Show the Game Over  
    Sleep(1000);  
    system("cls");  
    gotoXY(5,4);  
    cout<<"GAME OVER!!!";  
    gotoXY(5,5);  
    cout<<"By:Anjay";  
    gotoXY(5,6);  
    cout<<"ARK";  
    gotoXY(0,0);  
    Sleep(10000);  

    // Kills the second thread  
    mySecondThread.detach();  
  }  

  int main()  
  {  


        startGame();  
    return 0;  
  } 
