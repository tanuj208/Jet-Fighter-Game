#include "main.h"

#ifndef ISLAND_H
#define ISLAND_H


class Island {
public:
    Island() {}
    Island(float x, float y, float rad);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    float rad;
private:
    VAO *island;
};

#endif
