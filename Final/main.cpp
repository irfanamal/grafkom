#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <SOIL/SOIL.h>

#define ESCAPE 27
#define MAX_PARTICLES 2000
float slowdown = 1.0;
float velocity = 0.8;
float hailSize = 0.012;

typedef struct
{
  // Life
  bool alive; // is the particle alive?
  float life; // particle lifespan
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
} particles;

particles par_sys[MAX_PARTICLES];

GLint window;
GLint window2;
GLint Xsize = 1000;
GLint Ysize = 800;
float i, theta;
GLint nml = 0, day = 1;

GLfloat xt = 0.0, yt = 0.0, zt = 0.0, xw = 0.0;
GLfloat xs = 1.0, ys = 1.0, zs = 1.0;
GLfloat xangle = 0.0, yangle = 0.0, zangle = 0.0, angle = 0.0;

GLfloat r = 0, g = 0, b = 1;
GLint light = 1;
int count = 1, flg = 1;
int view = 0;
int flag1 = 0;
int aflag = 1;                //to switch car driving mode
int flag2 = 0, wheelflag = 0; //to switch fog effect
GLUquadricObj *t;

GLuint texture[1];

static void SpecialKeyFunc(int Key, int x, int y);

int LoadGLTextures()
{
  texture[0] = SOIL_load_OGL_texture(
      "images.png",
      SOIL_LOAD_AUTO,
      SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y);

  if (texture[0] == 0)
    return false;

  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  return true;
}

GLvoid Transform(GLfloat Width, GLfloat Height)
{
  glViewport(0, 0, Width, Height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, Width / Height,0.1, 100.0);
  glMatrixMode(GL_MODELVIEW);
}

void initParticles(int i)
{
  par_sys[i].alive = true;
  par_sys[i].life = 1.0;
  par_sys[i].fade = float(rand() % 100) / 1000.0f + 0.003f;

  par_sys[i].xpos = (float)(rand() % 21) - 10;
  par_sys[i].ypos = 10.0;
  par_sys[i].zpos = (float)(rand() % 21) - 10;

  par_sys[i].red = 0.5;
  par_sys[i].green = 0.5;
  par_sys[i].blue = 1.0;

  par_sys[i].vel = velocity;
  par_sys[i].gravity = 0.8; //-0.8;
}

void drawRain()
{
  float x, y, z;
  for (int loop = 0; loop < MAX_PARTICLES; loop = loop + 2)
  {
    if (par_sys[loop].alive == true)
    {
      x = par_sys[loop].xpos;
      y = par_sys[loop].ypos;
      z = par_sys[loop].zpos;

      // Draw particles
      glColor3f(0.2, 0.2, 1.0);
      glBegin(GL_LINES);
      glVertex3f(x, y, z);
      glVertex3f(x, y - 0.1, z);
      glEnd();

      // Update values
      //Move
      // Adjust slowdown for speed!
      par_sys[loop].ypos -= par_sys[loop].vel / (slowdown * 1000);
      par_sys[loop].vel += par_sys[loop].gravity;
      // Decay
      par_sys[loop].life -= par_sys[loop].fade;

      if (par_sys[loop].ypos <= -0.0)
      {
        par_sys[loop].life = -1.0;
      }
      //Revive
      if (par_sys[loop].life < 0.0)
      {
        initParticles(loop);
      }
    }
  }
}


GLvoid InitGL(GLfloat Width, GLfloat Height)
{

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glLineWidth(2.0);         /* Add line width,   ditto */
  Transform(Width, Height); /* Perform the transformation */
  t = gluNewQuadric();
  gluQuadricDrawStyle(t, GLU_FILL);

  glEnable(GL_LIGHTING);

  glEnable(GL_LIGHT0);

  GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8, 1.0f};
  GLfloat specularLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
  GLfloat position[] = {1.5f, 1.0f, 4.0f, 1.0f};
  // GLfloat position[] = {0.0f, 0.0f, 0.0f, 0.0f};

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
}
void init()
{
  glClearColor(0, 0, 0, 0);
  glPointSize(5.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 900.0, 0.0, 600.0, 50.0, -50.0);
  glutPostRedisplay();
  for (int loop = 0; loop < MAX_PARTICLES; loop++)
  {
    initParticles(loop);
  }
}
void display_string(int x, int y, char *string, int font)
{
  int len, i;
  glColor3f(0.8, 0.52, 1.0);
  glRasterPos2f(x, y);
  len = (int)strlen(string);
  for (i = 0; i < len; i++)
  {
    if (font == 1)
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    if (font == 2)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    if (font == 3)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
    if (font == 4)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, string[i]);
  }
}


GLvoid DrawGLScene()
{

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[0]);

  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (view == 0)
  {
    init();
  }
  else
  {
    if (count == 1)
      InitGL(Xsize, Ysize);

    if (aflag == 1) /* Initialize our window. */
      glClearColor(1, 1, 1, 1);
    else
      glClearColor(0.1, 0.1, 0.1, 0);
    glPushMatrix();

    glLoadIdentity();
    glTranslatef(-1.0, 0.0, -3.5);
    glRotatef(xangle, 1.0, 0.0, 0.0);
    glRotatef(yangle, 0.0, 1.0, 0.0);
    glRotatef(zangle, 0.0, 0.0, 1.0);
    glTranslatef(xt, yt, zt);
    drawRain();
    glScalef(xs, ys, zs);
    glEnable(GL_COLOR_MATERIAL);

    if (flag2 == 1)
    {
      GLfloat fogcolour[4] = {1.0, 1.0, 1.0, 1.0};

      glFogfv(GL_FOG_COLOR, fogcolour);
      glFogf(GL_FOG_DENSITY, 0.1);
      glFogi(GL_FOG_MODE, GL_EXP);
      glFogf(GL_FOG_START, 3.0);
      glFogf(GL_FOG_END, 100.0);
      glHint(GL_FOG_HINT, GL_FASTEST);
      glEnable(GL_FOG);
    }
    if (flag2 == 0)
    {
      glDisable(GL_FOG);
    }

    if (!aflag)
    {
      glBegin(GL_POINTS);
      glColor3f(1, 1, 1);
      glPointSize(200.0);
      int ccount = 0;
      float x = 10, y = 10;
      while (ccount < 20)
      {
        glVertex2f(x, y);
        x += 10;
        y += 10;
        if (y > Ysize)
          y -= 10;
        if (x > Xsize)
          x -= 10;
        ccount++;
      }
      glEnd();
    }

    glColor3f(1.0, .75, 0.0);
    glPointSize(30.0);
    glBegin(GL_POINTS);
    glVertex3f(0.2, 0.3, 0.3);
    glVertex3f(0.2, 0.3, 0.7);
    glEnd();
    glPointSize(200.0);

    glBegin(GL_QUADS); /* OBJECT MODULE*/

    /* top of cube*/
    //************************FRONT BODY****************************************
    glColor3f(0, 0, 0);
    glVertex3f(0.2, 0.5, 0.8);
    glVertex3f(0.6, 0.5, 0.8);
    glVertex3f(0.6, 0.5, 0.2);
    glVertex3f(0.2, 0.5, 0.2);

    /* bottom of cube*/
    glVertex3f(0.2, 0.4, 0.8);
    glVertex3f(0.6, 0.2, 0.8);
    glVertex3f(0.6, 0.2, 0.2);
    glVertex3f(0.2, 0.2, 0.2);

    /* front of cube*/
    glVertex3f(0.2, 0.2, 0.8);
    glVertex3f(0.2, 0.5, 0.8);
    glVertex3f(0.2, 0.5, 0.2);
    glVertex3f(0.2, 0.2, 0.2);

    /* back of cube.*/
    glVertex3f(0.6, 0.2, 0.8);
    glVertex3f(0.6, 0.5, 0.8);
    glVertex3f(0.6, 0.5, 0.2);
    glVertex3f(0.6, 0.2, 0.2);

    /* left of cube*/
    glVertex3f(0.2, 0.2, 0.8);
    glVertex3f(0.6, 0.2, 0.8);
    glVertex3f(0.6, 0.5, 0.8);
    glVertex3f(0.2, 0.5, 0.8);

    /* Right of cube */
    glVertex3f(0.2, 0.2, 0.2);
    glVertex3f(0.6, 0.2, 0.2);
    glVertex3f(0.6, 0.5, 0.2);
    glVertex3f(0.2, 0.5, 0.2);
    //****************************************************************************
    glVertex3f(0.7, 0.85, 0.8);
    glVertex3f(0.7, 0.85, 0.2);
    glVertex3f(1.7, 0.85, 0.2); //top cover
    glVertex3f(1.7, 0.85, 0.8);
    //***************************back guard******************************
    glColor3f(0, 0, 0); /* Set The Color To Blue*/
    glVertex3f(1.8, 0.5, 0.8);
    glVertex3f(1.8, 0.5, 0.2);
    glVertex3f(1.8, 0.2, 0.2);
    glVertex3f(1.8, 0.2, 0.8);

    //******************MIDDLE BODY************************************
    glColor3f(r, g, b); /* Set The Color To Blue*/
    // glBegin(GL_QUADS);

    glTexCoord2f(0.6, 0.5);
    glVertex3f(0.6, 0.5, 0.8);
    glTexCoord2f(0.6, 0.2);
    glVertex3f(0.6, 0.2, 0.8);
    glTexCoord2f(1.8, 0.2);
    glVertex3f(1.8, 0.2, 0.8);
    glTexCoord2f(1.8, 0.5);
    glVertex3f(1.8, 0.5, 0.8);

    // glVertex3f(0.6, 0.5, 0.8);
    // glVertex3f(0.6, 0.2, 0.8);
    // glVertex3f(1.8, 0.2, 0.8);
    // glVertex3f(1.8, 0.5, 0.8);

    // glEnd();
    // glFlush();
    /* bottom of cube*/
    glVertex3f(0.6, 0.2, 0.8);
    glVertex3f(0.6, 0.2, 0.2);
    glVertex3f(1.8, 0.2, 0.2);
    glVertex3f(1.8, 0.2, 0.8);

    /* back of cube.*/
    glVertex3f(0.6, 0.5, 0.2);
    glVertex3f(0.6, 0.2, 0.2);
    glVertex3f(1.8, 0.2, 0.2);
    glVertex3f(1.8, 0.5, 0.2);

    //*********************ENTER WINDOW**********************************
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0.77, 0.83, 0.2);
    glVertex3f(0.75, 0.5, 0.2); //quad front window
    glVertex3f(1.2, 0.5, 0.2);
    glVertex3f(1.22, 0.83, 0.2);

    glVertex3f(1.27, 0.83, .2);
    glVertex3f(1.25, 0.5, 0.2); //quad back window
    glVertex3f(1.65, 0.5, 0.2);
    glVertex3f(1.67, 0.83, 0.2);

    glColor3f(r, g, b);
    glVertex3f(0.7, 0.85, 0.2);
    glVertex3f(0.7, 0.5, .2); //first separation
    glVertex3f(0.75, 0.5, 0.2);
    glVertex3f(0.77, 0.85, 0.2);

    glVertex3f(1.2, 0.85, 0.2);
    glVertex3f(1.2, 0.5, .2); //second separation
    glVertex3f(1.25, 0.5, 0.2);
    glVertex3f(1.27, 0.85, 0.2);

    glVertex3f(1.65, 0.85, 0.2);
    glVertex3f(1.65, 0.5, .2); //3d separation
    glVertex3f(1.7, 0.5, 0.2);
    glVertex3f(1.7, 0.85, 0.2);

    glVertex3f(0.75, 0.85, 0.2);
    glVertex3f(0.75, 0.83, 0.2); //line strip
    glVertex3f(1.7, 0.83, 0.2);
    glVertex3f(1.7, 0.85, 0.2);

    glVertex3f(0.75, 0.85, 0.8);
    glVertex3f(0.75, 0.83, 0.8); //line strip
    glVertex3f(1.7, 0.83, 0.8);
    glVertex3f(1.7, 0.85, 0.8);

    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0.77, 0.83, 0.8);
    glVertex3f(0.75, 0.5, 0.8); //quad front window
    glVertex3f(1.2, 0.5, 0.8);
    glVertex3f(1.22, 0.83, 0.8);

    glVertex3f(1.27, 0.83, .8);
    glVertex3f(1.25, 0.5, 0.8); //quad back window
    glVertex3f(1.65, 0.5, 0.8);
    glVertex3f(1.67, 0.83, 0.8);

    glColor3f(r, g, b);
    glVertex3f(0.7, 0.85, 0.8);
    glVertex3f(0.7, 0.5, .8); //first separation
    glVertex3f(0.75, 0.5, 0.8);
    glVertex3f(0.77, 0.85, 0.8);

    glVertex3f(1.2, 0.85, 0.8);
    glVertex3f(1.2, 0.5, .8); //second separation
    glVertex3f(1.25, 0.5, 0.8);
    glVertex3f(1.27, 0.85, 0.8);

    glVertex3f(1.65, 0.85, 0.8);
    glVertex3f(1.65, 0.5, .8);
    glVertex3f(1.7, 0.5, 0.8);
    glVertex3f(1.7, 0.85, 0.8);

    //**************************************************************
    /* top of cube*/
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0.6, 0.5, 0.8);
    glVertex3f(0.6, 0.5, 0.2); //quad front window
    glVertex3f(0.7, 0.85, 0.2);
    glVertex3f(0.7, 0.85, 0.8);

    glVertex3f(1.7, 0.85, .8);
    glVertex3f(1.7, 0.85, 0.2); //quad back window
    glVertex3f(1.8, 0.5, 0.2);
    glVertex3f(1.8, 0.5, 0.8);
    glPopMatrix();
  }
  glEnd();

  if (wheelflag)
  {
    glPushMatrix();
    glTranslatef(xw, 0, 0);
    glColor3f(0.5, .2, 0.3);
    glBegin(GL_QUADS);
    for (i = 0; i < 200; i += 0.2)
    {
      glVertex3f(-100 + i, 0, 1);
      glVertex3f(-99.9 + i, 0, 1);
      glVertex3f(-99.9 + i, 0.2, 1);
      glVertex3f(-100 + i, 0.2, 1);
      i += 0.5;
    }
    for (i = 0; i < 200; i += 0.2)
    {
      glVertex3f(-100 + i, 0, 0);
      glVertex3f(-99.9 + i, 0, 0);
      glVertex3f(-99.9 + i, 0.2, 0);
      glVertex3f(-100 + i, 0.2, 0);
      i += 0.5;
    }
    glEnd();
    glPopMatrix();
  }

  glEnd();
  //
  glBegin(GL_TRIANGLES); /* start drawing the cube.*/

  /* top of cube*/
  glColor3f(0.3, 0.3, 0.3);
  glVertex3f(0.6, 0.5, 0.8);
  glVertex3f(0.7, 0.85, 0.8); //tri front window
  glVertex3f(0.7, 0.5, 0.8);

  glVertex3f(0.6, 0.5, 0.2);
  glVertex3f(0.7, 0.85, 0.2); //tri front window
  glVertex3f(0.7, 0.5, 0.2);

  glVertex3f(1.7, 0.85, 0.2);
  glVertex3f(1.8, 0.5, 0.2); //tri back window
  glVertex3f(1.7, 0.5, 0.2);

  glVertex3f(1.7, 0.85, 0.8);
  glVertex3f(1.8, 0.5, 0.8); //tri back window
  glVertex3f(1.7, 0.5, 0.8);

  glEnd();
  glFlush();
  //********************WHEEL
  glPushMatrix();
  glColor3f(0.8,0.8,0.8);
  glTranslatef(1.65,0.2,0.38);
  glRotatef(90.0,0,1,0);
  gluCylinder(t,0.02,0.03,.25,10,10);
  glPopMatrix();

  glColor3f(0.7, 0.7, 0.7);
  glPushMatrix();
  glBegin(GL_LINE_STRIP);
  for (theta = 0; theta < 360; theta = theta + 40)
  {
    glVertex3f(0.6, 0.2, 0.72);
    glVertex3f(0.6 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.72);
  }
  glEnd();

  glBegin(GL_LINE_STRIP);
  for (theta = 0; theta < 360; theta = theta + 40)
  {
    glVertex3f(0.6, 0.2, 0.28);
    glVertex3f(0.6 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.28);
  }
  glEnd();

  glBegin(GL_LINE_STRIP);
  for (theta = 0; theta < 360; theta = theta + 40)
  {
    glVertex3f(1.7, 0.2, 0.28);
    glVertex3f(1.7 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.28);
  }
  glEnd();

  glBegin(GL_LINE_STRIP);
  for (theta = 0; theta < 360; theta = theta + 40)
  {
    glVertex3f(1.7, 0.2, 0.62);
    glVertex3f(1.7 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.62);
  }
  glEnd();
  glTranslatef(0.6, 0.2, 0.7);
  glColor3f(0, 0, 0);
  glutSolidTorus(0.05, 0.12, 10, 25);

  glTranslatef(0, 0, -0.4);
  glutSolidTorus(0.05, 0.12, 10, 25);

  glTranslatef(1.1, 0, 0);
  glutSolidTorus(0.05, 0.12, 10, 25);

  glTranslatef(0, 0, 0.4);
  glutSolidTorus(0.05, 0.12, 10, 25);
  glPopMatrix();
  //*************************************************************

  glPopMatrix();
  glEnable(GL_DEPTH_TEST);
  glutPostRedisplay();
  glutSwapBuffers();

  glFlush();
}

static void SpecialKeyFunc(int Key, int x, int y)
{
  switch (Key)
  {
  case GLUT_KEY_RIGHT:
    if (!wheelflag)
      xt += 0.2;
    if (wheelflag)
    {
      angle += 5;
      xw += 0.2;
    }
    glutPostRedisplay();
    break;

  case GLUT_KEY_LEFT:
    if (!wheelflag)
      xt -= 0.2;
    if (wheelflag)
    {
      angle += 5;
      xw -= 0.2;
    }
    glutPostRedisplay();
    break;
  }
}

void NormalKey(GLubyte key, GLint x, GLint y)
{
  switch (key)
  {
  case ESCAPE:
    printf("escape pressed. exit.\n");
    glutDestroyWindow(window);
    exit(0);
    break;

  case ' ':
    view = 1;
    DrawGLScene();
    break;

  case 'x':
    xangle += 5.0;
    glutPostRedisplay();
    break;

  case 'X':
    xangle -= 5.0;
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

  case 'u': /* Move up */
    yt += 0.2;
    glutPostRedisplay();
    break;

  case 'U':
    yt -= 0.2; /* Move down */
    glutPostRedisplay();
    break;

  case 'f': /* Move forward */
    zt += 0.2;
    glutPostRedisplay();
    break;

  case 'F':
    zt -= 0.2; /* Move away */
    glutPostRedisplay();
    break;

  case 'r':
    xangle = 0.0;
    yangle = 0.0;
    zangle = 0.0;
    yt = 0.0;
    zt = 0.0;
    xt = 0.0;
    xw = 0.0;
    angle = 0.0;
    glutPostRedisplay();
    break;

  default:
    break;
  }
}

GLuint LoadTexture(const char *filename)
{
  GLuint texture;
  int width, height;

  unsigned char *data;

  FILE *file;
  file = fopen(filename, "rb");

  if (file == NULL)
    return 0;

  data = (unsigned char *)malloc(Xsize * Ysize * 3);
  fread(data, Xsize * Ysize, 1, file);
  fclose(file);

  for (int i = 0; i < width * height; i++)
  {
    int index = i * 3;
    unsigned char B, R;
    B = data[index];
    R = data[index + 2];

    data[index] = R;
    data[index + 2] = B;
  }

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
  free(data);

  return texture;
}

void idle(void)
{
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  // display_string(10,340,"X-Y-Z KEYS FOR CORRESPONDING ROTATION",3);
  // display_string(10,280+30,"U-F FOR CAMERA VIEW SETTINGS",3);
  // display_string(10,250+30,"USE LEFT ARROW(<-) AND RIGHT ARROW(->) TO MOVE CAR",3);
  // display_string(10,220+30,"ESCAPE TO EXIT",3);

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(Xsize, Ysize);
  glutInitWindowPosition(20, 20);
  glutCreateWindow("3D CAR ANIMATION");

  // here
  // glEnable(GL_DEPTH_TEST);
  // glDepthFunc(GL_LESS);
  // glShadeModel(GL_SMOOTH);
  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);

  // GLuint texture[1];
  // texture[0] = LoadTexture("test.jpg");
  // glBindTexture (GL_TEXTURE_2D, texture[0]);

  glutDisplayFunc(DrawGLScene);
  glutKeyboardFunc(NormalKey);
  glutSpecialFunc(SpecialKeyFunc);

  InitGL(Xsize, Ysize);

  glEnable(GL_DEPTH_TEST);
  
  LoadGLTextures();

  glutMainLoop();
  return 1;
}
