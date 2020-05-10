#include "callbacks.h"
#include "init.h"

/**
 * Set the callbacks for GLUT.
 */
void set_callbacks()
{
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboard_up);
  glutSpecialFunc(keyboard_special);
  glutIdleFunc(idle);
}

/**
 * Main function
 */
int main(int argc, char *argv[])
{
  int window;

  glutInit(&argc, argv);

  glutInitWindowSize(1280, 720);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);

  window = glutCreateWindow("Chess - Streba Daniel (H0SRE6)");
  glutSetWindow(window);

  init_opengl();
  init_scene(&scene);
  init_camera(&camera);
  set_callbacks();

  glutMainLoop();

  return 0;
}
