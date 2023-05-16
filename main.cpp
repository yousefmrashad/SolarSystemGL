#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

double r, x, y, theta;
double m = 0, v = 0, e = 0, mr = 0, j = 0, s = 0, u = 0, n = 0;
double mercury_x = 400;
double mercury_y = 0;
double venus_x = 600;
double venus_y = 0;
double earth_x = 800;
double earth_y = 0;
double mars_x = 1000;
double mars_y = 0;
double jupiter_x = 1200;
double jupiter_y = 0;
double saturn_x = 1400;
double saturn_y = 0;
double uranus_x = 1600;
double uranus_y = 0;
double neptune_x = 1800;
double neptune_y = 0;
double sun_r = 200;
int sr = 1;

double zx[200];
double zy[200];

void timer(int);

void drawStars() {
    // Draw 200 random stars
    for (int z = 0; z <= 200; z++) {
        glPointSize(1.5);
        glBegin(GL_POINTS);
        glColor3ub(255, 255, 255);
        glVertex2f(zx[z], zy[z]);
        glEnd();
    }
}

void drawOrbits(){
    //draw orbits
    r = 1800;
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i <= 360; i++) {
            glPointSize(1.0f);
            glBegin(GL_POINTS);
            glColor3ub(255, 255, 255);

            theta = i * 3.142 / 180;
            glVertex2f(r * cos(theta), r * sin(theta));
            glEnd();
        }
        r -= 200;
    }
}

void drawCelestialBodies() {
    //sun halo
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 150);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(sun_r * cos(theta), sun_r * sin(theta));
    }
    glEnd();

    //sun
    glBegin(GL_POLYGON);
    glColor3ub(254, 204, 25);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(200 * cos(theta), 200 * sin(theta));
    }
    glEnd();

    //mercury
    glBegin(GL_POLYGON);
    glColor3ub(204, 126, 56);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(50 * cos(theta) + mercury_x, 50 * sin(theta) + mercury_y);
    }
    glEnd();

    //venus
    glBegin(GL_POLYGON);
    glColor3ub(215, 122, 98);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(80 * cos(theta) + venus_x, 80 * sin(theta) + venus_y);
    }
    glEnd();

    //earth
    glBegin(GL_POLYGON);
    glColor3ub(70, 248, 202);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(80 * cos(theta) + earth_x, 80 * sin(theta) + earth_y);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(125, 223, 63);
    for (int i = 200; i <= 260; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(80 * cos(theta) + earth_x, 80 * sin(theta) + earth_y);
    }
    glVertex2f(-40 + earth_x, -10 + earth_y);
    glVertex2f(-20 + earth_x, -20 + earth_y);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(125, 223, 63);
    for (int i = 280; i <= 350; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(80 * cos(theta) + earth_x, 80 * sin(theta) + earth_y);
    }
    glVertex2f(40 + earth_x, -10 + earth_y);
    glVertex2f(20 + earth_x, -20 + earth_y);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(125, 223, 63);
    for (int i = 70; i <= 130; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(80 * cos(theta) + earth_x, 80 * sin(theta) + earth_y);
    }
    glVertex2f(-40 + earth_x, 10 + earth_y);
    glVertex2f(20 + earth_x, 20 + earth_y);
    glEnd();
    //mars
    glBegin(GL_POLYGON);
    glColor3ub(198, 62, 60);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(70 * cos(theta) + mars_x, 70 * sin(theta) + mars_y);
    }
    glEnd();

    //jupiter
    glBegin(GL_POLYGON);
    glColor3ub(214, 206, 158);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(120 * cos(theta) + jupiter_x, 120 * sin(theta) + jupiter_y);
    }
    glEnd();

    //saturn
    glBegin(GL_POLYGON);
    glColor3ub(231, 203, 191);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(130 * cos(theta) + saturn_x, 60 * sin(theta) + saturn_y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(110 * cos(theta) + saturn_x, 50 * sin(theta) + saturn_y);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(227, 197, 101);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(90 * cos(theta) + saturn_x, 90 * sin(theta) + saturn_y);
    }
    glEnd();

    //uranus
    glBegin(GL_POLYGON);
    glColor3ub(36, 97, 253);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(80 * cos(theta) + uranus_x, 80 * sin(theta) + uranus_y);
    }
    glEnd();

    //neptune
    glBegin(GL_POLYGON);
    glColor3ub(153, 223, 254);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(80 * cos(theta) + neptune_x, 80 * sin(theta) + neptune_y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawStars();
    drawOrbits();
    drawCelestialBodies();

    glutSwapBuffers();
}

void init() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1900, 1900, -1900, 1900);

}


int main(int argc, char **argv) {
    for(int i = 0; i < 200; i++){
        zx[i] = rand() % 3800 - 1900;
        zy[i] = rand() % 3800 - 1900;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("Solar System Model");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
    sun_r += sr;
    if (sun_r == 200){
        sr = 1;
    }
    if(sun_r == 250){
        sr = -1;
    }
    if (n < 360) {
        theta = n * 3.142 / 180;
        neptune_x = 1800 * cos(theta);
        neptune_y = 1800 * sin(theta);
    }
    if (n >= 360) {
        n = 0;
    }
    if (u < 360) {
        theta = u * 3.142 / 180;
        uranus_x = 1600 * cos(theta);
        uranus_y = 1600 * sin(theta);
    }
    if (u >= 360) {
        u = 0;
    }
    if (s < 360) {
        theta = s * 3.142 / 180;
        saturn_x = 1400 * cos(theta);
        saturn_y = 1400 * sin(theta);
    }
    if (s >= 360) {
        s = 0;
    }
    if (j < 360) {
        theta = j * 3.142 / 180;
        jupiter_x = 1200 * cos(theta);
        jupiter_y = 1200 * sin(theta);
    }
    if (j >= 360) {
        j = 0;
    }

    if (mr < 360) {
        theta = mr * 3.142 / 180;
        mars_x = 1000 * cos(theta);
        mars_y = 1000 * sin(theta);
    }
    if (mr >= 360) {
        mr = 0;
    }

    if (e < 360) {
        theta = e * 3.142 / 180;
        earth_x = 800 * cos(theta);
        earth_y = 800 * sin(theta);
    }
    if (e >= 360) {
        e = 0;
    }

    if (v < 360) {
        theta = v * 3.142 / 180;
        venus_x = 600 * cos(theta);
        venus_y = 600 * sin(theta);
    }
    if (v >= 360) {
        v = 0;
    }

    if (m < 360) {
        theta = m * 3.142 / 180;
        mercury_x = 400 * cos(theta);
        mercury_y = 400 * sin(theta);
    }
    if (m >= 360) {
        m = 0;
    }
    n += (0.006 * 2);
    u += (0.012 * 2);
    s += (0.034 * 2);
    j += (0.084 * 2);
    mr += (0.53 * 2);
    e += (1 * 2);
    v += (1.62 * 2);
    m += (4.16 * 2);

}
