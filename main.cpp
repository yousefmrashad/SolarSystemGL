#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <cmath>

// Orbit radius and global theta
double r, theta;

// Angular position displacement variables
double m = 0, v = 0, e = 0, mr = 0, j = 0, s = 0, u = 0, n = 0;

// Planet position variables declaration and initialization
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

// Sun halo radius variable
double sun_r = 250;

// Sun halo increment/decrement
int sr = 1;

// Timer stop flag
bool stop = false;

// Random star positions
double zx[200];
double zy[200];

// Timer callback function
void timer(int);

// Planet position reset function
void resetPlanetPositions() {
    mercury_x = 400;
    mercury_y = 0;
    venus_x = 600;
    venus_y = 0;
    earth_x = 800;
    earth_y = 0;
    mars_x = 1000;
    mars_y = 0;
    jupiter_x = 1200;
    jupiter_y = 0;
    saturn_x = 1400;
    saturn_y = 0;
    uranus_x = 1600;
    uranus_y = 0;
    neptune_x = 1800;
    neptune_y = 0;
    n = 0;
    u = 0;
    s = 0;
    j = 0;
    mr = 0;
    e = 0;
    v = 0;
    m = 0;
}

// Keyboard callback function
void keyboard(unsigned char c, int x, int y) {
    if (c == 27) exit(0); // Escape key
    if (c == 's' || c == 'S') {
        stop = !stop;
        if (!stop) {
            timer(0);  // Start the timer immediately
        }
    };
    if (c == 'r' || c == 'R') resetPlanetPositions();
}

// Drawing functions
void drawStars() {
    // Draw 200 random stars
    for (int z = 0; z <= 200; z++) {
        glPointSize(1.5);
        glBegin(GL_POINTS);
        glColor3ub(255, 255, 255);
        // Positions obtained from loop in main()
        glVertex2f(zx[z], zy[z]);
        glEnd();
    }
}

void drawOrbits() {
    // Draw orbits in descending order
    r = 1800;
    glPointSize(1.0f);
    glBegin(GL_POINTS);
    glColor3ub(255, 255, 255);
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i <= 360; i++) {
            theta = i * 3.142 / 180;
            glVertex2f(r * cos(theta), r * sin(theta));
        }
        // Update orbit radius - move to next planet
        r -= 200;
    }
    glEnd();
}

void drawCelestialBodies() {

    // Sun halo
    glBegin(GL_POLYGON);
    // Same as Sun color, but with 50% transparency
    glColor4f(1, 0.8, 0.098,0.5);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(sun_r * cos(theta), sun_r * sin(theta)); // `sun_r` (halo radius) is updated every timer call
    }
    glEnd();

    // Sun
    glBegin(GL_POLYGON);
    glColor3ub(254, 204, 25);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(250 * cos(theta), 250 * sin(theta)); // Sun radius = 250
    }
    glEnd();

    // Mercury
    glBegin(GL_POLYGON);
    glColor3ub(204, 126, 56);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(50 * cos(theta) + mercury_x, 50 * sin(theta) + mercury_y); // Mercury radius = 50
        // x and y positions are updated every timer call
    }
    glEnd();

    // Venus
    glBegin(GL_POLYGON);
    glColor3ub(215, 122, 98);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(80 * cos(theta) + venus_x, 80 * sin(theta) + venus_y);
    }
    glEnd();

    // Earth
    glBegin(GL_POLYGON);
    glColor3ub(70, 248, 202);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(80 * cos(theta) + earth_x, 80 * sin(theta) + earth_y);
    }
    glEnd();

    // Earth landmasses (drawn on top of the planet)
    glBegin(GL_POLYGON);

    // Green
    glColor3ub(125, 223, 63);
    // Draw the polygon's outside curve tracing the curvature of the Earth
    for (int i = 200; i <= 260; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(80 * cos(theta) + earth_x, 80 * sin(theta) + earth_y);
    }
    // Complete polygon with two points inside Earth
    // Negatives indicate the landmass is in the third quarter
    glVertex2f(-40 + earth_x, -10 + earth_y);
    glVertex2f(-20 + earth_x, -20 + earth_y);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(125, 223, 63);
    for (int i = 280; i <= 350; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(80 * cos(theta) + earth_x, 80 * sin(theta) + earth_y);
    }
    // Only negative y indicate the landmass is in the fourth quarter
    glVertex2f(40 + earth_x, -10 + earth_y);
    glVertex2f(20 + earth_x, -20 + earth_y);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(125, 223, 63);
    for (int i = 70; i <= 130; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(80 * cos(theta) + earth_x, 80 * sin(theta) + earth_y);
    }
    // Negatives x indicate the vertex is in the second quarter
    // Positives indicate the vertex is in the first quarter
    glVertex2f(-40 + earth_x, 10 + earth_y);
    glVertex2f(20 + earth_x, 20 + earth_y);
    glEnd();

    // Mars
    glBegin(GL_POLYGON);
    glColor3ub(198, 62, 60);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(70 * cos(theta) + mars_x, 70 * sin(theta) + mars_y);
    }
    glEnd();

    // Jupiter
    glBegin(GL_POLYGON);
    glColor3ub(214, 206, 158);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(120 * cos(theta) + jupiter_x, 120 * sin(theta) + jupiter_y);
    }
    glEnd();

    // Saturn rings; Two concentric ellipses
    // Outside ring
    glBegin(GL_POLYGON);
    // Ring color
    glColor3ub(231, 203, 191);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        // Ellipse where x is longer than y
        glVertex2f(130 * cos(theta) + saturn_x, 60 * sin(theta) + saturn_y);
    }
    glEnd();

    // Inside ring
    glBegin(GL_POLYGON);

    // Space color (between the ring and the planet)
    glColor3ub(0, 0, 0);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(110 * cos(theta) + saturn_x, 50 * sin(theta) + saturn_y);
    }
    glEnd();

    // Saturn (drawn on top of the rings)
    glBegin(GL_POLYGON);
    glColor3ub(227, 197, 101);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(90 * cos(theta) + saturn_x, 90 * sin(theta) + saturn_y);
    }
    glEnd();

    // Uranus
    glBegin(GL_POLYGON);
    glColor3ub(36, 97, 253);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(80 * cos(theta) + uranus_x, 80 * sin(theta) + uranus_y);
    }
    glEnd();

    // Neptune
    glBegin(GL_POLYGON);
    glColor3ub(153, 223, 254);
    for (int i = 0; i <= 360; i++) {
        theta = i * 3.142 / 180;
        glVertex2f(80 * cos(theta) + neptune_x, 80 * sin(theta) + neptune_y);
    }
    glEnd();
}

void display() {
    // Clearing color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Drawing objects
    drawStars();
    drawOrbits();
    drawCelestialBodies();

    // Swap front and back buffers (double buffering explained below)
    glutSwapBuffers();
}

void init() {
    // Space color (black)
    glClearColor(0, 0, 0, 0);

    // This function sets the current matrix mode to the projection matrix.
    // The projection matrix is responsible for transforming 3D coordinates to 2D screen coordinates.
    glMatrixMode(GL_PROJECTION);

    // Loading identity matrix to reset transforms
    glLoadIdentity();

    // Defining the coordinate system
    gluOrtho2D(-1900, 1900, -1900, 1900);

    // Enable blending in order to achieve transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


int main(int argc, char **argv) {

    // Obtaining star positions using `rand()`
    // Modulus is used because no remainder is bigger than dividend, thus `rand() % 3800` will return max of 3799
    // Subtract by 1900 to get both positive and negative coordinates, from -1900 to 1899 (ortho2D bounds)
    for (int i = 0; i < 200; i++) {
        zx[i] = rand() % 3800 - 1900;
        zy[i] = rand() % 3800 - 1900;
    }

    glutInit(&argc, argv);

    // This function sets the display mode for the window.
    // The GLUT_DOUBLE flag specifies double buffering, which helps to prevent flickering in the animation.
    // The GLUT_RGB flag indicates that the color buffer should use RGB color model.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("Solar System Model");

    init();

    // Assign display and keyboard callback functions
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    // Set timer callback function; Called every set amount of time to update positions of objects
    // The timer is first called at time 0
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}

void timer(int) {
    // Call display function again
    glutPostRedisplay();

    if (!stop) {
        // Call timer again at time 10
        glutTimerFunc(10, timer, 0);
    }

    // Update Sun halo radius
    sun_r += sr;
    if (sun_r == 250) {
        sr = 1;
    }
    if (sun_r == 300) {
        sr = -1;
    }

    // Update Neptune angular position
    if (n < 360) {
        theta = n * 3.142 / 180;
        neptune_x = 1800 * cos(theta);
        neptune_y = 1800 * sin(theta);
    }
    if (n >= 360) {
        n = 0;
    }

    // Update Uranus angular position
    if (u < 360) {
        theta = u * 3.142 / 180;
        uranus_x = 1600 * cos(theta);
        uranus_y = 1600 * sin(theta);
    }
    if (u >= 360) {
        u = 0;
    }

    // Update Saturn angular position
    if (s < 360) {
        theta = s * 3.142 / 180;
        saturn_x = 1400 * cos(theta);
        saturn_y = 1400 * sin(theta);
    }
    if (s >= 360) {
        s = 0;
    }

    // Update Jupiter angular position
    if (j < 360) {
        theta = j * 3.142 / 180;
        jupiter_x = 1200 * cos(theta);
        jupiter_y = 1200 * sin(theta);
    }
    if (j >= 360) {
        j = 0;
    }

    // Update Mars angular position
    if (mr < 360) {
        theta = mr * 3.142 / 180;
        mars_x = 1000 * cos(theta);
        mars_y = 1000 * sin(theta);
    }
    if (mr >= 360) {
        mr = 0;
    }

    // Update Earth angular position
    if (e < 360) {
        theta = e * 3.142 / 180;
        earth_x = 800 * cos(theta);
        earth_y = 800 * sin(theta);
    }
    if (e >= 360) {
        e = 0;
    }

    // Update Venus angular position
    if (v < 360) {
        theta = v * 3.142 / 180;
        venus_x = 600 * cos(theta);
        venus_y = 600 * sin(theta);
    }
    if (v >= 360) {
        v = 0;
    }

    // Update Mercury angular position
    if (m < 360) {
        theta = m * 3.142 / 180;
        mercury_x = 400 * cos(theta);
        mercury_y = 400 * sin(theta);
    }
    if (m >= 360) {
        m = 0;
    }

    // Angular position updates calculated respective to Earth
    n += (0.006 * 2);
    u += (0.012 * 2);
    s += (0.034 * 2);
    j += (0.084 * 2);
    mr += (0.53 * 2);
    e += (1 * 2);
    v += (1.62 * 2);
    m += (4.16 * 2);
}
