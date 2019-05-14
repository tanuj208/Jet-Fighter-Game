#include "main.h"

#ifndef POWERUP_H
#define POWERUP_H


class Powerup {
public:
    Powerup() {}
    Powerup(float x, float y, float z, bool type);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    bool fuel;
private:
    VAO *powerup;
};

#endif
