//
//  main.cpp
//  HW6CircleEllipse
//
//  Created by Madelyn Reyes on 10/14/17.
//  Copyright © 2017 Madelyn Reyes. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>

void init(void){
    glClearColor(.60,.87,.46,0.5);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,500.0, 0.0, 400.0);
}

class screenPt
{
private:
    GLint x, y;
public:
    /*  Default Constructor: initializes coordinate position to (0, 0).  */
    screenPt ( )  {
        x = y = 0; }
    void setCoords (GLint xCoordValue, GLint yCoordValue)  {
        x = xCoordValue;
        y = yCoordValue;
    }
    GLint getx ( ) const  {
        return x; }
    GLint gety ( ) const  {
        return y; }
    void incrementx ( )  {
        x++; }
    void decrementy ( )  {
        y--; }
};
void setPixel (GLint xCoord, GLint yCoord)
{
    glBegin (GL_POINTS);
    glVertex2i (xCoord, yCoord);
    glEnd ( );
}
void circleMidpoint (GLint xc, GLint yc, GLint radius, GLfloat r, GLfloat g, GLfloat b)
{
    glColor3f(r,g, b);
    screenPt circPt;
    GLint p = 1 - radius;         //  Initial value for midpoint parameter.
    circPt.setCoords (0, radius); //  Set coordinates for top point of circle.
    void circlePlotPoints (GLint, GLint, screenPt);
    /*  Plot the initial point in each circle quadrant.  */
    circlePlotPoints (xc, yc, circPt);
    /*  Calculate next point and plot in each octant.  */
    

        while (circPt.getx ( ) < circPt.gety ( )) {
            circPt.incrementx ( );
            if (p < 0)
                p += 2 * circPt.getx ( ) + 1;
            else {
                circPt.decrementy ( );
                p += 2 * (circPt.getx ( ) - circPt.gety ( )) + 1;
            }
            circlePlotPoints (xc, yc, circPt);
        }
}
void circlePlotPoints (GLint xc, GLint yc, screenPt circPt)
{
    setPixel (xc + circPt.getx ( ), yc + circPt.gety ( ));
    setPixel (xc - circPt.getx ( ), yc + circPt.gety ( ));
    setPixel (xc + circPt.getx ( ), yc - circPt.gety ( ));
    setPixel (xc - circPt.getx ( ), yc - circPt.gety ( ));
    setPixel (xc + circPt.gety ( ), yc + circPt.getx ( ));
    setPixel (xc - circPt.gety ( ), yc + circPt.getx ( ));
    setPixel (xc + circPt.gety ( ), yc - circPt.getx ( ));
    setPixel (xc - circPt.gety ( ), yc - circPt.getx ( ));
}


inline int round (const float a)  { return int (a + 0.5); }

void ellipseMidpoint (int xCenter, int yCenter, int Rx, int Ry, GLfloat r, GLfloat g, GLfloat b)
{
    glColor3f(r, g, b);
    int Rx2 = Rx * Rx;
    int Ry2 = Ry * Ry;
    int twoRx2 = 2 * Rx2;
    int twoRy2 = 2 * Ry2;
    int p;
    int x = 0;
    int y = Ry;
    int px = 0;
    int py = twoRx2 * y;
    void ellipsePlotPoints (int, int, int, int);
    /* Plot the initial point in each quadrant. */
        ellipsePlotPoints (xCenter, yCenter, x, y);
    /* Region 1 */
    p = round (Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
    while (px < py) {
        x++;
        px += twoRy2;
        if (p < 0)
            p += Ry2 + px;
        else {
            y--;
            py -= twoRx2;
            p += Ry2 + px - py;
        }
        ellipsePlotPoints (xCenter, yCenter, x, y);
    }
    /* Region 2 */
    p = round (Ry2 * (x+0.5) * (x+0.5) + Rx2 * (y-1) * (y-1) - Rx2 * Ry2);
    while (y > 0) {
        y--;
        py -= twoRx2;
        if (p > 0)
            p += Rx2 - py;
        else {
            x++;
            px += twoRy2;
            p += Rx2 - py + px;
        }
        ellipsePlotPoints (xCenter, yCenter, x, y);
    }
}
void ellipsePlotPoints (int xCenter, int yCenter, int x, int y)
{
    setPixel (xCenter + x, yCenter + y);
    setPixel (xCenter - x, yCenter + y);
    setPixel (xCenter + x, yCenter - y);
    setPixel (xCenter - x, yCenter - y);
}



void drawCircle(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(4);
    circleMidpoint(100, 200, 60, 0.0,0.0,1.0);
    circleMidpoint(230, 200, 60, 0.0,0.0,0.0);
    circleMidpoint(360, 200, 60, 1.0,0.0,0.0);
    
    circleMidpoint(170, 140, 60, 1.0,1.0,0.0);
    circleMidpoint(300, 140, 60, 0.0,1.0,0.0);
  
    glFlush();
}

void drawEllipse(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);
    ellipseMidpoint(100, 200, 70, 60,0.0,0.0,1.0);
    ellipseMidpoint(245, 200, 70, 60, 0.0,0.0,0.0);
    ellipseMidpoint(390, 200, 70, 60, 1.0,0.0,0.0);
    
    ellipseMidpoint(185, 130, 70, 60, 1.0,1.0,0.0);
    ellipseMidpoint(335, 130, 70, 60, 0.0,1.0,0.0);
    
    
    glFlush();
}




int main(int argc,  char ** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(30,30);
    glutInitWindowSize(500,400);
    glutCreateWindow("Dem rings doe");
    init();
    //glutDisplayFunc(drawCircle);
   glutDisplayFunc(drawEllipse);
    glutMainLoop();
    
}
