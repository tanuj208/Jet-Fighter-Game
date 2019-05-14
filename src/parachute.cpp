#include "parachute.h"
#include "main.h"

Parachute::Parachute(float x, float y, float z, float r1, float r2, float r3, float r4, float h, float H, float dim) {
    this->position = glm::vec3(x, y, z);
    int n = 25;
    int line_len = 4 * getCuboidSize();
    int cyl_len = getCylSize(n);
    speed = 1.0f;
    int box_len = getCuboidSize();
    GLfloat fr1[cyl_len + 5];
    GLfloat fr2[cyl_len + 5];
    GLfloat fr3[cyl_len + 5];
    GLfloat box[box_len + 5];
    drawCuboid(0.0f, 0.0f, 0.0f, dim, dim, dim, box);
    GLfloat lines[30] = {
        0.0f, dim/2, dim/2,
        0.0f, r4, H + dim/2,
        0.0f, -dim/2, dim/2,
        0.0f, -r4, H + dim/2,
        dim/2, 0.0f, dim/2,
        r4, 0.0f, H + dim/2,
        -dim/2, 0.0f, dim/2,
        -r4, 0.0f, H + dim/2
    };
    drawCyl(0.0f, 0.0f, H+h/2+dim/2, n, r3, r4, h, fr3);
    drawCyl(0.0f, 0.0f, H+3*h/2+dim/2, n, r2, r3, h, fr2);
    drawCyl(0.0f, 0.0f, H+5*h/2+dim/2, n, r1, r2, h, fr1);
    // drawCyl(0.0f, 0.0f, ht2/2, 25, rad2, rad3, ht2, vol2);
    // drawCyl(0.0f, 0.0f, ht1/2+ht2, 25, rad1, rad2, ht1, vol1);
    // int i;
    // int cntr=0;
    // for(i=0;i<cyl_len/3;i++)
    // {
    //     float x=rand()%2000;
    //     x+=4000;
    //     x = x*1.0f/10000.0f;
    //     // cout<<x<<endl;
    //     color[cntr] = x;
    //     cntr++;
    //     color[cntr] = 0.0f;
    //     cntr++;
        
    //     x = rand() % 1000;
    //     x+=1000;
    //     x = x * 1.0f/10000.0f;
    //     color[cntr] = x;
    //     cntr++;
    // }

    this->box = create3DObject(GL_TRIANGLES, box_len/3, box, {204, 0, 0}, GL_FILL);
    this->lines = create3DObject(GL_LINES, 8, lines, {0, 0, 0}, GL_FILL);
    this->fr1 = create3DObject(GL_TRIANGLES, cyl_len/3, fr1, {51, 204, 51}, GL_FILL);
    this->fr2 = create3DObject(GL_TRIANGLES, cyl_len/3, fr2, {51, 204, 51}, GL_FILL);
    this->fr3 = create3DObject(GL_TRIANGLES, cyl_len/3, fr3, {51, 204, 51}, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->fr1);
    draw3DObject(this->fr2);
    draw3DObject(this->fr3);
    draw3DObject(this->lines);
    draw3DObject(this->box);
}

void Parachute::tick() {
    double time_change = 1.0f/60.0f;
    this->position.z -= speed * time_change;
}
