#include "bomb.h"
#include "main.h"

Bomb::Bomb(float x, float y, float z, float rad, float ht, float dir_x, float dir_y, float forward_speed) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->angular_speed = 0;
    this->speed = 0;
    this->dir_x = dir_x;
    this->dir_y = dir_y;
    this->forward_speed = forward_speed;
    this->back_accel = -20.0f;
    int n = 25;
    int len = getCylSize(n);
    int base_len = getPolSize(n);
    GLfloat mis[len + 5];
    GLfloat base[2*base_len + 5];
    drawCyl(0.0f, 0.0f, ht/2, n, rad, rad, ht, mis);
    drawPol(n, 0.0f, 0.0f, rad, base, 0.0f, 0);
    drawPol(n, 0.0f, 0.0f, rad, base, ht, base_len);

    this->bomb = create3DObject(GL_TRIANGLES, len/3, mis, {0, 51, 0}, GL_FILL);
    this->base = create3DObject(GL_TRIANGLES, 2*base_len/3, base, {0, 51, 0}, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    float right_angle = (90.0f * PI) / 180.0f;
    glm::mat4 rotate_90 = glm::rotate(-right_angle, glm::vec3(1, 0, 0));
    glm::mat4 rotate = glm::rotate(this->rotation, glm::vec3(1, 1, 1));

    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate * rotate * rotate_90;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->bomb);
    draw3DObject(this->base);
}

void Bomb::tick() {
    float time_change = (1.0f)/60.0f;
    float accel = 2.0f;
    float ang_accel = 3.0f;
    float dist = this->speed * time_change + (1/2.0f) * accel * time_change * time_change;
    this->speed += accel * time_change;
    this->position.z -= dist;
    float ang_dist = this->angular_speed * time_change + (1/2.0f) * ang_accel * time_change * time_change;
    this->angular_speed += ang_accel * time_change;
    this->rotation += ang_dist;

    float forward_dist;
    if(this->forward_speed > 0)
    {
        forward_dist = this->forward_speed * time_change + (1.0f/2.0f)*this->back_accel * time_change * time_change;
        this->forward_speed += this->back_accel * time_change;
        this->position.x += this->dir_x * dist;
        this->position.y += this->dir_y * dist;
        if(this->forward_speed < 0)
            this->forward_speed = 0;
    }
    else
    {
        forward_dist = this->forward_speed * time_change - (1.0f/2.0f)*this->back_accel * time_change * time_change;
        this->forward_speed -= this->back_accel * time_change;
        this->position.x += this->dir_x * dist;
        this->position.y += this->dir_y * dist;
        if(this->forward_speed > 0)
            this->forward_speed = 0;
    }
    this->position.x += this->dir_x * forward_dist;
    this->position.y += this->dir_y * forward_dist;
}
