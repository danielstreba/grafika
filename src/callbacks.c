#include "callbacks.h"
#include "draw.h"

#include <stdio.h>

struct
{
  int x;
  int y;
  int is_down;
} mouse_device;

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  set_view(&camera);
  draw_scene(&scene);

  glPopMatrix();

  if (is_help_displayed)
  {
    draw_help(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
  }

  glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
  int x, y, w, h;
  double ratio;

  ratio = (double)width / height;
  if (ratio > VIEWPORT_RATIO)
  {
    w = (int)((double)height * VIEWPORT_RATIO);
    h = height;
    x = (width - w) / 2;
    y = 0;
  }
  else
  {
    w = width;
    h = (int)((double)width / VIEWPORT_RATIO);
    x = 0;
    y = (height - h) / 2;
  }

  glViewport(x, y, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01f, 15000.0f);
}

void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_MOUSE_WHEEL_DOWN)
  {
    if (camera.distance <= 50.0f)
    {
      camera.distance += 0.5f;
      glutPostRedisplay();
    }
  }
  else if (button == GLUT_MOUSE_WHEEL_UP)
  {
    if (camera.distance >= 1.0f)
    {
      camera.distance -= 0.5f;
      glutPostRedisplay();
    }
  }
  else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
  {
    mouse_device.is_down = TRUE;
    mouse_device.x = x;
    mouse_device.y = y;
  }

  if (state == GLUT_UP)
  {
    mouse_device.is_down = FALSE;
  }
}

void motion(int x, int y)
{
  rotate_camera(&camera, mouse_device.x - x, mouse_device.y - y);
  mouse_device.x = x;
  mouse_device.y = y;

  glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'w':
  case 'W':
    set_camera_speed(&camera, 5);
    break;
  case 's':
  case 'S':
    set_camera_speed(&camera, -5);
    break;
  case 'a':
  case 'A':
    set_camera_side_speed(&camera, 5);
    break;
  case 'd':
  case 'D':;
    set_camera_side_speed(&camera, -5);
    break;
  case '+':;
    GLfloat current_ambient[4], current_diffuse[4], current_specular[4];
    glGetLightfv(GL_LIGHT0, GL_AMBIENT, current_ambient);
    glGetLightfv(GL_LIGHT0, GL_DIFFUSE, current_diffuse);
    glGetLightfv(GL_LIGHT0, GL_SPECULAR, current_specular);

    if (current_specular[3] < 1.0f)
    {
      int i;
      for (i = 0; i < 4; ++i)
      {
        current_ambient[i] += 0.1f;
        current_diffuse[i] += 0.1f;
        current_specular[i] += 0.1f;
      }

      glLightfv(GL_LIGHT0, GL_AMBIENT, current_ambient);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, current_diffuse);
      glLightfv(GL_LIGHT0, GL_SPECULAR, current_specular);
    }
    break;

  case '-':;
    glGetLightfv(GL_LIGHT0, GL_AMBIENT, current_ambient);
    glGetLightfv(GL_LIGHT0, GL_DIFFUSE, current_diffuse);
    glGetLightfv(GL_LIGHT0, GL_SPECULAR, current_specular);

    if (current_specular[3] > 0.0f)
    {
      int i;
      for (i = 0; i < 4; ++i)
      {
        current_ambient[i] -= 0.1f;
        current_diffuse[i] -= 0.1f;
        current_specular[i] -= 0.1f;
      }

      glLightfv(GL_LIGHT0, GL_AMBIENT, current_ambient);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, current_diffuse);
      glLightfv(GL_LIGHT0, GL_SPECULAR, current_specular);
    }
    break;

  case 'i':
  {
    int x = scene.current_tile->position.x;
    int y = scene.current_tile->position.y + 1;
    int z = scene.current_tile->position.z / 2;
    struct Tile *next_tile = &scene.game_board.tile[x][y][z];
    if (!next_tile->is_occupied && y <= 7)
    {
      next_tile->object = scene.current_tile->object;
      scene.current_tile->object = EmptyObject;
      scene.current_tile->is_occupied = FALSE;

      scene.current_tile = next_tile;
      scene.current_tile->is_occupied = TRUE;
    }
    break;
  }

  case 'k':
  {
    int x = scene.current_tile->position.x;
    int y = scene.current_tile->position.y - 1;
    int z = scene.current_tile->position.z / 2;
    struct Tile *next_tile = &scene.game_board.tile[x][y][z];
    if (!next_tile->is_occupied && y >= 0)
    {
      next_tile->object = scene.current_tile->object;
      scene.current_tile->object = EmptyObject;
      scene.current_tile->is_occupied = FALSE;

      scene.current_tile = next_tile;
      scene.current_tile->is_occupied = TRUE;
    }
    break;
  }

  case 'j':
  {
    int x = scene.current_tile->position.x - 1;
    int y = scene.current_tile->position.y;
    int z = scene.current_tile->position.z / 2;
    struct Tile *next_tile = &scene.game_board.tile[x][y][z];
    if (!next_tile->is_occupied && x >= 0)
    {
      next_tile->object = scene.current_tile->object;
      scene.current_tile->object = EmptyObject;
      scene.current_tile->is_occupied = FALSE;

      scene.current_tile = next_tile;
      scene.current_tile->is_occupied = TRUE;
    }
    break;
  }

  case 'l':
  {
    int x = scene.current_tile->position.x + 1;
    int y = scene.current_tile->position.y;
    int z = scene.current_tile->position.z / 2;
    struct Tile *next_tile = &scene.game_board.tile[x][y][z];
    if (!next_tile->is_occupied && x <= 7)
    {
      next_tile->object = scene.current_tile->object;
      scene.current_tile->object = EmptyObject;
      scene.current_tile->is_occupied = FALSE;

      scene.current_tile = next_tile;
      scene.current_tile->is_occupied = TRUE;
    }
    break;
  }
  }

  glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'w':
  case 'W':
  case 's':
  case 'S':
    set_camera_speed(&camera, 0.0f);
    break;

  case 'a':
  case 'A':
  case 'd':
  case 'D':
    set_camera_side_speed(&camera, 0.0f);
    break;
  }

  glutPostRedisplay();
}

void keyboard_special(int key, int x, int y)
{
  switch (key)
  {
  case GLUT_KEY_F1:
    is_help_displayed = (is_help_displayed) ? FALSE : TRUE;
    break;

  case GLUT_KEY_F2:
    reset_scene(&scene);
    break;

  case GLUT_KEY_PAGE_UP:
  {
    int x = scene.current_tile->position.x;
    int y = scene.current_tile->position.y;
    int z = 1;
    struct Tile *next_tile = &scene.game_board.tile[x][y][z];
    if (scene.current_tile->position.z == 0.0f && !next_tile->is_occupied)
    {
      next_tile->object = scene.current_tile->object;
      scene.current_tile->object = EmptyObject;
      scene.current_tile->is_occupied = FALSE;

      scene.current_tile = next_tile;
      scene.current_tile->is_occupied = TRUE;
    }
    break;
  }

  case GLUT_KEY_PAGE_DOWN:
  {
    int x = scene.current_tile->position.x;
    int y = scene.current_tile->position.y;
    int z = 0;
    struct Tile *next_tile = &scene.game_board.tile[x][y][z];
    if (scene.current_tile->position.z == 2.0f && !next_tile->is_occupied)
    {
      next_tile->object = scene.current_tile->object;
      scene.current_tile->object = EmptyObject;
      scene.current_tile->is_occupied = FALSE;

      scene.current_tile = next_tile;
      scene.current_tile->is_occupied = TRUE;
    }
    break;
  }

  case GLUT_KEY_UP:
  {
    if (scene.current_tile->position.z == 2.0f)
    {
      break;
    }

    int x = (int)scene.current_tile->position.x;
    int z = 0;

    int i;
    for (i = (int)scene.current_tile->position.y + 1; i < 8; i++)
    {
      struct Tile *next_tile = &scene.game_board.tile[x][i][z];
      if (next_tile->is_occupied == 1)
      {
        scene.current_tile = next_tile;
        break;
      }
    }
    break;
  }

  case GLUT_KEY_DOWN:
  {
    if (scene.current_tile->position.z == 2.0f)
    {
      break;
    }

    int x = (int)scene.current_tile->position.x;
    int z = 0;

    int i;
    for (i = (int)scene.current_tile->position.y - 1; i >= 0; i--)
    {
      struct Tile *next_tile = &scene.game_board.tile[x][i][z];
      if (next_tile->is_occupied == 1)
      {
        scene.current_tile = next_tile;
        break;
      }
    }
    break;
  }

  case GLUT_KEY_RIGHT:
  {
    if (scene.current_tile->position.z == 2.0f)
    {
      break;
    }

    int y = (int)scene.current_tile->position.y;
    int z = 0;

    int i;
    for (i = (int)scene.current_tile->position.x + 1; i < 8; i++)
    {
      struct Tile *next_tile = &scene.game_board.tile[i][y][z];
      if (next_tile->is_occupied == 1)
      {
        scene.current_tile = next_tile;
        break;
      }
    }
    break;
  }

  case GLUT_KEY_LEFT:
  {
    if (scene.current_tile->position.z == 2.0f)
    {
      break;
    }

    int y = (int)scene.current_tile->position.y;
    int z = 0;

    int i;
    for (i = (int)scene.current_tile->position.x - 1; i >= 0; i--)
    {
      struct Tile *next_tile = &scene.game_board.tile[i][y][z];
      if (next_tile->is_occupied == 1)
      {
        scene.current_tile = next_tile;
        break;
      }
    }
    break;
  }
  
  glutPostRedisplay();
  }
}

void idle()
{
  static int last_frame_time = 0;
  int current_time;
  double elapsed_time;

  current_time = glutGet(GLUT_ELAPSED_TIME);
  elapsed_time = (double)(current_time - last_frame_time) / 1000;
  last_frame_time = current_time;

  update_camera(&camera, elapsed_time);

  glutPostRedisplay();
}
