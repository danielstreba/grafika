#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "scene.h"

#define VIEWPORT_RATIO (16.0f / 9.0f)
#define VIEWPORT_ASPECT 45.0f

#define GLUT_MOUSE_WHEEL_UP 3
#define GLUT_MOUSE_WHEEL_DOWN 4

/**
 * Scene
 */
Scene scene;

/**
 * Camera
 */
Camera camera;

/**
 * Call when need to display the graphical content
 */
void display();

/**
 * Call after windows resizing
 */
void reshape(GLsizei width, GLsizei height);

/**
 * Call after mouse button event
 */
void mouse(int button, int state, int x, int y);

/**
 * Call after mouse event
 */
void motion(int x, int y);

/**
 * Call after keyboard event
 */
void keyboard(unsigned char key, int x, int y);

/**
 * Call after keyboard release event
 */
void keyboard_up(unsigned char key, int x, int y);

/**
  * Call after special key (function keys, etc.) event
  */
void keyboard_special(int key, int x, int y);

/**
 * Call when there is no other event
 */
void idle();

#endif /* CALLBACKS_H */
