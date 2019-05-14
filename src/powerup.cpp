#include "powerup.h"
#include "main.h"

Powerup::Powerup(float x, float y, float z, bool type) {
    this->position = glm::vec3(x, y, z);
    if(type==0)
        this->fuel  = 0;
    else
        this->fuel = 1;
    
    int len = getCuboidSize();

    GLfloat powerup[len+5];
    drawCuboid(0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, powerup);
    color_t color;
    if(type==1)
        color = {204, 0, 0};
    else
        color = {51, 204, 51};
    
    this->powerup = create3DObject(GL_TRIANGLES, len/3, powerup, color, GL_FILL);
}

void Powerup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->powerup);
}
