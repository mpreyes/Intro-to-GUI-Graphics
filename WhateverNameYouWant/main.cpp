//
//  main.cpp
//  WhateverNameYouWant
//
//  Created by Madelyn Reyes on 8/24/17.
//  Copyright © 2017 Madelyn Reyes. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,150.0);
}
void lineSegment(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.5,0.2);
    glBegin(GL_LINES);
    glVertex2i(180,30);
    glVertex2i(10,145);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(100,30);
    glVertex2i(10,145);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(10,30);
    glVertex2i(10,145);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(300,30);
    glVertex2i(10,145);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(400,30);
    glVertex2i(10,145);
    glEnd();


    glFlush(); }
int main(int argc, char ** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(700,600);
    glutCreateWindow("That line doe");
    init();
    glutDisplayFunc(lineSegment);
    glutMainLoop();
}
