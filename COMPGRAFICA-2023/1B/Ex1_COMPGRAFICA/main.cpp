#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>

 void display(){
    glClearColor(0.0, 1.0, 0.0, 0.0); // LIMPANDO E DEFININDO AS CORES DO FUNDO PARA VERDE (GRAMADO).
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(15.0); // AUMENTANDO OS TAMANHOS DOS PONTOS.

    glBegin(GL_POINTS); // INICIANDO E DEFININDO O MODO DE DESENHO PARA PONTOS. (FLOR)

        glColor3f(1.0, 0.0, 0.0); // DEFININDO COR PARA VERMELHO

        glVertex2f(0.0, 0.0); // MEIO
        glVertex2f(0.0, 0.05);
        glVertex2f(0.0, 0.15);
        glVertex2f(0.0, 0.25);
        glVertex2f(0.0, 0.35);
        glVertex2f(0.0, 0.45);

        glVertex2f(0.1, 0.0);  // DIREITA
        glVertex2f(0.1, 0.05);
        glVertex2f(0.1, 0.15);
        glVertex2f(0.1, 0.25);
        glVertex2f(0.1, 0.35);

        glVertex2f(0.2, 0.05); // DETALHE
        glVertex2f(0.2, 0.15);
        glVertex2f(0.2, 0.25);
        glVertex2f(0.2, 0.35);
        glVertex2f(0.2, 0.45);

        glVertex2f(-0.1, 0.0); // ESQUERDA
        glVertex2f(-0.1, 0.05);
        glVertex2f(-0.1, 0.15);
        glVertex2f(-0.1, 0.25);
        glVertex2f(-0.1, 0.35);

        glVertex2f(-0.2, 0.05); // DETALHE
        glVertex2f(-0.2, 0.15);
        glVertex2f(-0.2, 0.25);
        glVertex2f(-0.2, 0.35);
        glVertex2f(-0.2, 0.45);

    glEnd();

        glBegin(GL_POINTS); // INICIANDO E DEFININDO O MODO DE DESENHO PARA PONTOS. (CAULE)

        glColor3f(0.0, 0.5, 0.0); // DEFININDO COR PARA VERDE ESCURO

        glVertex2f(0.0, -0.1);
        glVertex2f(0.0, -0.2);
        glVertex2f(0.1, -0.2);
        glVertex2f(0.1, -0.3);
        glVertex2f(0.0, -0.3);
        glVertex2f(0.0, -0.4);
        glVertex2f(-0.1, -0.4);
        glVertex2f(0.0, -0.5);

    glEnd();
    glFlush();
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutCreateWindow("Flores");
    glutInitWindowSize(400, 400);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
