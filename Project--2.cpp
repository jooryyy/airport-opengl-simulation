#include <GL/glut.h>
#include <math.h>


// Global variables for animation and keyboard
float planeX = 0.0f;
float planeY = 190.0f;
float wheelOffset = 0.0f;
float speed = 0.0f;       // Speed control & Acceleration
int flightMode = 0;       // 0: Takeoff, 1: Landing
bool tookOff = false;           // Whether the plane has taken off
const float MAX_SPEED = 3.0f;   // Maximum speed the plane can reach
const float SPEED_STEP = 0.5f;  // Amount speed changes per key press

// Effects Module vars (Joory)
float coff = 0.0f;   // cloud offset
int day = 1;          // 1 = day, 0 = night
int liton = 1;        // runway lights on/off
int blk = 0;          // blink frame counter
int dn = 0;           // day/night frame counter
float flgoff = 0.0f;  // flag wave offset
float radang = 0.0f;  // radar rotation angle

//====================================================
// Sky Module
//====================================================
// Draw a filled circle
void drawCircle(float x, float y, float r)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        float angle = i * 3.1415926f / 180.0f;
        glVertex2f(
            x + r * cos(angle),
            y + r * sin(angle)
        );
    }
    glEnd();
}
// Draw a cloud using multiple circles
void drawCloud(float x, float y)
{
    glColor3f(1, 1, 1);
    drawCircle(x, y, 20);
    drawCircle(x + 20, y + 10, 22);
    drawCircle(x + 45, y, 20);
    drawCircle(x + 22, y - 10, 18);
}
// Draw the complete sky scene
void drawSky()
{
    //---------------- Sky ----------------
    if (day)
        glColor3f(0.53f, 0.81f, 0.98f);
    else
        glColor3f(0.05f, 0.05f, 0.20f);

    glBegin(GL_QUADS);
    glVertex2f(0, 700);
    glVertex2f(1000, 700);
    glVertex2f(1000, 250);
    glVertex2f(0, 250);
    glEnd();
    //---------------- Ground ----------------
    if (day)
        glColor3f(0.22f, 0.65f, 0.22f);
    else
        glColor3f(0.08f, 0.25f, 0.08f);

    glBegin(GL_QUADS);
    glVertex2f(0, 250);
    glVertex2f(1000, 250);
    glVertex2f(1000, 0);
    glVertex2f(0, 0);
    glEnd();
    //---------------- Sun / Moon ----------------
    if (day)
        glColor3f(1, 1, 0);
    else
        glColor3f(0.9f, 0.9f, 0.85f);
    drawCircle(850, 580, 45);
    //---------------- Clouds (animated) ----------------
    drawCloud(fmod(120 + coff, 1100) - 100, 560);
    drawCloud(fmod(350 + coff, 1100) - 100, 620);
    drawCloud(fmod(620 + coff, 1100) - 100, 520);
}
//====================================================
// Runway Module (Leena )
//====================================================
void drawRunway()
{
    // the main runway
    glColor3f(0.26f, 0.26f, 0.26f);
    glBegin(GL_QUADS);
    glVertex2f(0, 250); glVertex2f(1000, 250);
    glVertex2f(1000, 130); glVertex2f(0, 130);
    glEnd();

    // the white lines
    glColor3f(1.0f, 1.0f, 1.0f);
    for (float x = 50; x < 950; x += 60) {
        glBegin(GL_QUADS);
        glVertex2f(x, 195); glVertex2f(x + 30, 195);
        glVertex2f(x + 30, 185); glVertex2f(x, 185);
        glEnd();
    }

    // Runway edge lights (blinking added by Joory)
    if (liton)
        glColor3f(1.0f, 0.75f, 0.0f);
    else
        glColor3f(0.4f, 0.3f, 0.0f);

    for (float x = 20; x < 980; x += 65) {
        // Top lights (hidden behind the building area)
        if (x < 500 || x > 850) {
            glBegin(GL_QUADS);
            glVertex2f(x, 255); glVertex2f(x + 6, 255);
            glVertex2f(x + 6, 250); glVertex2f(x, 250);
            glEnd();
        }

        // Bottom lights
        glBegin(GL_QUADS);
        glVertex2f(x, 130); glVertex2f(x + 6, 130);
        glVertex2f(x + 6, 125); glVertex2f(x, 125);
        glEnd();
    }
}
//====================================================
// Airport Module
// (Third student's code goes here)
//====================================================
//====================================================
// Plane Module (Leen)
//====================================================
void drawPlane()
{
    // Link to global vars
    float r = planeX;
    float f = planeY;

    // Tail
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.2f, 0.8f);

    glVertex2i(r + 20, f + 50);
    glVertex2i(r + 40, f + 50);
    glVertex2i(r + 40, f + 60);
    glVertex2i(r + 20, f + 80);
    glVertex2i(r, f + 80);

    glEnd();

    // Body
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2i(r + 20, f + 30);
    glVertex2i(r + 210, f + 30);
    glVertex2i(r + 210, f + 40);
    glVertex2i(r + 200, f + 50);
    glVertex2i(r + 160, f + 50);
    glVertex2i(r + 160, f + 60);
    glVertex2i(r + 30, f + 60);
    glVertex2i(r, f + 50);
    glVertex2i(r, f + 40);

    glEnd();

    // Cockpit
    glBegin(GL_POLYGON);
    glColor3f(0.35f, 0.80f, 1.0f);

    glVertex2i(r + 160, f + 50);
    glVertex2i(r + 180, f + 50);
    glVertex2i(r + 170, f + 60);
    glVertex2i(r + 160, f + 60);

    glEnd();

    // Windows
    glLineWidth(4);

    for (int i = 0; i < 6; i++)
    {
        glBegin(GL_LINES);

        glColor3f(0.0f, 0.0f, 0.0f);

        glVertex2f(r + 40 + (i * 20), f + 50);
        glVertex2f(r + 50 + (i * 20), f + 50);

        glEnd();
    }

    // Wing
    glBegin(GL_POLYGON);
    glColor3f(0.75f, 0.75f, 0.75f);

    glVertex2i(r + 30, f + 20);
    glVertex2i(r + 120, f + 20);
    glVertex2i(r + 140, f + 40);
    glVertex2i(r + 40, f + 40);
    glVertex2i(r, f + 30);

    glEnd();

    // Engine 1
    glBegin(GL_POLYGON);
    glColor3f(0.35f, 0.35f, 0.35f);

    glVertex2i(r + 50, f + 10);
    glVertex2i(r + 70, f + 10);
    glVertex2i(r + 70, f + 30);
    glVertex2i(r + 50, f + 30);
    glVertex2i(r + 40, f + 20);

    glEnd();

    // Engine 2
    glBegin(GL_POLYGON);
    glColor3f(0.35f, 0.35f, 0.35f);

    glVertex2i(r + 90, f + 10);
    glVertex2i(r + 110, f + 10);
    glVertex2i(r + 110, f + 30);
    glVertex2i(r + 90, f + 30);
    glVertex2i(r + 80, f + 20);

    glEnd();

    // Wheel 1
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(r + 40, f + 20);
    glVertex2f(r + 40, f + wheelOffset); // Move up
    glEnd();
    drawCircle(r + 40, f + wheelOffset, 5); // Move up

    // Wheel 2
    glBegin(GL_LINES);
    glVertex2f(r + 140, f + 30);
    glVertex2f(r + 140, f + wheelOffset); // Move up
    glEnd();
    drawCircle(r + 140, f + wheelOffset, 5); // Move up

    // Wheel 3
    glBegin(GL_LINES);
    glVertex2f(r + 180, f + 30);
    glVertex2f(r + 180, f + wheelOffset); // Move up
    glEnd();
    drawCircle(r + 180, f + wheelOffset, 5); // Move up
}
//====================================================
// Effects Module (Joory)
//====================================================
// 3 waving flags near the runway
void drawflags()
{
    float xs[3] = { 60, 500, 940 };

    for (int i = 0; i < 3; i++)
    {
        float px = xs[i];
        float py = 255;
        float w = sin(flgoff + i) * 8.0f; // wind wave

        // pole
        glColor3f(0.3f, 0.3f, 0.3f);
        glBegin(GL_LINES);
        glVertex2f(px, py);
        glVertex2f(px, py + 45);
        glEnd();

        // flag cloth
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        glVertex2f(px, py + 45);
        glVertex2f(px + 30 + w, py + 40);
        glVertex2f(px + 30 + w, py + 28);
        glVertex2f(px, py + 33);
        glEnd();
    }
}

// rotating radar
void drawradar()
{
    float rx = 200;  
    float ry = 250;  

    // support tower
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(rx, ry);
    glVertex2f(rx, ry + 70);
    glEnd();

    // platform on top of the tower
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(rx - 12, ry + 70);
    glVertex2f(rx + 12, ry + 70);
    glVertex2f(rx + 12, ry + 78);
    glVertex2f(rx - 12, ry + 78);
    glEnd();

    // rotating dish bar
    glPushMatrix();
    glTranslatef(rx, ry + 78, 0);
    glRotatef(radang * 57.2958f, 0, 0, 1); // radians to degrees

    glColor3f(0.85f, 0.85f, 0.85f);
    glBegin(GL_QUADS);
    glVertex2f(-35, -5);
    glVertex2f(35, -5);
    glVertex2f(35, 5);
    glVertex2f(-35, 5);
    glEnd();

    // center hub
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(0, 0, 5);

    glPopMatrix();
}

//====================================================
// Animation Module (Razan)

void updateTimer(int value)
{
    if (flightMode == 0) {
        // --- TAKEOFF PHASE ---
        planeX += speed;

        // 2. Takeoff & Retract wheels
        if (tookOff) {
            planeY += (speed * 0.4f);
            if (wheelOffset < 20.0f) wheelOffset += 0.25f;
        }

        // 3. Switch to Landing mode when off-screen
        if (planeX > 1100.0f) {
            flightMode = 1;
            planeX = -200.0f;
            planeY = 450.0f;
            speed = 2.5f;
        }
    }
    else if (flightMode == 1) {
        // --- LANDING PHASE ---

        planeX += speed;

        // 1. Descend & Deploy wheels
        if (planeY > 190.0f) {
            planeY -= 1.0f;
            if (wheelOffset > 0.0f) wheelOffset -= 0.25f;
        }
        // 2. Touchdown & Deceleration
        else {
            planeY = 190.0f;
            if (speed > 0.5f) speed -= 0.02f;
        }

        // 3. Switch back to Takeoff mode
        if (planeX > 1100.0f) {
            flightMode = 0;
            planeX = 0.0f;
            planeY = 190.0f;
            speed = 0.0f;
            tookOff = false;
        }
    }

    // Joory's effects updates
    coff += 0.3f;
    if (coff > 1100.0f) coff -= 1100.0f;

    blk++;
    if (blk >= 30) {
        liton = !liton;
        blk = 0;
    }

    dn++;
    if (dn >= 600) {
        day = !day;
        dn = 0;
    }

    flgoff += 0.1f;

    radang += 0.05f;
    if (radang > 6.2832f) radang -= 6.2832f; // keep angle within 0-2*PI

    // Redraw frame
    glutPostRedisplay();

    // 16ms delay (~60fps)
    glutTimerFunc(16, updateTimer, 0);
}
//====================================================
// Keyboard Module (dana)
//====================================================

// Handles keyboard input for takeoff, reset, and exit
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        if (!tookOff && speed >= MAX_SPEED) {
            tookOff = true;
        }
        break;

    case 'r':
    case 'R':
        planeX = 0.0f;
        planeY = 190.0f;
        speed = 0.0f;
        tookOff = false;
        flightMode = 0;
        wheelOffset = 0.0f;
        break;

    case 'n':
    case 'N':
        day = !day;   // Manually toggle day/night mode 
        dn = 0;      // Reset the automatic toggle counter to avoid an immediate double-switch
        break;

    case 27:
        exit(0);
        break;
    }
    // Refresh the screen to reflect any changes
    glutPostRedisplay();
}

// Handles arrow key presses to increase or decrease the plane's speed
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if (speed < MAX_SPEED)
            speed += SPEED_STEP;
        break;

    case GLUT_KEY_DOWN:
        if (!tookOff) {
            if (speed > 0)
                speed -= SPEED_STEP;
        }
        else {   // Prevent speed from dropping below 3 while airborne (avoids stopping mid-air)
            if (speed > 1.0)
                speed -= SPEED_STEP;
        }
        break;
    }

    glutPostRedisplay();
}
//====================================================
// Display Function
//====================================================
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawSky();
    drawRunway();
    // drawAirport();
    drawflags();
    drawradar();
    drawPlane();
    glFlush();
}
//====================================================
// Main Function
//====================================================
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Airport Runway Simulation");
    gluOrtho2D(0, 1000, 0, 700);
    glutDisplayFunc(display);
    // Start timer
    glutTimerFunc(0, updateTimer, 0);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}