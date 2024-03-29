#include <GL/glut.h>
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

Camera camera;

float posicaluz[4]={15.0,10.0,25.0,15.0};
bool luzativa = true;

void Iniciarluzes(){
    float luzAmbiente[4]={0.50,0.50,0.50,10.0};
    float luzDifusa[4]={1.0,14.0,0,10.0};
    float especularidade[4]={1.0,1.0,1.0,1.0};

    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    glMateriali(GL_FRONT, GL_SHININESS, 10);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaluz);


    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
}

// Função de callback para controle das transformações da câmera via teclado
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
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
        case 'i':
            camera.ZoomIn(1.0f);
            break;
        case 'o':
            camera.ZoomOut(1.0f);
            break;
        case 'x':
            posicaluz[0] -=1;      
            break;
        case 'y':
            posicaluz[1] -=1;      
            break;
        case 'X':
            posicaluz[0] +=1;      
            break;
        case 'Y':
            posicaluz[1] +=1;      
            break;
        case 'q':
            luzativa = !luzativa;
            if (luzativa){
                glEnable(GL_LIGHT0);
            }else{
                glDisable(GL_LIGHT0);
            }
        default:
            break;
    }
    glLightfv(GL_LIGHT0, GL_POSITION, posicaluz);
    glutPostRedisplay();
}
class Tree {
public:
    void draw() {
        glColor3f(0.4, 0.2, 0.0); 
        glPushMatrix();
        glRotatef(-90, 1.0, 0.0, 0.0); 
        glutSolidCone(0.5, 5.0, 8, 8);
        glPopMatrix();
        glColor3f(0.0, 0.6, 0.0); 
        glPushMatrix();
        glTranslatef(0.0, 5.0, 0.0); 
        glutSolidSphere(2.5, 16, 16);
        glPopMatrix();
    }
};

Tree tree; 

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.applyTransformations();    

    glColor3f(1.0, 0.0, 0.0);

    glTranslatef(0, 0, 0);
    glutSolidCube(2.0);

    glPushMatrix();
    glTranslatef(3.0, 0.0, 0.0); 
    tree.draw();

    glTranslatef(1.0, 0.0, 6.0); 
    glColor3f(0.0, 0.0, 1.0);
    glutSolidTeapot(2.0);
  
     
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

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glOrtho(-100, 100, -100, 100, -10, 10);
    glutCreateWindow("MANIPULACAO DE LUZES");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    Iniciarluzes();


    glEnable(GL_DEPTH_TEST);
    camera.setShape(45, 1, 1.05, 500); 
    Vertice v1(-5.5, -5, 10); // Posição da câmera (x, y, z) - agora está fora do cubo
    Vertice v2(0, 0, 0); // Ponto de interesse para onde a câmera está olhando (x, y, z) - apontando para o centro do cubo
    Vertice v3(0, 1, 0); // Vetor "up" da câmera (x, y, z)
    camera.set(v1, v2, v3);
    glutMainLoop();
    return 0;
}
