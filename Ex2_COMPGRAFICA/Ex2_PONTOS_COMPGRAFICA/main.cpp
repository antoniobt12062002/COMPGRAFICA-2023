#include <GL/glut.h>
#include <vector>
#include <limits>
#include <cmath>

struct Point {
    int x;
@@ -47,11 +49,32 @@ void keyboard(int key, int x, int y) {
}

void mouse(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;
    points.push_back({x, y});
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
