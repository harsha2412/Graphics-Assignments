//
//  prog5_Gwalani.cpp
//  SolarSystem
//
//  Created by Harsha Gwalani on 11/15/15.
//  Copyright © 2015 Harsha Gwalani. All rights reserved.
//
/*
 ------------ Name :- Harsha Gwalani-------------------------
 ------------Computer Graphics :- Program 5------------------
 ------------Instructor:- Dr. Robert Renka-------------------
 
 This program displays a solar system model and provides ways to change the orientation and location of the viewer. The planets rotate around their own axis and revolve around the sun. The moon revolves around the earth.
 
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<iostream>
#include<math.h>

using namespace std;
#define PI 3.14159265;
float static zoom =1;
static int year = 0, day = 0,day1=0,year1=0,year2=0,day2=0,spinx=0,spiny=0,spinz=0,spinu=0,spinl=0;
float static currentOAngle =45;
int shadeModel = GL_SMOOTH;
float static currentLAngle = 45;
float static currentOAxis[3]={1,1,1};
float static currentLAxis[3]={1,1,1};
float static r = 3;
float Cx=0,Cy=0,Cz=-2*r;
static float shift =0;
void normalizeQuarternion(float q[]);
void convertToQuarternion(float q[],float angle,float pole[]);
void quarternionProduct(float q1[],float q2[],float q[]);
void getRotationQuarternion(float q[],float angle,char ch);
void reInitializeGlobalVariables();
void init(void)
{
    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = { 0.0, 0.0, 0.0, 0.0 };
    GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
   
    
    glClearColor(0.0, 0.1, 0.1, 0.0);
    glEnable(GL_DEPTH_TEST);
   
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR,specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

//normalizes the quarternion q
void normalizeQuarternion(float q[]){
    float sum =0;
    for(int i=0;i<4;i++){
        sum = sum + (q[i]*q[i]);
    }
    sum = sqrt(sum);
    if(sum!=0){
    for(int i=0;i<4;i++){
        q[i]=q[i]/sum;
    }
    }
    
}
//converts the angle and pole in quarternion q
void convertToQuarternion(float q[],float angle,float pole[]){
    angle = angle/360;
    angle = angle*PI;
    q[0]=cos(angle);
    
    for(int i=0;i<3;i++){
        q[i+1]=pole[i]*sin(angle);
    }
    normalizeQuarternion(q);
}
//computes the quarternion product q = q1*q2
void quarternionProduct(float q1[],float q2[],float q[]){
    q[0]= q1[0]*q2[0]- (q1[1]*q2[1]+q1[2]*q2[2]+q1[3]*q2[3]);
    q[1]= q1[0]*q2[1] + q2[0]*q1[1]+ (q1[2]*q2[3] -q2[2]*q1[3]);
    q[2]= q1[0]*q2[2] + q2[0]*q1[2]+(q2[1]*q1[3] -q2[3]*q1[1]);
    q[3]= q1[0]*q2[3] + q2[0]*q1[3] +(q1[1]*q2[2] -q2[1]*q1[2]);
    
}
//convert a quarternion into a vector and angle (the angle is returned)
float convertToEuler(float q[],float vector[]){
    float angle = 2*acos(q[0])*180;
    angle = angle/PI;
    float sum =0;
    for(int i=1;i<4;i++){
        sum = sum + (q[i]*q[i]);
    }
    sum = sqrt(sum);
    
    for(int i=0;i<3;i++){
        vector[i]=q[i+1]/sum;
    }
    return angle;
}
// updates q the required rotation quarternion depending on the axis and the angle
void getRotationQuarternion(float q[],float angle,char ch){
    if(ch=='x'){
        float pole[3] ={1,0,0};
        convertToQuarternion(q, angle, pole);
    }
    if(ch=='y'){
        float pole[3] ={0,1,0};
        convertToQuarternion(q, angle, pole);
    }
    if(ch=='z'){
        float pole[3] ={0,0,1};
        convertToQuarternion(q, angle, pole);
    }
    
}

void mouse(int button, int state, int x, int y)
{
    
    
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(NULL);
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

void display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glShadeModel(shadeModel);
    //centre at 0,0,-2r
    glTranslated(0, 0, -2*r);
    cout <<" Current O Angle = "<<currentOAngle<<"Curent o Axis "<<currentOAxis[0]<<" "<<currentOAxis[1]<<" "<<currentOAxis[2]<<"\n";
    cout<<" Location angle and axis "<<currentLAngle<<" "<<" "<<currentLAxis[0]<<" "<<currentLAxis[1]<<" "<<currentLAxis[2]<<"\n";
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.8, 0.7, 0.0, 1.0 };
    GLfloat mat_ambient_color[] = { 0.0, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 0.5, 0.0, 1.0 };
    GLfloat mat_diffuse1[] = { 0.0, 0.5, 1.0, 1.0 };
    GLfloat mat_diffuse2[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_diffuse3[] = { 1.0, 0.1, 0.3, 1.0 };
    GLfloat mat_diffuse4[] = { 0.5, 0.2, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    
    GLfloat low_shininess[] = { 5.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};
    
   
    glMaterialfv(GL_BACK, GL_AMBIENT,mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT,no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    //shift = -r for change in location
    // Orientation and Location Rotations
    glRotated(currentOAngle, currentOAxis[0],currentOAxis[1], currentOAxis[2]);
    glTranslated(0.0, 0.0,shift);
    glRotated(currentLAngle, currentLAxis[0],currentLAxis[1], currentLAxis[2]);
    
    glutSolidSphere(1.0, 20, 16);   /* draw sun */
    glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
    glTranslatef (3.0, 0, 0.0);
    glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glutSolidSphere(0.2, 10, 8);    /* draw smaller planet */
    
    //Drawing a moon for the above planet
    glRotatef ((GLfloat) year1, 0.0, 1.0, 0.0);
    glTranslatef (1.0,0, 0.0);
    glRotatef ((GLfloat) day1, 0.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glutSolidSphere(0.15, 10, 8);
    
    
    //Draw another planet
    
    glRotatef (- day1, 0.0, 1.0, 0.0);
    glTranslatef (-1.0, 0, 0.0);
    glRotatef (- year1, 0.0, 1.0, 0.0);
    glRotatef (- day, 0.0, 1.0, 0.0);
    glTranslatef (-3.0, 0, 0.0);
    glRotatef (- year, 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) year2, 0.0, 1.0, 0.0);
    glTranslatef (-3.0,0, 0.0);
    glRotatef ((GLfloat) day2, 0.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
    glutSolidSphere(0.3 , 10, 8);
    // Draw Another Planet
    glRotatef (- day2, 0.0, 1.0, 0.0);
    glTranslatef (3.0,1.0, 0.0);
    glRotatef (- year2, 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) year1, 0.0, 1.0, 0.0);
    glTranslatef (-5.0,0.4, 0.0);
    glRotatef ((GLfloat) day2, 0.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
    glutSolidSphere(0.35 , 10, 8);
    
    glutSwapBuffers();
}

void reshape (int width, int height)
{
    if(width>height){
        glViewport((GLsizei)(width-height)/2,0,(GLsizei)height,(GLsizei)height);
    }
    
    else {
        glViewport(0,(GLsizei)(height-width)/2,(GLsizei)width,(GLsizei)width);
    }
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    float znear = r;
    float zfar = 5*r;
    glFrustum(-r*1.5*zoom, r*1.5*zoom, -r*1.5*zoom, r*1.5*zoom,znear,zfar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
     glutPostRedisplay();
    
}

void reInitializeGlobalVariables(){
    
    day=0;
    day1=0;
    year1=0;
    year =0;
    year2=0;
    day2=0;
    zoom =1;
    shift=0;
    spinx=0;
    spiny=0;
    spinz=0;spinu=0;spinl=0;
    currentOAngle =45;
    currentLAngle = 45;
    
    for(int i=0;i<3;i++){
        currentOAxis[i] =1;
        currentLAxis[i]=1;
    }
    
}

void menu(int item)
{
    GLint w = glutGet(GLUT_WINDOW_WIDTH);
    float quarternion[4];
    float location[4];
    float orientation[4];
    float product[4];
    GLint h = glutGet(GLUT_WINDOW_HEIGHT);
    
    switch(item){
        case 'i':
        case 'I':
            reInitializeGlobalVariables();
            glutPostRedisplay();
        case 'd':
            shift =0;
            day = (day + 10) % 360;
            day2 = (day2 + 30) % 360;
            day1 = (day+5)%360;
            glutPostRedisplay();
            break;
        case 'D':
            shift =0;
            day = (day - 10) % 360;
            day2 = (day2 - 30) % 360;
            day1 = (day-5)%360;
            glutPostRedisplay();
            break;
        case 'R':
            shift =0;
            year = (year + 5) % 360;
            year1 =(year1+2) %360;
            year2 =(year2+10) %360;
            glutPostRedisplay();
            break;
        case 'r':
            shift =0;
            year = (year - 5) % 360;
            year1 =(year1-2) %360;
            year2 =(year2-10) %360;
            glutPostRedisplay();
            break;
        case '+':
            shift =0;
            zoom =zoom*0.85;
            reshape(w,h);
            break;
        case '-':
            zoom =zoom*1.2;
            reshape(w,h);
            break;
        case 't':
            shift =shift-0.2;
            glutPostRedisplay();
            break;
        case 'T':
            shift =shift+0.3;
            glutPostRedisplay();
            break;
        case 'x':
            shift =0;
            spinx = (spinx+4) % 360;
            getRotationQuarternion(quarternion,spinx,'x');
            convertToQuarternion(orientation,currentOAngle, currentOAxis);
            quarternionProduct(quarternion, orientation, product);
            currentOAngle = convertToEuler(product, currentOAxis);
            glutPostRedisplay();
            break;
        case 'X':
            shift =0;
            spinx = (spinx-4) % 360;
            getRotationQuarternion(quarternion,spinx,'x');
            convertToQuarternion(orientation,currentOAngle, currentOAxis);
            quarternionProduct(quarternion, orientation, product);
            currentOAngle = convertToEuler(product, currentOAxis);
            glutPostRedisplay();
            break;
        case 'L': //for L, l , U and u are passed to the menu function in response to arrow keys .
            shift =-r;
            spinl = (spinl+7) % 360;
            getRotationQuarternion(quarternion,spinl,'y');
            convertToQuarternion(location,currentLAngle, currentLAxis);
            quarternionProduct(quarternion, location, product);
            currentLAngle = convertToEuler(product, currentLAxis);
            glutPostRedisplay();
            break;
        case 'l':
            shift=-r;
            spinl = (spinl-7) % 360;
            getRotationQuarternion(quarternion,spinl,'y');
            convertToQuarternion(location,currentLAngle, currentLAxis);
            quarternionProduct(quarternion, location, product);
            currentLAngle = convertToEuler(product, currentLAxis);
            glutPostRedisplay();
            break;
        case 'u':
            shift = -r;
            spinu = (spinu+9) % 360;
            getRotationQuarternion(quarternion,spinu,'x');
            convertToQuarternion(location,currentLAngle, currentLAxis);
            quarternionProduct(quarternion, location, product);
            currentLAngle = convertToEuler(product, currentLAxis);
            glutPostRedisplay();
            break;
        case 'U':
            shift=-r;
            spinu = (spinu-9) % 360;
            getRotationQuarternion(quarternion,spinu,'x');
            convertToQuarternion(location,currentLAngle, currentLAxis);
            quarternionProduct(quarternion, location, product);
            currentLAngle = convertToEuler(product, currentLAxis);
            glutPostRedisplay();
            break;
        case 'y':
            shift =0;
            spiny = (spiny+4) % 360;
            getRotationQuarternion(quarternion,spiny,'y');
            convertToQuarternion(orientation,currentOAngle, currentOAxis);
            quarternionProduct(quarternion, orientation, product);
            currentOAngle = convertToEuler(product, currentOAxis);
            glutPostRedisplay();
            break;
        case 'Y':
            spiny = (spiny-4) % 360;
            getRotationQuarternion(quarternion,spiny,'y');
            convertToQuarternion(orientation,currentOAngle, currentOAxis);
            quarternionProduct(quarternion, orientation, product);
            currentOAngle = convertToEuler(product, currentOAxis);
            glutPostRedisplay();
            break;
        case 'z':
            shift =0;
            spinz = (spinz+1) % 360;
            getRotationQuarternion(quarternion,spinz,'z');
            convertToQuarternion(orientation,currentOAngle, currentOAxis);
            quarternionProduct(quarternion, orientation, product);
            currentOAngle = convertToEuler(product, currentOAxis);
            glutPostRedisplay();
            break;
        case 'Z':
            shift =0;
            spinz = (spinz-1) % 360;
            getRotationQuarternion(quarternion,spinz,'z');
            convertToQuarternion(orientation,currentOAngle, currentOAxis);
            quarternionProduct(quarternion, orientation, product);
            currentOAngle = convertToEuler(product, currentOAxis);
            glutPostRedisplay();
            break;
        case 'F':
            shift =0;
            shadeModel= GL_FLAT;
            glutPostRedisplay();
            break;
        case 'S':
            shift =0;
            shadeModel= GL_SMOOTH;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
            return;
    }
}
void makeMenu(void)
{
    glutCreateMenu(menu);
    glutAddMenuEntry(" d :- Rotate planets CCW ", 'd');
    glutAddMenuEntry(" D: Rotate planets CW ", 'D');
    glutAddMenuEntry("r: Revolve planets CCW ", 'r');
    glutAddMenuEntry("R : Revolve planets CW ", 'R');
    glutAddMenuEntry("x: change orientation wrt X axis CCW ", 'x');
    glutAddMenuEntry("X: change orientation wrt X axis CW ", 'X');
    glutAddMenuEntry("y: change orientation wrt y axis CCW ", 'y');
    glutAddMenuEntry("Y: change orientation wrt y axis CW ", 'Y');
    glutAddMenuEntry("z: change orientation wrt z axis CCW ", 'z');
    glutAddMenuEntry("Z: change orientation wrt Z axis CW ", 'Z');
    glutAddMenuEntry("->: change Location in the left direction ", 'L');
    glutAddMenuEntry("<-: change Location in the right direction  ", 'l');
    glutAddMenuEntry("Up Arrow: change Location in the up direction direction ", 'u');
    glutAddMenuEntry("Down Arrow: change Location in the down direction ", 'U');
    glutAddMenuEntry("t: Translate along the z axis in the positive direction ", 'z');
    glutAddMenuEntry("T: Traslate along z axis in the negative direction ", 'Z');
    glutAddMenuEntry("I/i: Original", 'I');
    glutAddMenuEntry("+ Zoom in", '+');
    glutAddMenuEntry("- Zoom Out ", '-');
    glutAddMenuEntry("s/S Smooth Shading ", 'S');
    glutAddMenuEntry("f/F Flat Shading ", 'F');
    glutAddMenuEntry("Esc Exit", 27);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    return;
}

void keyboard (unsigned char key, int x, int y)
{
    
    switch (key) {
        case 'i':
        case 'I':
            menu('I');
            break;
        case 'd':
            menu('d');
            break;
        case 'D':
            menu('D');
            break;
        case 'R':
            menu('R');
            break;
        case 'r':
            menu('r');
            break;
        case '+':
            menu('+');
            break;
        case '-':
            menu('-');
            break;
        case 't':
            menu('t');
            break;
        case 'T':
            menu('T');
            break;
        case 'x':
            menu('x');
            break;
        case 'X':
            menu('X');
            break;
        case 'y':
            menu('y');
            break;
        case 'Y':
            menu('Y');
            break;
        case 'z':
            menu('z');
            break;
        case 'Z':
            menu('Z');
            break;
        case 'F':
        case 'f':
            menu('F');
            break;
        case 'S':
        case 's':
            menu('S');
            break;
        case 27:
            menu(27);
            break;
        default:
            break;
    }
}


void arrowKeys(int key, int x, int y){
    GLint w = glutGet(GLUT_WINDOW_WIDTH);
    float quarternion[4];
    float location[4];
    float orientation[4];
    float product[4];
    GLint h = glutGet(GLUT_WINDOW_HEIGHT);
    switch(key)
    {
        case GLUT_KEY_UP:
            menu('L');
            break;
            
        case GLUT_KEY_DOWN:
            menu('l');
            break;
        case GLUT_KEY_LEFT:
            menu('U');
            break;
        case GLUT_KEY_RIGHT:
            menu('u');
            break;
            
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (2000,1900);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(arrowKeys);
    makeMenu();
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}