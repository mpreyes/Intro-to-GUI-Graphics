//
//  main.cpp
//  HW5LineAlgorithm
//
//  Created by Madelyn Reyes on 10/12/17.
//  Copyright © 2017 Madelyn Reyes. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <math.h>

using namespace std;
void init(void){
    glClearColor(.60,.87,.46,0.5);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,500.0, 0.0, 400.0);
}


inline int round (const float a)  { return int (a + 0.5); }

void setPixel (GLint xCoord, GLint yCoord)
{
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2i (xCoord, yCoord);
    glEnd();
}

void lineDDA(int x1, int y1, int x2, int y2){
    
    //make sure to test for slope. where it is located
    //if its negative, switch of the y and the x
    //for line with positive slope greater than 1.0, we interchange the role of x and y
    //
    int dx= (x2-x1);
    int dy= (y2-y1);
    int steps, k;
    float xIncrement, yIncrement;
    float x = x1, y = y1;
    if (fabs (dx) > fabs (dy)){
        steps = fabs (dx);
    }
    else{
        steps = fabs (dy);
    }
    xIncrement = float (dx) / float (steps);
    yIncrement = float (dy) / float (steps);
    
    setPixel (round (x), round (y));
    for (k = 0; k < steps; k++) {
        x += xIncrement;
        y += yIncrement;
        setPixel (round (x), round (y));
    
    }
}

void lineBres (int x1, int y1, int x2, int y2)
{

        //if dx =0, no change in x, vertical line
        //if dy = 0, no change in y, horizontal line
        //negative slope -> one coordinate decreases (y), the other increases (x)
        //positive slope > 1, exchange roles of x and y
    double dx = fabs(x2 - x1);
    double dy = fabs(y2 - y1);
    int p = (2 *dy) -dx;
    int x = x1;
    int y = y1;

    if(dy == 0){ //horizontal line
      //  cout << "horizontal line" << endl;
        for( x = x1; x < x2; x++){ //since we draw from left to right, only case to handle
            setPixel(x, y);
        }
    }
    else if(dx == 0){ //vertical line
       // cout << "vertical line " << endl;
        if(y1 < y2){
        for(y = y1; y < y2 ;y++){
            setPixel(x, y);
        }
        }
        else{
            for(int y = y2; y < y1 ;y++){
                setPixel(x, y);
            }
        }
    }
  //  dx = x2 - x1;
    else{
        double xs = x2 - x1;
        double ys = y2 - y1;
    double m = ys/ xs;
       //  cout << "m " << m << endl;
         if(m > 1){ //positive slopes greater than 1
          //    cout << "slope greater than 1" << endl;
        if (y1 > y2) {
            x = x2;
            y = y2;
            y2 = y1;
        }
        else {
            x = x1;
            y = y1;
        }
            setPixel (x, y);
            while (y < y2) {
                y++;
                if (p < 0)
                    p += 2*dx;
                else {
                    x++;
                    p += 2*(dx - dy);
                }
                setPixel (x, y);
            }
            
            
         }

      else if(m < 0 && m >= -1.0 ){ //slope between 0 and -1
       //  cout << "slope between -1 and 0" << endl;
        if (x1 > x2) {
            x = x2;
            y = y2;
            x2 = x1;
        }
        else {
            x = x1;
            y = y1;
        }
        setPixel (x, y);
        while (x < x2) {
            x++;
            if (p < 0)
                p += 2*dy;
            else {
                y--;
                p += 2*(dy - dx);
            }
            setPixel (x, y);
        }
        
    }
    else if(m < -1.0 ){ //negative slope less than -1
      //  cout << "slope less than -1" << endl;
        if (y1 > y2) {
            x = x2;
            y = y2;
            y2 = y1;
    
        }
        else {
            x = x1;
            y = y1;
        }
        setPixel (x, y);
        while (y < y2) {
            y++;
            if (p < 0)
                p += 2*dx;
            else {
                x--;
                p += 2*(dx - dy);
            }
            setPixel (x, y);
        }
        
    }
    else if(m > 0 && m <= 1){ // positve slope less than 1
   // else{
       // cout << "slope between 0 and 1" << endl;
        if (x1 > x2) {
            x = x2;
            y = y2;
            x2 = x1;
        }
        else {
            x = x1;
            y = y1;
        }
        
            setPixel (x, y);
            while (x < x2) {
                x++;
                if (p < 0)
                    p += 2*dy;
                else {
                    y++;
                    p += 2*(dy - dx);
                }
                setPixel (x, y);
            }
        
    }
    
    }
    
}

void displayBresenham(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
//    glColor3f (0.0, 0.0, 0.0);
//    lineBres(60,60, 100,60); //horizontal line
//     glColor3f (1.0, 0.0, 0.0);
//    lineBres(200, 200, 300, 100); //negative slope
//     glColor3f (0.0, 1.0, 0.0);
//    lineBres(100, 100, 200, 200); //positve slope
//    glColor3b(1.0, 0.0, 0.0);
//    lineBres(300,300,300,100); //vertical line
   // house 1
    glColor3f (0.0, 0.0, 0.0);
    lineBres(5,5,5,20);
    lineBres(5,20,47,20);
    lineBres(47,5,47,20);
    lineBres(5,5,47,5);
    lineBres(5,20,26,41); //slope is 1
    lineBres(26,41,47,20);
   // house 2
    glColor3f (0.6, 0.4, 0.3);
    lineBres(55,5,55,20);
    lineBres(55,20,97,20);
    lineBres(97,5,97,20);
    lineBres(55,5,97,5);
    lineBres(55,20,76,100);
    lineBres(76,100,97,20);
   // house 3
    glColor3f (0.6, 0.0, 0.3);
    lineBres(105,5,105,20);
    lineBres(105,20,147,20);
    lineBres(147,5,147,20);
    lineBres(105,5,147,5);
    lineBres(105,20,126,25);
    lineBres(126,25,147,20);
    //star
    glColor3f(1.0,1.0,0.0);
    lineBres(105,100,147,100); //horizontal line
    lineBres(126,76,126,124); //vertical line
    lineBres(147,124,105,76); //+slope greater than 1
    lineBres(105,124,147,76); //negative slope less than -1
    lineBres(137,76,116,124); //negative slope less than -1
    lineBres(137,124,116,76); //+slope greater than 1
    lineBres(147,88,105,112); //negative slope between 0 and -1
    lineBres(147,112,105,88); //positive slope between 0 and 1
    
    glFlush();
    
}
void displayDDA(void){
    glClear(GL_COLOR_BUFFER_BIT);
    //house 1
    glColor3f (0.0, 0.0, 0.0);
    lineDDA(5,5,5,20);
    lineDDA(5,20,47,20);
    lineDDA(47,5,47,20);
    lineDDA(5,5,47,5);
    lineDDA(5,20,26,41);
    lineDDA(26,41,47,20);
    //house 2
    glColor3f (0.6, 0.4, 0.3);
    lineDDA(55,5,55,20);
    lineDDA(55,20,97,20);
    lineDDA(97,5,97,20);
    lineDDA(55,5,97,5);
    lineDDA(55,20,76,100);
    lineDDA(76,100,97,20);
    //house 3
    glColor3f (0.6, 0.0, 0.3);
    lineDDA(105,5,105,20);
    lineDDA(105,20,147,20);
    lineDDA(147,5,147,20);
    lineDDA(105,5,147,5);
    lineDDA(105,20,126,25);
    lineDDA(126,25,147,20);
    //star
    glColor3f(1.0,1.0,0.0);
    lineDDA(105,100,147,100);
    lineDDA(126,76,126,124);
    lineDDA(147,124,105,76);
    lineDDA(105,124,147,76);
    lineDDA(137,76,116,124);
    lineDDA(137,124,116,76);
    lineDDA(147,88,105,112);
    lineDDA(147,112,105,88);
    glFlush();
    
}
int main(int argc,  char ** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(30,30);
    glutInitWindowSize(500,400);
    glutCreateWindow("Dem houses doe");
    init();
    //glutDisplayFunc(displayDDA);
    glutDisplayFunc(displayBresenham);
    glutMainLoop();
    
}
