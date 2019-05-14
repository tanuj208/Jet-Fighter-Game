#include "plane.h"
#include "main.h"

Plane::Plane(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 0;
    this->fuel = 100;
    this->hp = 100;
    this->back_accel = -5.0f;
    this->rad = 0.25f;
    this->len = 2.0f;
    this->yawAngle = 0;
    this->rollAngle = 0;
    int n = 25;
    int body_array_len = getCylSize(n);
    int circ_len = getPolSize(n);
    int wing_array_len = getCuboidSize();
    int tail_array_len = getCuboidSize();
    int top_array_len = getCylSize(n);
    float tmp = 0.1f;
    GLfloat wings[8*3*3+5] = {
        0.0f, -tmp, 2*rad,
        -3*rad, -tmp, rad,
        3*rad, -tmp, rad,
        0.0f, tmp, 2*rad,
        -3*rad, tmp, rad,
        3*rad, tmp, rad
    };
    drawRect(0.0f,-tmp, 2*rad, 0.0f, tmp, 2*rad, -3*rad, tmp, rad, -3*rad, -tmp, rad, wings, 18);
    drawRect(0.0f, tmp, 2*rad, 0.0f, -tmp, 2*rad, 3*rad, -tmp, rad, 3*rad, tmp, rad, wings, 36);
    drawRect(3*rad, tmp, rad, 3*rad, -tmp, rad, -3*rad, -tmp, rad, -3*rad, tmp, rad, wings, 54);

    float z1 = -3*len/8;
    float z2 = -5*len/8;

    GLfloat tails[8*3*3+5] = {
        0.0f, -tmp, z1,
        -2*rad, -tmp, z2,
        2*rad, -tmp, z2,
        0.0f, tmp, z1,
        -2*rad, tmp, z2,
        2*rad, tmp, z2,
    };
    drawRect(0.0f, -tmp, z1, 0.0f, tmp, z1, -2*rad, tmp, z2, -2*rad, -tmp, z2, tails, 18);
    drawRect(0.0f, -tmp, z1, 0.0f, tmp, z1, 2*rad, tmp, z2, 2*rad, -tmp, z2, tails, 36);
    drawRect(-2*rad, -tmp, z2, -2*rad, tmp, z2, 2*rad, tmp, z2, 2*rad, -tmp, z2, tails, 54);

    GLfloat plane_body[body_array_len + 5];
    GLfloat top[top_array_len + 5];
    GLfloat circ1[circ_len + 5];
    GLfloat circ2[circ_len + 5];

    drawPol(n, 0.0f, 0.0f, rad, circ1, len/2, 0);
    drawPol(n, 0.0f, 0.0f, rad, circ2, -len/2, 0);
    drawCyl(0.0f, 0.0f, 0.0f, n, rad, rad, len, plane_body);
    drawCyl(0.0f, 0.0f, 3*len/4, n, 0.0f, rad, len/2, top);

    // this->circ1 = create3DObject(GL_TRIANGLES, circ_len/3, circ1, COLOR_RED, GL_LINE);
    // this->circ2 = create3DObject(GL_TRIANGLES, circ_len/3, circ2, COLOR_RED, GL_LINE);
    // this->body = create3DObject(GL_TRIANGLES, body_array_len/3, plane_body, COLOR_RED, GL_LINE);
    // this->top = create3DObject(GL_TRIANGLES, top_array_len/3, top, COLOR_RED, GL_LINE);
    // this->wings = create3DObject(GL_TRIANGLES, 24, wings, COLOR_RED, GL_LINE);
    // this->tails = create3DObject(GL_TRIANGLES, 24, tails, COLOR_RED, GL_LINE);
    color_t color1 = {102, 102, 153};
    color_t color2 = {71, 71, 107};

    this->circ1 = create3DObject(GL_TRIANGLES, circ_len/3, circ1, color2, GL_FILL);
    this->circ2 = create3DObject(GL_TRIANGLES, circ_len/3, circ2, color2, GL_FILL);
    this->body = create3DObject(GL_TRIANGLES, body_array_len/3, plane_body, color1, GL_FILL);
    this->top = create3DObject(GL_TRIANGLES, top_array_len/3, top, color2, GL_LINE);
    this->wings = create3DObject(GL_TRIANGLES, 24, wings, color2, GL_FILL);
    this->tails = create3DObject(GL_TRIANGLES, 24, tails, color2, GL_FILL);
}

void Plane::draw(glm::mat4 VP, bool flag) {
    Matrices.model = glm::mat4(1.0f);
    float right_angle = (90.0f * PI) / 180.0f;
    glm::mat4 rotate_90 = glm::rotate(-right_angle, glm::vec3(1, 0, 0));
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 yaw = glm::rotate(this->yawAngle, glm::vec3(0, 0, 1));
    glm::mat4 pitch = glm::rotate(this->pitchAngle, glm::vec3(1, 0, 0));
    glm::mat4 roll = glm::rotate(this->rollAngle, glm::vec3(0, 1, 0));
    rotate *= yaw *pitch * roll;
    this->yawAngle = 0;
    this->pitchAngle = 0;
    this->rollAngle = 0;
    Matrices.model *= (translate*rotate*rotate_90);

    if(flag)
    {
        this->dir_x = rotate[1][0];
        this->dir_y = rotate[1][1];
        this->dir_z = rotate[1][2];

        this->up_x = rotate[2][0];
        this->up_y = rotate[2][1];
        this->up_z = rotate[2][2];

        this->perp_x = rotate[0][0];
        this->perp_y = rotate[0][1];
        this->perp_z = rotate[0][2];
    }

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->wings);
    draw3DObject(this->circ1);
    draw3DObject(this->circ2);
    draw3DObject(this->body);
    draw3DObject(this->top);
    draw3DObject(this->tails);
}

void Plane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plane::tick() {
    double time_change = 1.0f/60.0f;
    if(this->speed > 0)
    {
        float dist = this->speed * time_change + (1.0f/2.0f)*this->back_accel * time_change * time_change;
        this->speed += this->back_accel * time_change;
        this->position.x += this->dir_x * dist;
        this->position.y += this->dir_y * dist;
        this->position.z += this->dir_z * dist;
        if(this->speed < 0)
            this->speed = 0;
    }
    else
    {
        float dist = this->speed * time_change - (1.0f/2.0f)*this->back_accel * time_change * time_change;
        this->speed -= this->back_accel * time_change;
        this->position.x += this->dir_x * dist;
        this->position.y += this->dir_y * dist;
        this->position.z += this->dir_z * dist;
        if(this->speed > 0)
            this->speed = 0;
    }
    if(this->speed > MAX_SPEED)
        this->speed = MAX_SPEED;
    if(this->speed < -MAX_SPEED)
        this->speed = -MAX_SPEED;
    
}
