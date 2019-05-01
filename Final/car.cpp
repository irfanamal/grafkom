#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include "SOIL.h"

#define ESCAPE 27
#define MAX_PARTICLES 3000
float slowdown = 1.0;
float velocity = 0.8;
float hailsize = 0.012;

typedef struct {
  // Life
  bool alive;	// is the particle alive?
  float life;	// particle lifespan
  float fade; // decay
  // color
  float red;
  float green;
  float blue;
  // Position/direction
  float xpos;
  float ypos;
  float zpos;
  // Velocity/Direction, only goes down in y dir
  float vel;
  // Gravity
  float gravity;
}particles;

// Paticle System
particles par_sys[MAX_PARTICLES];

GLint window;
GLint window2;
GLint Xsize=1000;
GLint Ysize=800;
float i,theta;
GLint nml=0,day=1;

GLfloat xt=0.0,yt=-0.4,zt=0.0,xw=0.0;   
GLfloat xs=1.0,ys=1.0,zs=1.0;
GLfloat xangle=-5,yangle=0.0,zangle=0.0,angle=0.0;   

GLfloat r=0,g=0,b=1;
GLint light=1;
int count=1,flg=1;
int view=0;
int flag1=1,aflag=1;            //to switch car driving mode
int flag2=1,wheelflag=0;   //to switch fog effect
GLUquadricObj *t;

static void SpecialKeyFunc( int Key, int x, int y );

GLuint texture[1];

int LoadGLTextures()
{
    texture[0] = SOIL_load_OGL_texture
        (
        "metal.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );

    if(texture[0] == 0)
        return false;


    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    return true;
}

GLvoid Transform(GLfloat Width, GLfloat Height)
{
    glViewport(0, 0, Width, Height);          
    glMatrixMode(GL_PROJECTION);                  
    glLoadIdentity();			
    gluPerspective(45.0,Width/Height,0.1,100.0); 
    glMatrixMode(GL_MODELVIEW);                   
}


void initParticles(int i) {
    par_sys[i].alive = true;
    par_sys[i].life = 1.0;
    par_sys[i].fade = float(rand()%100)/1000.0f+0.003f;

    par_sys[i].xpos = (float) (rand() % 21) - 10;
    par_sys[i].ypos = 8.0;
    par_sys[i].zpos = (float) (rand() % 12) - 10;

    par_sys[i].red = 0.5;
    par_sys[i].green = 0.5;
    par_sys[i].blue = 1.0;

    par_sys[i].vel = velocity;
    par_sys[i].gravity = 0.8;//-0.8;

}
// For Hail
void drawHail() {
  float x, y, z;

  for (int loop = 0; loop < MAX_PARTICLES; loop=loop+2) {
    if (par_sys[loop].alive == true) {
      x = par_sys[loop].xpos;
      y = par_sys[loop].ypos;
      z = par_sys[loop].zpos;

      // Draw particles
      glColor3f(0.7, 0.7, 1.0);
      glBegin(GL_QUADS);
        // Front
        glVertex3f(x-hailsize, y-hailsize, z+hailsize); // lower left
        glVertex3f(x-hailsize, y+hailsize, z+hailsize); // upper left
        glVertex3f(x+hailsize, y+hailsize, z+hailsize); // upper right
        glVertex3f(x+hailsize, y-hailsize, z+hailsize); // lower left
        //Left
        glVertex3f(x-hailsize, y-hailsize, z+hailsize);
        glVertex3f(x-hailsize, y-hailsize, z-hailsize);
        glVertex3f(x-hailsize, y+hailsize, z-hailsize);
        glVertex3f(x-hailsize, y+hailsize, z+hailsize);
        // Back
        glVertex3f(x-hailsize, y-hailsize, z-hailsize);
        glVertex3f(x-hailsize, y+hailsize, z-hailsize);
        glVertex3f(x+hailsize, y+hailsize, z-hailsize);
        glVertex3f(x+hailsize, y-hailsize, z-hailsize);
        //Right
        glVertex3f(x+hailsize, y+hailsize, z+hailsize);
        glVertex3f(x+hailsize, y+hailsize, z-hailsize);
        glVertex3f(x+hailsize, y-hailsize, z-hailsize);
        glVertex3f(x+hailsize, y-hailsize, z+hailsize);
        //Top
        glVertex3f(x-hailsize, y+hailsize, z+hailsize);
        glVertex3f(x-hailsize, y+hailsize, z-hailsize);
        glVertex3f(x+hailsize, y+hailsize, z-hailsize);
        glVertex3f(x+hailsize, y+hailsize, z+hailsize);
        //Bottom
        glVertex3f(x-hailsize, y-hailsize, z+hailsize);
        glVertex3f(x-hailsize, y-hailsize, z-hailsize);
        glVertex3f(x+hailsize, y-hailsize, z-hailsize);
        glVertex3f(x+hailsize, y-hailsize, z+hailsize);
      glEnd();

      // Update values
      //Move
      if (par_sys[loop].ypos <= 0) {
        par_sys[loop].vel = par_sys[loop].vel*-0.35;
      }
      par_sys[loop].ypos -= par_sys[loop].vel / (slowdown*1000); // * 1000
      par_sys[loop].vel += par_sys[loop].gravity;

      // Decay
      par_sys[loop].life -= par_sys[loop].fade;

      //Revive
      if (par_sys[loop].life < 0.0) {
        initParticles(loop);
      }
    }
  }
}

void drawRain() {
  float x, y, z;
  for (int loop = 0; loop < MAX_PARTICLES; loop=loop+2) {
    if (par_sys[loop].alive == true) {
      x = par_sys[loop].xpos;
      y = par_sys[loop].ypos;
      z = par_sys[loop].zpos;

      // Draw particles
      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_LINES);
        glVertex3f(x, y, z);
        glVertex3f(x, y-0.1, z);
      glEnd();

      // Update values
      //Move
      // Adjust slowdown for speed!
      
      par_sys[loop].ypos -= par_sys[loop].vel / (slowdown*1000);
      par_sys[loop].vel += par_sys[loop].gravity;
      // Decay
      par_sys[loop].life -= par_sys[loop].fade;

      if (par_sys[loop].ypos <= -0.0) {
        par_sys[loop].life = -1.0;
      }
      //Revive
      if (par_sys[loop].life < 0.0) {
        initParticles(loop);
      }
    }
  }
}

GLvoid InitGL(GLfloat Width, GLfloat Height)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLineWidth(2.0);              /* Add line width,   ditto */
    Transform( Width, Height ); /* Perform the transformation */
    t=gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat position[] = { 1.5f, 1.0f, 4.0f, 1.0f };

    // drawRain();
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}
void init()
{
    glClearColor(0,0,0,0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,900.0,0.0,600.0,50.0,-50.0);
	glutPostRedisplay(); 
    for (int loop = 0; loop < MAX_PARTICLES; loop++) {
        initParticles(loop);
    }		
}

GLvoid DrawGLScene()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);


    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);



    


  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
if(view==0)
{
init();
}
else
{
  if(count==1)
	InitGL(Xsize,Ysize);
  if(aflag==1)/* Initialize our window. */
  glClearColor(0.95,0.95,1,1);
  else
	glClearColor(0.1,0.1,0.1,0);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-1.0,0.0,-3.5);
    glRotatef(xangle,1.0,0.0,0.0);
    glRotatef(yangle,0.0,1.0,0.0);
    glRotatef(zangle,0.0,0.0,1.0);
    glTranslatef(xt,yt,zt);
    drawHail();
    glScalef(xs,ys,zs);
    glEnable(GL_COLOR_MATERIAL);

    if(flag2==1)
    {
        GLfloat fogcolour[4]={1.0,1.0,1.0,1.0};

        glFogfv(GL_FOG_COLOR,fogcolour);              
        glFogf(GL_FOG_DENSITY,0.1);                   
        glFogi(GL_FOG_MODE,GL_EXP);                   
        glFogf(GL_FOG_START,3.0);                  
        glFogf(GL_FOG_END,100.0);                    
        glHint(GL_FOG_HINT, GL_FASTEST);             
        glEnable(GL_FOG);
    }
    if(flag2==0)
    {
        glDisable(GL_FOG);
    }

    if(!aflag){
        glBegin(GL_POINTS);
        glColor3f(1,1,1);
        glPointSize(200.0);
        int ccount=0;
        float x=10,y=10;
        while(ccount<20)
        {
            glVertex2f(x,y);
            x+=10;
            y+=10;
            if(y>Ysize) y-=10;
            if(x>Xsize) x-=10;
            ccount++;
        }
        glEnd();}

        glColor3f(1.0,1.0,9.0);
        glPointSize(30.0);
        glBegin(GL_POINTS);
        glVertex3f(0.25,0.3,0.3);
        glVertex3f(0.25,0.3,0.5);
        glEnd();
        glPointSize(200.0);



        glBegin(GL_QUADS);                /* OBJECT MODULE*/

        /* top of cube*/
        //************************FRONT BODY****************************************
        // glColor3f(r,g,b);

        glTexCoord2f(0.3, 0.4); glVertex3f(0.3, 0.4,0.6);
        glTexCoord2f(0.6, 0.5); glVertex3f(0.6, 0.5,0.6);
        glTexCoord2f(0.6, 0.5); glVertex3f(0.6, 0.5,0.2);
        glTexCoord2f(0.3, 0.4); glVertex3f(0.3,0.4,0.2);
        

        /* bottom of cube*/
       glTexCoord2f(0.3,0.4);  glVertex3f( 0.3,0.4,0.6);  
        glTexCoord2f(0.6,0.2); glVertex3f(0.6,0.2,0.6);    
       glTexCoord2f(0.6,0.2);  glVertex3f(0.6,0.2,0.2);   
       glTexCoord2f(0.3,0.2);  glVertex3f( 0.3,0.2,0.2);  

                

        /* front of cube*/
        glTexCoord2f(0.3,0.2);  glVertex3f( 0.3,0.2,0.6); 
        glTexCoord2f(0.3, 0.4); glVertex3f(0.3, 0.4,0.6);  
        glTexCoord2f(0.3,0.4);  glVertex3f(0.3,0.4,0.2);  
        glTexCoord2f(0.3,0.2);  glVertex3f( 0.3,0.2,0.2); 

        

        glTexCoord2f(0.3, 0.2); glVertex3f( 0.3, 0.2,0.6);
        glTexCoord2f(0.3, 0.4); glVertex3f(0.3, 0.4,0.6);
        glTexCoord2f(0.3, 0.4); glVertex3f(0.3, 0.4,0.2);
        glTexCoord2f(0.3, 0.2); glVertex3f( 0.3,0.2,0.2);



        /* back of cube.*/
        glTexCoord2f(0.6,0.2); glVertex3f(0.6,0.2,0.6);
        glTexCoord2f(0.6,0.5); glVertex3f(0.6,0.5,0.6);
        glTexCoord2f(0.6,0.5); glVertex3f(0.6,0.5,0.2);
        glTexCoord2f(0.6,0.2); glVertex3f(0.6,0.2,0.2);

        /* left of cube*/
        glTexCoord2f(0.3,0.2); glVertex3f(0.3,0.2,0.6);
        glTexCoord2f(0.6,0.2); glVertex3f(0.6,0.2,0.6);
        glTexCoord2f(0.6,0.5); glVertex3f(0.6,0.5,0.6);
        glTexCoord2f(0.3,0.4); glVertex3f(0.3,0.4,0.6);

        /* Right of cube */
        glTexCoord2f( 0.3,0.2); glVertex3f( 0.3,0.2,0.2);
        glTexCoord2f( 0.6,0.2); glVertex3f( 0.6,0.2,0.2);
        glTexCoord2f( 0.6,0.5); glVertex3f( 0.6,0.5,0.2);
        glTexCoord2f( 0.3,0.4); glVertex3f( 0.3,0.4,0.2);
        //****************************************************************************
        glTexCoord2f(0.7,0.8); glVertex3f(0.7,0.8,0.6);
        glTexCoord2f(0.7,0.8); glVertex3f(0.7,0.8,0.2);
        glTexCoord2f(1.7,0.8); glVertex3f(1.7,0.8,0.2);        //top cover
        glTexCoord2f(1.7,0.8); glVertex3f(1.7,0.8,0.6);
        //***************************back guard******************************
       

        glTexCoord2f(0.6, 0.5); glVertex3f( 0.6, 0.5,0.6);
        glTexCoord2f(0.6, 0.2); glVertex3f(0.6, 0.2,0.6);
        glTexCoord2f(1.8, 0.2); glVertex3f(1.8, 0.2,0.6);
        glTexCoord2f(1.8, 0.5); glVertex3f( 1.8,0.5,0.6);


        /* bottom of cube*/
        glTexCoord2f(0.6,0.2); glVertex3f(0.6,0.2,0.6);
        glTexCoord2f(0.6,0.2); glVertex3f(0.6,0.2,0.2);
        glTexCoord2f(1.8,0.2); glVertex3f(1.8,0.2,0.2);
        glTexCoord2f(1.8,0.2); glVertex3f(1.8,0.2,0.6);

        /* back of cube.*/
        glTexCoord2f(0.6,0.5); glVertex3f(0.6,0.5,0.2);
        glTexCoord2f(0.6,0.2); glVertex3f(0.6,0.2,0.2);
        glTexCoord2f(1.8,0.2); glVertex3f(1.8,0.2,0.2);
        glTexCoord2f(1.8,0.5); glVertex3f(1.8,0.5,0.2);
        //*********************ENTER WINDOW**********************************
        // glColor3f(0.3,0.3,0.3);
        glTexCoord2f(0.77, 0.77); glVertex3f(0.77, 0.77,0.2);
        glTexCoord2f(0.75, 0.50); glVertex3f(0.75, 0.50,0.2);        //quad front window
        glTexCoord2f(1.20, 0.50); glVertex3f(1.20, 0.50,0.2);
        glTexCoord2f(1.22, 0.77); glVertex3f(1.22, 0.77,0.2);

        glTexCoord2f(1.27,0.77); glVertex3f(1.27,0.77,0.2);
        glTexCoord2f(1.25,0.50); glVertex3f(1.25,0.50,0.2);        //quad back window
        glTexCoord2f(1.65,0.50); glVertex3f(1.65,0.50,0.2);
        glTexCoord2f(1.67,0.77); glVertex3f(1.67,0.77,0.2);

        // glColor3f(r,g,b);
        glTexCoord2f(0.70,0.8); glVertex3f(0.70,0.8,0.2);
        glTexCoord2f(0.70,0.5); glVertex3f(0.70,0.5,0.2);       //first separation
        glTexCoord2f(0.75,0.5); glVertex3f(0.75,0.5,0.2);
        glTexCoord2f(0.77,0.8); glVertex3f(0.77,0.8,0.2);

        glTexCoord2f(1.20,0.8); glVertex3f(1.20,0.8,0.2);
        glTexCoord2f(1.20,0.5); glVertex3f(1.20,0.5,0.2);       //second separation
        glTexCoord2f(1.25,0.5); glVertex3f(1.25,0.5,0.2);
        glTexCoord2f(1.27,0.8); glVertex3f(1.27,0.8,0.2);

        glTexCoord2f(1.65,0.8); glVertex3f(1.65,0.8,0.2);
        glTexCoord2f(1.65,0.5); glVertex3f(1.65,0.5,0.2);     //3d separation
        glTexCoord2f(1.70,0.5); glVertex3f(1.70,0.5,0.2);
        glTexCoord2f(1.70,0.8); glVertex3f(1.70,0.8,0.2);

        glTexCoord2f(0.75, 0.80); glVertex3f(0.75, 0.80,0.2);
        glTexCoord2f(0.75, 0.77); glVertex3f(0.75, 0.77,0.2);        //line strip
        glTexCoord2f(1.70, 0.77); glVertex3f(1.70, 0.77,0.2);
        glTexCoord2f(1.70, 0.80); glVertex3f(1.70, 0.80,0.2);

        glTexCoord2f( 0.75, 0.8); glVertex3f( 0.75, 0.8,0.6);
        glTexCoord2f(0.75, 0.77); glVertex3f(0.75, 0.77,0.6);        //line strip
        glTexCoord2f(1.70, 0.77); glVertex3f(1.70, 0.77,0.6);
        glTexCoord2f(1.70, 0.80); glVertex3f(1.70, 0.80,0.6);

        // glColor3f(0.30, 0.30,0.3);
        glTexCoord2f(0.77, 0.77); glVertex3f(0.77, 0.77,0.6);
        glTexCoord2f(0.75, 0.50); glVertex3f(0.75, 0.50,0.6);        //quad front window
        glTexCoord2f(1.20, 0.50); glVertex3f(1.20, 0.50,0.6);
        glTexCoord2f(1.22, 0.77); glVertex3f(1.22, 0.77,0.6);

        glTexCoord2f(1.27,0.77); glVertex3f(1.27,0.77,0.6);
        glTexCoord2f(1.25,0.50); glVertex3f(1.25,0.50,0.6);        //quad back window
        glTexCoord2f(1.65,0.50); glVertex3f(1.65,0.50,0.6);
        glTexCoord2f(1.67,0.77); glVertex3f(1.67,0.77,0.6);

        // glColor3f(r,g,b);
        glTexCoord2f(0.70,0.8); glVertex3f(0.70,0.8,0.6);
        glTexCoord2f(0.70,0.5); glVertex3f(0.70,0.5,0.6);       //first separation
        glTexCoord2f(0.75,0.5); glVertex3f(0.75,0.5,0.6);
        glTexCoord2f(0.77,0.8); glVertex3f(0.77,0.8,0.6);

        glTexCoord2f(1.20,0.8); glVertex3f(1.20,0.8,0.6);
        glTexCoord2f(1.20,0.5); glVertex3f(1.20,0.5,0.6);       //second separation
        glTexCoord2f(1.25,0.5); glVertex3f(1.25,0.5,0.6);
        glTexCoord2f(1.27,0.8); glVertex3f(1.27,0.8,0.6);

        glTexCoord2f(1.65,0.8); glVertex3f(1.65,0.8,0.6);
        glTexCoord2f(1.65,0.5); glVertex3f(1.65,0.5,0.6);
        glTexCoord2f(1.70,0.5); glVertex3f(1.70,0.5,0.6);
        glTexCoord2f(1.70,0.8); glVertex3f(1.70,0.8,0.6);



        //**************************************************************
        
        /* top of cube*/

        glTexCoord2f(0.6, 0.5); glVertex3f(0.6, 0.5,0.6);
        glTexCoord2f(0.6, 0.5); glVertex3f(0.6, 0.5,0.2);        //quad front window
        glTexCoord2f(0.7, 0.8); glVertex3f(0.7, 0.8,0.2);
        glTexCoord2f(0.7, 0.8); glVertex3f(0.7, 0.8,0.6);

        glTexCoord2f(1.7,0.8); glVertex3f(1.7,0.8,0.6);
        glTexCoord2f(1.7,0.8); glVertex3f(1.7,0.8,0.2);        //quad back window
        glTexCoord2f(1.8,0.5); glVertex3f(1.8,0.5,0.2);
        glTexCoord2f(1.8,0.5); glVertex3f(1.8,0.5,0.6);


        //*****************************road and surrounding development***********************************
        if(flag1)
        {
            glPushMatrix();
            glTranslatef(xw,0,0);
            glColor3f(0,1,0);
            glVertex3f(-100,-0.0,-100);
            glVertex3f(-100,-0.0,10);         //a green surroundings
            glVertex3f(100,-0.0,10);
            glVertex3f(100,-0.0,-100);

            
            glPopMatrix();
        }
        glEnd();

        glEnd();
        
        //
        glBegin(GL_TRIANGLES);                /* start drawing the cube.*/

        /* top of cube*/
        // glColor3f(0.3,0.3,0.3);
        glVertex3f( 0.6, 0.5,0.6);
        glVertex3f( 0.7,0.8,0.6);       //tri front window
        glVertex3f(0.7,0.5,0.6);

        glVertex3f( 0.6, 0.5,0.2);
        glVertex3f( 0.7,0.8,0.2);       //tri front window
        glVertex3f(0.7,0.5,0.2);

        glVertex3f( 1.7, 0.8,0.2);
        glVertex3f( 1.8,0.5,0.2);       //tri back window
        glVertex3f( 1.7,0.5,0.2);

        glVertex3f( 1.7, 0.8,0.6);
        glVertex3f( 1.8,0.5,0.6);       //tri back window
        glVertex3f(1.7,0.5,0.6);

        glEnd();
        glFlush();
        //************IGNITION SYSTEM
        glPushMatrix();
        glColor3f(0.3,0.3,0.3);
        glTranslatef(1.4,0.2,0.3);
        glRotatef(90.0,0,1,0);
        gluCylinder(t,0.02,0.03,.5,10,10);
        glPopMatrix();
        //********************WHEEL

        // glColor3f(0.7,0.7,0.7);
        glPushMatrix();
        glBegin(GL_LINE_STRIP);
        for(theta=0;theta<360;theta=theta+40)
        {
            glVertex3f(0.6,0.2,0.62);
            glVertex3f(0.6+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.62);
        }
        glEnd();

        glBegin(GL_LINE_STRIP);
        for(theta=0;theta<360;theta=theta+40)
        {
            glVertex3f(0.6,0.2,0.18);
            glVertex3f(0.6+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.18);
        }
        glEnd();

        glBegin(GL_LINE_STRIP);
        for(theta=0;theta<360;theta=theta+40)
        {
            glVertex3f(1.6,0.2,0.18);
            glVertex3f(1.6+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.18);
        }
        glEnd();

        glBegin(GL_LINE_STRIP);
        for(theta=0;theta<360;theta=theta+40)
        {
            glVertex3f(1.6,0.2,0.62);
            glVertex3f(1.6+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.62);
        }
        glEnd();
        glTranslatef(0.6,0.2,0.6);
        glColor3f(0,0,0);
        glutSolidTorus(0.04,0.12,10,25);

        glTranslatef(-0.05,0,-0.4);
        glutSolidTorus(0.04,0.12,10,25);

        glTranslatef(1.1,0,0);
        glutSolidTorus(0.04,0.12,10,25);

        glTranslatef(-0.05,0,0.4);
        glutSolidTorus(0.04,0.12,10,25);
        glPopMatrix();
        //*************************************************************
        glPopMatrix();
        glEnable(GL_DEPTH_TEST);
        glutPostRedisplay();

        glutSwapBuffers();

        glFlush();
    }
}

void NormalKey(GLubyte key, GLint x, GLint y)
{
    switch ( key )    {
     case ESCAPE : printf("escape pressed. exit.\n");
	               glutDestroyWindow(window);	
	               exit(0);
                                   break;

      case ' ':view=1;
                   DrawGLScene();
                   break;

      case 'x': xangle += 5.0;
                      glutPostRedisplay();
                      break;

       case 'X':xangle -= 5.0;
                       glutPostRedisplay();
                       break;

      case 'y':
        yangle += 5.0;
        glutPostRedisplay();
        break;

     case 'Y':
        yangle -= 5.0;
        glutPostRedisplay();
        break;

     case 'z':
        zangle += 5.0;
        glutPostRedisplay();
        break;

     case 'Z':
        zangle -= 5.0;
        glutPostRedisplay();
        break;

      case 'u':                          /* Move up */
        yt += 0.2;
        glutPostRedisplay();
        break;

      case 'U':
        yt -= 0.2;                      /* Move down */
        glutPostRedisplay();
        break;

      case 'f':                          /* Move forward */
        zt += 0.2;
        glutPostRedisplay();
        break;

      case 'F':
        zt -= 0.2;                      /* Move away */
        glutPostRedisplay();
        break;


     default:
	break;
    }

}

static void SpecialKeyFunc( int Key, int x, int y )
{
	switch ( Key ) {
case GLUT_KEY_RIGHT:
		if(!wheelflag)
		xt += 0.2;
		if(wheelflag)
		{
		angle+=5;
		xw+=0.2;
		}
	   glutPostRedisplay();
		break;

case GLUT_KEY_LEFT:
		if(!wheelflag)
		xt -= 0.2;
		if(wheelflag)
		{
		angle+=5;
		xw-=0.2;
		}
        glutPostRedisplay();
		break;

case GLUT_KEY_UP:
        if(!wheelflag)
        yt += 0.2;
        
        glutPostRedisplay();
        break;

case GLUT_KEY_DOWN:
        if(!wheelflag)
        yt -= 0.2;
        
        glutPostRedisplay();
        break;
	}
}



void ChangeSize(int w, int h)
{
    if(h == 0)
    {
        h = 1;
    }
    float ratio = 1.0f * w/h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,w,h);
    gluPerspective(45,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,6.0,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);
}

void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);               

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);    
    glutInitWindowSize(Xsize,Ysize);     
    glutInitWindowPosition(20,20);         
    glutCreateWindow("3D CAR ANIMATION");

    glutDisplayFunc(DrawGLScene);       
    glutKeyboardFunc(NormalKey);         
    glutSpecialFunc( SpecialKeyFunc );
    InitGL(Xsize,Ysize);

    glEnable(GL_DEPTH_TEST);

    LoadGLTextures();

    glutMainLoop();                     
    return 1;
}

