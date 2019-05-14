#include "main.h"

#ifndef MOUNTAIN_H
#define MOUNTAIN_H


class Mountain {
public:
    Mountain() {}
    Mountain(float x, float y, float rad, float ht);
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *mountain;
};

#endif
