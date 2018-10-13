#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define WIDTH 600
#define HEIGHT 480
#define MAX_POINT_NUM 48
#define SMOOTH 0.005

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
int point_num = 0;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
}

void draw_point(Point point)
{
}

void draw_line(Point p1, Point p2, float r, float g, float b)
{
    glColor3f(r, g, b);
    glPointSize(2.0);
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
    glFlush();
    // glutSwapBuffers();
}
long factorial(long number)
{
    if (number <= 1)
        return 1;
	else
		return number * factorial(number - 1);
}

int c_n_k(int n, int k)
{
    return factorial(n) / (factorial(k) * factorial(n - k));
}

Point bezier_point(Point point[], int point_num, double t)
{
    Point p(0, 0, true);
    double x = 0, y = 0;
    for (int i = 0; i < point_num; i++) {
        x += c_n_k(point_num - 1, i) * pow(1 - t, point_num - 1 - i) * pow(t, i) * point[i].x;
        y += c_n_k(point_num - 1, i) * pow(1 - t, point_num - 1 - i) * pow(t, i) * point[i].y;
        // cout << point_num << " " << i << " " << c_n_k(point_num, i) << "   ";
    }
    cout << endl;
    p.x = x;
    p.y = y;
    return p;
}

void mouse_click(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        cout << "mouse left btn click" << endl;
        point[point_num++].init(x, y);
    } else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        cout << "mouse right btn click" << endl;
        glClear(GL_COLOR_BUFFER_BIT);
        for (int i = 1; i < point_num; i++) {
            draw_line(point[i - 1], point[i], 1.0, 0.0, 0.0);
        }
        Point p_current = point[0];
        if (point_num >= 3) {
            for (double t = 0.0; t < 1.0; t += SMOOTH) {
                Point p = bezier_point(point, point_num, t);
                draw_line(p_current, p, 0.0, 1.0, 0.0);
                p_current = p;
            }
        }
        point_num = 0;
    }
}

void mouse_move(int x, int y)
{
    static int cnt = 0;
    cout << "move to " << x << ", " << y << endl;
    glClear(GL_COLOR_BUFFER_BIT);
    if (point_num > 0) {
        Point tmp(x, y, true);
        for (int i = 1; i < point_num; i++) {
            draw_line(point[i - 1], point[i], 1.0, 0.0, 0.0);
        }
        draw_line(point[point_num - 1], tmp, 1.0, 0.0, 0.0); 
        Point p_current = point[0];
        point[point_num++] = tmp;
        if (point_num >= 3) {
            for (double t = 0.0; t < 1.0; t += SMOOTH) {
                Point p = bezier_point(point, point_num, t);
                draw_line(p_current, p, 0.0, 1.0, 0.0);
                p_current = p;
            }
        }
        point_num--;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'q':
            exit(0);
            break;
        case 'c':
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
    glutCreateWindow("BEZIER");
    init();
    glutMouseFunc(mouse_click);
    glutPassiveMotionFunc(mouse_move);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
