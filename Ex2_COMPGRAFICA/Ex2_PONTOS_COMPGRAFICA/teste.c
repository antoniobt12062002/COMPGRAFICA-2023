#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glut.h>

// Variáveis globais
int window_width = 800; // largura da janela
int window_height = 600; // altura da janela
std::vector<int> points; // vetor que armazena as coordenadas dos pontos
int selected_point_index = -1; // índice do ponto selecionado (-1 = nenhum ponto selecionado)

// Função que desenha os pontos
void drawPoints() {
    glPointSize(5);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < points.size(); i += 2) {
        glVertex2i(points[i], points[i + 1]);
    }
    glEnd();
}

// Verifica se o clique foi dentro de um ponto e retorna o índice do ponto selecionado
int pointSelection(int x, int y) {
    for (int i = 0; i < points.size(); i += 2) {
        float distance = std::sqrt(std::pow(x - points[i], 2) + std::pow(window_height - y - points[i + 1], 2));
        if (distance <= 5) {
            return i/2;
        }
    }
    return -1;
}

// Função callback do mouse
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Cria um novo ponto
        points.push_back(x);
        points.push_back(window_height - y);
        glutPostRedisplay();
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Seleciona o ponto mais próximo
        selected_point_index = pointSelection(x, y);
    }
}

// Função callback do teclado
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            if (selected_point_index != -1) {
                points[selected_point_index * 2 + 1] += 10;
                glutPostRedisplay();
            }
            break;
        case 'a':
            if (selected_point_index != -1) {
                points[selected_point_index * 2] -= 10;
                glutPostRedisplay();
            }
            break;
        case 's':
            if (selected_point_index != -1) {
                points[selected_point_index * 2 + 1] -= 10;
                glutPostRedisplay();
            }
            break;
        case 'd':
            if (selected_point_index != -1) {
                points[selected_point_index * 2] += 10;
                glutPostRedisplay();
            }
            break;
    }
}

// Função callback do desenho da cena
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPoints();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Ponto e Movimento");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutMainLoop();
    return 0;
}
