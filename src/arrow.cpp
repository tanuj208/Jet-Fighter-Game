#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y, float z, float tarx, float tary) {
    this->position = glm::vec3(x, y, z);
    this->target = glm::vec3(tarx, tary, 2.0f);

    int len = getCuboidSize();
    GLfloat ar2[len + 5];
    GLfloat ar1[len + 5] = {
        0.0f, 2.0f, 0.2f,
        -0.5f, 1.0f, 0.2f,
        0.5f, 1.0f, 0.2f,
        0.0f, 2.0f, -0.2f,
        -0.5f, 1.0f, -0.2f,
        0.5f, 1.0f, -0.2f,
    };
    int rect_len = getRectSize();
    drawRect(0.0f, 2.0f, 0.2f, -0.5f, 1.0f, 0.2f, -0.5f, 1.0f, -0.2f, 0.0f, 2.0f, -0.2f, ar1, 18);
    drawRect(0.0f, 2.0f, 0.2f, 0.5f, 1.0f, 0.2f, 0.5f, 1.0f, -0.2f, 0.0f, 2.0f, -0.2f, ar1, 18+rect_len);
    drawRect(-0.5f, 1.0f, 0.2f, 0.5f, 1.0f, 0.2f, 0.5f, 1.0f, -0.2f, -0.5f, 1.0f, -0.2f, ar1, 18+2*rect_len);

    drawCuboid(0.0f, 0.0f, 0.0f, 0.4f, 2.0f, 0.4f, ar2);

    this->ar1 = create3DObject(GL_TRIANGLES, rect_len + 6, ar1, {204, 51, 0}, GL_FILL);
    this->ar2 = create3DObject(GL_TRIANGLES, len/3, ar2, {204, 51, 0}, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);

    glm::mat4 rotate = glm::mat4(1.0f);

    glm::vec3 dir = this->target - this->position;
    dir = glm::normalize(dir);
    glm::vec3 up(0, 0, 1);
    glm::vec3 perp = glm::cross(up, dir);
    perp = glm::normalize(perp);

    rotate[0][0] = perp[0];
    rotate[0][1] = perp[1];
    rotate[0][2] = perp[2];

    rotate[1][0] = dir[0];
    rotate[1][1] = dir[1];
    rotate[1][2] = dir[2];

    rotate[2][0] = up[0];
    rotate[2][1] = up[1];
    rotate[2][2] = up[2];

    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ar1);
    draw3DObject(this->ar2);
}
