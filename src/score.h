#include "main.h"

#ifndef SCORE_H
#define SCORE_H


class Score {
public:
    Score() {}
    Score(float x, float y, string number);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    string number;
private:
    VAO *ob1;
    VAO *ob2;
    VAO *ob3;
    VAO *ob4;
    VAO *ob5;
    VAO *ob6;
    VAO *ob7;
};

#endif
