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
    glLineWidth(2.0);

    if (points.size() > 1) {
        glBegin(GL_LINE_STRIP);
        for (const auto& point : points) {
            glVertex2i(point.x, point.y);
        }
        glEnd();
    }

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (state != GLUT_DOWN) return;

    if (button == GLUT_LEFT_BUTTON) { // ADD LINHA NO VETOR
        points.push_back({x, y});
    }
    else if (button == GLUT_RIGHT_BUTTON) { //REMOVE LINHA

        int min_distance = std::numeric_limits<int>::max();
        int closest_index = -1;
        for (int i = 1; i < points.size(); i++) {
            int distance = std::sqrt(
                std::pow(points[i].x - x, 2) + std::pow(points[i].y - y, 2)) +
                std::sqrt(std::pow(points[i-1].x - x, 2) + std::pow(points[i-1].y - y, 2));
            if (distance < min_distance) {
                min_distance = distance;
                closest_index = i;
            }
        }
        if (closest_index != -1) {
            points.erase(points.begin() + closest_index - 1, points.begin() + closest_index + 1);
        }
    }

    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Linhas");
    gluOrtho2D(0, 400, 400, 0);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
