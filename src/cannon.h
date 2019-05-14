#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float rad1, float rad2, float ht, float island_rad);
    glm::vec3 position;
    glm::vec3 dir;
    glm::mat4 rotate;
    void draw(glm::mat4 VP);
    void tick(float x_cor, float y_cor, float z_cor);
    float island_rad;
private:
    VAO *cannon;
};

#endif
