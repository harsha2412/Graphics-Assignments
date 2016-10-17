/*
 ------------ Name :- Harsha Gwalani-------------------------
 ------------Computer Graphics :- Program 3------------------
 ------------Instructor:- Dr. Robert Renka-------------------
 
 This program displays 5 emoticons repeatedly with animated objects.
 
 
 */


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<iostream>
#include<math.h>


//Constants
using namespace std;
static int delta =5;
static GLfloat spin = 0;
static int counter= 1;
int static faceType=1;
int static scaleFactor = 1;
int static rotationCount=0;
int static numberOfTurns =0;
int static  speed=0;
//function prototypes
void createCircle(float,int,int);
void createCircleOutline(float,int,int);
void createTriangle(float[],float[],float[]);
void createFace(float[]);
void smile(void); //2
void cry(void); //3
void angel(void); //4
void demon(void); //5
void straight(void); //1
void showFaces(int);
void createStar(void);
void spinDisplay(void);
void createEllipse(float, float );
void initializeStaticVariables(void);
void alterSpeed(void);

// controls the spin angle and number of turns for each icon depending on the speed
// speed ==1 => slower and speed==2 ==> faster
void alterSpeed(){
    
    switch (faceType%6) {
        case 1:
        default:
        delta =2.5;
            numberOfTurns=1;
            break;
        case 2:
            numberOfTurns=200;
            break;
    
        case 3:
            numberOfTurns=5;
            delta=5;
            break;
        case 4:
        case 5:
            numberOfTurns=5;
            delta=5;
            
            break;
       
    }
    if(speed==1){
        delta =delta-1;
        numberOfTurns=numberOfTurns*2;
    }
    if(speed==2){
        delta =delta+2;
        numberOfTurns=numberOfTurns/2;
    }
   
}

void initializeStaticVariables(){
    spin =0;
    delta =5;
    rotationCount=0;
    numberOfTurns=0;
    counter =0;
    scaleFactor=1;
    
}

// creates a star using 2 triangles
void createStar(){
    float v1[] ={-1,0,0};
    float v2[] ={1,0,0};
    float v3[] = {0,1,0};
    createTriangle(v2, v1, v3);
    float v4[] = {-1,0.5,0};
    float v5[] ={1,0.5,0};
    float v6[] = {0,-0.5,0};
    createTriangle(v4, v5, v6);
    
}

// calls emoticon function depending on type
void showFaces(int type){
    
    switch (type){
        case 1:
            straight();
            break;
        case 2:
            smile();
            break;
        case 3:
            cry();
            break;
        case 4:
            angel();
            break;
        case 5:
            demon();
            break;
        default:
            straight();
            break;
    }
    
    
    
}

//Display Function
void display(void)
{
    glLoadIdentity();
    showFaces(faceType%6);
    glutSwapBuffers();
}

//creates a filled full or semi circle (up and down) with radius as radius centred at origin
void createCircle(float radius, int angle, int direction){
    
    glBegin(GL_TRIANGLE_FAN);
    for(int i=direction;i<angle;i++){
        GLfloat x = radius*cos((i*M_PI)/180);
        GLfloat y = radius*sin((i*M_PI)/180);
        glVertex2f(x,y);
    }
    glEnd();
    
}

// creates an ellipse centred at origin
void createEllipse(float radx, float rady){
    
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<360;i++){
        GLfloat x = radx*cos((i*M_PI)/180);
        GLfloat y = rady*sin((i*M_PI)/180);
        glVertex2f(x,y);
    }
    glEnd();
}

// moves a point x in elliptical motion by the spin angle;
void createEllipseTrace(float radx, float rady){
    glColor3f(1.00, 1.00,1.00);
    glBegin(GL_POINTS);
    GLfloat x = radx*cos((spin*M_PI)/180);
    GLfloat y = rady*sin((spin*M_PI)/180);
    glVertex2f(x,y);
    glEnd();
    
}

// creates a circular / semi circular outline
void createCircleOutline(float radius, int angle, int direction){
    glColor3f(0.00, 0.00,0.00);
    glBegin(GL_LINE_LOOP);
    for(int i=direction;i<angle;i++){
        GLfloat x = radius*cos((i*M_PI)/180);
        GLfloat y = radius*sin((i*M_PI)/180);
        glVertex2f(x,y);
    }
    glEnd();
    
}

// straight face emoticon uses the createFace()
void straight(){
    
    glLoadIdentity();
    glClearColor (0.0, 0.0, 0.0, 1.0);
    float color[] ={1.0,1.0,0};
    createFace(color);
    glColor3f(0.0,0.0,0.0);
    glLineWidth(3.5);
    glBegin(GL_LINES);
    glVertex2f(4,-5);
    glVertex2f(-4,-5);
    glEnd();
    cout<<"Straight face"<<endl;
    glLoadIdentity();
    glLineWidth(1.0);
    glColor3f(1.00, 0.00,0.00);
    //delta = 2.98 ;
    alterSpeed();
    for(int i=0;i<360;i=i+10){
        glRotatef(spin, 0, 0, 1);
        glTranslated(15*cos((i*M_PI)/180),15*sin((i*M_PI)/180), 0 );
        glutSolidCube(2.0);
        glLoadIdentity();
        
    }
    glLoadIdentity();
    spinDisplay();
    if(rotationCount>numberOfTurns){
        faceType++;
        initializeStaticVariables();
    }
    
    glutPostRedisplay();
    
    
}


void smile(){
    
    glLoadIdentity();
    glClearColor (0.0, 1.0, 1.0, 1.0);
    glLineWidth(1.0);
    float color[] ={1.0,1.0,0};
    createFace(color);
    glLoadIdentity();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
     glVertex2f(4,-5);
     glVertex2f(-4,-5);
    glEnd();
    glColor3f(0.75,0.22,0.55);
    glTranslated(0, -5, 0);
    createCircle(4,360,180);
    //createCircleOutline(4,360,180);
    glLoadIdentity();
    glColor3f(1.0,0.76,0.0);
    glTranslated(20.00, 20.00, 0);
    float rad = 2.5*scaleFactor;
    createCircle(rad,360,0);
    glLoadIdentity();
    glTranslated(20, 20, 0);
    GLfloat rayAngle = 0;
    int rayLength = 2;
    //numberOfTurns =200;
    alterSpeed();
    glLineWidth(3.3);
    for(int i =0;i<8;i++){
        glRotatef(rayAngle, 0, 0, 1);
        glBegin(GL_LINES);
         glVertex2f(0, rad+1);
         glVertex2f(0,rad+1+rayLength*scaleFactor );
        glEnd();
        rayAngle = rayAngle +45;
        
    }
    glLoadIdentity();
    if(rotationCount%10){
        scaleFactor=1;
        
    }
    else {
        scaleFactor =2;
    }
    rotationCount++;
    if(rotationCount>numberOfTurns){
        faceType++;
        initializeStaticVariables();
    }
    glutPostRedisplay();
    
    
}



void cry(){
    glLineWidth(1.0);
    glClearColor (0.5, 0.5, 0.5, 1.0);
    float color[] ={1.0,1.0,0};
    createFace(color);
    glLoadIdentity();
    glColor3f(0.0,0.0,0.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
      glVertex2f(4,-8);
      glVertex2f(-4,-8);
    glEnd();
    glColor3f(0.88,0.22,0.55);
    glTranslated(0, -8, 0);
    glLineWidth(1.0);
    createCircle(4,180,0);
   // createCircleOutline(4,180,0);
    
    //Rain !!
    glColor3f(0.0,.588,1.00);
    
    int shift =0;
    int shifty =0;
    glPointSize(2.2);
    
   // cout<<rotationCount<<"rotation Count"<<endl;
    alterSpeed();
    while(shifty<counter){
        glTranslated(-25, 25-shifty, 0);
        for(int i =0;i<15;i++){
            glTranslated(shift,0,0);
            glRotatef(45, 0, 0, 1);
            glColor3f(0.0,.588,1.00);
            glBegin(GL_LINES);
              glVertex2f(0, 0);
              glVertex2f(0, 3);
            glEnd();
            glRotatef(-45, 0, 0, 1);
            glTranslated(-shift,0,0);
            shift = shift+5;
        }
        shift =0;
        glLoadIdentity();
        shifty= shifty+3;
        
    }
    
    if(counter<60){
        counter++;
        
    }
    else{
        counter =1;
        rotationCount++;
    }
    
    
    if(rotationCount>numberOfTurns){
        faceType++;
        initializeStaticVariables();
        glPointSize(1);
    }
    glutPostRedisplay();
    
}

void demon(){
    glClearColor (0.0,0.0,0.0,1);
    glLineWidth(1.0);
    float color[] ={1.0,0.00,1.0};
    createFace(color);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(4,6.75);
    glVertex2f(1.0,5);
    glEnd();
    glBegin(GL_LINES);
      glVertex2f(-4,6.75);
      glVertex2f(-1.0,5);
    glEnd();
    glLineWidth(7.0);
    glColor3f(1.0,1.0,1.0);
    glTranslated(4, 9, 0);
    // Horns
    glBegin(GL_LINES);
      glVertex2f(0,0);
      glVertex2f(0,3.0*scaleFactor);
    glEnd();
    glTranslated(-4, -9, 0);
    
    glTranslated(-4, 9, 0);
    //glScaled(0, scaleFactor, 0);
    glBegin(GL_LINES);
      glVertex2f(0,0);
      glVertex2f(0,3.0*scaleFactor);
    glEnd();
    glTranslated(4, -9, 0);
    
    
    glLoadIdentity();
    
    glLineWidth(1.0);
    
    glColor3f(0.80,0.22,0.55);
    glTranslated(0, -8, 0);
    //glLineWidth(1.0);
    createCircle(4,180,0);
    //createCircleOutline(4,180,0);
    glColor3f(1.0,1.0,1.0);
    glLoadIdentity();
    ;
    //glTranslated(-29,25,0);
    glRotatef(spin, 0, 0, 0);
    int shift =0;
    int shifty =0;
    numberOfTurns=5;
    alterSpeed();
    while(shifty<15){
        
        glTranslated(-29,31-shifty, 0);
        glRotatef(spin, 0, 0, 0);
        for(int i =0;i<15;i++){
            
            glTranslated(shift,0,0);
            createStar();
            glTranslated(-shift,0,0);
            shift = shift+5;
            
        }
        shift =0;
        glLoadIdentity();
        shifty =shifty+2;
    }
    spinDisplay();
    scaleFactor++;
    scaleFactor = scaleFactor%2;
    if(rotationCount>numberOfTurns){
        initializeStaticVariables();
        faceType++;
    }
    
    glutPostRedisplay();
}

void angel(){
    glClearColor (0.0, 1.0, 1.0, 1.0);
    glLineWidth(1.0);
    float color[] ={1.0,1.0,0};
    createFace(color);
    glLoadIdentity();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
     glVertex2f(4,-5);
     glVertex2f(-4,-5);
    glEnd();
    glColor3f(1.0,0.22,0.55);
    glTranslated(0, -5, 0);
    createCircle(4,360,180);
    //createCircleOutline(4,360,180);
    glLoadIdentity();
    glColor3f(0.0,0.77,1.0);
    glLineWidth(3.0);
    glTranslated(0, 9.756, 0);
    createEllipse(7.7, 2.4);
    glPointSize(0.01);
    glColor3f(0.0,0.70,1.0);
    createEllipseTrace(7.7, 2.4);
    delta=3;
    numberOfTurns=5;
    alterSpeed();
    spinDisplay();
    if(rotationCount==numberOfTurns){
        faceType++;
        initializeStaticVariables();
    }
    glLineWidth(1.0);
    glutPostRedisplay();
    
    
}

//creates a  face with eyes and nose
void createFace(float color[]){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3fv(color);
    createCircle(10,360,0);
    createCircleOutline(10,360,0);
    glTranslated(4,5, 0);
    glColor3f(1.0, 1.0,1.0);
    //createCircle(1.75,360,0);
    createCircleOutline(1.75,360,0);
    glLoadIdentity();
    glTranslated(-4,5, 0);
    //createCircle(1.75,360,0);
    createCircleOutline(1.75,360,0);
    glLoadIdentity();
    glPointSize(4.5);
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
      glVertex2f(4,5);
      glVertex2f(-4,5);
    glEnd();
    glPointSize(1);
    float v1 [] = {-1.0,-1.75,0.0};
    float v2 [] = {1,-1.75,0.0};
    float v3 [] ={0,1.75,0.0};
    glColor3f(0.1, 0.2, 0.3);
    createTriangle(v1,v2,v3);
    
    
    
}

// creates a traingle given 3 vertices
void createTriangle(float v1[],float v2[], float v3[]){
    glBegin(GL_TRIANGLES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
    glEnd();
    
}

//Changes the spin angle
void spinDisplay(void)
{
    
    spin = spin +delta;
    
    if (spin > 360 ){
        rotationCount++;
        spin = spin - 360;
    }
    if (spin < 0){
        spin = spin + 360.0;
    }
    
}

void menu(int item)
{
    
    switch (item) {
        case 'S':
            initializeStaticVariables();
            delta=2.5;
            faceType =1;
            break;
        case 'L':
            initializeStaticVariables();
            faceType =2;
            break;
        case 32:
          //  initializeStaticVariables();
            glutIdleFunc(NULL);
            break;
        case 'C':
            initializeStaticVariables();
            faceType =3;
            break;
        case 'A':
            initializeStaticVariables();
            faceType=4;
            break;
        case 'D':
            initializeStaticVariables();
            faceType =5;
            break;
        case '-':
            speed =1;
            break;
        case '+':
            speed =2;
            break;
        case '0':
            speed=0;
            break;
        case 27:
            exit(0);
    }
    glutPostRedisplay();
    return;
}

void makeMenu(void)
{
    glutCreateMenu(menu);
    glutAddMenuEntry("L/l: Smile", 'L');
    glutAddMenuEntry("C/c: Cry", 'C');
    glutAddMenuEntry("S/s: Straight", 'S');
    glutAddMenuEntry("A/a: Angel", 'A');
    glutAddMenuEntry("D/d: Demon", 'D');
    glutAddMenuEntry("-: Slower", '-');
    glutAddMenuEntry("+: Faster", '+');
    glutAddMenuEntry("0: Medium Pace", '0');
    glutAddMenuEntry("Space : Pause", '-');
    glutAddMenuEntry("Esc Exit", 27);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    return;
}
void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glShadeModel (GL_FLAT);
}

void reshape(int width, int height)
{
    if(width>height){
    glViewport((GLsizei)(width-height)/2,0,(GLsizei)height,(GLsizei)height);
    }
    else {
        
         glViewport(0,(GLsizei)(height-width)/2,(GLsizei)width,(GLsizei)width);
    }
        glFlush();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
   
    glOrtho(-30,30, -30,30, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//Keyboard Press functions
void keyboard(unsigned char key, int x, int y){
    if (key == 27)
        exit(0);
    else if (key=='A'|| key=='a' ) {
        menu('A');
    }
    else if (key=='S'|| key=='s') {
        menu('S');
    }
    else if (key=='L'|| key=='l') {
        menu('L');
    }
    else if (key=='D'|| key=='d') {
        menu('D');
    }
    else if (key=='C'|| key=='c') {
        menu('C');
    }
    
    else if(key=='+'){
        menu('+');
    }
    
    else if(key=='-' ){
        menu('-');
    }
    else if(key=='0' ){
        menu('0');
    }
    else if(key==32){
        menu(32);
    }
    
    
}

//mouse handler function

void mouse(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            break;
        case GLUT_MIDDLE_BUTTON:
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(NULL);
            break;
        default:
            break;
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (800, 500);
    glutInitWindowPosition (-1, -1);
    glutCreateWindow ("Emoticons Animation");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    makeMenu();
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}


