#include "main.h"

#ifndef SMOKE_RINGS_H
#define SMOKE_RINGS_H


class Smoke_ring {
public:
    Smoke_ring() {}
    Smoke_ring(float x, float y, float z, float rad);
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *ring;
};

#endif
