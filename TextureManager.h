#ifndef VIDEOGAME_TEXTUREMANAGER_H
#define VIDEOGAME_TEXTUREMANAGER_H

#include <iostream>

#include <GL/glew.h>
#include <FreeImage.h>


class TextureManager {
public:
    GLuint loadTexture(const std::string &filename, GLenum image_format = GL_RGB, GLenum internal_format = GL_RGB,
                       GLint level = 0, GLint border = 0);
    static TextureManager &instance();
private:
    explicit TextureManager();
    virtual ~TextureManager();
    TextureManager(const TextureManager &tm) = delete;
    TextureManager& operator=(const TextureManager &tm) = delete;

    static TextureManager* _inst;
};


#endif //VIDEOGAME_TEXTUREMANAGER_H
