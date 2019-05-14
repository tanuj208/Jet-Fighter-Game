#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z, float r1, float r2, float r3, float r4, float h, float H, float dim);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    float speed;
private:
    VAO *fr1;
    VAO *fr2;
    VAO *fr3;
    VAO *lines;
    VAO *box;
};

#endif
