//
//  main.cpp
//  HW2Fractals
//  Created by Madelyn Reyes on 9/3/17.
//  Copyright © 2017 Madelyn Reyes. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <cmath>

void init(void){
    glClearColor(0,0,0,0.0); //light blue
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,800.0,0.0,700.0);
    
}

void setPixel(int i, int j){
    glBegin(GL_POINTS);
      glVertex2i(i,j);
    glEnd();

}


void showMandelbrot(void){
    glClear(GL_COLOR_BUFFER_BIT);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    int width = glutGet(GLUT_WINDOW_WIDTH);
    
    float RE_Max = 2.0;
   // double IM_Max = 2;
    float RE_Min =  -2.5;
    float IM_Min = -2.0;
    
    int N = 64;

   
    float delta = (RE_Max - RE_Min)/width;
    
    float z_real = RE_Min;
 
    
    for(int i =0; i < width; i++){
        z_real += delta;
    float  z_imag = IM_Min;
        for(int j =0; j < height; j++){
            z_imag += delta;
            int count = 0;
            // int complexnumX = 0;
            float x_real = 0.0;
            float x_imag = 0.0;
           
            //float z = 0;
            //x = x_real + x_imag;
            
            while(( ((x_real * x_real) + (x_imag * x_imag)) <= 4.0) && (count < N)){
               /// std::cout << x_real;
               float new_x_real =(x_real * x_real) - (x_imag *x_imag);
                x_imag = 2 * (x_real * x_imag);
                 x_real = new_x_real;
               // std::cout << x_real;
                x_real += z_real;
                x_imag += z_imag;
               


            //int complexnumX = pow(complexnumX,2) + z;
                count++;
            }
            if( ((x_real * x_real)  + (x_imag * x_imag) ) <= 4.0){
              
                glColor3f(0.0,0.0,0.0);
                 setPixel(i, j);
    
            }
            else{
                 float color = 1 + 254 * count/N;
                 color =  color / 255;
                glColor3f(0,color,color);
                 setPixel(i, j);
                
            }
            
        }
        glFlush();
        
    }
 
}

void showJulia(void){
    
    //z = -0.8 + 0.156i;
    //-1.5 <= x0.real <=1.5
    //-1.5 <=x0.imag <= 1.5
    
    glClear(GL_COLOR_BUFFER_BIT);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    int width = glutGet(GLUT_WINDOW_WIDTH);
    
    float RE_Max = 1.5;
    // double IM_Max = 2;
    float RE_Min =  -1.5;
    float IM_Min = -1.5;
    
    int N = 128;
    
    
    float delta = (RE_Max - RE_Min)/width;
    float z_real = RE_Min;

    float hold_real = -0.8;
    float hold_im = 0.156;
    
    for(int i =0; i < width; i++){
        z_real += delta;
        float  z_imag = IM_Min;
        for(int j =0; j < height; j++){
            z_imag += delta;
            int count = 0;
            // int complexnumX = 0;
            float x_real = z_real;
            float x_imag = z_imag;
            
            //float z = 0;
            //x = x_real + x_imag;
            
            while(( ((x_real * x_real) + (x_imag * x_imag)) <= 4.0) && (count < N)){
                /// std::cout << x_real;
                float new_x_real =(x_real * x_real) - (x_imag *x_imag);
                x_imag = 2 * (x_real * x_imag);
                x_real = new_x_real;
                // std::cout << x_real;
//                x_real += z_real;
//                x_imag += z_imag;
                x_imag  += hold_im;
                x_real += hold_real;
                
                
                
                
                //int complexnumX = pow(complexnumX,2) + z;
                count++;
            }
            if( ((x_real * x_real)  + (x_imag * x_imag) ) <= 4.0){
                
                glColor3f(0.0,0.0,0.0);
                setPixel(i, j);
                
            }
            else{
                float color = 1 + 254 * count/N;
                color =  color / 255;
                glColor3f(0,color,color);
                setPixel(i, j);
                
            }
            
        }
        glFlush();
        
    }
    
    
}


int main(int argc, char ** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(800,700); //width, height
    glutCreateWindow("Fractals Homework- Mandelbrot/Julia Sets");
    init();
    //glutDisplayFunc(showMandelbrot);
    glutDisplayFunc(showJulia);
    glutMainLoop();
 

    
}




