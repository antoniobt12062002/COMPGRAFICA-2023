#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

struct Vertex {
    float x, y, z;

    Vertex(float x, float y, float z) : x(x), y(y), z(z) {}
};

std::vector<Vertex> vertices;
std::vector<std::vector<int>> faces;

void loadObjFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        char trash;

        if (line.substr(0, 2) == "v ") {
            float x, y, z;
            iss >> trash >> x >> y >> z;
            vertices.push_back(Vertex(x, y, z));
        } else if (line.substr(0, 2) == "f ") {
            std::vector<int> faceIndices;
            int vIndex;
            iss >> trash;

            while (iss >> vIndex) {
                faceIndices.push_back(vIndex - 1);
                if (iss.peek() == '/') {
                    iss.ignore(2, ' '); // Ignore normal and texture indices
                }
            }

            faces.push_back(faceIndices);
        }
    }

    file.close();
}

void drawObjLineStrip() {
    glBegin(GL_LINE_STRIP);
    for (const std::vector<int>& face : faces) {
        for (int index : face) {
            const Vertex& vertex = vertices[index];
            glVertex3f(vertex.x, vertex.y, vertex.z);
        }
        const Vertex& firstVertex = vertices[face[0]];
        glVertex3f(firstVertex.x, firstVertex.y, firstVertex.z);
    }
    glEnd();
}

// Funções de Transformação Personalizadas

void scale(float sx, float sy, float sz) {
    for (Vertex& vertex : vertices) {
        vertex.x *= sx;
        vertex.y *= sy;
        vertex.z *= sz;
    }
}

void translate(float dx, float dy, float dz) {
    for (Vertex& vertex : vertices) {
        vertex.x += dx;
        vertex.y += dy;
        vertex.z += dz;
    }
}

void rotateX(float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);

    for (Vertex& vertex : vertices) {
        float newY = vertex.y * cosA - vertex.z * sinA;
        float newZ = vertex.y * sinA + vertex.z * cosA;
        vertex.y = newY;
        vertex.z = newZ;
    }
}

void rotateY(float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);

    for (Vertex& vertex : vertices) {
        float newX = vertex.x * cosA + vertex.z * sinA;
        float newZ = -vertex.x * sinA + vertex.z * cosA;
        vertex.x = newX;
        vertex.z = newZ;
    }
}

void rotateZ(float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);

    for (Vertex& vertex : vertices) {
        float newX = vertex.x * cosA - vertex.y * sinA;
        float newY = vertex.x * sinA + vertex.y * cosA;
        vertex.x = newX;
        vertex.y = newY;
    }
}

// Variáveis de controle das transformações
float scale_factor = 1.0f;
float translate_x = 0.0f;
float translate_y = 0.0f;
float translate_z = 0.0f;
float rotate_x = 0.0f;
float rotate_y = 0.0f;
float rotate_z = 0.0f;

// Função de callback para controle das transformações via teclado
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Translação
        case 'x':
            translate_x -= 0.1f;
            break;
        case 'X':
            translate_x += 0.1f;
            break;
        case 'y':
            translate_y -= 0.1f;
            break;
        case 'Y':
            translate_y += 0.1f;
            break;
        case 'z':
            translate_z -= 0.1f;
            break;
        case 'Z':
            translate_z += 0.1f;
            break;
        // Rotação
        case 'r':
            rotate_x -= 0.1f;
            ;
            break;
        case 'R':
            rotate_x += 0.1f;
            break;
        case 'u':
            rotate_y -= 0.1f;
            break;
        case 'U':
            rotate_y += 0.1f;
            break;
        case 'w':
            rotate_z -= 0.1f;
            break;
        case 'W':
            rotate_z += 0.1f;
            break;
        // Escala
        case 's':
            scale_factor -= 0.1f;
            break;
        case 'S':
            scale_factor += 0.1f;
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);
    glColor3f(1.0, 1.0, 1.0);

    // Aplicar as transformações antes de desenhar o objeto
    glPushMatrix();
    glTranslatef(translate_x, translate_y, translate_z);
    glRotatef(rotate_x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotate_y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotate_z, 0.0f, 0.0f, 1.0f);
    glScalef(scale_factor, scale_factor, scale_factor);

    drawObjLineStrip();
    glPopMatrix();

    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLfloat)width / (GLfloat)height, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.obj>" << std::endl;
        return 1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OBJ File Viewer");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    loadObjFile(argv[1]);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
