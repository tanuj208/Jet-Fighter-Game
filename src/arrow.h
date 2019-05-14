#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z, float tarx, float tary);
    glm::vec3 target;
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *ar1;
    VAO *ar2;
};

#endif
