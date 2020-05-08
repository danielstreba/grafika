#include "draw.h"

void draw_skybox(GLuint skybox_texture_id[], vec3 position, float width, float height, float length)
{
    // Center the Skybox around the given x,y,z position
    position.x = position.x - width / 2;
    position.y = position.y - height / 2;
    position.z = position.z - length / 2;

    // Draw Front side
    glBindTexture(GL_TEXTURE_2D, skybox_texture_id[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position.x, position.y, position.z + length);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position.x, position.y + height, position.z + length);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position.x + width, position.y + height, position.z + length);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position.x + width, position.y, position.z + length);
    glEnd();

    // Draw Back side
    glBindTexture(GL_TEXTURE_2D, skybox_texture_id[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position.x + width, position.y, position.z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position.x + width, position.y + height, position.z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position.x, position.y + height, position.z);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position.x, position.y, position.z);
    glEnd();

    // Draw Left side
    glBindTexture(GL_TEXTURE_2D, skybox_texture_id[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position.x, position.y + height, position.z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position.x, position.y + height, position.z + length);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position.x, position.y, position.z + length);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position.x, position.y, position.z);
    glEnd();

    // Draw Right side
    glBindTexture(GL_TEXTURE_2D, skybox_texture_id[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position.x + width, position.y, position.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position.x + width, position.y, position.z + length);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position.x + width, position.y + height, position.z + length);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position.x + width, position.y + height, position.z);
    glEnd();

    // Draw Up side
    glBindTexture(GL_TEXTURE_2D, skybox_texture_id[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position.x + width, position.y + height, position.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position.x + width, position.y + height, position.z + length);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position.x, position.y + height, position.z + length);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position.x, position.y + height, position.z);
    glEnd();

    // Draw Down side
    glBindTexture(GL_TEXTURE_2D, skybox_texture_id[5]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position.x, position.y, position.z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position.x, position.y, position.z + length);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position.x + width, position.y, position.z + length);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position.x + width, position.y, position.z);
    glEnd();
}

void draw_board(const Scene *scene)
{
    glPushMatrix();
    glTranslatef(-0.5f, -0.5f, -0.02f);
    glBindTexture(GL_TEXTURE_2D, scene->chess_board.texture_id);
    draw_model(&(scene->chess_board.model));
    glPopMatrix();

    int i, j;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            int id = (i + j) % 2;

            glBindTexture(GL_TEXTURE_2D, scene->marble_texture_id[id]);
            glBegin(GL_QUADS);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(-0.5f + i, 0.5f + j, -0.01f);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(0.5f + i, 0.5f + j, -0.01f);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(0.5f + i, -0.5f + j, -0.01f);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-0.5f + i, -0.5f + j, -0.01f);
            glEnd();
        }
    }
}

void draw_pieces(const Scene *scene)
{
    int i, j, k;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            for (k = 0; k < 2; k++)
            {
                struct vec3 position = {.x = scene->game_board.tile[i][j][k].position.x,
                                        .y = scene->game_board.tile[i][j][k].position.y,
                                        .z = scene->game_board.tile[i][j][k].position.z};

                if (scene->current_tile->position.x == position.x &&
                    scene->current_tile->position.y == position.y &&
                    scene->current_tile->position.z == position.z)
                {
                    draw_highlight(position);
                }

                glPushMatrix();
                glTranslatef(position.x, position.y, position.z);
                glBindTexture(GL_TEXTURE_2D, scene->game_board.tile[i][j][k].object.texture_id);
                draw_model(&(scene->game_board.tile[i][j][k].object.model));
                glPopMatrix();
            }
        }
    }
}

void draw_highlight(const vec3 position)
{
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(position.x - 0.5f, position.y - 0.5f, position.z);
    glVertex3f(position.x - 0.5f, position.y - 0.5f, position.z + 2.0f);

    glVertex3f(position.x + 0.5f, position.y - 0.5f, position.z);
    glVertex3f(position.x + 0.5f, position.y - 0.5f, position.z + 2.0f);

    glVertex3f(position.x - 0.5f, position.y + 0.5f, position.z);
    glVertex3f(position.x - 0.5f, position.y + 0.5f, position.z + 2.0f);

    glVertex3f(position.x + 0.5f, position.y + 0.5f, position.z);
    glVertex3f(position.x + 0.5f, position.y + 0.5f, position.z + 2.0f);

    glVertex3f(position.x + 0.5f, position.y + 0.5f, position.z + 2.0f);
    glVertex3f(position.x - 0.5f, position.y + 0.5f, position.z + 2.0f);

    glVertex3f(position.x + 0.5f, position.y + 0.5f, position.z);
    glVertex3f(position.x - 0.5f, position.y + 0.5f, position.z);

    glVertex3f(position.x + 0.5f, position.y + 0.5f, position.z + 2.0f);
    glVertex3f(position.x + 0.5f, position.y - 0.5f, position.z + 2.0f);

    glVertex3f(position.x + 0.5f, position.y + 0.5f, position.z);
    glVertex3f(position.x + 0.5f, position.y - 0.5f, position.z);

    glVertex3f(position.x - 0.5f, position.y + 0.5f, position.z + 2.0f);
    glVertex3f(position.x - 0.5f, position.y - 0.5f, position.z + 2.0f);

    glVertex3f(position.x - 0.5f, position.y + 0.5f, position.z);
    glVertex3f(position.x - 0.5f, position.y - 0.5f, position.z);

    glVertex3f(position.x + 0.5f, position.y - 0.5f, position.z + 2.0f);
    glVertex3f(position.x - 0.5f, position.y - 0.5f, position.z + 2.0f);

    glVertex3f(position.x + 0.5f, position.y - 0.5f, position.z);
    glVertex3f(position.x - 0.5f, position.y - 0.5f, position.z);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
}