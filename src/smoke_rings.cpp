#include "smoke_rings.h"
#include "main.h"

Smoke_ring::Smoke_ring(float x, float y, float z, float rad) {
    this->position = glm::vec3(x, y, z);
    int n = 25;
    int len = getCylSize(n);
    GLfloat ring[len + 5];
    drawCyl(0.0f, 0.0f, 0.0f, n, rad, rad, 0.5f, ring);

    this->ring = create3DObject(GL_TRIANGLES, len/3, ring, {102, 102, 153}, GL_FILL);
}

void Smoke_ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    float right_angle = (90.0f * PI) / 180.0f;
    glm::mat4 rotate_90 = glm::rotate(-right_angle, glm::vec3(1, 0, 0));
    Matrices.model *= translate * rotate_90;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ring);
}
