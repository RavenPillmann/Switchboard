//Raven Pillmann
//Game 1
//Graphics A - Fall 2014
//14.09.2014

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <time.h>

#if defined (WIN32) || defined(_WIN32) || defined (_WIN32_)
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#elif __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#endif

// initializes an array
int squares [16] = {};
bool rPressed = false;
bool cPressed = false;

int middle;
int right;
int left;
int above;
int below;
bool mouseWasClicked = false;

void onDisplay( )
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw all of the squares based on their color
    glBegin(GL_QUADS);
    
    //Set values for x1, x2, y1, y2
    double x1 = -1;
    double x2 = -.5;
    double y1 = -1;
    double y2 = -.5;
    //Loops through squares, uses the integer at each value to determine what color is drawn
    int j = 0;
    for (int i = 0; i < 16; i++){
        j++;
        if(squares[i]==1){
            glColor3d(1,0,0);
            glVertex2d(x1,y1);
            glVertex2d(x1,y2);
            glColor3d(0.7,0,0);
            glVertex2d(x2,y2);
            glColor3d(0.5,0,0);
        }
        else{
            glColor3d(0,1,0);
            glVertex2d(x1,y1);
            glVertex2d(x1,y2);
            glColor3d(0,0.7,0);
            glVertex2d(x2,y2);
            glColor3d(0,0.5,0);
        }
        glVertex2d(x2,y1);
        
        if((j%4 == 0) && (i > 0)){
            x1 = -1;
            x2 = -.5;
            y1 = y1 + .5;
            y2 = y2 + .5;
        }
        else{
            x1 = x1 + .5;
            x2 = x2 + .5;
        }
    }
    glEnd();
    
    glutSwapBuffers();
}

void onKeyboard(unsigned char key, int x, int y){
    
    if (key == 'c'){
        //replace array squares with all red array
        cPressed = true;
    }
    if (key == 'r'){
        rPressed = true;
    }
    
}

void onMouse(int button, int state, int x, int y){
    
    if(state == GLUT_DOWN){
        mouseWasClicked = true;

        double winWidth = glutGet(GLUT_WINDOW_WIDTH);
        double winHeight = glutGet(GLUT_WINDOW_HEIGHT);
        
        double w1 = 0;
        double w2 = .25 * winWidth;
        double w3 = .5 * winWidth;
        double w4 = .75 * winWidth;
        double w5 = 1 * winWidth;
        
        double h1 = 0;
        double h2 = .25 * winHeight;
        double h3 = .5 * winHeight;
        double h4 = .75 * winHeight;
        double h5 = 1 * winHeight;
        
        
        if ((y>=h1) && (y<h2)){
            if ((x>=w1)&&(x<w2)){
                middle = 12;
            }
            else if ((x>=w2)&&(x<w3)){
                middle = 13;
            }
            else if ((x>=w3)&&(x<w4)){
                middle = 14;
            }
            else if ((x>=w4) && (x<w5)){
                middle = 15;
            }
        }
        else if ((y>=h2) && (y<h3)){
            if ((x>=w1)&&(x<w2)){
                middle = 8;
            }
            else if ((x>=w2)&&(x<w3)){
                middle = 9;
            }
            else if ((x>=w3)&&(x<w4)){
                middle = 10;
            }
            else if ((x>=w4) && (x<w5)){
                middle = 11;
            }
        }
        else if ((y>=h3) && (y<h4)){
            if ((x>=w1)&&(x<w2)){
                middle = 4;
            }
            else if ((x>=w2)&&(x<w3)){
                middle = 5;
            }
            else if ((x>=w3)&&(x<w4)){
                middle = 6;
            }
            else if ((x>=w4) && (x<w5)){
                middle = 7;
            }
        }
        else if ((y>=h4) && (y<h5)){
            if ((x>=w1)&&(x<w2)){
                middle = 0;
            }
            else if ((x>=w2)&&(x<w3)){
                middle = 1;
            }
            else if ((x>=w3)&&(x<w4)){
                middle = 2;
            }
            else if ((x>=w4) && (x<w5)){
                middle = 3;
            }
        }
    }
}

void onIdle(){
    if (cPressed == true){
        for(int i=0; i<16; i++){
            squares[i] = 1;
        }
        cPressed = false;
    }
    if (rPressed == true){
        //srand(time(NULL));
        //randomly assign values for the array
        for(int i = 0; i<16; i++){
            int randomInt = rand() % 2;
            squares[i]=randomInt;
        }
        rPressed = false;
    }
    if(mouseWasClicked == true){
        //middle
        if ((middle>=0) && (middle <4)){
            right = (middle+1)%4;
            left = (middle+3)%4;
        }
        if ((middle >=4)&& (middle <8)){
            right = ((middle+1)%4)+4;
            left = ((middle+3)%4)+4;
        }
        if ((middle >=8)&&(middle < 12)){
            right = ((middle+1)%4)+8;
            left = ((middle+3)%4)+8;
        }
        if ((middle >=12)&&(middle <16)){
            right = ((middle+1)%4)+12;
            left = ((middle+3)%4)+12;
        }
        above = (middle + 4)%16;
        below = (middle + 12)%16;
        
        squares[middle] = (squares[middle]+1)%2;
        squares[left] = (squares[left]+1)%2;
        squares[right] = (squares[right]+1)%2;
        squares[above] = (squares[above]+1)%2;
        squares[below] = (squares[below]+1)%2;
        
        mouseWasClicked = false;
        
    }
    
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    //DEFINE YOUR WINDOW
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    //Sets glut fram buffer to rgb mode, sets it to double buffer
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Game");
    
    //Set up the board values
    srand(time(NULL));
    //randomly assign values for the array
    for(int i = 0; i<16; i++){
        int randomInt = rand() % 2;
        squares[i]=randomInt;
    }
    
    //Event Handlers
    
    glutIdleFunc(onIdle);
    glutMouseFunc(onMouse);
    glutKeyboardFunc(onKeyboard);
    glutDisplayFunc(onDisplay);
    
    //THEN PASS CONTROL TO GLUT VIA GLUTMAINLOOP
    glutMainLoop();
    
    return 0;
}
