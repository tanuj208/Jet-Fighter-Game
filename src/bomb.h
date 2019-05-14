#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z, float rad, float ht, float dir_x, float dir_y, float forward_speed);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    float speed;
    float forward_speed;
    float dir_x;
    float dir_y;
    float angular_speed;
    float rotation;
    float back_accel;
private:
    VAO *bomb;
    VAO *base;
};

#endif
