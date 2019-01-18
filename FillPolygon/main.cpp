//
//  main.cpp
//  FillPolygon
//
//  Created by Madelyn Reyes on 10/19/17.
//  Copyright © 2017 Madelyn Reyes. All rights reserved.
//


#include <iostream>
#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

void init(void){
    glClearColor(.60,.87,.46,0.5);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,500.0, 0.0, 400.0);
    
}

class LineBres {
    
public:
    double x1;
    int y1;
    int x2;
    int y2;
    double slope;
    double dx;
    double dy;
    int yMax;
    int yMin;
    bool active = false; //ayy dr arisoa
    int sign;
    double xIncrement;
   LineBres(int X1, int Y1, int X2, int Y2){
        x1 = X1; //edge shortening
        y1 = Y1;
        x2 = X2;
        y2 = Y2;
         dy = double(y2 - y1);
         dx = double(x2 - x1);
        slope = double(dy/dx);
         xIncrement = (1.0/ slope); //  1/m
       if(y1 > y2){
           yMax = y1;
           yMin = y2;
       }
       else{
           yMax = y2;
           yMin = y1;
       }
        if(slope == 0){
           sign = 0;
       }
       else if(slope > 0){
           sign = 1;
       } else{
           sign = -1;
       }
    
    }
    void printDetails(void){
        cout << x1 <<  " " <<  y1 << " " << x2 << " " << y2 << " " << slope << " " << xIncrement <<  endl;
    }
};
inline int round (const float a)  { return int (a + 0.5); }



void setPixel (GLint xCoord, GLint yCoord)
{
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2i (xCoord, yCoord);
    glEnd();
}



void drawlineBres (int x1, int y1, int x2, int y2)
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
    else{  //here we know slope is not undefined
        
        double xs = x2 - x1;
        double ys = y2 - y1;
        double m = ys/ xs;
         // cout << "m " << m << endl;
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

void fillPolygon(){
}

void displayScene(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);  //ten vertices
    vector<LineBres> filterHorizontal;
    vector<LineBres> EdgeLines;
    vector<int> activeEdge;
    
    filterHorizontal.push_back(LineBres(50,50,300,50));
    filterHorizontal.push_back(LineBres(50,50,55,200));
    filterHorizontal.push_back(LineBres(55,200,70,180));
    filterHorizontal.push_back(LineBres(70,180,80,250));
    filterHorizontal.push_back(LineBres(80,250,98,150));
    filterHorizontal.push_back(LineBres(98,150,200,120));
    filterHorizontal.push_back(LineBres(200,120,205,210));
    filterHorizontal.push_back(LineBres(205,210,220,112));
    filterHorizontal.push_back(LineBres(220,112,250,160));
    filterHorizontal.push_back(LineBres(250,160,300,50));
    //cout << filterHorizontal.size() << endl;
    
    for(int i =0; i < filterHorizontal.size(); i++){  //push to initial vector
       // cout << filterHorizontal.at(i).slope << "\n";
        
        if(filterHorizontal.at(i).slope != 0){ //eliminate horizontal lines
           // int x1 = EdgeLines.at(i).x1;
            //int y1 = EdgeLines.at(i).y1;
            int x2Temp = filterHorizontal.at(i).x2;
            int y2Temp = filterHorizontal.at(i).y2;
           if(filterHorizontal.at(i).y1 > filterHorizontal.at(i).y2){
              // cout << filterHorizontal.at(i).y1 << "\n";
                filterHorizontal.at(i).x2 = filterHorizontal.at(i).x1; //if y1 > y2, y2 = y1, x2 = x1
                filterHorizontal.at(i).y2 = filterHorizontal.at(i).y1; //new y2, x2
              // int x2 = EdgeLines.at(i).x2;
               //int y2 = EdgeLines.at(i).y2;
                filterHorizontal.at(i).x1 = x2Temp;
                filterHorizontal.at(i).y1 = y2Temp;
            }
            EdgeLines.push_back(filterHorizontal.at(i));
        }
    }
    
     //sorting the ye olde edges
        sort(EdgeLines.begin(),EdgeLines.end(), [](const LineBres& a, const LineBres& b){
            return a.y1 < b.y1;
        });
 
 
    int yMin = EdgeLines.at(0).y1;
    
    for(int f =0; f < EdgeLines.size(); f++){
        EdgeLines.at(f).printDetails();
    }
    
    //last element of y1 can be compared with elements of y2 to get yMax
    int yMax = EdgeLines.at((EdgeLines.size() -1)).y1;
    for(int m =0; m < EdgeLines.size(); m++){
        if(EdgeLines.at(m).y2 > yMax){
            yMax = EdgeLines.at(m).y2;
        }
    }
    
    for(int y = yMin; y < yMax; y++){
        vector<int> xVals; // holds dem x values. i choose camelCase
        for(int l = 0; l < EdgeLines.size(); l++){
            if(EdgeLines.at(l).y1 <= y && y < EdgeLines.at(l).y2){ //if y is between y1 & y2
                EdgeLines.at(l).active = true; //this is an active edge
                
            }
        }
        for(int e =0; e < EdgeLines.size(); e++){
            if(EdgeLines.at(e).active){ //if its active, push it into ye olde vector
                xVals.push_back(EdgeLines.at(e).x1);
                EdgeLines.at(e).x1 += EdgeLines.at(e).xIncrement;
                EdgeLines.at(e).active = false;
               // cout << EdgeLines.at(e).x1 << " ";
            }
        }
        
        sort(xVals.begin(), xVals.end());
        for(int d = 0; d < xVals.size(); d+= 2){ //pairing dem bois
            drawlineBres(xVals.at(d),y, xVals.at(d+1),y);
        }

    }

//    drawlineBres(50,50,300,50); //points are clockwise
//    drawlineBres(50,50,55,200);
//    drawlineBres(55,200,70,180);
//    drawlineBres(70,180,80,250);
//    drawlineBres(80,250,98,150);
//    drawlineBres(98,150,200,120);
//    drawlineBres(200,120, 205,210);
//    drawlineBres(205,210,220,112);
//    drawlineBres(220,112,250,160);
//    drawlineBres(250,160,300,50);

    glFlush();


  
}


int main(int argc,  char ** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(30,30);
    glutInitWindowSize(500,400);
    glutCreateWindow("Dat fill doe");
    init();
    glutDisplayFunc(displayScene);
    glutMainLoop();
    
}
