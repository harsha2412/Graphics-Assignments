//
//  prog4_Gwalani.cpp
//  Light
//
//  Created by Harsha Gwalani on 11/2/15.
//  Copyright © 2015 Harsha Gwalani. All rights reserved.
//

/*
 ------------ Name :- Harsha Gwalani-------------------------
 ------------Computer Graphics :- Program 4------------------
 ------------Instructor:- Dr. Robert Renka-------------------
 
 This program displays a bivariate function with lighting and shading. The user can rotate the function anout the x or y axis.
 
 
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<iostream>
#include<math.h>

using namespace std;



static int K = 100;

static GLfloat spin = 0;
static int nv = (K+1)*(K+1);
static int nt = K*K*2;
static int dx=0;
static int dy =0;
static GLfloat zoom=1;
void reshape(int,int);
float f(float,float);




//store vertex coordinates in v
void storeVertices(float v[][3]){
    float h = 1.0/K;
    int indv = 0;
    for (int j = 0 ;j<=K; j++){
        float y = j*h;
        for (int i = 0; i<=K;i++){
            float  x = i*h;
            v[indv][0] = x;
            v[indv][1] = y;
            v[indv][2] = f(x,y);
            indv = indv + 1;
        }
        
    }
    
    
    
}

//store triangle vertices in ltri
void storeTriangles(int ltri[][3]){
    
    int indt = 0;
    for (int j = 1 ;j<=K;j++){
        for(int i=1;i<=K;i++ ){
            int indv = j*(K+1) + i;
            
            ltri[indt][0] = indv-K-2;
            ltri[indt][1] = indv-K-1;
            ltri[indt][2] = indv;
            ltri[indt+1][0] = indv-K-2;
            ltri[indt+1][1] = indv;
            ltri[indt+1][2] =indv-1;;
            indt = indt + 2;
        }
    }
    
}

//normalization function
void normalize(float n[3]){
    float magnitude = sqrt((n[0]*n[0])+(n[1]*n[1])+(n[2]*n[2]));
    if(magnitude!=0){
        for(int i =0;i<3;i++){
            n[i] = n[i]/magnitude;
        }
    }
    
    
}


//compute vertex normals from face normals
void computeVertexNormals(float vn[][3], float v[][3],int ltri[][3]){
    for (int indt = 0;indt<nt;indt++){
        int i1 = ltri[indt][0];
        int i2 = ltri[indt][1];
        int i3 = ltri[indt][2];
        float tn[3]={0.0,0.0,0.0};
        tn[0] = (v[i2][1]-v[i1][1])*(v[i3][2]-v[i1][2])-(v[i2][2]-v[i1][2])*(v[i3][1]-v[i1][1]);
        tn[1] = (v[i2][2]-v[i1][2])*(v[i3][0]-v[i1][0])-(v[i2][0]-v[i1][0])*(v[i3][2]-v[i1][2]);
        tn[2] = (v[i2][0]-v[i1][0])*(v[i3][1]-v[i1][1])-(v[i2][1]-v[i1][1])*(v[i3][0]-v[i1][0]);
        normalize(tn);
        vn[i1][0] += tn[0];
        vn[i1][1] += tn[1];
        vn[i1][2] +=tn[2];
        vn[i2][0] += tn[0];
        vn[i2][1] += tn[1];
        vn[i2][2] +=tn[2];
        vn[i3][0] += tn[0];
        vn[i3][1] += tn[1];
        vn[i3][2] +=tn[2];
        // cout<<"vertex Normals = "<<vn[i1][0]<<" "<<vn[i1][1]<<" "<<vn[i1][2]<<endl;
    }
    
    
}

void display(void)
{
    
    glLoadIdentity();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable(GL_DEPTH_TEST);
    glColor3f(0.00, 1.00,1.00);
    float v[nv][3];
    
    int ltri[nt][3];
    
    float  vn[nv][3];
    
    
    float h =1.0/K;
    float x = h*(K/2);
    float y = h*(K/2);
    float z =  f(x,y);
    storeVertices(v);
    storeTriangles(ltri);
    
    glRotatef(spin, 0+dx, 0+dy, 0);
    glScaled(zoom, zoom,1);
    // glTranslated(-x, -y, -z); // To shift to the center
    for (int i=0;i<nv;i++){
        
        vn[i][0] = 0;
        vn[i][1] = 0;
        vn[i][2] = 0;
    }
    computeVertexNormals(vn, v, ltri);
    for(int i=0;i<nv;i++){
        normalize(vn[i]);
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0,v);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer( GL_FLOAT, 0,vn);
    glDrawElements(GL_TRIANGLES, nt*3, GL_UNSIGNED_INT,ltri);
    
    glutSwapBuffers();
}

//f(x,y) function
float f(float x, float y){
    
    return (.5*exp(-.04*sqrt((80*x-40)*(80*x-40) + (90*y-45)*(90*y-45)))*cos(0.15*sqrt((80*x-40)*(80*x-40) + (90*y-45)*(90*y-45))));
    
}





void reshape(int width, int height)
{
    
    if(width>height){
        glViewport((GLsizei)(width-height)/2,0,(GLsizei)height,(GLsizei)height);
    }
    else {
        
        glViewport(0,(GLsizei)(height-width)/2,(GLsizei)width,(GLsizei)width);
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1*zoom, 1*zoom, -1*zoom, 1*zoom,0,10 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutSwapBuffers();
}

void menu(int item)
{
    switch (item) {
        case 'x':
            dx=1;
            if(dy){
                dy=0;
            }
            spin = spin-20;
            glutPostRedisplay();
            break;
        case 'y':
            dy=1;
            if(dx){
                dx=0;
            }
            spin = spin-20;
            glutPostRedisplay();
            break;
        case 32:
            spin =0;
            zoom =1;
            glutPostRedisplay();
            break;
        case '+':
            zoom = zoom*1.25;
            glutReshapeFunc(reshape);
            glutPostRedisplay();
            break;
        case '-':
            zoom =zoom*0.5;
            glutReshapeFunc(reshape);
            glutPostRedisplay();
            break;
            
        case 27:
            exit(0);
    }
    return;
}

void makeMenu(void)
{
    glutCreateMenu(menu);
    glutAddMenuEntry("x: Rotate about X Axis", 'x');
    glutAddMenuEntry("y: Rotate about Y Axis", 'y');
    glutAddMenuEntry("Space: Original", 32);
    glutAddMenuEntry("+ Zoom in", '+');
    glutAddMenuEntry("- Zoom Out ", '-');
    glutAddMenuEntry("Esc Exit", 27);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    return;
}
void keyboard(unsigned char key, int x, int y){
    if (key == 27)
        exit(0);
    else if (key=='x') {
        menu('x');
    }
    else if (key=='y') {
        menu('y');
    }
    else if (key==32) {
        menu(32);
    }
    else if (key=='+') {
        menu('+');
    }
    else if (key=='-') {
        menu('-');
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
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    //Light Source Postion at the origin
    GLfloat light_position[] = {0.0,0.0,0.0,1.0};
    GLfloat mat_specular[] = { 0.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 20.0 };
    GLfloat light_ambient[] = {1.0,1.0,1.0,1.0};
    GLfloat light_diffuse[] = {0.0,1.0,0.0,1.0};
    GLfloat mat_ambient[] = { 1.0, 0.2, 0.3, 1.0 };
    GLfloat mat_ambientb[] = { 0.0, 0.0, 1.0, 1.0 };
    
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_BACK, GL_AMBIENT, mat_ambientb);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light_ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE);
    glutInitWindowSize (400, 400);
    glutInitWindowPosition (-100, -100);
    glutCreateWindow ("Program 4");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    makeMenu();
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
