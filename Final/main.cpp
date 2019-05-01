#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <SOIL/SOIL.h>

#define ESCAPE 27
#define MAX_PARTICLES 2000
#define SMOKE_PARTICLES 30
float slowdown = 1.0;
float velocity = 0.8;
float hailSize = 0.012;
float zoom = -40.0;

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

particles par_sys[1000*MAX_PARTICLES];
particles par_sys_smoke[MAX_PARTICLES];


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
      "putih.jpg",
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
  gluPerspective(45.0, Width / Height, 0.1, 100.0);
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

  par_sys_smoke[i].alive = true;
  par_sys_smoke[i].life = 1.0;
  par_sys_smoke[i].fade = float(rand() % 100) / 1000.0f + 0.003f;

  par_sys_smoke[i].xpos = 1.65;
  par_sys_smoke[i].ypos = 0.2;
  par_sys_smoke[i].zpos = 0.38;

  par_sys_smoke[i].red = 0.8;
  par_sys_smoke[i].green = 0.8;
  par_sys_smoke[i].blue = 0.8;

  par_sys_smoke[i].vel = 0.9;
  par_sys_smoke[i].gravity = 0.4; //-0.8;

}

void drawRain()
{
  float x, y, z;
  for (int loop = 0; loop < 100*MAX_PARTICLES; loop = loop + 2)
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



void drawSmoke() {
  float x, y, z;
  float slowdown = 5.0;
  for (int loop = 0; loop < MAX_PARTICLES/2; loop=loop+2) {
    if (par_sys_smoke[loop].alive == true) {
      x = par_sys_smoke[loop].xpos;
      y = par_sys_smoke[loop].ypos;
      z = par_sys_smoke[loop].zpos;

      // Draw particles
      if(x >1.85) {
        glColor3f(0.2, 0.2, 0.2);
        glPushMatrix();
        glTranslatef(x, y, z);
        glutSolidSphere(0.025, 16, 16);
        glPopMatrix();
      }

      // Update values
      //Move
      par_sys_smoke[loop].xpos += par_sys_smoke[loop].vel / (slowdown*1000);
      par_sys_smoke[loop].vel += par_sys_smoke[loop].gravity;
      // Decay
      par_sys_smoke[loop].life -= par_sys_smoke[loop].fade;

      //Revive
      if (par_sys_smoke[loop].life < 0.0) {
        initParticles(loop);
      }
    }
  }
}


GLvoid InitGL(GLfloat Width, GLfloat Height)
{

  glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
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
      glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
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
    drawSmoke();
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

    glRotatef(180.0, 0.0, 1.0, 0.0);
    glTranslatef(-1.1, 0.4, 0.0);
    glBegin(GL_QUADS); /* OBJECT MODULE*/

    glColor3f(1.0,1.0, 1.0);
    glTexCoord2f(-0.7500f, -0.5000f);
    glVertex3f(-0.7500f, -0.5000f, -0.5f);
    glTexCoord2f(0.1875f, -0.5000f);
    glVertex3f( 0.1875f, -0.5000f, -0.5f);
    glTexCoord2f(0.1875f, 0.6670f);
    glVertex3f( 0.1875f,  0.6670f, -0.5f);
    glTexCoord2f(-0.7500f, 0.6670f);
    glVertex3f(-0.7500f,  0.6670f, -0.5f);

    glTexCoord2f(0.1875f, -0.5000f);
    glVertex3f(0.1875f, -0.5000f, -0.5f);
    glTexCoord2f(0.8125f, -0.5000f);
    glVertex3f(0.8125f, -0.5000f, -0.5f);
    glTexCoord2f(0.8125f,  0.1667f);
    glVertex3f(0.8125f,  0.1667f, -0.5f);
    glTexCoord2f(0.1875f,  0.1667f);
    glVertex3f(0.1875f,  0.1667f, -0.5f); 
    
    glTexCoord2f(-0.7500f, -0.5000f);
    glVertex3f(-0.7500f, -0.5000f,  0.5f);
    glTexCoord2f(0.1875f, -0.5000f);
    glVertex3f(0.1875f, -0.5000f,  0.5f);
    glTexCoord2f(0.1875f,  0.6670f);
    glVertex3f(0.1875f,  0.6670f,  0.5f);
    glTexCoord2f(-0.7500f,  0.6670f);
    glVertex3f(-0.7500f,  0.6670f,  0.5f);  

    glTexCoord2f(0.1875f, -0.5000f);
    glVertex3f(0.1875f, -0.5000f,  0.5f);
    glTexCoord2f(0.8125f, -0.5000f);
    glVertex3f(0.8125f, -0.5000f,  0.5f);
    glTexCoord2f(0.8125f,  0.1667f);
    glVertex3f(0.8125f,  0.1667f,  0.5f);
    glTexCoord2f(0.1875f,  0.1667f);
    glVertex3f(0.1875f,  0.1667f,  0.5f);

    glTexCoord2f(-0.75f,  0.667f);
    glVertex3f(-0.75f,  0.667f,  0.5f);
    glTexCoord2f(-0.75f,  0.667f);
    glVertex3f(-0.75f,  0.667f, -0.5f);
    glTexCoord2f(-0.75f, -0.500f);
    glVertex3f(-0.75f, -0.500f, -0.5f);
    glTexCoord2f(-0.75f, -0.500f);
    glVertex3f(-0.75f, -0.500f,  0.5f);

    glTexCoord2f(0.1875f,  0.6670f);
    glVertex3f(0.1875f,  0.6670f,  0.5f);
    glTexCoord2f(0.1875f,  0.6670f);
    glVertex3f(0.1875f,  0.6670f, -0.5f);
    glTexCoord2f(0.1875f,  0.1667f);
    glVertex3f(0.1875f,  0.1667f, -0.5f);
    glTexCoord2f(0.1875f,  0.1667f);
    glVertex3f(0.1875f,  0.1667f,  0.5f);

    glTexCoord2f(0.8125f,  0.1667f);
    glVertex3f(0.8125f,  0.1667f,  0.5f);
    glTexCoord2f(0.8125f,  0.1667f);
    glVertex3f(0.8125f,  0.1667f, -0.5f);
    glTexCoord2f(0.8125f, -0.5f);
    glVertex3f(0.8125f, -0.5f, -0.5f);
    glTexCoord2f(0.8125f, -0.5f);
    glVertex3f(0.8125f, -0.5f,  0.5f);

    glTexCoord2f(-0.7500f, -0.5f);
    glVertex3f(-0.7500f, -0.5f, -0.5f);
    glTexCoord2f(0.8125f, -0.5f);
    glVertex3f(0.8125f, -0.5f, -0.5f);
    glTexCoord2f(0.8125f, -0.5f);
    glVertex3f(0.8125f, -0.5f,  0.5f);
    glTexCoord2f(-0.7500f, -0.5f);
    glVertex3f(-0.7500f, -0.5f,  0.5f);

    glTexCoord2f(-0.7500f,  0.667f);
    glVertex3f(-0.7500f,  0.667f, -0.5f);
    glTexCoord2f(0.1875f,  0.667f);
    glVertex3f(0.1875f,  0.667f, -0.5f);
    glTexCoord2f(0.1875f,  0.667f);
    glVertex3f(0.1875f,  0.667f,  0.5f);
    glTexCoord2f(-0.7500f,  0.667f);
    glVertex3f(-0.7500f,  0.667f,  0.5f);

    glTexCoord2f(0.1875f,  0.1667f);
    glVertex3f(0.1875f,  0.1667f, -0.5f);
    glTexCoord2f(0.8125f,  0.1667f);
    glVertex3f(0.8125f,  0.1667f, -0.5f);
    glTexCoord2f(0.8125f,  0.1667f);
    glVertex3f(0.8125f,  0.1667f,  0.5f);
    glTexCoord2f(0.1875f,  0.1667f);
    glVertex3f(0.1875f,  0.1667f,  0.5f);

    glPopMatrix();
  }
  glEnd();

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

  case 'w':
    xangle += 5.0;
    glutPostRedisplay();
    break;

  case 's':
    xangle -= 5.0;
    glutPostRedisplay();
    break;

  case 'a':
    yangle += 5.0;
    glutPostRedisplay();
    break;

  case 'd':
    yangle -= 5.0;
    glutPostRedisplay();
    break;

  case 'q':
    zangle += 5.0;
    glutPostRedisplay();
    break;

  case 'e':
    zangle -= 5.0;
    glutPostRedisplay();
    break;

  case 'u': /* Move up */
    yt += 0.2;
    glutPostRedisplay();
    break;

  case 'j':
    yt -= 0.2; /* Move down */
    glutPostRedisplay();
    break;

  case 'f': /* Move forward */
    zt += 0.2;
    glutPostRedisplay();
    break;

  case 'z':
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
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(Xsize, Ysize);
  glutInitWindowPosition(20, 20);
  glutCreateWindow("GRAFKOM");

  glutDisplayFunc(DrawGLScene);
  glutKeyboardFunc(NormalKey);
  glutSpecialFunc(SpecialKeyFunc);

  InitGL(Xsize, Ysize);

  glEnable(GL_DEPTH_TEST);
  
  LoadGLTextures();

  glutMainLoop();
  return 1;
}
