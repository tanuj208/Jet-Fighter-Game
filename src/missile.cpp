#include "missile.h"
#include "main.h"

Missile::Missile(float x, float y, float z, float rad, float ht, float dir_x, float dir_y, float dir_z, glm::mat4 rotate, float speed, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotate = rotate;
    this->dir_x = dir_x;
    this->dir_y = dir_y;
    this->dir_z = dir_z;
    this->speed = speed;
    int n = 25;
    int len = getCylSize(n);
    int base_len = getPolSize(n);
    GLfloat mis[len + 5];
    GLfloat base[2*base_len + 5];
    drawCyl(0.0f, 0.0f, ht/2, n, rad, rad, ht, mis);
    drawPol(n, 0.0f, 0.0f, rad, base, 0.0f, 0);
    drawPol(n, 0.0f, 0.0f, rad, base, ht, base_len);

    this->missile = create3DObject(GL_TRIANGLES, len/3, mis, color, GL_FILL);
    this->base = create3DObject(GL_TRIANGLES, 2*base_len/3, base, color, GL_FILL);
}

void Missile::draw(glm::mat4 VP, bool flag) {
    Matrices.model = glm::mat4(1.0f);
    float right_angle = (90.0f * PI) / 180.0f;
    glm::mat4 rotate_90 = glm::rotate(-right_angle, glm::vec3(1, 0, 0));

    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    if(flag)
    {
        this->rotate[2][0] = this->rotate[1][0];
        this->rotate[2][1] = this->rotate[1][1];
        this->rotate[2][2] = this->rotate[1][2];
        this->rotate[1][0] = this->dir_x;
        this->rotate[1][1] = this->dir_y;
        this->rotate[1][2] = this->dir_z;
    }
    Matrices.model *= translate * this->rotate * rotate_90;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->missile);
    draw3DObject(this->base);
}

void Missile::tick() {
    float time_change = 1.0f/60.0f;
    float dist = time_change * this->speed;
    this->position.x += this->dir_x * dist;
    this->position.y += this->dir_y * dist;
    this->position.z += this->dir_z * dist;
}
