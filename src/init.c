#include "init.h"

#include <GL/glut.h>

void init_opengl()
{
  glShadeModel(GL_SMOOTH);

  glEnable(GL_NORMALIZE);
  glEnable(GL_AUTO_NORMAL);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearStencil(0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);

  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glEnable(GL_TEXTURE_2D);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}
