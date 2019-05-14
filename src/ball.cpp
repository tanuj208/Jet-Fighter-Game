#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // int n = 600;
    int n1=100;
    int n2=100;
    int rad1 = 2.0f;
    int rad2 = 0.0f;
    int base_len = getPolSize(n1);
    int len = getCylSize(n2);

    GLfloat vertex_buffer_data[len+5];
    GLfloat base1[base_len+5];
    GLfloat base2[base_len+5];
    drawPol(n1, 0.0f, 0.0f, rad1, base1, 2.5f, 0);
    drawPol(n1, 0.0f, 0.0f, rad2, base2, -2.5f, 0);
    drawCyl(0.0f, 0.0f, 0.0f, n2, rad1, rad2, 5.0f, vertex_buffer_data);
    // drawCuboid(0.0f, 0.0f, 0.0f, 2.0f, 4.4f, 3.0f, vertex_buffer_data, len);
    // drawPol(n1, 0.0f, 0.0f, 0.2f, vertex_buffer_data, 22.0f, 0);
    // drawPol(n2, 1.0f, 1.0f, 0.3f, vertex_buffer_data, 22.0f, len);
    // len+=len2;
    // drawRect(1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.f, 1.0f, -1.0f, 0.0f, vertex_buffer_data, getRectSize(), 0);
    // drawRect(1.0f, 1.0f, 2.0f, -1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 2.0f, 1.0f, -1.0f, 0.0f, vertex_buffer_data, getRectSize(),getRectSize());

    this->object = create3DObject(GL_TRIANGLES,len/3, vertex_buffer_data, color, GL_FILL);
    this->base1 = create3DObject(GL_TRIANGLES,base_len/3, base1, color, GL_FILL);
    this->base2 = create3DObject(GL_TRIANGLES,base_len/3, base2, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->base1);
    draw3DObject(this->base2);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

