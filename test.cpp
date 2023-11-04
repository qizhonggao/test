#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#define MAX_CHAR 128
#include <vector>
float scale = 1;//定义放缩初始值
float scale1 = 1;//view
const float MAX_SCALE = 15.0f;//限制其最大倍数
GLfloat fwStart = -450, fwStartSize = 3, fwSStep = 0, fwSSStep = 0;
GLfloat size;
GLfloat starRotate = 0, starRotateStep = 0.03;
GLfloat Color = 1;
float angle = 0;
const float MAX_angle = 45;
float x = 0;
float y = 0;
float translation = 0.0f;  // 初始平移距离
float transformation = 0.0f;//cloud 平移
bool scaleDone = false;  // 放大动画是否完成的标志
bool rotationDone = false;  // 旋转动画是否完成的标志
bool translationDone = false;  // 平移动画是否完成的标志
bool next = false;
bool drawFirework = false;
typedef struct { GLfloat x1, y1; } point; // define a 2D point
point p0 = { 50,150 }; // set initial co-ordinate values of the point
GLfloat step1 = 1; // declare step
float r = 1;

// movement of the balloon
GLfloat speed = 0.0001;
int time_interval = 100; // increase refresh interval for smoother motion
GLfloat step = speed * time_interval; // decrease incremental step for smoother motion
bool draw_balloon = false; // 鼠标点击，draw_balloon = 1

void when_in_mainloop() { // idle callback function

    glutPostRedisplay(); // force OpenGL to redraw the current window
}

void OnTimer(int value) {
    p0.y1 += step;
    if (p0.y1 >= 600) // Adjusted upper bound to 375
        p0.y1 = 0;
    else if (p0.y1 <= 0)
        p0.y1 = 599;
    r += step1;
    if (r >= 360)
        r = 0;
    else if (r <= 0)
        r = 359;
    glutTimerFunc(time_interval, OnTimer, 1);
}
void keyboard_input1(unsigned char key, int x, int y) {
    if (key == 'q' || key == 'Q')
        exit(0);
    else if (key == 'l' || key == 'L') // speed goes down

        step -= 0.001;
    else if (key == 'u' || key == 'U') // speed goes up
        step += 0.001;
    if (key == 'r' || key == 'R') // move the viewport to the right
        next = true;
    if (key == 's' || key == 'S') // move the viewport down
        drawFirework = !drawFirework;
}
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        draw_balloon = !draw_balloon;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        draw_balloon = !draw_balloon;
        std::cout << "drawBalloon" << std::endl;

    }
}
//std::vector<std::pair<float, float>> controlPoints; // 曲线的控制点
void drawBalloon(void) {
    //  
    glPushMatrix();
    glOrtho(0, 800, 0, 600, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



    glColor3f(1.0, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.14159 / 180;
        float x1 = p0.x1 + 20 * cos(theta);
        float y1 = p0.y1 + 30 * sin(theta);
        glVertex2f(x1, y1);
    }


    glEnd();
    // Draw the wavy string
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);

    glVertex2f(p0.x1, p0.y1 - 30);

    for (float y1 = p0.y1 - 30; y1 < p0.y1 - 65; y1 = y1 - 0.1) {

        float x1 = p0.x1;
        glVertex2f(x1, y1);
    }
    glVertex2f(50, p0.y1 - 100);
    glEnd();

    glPopMatrix();

    //glutTimerFunc(time_interval, OnTimer, 1);

}


void drawSun(float x, float y) {

    glPushMatrix();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.0, 0.0); // 设置圆心的颜色，这里是red色
    glVertex2f(x, y); // 圆心
    glColor3f(255, 215, 0);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159265 / 180;
        float x1 = 0.008 * cos(angle); // x坐标
        float y1 = 0.008 * sin(angle); // y坐标，50为y轴半径，100为x轴半径

        //// 应用波浪形状，这里使用正弦函数
        glVertex2f(x + x1, y + y1);
    }
    glEnd();
    glPopMatrix();
}


void picture(void) {
    glBegin(GL_POLYGON);
    glColor3f(0.72, 0.81, 0.6);
    glBegin(GL_POLYGON);
    glVertex2f(-0.03, -0.027);
    glVertex2f(0, -0.029);
    glVertex2f(0, 0.037);
    glVertex2f(-0.03, 0.033);
    glEnd();

    glColor3f(0.05, 0.3, 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(0, -0.029);
    glVertex2f(0.02, -0.027);
    glVertex2f(0.02, 0.033);
    glVertex2f(0, 0.037);
    glEnd();


    //镂空
    glColor3f(250, 0.7, 250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.018, 0.026);
    glVertex2f(-0.011, 0.025 + 0.007 / 15);
    glVertex2f(-0.01, 0.035 - 0.01 / 20);
    glVertex2f(-0.02, 0.033 + 0.01 / 17);
    glEnd();
    glColor3f(250, 0.7, 250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.03, -0.015);
    glVertex2f(-0.028, -0.012);
    glVertex2f(-0.028, 0);
    glVertex2f(-0.03, 0.002);
    glEnd();
    glColor3f(250, 0.7, 250);
    glBegin(GL_POLYGON);
    glVertex2f(-0.026, -0.015);
    glVertex2f(-0.021, -0.015);
    glVertex2f(-0.018, -0.01);
    glVertex2f(0, -0.006);
    glVertex2f(0, 0.006);
    glVertex2f(-0.005, 0.0);
    glVertex2f(-0.026, 0.0);
    glEnd();
    glColor3f(250, 0.4, 250);
    glBegin(GL_POLYGON);
    glVertex2f(0, -0.006);
    glVertex2f(0.008, -0.006);
    glVertex2f(0.02, -0.02);
    glVertex2f(0.02, -0.003);
    glVertex2f(0.015, -0.004);
    glVertex2f(0.015, 0.0342);
    glVertex2f(0.01, 0.0347);
    glVertex2f(0.008, 0.006);
    glVertex2f(0, 0.006);
    glEnd();

}

//drawcloud
void drawwhitecicle(float x, float y) {

    glColor3f(1.0, 1.0, 1.0); // 设置颜色为白色
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x, y); // 圆心

    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159265 / 180;
        float x1 = 0.006 * cos(angle); // x坐标
        float y1 = 0.006 * sin(angle); // y坐标，50为y轴半径，100为x轴半径

        glVertex2f(x + x1, y + y1);
    }
    glEnd();
}
//创建云朵样子
void drawCloud(float x, float y) {
    drawwhitecicle(x, y);
    drawwhitecicle(x - 0.004, y);
    drawwhitecicle(x + 0.004, y);
}


//风车
void flow(void) {
    glPushMatrix();
    glTranslatef(0.04, 0, 0);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(0, -0.02);
    glVertex2f(0, 0);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.04, 0, 0);
    glRotatef(r, 0, 0, 1);
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 0);
    glVertex2f(0.005, 0.0025);
    glVertex2f(0.003, 0.0075);
    glEnd();
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 0);
    glVertex2f(0.005, 0.0025);
    glVertex2f(0.003, 0.0075);

    glEnd();
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 0);
    glVertex2f(0.005, 0.0025);
    glVertex2f(0.003, 0.0075);
    glEnd();
    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 0);
    glVertex2f(0.005, 0.0025);
    glVertex2f(0.003, 0.0075);
    glEnd();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glutIdleFunc(when_in_mainloop);
    glutTimerFunc(time_interval, OnTimer, 1);
}


//cardExpand

void card(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPushMatrix();
    glScalef(scale, scale, 1);
    glBegin(GL_POLYGON);
    glColor3f(0, 1, 0);
    glVertex2f(-0.05, -0.05);
    glColor3f(0, 1, 0);
    glVertex2f(0.05, -0.05);
    glColor3f(0, 1, 1);
    glVertex2f(0.05, 0.05);
    glColor3f(0, 1, 1);
    glVertex2f(-0.05, 0.05);
    glEnd();
    picture();
    drawSun(-0.04, 0.04);
    drawCloud(0.02, 0.04);
    flow();
    glPopMatrix();

    glColor3f(1.0, 0.0f, 0.0f); // Set text color to black
    glRasterPos2f(0.3, 0.36); // Set position for text
    // The text to be rendered
    const char* text = "XJTLU TO DREAM";
    // Loop through the characters in the text and render them one by one
    for (int i = 0; text[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

}

//String congrtulation and balloon
void congratulate(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f); // Set text color to black
    glRasterPos2f(-0.4, 0.8); // Set position for text
    // The text to be rendered
    const char* text = "CONGRATULATIONS!!!";
    // Loop through the characters in the text and render them one by one
    for (int i = 0; text[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
    glRasterPos2f(0.6, 0.75); // Set position for text
    // The text to be rendered
    const char* text1 = "------for 2024";
    // Loop through the characters in the text and render them one by one
    for (int i = 0; text[i] != '\0'; ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, text1[i]);
    }

}

void envelop(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(x + translation, y + translation, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glScalef(scale, scale, 1.0f);
    glTranslatef(-x, -y, 0.0f);
    glColor3f(0.91, 0.78, 0.6);
    glBegin(GL_POLYGON);

    glVertex2f(-0.05, -0.05);

    glVertex2f(0.05, -0.05);

    glVertex2f(0.05, 0.05);

    glVertex2f(-0.05, 0.05);
    glEnd();
    glPopMatrix();
}
void update(int value) {
    if (scale <= MAX_SCALE) {
        scale += 0.005;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}
//viewupdate
void viewupdate(int value) {
    if (scale1 >= 0.5) {
        scale1 -= 0.01;
    }
    glutPostRedisplay();
    glutTimerFunc(16, viewupdate, 0);
}
void animate(int value) {
    if (!scaleDone) {
        scale += 0.005f;  // 增加放大倍数
        if (scale >= 15.0f) {
            scale = 15.0f;  // 达到最大放大倍数时，标记为完成
            scaleDone = true;
        }
    }
    else if (!rotationDone) {
        angle += 0.001f;  // 增加旋转角度
        if (angle >= MAX_angle) {
            angle = 45.0f;  // 达到最大旋转角度时，标记为完成
            rotationDone = true;
        }
    }
    else if (!translationDone) {
        translation -= 0.0001f;  // 减小平移距离
        if (y <= -1.0f) {
            y = -1.0f;  // 达到最大平移距离时，标记为完成
            translationDone = true;
        }
    }

    glutPostRedisplay();  // 重新渲染画面

    if (!(scaleDone && rotationDone && translationDone)) {
        // 设置下一帧的更新
        glutTimerFunc(16, animate, 0);
    }
}
// to select a font
void selectFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

void GL_FIREWORK(float x, float y)
{
   // std::cout << "firework0" << std::endl;
    // 烟花起始火焰
    float size = 4;
    glColor3f(0.7, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y - 50 + fwStart);
    glColor3f(0.8, 0.5, 0);
    for (int i = 0; i <= 20; i++)
        glVertex2f(x + fwStartSize * cos(2 * 3.1415 / 15 * i), y + fwStart + fwStartSize * 4 / 3 * sin(2 * 3.1415 / 15 * i));
    glEnd();
    //std::cout << "firework1" << std::endl;
    // 烟花中的火焰星星
    for (float i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(1, 1.333, 0);
        glRotatef(i * 72, 0, 0, 1);
        glScalef(1, 0.75, 0);
        glTranslatef(-x, -y, 0);
        glColor3f(1, 0.93, 0.6);
        glBegin(GL_TRIANGLES);
        glVertex2f(x, y);
        glColor3f(0.72, 0.6, 0);
        glVertex2f(x + 2 * size, y);
        glVertex2f(x, y + 20 * size);
        glEnd();
        glPopMatrix();
    }
    // 烟花爆炸后的火焰
    for (float i = 0; i < 18; i++) {
        glPushMatrix();
        glTranslatef(x, y, 0);
        glScalef(1, 1.333, 0);
        glRotatef(i * 20, 0, 0, 1);
        glScalef(1, 0.75, 0);
        glTranslatef(-x, -y, 0);
        glColor3f(1, 0, 0);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x + 3 * size + 2 * size * sin(i * 2), y);
        glColor3f(1, 0.8, 0);
        for (int j = 0; j <= 20; j++)
            glVertex2f(x + 20 * size + 2 * size * (sin(i * 3) + cos(i * 3)), y + 4 / 3 * size * sin(2 * 3.1415 / 15 * j));
        glEnd();
        glPopMatrix();
    }

}

void renderScence(void) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor(0.1, 0.1, 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    congratulate();
    card();
    glutTimerFunc(0, update, 0);
    envelop();
    glutTimerFunc(0, animate, 0);
    if (draw_balloon) {
        drawBalloon();
        
    }
    if (next) {
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glScalef(scale1, scale1, scale1);
        glutTimerFunc(0, viewupdate, 0);
        selectFont(256, ANSI_CHARSET, "Times New Roman");

        glColor3f(Color, Color, Color + 0.08);
        glRasterPos2f(277, 265);
        for (const char* c = "DREAM TO DREAM ! CONGRATULATION"; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        }
        
        if (drawFirework) {
            GL_FIREWORK(150, 350);
            GL_FIREWORK(400, 350);
            GL_FIREWORK(1200, 350);
            GL_FIREWORK(1400, 350);
            std::cout << "1" << std::endl;
        }
    }
    
    glutSwapBuffers();
}
int main(int argc, char* argv[]) {
    glutInit(&argc, (char**)argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("2024 XJTLU Graduation Ceremony");
    glutKeyboardFunc(keyboard_input1);
    glutMouseFunc(mouse);
    glutDisplayFunc(renderScence);
    glutMainLoop();
}