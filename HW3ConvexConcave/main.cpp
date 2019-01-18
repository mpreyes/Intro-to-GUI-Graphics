//
//  main.cpp
//  HW3ConvexConcave
//
//  Created by Madelyn Reyes on 9/16/17.
//  Copyright © 2017 Madelyn Reyes. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <streambuf>

#include <GLUT/glut.h>
 using namespace std;
int concave = 0;
int convex = 0;
bool isconcave = false;
//vector<int> convcon;


void init(void){
     glClearColor(.60, .87, .46, 0.5);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,400,0.0,400.0);
}
//void printOut(vector<int>convcon){
//    for(int s =0; s < convcon.size();s++){
//        if(convcon.at(s) == 1){
//            cout << "Polygon is convex" << endl;
//        }
//        if(convcon.at(s) == 0){
//            cout << "polygon is concave" << endl;
//        }
//    }
//
//}
void isConvex(){
    cout << "Polygon is convex" << endl;
     //glColor3f(0.0,0.0,1.0); // blue
    
}
void isConcave(){
     cout << "polygon is concave" << endl;
    //glColor3f(1.0,0.0,0.0); //red

}

void printOut(bool t){
    if(t){
        isConcave();
    }
    else{
        isConvex();
    }
    
}
void drawPolygon(vector<int> a, vector<int> b,int n){
    glBegin(GL_LINES);
    glPointSize(15);
       for(int c =0; c < n-1; c++){
        glVertex2i(a.at(c),b.at(c));
        glVertex2i(a.at(c+1),b.at(c+1));
    }
    glVertex2i(a.at(n-1),b.at(n-1));
    glVertex2i(a.at(0),b.at(0));
    glEnd();
    glFlush();
}

void displayPolygon(void){
    
//    for(int e = 0; e < 2;e++){
//        cout << e << " " << endl;
//    }
    glClear(GL_COLOR_BUFFER_BIT);
    ifstream file("/Users/madelynreyes/Desktop/test.txt");
    string line;
    
    vector<int> testcase;
    vector <int> xcoor;
    vector <int> ycoor;
    vector <string> hold;
    string xcor;
    string ycor;
    
    while(getline(file,line)){
        istringstream iss(line);
        int i;
        while(iss >> i){
            if(i < 9){ //assuming there are less than 9 coordinate pts per polygon.
                testcase.push_back(i);
            }
            else{
                if(iss.peek() == ','){
                    xcoor.push_back(i); //pushing x coordinates into xcoor
                }
                if(iss.peek() == ','){
                    iss.ignore();
                }
                else{
                    ycoor.push_back(i); //pushing y coordinates int ycoor
                }
                
            }
            
        }
        
    }
    
    vector<int> xedge;
    vector<int> yedge;
    vector<int> results;
    int xlast;
    int ylast;
    int xsub;
    int ysub;
    int n;
    int count = 0;
   // int neg = 0;
    
    for(int k = 0; k < testcase.size();k++){ //size == 2
         n = testcase.at(k); //6
        for(int j =0; j < n-1; j++){ //iterates through 6/ creates edge vectors
            //p++;
            xsub = xcoor[j+1] - xcoor[j];
            ysub = ycoor[j+1] - ycoor[j];
            yedge.push_back(ysub);
            xedge.push_back(xsub);
            // cout << ylast;
        }
        xlast =  xcoor[0] - xcoor[n-1];
        ylast =  ycoor[0] - ycoor[n-1];
        yedge.push_back(ylast);
        xedge.push_back(xlast);
        
        int crosshold;
        
        for(int x =0; x < n-1; x++){ //doing a fancy cross product workaround
            crosshold = ((xedge[x] * yedge[x+1]) - (yedge[x] * xedge[x+1]));
            results.push_back(crosshold);
            crosshold = 0;
        }
        crosshold = ((xedge[n-2] *yedge[n-1]) -(yedge[n-2]* xedge[n-1]));
        results.push_back(crosshold);
        
        for(int g =0; g < results.size(); g++){//checking if all numbers are either - or +
            if(results[g] >= 0){ //pos
                count++;
            }
            else if(results[g] < 0){ //neg
                count--;
            }
        }
        
         //cout << "count " << count << " ";
        //cout << "results " << results.size() << " ";
        if((count % results.size()) == 0){ //they are all the same sign, convex
            cout << "Polygon is convex" << endl;
           // isConvex();
            glColor3f(0.0,0.0,1.0); // blue
            drawPolygon(xcoor, ycoor,n);
            //convcon.push_back(1); //convex
            //concave++;
        }
        else{ //it is concave
          cout << "polygon is concave" << endl;
           // isConcave();
            glColor3f(1.0,0.0,0.0); //red
            drawPolygon(xcoor, ycoor,n);
           // isconcave = true;
           // convcon.push_back(0); //concave
            
        }
       // printOut(isconcave);
        glEnd();
        glFlush();
        xedge.clear();
        yedge.clear();
        xcoor.erase(xcoor.begin(),xcoor.begin()+ n);
        ycoor.erase(ycoor.begin(),ycoor.begin()+ n);
        results.clear();
       // cout << count << " ";
        count  = 0;
      //  isconcave = false;
//        pos = 0;
//        neg = 0;

    }
    
    file.close();
    
}

int main(int argc,  char ** argv) {
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(400,400);
    glutCreateWindow("Dem polygons doe");
    init();
    glutDisplayFunc(displayPolygon);
    glutMainLoop();
   
    
}
