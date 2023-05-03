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
    glutPostRedisplay();
}

void rotate(float angle) {
    float theta = angle * M_PI / 180.0;  // converte ângulo em graus para radianos

    int center_x = 400 / 2;
    int center_y =  400 / 2;

    for (auto& point : points) {
        int x = point.x - center_x;
        int y = point.y - center_y;

        point.x = center_x + x * cos(theta) - y * sin(theta);
        point.y = center_y + x * sin(theta) + y * cos(theta);
    }

    glutPostRedisplay();
}

void escala(float aumentar) {
    float fatorEscala = aumentar;

    int center_x = 400 / 2;
    int center_y =  400 / 2;

    for (auto& point : points) {
        int x = point.x - center_x;
        int y = point.y - center_y;

        point.x = center_y + x * fatorEscala;
        point.y = center_y + y * fatorEscala;
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            for (auto& point : points) {
                point.x -= 10;
            }
            break;
        case 'd':
            for (auto& point : points) {
                point.x += 10;
            }
            break;
        case 'w':
            for (auto& point : points) {
                point.y -= 10;
            }
            break;
        case 's':
            for (auto& point : points) {
                point.y += 10;
            }
            break;
        case 'r':
            rotate(45);  // rotação de 45 graus
            break;
        case 'R':
            rotate(-45);  // rotação de -45 graus
            break;
        case 'e':
            escala(1.1);
            break;
        case 'E':
            escala(0.9);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Atividade 5");
    gluOrtho2D(0, 400, 400, 0);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
