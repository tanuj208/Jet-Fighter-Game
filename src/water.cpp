#include "water.h"
#include "main.h"

Water::Water(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    int n = 100;
    int len = getRectSize();
    GLfloat water[len+5];
    drawRect(-1000.0f, -1000.0f, 0.0f, -1000.0f, 1000.0f, 0.0f, 1000.0f, 1000.0f, 0.0f, 1000.0f, -1000.0f, 0.0f, water, 0);

    this->water = create3DObject(GL_TRIANGLES, len/3, water, {0, 119, 190}, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->water);
}
