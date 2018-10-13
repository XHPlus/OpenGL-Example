#include <GL/glut.h>
#include <iostream>

#define WIDTH 600
#define HEIGHT 480
#define MAX_POINT_NUM 48

using namespace std;

class Point
{
    public:
        Point() {}
        Point(int _x, int _y, int _inited = true)
        {
            this->x = _x;
            this->y = HEIGHT - _y;
            this->inited = _inited;
        }
        int x, y;
        bool inited = false;
        void set(int _x, int _y)
        {
            this->x = _x;
            this->y = HEIGHT - _y;
        }
        void init(int _x, int _y)
        {
            this->x = _x;
            this->y = HEIGHT - _y;
            this->inited = true;
        }
        void deinit()
        {
            this->inited = false;
        }
        int getx()
        {
            return x;
        }
        int gety()
        {
            return y;
        }
};

Point point[MAX_POINT_NUM];
int point_num;

void draw_line(Point p1, Point p2)
{
    glColor3f(1.0,0.0,0.0);
    glPointSize(2.0);
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        point[point_num++].init(x, y);
    }
}

void mouse_move(int x, int y)
{
    if (point_num > 0 && point_num % 2 == 1) {
        glClear(GL_COLOR_BUFFER_BIT);
        Point tmp(x, y, true);
        for (int i = 1; i < point_num; i += 2) {
            draw_line(point[i - 1], point[i]);
        }
        draw_line(point[point_num - 1], tmp);
    }
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0);
    // glColor3f(1.0,1.0,1.0);
    // glPointSize(2.0);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
    // glShadeModel(GL_FLAT);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'q':
            exit(0);
            break;
        case 'c':
            point_num = 0;
            glClear(GL_COLOR_BUFFER_BIT);
            glFlush();
            break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("LINE");
    init();
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(mouse_move);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
