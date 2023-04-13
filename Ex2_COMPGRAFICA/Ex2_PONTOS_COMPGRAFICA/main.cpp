#include <GL/glut.h>
#include <vector>
#include <limits>
#include <cmath>

struct Point {
    int x;
    int y;
};

std::vector<Point> points;  //VETOR PARA ARMAZER PONTOS

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);  //DEFINE A COR BRANCA PARA O PONTO
    glPointSize(5.0);

    for (const auto& point : points) {
        glBegin(GL_POINTS);
        glVertex2i(point.x, point.y);
        glEnd();
    }

    glFlush();
}

void keyboard(int key, int x, int y) {
    if (points.empty()) return;

    Point& last_point = points.back();

    switch (key) {
        case GLUT_KEY_LEFT:
            last_point.x -= 5;
            break;
        case GLUT_KEY_RIGHT:
            last_point.x += 5;
            break;
        case GLUT_KEY_UP:
            last_point.y -= 5;
            break;
        case GLUT_KEY_DOWN:
            last_point.y += 5;
            break;
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (state != GLUT_DOWN) return;

    if (button == GLUT_LEFT_BUTTON) { // ADD PONTO NO VERTOR
        points.push_back({x, y});
}
else if (button == GLUT_RIGHT_BUTTON) { //REMOVE PONTO

        int min_distance = std::numeric_limits<int>::max();
        int closest_index = -1;
        for (int i = 0; i < points.size(); i++) {
            int distance = std::sqrt(std::pow(points[i].x - x, 2) + std::pow(points[i].y - y, 2));
            if (distance < min_distance) {
                min_distance = distance;
                closest_index = i;
            }
        }
        if (closest_index != -1) {
            points.erase(points.begin() + closest_index);
        }
    }

    glutPostRedisplay();

}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Pontos");
    gluOrtho2D(0, 400, 400, 0);
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
