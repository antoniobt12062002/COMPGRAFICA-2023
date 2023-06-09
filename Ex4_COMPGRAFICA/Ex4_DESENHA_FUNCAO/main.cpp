#include <GL/glut.h>
#include <math.h>

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_LINE_STRIP);

    for (float x = -10; x <= 10; x += 0.1) {
        float y = sin(x) * cos(x); // função escolhida
        glVertex2f(50 * x + 100, 50 * y + 100); // escala do gráfico para a janela
    }

    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("y = sin(x) * cos(x)");
    gluOrtho2D(0, 400, 400, 0);
    glutDisplayFunc(display);
    glutMainLoop();
}
