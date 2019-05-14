#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H

class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z, float rad, float ht, float dir_x, float dir_y, float dir_z, glm::mat4 rotate, float speed, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP, bool flag);
    void tick();
    float speed;
    float dir_x;
    float dir_y;
    float dir_z;
    glm::mat4 rotate;
private:
    VAO *missile;
    VAO *base;
};

#endif
