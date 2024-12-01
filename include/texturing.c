#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/texturing.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb-master/stb_image.h"

void initTexture(char* pathToImg, unsigned int *texture) {
    int width, height, nrChannels;

    unsigned char *data  = stbi_load(pathToImg, &width, &height, &nrChannels, 0);
    printf("%i %i %i\n", width, height, nrChannels);

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGBA, 
        width, height, 
        0, 
        nrChannels == 4? GL_RGBA : GL_RGB, 
        GL_UNSIGNED_BYTE, 
        data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
}

void renderImage(float width, float height, float xPos, float yPos, unsigned int texture) {
    float vertices[] = {
        xPos + width, yPos + height, 0.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,

        xPos + width, yPos, 0.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 0.0f,

        xPos, yPos, 0.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 0.0f,

        xPos, yPos + height, 0.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 1.0f,
    };

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.5);

    glPushMatrix();
    // -
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(2, GL_FLOAT, 8 * sizeof(float), vertices);
    glTexCoordPointer(2, GL_FLOAT, 8 * sizeof(float), vertices + 6);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    //-
    glPopMatrix();
    glDisable(GL_ALPHA_TEST);
}

void renderImageFromMatrix (float vertices[], unsigned int texture)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.5);

    glPushMatrix();
    // -
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(2, GL_FLOAT, 8 * sizeof(float), vertices);
    glTexCoordPointer(2, GL_FLOAT, 8 * sizeof(float), vertices + 6);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    // -
    glPopMatrix();
    glDisable(GL_ALPHA_TEST);
}
