#include "dashboard.h"
#include "main.h"

Dashboard::Dashboard(float fuel_remain, float hp_remain, float speed, float altitude, float w, float h, float dir_x, float dir_y) {
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    int n = 25;
    int len = getRectSize();
    int circLen = getPolSize(n);
    float bar_width = w/8;
    float bar_height = h/15;
    float buffer = 0.2f;
    float x1,x2,y1,y2,cx,cy,cz;
    float speedAngle = (speed / MAX_SPEED) * 240.0f;
    altitude+=10;
    altitude /= (MAX_ALTITUDE+10);
    float rad;
    float mod = sqrt(dir_x * dir_x + dir_y * dir_y);
    dir_x /= mod;
    dir_y /= mod;

    x1 = -w/2 + buffer;
    x2 = -w/2 + buffer + bar_width;
    y1 = -h/2 + buffer;
    y2 = -h/2 + bar_height + buffer;

    GLfloat fuelbar[30] = {
        x1, y1, 0.0f,
        x1, y2, 0.0f,
        x1, y2, 0.0f,
        x2, y2, 0.0f,
        x2, y2, 0.0f,
        x2, y1, 0.0f,
        x2, y1, 0.0f,
        x1, y1, 0.0f,
    };
    GLfloat fuel[len + 5];
    x2 = -w/2 + buffer + (bar_width * fuel_remain);
    drawRect(x1, y1, 0.0f, x1, y2, 0.0f, x2, y2, 0.0f, x2, y1, 0.0f, fuel, 0);

    y1+=bar_height;
    y2+=bar_height;
    x2 = -w/2 + buffer + bar_width;
    GLfloat hpbar[30] = {
        x1, y1, 0.0f,
        x1, y2, 0.0f,
        x1, y2, 0.0f,
        x2, y2, 0.0f,
        x2, y2, 0.0f,
        x2, y1, 0.0f,
        x2, y1, 0.0f,
        x1, y1, 0.0f,
    };
    GLfloat hp[len + 5];
    x2 = -w/2 + buffer + (bar_width * hp_remain);
    drawRect(x1, y1, 0.0f, x1, y2, 0.0f, x2, y2, 0.0f, x2, y1, 0.0f, hp, 0);

    GLfloat speedbar[circLen + 5];
    rad = h/16;
    cx = -w/2 + buffer + rad;
    cy = h/2 - buffer - rad;
    drawPol(n, cx, cy, rad, speedbar, 0.0f, 0);
    GLfloat speedCirc[circLen + 5];
    drawPol(n, cx, cy, rad/3.0f, speedCirc, 0.2f, 0);

    float nx = -rad;
    float ny = 0.0f;
    float angle = -(-30.0f + speedAngle) * PI / 180.0f;
    float cx1 = nx * cos(angle) - ny * sin(angle) + cx;
    float cy1 = nx * sin(angle) + ny * cos(angle) + cy;
    angle = -(-28.0f + speedAngle)*PI/180.0f;
    nx = -rad/3;
    float cx2 = nx * cos(angle) - ny * sin(angle) + cx;
    float cy2 = nx * sin(angle) + ny * cos(angle) + cy;

    angle = -(-38.0f + speedAngle)*PI/180.0f;
    nx = -rad/3;
    float cx3 = nx * cos(angle) - ny * sin(angle) + cx;
    float cy3 = nx * sin(angle) + ny * cos(angle) + cy;
    GLfloat speed_needle[10] = {
        cx1, cy1, 0.1f,
        cx2, cy2, 0.1f,
        cx3, cy3, 0.1f,
    };


    GLfloat altitudebar[len + 5];
    GLfloat altitudeNeedle[len + 5];
    x2 = w/2 - buffer;
    x1 = x2-0.2f;
    y1 = 0;
    y2 = h/2-buffer;
    drawRect(x1, y1, 0.0f, x2, y1, 0.0f, x2, y2, 0.0f, x1, y2, 0.0f, altitudebar, 0);

    x1 -= 0.1f;
    x2 += 0.1f;
    altitude *= h/2-buffer;
    y1 = altitude + 0.2f;
    y2 = altitude - 0.2f;
    drawRect(x1, y1, 0.0f, x2, y1, 0.0f, x2, y2, 0.0f, x1, y2, 0.0f, altitudeNeedle, 0);

    GLfloat compassbar[circLen + 5];
    rad = h/13;
    cx = w/2 - buffer - rad;
    cy = -h/2 + buffer + rad;
    drawPol(n, cx, cy, rad, compassbar, 0.0f, 0);
    float x_dir = dir_x * rad;
    float y_dir = dir_y * rad;
    x_dir += cx;
    y_dir += cy;
    nx = -0.1f;

    float x_perp = 1.0f;
    float y_perp = -(dir_x/dir_y);
    mod = sqrt(x_perp * x_perp + y_perp * y_perp);
    x_perp /= mod;
    y_perp /= mod;

    x1 = x_perp * 0.1f;
    y1 = y_perp * 0.1f;
    x2 = -x1;
    y2 = -y1;

    // cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;

    x1 += cx;
    x2 += cx;
    y1 += cy;
    y2 += cy;

    GLfloat compassNeedle1[10] = {
        x1, y1, 0.1f,
        x2, y2, 0.1f,
        x_dir, y_dir, 0.1f
    };

    x_dir = -dir_x * rad;
    y_dir = -dir_y * rad;
    x_dir += cx;
    y_dir += cy;

    GLfloat compassNeedle2[10] = {
        x1, y1, 0.1f,
        x2, y2, 0.1f,
        x_dir, y_dir, 0.1f
    };

    this->fuelbar = create3DObject(GL_LINES, 8, fuelbar, {204, 0, 0}, GL_LINE);
    this->fuel = create3DObject(GL_TRIANGLES, len/3, fuel, {204, 0, 0}, GL_FILL);
    this->hpbar = create3DObject(GL_LINES, 8, hpbar, {51, 204, 51}, GL_LINE);
    this->hp = create3DObject(GL_TRIANGLES, len/3, hp, {51, 204, 51}, GL_FILL);
    this->speedbar = create3DObject(GL_TRIANGLES, circLen/3, speedbar, {0, 0, 0}, GL_FILL);
    this->speedcirc = create3DObject(GL_TRIANGLES, circLen/3, speedCirc, {255, 255, 153}, GL_FILL);
    this->speed = create3DObject(GL_TRIANGLES, 3, speed_needle, {255, 51, 0}, GL_FILL);
    this->altitudebar = create3DObject(GL_TRIANGLES, len/3, altitudebar, {0, 0, 0}, GL_FILL);
    this->altitude = create3DObject(GL_TRIANGLES, len/3, altitudeNeedle, {255, 255, 153}, GL_FILL);
    this->compassbar = create3DObject(GL_TRIANGLES, circLen/3, compassbar, {255, 184, 77}, GL_FILL);
    this->compassNeedle1 = create3DObject(GL_TRIANGLES, 3, compassNeedle1, {255, 0, 0}, GL_FILL);
    this->compassNeedle2 = create3DObject(GL_TRIANGLES, 3, compassNeedle2, {0, 0, 255}, GL_FILL);
}

void Dashboard::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->fuelbar);
    draw3DObject(this->fuel);
    draw3DObject(this->hpbar);
    draw3DObject(this->hp);
    draw3DObject(this->speedbar);
    draw3DObject(this->speedcirc);
    draw3DObject(this->speed);
    draw3DObject(this->altitudebar);
    draw3DObject(this->altitude);
    draw3DObject(this->compassbar);
    draw3DObject(this->compassNeedle1);
    draw3DObject(this->compassNeedle2);
}
