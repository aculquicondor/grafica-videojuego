#ifndef VIDEOGAME_MODEL_H
#define VIDEOGAME_MODEL_H

#include <vector>
#include <fstream>
#include <cstdio>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <GL/gl.h>


class Model {
public:
    Model(const std::string filename);

    void draw() const;
private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;

    std::vector<unsigned int> vertexIndices;
    std::vector<unsigned int> uvIndices;
    std::vector<unsigned int> normalIndices;
};


#endif //VIDEOGAME_MODEL_H
