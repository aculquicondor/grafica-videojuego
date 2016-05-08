#include "TextureManager.h"


GLuint TextureManager::loadTexture(const std::string &filename,
                                   GLenum image_format, GLenum internal_format,
                                   GLint level, GLint border) {
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    FIBITMAP *dib(0);
    BYTE* bits(0);
    unsigned int width(0), height(0);
    GLuint textureID;

    fif = FreeImage_GetFileType(filename.c_str(), 0);
    if(fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename.c_str());
    if(fif == FIF_UNKNOWN)
        return 0;

    if(FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_Load(fif, filename.c_str());
    if(!dib)
        return 0;

    bits = FreeImage_GetBits(dib);
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);
    if((bits == 0) || (width == 0) || (height == 0))
        return 0;

    glGenTextures(1, &textureID);


    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, bits);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    FreeImage_Unload(dib);

    return textureID;
}
