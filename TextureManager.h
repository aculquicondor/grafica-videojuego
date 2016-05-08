#ifndef VIDEOGAME_TEXTUREMANAGER_H
#define VIDEOGAME_TEXTUREMANAGER_H

#include <iostream>

#include <GL/glew.h>
#include <FreeImage.h>


class TextureManager {
public:
    static GLuint loadTexture(const std::string &filename,
                              GLenum image_format = GL_RGB, GLenum internal_format = GL_RGB,
                              GLint level = 0, GLint border = 0);
};


#endif //VIDEOGAME_TEXTUREMANAGER_H
