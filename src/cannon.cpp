#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, float rad1, float rad2, float ht, float island_rad) {
    this->position = glm::vec3(x, y, -8.4);
    this->island_rad = island_rad;
    int n = 25;
    int cyl_len = getCylSize(n);
    int base_len = getCuboidSize();

    GLfloat base[base_len + 5];
    GLfloat cannon[cyl_len + 5];
    drawCyl(0.0f, 0.0f, ht/2, n, rad1, rad2, ht, cannon);

    this->cannon = create3DObject(GL_TRIANGLES, cyl_len/3, cannon, {51, 51, 51}, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);

    glm::vec3 perp(-this->dir[1], this->dir[0], 0.0f);
    perp = glm::normalize(perp);
    glm::vec3 third = glm::cross(this->dir, perp);
    third = glm::normalize(third);

    glm::mat4 rotate = glm::mat4(1.0f);
    rotate[0][0] = perp[0];
    rotate[0][1] = perp[1];
    rotate[0][2] = perp[2];

    rotate[2][0] = this->dir[0];
    rotate[2][1] = this->dir[1];
    rotate[2][2] = this->dir[2];

    rotate[1][0] = third[0];
    rotate[1][1] = third[1];
    rotate[1][2] = third[2];

    Matrices.model *= translate * rotate;
    this->rotate = rotate;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->cannon);
}

void Cannon::tick(float x_cor, float y_cor, float z_cor) {
    glm::vec3 dir(x_cor - this->position.x, y_cor - this->position.y, z_cor - this->position.z);
    dir = glm::normalize(dir);
    this->dir = dir;
}