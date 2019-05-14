#include "main.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H


class Dashboard {
public:
    Dashboard() {}
    Dashboard(float fuel_remain, float hp_remain, float speed, float altitude, float w, float h, float dir_x, float dir_y);
    glm::vec3 position;
    void draw(glm::mat4 VP);
private:
    VAO *fuelbar;
    VAO *fuel;
    VAO *hpbar;
    VAO *hp;
    VAO *speedbar;
    VAO *speedcirc;
    VAO *speed;
    VAO *altitudebar;
    VAO *altitude;
    VAO *compassbar;
    VAO *compassNeedle1;
    VAO *compassNeedle2;
};

#endif
