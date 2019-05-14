#include "main.h"
#include "timer.h"
#include "ball.h"
#include "plane.h"
#include "water.h"
#include "dashboard.h"
#include "mountain.h"
#include "volcano.h"
#include "island.h"
#include "missile.h"
#include "parachute.h"
#include "powerup.h"
#include "arrow.h"
#include "smoke_rings.h"
#include "bomb.h"
#include "score.h"
#include "cannon.h"

using namespace std;

GLMatrices Matrices;
GLMatrices Mat2;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

// Ball ball1;
Plane plane;
Water water;
Dashboard dashboard;
Arrow arrow;
vector<Mountain> mountains;
vector<Volcano> volcanoes;
vector<Island> islands;
vector<Missile> plane_missiles;
vector<Missile> enemy_missiles;
vector<Parachute> parachutes;
vector<Powerup> powerups;
vector<Smoke_ring> rings;
vector<Bomb> bombs;
vector<int> empty_islands;
Score score_display[10];
Cannon cannon;
double r,theta,phi;
double gl_x, gl_y, gl_z;
double barrel_rad;
double barrel_angle;
double barrel_forward_speed;
float init_x, init_y, init_z;
double looping_angle;
double loop_forward_speed;
double barrel_angle2;
double barrel2_forward_speed;

// 0 -> follow cam, 1 -> first person, 2-> top view, 3->tower view, 4->helicopter view
int view = 0;
bool cannon_destroyed = true;
int checkpoints_passed = 0;
int time_spent;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
double PI = 3.1415926535897;
float MAX_ALTITUDE = 40.0f;
float MAX_SPEED = 20.0f;
bool changed = false;
bool bombed = false;
bool fired = false;
int score = 0;
double x_pos, y_pos;
bool barrel_roll = false;
bool looping_loop = false;
bool barrel_roll2 = false;
int max_parachutes = 20;
int max_powerups = 20   ;
int max_rings = 15;
int lastPlayed = -120;

Timer t60(1.0 / 60);

string sevenSegment(int x)
{
    if(x==0)
        return "1111110";
    else if(x==1)
        return "0110000";
    else if(x==2)
        return "1101101";
    else if(x==3)
        return "1111001";
    else if(x==4)
        return "0110011";
    else if(x==5)
        return "1011011";
    else if(x==6)
        return "1011111";
    else if(x==7)
        return "1110000";
    else if(x==8)
        return "1111111";
    else
        return "1111011";
}

void draw_cannon() {
    bool flag = true;
    if(!cannon_destroyed)
        return;
    while(flag)
    {
        int x = rand() % sz(empty_islands);
        x = empty_islands[x];
        int dist = get_distance(islands[x].position.x, islands[x].position.y, islands[x].position.z, plane.position.x, plane.position.y, plane.position.z);
        if(dist >= 250 && dist <= 500) {
            flag = false;
            cannon_destroyed = false;
            cannon = Cannon(islands[x].position.x, islands[x].position.y, 0.5f, 1.5f, 15.0f, islands[x].rad);
        }
    }
}

void draw() {
    int i;
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram (programID);

    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;
    if(view == 0)
    {
        eye = glm::vec3(plane.position.x - 5.0f * plane.dir_x + 3.0f * plane.up_x, plane.position.y - 5.0f * plane.dir_y + 3.0f * plane.up_y, plane.position.z - 5.0f * plane.dir_z + 3.0f * plane.up_z);
        target = plane.position;
        up  = glm::vec3(plane.up_x, plane.up_y, plane.up_z);
    }
    else if(view == 1)
    {
        eye = glm::vec3(plane.position.x + plane.len * plane.dir_x / 2.0f, plane.position.y + plane.len * plane.dir_y / 2.0f, plane.position.z + plane.len * plane.dir_z / 2.0f);
        target = glm::vec3(plane.position.x + plane.len * plane.dir_x, plane.position.y + plane.len * plane.dir_y, plane.position.z + plane.len * plane.dir_z);
        up = glm::vec3(plane.up_x, plane.up_y, plane.up_z);
    }
    else if(view == 2)
    {
        eye = glm::vec3(plane.position.x, plane.position.y, 70.0f);
        target = plane.position;
        up = glm::vec3(1, 0, 0);
    }
    else if(view == 3)
    {
        eye = glm::vec3(26.0f, 30.0f, 28.0f);
        target = plane.position;
        up  = glm::vec3(0, 0, 1);
    }
    else
    {
        x_pos -= 450;
        y_pos -= 450;
        x_pos /= 450;
        y_pos /= 450;
        if(x_pos < -1)
            x_pos = -1;
        if(x_pos > 1)
            x_pos = 1;
        if(y_pos < -1)
            y_pos = -1;
        if(y_pos > 1)
            y_pos = 1;
        theta = x_pos * PI / 2;
        phi = y_pos * PI / 2;
        float R = r * screen_zoom;
        double x = plane.position.x - plane.dir_x * R * (cos(theta) + cos(phi)) + plane.perp_x * R * sin(theta) + plane.up_x * R * sin(phi);
        double y = plane.position.y - plane.dir_y * R * (cos(theta) + cos(phi)) + plane.perp_y * R * sin(theta) + plane.up_y * R * sin(phi);
        double z = plane.position.z - plane.dir_z * R * (cos(theta) + cos(phi)) + plane.perp_z * R * sin(theta) + plane.up_z * R * sin(phi);
        eye = glm::vec3(x, y, z);
        target = plane.position;
        up = glm::vec3(0, 0, 1);
    }
    
    Matrices.view = glm::lookAt( eye, target, up );

    glm::vec3 eyeScore(0, 0, 20);
    glm::vec3 targetScore(0, 0, 0);
    glm::vec3 upScore(0, 1, 0);
    Mat2.view = glm::lookAt(eyeScore, targetScore, upScore);
    if(rand() % 100 == 51)
    {
        glm::vec3 dir = plane.position - cannon.position;
        dir[2]--;
        dir = glm::normalize(dir);
        enemy_missiles.pb(Missile(cannon.position.x + 4.0f * cannon.dir[0], cannon.position.y + 4.0f * cannon.dir[1], cannon.position.z + 4.0f * cannon.dir[2], 0.2f, 1.0f, dir[0], dir[1], dir[2], cannon.rotate, 10.0f, {255, 255, 0}));
    }
    if(sz(parachutes) < max_parachutes)
    {
        float distx = (rand() % 1000000)/1000.0f  - 500.0f;
        float disty = (rand() % 1000000)/1000.0f  - 500.0f;
        parachutes.pb(Parachute(plane.position.x + distx, plane.position.y + disty, 50.0f, 0.1f, 0.6f, 0.9f, 1.0f, 0.5f, 1.0f, 0.5f));
    }
    if(sz(powerups) < max_powerups)
    {
        float distx = (rand() % 1000000)/1000.0f  - 500.0f;
        float disty = (rand() % 1000000)/1000.0f  - 500.0f;
        float distz = (rand() % 20000)/1000.0f + 20.0f;
        float random_value = rand() % 2;
        powerups.pb(Powerup(plane.position.x + distx, plane.position.y + disty, distz, random_value));
    }
    if(sz(rings) < max_rings)
    {
        float distx = (rand() % 1000000)/1000.0f  - 500.0f;
        float disty = (rand() % 1000000)/1000.0f  - 500.0f;
        float distz = (rand() % 20000)/1000.0f + 20.0f;
        rings.pb(Smoke_ring(distx, disty, distz, 2.0f));
    }
    draw_cannon();
    float val;
    if(view == 1)
        val = 1.0f;
    else
        val = 0;
    
    arrow = Arrow(plane.position.x + 7.0f * plane.dir_x + val * plane.up_x, plane.position.y + 7.0f * plane.dir_y + val * plane.up_y, plane.position.z + 7.0f * plane.dir_z + val * plane.up_z, cannon.position.x, cannon.position.y);

    vector<int> sc;
    int tmp = score;
    if(score == 0)
        sc.pb(0);
    while(tmp!=0)
    {
        sc.pb(tmp%10);
        tmp/=10;
    }
    int cntr=0;
    for(i=sz(sc)-1;i>=0;i--)
    {
        score_display[cntr] = Score(-1.0f + cntr * 0.4f, -3.2f, sevenSegment(sc[i]));
        cntr++;
    }

    dashboard = Dashboard(plane.fuel / 100.0f, plane.hp / 100.0f, plane.speed, plane.position.z, 8.0f, 8.0f, plane.dir_x, plane.dir_y);
    
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VPScore = Mat2.projection * Mat2.view;

    glm::mat4 MVP;
    glm::mat4 MVPScore;

    if(plane.position.z > MAX_ALTITUDE && !barrel_roll && !looping_loop)
        plane.position.z = MAX_ALTITUDE;
    if(plane.position.z <= -10.0f)
        plane.hp-=5;
    if(barrel_roll)
        plane.draw(VP, false);
    else
        plane.draw(VP, true);
    
    water.draw(VP);
    cannon.draw(VP);
    dashboard.draw(VPScore);
    if(!barrel_roll && !barrel_roll2 && !looping_loop)
        arrow.draw(VP);
    for(i=0;i<sz(volcanoes);i++)
        volcanoes[i].draw(VP);
    for(i=0;i<sz(mountains);i++)
        mountains[i].draw(VP);
    for(i=0;i<sz(islands);i++)
        islands[i].draw(VP);
    for(i=0;i<sz(plane_missiles);i++)
        plane_missiles[i].draw(VP, false);
    for(i=0;i<sz(enemy_missiles);i++)
        enemy_missiles[i].draw(VP, true);
    for(i=0;i<sz(parachutes);i++)
        parachutes[i].draw(VP);
    for(i=0;i<sz(powerups);i++)
        powerups[i].draw(VP);
    for(i=0;i<sz(rings);i++)
        rings[i].draw(VP);
    for(i=0;i<sz(bombs);i++)
        bombs[i].draw(VP);
    for(i=0;i<sz(sc);i++)
        score_display[i].draw(VPScore);
}

void tick_input(GLFWwindow *window) {
    int v = glfwGetKey(window, GLFW_KEY_V);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int q = glfwGetKey(window, GLFW_KEY_Q);
    int e = glfwGetKey(window, GLFW_KEY_E);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int t = glfwGetKey(window, GLFW_KEY_T);
    int r = glfwGetKey(window, GLFW_KEY_R);
    int y = glfwGetKey(window, GLFW_KEY_Y);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int b = glfwGetKey(window, GLFW_KEY_B);
    int rightClick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    int leftClick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    glfwGetCursorPos(window, &x_pos, &y_pos);
    if(v && !changed)
    {
        view++;
        view %= 5;
        changed = true;
    }
    else if(v == GLFW_RELEASE && changed)
        changed = false;
    
    if(a && !barrel_roll && !looping_loop && !barrel_roll2)
        plane.rollAngle -= 0.01;
    if(d && !barrel_roll && !looping_loop && !barrel_roll2)
        plane.rollAngle += 0.01;
    if(q && !barrel_roll && !looping_loop && !barrel_roll2)
        plane.yawAngle += 0.01;
    if(e && !barrel_roll && !looping_loop && !barrel_roll2)
        plane.yawAngle -= 0.01;
    if(up && !barrel_roll && !looping_loop && !barrel_roll2)
        plane.pitchAngle += 0.01;
    if(down && !barrel_roll && !looping_loop && !barrel_roll2)
        plane.pitchAngle -= 0.01;
    if(w && plane.fuel > 0 && !barrel_roll && !looping_loop && !barrel_roll2)
    {
        plane.speed += 0.2;
        score++;
        if(plane.speed >= 0)
        {
            if(time_spent - lastPlayed >= 80)
            {
                system("aplay -c 1 -t wav -q ./sound/plane.wav&");
                lastPlayed = time_spent;
            }
            plane.fuel -= 0.03;
        }
    }
    if(s && plane.fuel > 0 && !barrel_roll && !looping_loop && !barrel_roll2)
    {
        plane.speed -= 0.2;
        score++;
        if(plane.speed <= 0)
            plane.fuel -= 0.03;
    }
    if((b || rightClick) && !bombed) {
        system("aplay -c 1 -t wav -q ./sound/bomb.wav&");
        bombs.pb(Bomb(plane.position.x, plane.position.y, plane.position.z - 1.0f, 0.3f, 0.7f, plane.dir_x, plane.dir_y, plane.speed));
        bombed = true;
    }
    else if(b == GLFW_RELEASE && rightClick == GLFW_RELEASE && bombed)
        bombed = false;
    if(leftClick && !fired) {
        system("aplay -c 1 -t wav -q ./sound/missile.wav&");
        plane_missiles.pb(Missile(plane.position.x + plane.len*plane.dir_x/2, plane.position.y + plane.len*plane.dir_y/2, plane.position.z + plane.len*plane.dir_z/2, 0.2f, 1.0f, plane.dir_x, plane.dir_y, plane.dir_z, plane.rotate, abs(plane.speed) + 20.0f, {204, 51, 0}));
        fired = true;
    }
    else if(leftClick == GLFW_RELEASE && fired)
        fired = false;
    if(t && !barrel_roll && !looping_loop && !barrel_roll2) {
        barrel_roll = true;
        barrel_rad = 10.0f;
        barrel_angle = 0;
        barrel_forward_speed = 15.0f;
        init_x = plane.position.x;
        init_y = plane.position.y;
        init_z = plane.position.z;
    }
    if(r && !barrel_roll && !looping_loop && !barrel_roll2) {
        looping_loop = true;
        looping_angle = 0;
        loop_forward_speed = 15.0f;
        init_x = plane.dir_x;
        init_y = plane.dir_y;
        init_z = plane.dir_z;
    }
    if(y && !barrel_roll && !looping_loop && !barrel_roll2) {
        barrel_roll2 = true;
        barrel_angle2 = 0;
        barrel2_forward_speed = 15.0f;
    }
}

void tick_elements() {
    int i;
    if(barrel_roll) {
        barrel_angle += 1;
        plane.rollAngle -= PI / 180.0f;
        if(barrel_angle >= 360)
            barrel_roll = false;
        float dist = (1.0f/60.0f) * barrel_forward_speed;
        init_x += dist * plane.dir_x;
        init_y += dist * plane.dir_y;
        init_z += dist * plane.dir_z;
        plane.position.x += dist * plane.dir_x;
        plane.position.y += dist * plane.dir_y;
        plane.position.z += dist * plane.dir_z;
        gl_x = init_x + barrel_rad * plane.up_x;
        gl_y = init_y + barrel_rad * plane.up_y;
        gl_z = init_z + barrel_rad * plane.up_z;
        float dist1 = barrel_rad * cos(barrel_angle * PI / 180.0f);
        float dist2 = barrel_rad * sin(barrel_angle * PI / 180.0f);
        gl_x += dist2 * plane.perp_x - dist1 * plane.up_x;
        gl_y += dist2 * plane.perp_y - dist1 * plane.up_y;
        gl_z += dist2 * plane.perp_z - dist1 * plane.up_z;
        plane.position.x = gl_x;
        plane.position.y = gl_y;
        plane.position.z = gl_z;
    }
    if(looping_loop) {
        looping_angle += 1;
        plane.pitchAngle -= PI / 180.0f;
        if(looping_angle >= 360)
            looping_loop = false;
        float dist = (1.0f/60.0f) * loop_forward_speed;
        plane.position.x += dist * init_x;
        plane.position.y += dist * init_y;
        plane.position.z += dist * init_z;
    }
    if(barrel_roll2) {
        barrel_angle2 += 1;
        plane.rollAngle -= PI / 180.0f;
        if(barrel_angle2 >= 360)
            barrel_roll2 = false;
        float dist = barrel2_forward_speed * (1.0f/60.0f);
        plane.position.x += dist * plane.dir_x;
        plane.position.y += dist * plane.dir_y;
        plane.position.z += dist * plane.dir_z;
    }
    arrow.position.z = plane.position.z + 15.0f;
    if(!barrel_roll && !looping_loop && !barrel_roll2)
        plane.tick();
    water.position.x = plane.position.x;
    water.position.y = plane.position.y;
    bounding_box_t planeBx = createBoundingBox(plane.position.x, plane.position.y, plane.position.z, 0.5f, 2.0f, 0.5f);
    bounding_box_t cannonBx = createBoundingBox(cannon.position.x, cannon.position.y, cannon.position.z, cannon.island_rad, cannon.island_rad, 0.2f);
    for(i=0;i<sz(volcanoes);i++)
        if(get_distance(plane.position.x, plane.position.y, plane.position.z, volcanoes[i].position.x, volcanoes[i].position.y, volcanoes[i].position.z) <= 40.0f && !barrel_roll && !looping_loop)
            plane.hp -= 1;

    for(i=0;i<sz(parachutes);i++)
    {
        parachutes[i].tick();
        if(parachutes[i].position.z < -12)
            parachutes.erase(parachutes.begin() + i);
    }

    for(i=0;i<sz(enemy_missiles);i++)
    {
        enemy_missiles[i].tick();
        bounding_box_t enMissileBx = createBoundingBox(enemy_missiles[i].position.x, enemy_missiles[i].position.y, enemy_missiles[i].position.z, 0.75, 0.75, 0.75f);
        if(detect_collision(enMissileBx, planeBx))
        {
            plane.hp -= 30;
            enemy_missiles.erase(enemy_missiles.begin() + i);
        }
    }

    for(i=0;i<sz(plane_missiles);i++)
    {
        plane_missiles[i].tick();
        if(get_distance(plane_missiles[i].position.x, plane_missiles[i].position.y, plane_missiles[i].position.z, plane.position.x, plane.position.y, plane.position.z) >= 500.0f)
            plane_missiles.erase(plane_missiles.begin() + i);
        if(plane_missiles[i].position.z < -11)
            plane_missiles.erase(plane_missiles.begin() + i);
        bounding_box_t plane_missileBx = createBoundingBox(plane_missiles[i].position.x, plane_missiles[i].position.y, plane_missiles[i].position.z, 0.75f, 0.75f, 0.75f);
        int j;
        bool flag = false;
        for(j=0;j<sz(parachutes);j++)
        {
            bounding_box_t parachuteBx = createBoundingBox(parachutes[j].position.x, parachutes[j].position.y, parachutes[j].position.z + 1.25f, 0.75f, 0.75f, 2.5f);
            if(detect_collision(plane_missileBx, parachuteBx))
            {
                system("aplay -c 1 -t wav -q ./sound/parachute.wav&");
                parachutes.erase(parachutes.begin() + j);
                flag = true;
                score += 500;
                break;
            }
        }
        if(flag)
        {
            plane_missiles.erase(plane_missiles.begin() + i);
            break;
        }
        if(detect_collision(plane_missileBx, cannonBx))
        {
            score += 1000;
            checkpoints_passed ++;
            cannon_destroyed = true;
            plane_missiles.erase(plane_missiles.begin() + i);
            system("aplay -c 1 -t wav -q ./sound/cannon.wav&");
        }
    }
    for(i=0;i<sz(powerups);i++)
    {
        bounding_box_t powerUpBx = createBoundingBox(powerups[i].position.x, powerups[i].position.y, powerups[i].position.z, 0.5f, 0.5f, 0.5f);
        if(detect_collision(planeBx, powerUpBx))
        {
            if(powerups[i].fuel == 0)
            {
                plane.hp += 30.0f;
                if(plane.hp >= 100.0f)
                    plane.hp = 100.0f;
            }
            else
                plane.fuel = 100.0f;
            powerups.erase(powerups.begin() + i);
        }
    }
    cannon.tick(plane.position.x, plane.position.y, plane.position.z + 0.5f);

    for(i=0;i<sz(bombs);i++)
    {
        bombs[i].tick();
        if(bombs[i].position.z < -11)
            bombs.erase(bombs.begin() + i);
        bounding_box_t bombBx = createBoundingBox(bombs[i].position.x, bombs[i].position.y, bombs[i].position.z, 0.65f, 0.65f, 0.65f);
        int j;
        bool flag = false;
        for(j=0;j<sz(parachutes);j++)
        {
            bounding_box_t parachuteBx = createBoundingBox(parachutes[j].position.x, parachutes[j].position.y, parachutes[j].position.z + 1.25f, 0.75f, 0.75f, 2.5f);
            if(detect_collision(bombBx, parachuteBx))
            {
                system("aplay -c 1 -t wav -q ./sound/parachute.wav&");
                parachutes.erase(parachutes.begin() + j);
                flag = true;
                score += 50;
                break;
            }
        }
        if(flag)
        {
            bombs.erase(bombs.begin() + i);
            break;
        }
        if(detect_collision(bombBx, cannonBx))
        {
            system("aplay -c 1 -t wav -q ./sound/cannon.wav&");
            score += 200;
            checkpoints_passed ++;
            cannon_destroyed = true;
            bombs.erase(bombs.begin() + i);
        }
    }
    
    for(i=0;i<sz(rings);i++)
    {
        bounding_box_t ringBx = createBoundingBox(rings[i].position.x, rings[i].position.y, rings[i].position.z, 2.0f, 0.5f, 2.0f);
        if(detect_collision(planeBx, ringBx))
        {
            score += 200;
            rings.erase(rings.begin() + i);
        }
    }
}

void draw_island(int x, int y, int cntr) {
    int random = rand() % 8;
    float rad = ((rand() % 8000) * 1.0f)/1000.0f + 6.0f;
    float randx = ((rand() % 20000) * 1.0f)/1000.0f - 10.0f;
    float randy = ((rand() % 20000) * 1.0f)/1000.0f - 10.0f;
    islands.pb(Island(x + randx, y + randy, rad));
    if((abs(x) <= 20 || abs(y) <= 20) && random == 7)
        random = 1;
    if(random >= 0 && random < 3)
        empty_islands.pb(cntr);
    else if(random <= 6)
    {
        float ht = ((rand() % 8000)*1.0f)/1000.0f + 4.0f;
        mountains.pb(Mountain(x + randx, y + randy, rad - 2.0f, ht));
    }
    else if(random == 7)
    {
        float ht = ((rand() % 3000)*1.0f)/1000.0f + 2.0f;
        volcanoes.pb(Volcano(x + randx, y + randy, 2.0f, 3.0f, 4.0f, 3.0f, 4.0f));
    }
}

void draw_islands() {
    int i,j;
    int x = 0;
    int y;
    int cntr = 0;
    for(i=0;i<25;i++)
    {
        y=0;
        for(j=0;j<25;j++)
        {
            draw_island(x, y, cntr);
            y += 40;
            cntr++;
        }
        x += 40;
    }
    x = -40;
    for(i=0;i<25;i++)
    {
        y=0;
        for(j=0;j<25;j++)
        {
            draw_island(x, y, cntr);
            y += 40;
            cntr++;
        }
        x -= 40;
    }
    x = -40;
    for(i=0;i<25;i++)
    {
        y = -40;
        for(j=0;j<25;j++)
        {
            draw_island(x, y, cntr);
            y -= 40;
            cntr++;
        }
        x -= 40;
    }
    x = -40;
    for(i=0;i<25;i++)
    {
        y = -40;
        for(j=0;j<25;j++)
        {
            draw_island(x, y, cntr);
            y -= 40;
            cntr++;
        }
        x += 40;
    }
}

void initGL(GLFWwindow *window, int width, int height) {

    plane = Plane(0.0f, 0.0f, 10.0f);
    water = Water(0.0f, 0.0f, -10.0f);
    draw_islands();

    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Mat2.MatrixID =  glGetUniformLocation(programID, "MVPScore");

    reshapeWindow (window, width, height);

    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 900;
    int height = 900;
    time_spent = 0;
    r = 20.0f;
    theta = 0;
    phi = 0;

    window = initGLFW(width, height);

    initGL (window, width, height);

    while (!glfwWindowShouldClose(window)) {

        if (t60.processTick()) {
            time_spent++;
            draw();
            glfwSwapBuffers(window);
            tick_elements();
            tick_input(window);
        }

        glfwPollEvents();
        if(plane.hp <= 0)
        {
            cout<<"Crashed!!"<<endl;
            cout<<"Your final score is "<<score<<endl;
            break;
        }
        if(plane.fuel <= 0 && plane.speed == 0)
        {
            cout<<"Fuel over!!"<<endl;
            cout<<"Your final score is "<<score<<endl;
            break;
        }
        if(checkpoints_passed == 5)
        {
            cout<<"You won!!"<<endl;
            cout<<"Your final score is "<<score<<endl;
        }
    }
    quit(window);
}

bounding_box_t createBoundingBox(float x, float y, float z, float length, float breadth, float height) {
    bounding_box_t bx;
    bx.x = x;
    bx.y = y;
    bx.z = z;
    bx.length = length;
    bx.breadth = breadth;
    bx.height = height;
    return bx;
}

float get_distance(float x1, float y1, float z1, float x2, float y2, float z2) {
    return sqrt((x1-x2) * (x1-x2) + (y1-y2) * (y1-y2) + (z1-z2) * (z1-z2));
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
	return (abs(a.x - b.x) * 2 <= (a.length + b.length)) &&
		   (abs(a.y - b.y) * 2 <= (a.breadth + b.breadth)) &&
		   (abs(a.z - b.z) * 2 <= (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 500.0f);
    Mat2.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);

}

pii rotate(double x, double y, double angle, double cx, double cy) {    
    pii retVal;
    x-=cx;
    y-=cy;
    retVal.first = x * cos(angle) - y * sin(angle);
    retVal.second = x * sin(angle) + y * cos(angle);
    retVal.first += cx;
    retVal.second += cy;
    return retVal;
}

int getRectSize() {
    return 18;
}

int getPolSize(int n) {
    return 9*n;
}

int getCuboidSize() {
    return 3*36;
}

int getCylSize(int n) {
    return n*getRectSize();
}

void drawCyl(float cx, float cy, float cz, int n, float rad1, float rad2, float ht, GLfloat vertex_buffer_data[]) {
    int cntr = 0;
    double angle = 2 * PI  / n;
    float x1, y1, x2, y2;
    float x3, y3, x4, y4;
    x1 = cx + rad1;
    y1 = cy;
    x3 = cx + rad2;
    y3 = cy;
    pii tmp=rotate(x1, y1, angle, cx, cy);
    x2=tmp.first;
    y2=tmp.second;
    tmp = rotate(x3, y3, angle, cx, cy);
    x4 = tmp.first, y4 = tmp.second;
    int i;
    for(i=0;i<n;i++)
    {
        drawRect(x1,y1,cz+ht/2, x2,y2,cz+ht/2, x4,y4, cz-ht/2, x3,y3,cz-ht/2, vertex_buffer_data, cntr);
        cntr+=getRectSize();
        pii tmp=rotate(x2,y2,angle,cx,cy);
        x1 = x2, y1 = y2;
        x2=tmp.first,y2=tmp.second;
        tmp = rotate(x4, y4, angle, cx, cy);
        x3 = x4, y3 = y4;
        x4 = tmp.first, y4 = tmp.second;
    }

    return;
}

void drawRect(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, GLfloat vertex_buffer_data[], int stInd) {
    int size = getRectSize();
    GLfloat tmp[] = {
        x1, y1, z1,
        x2, y2, z2,
        x3, y3, z3,
        x1, y1, z1,
        x4, y4, z4,
        x3, y3, z3,
    };
    copy(tmp, tmp+size, vertex_buffer_data + stInd);
    return;
}

void drawCuboid(float cx, float cy, float cz, float length, float breadth, float height, GLfloat vertex_buffer_data[]) {
    int size = getCuboidSize();
    GLfloat tmp[] = {
        cx+length/2, cy+breadth/2, cz+height/2,
        cx+length/2, cy+breadth/2, cz-height/2,
        cx-length/2, cy+breadth/2, cz-height/2,
        cx+length/2, cy+breadth/2, cz+height/2,
        cx-length/2, cy+breadth/2, cz+height/2,
        cx-length/2, cy+breadth/2, cz-height/2,
        cx+length/2, cy+breadth/2, cz+height/2,
        cx+length/2, cy-breadth/2, cz+height/2,
        cx+length/2, cy-breadth/2, cz-height/2,
        cx+length/2, cy+breadth/2, cz+height/2,
        cx+length/2, cy+breadth/2, cz-height/2,
        cx+length/2, cy-breadth/2, cz-height/2,
        cx+length/2, cy+breadth/2, cz+height/2,
        cx+length/2, cy-breadth/2, cz+height/2,
        cx-length/2, cy-breadth/2, cz+height/2,
        cx+length/2, cy+breadth/2, cz+height/2,
        cx-length/2, cy+breadth/2, cz+height/2,
        cx-length/2, cy-breadth/2, cz+height/2,
        cx-length/2, cy-breadth/2, cz-height/2,
        cx+length/2, cy-breadth/2, cz-height/2,
        cx+length/2, cy+breadth/2, cz-height/2,
        cx-length/2, cy-breadth/2, cz-height/2,
        cx-length/2, cy+breadth/2, cz-height/2,
        cx+length/2, cy+breadth/2, cz-height/2,
        cx-length/2, cy-breadth/2, cz-height/2,
        cx+length/2, cy-breadth/2, cz-height/2,
        cx+length/2, cy-breadth/2, cz+height/2,
        cx-length/2, cy-breadth/2, cz-height/2,
        cx-length/2, cy-breadth/2, cz+height/2,
        cx+length/2, cy-breadth/2, cz+height/2,
        cx-length/2, cy-breadth/2, cz-height/2,
        cx-length/2, cy+breadth/2, cz-height/2,
        cx-length/2, cy+breadth/2, cz+height/2,
        cx-length/2, cy-breadth/2, cz-height/2,
        cx-length/2, cy-breadth/2, cz+height/2,
        cx-length/2, cy+breadth/2, cz+height/2,
    };
    copy(tmp, tmp+size, vertex_buffer_data);
    return;
}


void drawPol(int n, float cx, float cy, float rad, GLfloat vertex_buffer_data[], float z_cor, int stInd) {
    GLfloat prevx=rad;
    GLfloat prevy=0.0f;
    double angle=(2.0/n)*PI;
    int cntr=stInd;
    int i;
    for(i=0;i<3*n;i++)
    {
        if(i%3==0)
        {
            vertex_buffer_data[cntr] = cx;
            cntr++;
            vertex_buffer_data[cntr] = cy;
            cntr++;
            vertex_buffer_data[cntr] = z_cor;
            cntr++;
        }
        else if(i%3==1)
        {
            vertex_buffer_data[cntr] = prevx + cx;
            cntr++;
            vertex_buffer_data[cntr] = prevy + cy;
            cntr++;
            vertex_buffer_data[cntr] = z_cor;
            cntr++;
        }
        else
        {
            pii newCor = rotate(prevx, prevy, angle, 0.0f, 0.0f);
			prevx=newCor.first;
			prevy=newCor.second;
            vertex_buffer_data[cntr] = prevx + cx;
            cntr++;
            vertex_buffer_data[cntr] = prevy + cy;
            cntr++;
            vertex_buffer_data[cntr] = z_cor;
            cntr++;
        }
    }
    return;
}

