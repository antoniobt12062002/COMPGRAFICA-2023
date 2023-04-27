#include <GL/glut.h>
#include <math.h>

int CliqueMouseX, CliqueMouseY; // coordenadas do X, Y
int raio = 30;

void desenhaCirculo(int x, int y, int raio) {
    glBegin(GL_LINE_STRIP);
    double angulo = 0;
    for (double i = 0; i <= 360; i++) {
        glVertex2i(x + raio * cos(angulo), y + raio * sin(angulo)); // adiciona um vértice com coordenadas calculadas a partir do ângulo atual
        angulo = i * (3.14 / 360);
    }
    glEnd();
}

void desenhaLinha(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glVertex2i(x1, y1); // adiciona o primeiro ponto da linha
    glVertex2i(x2, y2); // adiciona o segundo ponto da linha
    glEnd();
}

void desenhaLagrima(int x, int y, int raio) {
    desenhaLinha(x, y - 60, x - 30, y); // desenha a primeira linha da lágrima
    desenhaCirculo(x, y, raio); // desenha o círculo da lágrima
    desenhaLinha(x, y - 60, x + 30, y); // desenha a segunda linha da lágrima
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    desenhaLagrima(CliqueMouseX, CliqueMouseY, raio);

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        CliqueMouseX = x;
        CliqueMouseY = y;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Tear Drop");
    gluOrtho2D(0, 400, 400, 0);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
