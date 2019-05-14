#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float y, float rad1, float rad2, float rad3, float ht1, float ht2) {
    this->position = glm::vec3(x, y, -9.9);
    int cyl_len = getCylSize(25);
    // int ash_len = getCuboidSize();
    // ash_count = 50;

    // GLfloat ashes[ash_count+2][ash_len+5];
    GLfloat vol1[cyl_len + 5];
    GLfloat vol2[cyl_len + 5];
    GLfloat color[cyl_len + 5];
    drawCyl(0.0f, 0.0f, ht2/2, 25, rad2, rad3, ht2, vol2);
    drawCyl(0.0f, 0.0f, ht1/2+ht2, 25, rad1, rad2, ht1, vol1);
    int i;
    // for(i=0;i<ash_count;i++)
    // {
    //     float random_z = ((rand() % 8000) * 1.0f) / 1000.0f + 5.0f;
    //     float random_x = ((rand() % 4000) * 1.0f) / 10000.0f;
    //     float random_y = ((rand() % 4000) * 1.0f) / 10000.0f;
    //     drawCuboid(random_x, random_y, random_z, 0.2f, 0.2f, 0.2f, ashes[i]);
    // }
    int cntr=0;
    for(i=0;i<cyl_len/3;i++)
    {
        float x=rand()%2000;
        x+=4000;
        x = x*1.0f/10000.0f;
        color[cntr] = x;
        cntr++;
        color[cntr] = 0.0f;
        cntr++;
        
        x = rand() % 1000;
        x+=1000;
        x = x * 1.0f/10000.0f;
        color[cntr] = x;
        cntr++;
    }

    this->volcano1 = create3DObject(GL_TRIANGLES, cyl_len/3, vol1, color, GL_FILL);
    this->volcano2 = create3DObject(GL_TRIANGLES, cyl_len/3, vol2, color, GL_FILL);
    // for(i=0;i<ash_count;i++)
    //     this->ashes[i] = create3DObject(GL_TRIANGLES, ash_len/3, ashes[i], {153, 0, 51}, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->volcano1);
    draw3DObject(this->volcano2);
    int i;
    // for(i=0;i<this->ash_count;i++)
    //     draw3DObject(this->ashes[i]);
}
