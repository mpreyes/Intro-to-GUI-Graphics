//
//  main.cpp
//  RedFlag
//
//  Created by Madelyn Reyes on 9/23/17.
//  Copyright © 2017 Madelyn Reyes. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>
using namespace std;

void init(void){
    glClearColor(.60, .87, .46, 0.5);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500.0,0.0, 400.0);

}
void resize(int width, int height){
    glutReshapeWindow(500, 400);
}

void renderText(GLdouble x, GLdouble y, const string &string){
    glColor3i(0, 0, 0);
    glRasterPos2d(x,y);
    for (int k = 0; k < string.size(); ++k){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[k]);
        
    }
}
void drawPole(int x1, int y1, int x2,int y2){
    glLineWidth(200);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(x1,y1);
    glVertex2i(x2,y2);
    glEnd();
    glFlush();

    
}
void setCircle(int x, int y, int r, int ptsize){
    static const double PI = 3.1415926535;
    double i;
    double angle;
    double x1;
    double y1;
    glColor3f(1.0, 1.0, 0.0);
    glPointSize(ptsize);
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
    glFlush();
}
void drawFinialBall(int x, int y, int ptsize){ //this is what the knob is called by the way.
    glPointSize(ptsize);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
    
    
}

void drawFlag(){
    
    glColor3f(0.8, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(60, 240); //lower left
    glVertex2i(140,335); //right down
    glVertex2i(60, 335); //upper left
    glVertex2i(140,240); // down right
    
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2i(140,220); //lower left
    glVertex2i(190,320); //right down
    glVertex2i(140,320); //upper left
    glVertex2i(190,220); // down right
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex2i(80,220);
    glVertex2i(125,280);
    glVertex2i(155,220);
    glEnd();
    

    glPointSize(70);
    glBegin(GL_POINTS);
    glVertex2i(115,285);
    glEnd();
    
     glFlush();
}
void drawStrings(){
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2i(45,334);
    glVertex2i(60,334);
    glVertex2i(45,241);
    glVertex2i(60,241);
    glEnd();
    glFlush();
    
}

void DrawScene(void){ //only using points,lines, triangles, quads, polygons
    glClear(GL_COLOR_BUFFER_BIT);
    renderText(200.0,210.0, "Red Flag!");
    renderText(320.0,40.0, "Madelyn Reyes");
    drawStrings();
    drawFlag();
    drawPole(30,65,30,360);
    drawPole(38,65,38,360);
    drawPole(43,65,43,360);
    setCircle(36,365,12,5);
    drawFinialBall(36,365,20);
    

    
    
    
    
    
    
    glutReshapeFunc(resize);
}

int main(int argc,  char ** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(30, 30);
    glutInitWindowSize(500, 400);
    glutCreateWindow("That flag doe");
    init();
    glutDisplayFunc(DrawScene);
    glutMainLoop();

}
