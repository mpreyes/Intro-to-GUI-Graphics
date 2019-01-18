//
//  main.cpp
//  HW4PieAndBar
//
//  Created by Madelyn Reyes on 9/30/17.
//  Copyright © 2017 Madelyn Reyes. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <cmath>
#include <queue>

using namespace std;
GLint yRaster = 150;
GLint xRaster = 25;
const GLdouble twoPi = 6.283185;
const GLdouble Pi = 3.14159265;
//GLint hiddenCircleX = 0;
//GLint hiddenCircleY = 0;
GLfloat pieControlSize = 0;
GLfloat textControlSize = 0;

vector <double> mainX;
vector <double> mainY;

//GLsizei winWidth = GLUT_WINDOW_WIDTH, winHeight = GLUT_WINDOW_HEIGHT;
GLsizei winWidth = 300, winHeight = 300;

void init(void){
    glClearColor(.60, .77, .46, 0.5);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,800.0,0.0,700.0);
    
}

typedef struct {
    double x;
    double y;
}CIRCLE;
CIRCLE circle;

class screenPt {
public:
    GLdouble x, y;
public:
    /*  Default Constructor: initializes coordinate position to (0, 0).  */
    screenPt (){
        x = y = 0; }
};


void displayBar(void){
   
    glClear(GL_COLOR_BUFFER_BIT);

            ifstream file("/Users/madelynreyes/Desktop/test3.txt");
            //string testcase;
            string line;
    
            vector<int> data;
            vector<string> label;
            while(getline(file,line)){
                istringstream iss(line);
                string s;
                int i;
                
                while(iss >> i && iss >> s){
                    data.push_back(i);
                    label.push_back(s);
                }
              
                }
                 file.close();
                int n = data.size();
    

   
    GLint fruit, k;
    string hold;
    glColor3f (0.0, 0.0, 1.0);     //  Set bar color to blue.
    for (k = 0; k < n; k++){
        glRecti(30 + k*60, 175, 50 + k*60,data.at(k) +220);
    }
    glColor3f (0.0, 0.0, 0.0); //Set text color to black.
     xRaster = 24; // Display chart labels.
    for (fruit = 0; fruit < n; fruit++) { //number of fruits
         hold = label[fruit]; //iterating over that fruit
         glRasterPos2i (xRaster, yRaster);
        for (int p =0; p < label[fruit].length(); p++){
            glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, hold[p]);
        
                                 xRaster += 9;
        }
        }
    


        glFlush();
}


void setCircle(int x, int y, int r, int ptSize){ //my own circle function
    static const double PI = 3.1415926535;
    double i;
    double angle;
    double x1;
    double y1;
    
    glPointSize(ptSize);
    glBegin(GL_POINTS);
    // glVertex2i(200,30);
    // glPointSize(3);
    for( i =0; i < 360; i += 0.1){
        angle = i;
        x1 = r * cos(angle * PI / 180);
        y1 = r * sin(angle * PI / 180);
        glVertex2i(x+ x1, y + y1);
    }
    glEnd();
   // glFlush();
}

vector<float> xpts;
vector <float> ypts;


void displayPie(void){


    // glClear (GL_COLOR_BUFFER_BIT);
    
    GLint xRast = 0;
    GLint yRast = 0;
    
            ifstream file("/Users/madelynreyes/Desktop/test3.txt");
            //string testcase;
            string line;
            //int n = stoi(line);
    
            vector<int> data;
            vector<string> label;
    
            while(getline(file,line)){
                istringstream iss(line);
                string s;
                int i;
                while(iss >> i && iss >> s){
                     data.push_back(i);
                     label.push_back(s);
                }
    
    
            }
    
    
    int n = data.size();


        pieControlSize = 1.1;
        textControlSize = 1.45;
    

    screenPt circCtr, piePt;
    GLint radius = (winWidth / 4) * pieControlSize;
    GLint Tradius = (winWidth / 4) * textControlSize;
    // Circle radius.
    GLdouble sliceAngle, previousSliceAngle = 0.0;
    GLint k, nSlices = n;                     // Number of slices.
    GLfloat dataSum = 0.0;
    circCtr.x = winWidth / 2;                  // Circle center position.
    circCtr.y = winHeight / 2;
    
   
for (k = 0; k < nSlices; k++){
      dataSum += data[k];
    
        }
    
    vector<double> totals;
    for(int i=0; i < data.size();i++){
        double total =(data[i]/dataSum) * twoPi; //gives total lengths of each data segment
        totals.push_back(total);
    }
    
    for (k = 0; k < nSlices; k++) {

        sliceAngle = twoPi * data[k] / dataSum + previousSliceAngle;

        piePt.x = circCtr.x + radius * cos(sliceAngle);
        piePt.y = circCtr.y + radius * sin(sliceAngle);
        
       // cout << piePt.x << endl;
        
        
      
//                double i, angle, x1, y1;
//                for( i =0; i < 360; i += .1){  //old code that draws with polygon per area.
//                    angle = i;
//                    x1 = radius * cos(angle * Pi / 180);
//                    y1 = radius * sin(angle * Pi / 180);
//                    srand(time(0)+ i);
//                    // cout << xpts[0] << endl;
//                   // cout << circCtr.x + x1 << endl;
//                    glColor3f((float) rand() /(float) RAND_MAX,(float) rand() /(float) RAND_MAX,(float) rand() /(float) RAND_MAX);
//                    glBegin(GL_POLYGON);
//                    glVertex2f(circCtr.x, circCtr.y);
//                    glVertex2f((circCtr.x + x1)-1,(circCtr.y + y1)-1);
//                    glVertex2f(circCtr.x + x1,circCtr.y + y1);
//                    //cout << circCtr.x + x1<< endl;
//                    glEnd();
//                }

//        glBegin(GL_LINES);   //code from the book
//        glVertex2i (circCtr.x, circCtr.y);
//        glVertex2i (piePt.x, piePt.y);
//        glEnd();
        
        
         xRast = circCtr.x-10 + Tradius * cos(sliceAngle);
         yRast = circCtr.y + Tradius * sin(sliceAngle);
        
    
//        xpts.push_back(piePt.x);
//        ypts.push_back(piePt.y);
        xpts.push_back(xRast); //pushing text positions into vectors
        ypts.push_back(yRast);
        
      
        
        previousSliceAngle = sliceAngle;
        
    }
   
   // double tempColor [n][3];
    vector <double> rTemp;
    vector <double> bTemp;
    vector <double> gTemp;
    
     int d = 0;
     double hold = totals[d]; //variable that holds the current length of the segment
    
            double i, angle, x1, y1;

    float red = (float) rand() /(float) RAND_MAX; //random colors
    float green =  (float) rand() /(float) RAND_MAX;
    float blue = (float) rand() /(float) RAND_MAX;
    rTemp.push_back(red);
    bTemp.push_back(blue);
    gTemp.push_back(green);
    
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLES);
    glVertex2f(circCtr.x, circCtr.y); //center
    glVertex2f(circCtr.x + radius, circCtr.y); //first outer pt of triangle
   
            for( i =0; i < twoPi; i += .01){
                angle = i;
                x1 = circCtr.x + cos(i)*radius;
                y1 = circCtr.y + sin(i)*radius;
                if(angle > hold){
                     d++;
                    hold += totals[d];
                     red = (float) rand() /(float) RAND_MAX;
                     green =  (float) rand() /(float) RAND_MAX;
                     blue = (float) rand() /(float) RAND_MAX;
                     glColor3f(red,green,blue);
                    rTemp.push_back(red);
                    bTemp.push_back(blue);
                    gTemp.push_back(green);
                }
                
                 glVertex2f(x1, y1);
                glVertex2f(circCtr.x, circCtr.y);
                 glVertex2f(x1, y1);
            }
    glEnd();
    glFlush();
   
    for(int k =0; k < label.size(); k++){
         glColor3f(rTemp[k],gTemp[k],bTemp[k]);
                string hold  = label[k];
        glRasterPos2i(xpts[k], ypts[k]);
        for (int p =0; p < label[k].length(); p++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, hold[p]);
        }
    }
    
    glColor3f(0.0,0.0,0.0);  //setting outer border of pie chart.
    setCircle(circCtr.x, circCtr.y, radius, 2);
    //Not sure if we were allowed to draw the border with points. picture in description shows border.
   
}


void displayFcn (void)
{
    glClear (GL_COLOR_BUFFER_BIT);   //  Clear display window.
    glColor3f (.60, .77, .46);       //  Set color to green.
    displayPie();
    glFlush();
}

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ( );
    gluOrtho2D (0.0, GLdouble (newWidth), 0.0, GLdouble (newHeight));
    
    glClear (GL_COLOR_BUFFER_BIT);
    
    /*  Reset display-window size parameters.  */
    winWidth = newWidth;
    winHeight = newHeight;
}

int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(30,30);
    glutInitWindowSize(850,700);
    glutCreateWindow("Them graphs doe");
   // glutDisplayFunc(displayBar);
    glutDisplayFunc(displayFcn); //pieChart
    init();
    glutReshapeFunc (winReshapeFcn);
    glutMainLoop();
    
}


//        ifstream file("/Users/madelynreyes/Desktop/graphs.txt"); //genering file input
//        //string testcase;
//        string line;
//        //int n = stoi(line);
//    
//        vector<int> data;
//        vector<string> label;
//    
//        while(getline(file,line)){
//            istringstream iss(line);
//            string s;
//            int i;
//            while(iss >> i && iss >> s){
//                 data.push_back(i);
//                 label.push_back(s);
//            }
//            
//    
//        }
//    
//        for(int i =0; i < label.size();i++){
//            cout << label[i] << endl;
//        }
//
//    

