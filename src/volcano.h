#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y, float rad1, float rad2, float rad3, float ht1, float ht2);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    // int ash_count;
private:
    VAO *volcano1;
    VAO *volcano2;
    // VAO *ashes[52];
};

#endif
