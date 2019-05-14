#include "mountain.h"
#include "main.h"

Mountain::Mountain(float x, float y, float rad, float ht) {
    this->position = glm::vec3(x, y, -10+ht/2);
    int n = 100;
    int len = getCylSize(n);
    GLfloat mountain[len+5];
    drawCyl(0.0f, 0.0f, 0.0f, n, 0.0f, rad, ht, mountain);
    GLfloat color[len + 5];
    int i;
    int cntr=0;
    for(i=0;i<len/3;i++)
    {
        color[cntr] = 0.0f;
        cntr++;
        float x = ((rand() % 255)*1.0f)/255;
        if(x<0.3)
            x+=0.2f;
        color[cntr] = x;
        cntr++;
        color[cntr] = 0.0f;
        cntr++;
    }

    this->mountain = create3DObject(GL_TRIANGLES, len/3, mountain, color, GL_FILL);
}

void Mountain::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= translate;

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->mountain);
}
