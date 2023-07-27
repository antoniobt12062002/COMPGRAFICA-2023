#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

class Vertice {
public:
    float EixoX, EixoY, EixoZ;

    Vertice() : EixoX(0), EixoY(0), EixoZ(0) {}
    Vertice(float x, float y, float z) : EixoX(x), EixoY(y), EixoZ(z) {}

    void set(const Vertice& v) {
        EixoX = v.EixoX;
        EixoY = v.EixoY;
        EixoZ = v.EixoZ;
    }

    float dot(const Vertice& v) const {
        return EixoX * v.EixoX + EixoY * v.EixoY + EixoZ * v.EixoZ;
    }

    Vertice cross(const Vertice& v) const {
        return Vertice(EixoY * v.EixoZ - EixoZ * v.EixoY,
                       EixoZ * v.EixoX - EixoX * v.EixoZ,
                       EixoX * v.EixoY - EixoY * v.EixoX);
    }

    void normalize() {
        float length = sqrt(EixoX * EixoX + EixoY * EixoY + EixoZ * EixoZ);
        EixoX /= length;
        EixoY /= length;
        EixoZ /= length;
    }
};

class Camera {
private:
    Vertice eye, u, v, n;
    double viewAngle, aspect, nearDist, farDist;

public:
    Camera() {}
    void set(Vertice eye, Vertice look, Vertice up);
    void roll(float angle);
    void pitch(float angle);
    void yaw(float angle);
    void setShape(float vAng, float asp, float nearD, float farD);
    void applyTransformations();
    void ZoomIn(float AnguloMais);
    void ZoomOut(float AnguloMenos);
};

void Camera::setShape(float vAngle, float asp, float nearD, float farD) {
    viewAngle = vAngle;
    aspect = asp;
    nearDist = nearD;
    farDist = farD;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(viewAngle, aspect, nearDist, farDist);
    glMatrixMode(GL_MODELVIEW);
}

void Camera::applyTransformations() {
    float m[16];

    // Column 1
    m[0] = u.EixoX;
    m[1] = v.EixoX;
    m[2] = -n.EixoX;
    m[3] = 0.0f;

    // Column 2
    m[4] = u.EixoY;
    m[5] = v.EixoY;
    m[6] = -n.EixoY;
    m[7] = 0.0f;

    // Column 3
    m[8] = u.EixoZ;
    m[9] = v.EixoZ;
    m[10] = -n.EixoZ;
    m[11] = 0.0f;

    // Column 4
    m[12] = -eye.EixoX * u.EixoX - eye.EixoY * u.EixoY - eye.EixoZ * u.EixoZ;
    m[13] = -eye.EixoX * v.EixoX - eye.EixoY * v.EixoY - eye.EixoZ * v.EixoZ;
    m[14] = eye.EixoX * n.EixoX + eye.EixoY * n.EixoY + eye.EixoZ * n.EixoZ;
    m[15] = 1.0f;

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(m);
}

void Camera::set(Vertice Eye, Vertice Look, Vertice Up) {
    eye.set(Eye);
    n = Vertice(eye.EixoX - Look.EixoX, eye.EixoY - Look.EixoY, eye.EixoZ - Look.EixoZ);
    u = Vertice(Up.cross(n));
    n.normalize();
    u.normalize();
    v = Vertice(n.cross(u));
    applyTransformations();
}

void Camera::roll(float angle) {
    float cs = cos(M_PI / 180 * angle);
    float sn = sin(M_PI / 180 * angle);
    Vertice t = u;
    u = Vertice(cs * t.EixoX - sn * v.EixoX, cs * t.EixoY - sn * v.EixoY,
          cs * t.EixoZ - sn * v.EixoZ);
    v = Vertice(sn * t.EixoX + cs * v.EixoX, sn * t.EixoY + cs * v.EixoY,
          sn * t.EixoZ + cs * v.EixoZ);
    applyTransformations();
}

void Camera::pitch(float angle) {
    float cs = cos(M_PI / 180 * angle);
    float sn = sin(M_PI / 180 * angle);
    Vertice t = v;
    v = Vertice(cs * t.EixoX - sn * n.EixoX, cs * t.EixoY - sn * n.EixoY,
          cs * t.EixoZ - sn * n.EixoZ);
    n = Vertice(sn * t.EixoX + cs * n.EixoX, sn * t.EixoY + cs * n.EixoY,
          sn * t.EixoZ + cs * n.EixoZ);
    applyTransformations();
}

void Camera::yaw(float angle) {
    float cs = cos(M_PI / 180 * angle);
    float sn = sin(M_PI / 180 * angle);
    Vertice t = n;
    n = Vertice(cs * t.EixoX - sn * u.EixoX, cs * t.EixoY - sn * u.EixoY,
          cs * t.EixoZ - sn * u.EixoZ);
    u = Vertice(sn * t.EixoX + cs * u.EixoX, sn * t.EixoY + cs * u.EixoY,
          sn * t.EixoZ + cs * u.EixoZ);
    applyTransformations();
}

void Camera::ZoomIn(float AnguloMenos) {
    viewAngle -= AnguloMenos;
    setShape(viewAngle, aspect, nearDist, farDist);
}

void Camera::ZoomOut(float AnguloMais) {
    viewAngle += AnguloMais;
    setShape(viewAngle, aspect, nearDist, farDist);
}

// Código do objeto 3D

struct Vertex {
    float x, y, z;
    Vertex(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct Normal {
    float x, y, z;
    Normal(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct TextureCoord {
    float u, v;
    TextureCoord(float u, float v) : u(u), v(v) {}
};

std::vector<Vertex> vertices;
std::vector<Normal> normals;
std::vector<TextureCoord> texCoords;
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
        } else if (line.substr(0, 3) == "vn ") {
            float x, y, z;
            iss >> trash >> trash >> x >> y >> z;
            normals.push_back(Normal(x, y, z));
        } else if (line.substr(0, 3) == "vt ") {
            float u, v;
            iss >> trash >> trash >> u >> v;
            texCoords.push_back(TextureCoord(u, v));
        } else if (line.substr(0, 2) == "f ") {
            std::vector<int> faceIndices;
            int vIndex, vtIndex, vnIndex;
            iss >> trash;

            while (iss >> vIndex) {
                faceIndices.push_back(vIndex - 1); // OBJ indices start at 1

                if (iss.peek() == '/') {
                    iss.ignore();
                    if (iss.peek() != '/') {
                        iss >> vtIndex;
                        texCoords[vIndex - 1] = texCoords[vtIndex - 1];
                    }

                    iss.ignore();
                    iss >> vnIndex;
                    normals[vIndex - 1] = normals[vnIndex - 1];
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

// Variável da câmera
Camera camera;

// Função de callback para controle das transformações da câmera via teclado
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Rotação da câmera
        case 'r':
            camera.roll(-1.0f);
            break;
        case 'R':
            camera.roll(1.0f);
            break;
        case 'u':
            camera.pitch(-1.0f);
            break;
        case 'U':
            camera.pitch(1.0f);
            break;
        case 'w':
            camera.yaw(-1.0f);
            break;
        case 'W':
            camera.yaw(1.0f);
            break;
        // Zoom da câmera
        case 'i': // Tecla 'i' para ZoomIn
            camera.ZoomIn(1.0f); // Pode ajustar o valor do ângulo para um zoom mais rápido ou lento
            break;
        case 'o': // Tecla 'o' para ZoomOut
            camera.ZoomOut(1.0f); // Pode ajustar o valor do ângulo para um zoom mais rápido ou lento
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    camera.applyTransformations(); // Usar a função applyTransformations()

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

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.obj>" << std::endl;
        return 1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Cubo!");
    glOrtho(-100, 100, -100, 100, -10, 10);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    loadObjFile(argv[1]);

    glEnable(GL_DEPTH_TEST);
    camera.setShape(180, 1.7, 1, 100);
    Vertice v1(0, 0, 30); // Posição da câmera (x, y, z)
    Vertice v2(0, 0, 0); // Ponto de interesse para onde a câmera está olhando (x, y, z)
    Vertice v3(0, 1, 0); // Vetor "up" da câmera (x, y, z)
    camera.set(v1, v2, v3);
    glutMainLoop();
    return 0;
}   
