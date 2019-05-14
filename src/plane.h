#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, bool flag);
    void set_position(float x, float y);
    void tick();
    float yawAngle;
    float rollAngle;
    float pitchAngle;
    float len;
    float rad;
    float speed;
    float back_accel;
    float dir_x;
    float dir_y;
    float dir_z;
    float up_x;
    float up_y;
    float up_z;
    float perp_x;
    float perp_y;
    float perp_z;
    float hp;
    float fuel;
    glm::mat4 rotate;
private:
    VAO *body;
    VAO *wings;
    VAO *tails;
    VAO *top;
    VAO *circ1;
    VAO *circ2;
};

#endif
