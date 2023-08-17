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

const int COLOR_RED = 1;
const int COLOR_GREEN = 2;
const int COLOR_BLUE = 3;
int selectedColor = COLOR_RED;

void loadObjFile(const char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        char trash;

        if (line.substr(0, 2) == "v ")
        {
            float x, y, z;
            iss >> trash >> x >> y >> z;
            vertices.push_back(Vertex(x, y, z));
        }
        else if (line.substr(0, 2) == "f ")
        {
            std::vector<int> faceIndices;
            int vIndex, tIndex, nIndex;
            iss >> trash;

            while (iss >> vIndex)
            {
                faceIndices.push_back(vIndex - 1);

                if (iss.peek() == '/')
                {
                    iss.ignore();
                    if (iss.peek() != '/')
                    {
                        iss >> tIndex;
                    }
                    iss.ignore();
                    iss >> nIndex;
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
        // Connect the first and last vertices to complete the line strip loop for each face
        const Vertex& firstVertex = vertices[face[0]];
        glVertex3f(firstVertex.x, firstVertex.y, firstVertex.z);
    }
    glEnd();
}

Vertex calculateCenterOfMass() {
    float sumX = 0.0f, sumY = 0.0f, sumZ = 0.0f;
    int numVertices = vertices.size();

    for (const Vertex& vertex : vertices) {
        sumX += vertex.x;
        sumY += vertex.y;
        sumZ += vertex.z;
    }

    float centerX = sumX / numVertices;
    float centerY = sumY / numVertices;
    float centerZ = sumZ / numVertices;

    return Vertex(centerX, centerY, centerZ);
}

void translate(const Vertex& center, float dx, float dy, float dz) {
    for (Vertex& vertex : vertices) {
        vertex.x += dx;
        vertex.y += dy;
        vertex.z += dz;
    }
}

void rotateX(const Vertex& center, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);

    for (Vertex& vertex : vertices) {
        float newY = (vertex.y - center.y) * cosA - (vertex.z - center.z) * sinA + center.y;
        float newZ = (vertex.y - center.y) * sinA + (vertex.z - center.z) * cosA + center.z;
        vertex.y = newY;
        vertex.z = newZ;
    }
}

void rotateY(const Vertex& center, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);

    for (Vertex& vertex : vertices) {
        float newX = (vertex.x - center.x) * cosA + (vertex.z - center.z) * sinA + center.x;
        float newZ = -(vertex.x - center.x) * sinA + (vertex.z - center.z) * cosA + center.z;
        vertex.x = newX;
        vertex.z = newZ;
    }
}

void rotateZ(const Vertex& center, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);

    for (Vertex& vertex : vertices) {
        float newX = (vertex.x - center.x) * cosA - (vertex.y - center.y) * sinA + center.x;
        float newY = (vertex.x - center.x) * sinA + (vertex.y - center.y) * cosA + center.y;
        vertex.x = newX;
        vertex.y = newY;
    }
}

void scale(const Vertex& center, float sx, float sy, float sz) {
    for (Vertex& vertex : vertices) {
        vertex.x = center.x + (vertex.x - center.x) * sx;
        vertex.y = center.y + (vertex.y - center.y) * sy;
        vertex.z = center.z + (vertex.z - center.z) * sz;
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
    Vertex center = calculateCenterOfMass();

    switch (key) {
        // Translação
        case 'x':
            translate(center, -0.1f, 0.0f, 0.0f);
            break;
        case 'X':
            translate(center, 0.1f, 0.0f, 0.0f);
            break;
        case 'y':
            translate(center, 0.0f, -0.1f, 0.0f);
            break;
        case 'Y':
            translate(center, 0.0f, 0.1f, 0.0f);
            break;
        case 'z':
            translate(center, 0.0f, 0.0f, -0.1f);
            break;
        case 'Z':
            translate(center, 0.0f, 0.0f, 0.1f);
            break;
        // Rotação
        case 'r':
            rotateX(center, -0.1f);
            break;
        case 'R':
            rotateX(center, 0.1f);
            break;
        case 'u':
            rotateY(center, -0.1f);
            break;
        case 'U':
            rotateY(center, 0.1f);
            break;
        case 'w':
            rotateZ(center, -0.1f);
            break;
        case 'W':
            rotateZ(center, 0.1f);
            break;
        // Escala
        case 's':
            scale(center, 0.9f, 0.9f, 0.9f);
            break;
        case 'S':
            scale(center, 1.1f, 1.1f, 1.1f);
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

void customKeyboard(unsigned char key, int x, int y) {
    Vertex center = calculateCenterOfMass();

    switch (key) {
        // Translação
        case 'x':
            translate(center, -0.1f, 0.0f, 0.0f);
            break;
        case 'X':
            translate(center, 0.1f, 0.0f, 0.0f);
            break;
        case 'y':
            translate(center, 0.0f, -0.1f, 0.0f);
            break;
        case 'Y':
            translate(center, 0.0f, 0.1f, 0.0f);
            break;
        case 'z':
            translate(center, 0.0f, 0.0f, -0.1f);
            break;
        case 'Z':
            translate(center, 0.0f, 0.0f, 0.1f);
            break;
        // Rotação
        case 'r':
            rotateX(center, -0.1f);
            break;
        case 'R':
            rotateX(center, 0.1f);
            break;
        case 'u':
            rotateY(center, -0.1f);
            break;
        case 'U':
            rotateY(center, 0.1f);
            break;
        case 'w':
            rotateZ(center, -0.1f);
            break;
        case 'W':
            rotateZ(center, 0.1f);
            break;
        // Escala
        case 's':
            scale(center, 0.9f, 0.9f, 0.9f);
            break;
        case 'S':
            scale(center, 1.1f, 1.1f, 1.1f);
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

    switch (selectedColor) {
        case COLOR_RED:
            glColor3f(1.0, 0.0, 0.0);
            break;
        case COLOR_GREEN:
            glColor3f(0.0, 1.0, 0.0);
            break;
        case COLOR_BLUE:
            glColor3f(0.0, 0.0, 1.0);
            break;
        default:
            glColor3f(1.0, 1.0, 1.0);
            break;
    }

    drawObjLineStrip();

    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (GLfloat)width / (GLfloat)height, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void colorMenu(int value) {
    selectedColor = value;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.obj>" << std::endl;
        return 1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OBJETO 3D MENU DE CORES");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(customKeyboard);

    loadObjFile(argv[1]);

    int colorMenuId = glutCreateMenu(colorMenu);
    glutAddMenuEntry("Red", COLOR_RED);
    glutAddMenuEntry("Green", COLOR_GREEN);
    glutAddMenuEntry("Blue", COLOR_BLUE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
