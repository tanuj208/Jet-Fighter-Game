#include "island.h"
#include "main.h"

Island::Island(float x, float y, float rad) {
    this->position = glm::vec3(x, y, -9.9);
    this->rad = rad;
    int n = rand()%20;
    n+=4;
    int len = getPolSize(n);
    GLfloat island[len + 5];
    drawPol(n, 0.0f, 0.0f, rad, island, 0.0f, 0);

    this->island = create3DObject(GL_TRIANGLES, len/3, island, {255, 153, 51}, GL_FILL);
}

void Island::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->island);
}
