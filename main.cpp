#include<iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <cmath>
#include<mmsystem.h>

using namespace std;

float obj_cloud1 = 0;
float obj_cloud2 = 0;
float obj_water = 0;
float obj_waterSpeed = 0.0002;
float obj_boat1 = 0;
float obj_boat2 = 0;
float obj_ship = 0;
float obj_shipSpeed = 0.002;
float obj_elevator = 0;
float obj_elevatorX = 0;
float obj_human = 0;
float obj_bus1 = 0;
float wheelAngle_bus1 = 0;
float obj_car1 = 0;
float wheelAngle_car1 = 0;
float obj_cableCar = 0;
float cableCar_Speed= 0.06;
float obj_cableCarX = 0;
float cableCarX_Speed= 0.06;
float obj_tunnelCar1 = 0;
float wheelAngle_tunnelCar1 = 0;
float obj_tunnelBus1 = 0;
float wheelAngle_tunnelBus1 = 0;
float obj_tunnelCar2 = 0;
float wheelAngle_tunnelCar2 = 0;
float obj_tunnelBus2 = 0;
float wheelAngle_tunnelBus2 = 0;
float obj_car2 = 0;
float wheelAngle_car2 = 0;
float obj_bus2 = 0;
float wheelAngle_bus2 = 0;
float obj_train = 0;

bool day = true;
bool scene1 = true;
bool shipForward = false;
bool shipBackward = false;
bool sound = true;
float rain = 0;
bool rainyDay = false;
bool snow = false;

void lineCircle(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_LINES);
    glLineWidth(8);
    for(int i=0;i<200;i++)
        {
            glColor3ub(r,g,b);
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=radius;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x+xc,y+yc);
        }
    glEnd();
}

void fillCircle(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0;i<200;i++)
        {
            glColor3ub(r,g,b);
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=radius;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x+xc,y+yc);
        }
    glEnd();
}

void DrawEllipse(float cx, float cy, float rx, float ry, int num_segments)
{
    float A = 2 * 3.1415926 / float(num_segments);
    float c = cos(A);//precalculate the sine and cosine
    float s = sin(A);
    float t;

    float x = 1;//we start at angle = 0
    float y = 0;

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    for(int i = 0; i< num_segments; i++)
    {
        //apply radius and offset
        glVertex2f(x * rx + cx, y * ry + cy);//output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

void circle(float r, float x, float y)
{
    glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
        {
            glColor3ub(90, 90, 90);
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y);
        }
        glEnd();
}

void drawWheel(float x, float y, float angle)
{
    glPushMatrix();///Save the current transformation matrix
    glTranslatef(x,y,0);///Translate to the specified (x, y) position
    float r = 0.1598;
    circle(r,x,y);
    glRotatef(angle,0,0,1);///Rotate the wheel by the specified angle around the z-axis

    ///Lines inside the wheel
    glBegin(GL_LINES);
    glColor3ub(192, 192, 192);
    glLineWidth(7);
    glVertex2f(-0.1598, 0);
    glVertex2f(0.1598, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(192, 192, 192);
    glLineWidth(7);
    glVertex2f(0, 0.1598);
    glVertex2f(0, -0.1598);
    glEnd();

    glPopMatrix();///Restore the previous transformation matrix
}

void sky()
{
    glBegin(GL_POLYGON);
    if(day)
    {
       glColor3ub(72,190,255);
    }
    else
    {
        if(scene1)
        {
            glColor3ub(11,33,67);
            ///glColor3ub(37,53,105);
        }
        else
        {
            glColor3ub(206,178,208);
        }
    }
    glVertex2f(0, 6.7870);
    glVertex2f(30, 6.7870);
    if(day)
    {
        glColor3ub(93,111,135);
    }
    else
    {
        glColor3ub(45,58,67);
    }
    glVertex2f(30, 15);
    glVertex2f(0, 15);
    glEnd();
}

void sun()
{
    fillCircle(0.4498,10.9974, 12.0000, 255,252,146);
}

void moon()
{
    fillCircle(0.4498,10.9974, 12.7672, 225,223,177);
}

void stars()
{
    srand(0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(1.2);
    glBegin(GL_POINTS);
    for (int i = 0; i <300; ++i)
        {
        float x = rand() % 30;
        float y = rand() % 15;
        glVertex2f(x, y);
    }
    glEnd();

}

void cloud()
{
    glPushMatrix();
    glTranslatef(obj_cloud1, 0, 0);

    glBegin(GL_POLYGON);
    glColor3ub(208,226,237);
    glVertex2f(11.25, 12.1200);
    glVertex2f(11.25, 12.3000);
    glVertex2f(13.4, 12.3000);
    glVertex2f(13.4, 12.1200);
    glEnd();

    fillCircle(0.4, 11.42, 12.515, 208, 226, 237);
    fillCircle(0.5, 12, 12.6700, 208,226,237);
    fillCircle(0.65, 12.6, 12.9200, 208,226,237);
    fillCircle(0.5, 13.2400, 12.6160, 208,226,237);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(obj_cloud2, 0, 0);

    glBegin(GL_POLYGON);
    glColor3ub(208,226,237);
    glVertex2f(26.25, 12.1200);
    glVertex2f(26.25, 12.3000);
    glVertex2f(28.4, 12.3000);
    glVertex2f(28.4, 12.1200);
    glEnd();

    fillCircle(0.4, 26.42, 12.515, 208, 226, 237);
    fillCircle(0.5, 27, 12.6700, 208,226,237);
    fillCircle(0.65, 27.6, 12.9200, 208,226,237);
    fillCircle(0.5, 28.2400, 12.6160, 208,226,237);

    glPopMatrix();
}
void moveCloud(int value)
{
    obj_cloud1-= 0.004;
    if(obj_cloud1<-14)
    {
        obj_cloud1 = 19;
    }

    obj_cloud2-= 0.004;
    if(obj_cloud2<-30)
    {
        obj_cloud2 = 6;
    }

    glutPostRedisplay();
    glutTimerFunc(10, moveCloud, 0);
}

void grass1()
{
    glBegin(GL_POLYGON);
    if(day)
    {
        glColor3ub(68, 163, 24);
    }
    else
    {
        glColor3ub(66,122,107);
    }
    glVertex2f(0, 6.8800);
    glVertex2f(0, 6.7870);
    glVertex2f(30, 6.7870);
    glVertex2f(30, 6.8800);
    glEnd();

    glBegin(GL_POLYGON);
    if(day)
    {
        glColor3ub(68, 163, 24);
    }
    else
    {
        glColor3ub(66,122,107);
    }
    glVertex2f(0, 0.6012);
    glVertex2f(0, 0);
    glVertex2f(30, 0);
    glVertex2f(30, 0.6012);
    glEnd();
}

void building1()
{
    ///roof
    glBegin(GL_POLYGON);
    glColor3ub(129, 87, 144);
    glVertex2f(3.1331, 10.5145);
    glVertex2f(4.1499, 10.5145);
    glVertex2f(4.1499, 10.7134);
    glVertex2f(3.1329, 10.7134);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(205,194,245);
    glVertex2f(3.1331, 10.5145);
    glVertex2f(4.1499, 10.5145);
    glVertex2f(4.1499, 10.5145);
    glVertex2f(4.1499, 10.7134);
    glVertex2f(4.1499, 10.7134);
    glVertex2f(3.1329, 10.7134);
    glVertex2f(3.1329, 10.7134);
    glVertex2f(3.1331, 10.5145);
    glEnd();

    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(129, 87, 144);
    glVertex2f(2.8108, 10.5145);
    glVertex2f(4.4225, 10.5145);
    glVertex2f(4.4225 , 8.6004);
    glVertex2f(2.8108, 8.6004);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(205,194,245);
    glVertex2f(2.8108, 10.5145);
    glVertex2f(4.4225, 10.5145);
    glVertex2f(4.4225, 10.5145);
    glVertex2f(4.4225 , 8.6004);
    glVertex2f(4.4225 , 8.6004);
    glVertex2f(2.8108, 8.6004);
    glVertex2f(2.8108, 8.6004);
    glVertex2f(2.8108, 10.5145);
    glEnd();

    ///Windows
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(3.1331, 10.3285);
    glVertex2f(3.4905, 10.3285);
    glVertex2f(3.4905, 10.0565 );
    glVertex2f(3.1331, 10.0565);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(3.7898, 10.0565);
    glVertex2f(4.1471, 10.0565);
    glVertex2f(4.1471, 10.3285);
    glVertex2f(3.7898, 10.3285);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(3.1331, 9.6546);
    glVertex2f(3.4905, 9.6546);
    glVertex2f(3.4905, 9.9266);
    glVertex2f(3.1331, 9.9266 );
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(3.7898, 9.9266);
    glVertex2f(4.1471, 9.9266);
    glVertex2f(4.1471, 9.6546);
    glVertex2f(3.7898, 9.6546);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(3.1331, 9.5060);
    glVertex2f(3.4905, 9.5060);
    glVertex2f(3.4905, 9.2340);
    glVertex2f(3.1331, 9.2340);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(3.7898, 9.5060);
    glVertex2f(4.1471, 9.5060);
    glVertex2f(4.1471, 9.2340);
    glVertex2f(3.7898, 9.2340);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(3.1331, 9.0947);
    glVertex2f(3.4905, 9.0947);
    glVertex2f(3.4905, 8.8227);
    glVertex2f(3.1331, 8.8227);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(3.7898, 9.0947);
    glVertex2f(4.1471, 9.0947);
    glVertex2f(4.1471, 8.8227);
    glVertex2f(3.7898, 8.8227);
    glEnd();
}

void building2()
{
    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(117,134,165);
    glVertex2f(2.1603, 8.6004);
    glVertex2f(4.7179, 8.6004);
    glVertex2f(4.7213, 6.7870);
    glVertex2f(2.1630, 6.7870);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(205,194,245);
    glVertex2f(2.1603, 8.6004);
    glVertex2f(4.7179, 8.6004);
    glVertex2f(4.7179, 8.6004);
    glVertex2f(4.7213, 6.7870);
    glVertex2f(4.7213, 6.7870);
    glVertex2f(2.1630, 6.7870);
    glVertex2f(2.1630, 6.7870);
    glVertex2f(2.1603, 8.6004);
    glEnd();

    ///Glass
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(207,255,249);
    glVertex2f(2.2313, 8.0650);
    glVertex2f(4.7213, 8.0650);
    glVertex2f(4.7213, 8.4812);
    glVertex2f(2.2313, 8.4812);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(205,194,245);
    glVertex2f(4.7213, 8.4812);
    glVertex2f(2.2313, 8.4812);
    glVertex2f(2.2313, 8.4812);
    glVertex2f(2.2313, 8.0650);
    glVertex2f(2.2313, 8.0650);
    glVertex2f(4.7213, 8.0650);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(207,255,249);
    glVertex2f(2.2313, 7.4630);
    glVertex2f(4.7213, 7.4630);
    glVertex2f(4.7213, 7.8792);
    glVertex2f(2.2313, 7.8792);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(205,194,245);
    glVertex2f(4.7213, 7.8792);
    glVertex2f(2.2313, 7.8792);
    glVertex2f(2.2313, 7.8792);
    glVertex2f(2.2313, 7.4630);
    glVertex2f(2.2313, 7.4630);
    glVertex2f(2.2313, 7.8792);
    glEnd();

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(207,255,249);
    glVertex2f(2.2313, 6.8778);
    glVertex2f(4.7213, 6.8778);
    glVertex2f(4.7213, 7.2940);
    glVertex2f(2.2313, 7.2940);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(205,194,245);
    glVertex2f(4.7213, 7.2940);
    glVertex2f(2.2313, 7.2940);
    glVertex2f(2.2313, 7.2940);
    glVertex2f(2.2313, 6.8778);
    glVertex2f(2.2313, 6.8778);
    glVertex2f(4.7213, 6.8778);
    glEnd();

    ///Mid lines
    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(205,194,245);
    glVertex2f(2.1613, 7.9702);
    glVertex2f(4.7191, 7.9702);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(205,194,245);
    glVertex2f(2.1613, 7.3815);
    glVertex2f(4.7191, 7.3815);
    glEnd();

    ///Lines
    /*glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(185, 156, 199);
    glVertex2f(2.5080, 8.0650);
    glVertex2f(2.5080, 8.4812);
    glEnd();*/
}

void building3()
{
    ///top
    glBegin(GL_POLYGON);
    glColor3ub(88,60,84);
    glVertex2f(6.9220, 10.6817);
    glVertex2f(7.6293, 10.6817);
    glVertex2f(7.6293, 10.4952);
    glVertex2f(6.9220, 10.4952);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(232,203,224);
    glVertex2f(6.9220, 10.6817);
    glVertex2f(7.6293, 10.6817);
    glVertex2f(7.6293, 10.6817);
    glVertex2f(7.6293, 10.4952);
    glVertex2f(7.6293, 10.4952);
    glVertex2f(6.9220, 10.4952);
    glEnd();

    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(88,60,84);
    glVertex2f(6.9220, 10.4952);
    glVertex2f(9.5307, 10.4949);
    glVertex2f(9.5307, 6.7870);
    glVertex2f(6.9220, 6.7870);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(232,203,224);
    glVertex2f(6.9220, 10.4952);
    glVertex2f(9.5307, 10.4949);
    glVertex2f(9.5307, 10.4949);
    glVertex2f(9.5307, 6.7870);
    glVertex2f(9.5307, 6.7870);
    glVertex2f(6.9220, 6.7870);
    glEnd();

    ///windows
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(6.9422, 9.8125);
    glVertex2f(7.2995, 9.8125);
    glVertex2f(7.2995, 10.0845);
    glVertex2f(6.9422, 10.0845);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(7.6293, 9.8125);
    glVertex2f(7.9866, 9.8125);
    glVertex2f(7.9866, 10.0845);
    glVertex2f(7.6293, 10.0845);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(8.2859, 9.8125);
    glVertex2f(8.6432, 9.8125);
    glVertex2f(8.6432, 10.0845);
    glVertex2f(8.2859, 10.0845);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(6.9422, 9.2520);
    glVertex2f(7.2995, 9.2520);
    glVertex2f(7.2995, 9.5240);
    glVertex2f(6.9422, 9.5240);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(7.6293, 9.2520);
    glVertex2f(7.9866, 9.2520);
    glVertex2f(7.9866, 9.5240);
    glVertex2f(7.6293, 9.5240);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(8.2859, 9.2520);
    glVertex2f(8.6432, 9.2520);
    glVertex2f(8.6432, 9.5240);
    glVertex2f(8.2859, 9.5240);
    glEnd();

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(6.9422, 8.7152);
    glVertex2f(7.2995, 8.7152);
    glVertex2f(7.2995, 8.9872);
    glVertex2f(6.9422, 8.9872);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(7.6293, 8.7152);
    glVertex2f(7.9866, 8.7152);
    glVertex2f(7.9866, 8.9872);
    glVertex2f(7.6293, 8.9872);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(8.2859, 8.7152);
    glVertex2f(8.6432, 8.7152);
    glVertex2f(8.6432, 8.9872);
    glVertex2f(8.2859, 8.9872);
    glEnd();

    ///4
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(6.9422, 8.1780);
    glVertex2f(7.2995, 8.1780);
    glVertex2f(7.2995, 8.4500);
    glVertex2f(6.9422, 8.4500);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(7.6293, 8.1780);
    glVertex2f(7.9866, 8.1780);
    glVertex2f(7.9866, 8.4500);
    glVertex2f(7.6293, 8.4500);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(8.2859, 8.1780);
    glVertex2f(8.6432, 8.1780);
    glVertex2f(8.6432, 8.4500);
    glVertex2f(8.2859, 8.4500);
    glEnd();

    ///door
    glBegin(GL_POLYGON);
    glColor3ub(112,75,91);
    glVertex2f(6.9220, 6.7870);
    glVertex2f(8.1917, 6.7870);
    glVertex2f(8.1917, 7.9141);
    glVertex2f(6.9220, 7.9141);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(232,203,224);
    glVertex2f(6.9220, 6.7870);
    glVertex2f(8.1917, 6.7870);
    glVertex2f(8.1917, 6.7870);
    glVertex2f(8.1917, 7.9141);
    glVertex2f(8.1917, 7.9141);
    glVertex2f(6.9220, 7.9141);
    glVertex2f(6.9220, 7.9141);
    glVertex2f(6.9220, 6.7870);
    glEnd();

    ///Side glass
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(8.9462, 10.4949);
    glVertex2f(8.9462, 6.7870);
    glVertex2f(9.5307, 6.7870);
    glVertex2f(9.5307, 10.4949);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(88,60,84);
    glVertex2f(8.9462, 10.4949);
    glVertex2f(8.9462, 6.7870);
    glVertex2f(8.9462, 6.7870);
    glVertex2f(9.5307, 6.7870);
    glVertex2f(9.5307, 6.7870);
    glVertex2f(9.5307, 10.4949);
    glEnd();

    ///mid line
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(88,60,84);
    glVertex2f(9.2496, 6.7870);
    glVertex2f(9.2496, 10.4949);
    glEnd();

}

void building4()
{
    ///top
    glBegin(GL_POLYGON);
    glColor3ub(114,158,161);
    glVertex2f(5.1595, 12.3990);
    glVertex2f(6.4223, 12.3990);
    glVertex2f(6.4223, 12.2124);
    glVertex2f(5.1595, 12.2124);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(190,246,221);
    glVertex2f(5.1595, 12.3990);
    glVertex2f(6.4223, 12.3990);
    glVertex2f(6.4223, 12.3990);
    glVertex2f(6.4223, 12.2124);
    glVertex2f(6.4223, 12.2124);
    glVertex2f(5.1595, 12.2124);
    glVertex2f(5.1595, 12.2124);
    glVertex2f(5.1595, 12.3990);
    glEnd();

    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(114,158,161);
    glVertex2f(4.7213, 12.2124);
    glVertex2f(6.9220, 12.2124);
    glVertex2f(6.9220, 6.7870);
    glVertex2f(4.7213, 6.7870);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(190,246,221);
    glVertex2f(4.7213, 12.2124);
    glVertex2f(6.9220, 12.2124);
    glVertex2f(6.9220, 12.2124);
    glVertex2f(6.9220, 6.7870);
    glVertex2f(6.9220, 6.7870);
    glVertex2f(4.7213, 6.7870);
    glVertex2f(4.7213, 6.7870);
    glVertex2f(4.7213, 12.2124);
    glEnd();

    ///windows
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(5.1574, 11.6773);
    glVertex2f(5.5147, 11.6773);
    glVertex2f(5.5147, 11.9493);
    glVertex2f(5.1574, 11.9493);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(6.0762, 11.6773);
    glVertex2f(6.4336, 11.6773);
    glVertex2f(6.4336, 11.9493);
    glVertex2f(6.0762, 11.9493);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(5.1574, 11.1381);
    glVertex2f(5.5147, 11.1381);
    glVertex2f(5.5147, 11.4101);
    glVertex2f(5.1574, 11.4101);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(6.0762, 11.1381);
    glVertex2f(6.4336, 11.1381);
    glVertex2f(6.4336, 11.4101);
    glVertex2f(6.0762, 11.4101);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(5.1574, 10.5706);
    glVertex2f(5.5147, 10.5706);
    glVertex2f(5.5147, 10.8426);
    glVertex2f(5.1574, 10.8426);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(6.0762, 10.5706);
    glVertex2f(6.4336, 10.5706);
    glVertex2f(6.4336, 10.8426);
    glVertex2f(6.0762, 10.8426);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(5.1574, 10.0314);
    glVertex2f(5.5147, 10.0314);
    glVertex2f(5.5147, 10.3034);
    glVertex2f(5.1574, 10.3034);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(6.0762, 10.0314);
    glVertex2f(6.4336, 10.0314);
    glVertex2f(6.4336, 10.3034);
    glVertex2f(6.0762, 10.3034);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(5.1574, 9.4697);
    glVertex2f(5.5147, 9.4697);
    glVertex2f(5.5147, 9.7417);
    glVertex2f(5.1574, 9.7417);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(6.0762, 9.4697);
    glVertex2f(6.4336, 9.4697);
    glVertex2f(6.4336, 9.7417);
    glVertex2f(6.0762, 9.7417);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(5.1574, 8.9304);
    glVertex2f(5.5147, 8.9304);
    glVertex2f(5.5147, 9.2024);
    glVertex2f(5.1574, 9.2024);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(6.0762, 8.9304);
    glVertex2f(6.4336, 8.9304);
    glVertex2f(6.4336, 9.2024);
    glVertex2f(6.0762, 9.2024);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(5.1574, 8.3779);
    glVertex2f(5.5147, 8.3779);
    glVertex2f(5.5147, 8.6499);
    glVertex2f(5.1574, 8.6499);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(6.0762, 8.3779);
    glVertex2f(6.4336, 8.3779);
    glVertex2f(6.4336, 8.6499);
    glVertex2f(6.0762, 8.6499);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(5.1574, 7.8169);
    glVertex2f(5.5147, 7.8169);
    glVertex2f(5.5147, 8.0889);
    glVertex2f(5.1574, 8.0889);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(6.0762, 7.8169);
    glVertex2f(6.4336, 7.8169);
    glVertex2f(6.4336, 8.0889);
    glVertex2f(6.0762, 8.0889);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(5.1574, 7.2814);
    glVertex2f(5.5147, 7.2814);
    glVertex2f(5.5147, 7.5534);
    glVertex2f(5.1574, 7.5534);
    glEnd();

    ///door
    glBegin(GL_POLYGON);
    glColor3ub(190,246,221);
    glVertex2f(6.0762, 6.7870);
    glVertex2f(6.4336, 6.7870);
    glVertex2f(6.4336, 7.3828);
    glVertex2f(6.0762, 7.3828);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(190,246,221);
    glVertex2f(6.0762, 6.7870);
    glVertex2f(6.4336, 6.7870);
    glVertex2f(6.4336, 6.7870);
    glVertex2f(6.4336, 7.3828);
    glVertex2f(6.4336, 7.3828);
    glVertex2f(6.0762, 7.3828);
    glVertex2f(6.0762, 7.3828);
    glVertex2f(6.0762, 6.7870);
    glEnd();
}

void building5()
{
    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(131,80,113);
    glVertex2f(11.7200, 9.7796);
    glVertex2f(11.7214, 6.7870);
    glVertex2f(12.7612, 6.7870);
    glVertex2f(12.7612, 7.9445);
    glVertex2f(12.8868, 7.9445);
    glVertex2f(12.8868, 8.0617);
    glVertex2f(13.1002, 8.0616);
    glVertex2f(13.1002, 9.3513);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(128,0,128);
    glVertex2f(11.7200, 9.7796);
    glVertex2f(11.7214, 6.7870);
    glVertex2f(11.7214, 6.7870);
    glVertex2f(12.7612, 6.7870);
    glVertex2f(12.7612, 6.7870);
    glVertex2f(12.7612, 7.9445);
    glVertex2f(12.7612, 7.9445);
    glVertex2f(12.8868, 7.9445);
    glVertex2f(12.8868, 7.9445);
    glVertex2f(12.8868, 8.0617);
    glVertex2f(12.8868, 8.0617);
    glVertex2f(13.1002, 8.0616);
    glVertex2f(13.1002, 8.0616);
    glVertex2f(13.1002, 9.3513);
    glVertex2f(13.1002, 9.3513);
    glVertex2f(11.7200, 9.7796);
    glEnd();

    ///glass
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(12.1179, 9.3513);
    glVertex2f(12.1179, 6.7870);
    glVertex2f(12.7612, 6.7870);
    glVertex2f(12.7612, 7.9445);
    glVertex2f(12.8868, 7.9445);
    glVertex2f(12.8868, 8.0617);
    glVertex2f(13.1002, 8.0616);
    glVertex2f(13.1002, 9.3513);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(128,0,128);
    glVertex2f(12.7612, 6.7870);
    glVertex2f(12.7612, 7.9445);
    glVertex2f(12.7612, 7.9445);
    glVertex2f(12.8868, 7.9445);
    glVertex2f(12.8868, 7.9445);
    glVertex2f(12.8868, 8.0617);
    glVertex2f(12.8868, 8.0617);
    glVertex2f(13.1002, 8.0616);
    glVertex2f(13.1002, 8.0616);
    glVertex2f(13.1002, 9.3513);
    glVertex2f(13.1002, 9.3513);
    glVertex2f(12.1179, 9.3513);
    glEnd();

    ///Lines
    ///1
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(131,80,113);
    glVertex2f(12.1194, 9.1037);
    glVertex2f(13.1002, 9.1037);
    glEnd();

    ///2
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(131,80,113);
    glVertex2f(12.1194, 8.8634);
    glVertex2f(13.1002, 8.8634);
    glEnd();

    ///3
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(131,80,113);
    glVertex2f(12.1194, 8.6372);
    glVertex2f(13.1002, 8.6372);
    glEnd();

    ///4
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(131,80,113);
    glVertex2f(12.1194, 8.4303);
    glVertex2f(13.1002, 8.4303);
    glEnd();

    ///5
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(131,80,113);
    glVertex2f(12.1194, 8.2234);
    glVertex2f(13.1002, 8.2234);
    glEnd();

    ///6
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(131,80,113);
    glVertex2f(12.1194, 8.0240);
    glVertex2f(12.8868, 8.0240);
    glEnd();

    ///7
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(131,80,113);
    glVertex2f(12.1194, 7.8321);
    glVertex2f(12.7612, 7.8321);
    glEnd();

    ///8
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(131,80,113);
    glVertex2f(12.1194, 7.6290);
    glVertex2f(12.7612, 7.6290);
    glEnd();

    ///9
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(131,80,113);
    glVertex2f(12.1194, 7.4218);
    glVertex2f(12.7612, 7.4218);
    glEnd();

    ///10
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(131,80,113);
    glVertex2f(12.1194, 7.2007);
    glVertex2f(12.7612, 7.2007);
    glEnd();

    ///11
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(131,80,113);
    glVertex2f(12.1194, 6.9938);
    glVertex2f(12.7612, 6.9938);
    glEnd();
}

void building6()
{
    ///roof
    glBegin(GL_POLYGON);
    glColor3ub(255,215,181);
    glVertex2f(12.8868, 7.9445);
    glVertex2f(13.4970, 7.9445);
    glVertex2f(13.4968, 8.0615);
    glVertex2f(12.8868, 8.0617);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(255,179,138);
    glVertex2f(12.8868, 7.9445);
    glVertex2f(13.4970, 7.9445);
    glVertex2f(13.4970, 7.9445);
    glVertex2f(13.4968, 8.0615);
    glVertex2f(13.4968, 8.0615);
    glVertex2f(12.8868, 8.0617);
    glVertex2f(12.8868, 8.0617);
    glVertex2f(12.8868, 7.9445);
    glEnd();

    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(255,215,181);
    glVertex2f(12.7612, 7.9445);
    glVertex2f(12.7612, 6.7870);
    glVertex2f(13.6020, 6.7870);
    glVertex2f(13.6020, 7.9445);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(255,179,138);
    glVertex2f(12.7612, 7.9445);
    glVertex2f(12.7612, 6.7870);
    glVertex2f(12.7612, 6.7870);
    glVertex2f(13.6020, 6.7870);
    glVertex2f(13.6020, 6.7870);
    glVertex2f(13.6020, 7.9445);
    glVertex2f(13.6020, 7.9445);
    glVertex2f(12.7612, 7.9445);
    glEnd();

    ///windows
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(12.8902, 7.6524);
    glVertex2f(13.1165, 7.6524);
    glVertex2f(13.1165, 7.8044);
    glVertex2f(12.8902, 7.8044);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(13.2869, 7.6524);
    glVertex2f(13.5132, 7.6524);
    glVertex2f(13.5132, 7.8044);
    glVertex2f(13.2869, 7.8044);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(12.8902, 7.2977);
    glVertex2f(13.1165, 7.2977);
    glVertex2f(13.1165, 7.4497);
    glVertex2f(12.8902, 7.4497);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(13.2869, 7.2977);
    glVertex2f(13.5132, 7.2977);
    glVertex2f(13.5132, 7.4497);
    glVertex2f(13.2869, 7.4497);
    glEnd();

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(12.8902, 6.9278);
    glVertex2f(13.1165, 6.9278);
    glVertex2f(13.1165, 7.0798);
    glVertex2f(12.8902, 7.0798);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(13.2869, 6.9278);
    glVertex2f(13.5132, 6.9278);
    glVertex2f(13.5132, 7.0798);
    glVertex2f(13.2869, 7.0798);
    glEnd();
}

void building7()
{
    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(26,140,184);
    glVertex2f(14.2700, 11.3812);
    glVertex2f(14.2700, 6.7870);
    glVertex2f(15.7277, 6.7870);
    glVertex2f(15.7277, 10.8066);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(24,154,211);
    glVertex2f(14.2700, 11.3812);
    glVertex2f(14.2700, 6.7870);
    glVertex2f(14.2700, 6.7870);
    glVertex2f(15.7277, 6.7870);
    glVertex2f(15.7277, 6.7870);
    glVertex2f(15.7277, 10.8066);
    glVertex2f(15.7277, 10.8066);
    glVertex2f(14.2700, 11.3812);
    glEnd();

    ///glass
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(14.6921, 10.8066);
    glVertex2f(14.6907, 6.7870);
    glVertex2f(15.7277, 6.7870);
    glVertex2f(15.7277, 10.8066);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(24,154,211);
    glVertex2f(14.6907, 6.7870);
    glVertex2f(15.7277, 6.7870);
    glVertex2f(15.7277, 6.7870);
    glVertex2f(15.7277, 10.8066);
    glVertex2f(15.7277, 10.8066);
    glVertex2f(14.6921, 10.8066);
    glEnd();

    ///Lines
    ///1
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 10.5656);
    glVertex2f(15.7277, 10.5656);
    glEnd();

    ///2
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 10.3592);
    glVertex2f(15.7277, 10.3592);
    glEnd();

    ///3
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 10.1238);
    glVertex2f(15.7277, 10.1238);
    glEnd();

    ///4
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 9.9057);
    glVertex2f(15.7277, 9.9057);
    glEnd();

    ///5
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 9.6913);
    glVertex2f(15.7277, 9.6913);
    glEnd();

    ///6
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 9.4538);
    glVertex2f(15.7277, 9.4538);
    glEnd();

    ///7
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 9.2170);
    glVertex2f(15.7277, 9.2170);
    glEnd();

    ///8
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 9.0019);
    glVertex2f(15.7277, 9.0019);
    glEnd();

    ///9
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 8.7926);
    glVertex2f(15.7277, 8.7926);
    glEnd();

    ///10
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 8.6011);
    glVertex2f(15.7277, 8.6011);
    glEnd();

    ///11
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 8.4109);
    glVertex2f(15.7277, 8.4109);
    glEnd();

    ///12
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 8.2109);
    glVertex2f(15.7277, 8.2109);
    glEnd();

    ///13
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 8.0183);
    glVertex2f(15.7277, 8.0183);
    glEnd();

    ///14
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 7.8052);
    glVertex2f(15.7277, 7.8052);
    glEnd();

    ///15
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 7.6065);
    glVertex2f(15.7277, 7.6065);
    glEnd();

    ///16
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 7.3808);
    glVertex2f(15.7277, 7.3808);
    glEnd();

    ///17
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 7.1732);
    glVertex2f(15.7277, 7.1732);
    glEnd();

    ///18
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(26,140,184);
    glVertex2f(14.6921, 6.9588);
    glVertex2f(15.7277, 6.9588);
    glEnd();
}

void building8()
{
    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(124,104,123);
    glVertex2f(13.6018, 8.8974);
    glVertex2f(13.6020, 6.7870);
    glVertex2f(14.6921, 6.7870);
    glVertex2f(14.6921, 8.6119);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(102,41,70);
    glVertex2f(13.6018, 8.8974);
    glVertex2f(13.6020, 6.7870);
    glVertex2f(13.6020, 6.7870);
    glVertex2f(14.6921, 6.7870);
    glVertex2f(14.6921, 6.7870);
    glVertex2f(14.6921, 8.6119);
    glVertex2f(14.6921, 8.6119);
    glVertex2f(13.6018, 8.8974);
    glEnd();

    ///glass
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(13.8773, 8.6119);
    glVertex2f(13.8773, 6.7870);
    glVertex2f(14.6921, 6.7870);
    glVertex2f(14.6921, 8.6119);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(102,41,70);
    glVertex2f(13.8773, 6.7870);
    glVertex2f(14.6921, 6.7870);
    glVertex2f(14.6921, 6.7870);
    glVertex2f(14.6921, 8.6119);
    glVertex2f(14.6921, 8.6119);
    glVertex2f(13.8773, 8.6119);
    glEnd();

    ///lines
    ///1
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(124,104,123);
    glVertex2f(13.8773, 8.4220);
    glVertex2f(14.6907, 8.4220);
    glEnd();

    ///2
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(124,104,123);
    glVertex2f(13.8773, 8.2226);
    glVertex2f(14.6907, 8.2226);
    glEnd();

    ///3
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(124,104,123);
    glVertex2f(13.8773, 8.0307);
    glVertex2f(14.6907, 8.0307);
    glEnd();

    ///4
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(124,104,123);
    glVertex2f(13.8773, 7.8276);
    glVertex2f(14.6907, 7.8276);
    glEnd();

    ///5
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(124,104,123);
    glVertex2f(13.8773, 7.6204);
    glVertex2f(14.6907, 7.6204);
    glEnd();

    ///6
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(124,104,123);
    glVertex2f(13.8773, 7.3993);
    glVertex2f(14.6907, 7.3993);
    glEnd();

    ///7
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(124,104,123);
    glVertex2f(13.8773, 7.1924);
    glVertex2f(14.6907, 7.1924);
    glEnd();

    ///8
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(124,104,123);
    glVertex2f(13.8773, 6.9856);
    glVertex2f(14.6907, 6.9856);
    glEnd();
}

void building9()
{
    ///roof
    glBegin(GL_POLYGON);
    glColor3ub(236,169,169);
    glVertex2f(15.5935, 9.6839);
    glVertex2f(16.6238, 9.6839);
    glVertex2f(16.6237, 9.4973);
    glVertex2f(15.5935, 9.4973);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(255,216,216);
    glVertex2f(15.5935, 9.6839);
    glVertex2f(16.6238, 9.6839);
    glVertex2f(16.6238, 9.6839);
    glVertex2f(16.6237, 9.4973);
    glVertex2f(16.6237, 9.4973);
    glVertex2f(15.5935, 9.4973);
    glVertex2f(15.5935, 9.4973);
    glVertex2f(15.5935, 9.6839);
    glEnd();

    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(236,169,169);
    glVertex2f(15.2860, 9.4973);
    glVertex2f(16.8977, 9.4973);
    glVertex2f(16.8977, 6.7870);
    glVertex2f(15.2860, 6.7870);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(255,216,216);
    glVertex2f(15.2860, 9.4973);
    glVertex2f(16.8977, 9.4973);
    glVertex2f(16.8977, 9.4973);
    glVertex2f(16.8977, 6.7870);
    glVertex2f(16.8977, 6.7870);
    glVertex2f(15.2860, 6.7870);
    glVertex2f(15.2860, 6.7870);
    glVertex2f(15.2860, 9.4973);
    glEnd();

    ///windows
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(15.6083, 8.8890);
    glVertex2f(15.9657, 8.8890);
    glVertex2f(15.9657, 9.1610);
    glVertex2f(15.6083, 9.1610);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(16.2649, 8.8890);
    glVertex2f(16.6223, 8.8890);
    glVertex2f(16.6223, 9.1610);
    glVertex2f(16.2649, 9.1610);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(15.6083, 8.3284);
    glVertex2f(15.9657, 8.3284);
    glVertex2f(15.9657, 8.6004);
    glVertex2f(15.6083, 8.6004);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(16.2649, 8.3284);
    glVertex2f(16.6223, 8.3284);
    glVertex2f(16.6223, 8.6004);
    glVertex2f(16.2649, 8.6004);
    glEnd();

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(15.6083, 7.7917);
    glVertex2f(15.9657, 7.7917);
    glVertex2f(15.9657, 8.0637);
    glVertex2f(15.6083, 8.0637);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(16.2649, 7.7917);
    glVertex2f(16.6223, 7.7917);
    glVertex2f(16.6223, 8.0637);
    glVertex2f(16.2649, 8.0637);
    glEnd();

    ///4
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(15.6083, 7.2669);
    glVertex2f(15.9657, 7.2669);
    glVertex2f(15.9657, 7.5389);
    glVertex2f(15.6083, 7.5389);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(16.2649, 7.2669);
    glVertex2f(16.6223, 7.2669);
    glVertex2f(16.6223, 7.5389);
    glVertex2f(16.2649, 7.5389);
    glEnd();
}

void building10()
{
    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(122,71,79);
    glVertex2f(16.8977, 8.0183);
    glVertex2f(18.2348, 8.0183);
    glVertex2f(18.2348, 6.7870);
    glVertex2f(16.8977, 6.7870);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(103,47,10);
    glVertex2f(16.8977, 8.0183);
    glVertex2f(18.2348, 8.0183);
    glVertex2f(18.2348, 8.0183);
    glVertex2f(18.2348, 6.7870);
    glVertex2f(18.2348, 6.7870);
    glVertex2f(16.8977, 6.7870);
    glVertex2f(16.8977, 6.7870);
    glVertex2f(16.8977, 8.0183);
    glEnd();

    ///Windows
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(17.0617, 7.5924);
    glVertex2f(17.4190, 7.5924);
    glVertex2f(17.4190, 7.8644);
    glVertex2f(17.0617, 7.8644);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(17.7079, 7.5924);
    glVertex2f(18.0652, 7.5924);
    glVertex2f(18.0652, 7.8644);
    glVertex2f(17.7079, 7.8644);
    glEnd();

    ///door
    glBegin(GL_POLYGON);
    glColor3ub(112,75,91);
    glVertex2f(17.3671, 7.2742);
    glVertex2f(17.8115, 7.2742);
    glVertex2f(17.8114, 6.7870);
    glVertex2f(17.3675, 6.7870);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(103,47,10);
    glVertex2f(17.3671, 7.2742);
    glVertex2f(17.8115, 7.2742);
    glVertex2f(17.8115, 7.2742);
    glVertex2f(17.8114, 6.7870);
    glVertex2f(17.8114, 6.7870);
    glVertex2f(17.3675, 6.7870);
    glVertex2f(17.3675, 6.7870);
    glVertex2f(17.3671, 7.2742);
    glEnd();
}

void building11()
{
    ///roof
    glBegin(GL_POLYGON);
    glColor3ub(151,113,115);
    glVertex2f(21.2438, 10.6817);
    glVertex2f(21.9511, 10.6817);
    glVertex2f(21.9511, 10.4951);
    glVertex2f(21.2438, 10.4952);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(255,232,213);
    glVertex2f(21.2438, 10.6817);
    glVertex2f(21.9511, 10.6817);
    glVertex2f(21.9511, 10.6817);
    glVertex2f(21.9511, 10.4951);
    glVertex2f(21.9511, 10.4951);
    glVertex2f(21.2438, 10.4952);
    glVertex2f(21.2438, 10.4952);
    glVertex2f(21.2438, 10.6817);
    glEnd();

    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(151,113,115);
    glVertex2f(20.1060, 6.7870);
    glVertex2f(21.9511, 6.7870);
    glVertex2f(21.9511, 10.4949);
    glVertex2f(20.1060, 10.4952);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(255,232,213);
    glVertex2f(20.1060, 6.7870);
    glVertex2f(21.9511, 6.7870);
    glVertex2f(21.9511, 6.7870);
    glVertex2f(21.9511, 10.4949);
    glVertex2f(21.9511, 10.4949);
    glVertex2f(20.1060, 10.4952);
    glVertex2f(20.1060, 10.4952);
    glVertex2f(20.1060, 6.7870);
    glEnd();

    ///glass
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(20.1060, 10.4952);
    glVertex2f(20.1060, 6.7870);
    glVertex2f(20.6495, 6.7870);
    glVertex2f(20.6495, 10.4952);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(151,113,115);
    glVertex2f(20.1060, 10.4952);
    glVertex2f(20.1060, 6.7870);
    glVertex2f(20.1060, 6.7870);
    glVertex2f(20.6495, 6.7870);
    glVertex2f(20.6495, 6.7870);
    glVertex2f(20.6495, 10.4952);
    glEnd();

    ///mid line
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(151,113,115);
    glVertex2f(20.3760, 6.7870);
    glVertex2f(20.3760, 10.4949);
    glEnd();

    ///windows
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(20.9371, 9.9014);
    glVertex2f(21.2945, 9.9014);
    glVertex2f(21.2945, 10.1734);
    glVertex2f(20.9371, 10.1734);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(21.5937, 9.9014);
    glVertex2f(21.9511, 9.9014);
    glVertex2f(21.9511, 10.1734);
    glVertex2f(21.5937, 10.1734);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(20.9371, 9.3408);
    glVertex2f(21.2945, 9.3408);
    glVertex2f(21.2945, 9.6128);
    glVertex2f(20.9371, 9.6128);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(21.5937, 9.3408);
    glVertex2f(21.9511, 9.3408);
    glVertex2f(21.9511, 9.6128);
    glVertex2f(21.5937, 9.6128);
    glEnd();

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(20.9371, 8.8041);
    glVertex2f(21.2945, 8.8041);
    glVertex2f(21.2945, 9.0761);
    glVertex2f(20.9371, 9.0761);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(21.5937, 8.8041);
    glVertex2f(21.9511, 8.8041);
    glVertex2f(21.9511, 9.0761);
    glVertex2f(21.5937, 9.0761);
    glEnd();

    ///4
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(20.9371, 8.2793);
    glVertex2f(21.2945, 8.2793);
    glVertex2f(21.2945, 8.5513);
    glVertex2f(20.9371, 8.5513);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(21.5937, 8.2793);
    glVertex2f(21.9511, 8.2793);
    glVertex2f(21.9511, 8.5513);
    glVertex2f(21.5937, 8.5513);
    glEnd();

    ///door
    glBegin(GL_POLYGON);
    glColor3ub(112,75,91);
    glVertex2f(21.3113, 6.7870);
    glVertex2f(21.9511, 6.7870);
    glVertex2f(21.9511, 7.9141);
    glVertex2f(21.3135, 7.9141);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(255,232,213);
    glVertex2f(21.3113, 6.7870);
    glVertex2f(21.9511, 6.7870);
    glVertex2f(21.9511, 6.7870);
    glVertex2f(21.9511, 7.9141);
    glVertex2f(21.9511, 7.9141);
    glVertex2f(21.3135, 7.9141);
    glVertex2f(21.3135, 7.9141);
    glVertex2f(21.3113, 6.7870);
    glEnd();
}

void building12()
{
    ///roof
    glBegin(GL_POLYGON);
    glColor3ub(47,88,139);
    glVertex2f(23.9523, 9.0535);
    glVertex2f(28.0230, 9.0535);
    glVertex2f(25.2842, 10.0924);
    glVertex2f(23.9523, 9.5177);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(27,45,72);
    glVertex2f(23.9523, 9.0535);
    glVertex2f(28.0230, 9.0535);
    glVertex2f(28.0230, 9.0535);
    glVertex2f(25.2842, 10.0924);
    glVertex2f(25.2842, 10.0924);
    glVertex2f(23.9523, 9.5177);
    glVertex2f(23.9523, 9.5177);
    glVertex2f(23.9523, 9.0535);
    glEnd();

    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(210,217,211);
    glVertex2f(28.0230, 9.0535);
    glVertex2f(23.9523, 9.0535);
    glVertex2f(23.9523, 6.7870);
    glVertex2f(28.0230, 6.7870);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(27,45,72);
    glVertex2f(28.0230, 9.0535);
    glVertex2f(23.9523, 9.0535);
    glVertex2f(23.9523, 9.0535);
    glVertex2f(23.9523, 6.7870);
    glVertex2f(23.9523, 6.7870);
    glVertex2f(28.0230, 6.7870);
    glVertex2f(28.0230, 6.7870);
    glVertex2f(28.0230, 9.0535);
    glEnd();

    ///pillar
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(127,153,177);
    glVertex2f(23.9523, 8.2186);
    glVertex2f(23.9523, 6.7870);
    glVertex2f(24.3782, 6.7870);
    glVertex2f(24.3782, 7.6556);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(27,45,72);
    glVertex2f(23.9523, 8.2186);
    glVertex2f(23.9523, 6.7870);
    glVertex2f(23.9523, 6.7870);
    glVertex2f(24.3782, 6.7870);
    glVertex2f(24.3782, 6.7870);
    glVertex2f(24.3782, 7.6556);
    glVertex2f(24.3782, 7.6556);
    glVertex2f(23.9523, 8.2186);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(127,153,177);
    glVertex2f(25.6306, 8.5031);
    glVertex2f(24.9044, 7.9401);
    glVertex2f(24.9044, 6.7870);
    glVertex2f(26.3568, 6.7870);
    glVertex2f(26.3568, 7.9401);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(27,45,72);
    glVertex2f(25.6195, 8.5031);
    glVertex2f(24.9044, 7.9401);
    glVertex2f(24.9044, 7.9401);
    glVertex2f(24.9044, 6.7870);
    glVertex2f(24.9044, 6.7870);
    glVertex2f(26.3568, 6.7870);
    glVertex2f(26.3568, 6.7870);
    glVertex2f(26.3568, 7.9401);
    glVertex2f(26.3568, 7.9401);
    glVertex2f(25.6195, 8.5031);
    glEnd();

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(127,153,177);
    glVertex2f(27.2335, 8.2186);
    glVertex2f(26.8516, 7.6556);
    glVertex2f(26.8516, 6.7870);
    glVertex2f(27.6154, 6.7870);
    glVertex2f(27.6154, 7.6556);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(27,45,72);
    glVertex2f(27.2335, 8.2186);
    glVertex2f(26.8516, 7.6556);
    glVertex2f(26.8516, 7.6556);
    glVertex2f(26.8516, 6.7870);
    glVertex2f(26.8516, 6.7870);
    glVertex2f(27.6154, 6.7870);
    glVertex2f(27.6154, 6.7870);
    glVertex2f(27.6154, 7.6556);
    glVertex2f(27.6154, 7.6556);
    glVertex2f(27.2335, 8.2186);
    glEnd();

    ///upper line
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(27,45,72);
    glVertex2f(25.2842, 10.0924);
    glVertex2f(25.2835, 10.6207);
    glEnd();
}

void building13()
{
    ///roof
    glBegin(GL_POLYGON);
    glColor3ub(85,170,170);
    glVertex2f(22.3319, 11.9770);
    glVertex2f(23.5947, 11.9770);
    glVertex2f(23.5947, 11.7904);
    glVertex2f(22.3319, 11.7904);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(187,204,221);
    glVertex2f(22.3319, 11.9770);
    glVertex2f(23.5947, 11.9770);
    glVertex2f(23.5947, 11.9770);
    glVertex2f(23.5947, 11.7904);
    glVertex2f(23.5947, 11.7904);
    glVertex2f(22.3319, 11.7904);
    glVertex2f(22.3319, 11.7904);
    glVertex2f(22.3319, 11.9770);
    glEnd();

    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(85,170,170);
    glVertex2f(21.9511, 6.7870);
    glVertex2f(23.9523, 6.7870);
    glVertex2f(23.9523, 11.7904);
    glVertex2f(21.9511, 11.7904);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(187,204,221);
    glVertex2f(21.9511, 6.7870);
    glVertex2f(23.9523, 6.7870);
    glVertex2f(23.9523, 6.7870);
    glVertex2f(23.9523, 11.7904);
    glVertex2f(23.9523, 11.7904);
    glVertex2f(21.9511, 11.7904);
    glVertex2f(21.9511, 11.7904);
    glVertex2f(21.9511, 6.7870);
    glEnd();

    ///windows
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(22.3303, 11.1381);
    glVertex2f(22.6877, 11.1381);
    glVertex2f(22.6877, 11.4101);
    glVertex2f(22.3303, 11.4101);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(23.2492, 11.1381);
    glVertex2f(23.6065, 11.1381);
    glVertex2f(23.6065, 11.4101);
    glVertex2f(23.2492, 11.4101);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(22.3303, 10.5706);
    glVertex2f(22.6877, 10.5706);
    glVertex2f(22.6877, 10.8426);
    glVertex2f(22.3303, 10.8426);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(23.2492, 10.5706);
    glVertex2f(23.6065, 10.5706);
    glVertex2f(23.6065, 10.8426);
    glVertex2f(23.2492, 10.8426);
    glEnd();

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(22.3303, 10.0314);
    glVertex2f(22.6877, 10.0314);
    glVertex2f(22.6877, 10.3034);
    glVertex2f(22.3303, 10.3034);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(23.2492, 10.0314);
    glVertex2f(23.6065, 10.0314);
    glVertex2f(23.6065, 10.3034);
    glVertex2f(23.2492, 10.3034);
    glEnd();

    ///4
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(22.3303, 9.4697);
    glVertex2f(22.6877, 9.4697);
    glVertex2f(22.6877, 9.7417);
    glVertex2f(22.3303, 9.7417);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(23.2492, 9.4697);
    glVertex2f(23.6065, 9.4697);
    glVertex2f(23.6065, 9.7417);
    glVertex2f(23.2492, 9.7417);
    glEnd();

    ///5
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(22.3303, 8.9304);
    glVertex2f(22.6877, 8.9304);
    glVertex2f(22.6877, 9.2024);
    glVertex2f(22.3303, 9.2024);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(23.2492, 8.9304);
    glVertex2f(23.6065, 8.9304);
    glVertex2f(23.6065, 9.2024);
    glVertex2f(23.2492, 9.2024);
    glEnd();

    ///6
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(22.3303, 8.3779);
    glVertex2f(22.6877, 8.3779);
    glVertex2f(22.6877, 8.6499);
    glVertex2f(22.3303, 8.6499);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(23.2492, 8.3779);
    glVertex2f(23.6065, 8.3779);
    glVertex2f(23.6065, 8.6499);
    glVertex2f(23.2492, 8.6499);
    glEnd();

    ///7
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(22.3303, 7.8169);
    glVertex2f(22.6877, 7.8169);
    glVertex2f(22.6877, 8.0889);
    glVertex2f(22.3303, 8.0889);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(23.2492, 7.8169);
    glVertex2f(23.6065, 7.8169);
    glVertex2f(23.6065, 8.0889);
    glVertex2f(23.2492, 8.0889);
    glEnd();

    ///8
    glBegin(GL_POLYGON);
    glColor3ub(196, 245, 238);
    glVertex2f(22.3303, 7.2814);
    glVertex2f(22.6877, 7.2814);
    glVertex2f(22.6877, 7.5534);
    glVertex2f(22.3303, 7.5534);
    glEnd();

    ///door
    glBegin(GL_POLYGON);
    glColor3ub(51,127,124);
    glVertex2f(23.2571, 6.7870);
    glVertex2f(23.6144, 6.7870);
    glVertex2f(23.6144, 7.3828);
    glVertex2f(23.2571, 7.3828);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(187,204,221);
    glVertex2f(23.2571, 6.7870);
    glVertex2f(23.6144, 6.7870);
    glVertex2f(23.6144, 6.7870);
    glVertex2f(23.6144, 7.3828);
    glVertex2f(23.6144, 7.3828);
    glVertex2f(23.2571, 7.3828);
    glVertex2f(23.2571, 7.3828);
    glVertex2f(23.2571, 6.7870);
    glEnd();
}

void roadSide()
{
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(132, 149, 141);
    glVertex2f(0, 6.7870);
    glVertex2f(0, 6.4468);
    glVertex2f(30, 6.4468);
    glVertex2f(30, 6.7870);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(132, 149, 141);
    glVertex2f(0, 5.3310);
    glVertex2f(0, 4.8904);
    glVertex2f(30, 4.8904);
    glVertex2f(30, 5.3310);
    glEnd();

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(132, 149, 141);
    glVertex2f(0, 2.7833);
    glVertex2f(0, 2.2101);
    glVertex2f(30, 2.2101);
    glVertex2f(30, 2.7833);
    glEnd();

    ///4
    glBegin(GL_POLYGON);
    glColor3ub(132, 149, 141);
    glVertex2f(0.0000, 0.9617);
    glVertex2f(0.0000, 0.6012);
    glVertex2f(30.0000, 0.6012);
    glVertex2f(30.0000, 0.9617);
    glEnd();
}

void elevator()
{
    glBegin(GL_POLYGON);
    glColor3ub(63, 60, 81);
    glVertex2f(0.0000, 6.7870);
    glVertex2f(0.0000, 6.4468);
    glVertex2f(30.000, 6.4468);
    glVertex2f(30.000, 6.7870);
    glEnd();

    ///Side lines
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(255, 255, 255);
    glVertex2f(0.0000, 6.7477);
    glVertex2f(30.000, 6.7477);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(255, 255, 255);
    glVertex2f(0.0000, 6.4926);
    glVertex2f(30.000, 6.4926);
    glEnd();

    glPushMatrix();
    glTranslatef(obj_elevator, 0, 0);

    ///Direction line
    ///1
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(0.6524, 6.6847);
    glVertex2f(0.7837, 6.6077);
    glVertex2f(0.7837, 6.6077);
    glVertex2f(0.6524, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(2.1787, 6.6847);
    glVertex2f(2.3100, 6.6077);
    glVertex2f(2.3100, 6.6077);
    glVertex2f(2.1787, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(3.6315, 6.6847);
    glVertex2f(3.7629, 6.6077);
    glVertex2f(3.7629, 6.6077);
    glVertex2f(3.6315, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(5.1709, 6.6847);
    glVertex2f(5.3023, 6.6077);
    glVertex2f(5.3023, 6.6077);
    glVertex2f(5.1709, 6.5307);
    glEnd();

    ///2
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(8.6399 , 6.6847);
    glVertex2f(8.7712, 6.6077);
    glVertex2f(8.7712, 6.6077);
    glVertex2f(8.6399 , 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(10.1662, 6.6847);
    glVertex2f(10.2975, 6.6077);
    glVertex2f(10.2975, 6.6077);
    glVertex2f(10.1662, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(11.6190, 6.6847);
    glVertex2f(11.7504, 6.6077);
    glVertex2f(11.7504, 6.6077);
    glVertex2f(11.6190, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(13.1584, 6.6847);
    glVertex2f(13.2897, 6.6077);
    glVertex2f(13.2897, 6.6077);
    glVertex2f(13.1584, 6.5307);
    glEnd();

    ///3
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(16.6273, 6.6847);
    glVertex2f(16.7587, 6.6077);
    glVertex2f(16.7587, 6.6077);
    glVertex2f(16.6273, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(18.1537, 6.6847);
    glVertex2f(18.2850, 6.6077);
    glVertex2f(18.2850, 6.6077);
    glVertex2f(18.1537, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(19.6065, 6.6847);
    glVertex2f(19.7379, 6.6077);
    glVertex2f(19.7379, 6.6077);
    glVertex2f(19.6065, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(21.1459, 6.6847);
    glVertex2f(21.2772, 6.6077);
    glVertex2f(21.2772, 6.6077);
    glVertex2f(21.1459, 6.5307);
    glEnd();

    ///4
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(24.6148, 6.6847);
    glVertex2f(24.7462, 6.6077);
    glVertex2f(24.7462, 6.6077);
    glVertex2f(24.6148, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(26.1412, 6.6847);
    glVertex2f(26.2725, 6.6077);
    glVertex2f(26.2725, 6.6077);
    glVertex2f(26.1412, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(27.5940, 6.6847);
    glVertex2f(27.7254, 6.6077);
    glVertex2f(27.7254, 6.6077);
    glVertex2f(27.5940, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(29.1334, 6.6847);
    glVertex2f(29.2647, 6.6077);
    glVertex2f(29.2647, 6.6077);
    glVertex2f(29.1334, 6.5307);
    glEnd();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(obj_elevatorX, 0, 0);

    ///5
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-7.3351, 6.6847);
    glVertex2f(-7.2038, 6.6077);
    glVertex2f(-7.2038, 6.6077);
    glVertex2f(-7.3351, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-5.8088, 6.6847);
    glVertex2f(-5.6775 , 6.6077);
    glVertex2f(-5.6775 , 6.6077);
    glVertex2f(-5.8088, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-4.3560, 6.6847);
    glVertex2f(-4.2246, 6.6077);
    glVertex2f(-4.2246, 6.6077);
    glVertex2f(-4.3560, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-2.8166, 6.6847);
    glVertex2f(-2.6852, 6.6077);
    glVertex2f(-2.6852, 6.6077);
    glVertex2f(-2.8166, 6.5307);
    glEnd();

    ///6
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-15.3226, 6.6847);
    glVertex2f(-15.1913, 6.6077);
    glVertex2f(-15.1913, 6.6077);
    glVertex2f(-15.3226, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-13.7963, 6.6847);
    glVertex2f(-13.6649, 6.6077);
    glVertex2f(-13.6649, 6.6077);
    glVertex2f(-13.7963, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-12.3434, 6.6847);
    glVertex2f( -12.2121, 6.6077);
    glVertex2f( -12.2121, 6.6077);
    glVertex2f(-12.3434, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-10.8041, 6.6847);
    glVertex2f(-10.6727, 6.6077);
    glVertex2f(-10.6727, 6.6077);
    glVertex2f(-10.8041, 6.5307);
    glEnd();

    ///7
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-23.3101, 6.6847);
    glVertex2f(-23.1788, 6.6077);
    glVertex2f(-23.1788, 6.6077);
    glVertex2f(-23.3101, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-21.7838, 6.6847);
    glVertex2f(-21.6524, 6.6077);
    glVertex2f(-21.6524, 6.6077);
    glVertex2f(-21.7838, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-20.3309, 6.6847);
    glVertex2f(-20.1996, 6.6077);
    glVertex2f(-20.1996, 6.6077);
    glVertex2f(-20.3309, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-18.7916, 6.6847);
    glVertex2f(-18.6602, 6.6077);
    glVertex2f(-18.6602, 6.6077);
    glVertex2f(-18.7916, 6.5307);
    glEnd();

    ///8
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-31.2976, 6.6847);
    glVertex2f(-31.1663, 6.6077);
    glVertex2f(-31.1663, 6.6077);
    glVertex2f(-31.2976, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-29.7713, 6.6847);
    glVertex2f(-29.6399, 6.6077);
    glVertex2f(-29.6399, 6.6077);
    glVertex2f(-29.7713, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-28.3184, 6.6847);
    glVertex2f(-28.1871, 6.6077);
    glVertex2f(-28.1871, 6.6077);
    glVertex2f(-28.3184, 6.5307);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(-26.7791, 6.6847);
    glVertex2f(-26.6477, 6.6077);
    glVertex2f(-26.6477, 6.6077);
    glVertex2f(-26.7791, 6.5307);
    glEnd();

    glPopMatrix();
}
void moveElevator(int value)
{
    obj_elevator+= 0.07;
    if(obj_elevator>30)
    {
        obj_elevator = -30;
    }

    obj_elevatorX+= 0.07;
    if(obj_elevatorX>60)
    {
        obj_elevatorX = 0;
    }

    glutPostRedisplay();
    glutTimerFunc(10, moveElevator, 0);
}

void human()
{
    glPushMatrix();
    glTranslatef(obj_human, 0, 0);

    ///Human1
    fillCircle(0.1455,1.7645, 7.1073, 49,49,49);
    fillCircle(0.1455,1.7661, 7.0639, 255,219,172);

    ///body
    glBegin(GL_POLYGON);
    glColor3ub(11,139,123);
    glVertex2f(1.6225, 7.0090);
    glVertex2f(1.9146, 7.0090);
    glVertex2f(1.9146, 6.8304);
    glVertex2f(1.6225, 6.8304);
    glEnd();

    ///legs
    glBegin(GL_POLYGON);
    glColor3ub(41,23,23);
    glVertex2f(1.6225, 6.8304);
    glVertex2f(1.7220, 6.8304);
    glVertex2f(1.6913, 6.5974);
    glVertex2f(1.6225, 6.5974);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(41,23,23);
    glVertex2f(1.7981, 6.8304);
    glVertex2f(1.9146, 6.8304);
    glVertex2f(1.9146, 6.5974);
    glVertex2f(1.7981, 6.5974);
    glEnd();

    ///hands
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(255,219,172);
    glVertex2f(1.6225, 7.0090);
    glVertex2f(1.5759, 6.9236);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(255,219,172);
    glVertex2f(1.9146, 7.0090);
    glVertex2f(1.9618, 6.9236);
    glEnd();

    ///Human2
    fillCircle(0.1455,10.7123, 7.1073, 49,49,49);
    fillCircle(0.1455,10.7139, 7.0639, 141,85,36);

    ///body
    glBegin(GL_POLYGON);
    glColor3ub(60,62,146);
    glVertex2f(10.5704, 7.0090);
    glVertex2f(10.8624, 7.0090);
    glVertex2f(10.8624, 6.8304);
    glVertex2f(10.5704, 6.8304);
    glEnd();

    ///legs
    glBegin(GL_POLYGON);
    glColor3ub(41,23,23);
    glVertex2f(10.5704, 6.8304);
    glVertex2f(10.6698, 6.8304);
    glVertex2f( 10.6391, 6.5974);
    glVertex2f(10.5704, 6.5974);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(41,23,23);
    glVertex2f(10.7459, 6.8304);
    glVertex2f(10.8624, 6.8304);
    glVertex2f(10.8624, 6.5974);
    glVertex2f(10.7925, 6.5974);
    glEnd();

    ///hands
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(141,85,36);
    glVertex2f(10.5704, 7.0090);
    glVertex2f(10.5237, 6.9236);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(141,85,36);
    glVertex2f(10.8624, 7.0090);
    glVertex2f(10.9096, 6.9236);
    glEnd();

    ///Human3
    fillCircle(0.1455,19.2303, 7.1073, 49,49,49);
    fillCircle(0.1455,19.2319, 7.0639, 198,134,66);

    ///body
    glBegin(GL_POLYGON);
    glColor3ub(139,11,11);
    glVertex2f(19.0883, 7.0090);
    glVertex2f(19.3804, 7.0090);
    glVertex2f(19.3804, 6.8304);
    glVertex2f(19.0883, 6.8304);
    glEnd();

    ///legs
    glBegin(GL_POLYGON);
    glColor3ub(41,23,23);
    glVertex2f(19.0883, 6.8304);
    glVertex2f(19.1877, 6.8304);
    glVertex2f(19.1570, 6.5974);
    glVertex2f(19.0883, 6.5974);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(41,23,23);
    glVertex2f(19.2639, 6.8304);
    glVertex2f(19.3804, 6.8304);
    glVertex2f(19.3804, 6.5974);
    glVertex2f(19.3105, 6.5974);
    glEnd();

    ///hands
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(198,134,66);
    glVertex2f(19.0883, 7.0090);
    glVertex2f(19.0417, 6.9236);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(198,134,66);
    glVertex2f(19.3804, 7.0090);
    glVertex2f(19.4276, 6.9236);
    glEnd();

    ///Human4
    fillCircle(0.1455,27.8742, 7.1073, 49,49,49);
    fillCircle(0.1455,27.8758, 7.0639, 241,194,125);

    ///body
    glBegin(GL_POLYGON);
    glColor3ub(139,134,11);
    glVertex2f(27.7322, 7.0090);
    glVertex2f(28.0243, 7.0090);
    glVertex2f(28.0243, 6.8304);
    glVertex2f(27.7322, 6.8304);
    glEnd();

    ///legs
    glBegin(GL_POLYGON);
    glColor3ub(41,23,23);
    glVertex2f(27.7322, 6.8304);
    glVertex2f(27.8316, 6.8304);
    glVertex2f(27.8009, 6.5974);
    glVertex2f(27.7322, 6.5974);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(41,23,23);
    glVertex2f(27.9078, 6.8304);
    glVertex2f(28.0243, 6.8304);
    glVertex2f(28.0243, 6.5974);
    glVertex2f(27.9544, 6.5974);
    glEnd();

    ///hands
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(241,194,125);
    glVertex2f(27.7322, 7.0090);
    glVertex2f(27.6856, 6.9236);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(241,194,125);
    glVertex2f(28.0243, 7.0090);
    glVertex2f(28.0715, 6.9236);
    glEnd();

    glPopMatrix();
}
void moveHuman(int value)
{
    obj_human+= 0.07;
    if(obj_human>30)
    {
        obj_human = -30;
    }

    glutPostRedisplay();
    glutTimerFunc(10, moveHuman, 0);
}

void mainRoad()
{
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(52, 52, 52);
    glVertex2f(0, 6.4468);
    glVertex2f(0, 5.3310);
    glVertex2f(30, 5.3310);
    glVertex2f(30, 6.4468);
    glEnd();

    ///Border
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(255, 255, 255);
    glVertex2f(0.0000, 6.3336);
    glVertex2f(30.0000, 6.3336);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(52, 52, 52);
    glVertex2f(0, 2.2101);
    glVertex2f(0, 0.9617);
    glVertex2f(30, 0.9617);
    glVertex2f(30, 2.2101);
    glEnd();

    ///Border
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(255, 255, 255);
    glVertex2f(0.0000, 1.1826);
    glVertex2f(30.0000, 1.1826);
    glEnd();
}

void cableCarPillar1()
{
    ///top
    glBegin(GL_POLYGON);
    glColor3ub(177,	195, 187);
    glVertex2f(2.3100, 8.7152);
    glVertex2f(2.5075, 8.7152);
    glVertex2f(2.4003, 8.8662);
    glEnd();

    ///Pillar
    glBegin(GL_POLYGON);
    glColor3ub(177,	195, 187);
    glVertex2f(2.5075, 5.2338);
    glVertex2f(2.3100, 5.2338);
    glVertex2f(2.3100, 8.7152);
    glVertex2f(2.5075, 8.7152);
    glEnd();

    ///ground
    glBegin(GL_POLYGON);
    glColor3ub(177,	195, 187);
    glVertex2f(2.2656, 5.4869);
    glVertex2f(2.5550, 5.4869);
    glVertex2f(2.5550, 5.1534);
    glVertex2f(2.2656, 5.1534);
    glEnd();

    ///Cable
    glBegin(GL_LINES);
    glLineWidth(7);
    glColor3ub(255, 255, 255);
    glVertex2f(2.5075, 8.7152);
    glVertex2f(30.0000, 8.7152);
    glEnd();
}
void cableCarPillar2()
{
    ///top
    glBegin(GL_POLYGON);
    glColor3ub(177,	195, 187);
    glVertex2f(26.9425, 8.7152);
    glVertex2f(27.1400, 8.7152);
    glVertex2f(27.0328, 8.8662);
    glEnd();

    ///Pillar
    glBegin(GL_POLYGON);
    glColor3ub(177, 195, 187);
    glVertex2f(27.1400, 5.2338);
    glVertex2f(26.9425, 5.2338);
    glVertex2f(26.9425, 8.7152);
    glVertex2f(27.1400, 8.7152);
    glEnd();

    ///ground
    glBegin(GL_POLYGON);
    glColor3ub(177,	195, 187);
    glVertex2f(26.8969, 5.4976);
    glVertex2f(27.1863, 5.4976);
    glVertex2f(27.1863, 5.1641);
    glVertex2f(26.8969, 5.1641);
    glEnd();

    ///Cable
    glBegin(GL_LINES);
    glLineWidth(7);
    glColor3ub(255, 255, 255);
    glVertex2f(0.0000, 8.7152);
    glVertex2f(26.9425, 8.7152);
    glEnd();
}
void cableCar()
{
    glPushMatrix();
    if(scene1)
    {
        glTranslatef(obj_cableCar, 0, 0);
    }
    else
    {
        glTranslatef(obj_cableCarX, 0, 0);
    }

    ///top
    glBegin(GL_POLYGON);
    glColor3ub(0, 153, 153);
    glVertex2f(7.6293, 8.7987);
    glVertex2f(8.1088, 8.7987);
    glVertex2f(8.1088, 8.7152);
    glVertex2f(7.6293, 8.7152);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(7.6293, 8.7987);
    glVertex2f(8.1088, 8.7987);
    glVertex2f(8.1088, 8.7987);
    glVertex2f(8.1088, 8.7152);
    glVertex2f(8.1088, 8.7152);
    glVertex2f(7.6293, 8.7152);
    glVertex2f(7.6293, 8.7152);
    glVertex2f(7.6293, 8.7987);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(7);
    glColor3ub(255, 255, 255);
    glVertex2f(7.8662, 8.7052);
    glVertex2f(7.8662, 8.4134);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 153, 153);
    glVertex2f(7.6293, 8.4134);
    glVertex2f(8.1088, 8.4134);
    glVertex2f(8.1088, 8.3300);
    glVertex2f(7.6293, 8.3300);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(7.6293, 8.4134);
    glVertex2f(8.1088, 8.4134);
    glVertex2f(8.1088, 8.4134);
    glVertex2f(8.1088, 8.3300);
    glVertex2f(8.1088, 8.3300);
    glVertex2f(7.6293, 8.3300);
    glVertex2f(7.6293, 8.3300);
    glVertex2f(7.6293, 8.4134);
    glEnd();

    ///body
    glBegin(GL_POLYGON);
    glColor3ub(0, 153, 153);
    glVertex2f(7.0857, 8.3333);
    glVertex2f(8.6432, 8.3333);
    glVertex2f(8.6432, 7.1497);
    glVertex2f(7.0849, 7.1497);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(7.0857, 8.3333);
    glVertex2f(8.6432, 8.3333);
    glVertex2f(8.6432, 8.3333);
    glVertex2f(8.6432, 7.1497);
    glVertex2f(8.6432, 7.1497);
    glVertex2f(7.0849, 7.1497);
    glVertex2f(7.0849, 7.1497);
    glVertex2f(7.0857, 8.3333);
    glEnd();

    ///Shade
    glBegin(GL_POLYGON);
    glColor3ub(171, 228, 224);
    glVertex2f(7.0856, 8.1174);
    glVertex2f(8.6432, 8.1174);
    glVertex2f(8.6432, 7.3783);
    glVertex2f(7.0850, 7.3783);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(7.0856, 8.1174);
    glVertex2f(8.6432, 8.1174);
    glVertex2f(8.6432, 8.1174);
    glVertex2f(8.6432, 7.3783);
    glVertex2f(8.6432, 7.3783);
    glVertex2f(7.0850, 7.3783);
    glVertex2f(7.0850, 7.3783);
    glVertex2f(7.0856, 8.1174);
    glEnd();

    ///door
    glBegin(GL_POLYGON);
    glColor3ub(0, 153, 153);
    glVertex2f(7.5598, 8.1961);
    glVertex2f(8.1737, 8.1961);
    glVertex2f(8.1737, 7.2869);
    glVertex2f(7.5598, 7.2869);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(7.5598, 8.1961);
    glVertex2f(8.1737, 8.1961);
    glVertex2f(8.1737, 8.1961);
    glVertex2f(8.1737, 7.2869);
    glVertex2f(8.1737, 7.2869);
    glVertex2f(7.5598, 7.2869);
    glVertex2f(7.5598, 7.2869);
    glVertex2f(7.5598, 8.1961);
    glEnd();

    ///Glass
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(171, 228, 224);
    glVertex2f(7.6251, 8.0569);
    glVertex2f(7.7906, 8.0569);
    glVertex2f(7.7906, 7.5697);
    glVertex2f(7.6251, 7.5697);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(7.6251, 8.0569);
    glVertex2f(7.7906, 8.0569);
    glVertex2f(7.7906, 8.0569);
    glVertex2f(7.7906, 7.5697);
    glVertex2f(7.7906, 7.5697);
    glVertex2f(7.6251, 7.5697);
    glVertex2f(7.6251, 7.5697);
    glVertex2f(7.6251, 8.0569);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(171, 228, 224);
    glVertex2f(7.9342, 8.0569);
    glVertex2f(8.0997, 8.0569);
    glVertex2f(8.0997, 7.5697);
    glVertex2f(7.9342, 7.5697);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(7.9342, 8.0569);
    glVertex2f(8.0997, 8.0569);
    glVertex2f(8.0997, 8.0569);
    glVertex2f(8.0997, 7.5697);
    glVertex2f(8.0997, 7.5697);
    glVertex2f(7.9342, 7.5697);
    glVertex2f(7.9342, 7.5697);
    glVertex2f(7.9342, 8.0569);
    glEnd();

    ///mid line
    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(7.8646, 8.1961);
    glVertex2f(7.8646, 7.2869);
    glEnd();

    glPopMatrix();
}
void moveCableCar(int value)
{
    obj_cableCar+= cableCar_Speed;
    if(obj_cableCar>30 || obj_cableCar<-3)
        {
            cableCar_Speed *=-1;
        }

    obj_cableCarX+= cableCarX_Speed;
    if(obj_cableCarX>17 || obj_cableCarX<-16)
        {
            cableCarX_Speed *=-1;
        }

    glutPostRedisplay();
    glutTimerFunc(10, moveCableCar, 0);
}

void tree1()
{
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(3.4571, 5.5628);
    glVertex2f(3.5221, 5.5628);
    glVertex2f(3.5221, 5.0282);
    glVertex2f(3.4571, 5.0282);
    glEnd();

    fillCircle(0.1924, 3.3538, 5.6459, 56, 108, 55);
    fillCircle(0.1775, 3.4761, 5.6817, 56, 108, 55);
    fillCircle(0.1775, 3.6364, 5.6365, 77,115,88);
    fillCircle(0.1775, 3.3958, 5.7807, 56, 108, 55);
    fillCircle(0.1775, 3.5723, 5.7807, 77,115,88);
    fillCircle(0.1775, 3.4920, 5.8662, 77,115,88);

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(11.5992, 5.5628);
    glVertex2f(11.6642, 5.5628);
    glVertex2f(11.6642, 5.0282);
    glVertex2f(11.5992, 5.0282);
    glEnd();

    fillCircle(0.1924, 11.4959, 5.6459, 56, 108, 55);
    fillCircle(0.1775, 11.6183, 5.6817, 56, 108, 55);
    fillCircle(0.1775, 11.7786, 5.6365, 77,115,88);
    fillCircle(0.1775, 11.5379, 5.7807, 56, 108, 55);
    fillCircle(0.1775, 11.7144, 5.7807, 77,115,88);
    fillCircle(0.1775, 11.6341, 5.8662, 77,115,88);

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(19.7032, 5.5628);
    glVertex2f(19.7682, 5.5628);
    glVertex2f(19.7682, 5.0282);
    glVertex2f(19.7032, 5.0282);
    glEnd();

    fillCircle(0.1924, 19.5999, 5.6459, 56, 108, 55);
    fillCircle(0.1775, 19.7222, 5.6817, 56, 108, 55);
    fillCircle(0.1775, 19.8825, 5.6365, 77,115,88);
    fillCircle(0.1775, 19.6419, 5.7807, 56, 108, 55);
    fillCircle(0.1775, 19.8184, 5.7807, 77,115,88);
    fillCircle(0.1775, 19.7381, 5.8662, 77,115,88);

    ///4
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(28.0850, 5.5628);
    glVertex2f(28.1501, 5.5628);
    glVertex2f(28.1501, 5.0282);
    glVertex2f(28.0850, 5.0282);
    glEnd();

    fillCircle(0.1924, 27.9818, 5.6459, 56, 108, 55);
    fillCircle(0.1775, 28.1041, 5.6817, 56, 108, 55);
    fillCircle(0.1775, 28.2644, 5.6365, 77,115,88);
    fillCircle(0.1775, 28.0237, 5.7807, 56, 108, 55);
    fillCircle(0.1775, 28.2002, 5.7807, 77,115,88);
    fillCircle(0.1775, 28.1199, 5.8662, 77,115,88);
}
void tree2()
{
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(3.4571, 3.0553);
    glVertex2f(3.5221, 3.0553);
    glVertex2f(3.5221, 2.5207);
    glVertex2f(3.4571, 2.5207);
    glEnd();

    fillCircle(0.1924, 3.3538, 3.1383, 56, 108, 55);
    fillCircle(0.1775, 3.4761, 3.1742, 56, 108, 55);
    fillCircle(0.1775, 3.6364, 3.1289, 77,115,88);
    fillCircle(0.1775, 3.3958, 3.2731, 56, 108, 55);
    fillCircle(0.1775, 3.5723, 3.2731, 77,115,88);
    fillCircle(0.1775, 3.4920, 3.3587, 77,115,88);

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(11.5992, 3.0553);
    glVertex2f(11.6642, 3.0553);
    glVertex2f(11.6642, 2.5207);
    glVertex2f(11.5992, 2.5207);
    glEnd();

    fillCircle(0.1924, 11.4959, 3.1383, 56, 108, 55);
    fillCircle(0.1775, 11.6183, 3.1742, 56, 108, 55);
    fillCircle(0.1775, 11.7786, 3.1289, 77,115,88);
    fillCircle(0.1775, 11.5379, 3.2731, 56, 108, 55);
    fillCircle(0.1775, 11.7144, 3.2731, 77,115,88);
    fillCircle(0.1775, 11.6341, 3.3587, 77,115,88);

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(19.7032, 3.0553);
    glVertex2f(19.7682, 3.0553);
    glVertex2f(19.7682, 2.5207);
    glVertex2f(19.7032, 2.5207);
    glEnd();

    fillCircle(0.1924, 19.5999, 3.1383, 56, 108, 55);
    fillCircle(0.1775, 19.7222, 3.1742, 56, 108, 55);
    fillCircle(0.1775, 19.8825, 3.1289, 77,115,88);
    fillCircle(0.1775, 19.6419, 3.2731, 56, 108, 55);
    fillCircle(0.1775, 19.8184, 3.2731, 77,115,88);
    fillCircle(0.1775, 19.7381, 3.3587, 77,115,88);

    ///4
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(28.0850, 3.0553);
    glVertex2f(28.1501, 3.0553);
    glVertex2f(28.1501, 2.5207);
    glVertex2f(28.0850, 2.5207);
    glEnd();

    fillCircle(0.1924, 27.9818, 3.1383, 56, 108, 55);
    fillCircle(0.1775, 28.1041, 3.1742, 56, 108, 55);
    fillCircle(0.1775, 28.2644, 3.1289, 77,115,88);
    fillCircle(0.1775, 28.0237, 3.2731, 56, 108, 55);
    fillCircle(0.1775, 28.2002, 3.2731, 77,115,88);
    fillCircle(0.1775, 28.1199, 3.3587, 77,115,88);
}

void tunnnel()
{
    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(177,	195, 187);
    glVertex2f(0.0000, 5.8685);
    glVertex2f(1.3081, 5.8685);
    glVertex2f(1.7967, 2.7833);
    glVertex2f(0.0000, 2.7833);
    glEnd();

    DrawEllipse(1.3189, 4.7345, 0.6711, 1.1243, 100);
}
void tunnelX()
{
    ///Structure
    glBegin(GL_POLYGON);
    glColor3ub(177, 195, 187);
    glVertex2f(0.0000, 5.3700);
    glVertex2f(0.0000, 2.7833);
    glVertex2f(0.6532, 2.7833);
    glVertex2f(0.6532, 5.3700);
    glEnd();
}

void tunnelRoad()
{
    ///Road
    glBegin(GL_POLYGON);
    glColor3ub(52, 52, 52);
    glVertex2f(0.6532, 4.8904);
    glVertex2f(0.6532, 2.7833);
    glVertex2f(30, 2.7833);
    glVertex2f(30, 4.8904);
    glEnd();

    ///Side border
    ///1
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(255, 255, 255);
    glVertex2f(0.6532, 4.7573);
    glVertex2f(30.0000, 4.7573);
    glEnd();

    ///2
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(255, 255, 255);
    glVertex2f(0.6532, 2.9592);
    glVertex2f(30.0000, 2.9592);
    glEnd();

    ///Road Border(middle)
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(0.6532, 3.8623);
    glVertex2f(1.1532, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(1.3809, 3.8623);
    glVertex2f(1.8809, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(2.1086, 3.8623);
    glVertex2f(2.6086, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(2.8863, 3.8623);
    glVertex2f(3.3863, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(3.6140, 3.8623);
    glVertex2f(4.1140, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(4.3417, 3.8623);
    glVertex2f(4.8417, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(5.0694, 3.8623);
    glVertex2f(5.5694, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(5.7971, 3.8623);
    glVertex2f(6.2971, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(6.5248, 3.8623);
    glVertex2f(7.0248, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(7.2525, 3.8623);
    glVertex2f(7.7525, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(7.9802, 3.8623);
    glVertex2f(8.4802, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(8.7079, 3.8623);
    glVertex2f(9.2079, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(9.4356, 3.8623);
    glVertex2f(9.9356, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(10.1633, 3.8623);
    glVertex2f(10.6633, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(10.8910, 3.8623);
    glVertex2f(11.3910, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(11.6187, 3.8623);
    glVertex2f(12.1187, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(12.3464, 3.8623);
    glVertex2f(12.8464, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(13.0741, 3.8623);
    glVertex2f(13.5741, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(13.8018, 3.8623);
    glVertex2f(14.3018, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(14.5295, 3.8623);
    glVertex2f(15.0295, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(15.2572, 3.8623);
    glVertex2f(15.7572, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(15.9849, 3.8623);
    glVertex2f(16.4849, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(16.7126, 3.8623);
    glVertex2f(17.2126, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(17.4403, 3.8623);
    glVertex2f(17.9403, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(18.1680, 3.8623);
    glVertex2f(18.6680, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(18.8957, 3.8623);
    glVertex2f(19.3957, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(19.6234, 3.8623);
    glVertex2f(20.1234, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(20.3511, 3.8623);
    glVertex2f(20.8511, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(21.0788, 3.8623);
    glVertex2f(21.5788, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(21.8065, 3.8623);
    glVertex2f(22.3065, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(22.5342, 3.8623);
    glVertex2f(23.0342, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(23.2619, 3.8623);
    glVertex2f(23.7619, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(23.9896, 3.8623);
    glVertex2f(24.4896, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(24.7173, 3.8623);
    glVertex2f(25.2173, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(25.4450, 3.8623);
    glVertex2f(25.9450, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(26.1727, 3.8623);
    glVertex2f(26.6727, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(26.9004, 3.8623);
    glVertex2f(27.4004, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(27.6281, 3.8623);
    glVertex2f(28.1281, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(28.3558, 3.8623);
    glVertex2f(28.8558, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(29.0835, 3.8623);
    glVertex2f(29.5835, 3.8623);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(29.8112, 3.8623);
    glVertex2f(30.0000, 3.8623);
    glEnd();
}
void tunnelRoadX()
{
    ///Road
    glBegin(GL_POLYGON);
    glColor3ub(52, 52, 52);
    glVertex2f(0.0000, 4.8904);
    glVertex2f(0.0000, 2.7833);
    glVertex2f(0.6532, 2.7833);
    glVertex2f(0.6532, 4.8904);
    glEnd();

    ///Side border
    ///1
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(255, 255, 255);
    glVertex2f(0.6532, 4.7573);
    glVertex2f(0.0000, 4.7573);
    glEnd();

    ///2
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(255, 255, 255);
    glVertex2f(0.6532, 2.9592);
    glVertex2f(0.0000, 2.9592);
    glEnd();

    ///Road Border(middle)
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(229,221,104);
    glVertex2f(0.4255, 3.8623);
    glVertex2f(0.0000, 3.8623);
    glEnd();
}

void trafficSignal()
{
    ///1
    ///pillar
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(24.5094, 5.0202);
    glVertex2f(24.3119, 5.0202);
    glVertex2f(24.3119, 6.0993);
    glVertex2f(24.5094, 6.0993);
    glEnd();

    ///Stand
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(24.0823, 6.0908);
    glVertex2f(24.7372, 6.0993);
    glVertex2f(24.7372, 7.3086);
    glVertex2f(24.0823, 7.3086);
    glEnd();

    fillCircle(0.1233, 24.4118, 7.0636, 234, 96, 96);
    fillCircle(0.1233, 24.4118, 6.7030, 255,214,85);
    fillCircle(0.1233, 24.4118, 6.3204, 108,241,107);

    ///2
    ///pillar
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(5.5959, 2.5419);
    glVertex2f(5.3985, 2.5419);
    glVertex2f(5.3985, 3.6209);
    glVertex2f(5.5959, 3.6209);
    glEnd();

    ///Stand
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(5.1689, 3.6125);
    glVertex2f(5.8237, 3.6125);
    glVertex2f(5.8237, 4.8303);
    glVertex2f(5.1689, 4.8303);
    glEnd();

    fillCircle(0.1233, 5.4983, 4.5853, 234, 96, 96);
    fillCircle(0.1233, 5.4983, 4.2247, 255,214,85);
    fillCircle(0.1233, 5.4983, 3.8420, 108,241,107);
}

void roadLight1()
{
    ///1
    ///Pillar
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(7.5003, 5.1087);
    glVertex2f(7.3646, 5.1087);
    glVertex2f(7.3653, 6.3490);
    glVertex2f(7.5011, 6.3490);
    glEnd();

    ///ground
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(7.3130, 5.3618);
    glVertex2f(7.5470, 5.3618);
    glVertex2f(7.5470, 5.0282);
    glVertex2f(7.3130, 5.0282);
    glEnd();

    if(day)
        {
            fillCircle(0.204, 7.4235, 6.6009, 255,254,224);
        }
    else
        {
            fillCircle(0.204, 7.4235, 6.6009, 253,250,114);
        }

    ///Stand
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(7.5017, 6.3490);
    glVertex2f(7.7229, 6.6475);
    glVertex2f(7.1235, 6.6475);
    glVertex2f(7.3658, 6.3490);
    glEnd();

    ///2
    ///Pillar
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(15.6275, 5.1087);
    glVertex2f(15.4918, 5.1087);
    glVertex2f(15.4925, 6.3490);
    glVertex2f(15.6283, 6.3490);
    glEnd();

    ///ground
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(15.4402, 5.3618);
    glVertex2f(15.6742, 5.3618);
    glVertex2f(15.6742, 5.0282);
    glVertex2f(15.4402, 5.0282);
    glEnd();

    if(day)
    {
        fillCircle(0.204, 15.5507, 6.6009, 255,254,224);
    }
    else
    {
        fillCircle(0.204, 15.5507, 6.6009, 253,250,114);
    }

    ///Stand
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(15.6289, 6.3490);
    glVertex2f(15.8501, 6.6475);
    glVertex2f(15.2507, 6.6475);
    glVertex2f(15.4925, 6.3490);
    glEnd();

    ///3
    ///Pillar
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(24.0625, 5.1087);
    glVertex2f(23.9269, 5.1087);
    glVertex2f(23.9276, 6.3490);
    glVertex2f(24.0634, 6.3490);
    glEnd();

    ///ground
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(23.8752, 5.3618);
    glVertex2f(24.1092, 5.3618);
    glVertex2f(24.1092, 5.0282);
    glVertex2f(23.8752, 5.0282);
    glEnd();

    if(day)
    {
        fillCircle(0.204, 23.9857, 6.6009, 255,254,224);
    }
    else
    {
        fillCircle(0.204, 23.9857, 6.6009, 253,250,114);
    }

    ///Stand
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(24.0640, 6.3490);
    glVertex2f(24.2851, 6.6475);
    glVertex2f(23.6857, 6.6475);
    glVertex2f(23.9276, 6.3490);
    glEnd();
}
void roadLight2()
{
    ///1
    ///Pillar
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(7.5003, 2.6011);
    glVertex2f(7.3646, 2.6011);
    glVertex2f(7.3653, 3.8415);
    glVertex2f(7.5011, 3.8415);
    glEnd();

    ///ground
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(7.3130, 2.8542);
    glVertex2f(7.5470, 2.8542);
    glVertex2f(7.5470, 2.5207);
    glVertex2f(7.3130, 2.5207);
    glEnd();

    if(day)
    {
        fillCircle(0.204, 7.4235, 4.1034, 255,254,224);
    }
    else
    {
        fillCircle(0.204, 7.4235, 4.1034, 253,250,114);
    }

    ///Stand
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(7.5017, 3.8415);
    glVertex2f(7.7229, 4.1400);
    glVertex2f(7.1235, 4.1400);
    glVertex2f(7.3658, 3.8415);
    glEnd();

    ///2
    ///Pillar
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(15.6275, 2.6815);
    glVertex2f(15.4918, 2.6815);
    glVertex2f(15.4925, 3.9219);
    glVertex2f(15.6283, 3.9219);
    glEnd();

    ///ground
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(15.4402, 2.8542);
    glVertex2f(15.6742, 2.8542);
    glVertex2f(15.6742, 2.5207);
    glVertex2f(15.4402, 2.5207);
    glEnd();

    if(day)
    {
        fillCircle(0.204, 15.5507, 4.1034, 255,254,224);
    }
    else
    {
        fillCircle(0.204, 15.5507, 4.1034, 253,250,114);
    }

    ///Stand
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(15.6289, 3.8415);
    glVertex2f(15.8501, 4.1400);
    glVertex2f(15.2507, 4.1400);
    glVertex2f(15.4925, 3.8415);
    glEnd();

    ///3
    ///Pillar
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(24.0625, 2.6815);
    glVertex2f(23.9269, 2.6815);
    glVertex2f(23.9276, 3.9219);
    glVertex2f(24.0634, 3.9219);
    glEnd();

    ///ground
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(23.8752, 2.8542);
    glVertex2f(24.1092, 2.8542);
    glVertex2f(24.1092, 2.5207);
    glVertex2f(23.8752, 2.5207);
    glEnd();

    if(day)
    {
        fillCircle(0.204, 23.9857, 4.1034, 255,254,224);
    }
    else
    {
        fillCircle(0.204, 23.9857, 4.1034, 253,250,114);
    }

    ///Stand
    glBegin(GL_POLYGON);
    glColor3ub(27,34,44);
    glVertex2f(24.0640, 3.8415);
    glVertex2f(24.2851, 4.1400);
    glVertex2f(23.6857, 4.1400);
    glVertex2f(23.9276, 3.8415);
    glEnd();

}

void train()
{
    glPushMatrix();
    glTranslatef(obj_train, 0, 0);

    ///top
    glBegin(GL_POLYGON);
    glColor3ub(216,219,226);
    glVertex2f(3.6463, 1.2519);
    glVertex2f(15.0490, 1.2519);
    glVertex2f(14.9008, 0.9809);
    glVertex2f(3.3291, 0.9809);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(7);
    glColor3ub(100, 131, 215);
    glVertex2f(3.6463, 1.2519);
    glVertex2f(15.0490, 1.2519);
    glVertex2f(15.0490, 1.2519);
    glVertex2f(14.9008, 0.9809);
    glVertex2f(14.9008, 0.9809);
    glVertex2f(3.3291, 0.9809);
    glVertex2f(3.3291, 0.9809);
    glVertex2f(3.6463, 1.2519);
    glEnd();

    ///body
    glBegin(GL_POLYGON);
    glColor3ub(147,165,216);
    glVertex2f(3.3291, 0.9809);
    glVertex2f(3.1257, 0.0000);
    glVertex2f(15.2892, 0.0000);
    glVertex2f(14.9008, 0.9809);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(7);
    glColor3ub(100, 131, 215);
    glVertex2f(15.2892, 0.0000);
    glVertex2f(14.9008, 0.9809);
    glVertex2f(14.9008, 0.9809);
    glVertex2f(3.3291, 0.9809);
    glVertex2f(3.3291, 0.9809);
    glVertex2f(3.1257, 0.0000);
    glEnd();

    ///front
    glBegin(GL_POLYGON);
    glColor3ub(220, 230, 255);
    glVertex2f(15.0490, 1.2519);
    glVertex2f(15.5748, 0.0000);
    glVertex2f(15.2892, 0.0000);
    glVertex2f(14.9008, 0.9809);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(7);
    glColor3ub(100, 131, 215);
    glVertex2f(15.5748, 0.0000);
    glVertex2f(15.0490, 1.2519);
    //glVertex2f(15.0490, 1.2519);
    //glVertex2f(14.9008, 0.9809);
    //glVertex2f(14.9008, 0.9809);
    //glVertex2f(15.2892, 0.0000);
    glEnd();

    ///Shade
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(220, 230, 255);
    glVertex2f(3.2394, 0.5485);
    glVertex2f(6.7810, 0.5460);
    glVertex2f(6.7810, 0.0000);
    glVertex2f(3.1257, 0.0000);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(6.7810, 0.5460);
    glVertex2f(3.2394, 0.5485);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(220, 230, 255);
    glVertex2f(6.9904, 0.5460);
    glVertex2f(10.6545, 0.5460);
    glVertex2f(10.6545, 0.0000);
    glVertex2f(6.9904, 0.0000);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(10.6545, 0.5460);
    glVertex2f(6.9904, 0.5460);
    glEnd();

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(220, 230, 255);
    glVertex2f(10.8639, 0.5460);
    glVertex2f(15.0730, 0.5460);
    glVertex2f(15.2892, 0.0000);
    glVertex2f(10.8639, 0.0000);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(15.0730, 0.5460);
    glVertex2f(10.8639, 0.5460);
    glEnd();

    ///door
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(147,165,216);
    glVertex2f(4.8335, 0.6837);
    glVertex2f(5.4474, 0.6848);
    glVertex2f(5.4474, 0.0000);
    glVertex2f(4.8335, 0.0000);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(5.4474, 0.0000);
    glVertex2f(5.4474, 0.6848);
    glVertex2f(5.4474, 0.6848);
    glVertex2f(4.8335, 0.6837);
    glVertex2f(4.8335, 0.6837);
    glVertex2f(4.8335, 0.0000);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(147,165,216);
    glVertex2f(8.5929, 0.6777);
    glVertex2f(9.2068, 0.6777);
    glVertex2f(9.2068, 0.0000);
    glVertex2f(8.5929, 0.0000);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(9.2068, 0.0000);
    glVertex2f(9.2068, 0.6777);
    glVertex2f(9.2068, 0.6777);
    glVertex2f(8.5929, 0.6777);
    glVertex2f(8.5929, 0.6777);
    glVertex2f(8.5929, 0.0000);
    glEnd();

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(147,165,216);
    glVertex2f(12.6533, 0.6970);
    glVertex2f(13.2672, 0.6970);
    glVertex2f(13.2672, 0.0000);
    glVertex2f(12.6533, 0.0000);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(13.2672, 0.0000);
    glVertex2f(13.2672, 0.6970);
    glVertex2f(13.2672, 0.6970);
    glVertex2f(12.6533, 0.6970);
    glVertex2f(12.6533, 0.6970);
    glVertex2f(12.6533, 0.0000);
    glEnd();

    ///glass
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(220, 230, 255);
    glVertex2f(4.8988, 0.5474);
    glVertex2f(5.0643, 0.5473);
    glVertex2f(5.0643, 0.0589);
    glVertex2f(4.8988, 0.0589);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(4.8988, 0.5474);
    glVertex2f(5.0643, 0.5473);
    glVertex2f(5.0643, 0.5473);
    glVertex2f(5.0643, 0.0589);
    glVertex2f(5.0643, 0.0589);
    glVertex2f(4.8988, 0.0589);
    glVertex2f(4.8988, 0.0589);
    glVertex2f(4.8988, 0.5474);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(220, 230, 255);
    glVertex2f(5.2079, 0.5474);
    glVertex2f(5.3734, 0.5474);
    glVertex2f(5.3734, 0.0589);
    glVertex2f(5.2078, 0.0589);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(5.2079, 0.5474);
    glVertex2f(5.3734, 0.5474);
    glVertex2f(5.3734, 0.5474);
    glVertex2f(5.3734, 0.0589);
    glVertex2f(5.3734, 0.0589);
    glVertex2f(5.2078, 0.0589);
    glVertex2f(5.2078, 0.0589);
    glVertex2f(5.2079, 0.5474);
    glEnd();

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(220, 230, 255);
    glVertex2f(8.6582, 0.5460);
    glVertex2f(8.8237, 0.5460);
    glVertex2f(8.8237, 0.0589);
    glVertex2f(8.6582, 0.0589);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(8.6582, 0.5460);
    glVertex2f(8.8237, 0.5460);
    glVertex2f(8.8237, 0.5460);
    glVertex2f(8.8237, 0.0589);
    glVertex2f(8.8237, 0.0589);
    glVertex2f(8.6582, 0.0589);
    glVertex2f(8.6582, 0.0589);
    glVertex2f(8.6582, 0.5460);
    glEnd();

    ///4
    glBegin(GL_POLYGON);
    glColor3ub(220, 230, 255);
    glVertex2f(8.9674, 0.5460);
    glVertex2f(9.1328, 0.5460);
    glVertex2f(9.1328, 0.0589);
    glVertex2f(8.9674, 0.0589);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(8.9674, 0.5460);
    glVertex2f(9.1328, 0.5460);
    glVertex2f(9.1328, 0.5460);
    glVertex2f(9.1328, 0.0589);
    glVertex2f(9.1328, 0.0589);
    glVertex2f(8.9674, 0.0589);
    glVertex2f(8.9674, 0.0589);
    glVertex2f(8.9674, 0.5460);
    glEnd();

    ///5
    glBegin(GL_POLYGON);
    glColor3ub(220, 230, 255);
    glVertex2f(12.7186, 0.5460);
    glVertex2f(12.8840, 0.5460);
    glVertex2f(12.8840, 0.0589);
    glVertex2f(12.7186, 0.0589);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(12.7186, 0.5460);
    glVertex2f(12.8840, 0.5460);
    glVertex2f(12.8840, 0.5460);
    glVertex2f(12.8840, 0.0589);
    glVertex2f(12.8840, 0.0589);
    glVertex2f(12.7186, 0.0589);
    glVertex2f(12.7186, 0.0589);
    glVertex2f(12.7186, 0.5460);
    glEnd();

    ///6
    glBegin(GL_POLYGON);
    glColor3ub(220, 230, 255);
    glVertex2f(13.0277, 0.5460);
    glVertex2f(13.1932, 0.5460);
    glVertex2f(13.1932, 0.0589);
    glVertex2f(13.0277, 0.0589);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(13.0277, 0.5460);
    glVertex2f(13.1932, 0.5460);
    glVertex2f(13.1932, 0.5460);
    glVertex2f(13.1932, 0.0589);
    glVertex2f(13.1932, 0.0589);
    glVertex2f(13.0277, 0.0589);
    glVertex2f(13.0277, 0.0589);
    glVertex2f(13.0277, 0.5460);
    glEnd();

    ///Mid line
    ///1
    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(5.1392, 0.0000);
    glVertex2f(5.1392, 0.6843);
    glEnd();

    ///2
    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(8.8990, 0.0000);
    glVertex2f(8.8990, 0.6843);
    glEnd();

    ///3
    glBegin(GL_LINES);
    glLineWidth(2);
    glColor3ub(0, 0, 0);
    glVertex2f(12.9576, 0.0000);
    glVertex2f(12.9576, 0.6843);
    glEnd();


    ///Divider
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(3.6463, 1.2519);
    glVertex2f(3.7511, 1.2519);
    glVertex2f(3.4383, 0.9809);
    glVertex2f(3.3291, 0.9809);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(3.3291, 0.9809);
    glVertex2f(3.4383, 0.9809);
    glVertex2f(3.2308, 0.0000);
    glVertex2f(3.1261, 0.0000);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(7.0982, 1.2519);
    glVertex2f(7.2750, 1.2519);
    glVertex2f(6.9904, 0.9809);
    glVertex2f(6.7810, 0.9809);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(6.7810, 0.9809);
    glVertex2f(6.7810, 0.0000);
    glVertex2f(6.9904, 0.0000);
    glVertex2f(6.9904, 0.9809);
    glEnd();

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(10.9717, 1.2519);
    glVertex2f(11.1485, 1.2519);
    glVertex2f(10.8639, 0.9809);
    glVertex2f(10.6545, 0.9809);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(10.6545, 0.9809);
    glVertex2f(10.8639, 0.9809);
    glVertex2f(10.8639, 0.0000);
    glVertex2f(10.6545, 0.0000);
    glEnd();

    ///4
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(14.9681, 1.2519);
    glVertex2f(15.0490, 1.2519);
    glVertex2f(14.9008, 0.9809);
    glVertex2f(14.7916, 0.9809);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(14.7916, 0.9809);
    glVertex2f(14.9008, 0.9809);
    glVertex2f(15.2892, 0.0000);
    glVertex2f(15.1676, 0.0000);
    glEnd();

    ///Divider line
    ///1
    glBegin(GL_LINES);
    glLineWidth(8);
    glColor3ub(0, 0, 0);
    glVertex2f(7.1881, 1.2519);
    glVertex2f(6.8857, 0.9809);
    glVertex2f(6.8857, 0.9809);
    glVertex2f(6.8853, 0.0000);
    glEnd();

    ///2
    glBegin(GL_LINES);
    glLineWidth(8);
    glColor3ub(0, 0, 0);
    glVertex2f(11.0616, 1.2519);
    glVertex2f(10.7592, 0.9809);
    glVertex2f(10.7592, 0.9809);
    glVertex2f(10.7592, 0.0000);
    glEnd();

    glPopMatrix();
}
void moveTrain(int value)
{
    obj_train+= 0.08;
    if(obj_train>35)
    {
        obj_train = -20;
    }

    glutPostRedisplay();
    glutTimerFunc(15, moveTrain, 0);
}

void tunnelCar1()
{
    glPushMatrix();
    glTranslatef(obj_tunnelCar1, 0, 0);

    lineCircle(0.1198, 2.9918, 4.1631, 255, 255, 255);
    lineCircle(0.1198, 4.3450, 4.1645, 255, 255, 255);

    ///body
    glBegin(GL_POLYGON);
    glColor3ub(204,41,76);
    glVertex2f(2.8177, 4.6585);
    glVertex2f(2.4870, 4.6590);
    glVertex2f(2.6270, 4.4968);
    glVertex2f(2.6271, 4.1631);
    glVertex2f(4.7682, 4.1632);
    glVertex2f(5.0004, 4.4614);
    glVertex2f(4.8926, 4.6053);
    glVertex2f(4.3053, 4.6585);
    glVertex2f(3.8567, 5.0282);
    glVertex2f(3.1339, 5.0282);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3ub(90, 90, 90);
    glVertex2f(2.8177, 4.6585);
    glVertex2f(2.4870, 4.6590);
    glVertex2f(2.4870, 4.6590);
    glVertex2f(2.6270, 4.4968);
    glVertex2f(2.6270, 4.4968);
    glVertex2f(2.6271, 4.1631);
    glVertex2f(2.6271, 4.1631);
    glVertex2f(4.7682, 4.1632);
    glVertex2f(4.7682, 4.1632);
    glVertex2f(5.0004, 4.4614);
    glVertex2f(5.0004, 4.4614);
    glVertex2f(4.8926, 4.6053);
    glVertex2f(4.8926, 4.6053);
    glVertex2f(4.3053, 4.6585);
    glVertex2f(4.3053, 4.6585);
    glVertex2f(3.8567, 5.0282);
    glVertex2f(3.8567, 5.0282);
    glVertex2f(3.1339, 5.0282);
    glVertex2f(3.1339, 5.0282);
    glVertex2f(2.8177, 4.6585);
    glEnd();

    ///glass
    glBegin(GL_POLYGON);
    glColor3ub(216,228,233);
    glVertex2f(3.1716, 4.9610);
    glVertex2f(3.8271, 4.9605);
    glVertex2f(4.1992, 4.6585);
    glVertex2f(2.9203, 4.6585);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3ub(90, 90, 90);
    glVertex2f(3.1716, 4.9610);
    glVertex2f(3.8271, 4.9605);
    glVertex2f(3.8271, 4.9605);
    glVertex2f(4.1992, 4.6585);
    glVertex2f(4.1992, 4.6585);
    glVertex2f(2.9203, 4.6585);
    glVertex2f(2.9203, 4.6585);
    glVertex2f(3.1716, 4.9610);
    glEnd();

    ///Mid line
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(58,38,66);
    glVertex2f(3.5227, 4.9600);
    glVertex2f(3.5227, 4.6585);
    glEnd();

    drawWheel(2.9918, 4.1631, wheelAngle_tunnelCar1);
    drawWheel(4.3450, 4.1645, wheelAngle_tunnelCar1);

    glPopMatrix();

}
void moveTunnelCar1(int value)
{
    wheelAngle_tunnelCar1 -= 2;
    if(wheelAngle_tunnelCar1<=360)
    {
        wheelAngle_tunnelCar1 +=360;
    }

    obj_tunnelCar1+= 0.06;
    if(obj_tunnelCar1>30)
    {
        obj_tunnelCar1 = -10;
    }

    glutPostRedisplay();
    glutTimerFunc(10,moveTunnelCar1,0);
}

void bus1()
{
    glPushMatrix();
    glTranslatef(obj_bus1, 0, 0);

    lineCircle(0.1198, 5.1674, 5.5826, 255, 255, 255);
    lineCircle(0.1198, 7.4022, 5.5885, 255, 255, 255);

    ///Body
    glBegin(GL_POLYGON);
    glColor3ub(161,221,115);
    glVertex2f(4.7215, 6.2573);
    glVertex2f(4.6651, 6.2571);
    glVertex2f(4.6651, 5.5885);
    glVertex2f(7.9462, 5.5885);
    glVertex2f(7.9462, 6.2580);
    glVertex2f(7.8477, 6.2579);
    glVertex2f(7.8477, 6.6770);
    glVertex2f(4.7215, 6.6773);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3ub(90, 90, 90);
    glVertex2f(4.7215, 6.2573);
    glVertex2f(4.6651, 6.2571);
    glVertex2f(4.6651, 6.2571);
    glVertex2f(4.6651, 5.5885);
    glVertex2f(4.6651, 5.5885);
    glVertex2f(7.9462, 5.5885);
    glVertex2f(7.9462, 5.5885);
    glVertex2f(7.9462, 6.2580);
    glVertex2f(7.9462, 6.2580);
    glVertex2f(7.8477, 6.2579);
    glVertex2f(7.8477, 6.2579);
    glVertex2f(7.8477, 6.6770);
    glVertex2f(7.8477, 6.6770);
    glVertex2f(4.7215, 6.6773);
    glVertex2f(4.7215, 6.6773);
    glVertex2f(4.7215, 6.2573);
    glEnd();

    ///glass
    glBegin(GL_POLYGON);
    glColor3ub(216,228,233);
    glVertex2f(7.8158, 6.6285);
    glVertex2f(4.7555, 6.6285);
    glVertex2f(4.7555, 6.2581);
    glVertex2f(7.8158, 6.2581);
    glEnd();

    ///front
    glBegin(GL_POLYGON);
    glColor3ub(90, 90, 90);
    glVertex2f(7.9462, 5.8925);
    glVertex2f(7.8226, 5.8925);
    glVertex2f(7.8226, 5.7496);
    glVertex2f(7.9462, 5.7496);
    glEnd();

    ///Lines
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(161,221,115);
    glVertex2f(5.0585, 6.6285);
    glVertex2f(5.0585, 6.2581);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(161,221,115);
    glVertex2f(5.3569, 6.6285);
    glVertex2f(5.3569, 6.2581);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(161,221,115);
    glVertex2f(5.6634, 6.6285);
    glVertex2f(5.6634, 6.2581);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(161,221,115);
    glVertex2f(5.9550, 6.6285);
    glVertex2f(5.9550, 6.2581);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(161,221,115);
    glVertex2f(6.2553, 6.6285);
    glVertex2f(6.2553, 6.2581);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(161,221,115);
    glVertex2f(6.5651, 6.6285);
    glVertex2f(6.5651, 6.2581);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(161,221,115);
    glVertex2f(6.8614, 6.6285);
    glVertex2f(6.8614, 6.2581);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(161,221,115);
    glVertex2f(7.1537, 6.6285);
    glVertex2f(7.1537, 6.2581);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(161,221,115);
    glVertex2f(7.4698, 6.6285);
    glVertex2f(7.4698, 6.2581);
    glEnd();

    ///glass lines
    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3ub(90, 90, 90);
    glVertex2f(7.8158, 6.6285);
    glVertex2f(4.7555, 6.6285);
    glVertex2f(4.7555, 6.6285);
    glVertex2f(4.7555, 6.2581);
    glVertex2f(4.7555, 6.2581);
    glVertex2f(7.8158, 6.2581);
    glVertex2f(7.8158, 6.2581);
    glVertex2f(7.8158, 6.6285);
    glEnd();

    drawWheel(5.1674, 5.5826, wheelAngle_bus1);
    drawWheel(7.4022, 5.5885, wheelAngle_bus1);

    glPopMatrix();
}
void moveBus1(int value)
{
    wheelAngle_bus1 -= 2;
    if(wheelAngle_bus1<=360)
    {
        wheelAngle_bus1 +=360;
    }

    obj_bus1+= 0.06;
    if(obj_bus1>30)
    {
        obj_bus1 = -10;
    }

    glutPostRedisplay();
    glutTimerFunc(10, moveBus1, 0);
}
void bus2()
{
    glPushMatrix();
    glTranslatef(obj_bus2, 0, 0);

    lineCircle(0.1198, 20.3568, 1.4986, 255, 255, 255);
    lineCircle(0.1198, 22.6005, 1.5045, 255, 255, 255);

    ///Body
    glBegin(GL_POLYGON);
    glColor3ub(113,144,94);
    glVertex2f(19.8937, 2.1732);
    glVertex2f(19.7760, 2.1730);
    glVertex2f(19.7760, 1.5045);
    glVertex2f(23.0571, 1.5045);
    glVertex2f(23.0571, 2.1739);
    glVertex2f(23.0163, 2.1739);
    glVertex2f(23.0163, 2.5930);
    glVertex2f(19.8937, 2.5933);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3ub(90, 90, 90);
    glVertex2f(19.8937, 2.1732);
    glVertex2f(19.7760, 2.1730);
    glVertex2f(19.7760, 2.1730);
    glVertex2f(19.7760, 1.5045);
    glVertex2f(19.7760, 1.5045);
    glVertex2f(23.0571, 1.5045);
    glVertex2f(23.0571, 1.5045);
    glVertex2f(23.0571, 2.1739);
    glVertex2f(23.0571, 2.1739);
    glVertex2f(23.0163, 2.1739);
    glVertex2f(23.0163, 2.1739);
    glVertex2f(23.0163, 2.5930);
    glVertex2f(23.0163, 2.5930);
    glVertex2f(19.8937, 2.5933);
    glVertex2f(19.8937, 2.5933);
    glVertex2f(19.8937, 2.1732);
    glEnd();

    ///glass
    glBegin(GL_POLYGON);
    glColor3ub(216,228,233);
    glVertex2f(22.9898, 2.5445);
    glVertex2f(19.9295, 2.5445);
    glVertex2f(19.9295, 2.1745);
    glVertex2f(22.9898, 2.1745);
    glEnd();

    ///front
    glBegin(GL_POLYGON);
    glColor3ub(90, 90, 90);
    glVertex2f(19.8996, 1.8085);
    glVertex2f(19.7760, 1.8085);
    glVertex2f(19.7760, 1.6656);
    glVertex2f(19.8996, 1.6656);
    glEnd();

    ///Lines
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(113,144,94);
    glVertex2f(20.2325, 2.5445);
    glVertex2f(20.2325, 2.1733);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(113,144,94);
    glVertex2f(20.5309, 2.5445);
    glVertex2f(20.5309, 2.1733);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(113,144,94);
    glVertex2f(20.8375, 2.5445);
    glVertex2f(20.8375, 2.1733);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(113,144,94);
    glVertex2f(21.1290, 2.5445);
    glVertex2f(21.1290, 2.1733);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(113,144,94);
    glVertex2f(21.4293, 2.5445);
    glVertex2f(21.4293, 2.1733);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(113,144,94);
    glVertex2f(21.7392, 2.5445);
    glVertex2f(21.7392, 2.1733);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(113,144,94);
    glVertex2f(22.0355, 2.5445);
    glVertex2f(22.0355, 2.1733);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(113,144,94);
    glVertex2f(22.3278, 2.5445);
    glVertex2f(22.3278, 2.1733);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(113,144,94);
    glVertex2f(22.6304, 2.5445);
    glVertex2f(22.6304, 2.1733);
    glEnd();

    ///glass lines
    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(90, 90, 90);
    glVertex2f(22.9898, 2.5445);
    glVertex2f(19.9295, 2.5445);
    glVertex2f(19.9295, 2.5445);
    glVertex2f(19.9295, 2.1745);
    glVertex2f(19.9295, 2.1745);
    glVertex2f(22.9898, 2.1745);
    glVertex2f(22.9898, 2.1745);
    glVertex2f(22.9898, 2.5445);
    glEnd();

    drawWheel(20.3568, 1.4986, wheelAngle_bus2);
    drawWheel(22.6005, 1.5045, wheelAngle_bus2);

    glPopMatrix();
}
void moveBus2(int value)
{
    wheelAngle_bus2 += 2;
    if(wheelAngle_bus2<=360)
    {
        wheelAngle_bus2 -=360;
    }

    obj_bus2-= 0.07;
    if(obj_bus2<-30)
    {
        obj_bus2 = 10;
    }
    glutPostRedisplay();
    glutTimerFunc(10, moveBus2, 0);
}

void tunnelCar2()
{
    glPushMatrix();
    glTranslatef(obj_tunnelCar2, 0, 0);

    lineCircle(0.1198, 9.1964, 3.2371, 255, 255, 255);
    lineCircle(0.1198, 10.5833, 3.2378, 255, 255, 255);

    ///body
    glBegin(GL_POLYGON);
    ///glColor3ub(36,165,181);
    glColor3ub(246,138,128);
    glVertex2f(9.2066, 3.7317);
    glVertex2f(8.6614, 3.6483);
    glVertex2f(8.5258, 3.5467);
    glVertex2f(8.6721, 3.2363);
    glVertex2f(10.9040, 3.2390);
    glVertex2f(10.9040, 3.5804);
    glVertex2f(11.0283, 3.7317);
    glVertex2f(10.6942, 3.7317);
    glVertex2f(10.4181, 4.1015);
    glVertex2f(9.7449, 4.1015);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3ub(90, 90, 90);
    glVertex2f(9.2066, 3.7317);
    glVertex2f(8.6614, 3.6483);
    glVertex2f(8.6614, 3.6483);
    glVertex2f(8.5258, 3.5467);
    glVertex2f(8.5258, 3.5467);
    glVertex2f(8.6721, 3.2363);
    glVertex2f(8.6721, 3.2363);
    glVertex2f(10.9040, 3.2390);
    glVertex2f(10.9040, 3.2390);
    glVertex2f(10.9040, 3.5804);
    glVertex2f(10.9040, 3.5804);
    glVertex2f(11.0283, 3.7317);
    glVertex2f(11.0283, 3.7317);
    glVertex2f(10.6942, 3.7317);
    glVertex2f(10.6942, 3.7317);
    glVertex2f(10.4181, 4.1015);
    glVertex2f(10.4181, 4.1015);
    glVertex2f(9.7449, 4.1015);
    glVertex2f(9.7449, 4.1015);
    glVertex2f(9.2066, 3.7317);
    glEnd();

    ///Glass
    glBegin(GL_POLYGON);
    glColor3ub(216,228,233);
    glVertex2f(9.7512, 4.0154);
    glVertex2f(10.3919, 4.0151);
    glVertex2f(10.5981, 3.7317);
    glVertex2f(9.3179, 3.7317);
    glEnd();

    ///Mid line
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(36,165,181);
    glVertex2f(10.0916, 4.0152);
    glVertex2f(10.0916, 3.7317);
    glEnd();

    ///glass line
    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3ub(90, 90, 90);
    glVertex2f(9.7512, 4.0154);
    glVertex2f(10.3919, 4.0151);
    glVertex2f(10.3919, 4.0151);
    glVertex2f(10.5981, 3.7317);
    glVertex2f(10.5981, 3.7317);
    glVertex2f(9.3179, 3.7317);
    glVertex2f(9.3179, 3.7317);
    glVertex2f(9.7512, 4.0154);
    glEnd();

    drawWheel(9.1964, 3.2371, wheelAngle_tunnelCar2);
    drawWheel(10.5833, 3.2378, wheelAngle_tunnelCar2);

    glPopMatrix();
}
void movetunnelCar2(int value)
{
    wheelAngle_tunnelCar2 += 2;
    if(wheelAngle_tunnelCar2<=360)
    {
        wheelAngle_tunnelCar2 -=360;
    }

    obj_tunnelCar2-= 0.06;
    if(obj_tunnelCar2<-15)
    {
        obj_tunnelCar2 = 25;
    }

    glutPostRedisplay();
    glutTimerFunc(10, movetunnelCar2, 0);
}

void car2()
{
    glPushMatrix();
    glTranslatef(obj_car2, 0, 0);

    lineCircle(0.1198, 7.5701, 1.5139, 255, 255, 255);
    lineCircle(0.1198, 8.9570, 1.5146, 255, 255, 255);

    ///body
    glBegin(GL_POLYGON);
    ///glColor3ub(158,102,119);
    glColor3ub(115,111,170);
    glVertex2f(7.5803, 2.0085);
    glVertex2f(7.0351, 1.9251);
    glVertex2f(6.8995, 1.8235);
    glVertex2f(7.0458, 1.5131);
    glVertex2f(9.2776, 1.5158);
    glVertex2f(9.2776, 1.8572);
    glVertex2f(9.4020, 2.0085);
    glVertex2f(9.0679, 2.0085);
    glVertex2f(8.7918, 2.3783);
    glVertex2f(8.1186, 2.3783);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3ub(90, 90, 90);
    glVertex2f(7.5803, 2.0085);
    glVertex2f(7.0351, 1.9251);
    glVertex2f(7.0351, 1.9251);
    glVertex2f(6.8995, 1.8235);
    glVertex2f(6.8995, 1.8235);
    glVertex2f(7.0458, 1.5131);
    glVertex2f(7.0458, 1.5131);
    glVertex2f(9.2776, 1.5158);
    glVertex2f(9.2776, 1.5158);
    glVertex2f(9.2776, 1.8572);
    glVertex2f(9.2776, 1.8572);
    glVertex2f(9.4020, 2.0085);
    glVertex2f(9.4020, 2.0085);
    glVertex2f(9.0679, 2.0085);
    glVertex2f(9.0679, 2.0085);
    glVertex2f(8.7918, 2.3783);
    glVertex2f(8.7918, 2.3783);
    glVertex2f(8.1186, 2.3783);
    glVertex2f(8.1186, 2.3783);
    glVertex2f(7.5803, 2.0085);
    glEnd();

    ///Glass
    glBegin(GL_POLYGON);
    glColor3ub(216,228,233);
    glVertex2f(8.1248, 2.2922);
    glVertex2f(8.7656, 2.2919);
    glVertex2f(8.9717, 2.0085);
    glVertex2f(7.6916, 2.0085);
    glEnd();

    ///Mid line
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(158,102,119);
    glVertex2f(8.4653, 2.2920 );
    glVertex2f(8.4653, 2.0085);
    glEnd();

    ///glass lines
    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3ub(90, 90, 90);
    glVertex2f(8.1248, 2.2922);
    glVertex2f(8.7656, 2.2919);
    glVertex2f(8.7656, 2.2919);
    glVertex2f(8.9717, 2.0085);
    glVertex2f(8.9717, 2.0085);
    glVertex2f(7.6916, 2.0085);
    glVertex2f(7.6916, 2.0085);
    glVertex2f(8.1248, 2.2922);
    glEnd();

    drawWheel(7.5701, 1.5139, wheelAngle_car2);
    drawWheel(8.9570, 1.5146, wheelAngle_car2);

    glPopMatrix();
}
void moveCar2(int value)
{
    wheelAngle_car2 += 2;
    if(wheelAngle_car2<=360)
    {
        wheelAngle_car2 -=360;
    }

    obj_car2-= 0.07;
    if(obj_car2<-15)
    {
        obj_car2 = 25;
    }

    glutPostRedisplay();
    glutTimerFunc(10, moveCar2, 0);
}

void car1()
{
    glPushMatrix();
    glTranslatef(obj_car1, 0, 0);

    lineCircle(0.1198, 23.6694, 5.6643, 255, 255, 255);
    lineCircle(0.1198, 25.0226, 5.6657, 255, 255, 255);

    ///body
    glBegin(GL_POLYGON);
    glColor3ub(80,166,197);
    glVertex2f(23.4953, 6.1597);
    glVertex2f(23.1646, 6.1602 );
    glVertex2f(23.3046, 5.9980);
    glVertex2f(23.3046, 5.6643);
    glVertex2f(25.4458, 5.6644);
    glVertex2f(25.6779, 5.9626);
    glVertex2f(25.5702, 6.1066);
    glVertex2f(24.9828, 6.1597);
    glVertex2f(24.5343, 6.5294);
    glVertex2f(23.8115, 6.5294);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3ub(90, 90, 90);
    glVertex2f(23.4953, 6.1597);
    glVertex2f(23.1646, 6.1602);
    glVertex2f(23.1646, 6.1602);
    glVertex2f(23.3046, 5.9980);
    glVertex2f(23.3046, 5.9980);
    glVertex2f(23.3046, 5.6643);
    glVertex2f(23.3046, 5.6643);
    glVertex2f(25.4458, 5.6644);
    glVertex2f(25.4458, 5.6644);
    glVertex2f(25.6779, 5.9626);
    glVertex2f(25.6779, 5.9626);
    glVertex2f(25.5702, 6.1066);
    glVertex2f(25.5702, 6.1066);
    glVertex2f(24.9828, 6.1597);
    glVertex2f(24.9828, 6.1597);
    glVertex2f(24.5343, 6.5294);
    glVertex2f(24.5343, 6.5294);
    glVertex2f(23.8115, 6.5294);
    glVertex2f(23.8115, 6.5294);
    glVertex2f(23.4953, 6.1597);
    glEnd();

    ///Glass
    glBegin(GL_POLYGON);
    glColor3ub(216,228,233);
    glVertex2f(23.8492, 6.4622);
    glVertex2f(24.5047, 6.4617);
    glVertex2f(24.8767, 6.1597);
    glVertex2f(23.5979, 6.1597);
    glEnd();

    ///Mid line
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(80,166,197);
    glVertex2f(24.2002, 6.4612);
    glVertex2f(24.2002, 6.1597);
    glEnd();

    ///glass lines
    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3ub(90, 90, 90);
    glVertex2f(23.8492, 6.4622);
    glVertex2f(24.5047, 6.4617);
    glVertex2f(24.5047, 6.4617);
    glVertex2f(24.8767, 6.1597);
    glVertex2f(24.8767, 6.1597);
    glVertex2f(23.5979, 6.1597);
    glVertex2f(23.5979, 6.1597);
    glVertex2f(23.8492, 6.4622);
    glEnd();

    drawWheel(23.6694, 5.6643, wheelAngle_car1);
    drawWheel(25.0226, 5.6657, wheelAngle_car1);

    glPopMatrix();
}
void moveCar1(int value)
{
    wheelAngle_car1 -= 2;
    if(wheelAngle_car1<=360)
    {
        wheelAngle_car1 +=360;
    }

    obj_car1+= 0.06;
    if(obj_car1>10)
    {
        obj_car1 = -30;
    }

    glutPostRedisplay();
    glutTimerFunc(10, moveCar1, 0);
}

void tunnelBus1()
{
    glPushMatrix();
    glTranslatef(obj_tunnelBus1, 0, 0);

    lineCircle(0.1198, 15.8332, 4.1896, 255, 255, 255);
    lineCircle(0.1198, 18.0680, 4.1955, 255, 255, 255);

    ///Body
    glBegin(GL_POLYGON);
    glColor3ub(77,103,118);
    glVertex2f(15.3309, 4.1955);
    glVertex2f(18.6120, 4.1955);
    glVertex2f(18.6120, 4.8650);
    glVertex2f(18.5135, 4.8649);
    glVertex2f(18.5135, 5.2840);
    glVertex2f(15.3873, 5.2843);
    glVertex2f(15.3873, 4.8643);
    glVertex2f(15.3309, 4.8641);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3ub(90, 90, 90);
    glVertex2f(15.3309, 4.1955);
    glVertex2f(18.6120, 4.1955);
    glVertex2f(18.6120, 4.1955);
    glVertex2f(18.6120, 4.8650);
    glVertex2f(18.6120, 4.8650);
    glVertex2f(18.5135, 4.8649);
    glVertex2f(18.5135, 4.8649);
    glVertex2f(18.5135, 5.2840);
    glVertex2f(18.5135, 5.2840);
    glVertex2f(15.3873, 5.2843);
    glVertex2f(15.3873, 5.2843);
    glVertex2f(15.3873, 4.8643);
    glVertex2f(15.3873, 4.8643);
    glVertex2f(15.3309, 4.8641);
    glVertex2f(15.3309, 4.8641);
    glVertex2f(15.3309, 4.1955);
    glEnd();

    ///glass
    glBegin(GL_POLYGON);
    glColor3ub(216,228,233);
    glVertex2f(18.4816, 5.2355);
    glVertex2f(15.4213, 5.2353);
    glVertex2f(15.4210, 4.8643);
    glVertex2f(18.4816, 4.8652);
    glEnd();

    ///front
    glBegin(GL_POLYGON);
    glColor3ub(90, 90, 90);
    glVertex2f(18.6120, 4.4995);
    glVertex2f(18.4884, 4.4995);
    glVertex2f(18.4884, 4.3566);
    glVertex2f(18.6120, 4.3566);
    glEnd();

    ///Lines
    ///1
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(77,103,118);
    glVertex2f(15.7243, 5.2354);
    glVertex2f(15.7243, 4.8650);
    glEnd();

    ///2
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(77,103,118);
    glVertex2f(16.0227, 5.2354);
    glVertex2f(16.0227, 4.8650);
    glEnd();

    ///3
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(77,103,118);
    glVertex2f(16.3292, 5.2354);
    glVertex2f(16.3292, 4.8650);
    glEnd();

    ///4
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(77,103,118);
    glVertex2f(16.6208, 5.2354);
    glVertex2f(16.6208, 4.8650);
    glEnd();

    ///5
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(77,103,118);
    glVertex2f(16.9211, 5.2354);
    glVertex2f(16.9211, 4.8650);
    glEnd();

    ///6
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(77,103,118);
    glVertex2f(17.2310, 5.2354);
    glVertex2f(17.2310, 4.8650);
    glEnd();

    ///7
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(77,103,118);
    glVertex2f(17.5272, 5.2354);
    glVertex2f(17.5272, 4.8650);
    glEnd();

    ///8
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(77,103,118);
    glVertex2f(17.8196, 5.2354);
    glVertex2f(17.8196, 4.8650);
    glEnd();

    ///9
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(77,103,118);
    glVertex2f(18.1356, 5.2354);
    glVertex2f(18.1356, 4.8650);
    glEnd();

    ///glass lines
    glBegin(GL_LINES);
    glLineWidth(7);
    glColor3ub(90, 90, 90);
    glVertex2f(18.4816, 5.2355);
    glVertex2f(15.4213, 5.2353);
    glVertex2f(15.4213, 5.2353);
    glVertex2f(15.4210, 4.8643);
    glVertex2f(15.4210, 4.8643);
    glVertex2f(18.4816, 4.8652);
    glVertex2f(18.4816, 4.8652);
    glVertex2f(18.4816, 5.2355);
    glEnd();

    drawWheel(15.8332, 4.1896, wheelAngle_tunnelBus1);
    drawWheel(18.0680, 4.1955, wheelAngle_tunnelBus1);

    glPopMatrix();
}
void moveTunnelBus1(int value)
{
    wheelAngle_tunnelBus1 -= 2;
    if(wheelAngle_tunnelBus1<=360)
    {
        wheelAngle_tunnelBus1 +=360;
    }

    obj_tunnelBus1+= 0.06;
    if(obj_tunnelBus1>20)
    {
        obj_tunnelBus1 = -20;
    }

    glutPostRedisplay();
    glutTimerFunc(10, moveTunnelBus1, 0);
}

void tunnelBus2()
{
    glPushMatrix();
    glTranslatef(obj_tunnelBus2, 0, 0);

    lineCircle(0.1198, 26.9643, 3.2379, 255, 255, 255);
    lineCircle(0.1198, 29.2080, 3.2438, 255, 255, 255);

    ///Body
    glBegin(GL_POLYGON);
    glColor3ub(180,167,126);
    glVertex2f(26.5012, 3.9125);
    glVertex2f(26.3835, 3.9124);
    glVertex2f(26.3835, 3.2438);
    glVertex2f(29.6646, 3.2438);
    glVertex2f(29.6646, 3.9133);
    glVertex2f(29.6238, 3.9132);
    glVertex2f(29.6238, 4.3323);
    glVertex2f(26.5012, 4.3326);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(4);
    glColor3ub(90, 90, 90);
    glVertex2f(26.5012, 3.9125);
    glVertex2f(26.3835, 3.9124);
    glVertex2f(26.3835, 3.9124);
    glVertex2f(26.3835, 3.2438);
    glVertex2f(26.3835, 3.2438);
    glVertex2f(29.6646, 3.2438);
    glVertex2f(29.6646, 3.2438);
    glVertex2f(29.6646, 3.9133);
    glVertex2f(29.6646, 3.9133);
    glVertex2f(29.6238, 3.9132);
    glVertex2f(29.6238, 3.9132);
    glVertex2f(29.6238, 4.3323);
    glVertex2f(29.6238, 4.3323);
    glVertex2f(26.5012, 4.3326);
    glVertex2f(26.5012, 4.3326);
    glVertex2f(26.5012, 3.9125);
    glEnd();

    ///glass
    glBegin(GL_POLYGON);
    glColor3ub(216,228,233);
    glVertex2f(29.5674, 4.2838);
    glVertex2f(26.5370, 4.2838);
    glVertex2f(26.5368, 3.9126);
    glVertex2f(29.5674, 3.9126);
    glEnd();

    ///front
    glBegin(GL_POLYGON);
    glColor3ub(90, 90, 90);
    glVertex2f(26.5071, 3.5297);
    glVertex2f(26.3835, 3.5297);
    glVertex2f(26.3835, 3.3867);
    glVertex2f(26.5071, 3.3867);
    glEnd();

    ///Lines
    ///1
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(180,167,126);
    glVertex2f(26.8400, 4.2838);
    glVertex2f(26.8400, 3.9126);
    glEnd();

    ///2
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(180,167,126);
    glVertex2f(27.1385, 4.2838);
    glVertex2f(27.1385, 3.9126);
    glEnd();

    ///3
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(180,167,126);
    glVertex2f(27.4450, 4.2838);
    glVertex2f(27.4450, 3.9126);
    glEnd();

    ///4
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(180,167,126);
    glVertex2f(27.7366, 4.2838);
    glVertex2f(27.7366, 3.9126);
    glEnd();

    ///5
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(180,167,126);
    glVertex2f(28.0369, 4.2838);
    glVertex2f(28.0369, 3.9126);
    glEnd();

    ///6
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(180,167,126);
    glVertex2f(28.3467, 4.2838);
    glVertex2f(28.3467, 3.9126);
    glEnd();

    ///7
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(180,167,126);
    glVertex2f(28.6430, 4.2838);
    glVertex2f(28.6430, 3.9126);
    glEnd();

    ///8
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(180,167,126);
    glVertex2f(28.9353, 4.2838);
    glVertex2f(28.9353, 3.9126);
    glEnd();

    ///9
    glBegin(GL_LINES);
    glLineWidth(15);
    glColor3ub(180,167,126);
    glVertex2f(29.2379, 4.2838);
    glVertex2f(29.2379, 3.9126);
    glEnd();

    ///glass lines
    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(90, 90, 90);
    glVertex2f(29.5674, 4.2838);
    glVertex2f(26.5370, 4.2836);
    glVertex2f(26.5370, 4.2836);
    glVertex2f(26.5368, 3.9126);
    glVertex2f(26.5368, 3.9126);
    glVertex2f(29.5674, 3.9134);
    glVertex2f(29.5674, 3.9134);
    glVertex2f(29.5674, 4.2838);
    glEnd();

    drawWheel(26.9643, 3.2379, wheelAngle_tunnelBus2);
    drawWheel(29.2080, 3.2438, wheelAngle_tunnelBus2);

    glPopMatrix();
}
void movetunnelBus2(int value)
{
    wheelAngle_tunnelBus2 += 2;
    if(wheelAngle_tunnelBus2<=360)
    {
        wheelAngle_tunnelBus2 -=360;
    }

    obj_tunnelBus2-= 0.06;
    if(obj_tunnelBus2<-35)
    {
        obj_tunnelBus2 = 5;
    }

    glutPostRedisplay();
    glutTimerFunc(10, movetunnelBus2, 0);
}

void river()
{
    glPushMatrix();
    glTranslatef(0, obj_water, 0);

    glBegin(GL_POLYGON);
    if(day)
    {
        glColor3ub(0,134,173);
    }
    else
    {
        glColor3ub(0,70,96);

    }
    glVertex2f(0.0000, 10.1563);
    glVertex2f(30.0000, 10.1563);
    if(day)
    {
        glColor3ub(51,182,193);
    }
    else
    {
        glColor3ub(51,182,193);
    }
    glVertex2f(30.0000, 7.0733);
    glVertex2f(0.0000, 7.0733);
    glEnd();

    glPopMatrix();
}
void moveWater(int value)
{
    obj_water-= obj_waterSpeed;
    if(obj_water>0 || obj_water<-0.07)
    {
        obj_waterSpeed *=-1;
    }

    glutPostRedisplay();
    glutTimerFunc(10, moveWater, 0);
}

void grass2()
{
    glBegin(GL_POLYGON);
    if(day)
    {
        glColor3ub(68, 163, 24);
    }
    else
    {
        glColor3ub(66,122,107);
    }
    glVertex2f(0.0000, 10.0000);
    glVertex2f(30.0000, 10.0000);
    glVertex2f(30.0000, 10.2157);
    glVertex2f(0.0000, 10.2157);
    glEnd();

    glBegin(GL_POLYGON);
    if(day)
    {
        glColor3ub(68, 163, 24);
    }
    else
    {
        glColor3ub(66,122,107);
    }
    glVertex2f(0.0000, 7.0733);
    glVertex2f(30.0000, 7.0733);
    glVertex2f(30.0000, 6.7870);
    glVertex2f(0.0000, 6.7870);
    glEnd();
}

void ghat()
{
    glBegin(GL_POLYGON);
    glColor3ub(63, 60, 81);
    glVertex2f(14.3791, 7.5261);
    glVertex2f(14.7813, 7.5261);
    glVertex2f(15.0896, 6.7870);
    glVertex2f(14.0708, 6.7870);
    glEnd();

    ///Human
    fillCircle(0.1455,14.5934, 7.5832, 49,49,49);
    fillCircle(0.1455,14.5950, 7.5398, 241,194,125);

    ///body
    glBegin(GL_POLYGON);
    glColor3ub(107,42,58);
    glVertex2f(14.4514, 7.4849);
    glVertex2f(14.7435, 7.4849);
    glVertex2f(14.7435, 7.3063);
    glVertex2f(14.4514, 7.3063);
    glEnd();

    ///legs
    glBegin(GL_POLYGON);
    glColor3ub(41,23,23);
    glVertex2f(14.4514, 7.3063);
    glVertex2f(14.5509, 7.3063);
    glVertex2f(14.5201, 7.0733);
    glVertex2f(14.4514, 7.0733);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(41,23,23);
    glVertex2f(14.6270, 7.3063);
    glVertex2f(14.7435, 7.3063);
    glVertex2f(14.7435, 7.0733);
    glVertex2f(14.6736, 7.0733);
    glEnd();

    ///hands
    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(241,194,125);
    glVertex2f(14.4514, 7.4849);
    glVertex2f(14.4048, 7.3995);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(20);
    glColor3ub(241,194,125);
    glVertex2f(14.7435, 7.4849);
    glVertex2f(14.7907, 7.3995);
    glEnd();
}

void boat1()
{
    glPushMatrix();
    glTranslatef(obj_boat1, 0, 0);

    ///body
    glBegin(GL_POLYGON);
    glColor3ub(228,199,119);
    glVertex2f(6.2349, 9.7470);
    glVertex2f(9.7173, 9.7471);
    glVertex2f(9.4959, 9.2792);
    glVertex2f(6.4806, 9.2779);
    glEnd();

    ///lower body
    glBegin(GL_POLYGON);
    glColor3ub(48,177,206);
    glVertex2f(6.4806, 9.2779);
    glVertex2f(9.4959, 9.2779);
    glVertex2f(9.5197, 9.3294);
    glVertex2f(6.4536, 9.3294);
    glEnd();

    ///Stripe
    glBegin(GL_POLYGON);
    glColor3ub(74,74,74);
    glVertex2f(6.3303, 9.5649);
    glVertex2f(9.6308, 9.5649);
    glVertex2f(9.5980, 9.4949);
    glVertex2f(6.3670, 9.4949);
    glEnd();

    ///stick
    glBegin(GL_POLYGON);
    glColor3ub(74,74,74);
    glVertex2f(7.7114, 10.7145);
    glVertex2f(7.7434, 10.7145);
    glVertex2f(7.7434, 9.7470);
    glVertex2f(7.7114, 9.7470);
    glEnd();

    ///up
    glBegin(GL_POLYGON);
    glColor3ub(245,241,230);
    glVertex2f(7.7106, 9.9425);
    glVertex2f(7.7114, 10.7145);
    glVertex2f(7.3455, 9.9419);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(245,241,230);
    glVertex2f(7.9752, 9.9428);
    glVertex2f(7.7434, 11.0890);
    glVertex2f(7.7434, 9.7470);
    glEnd();

    glPopMatrix();
}
void moveBoat1(int value)
{
    obj_boat1-= 0.008;
    if(obj_boat1<-10)
    {
        obj_boat1= 25;
    }

    glutPostRedisplay();
    glutTimerFunc(10, moveBoat1, 0);
}

void boat2()
{
    glPushMatrix();
    glTranslatef(obj_boat2, 0, 0);

    ///body
    glBegin(GL_POLYGON);
    glColor3ub(184,92,92);
    glVertex2f(20.4365, 9.4958);
    glVertex2f(23.9190, 9.4959);
    glVertex2f(23.6975, 9.0279);
    glVertex2f(20.6823, 9.0267);
    glEnd();

    ///lower body
    glBegin(GL_POLYGON);
    ///glColor3ub(41,164,195);
    glColor3ub(48,177,206);
    glVertex2f(20.6823, 9.0267);
    glVertex2f(23.6975, 9.0267);
    glVertex2f(23.7213, 9.0782);
    glVertex2f(20.6553, 9.0782);
    glEnd();

    ///Stripe
    glBegin(GL_POLYGON);
    glColor3ub(74,74,74);
    glVertex2f(20.5255, 9.3260);
    glVertex2f(23.8383, 9.3254);
    glVertex2f(23.8054, 9.2560);
    glVertex2f(20.5622, 9.2560);
    glEnd();

    ///stick
    glBegin(GL_POLYGON);
    glColor3ub(74,74,74);
    glVertex2f(21.9132, 10.4623);
    glVertex2f(21.9452, 10.4623);
    glVertex2f(21.9452, 9.4948);
    glVertex2f(21.9132, 9.4948);
    glEnd();

    ///up
    glBegin(GL_POLYGON);
    glColor3ub(245,241,230);
    glVertex2f(21.9125, 9.6884);
    glVertex2f(21.9132, 10.4623);
    glVertex2f(21.3864, 9.6903);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(245,241,230);
    glVertex2f(22.1771, 9.6906);
    glVertex2f( 21.9452, 10.8368);
    glVertex2f(21.9452, 9.4948);
    glEnd();

    glPopMatrix();
}
void moveBoat2(int value)
{
    obj_boat2-= 0.007;
    if(obj_boat2<-25)
    {
        obj_boat2= 10;
    }

    glutPostRedisplay();
    glutTimerFunc(10, moveBoat2, 0);
}

void ship()
{
    glPushMatrix();
    glTranslatef(obj_ship, 0, 0);

    ///body
    glBegin(GL_POLYGON);
    //glColor3ub(19,66,109);
    glColor3ub(23,87,126);
    glVertex2f(11.7431, 8.4704);
    glVertex2f(17.5483, 8.2571);
    glVertex2f(17.5483, 7.4699);
    glVertex2f(13.1359, 7.4699);
    glEnd();

    ///lower body
    glBegin(GL_POLYGON);
    ///glColor3ub(38,173,184);
    glColor3ub(75,161,174);
    glVertex2f(12.7865, 7.7209);
    glVertex2f(17.5483, 7.5999);
    glVertex2f(17.5483, 7.4699);
    glVertex2f(13.1359, 7.4699);
    glEnd();

    fillCircle(0.1090, 13.0294, 8.2286, 74,74,74);
    fillCircle(0.1090, 13.9687, 8.1782, 74,74,74);
    fillCircle(0.1090, 14.9265, 8.1570, 74,74,74);
    fillCircle(0.1090, 15.8401, 8.1341, 74,74,74);
    fillCircle(0.1090, 16.8153, 8.0999, 74,74,74);

    ///lower deck
    glBegin(GL_POLYGON);
    glColor3ub(255,251,244);
    glVertex2f(12.9006, 9.0114);
    glVertex2f(16.5720, 9.0114);
    glVertex2f(16.5720, 8.2930);
    glVertex2f(12.9014, 8.4279);
    glEnd();

    ///glass
    glBegin(GL_POLYGON);
    glColor3ub(182,213,235);
    glVertex2f(13.1316, 8.8198);
    glVertex2f(16.3606, 8.8198);
    glVertex2f(16.3606, 8.5402);
    glVertex2f(13.1316, 8.5402);
    glEnd();

    ///Stripe
    glBegin(GL_POLYGON);
    glColor3ub(74,74,74);
    glVertex2f(12.8553, 9.0600);
    glVertex2f(16.6086, 9.0600);
    glVertex2f(16.6086, 9.0114);
    glVertex2f(12.8553, 9.0114);
    glEnd();

    ///upper deck
    glBegin(GL_POLYGON);
    glColor3ub(255,251,244);
    glVertex2f(13.6486, 9.4368);
    glVertex2f(15.8921, 9.4368);
    glVertex2f(15.8921, 9.0600);
    glVertex2f(13.6486, 9.0600);
    glEnd();

    ///upper glass
    glBegin(GL_POLYGON);
    glColor3ub(182,213,235);
    glVertex2f(13.8797, 9.3325);
    glVertex2f(15.6218, 9.3325);
    glVertex2f(15.6218, 9.1568);
    glVertex2f(13.8797, 9.1568);
    glEnd();

    ///upper stripe
    glBegin(GL_POLYGON);
    glColor3ub(74,74,74);
    glVertex2f(13.6033, 9.4753);
    glVertex2f(15.9392, 9.4753);
    glVertex2f(15.9392, 9.4368);
    glVertex2f(13.6033, 9.4368);
    glEnd();

    ///Stick
    glBegin(GL_POLYGON);
    glColor3ub(74,74,74);
    glVertex2f(14.7524, 10.0624);
    glVertex2f(14.7844, 10.0628);
    glVertex2f(14.7844, 9.4753);
    glVertex2f(14.7524, 9.4753);
    glEnd();

    ///flag
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(14.7844, 10.0628);
    glVertex2f(15.2689, 10.0628);
    glVertex2f(15.2689, 9.8574);
    glVertex2f(14.7844, 9.8574);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(14.7844, 10.0628);
    glVertex2f(15.2689, 10.0628);
    glVertex2f(15.2689, 9.9964);
    glVertex2f(14.7844, 9.9964);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(48,104,68);
    glVertex2f(14.7844, 9.9290);
    glVertex2f(15.2689, 9.9290);
    glVertex2f(15.2689, 9.8574);
    glVertex2f(14.7844, 9.8574);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);
    glVertex2f(14.9132, 9.9614);
    glVertex2f(14.7844, 10.0628);
    glVertex2f(14.7844, 9.8627);
    glEnd();

    glPopMatrix();
}
void moveShip(int value)
{
    if(shipForward)
    {
        obj_ship-= 0.02;
        if(obj_ship<-20)
        {
            obj_ship = 20;
        }
    }
    else if(shipBackward)
    {
        obj_ship+= 0.02;
        if(obj_ship>20)
        {
            obj_ship = -20;
        }
    }
    else
    {
        obj_ship-= obj_shipSpeed;
        if(obj_ship>0.04 || obj_ship<-0.04)
        {
            obj_shipSpeed *=-1;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(10, moveShip, 0);
}

void mountain()
{
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(95,99,80);
    glVertex2f(-0.0818, 11.2556);
    glVertex2f(1.3656, 10.2157);
    glVertex2f(-1.7265, 10.2157);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(95,99,80);
    glVertex2f(1.6447, 11.2556);
    glVertex2f(3.0921, 10.2157);
    glVertex2f(0.0000, 10.2157);
    glEnd();

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(95,99,80);
    glVertex2f(3.5328, 11.2556);
    glVertex2f(4.9802, 10.2157);
    glVertex2f(1.8881, 10.2157);
    glEnd();

    ///4
    glBegin(GL_POLYGON);
    glColor3ub(95,99,80);
    glVertex2f(5.5504, 11.2556);
    glVertex2f(6.9978, 10.2157);
    glVertex2f(3.9057, 10.2157);
    glEnd();

    ///5
    glBegin(GL_POLYGON);
    ///glColor3ub(177,196,216);
    glColor3ub(95,99,80);
    glVertex2f(7.6281, 11.2556);
    glVertex2f(9.0754, 10.2157);
    glVertex2f(5.9833, 10.2157);
    glEnd();


    ///6
    glBegin(GL_POLYGON);
    glColor3ub(95,99,80);
    glVertex2f(9.7061, 11.2556);
    glVertex2f(11.2955, 10.2157);
    glVertex2f(8.1179, 10.2157);
    glEnd();

    ///7
    glBegin(GL_POLYGON);
    glColor3ub(95,99,80);
    glVertex2f(11.9792, 11.2556);
    glVertex2f(13.4266, 10.2157);
    glVertex2f(10.3345, 10.2157);
    glEnd();

    ///8
    glBegin(GL_POLYGON);
    glColor3ub(95,99,80);
    glVertex2f(14.1433, 11.2556);
    glVertex2f(15.5907, 10.2157);
    glVertex2f(12.4986, 10.2157);
    glEnd();

    ///9
    glBegin(GL_POLYGON);
    glColor3ub(95,99,80);
    glVertex2f(16.2656, 11.2556);
    glVertex2f(17.7130, 10.2157);
    glVertex2f(14.6209, 10.2157);
    glEnd();

    ///10
    glBegin(GL_POLYGON);
    glColor3ub(95,99,80);
    glVertex2f(18.4099, 11.2556);
    glVertex2f(19.8572, 10.2157);
    glVertex2f(16.7652, 10.2157);
    glEnd();

    ///11
    glBegin(GL_POLYGON);
    glColor3ub(95,99,80);
    glVertex2f(20.4968, 11.2556);
    glVertex2f(21.9441, 10.2157);
    glVertex2f(18.8521, 10.2157);
    glEnd();

    ///12
    glBegin(GL_POLYGON);
    glColor3ub(95,99,80);
    glVertex2f(22.6121, 11.2556);
    glVertex2f(24.0594, 10.2157);
    glVertex2f(20.9673, 10.2157);
    glEnd();

    ///13
    glBegin(GL_POLYGON);
    glColor3ub(95,99,80);
    glVertex2f(24.5709, 11.2556);
    glVertex2f(26.0182, 10.2157);
    glVertex2f(22.9262, 10.2157);
    glEnd();

    ///14
    glBegin(GL_POLYGON);
    glColor3ub(95,99,80);
    glVertex2f(26.6200, 11.2556);
    glVertex2f(28.0673, 10.2157);
    glVertex2f(24.9752, 10.2157);
    glEnd();

    ///15
    glBegin(GL_POLYGON);
    glColor3ub(95,99,80);
    glVertex2f(28.5401, 11.2556);
    glVertex2f(29.9875, 10.2157);
    glVertex2f(26.8954, 10.2157);
    glEnd();

    ///16
    glBegin(GL_POLYGON);
    ///glColor3ub(221,229,244);
    glColor3ub(95,99,80);
    glVertex2f(30.5505, 11.2556);
    glVertex2f(31.9979, 10.2157);
    glVertex2f(28.9058, 10.2157);
    glEnd();
}
void mountainTree()
{
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(1.6132, 10.4339);
    glVertex2f(1.6660, 10.4339);
    glVertex2f(1.6660, 10.1905);
    glVertex2f(1.6132, 10.1905);
    glEnd();

    fillCircle(0.1412, 1.5014, 10.4947, 56, 108, 55);
    fillCircle(0.1412, 1.6237, 10.5305, 56, 108, 55);
    fillCircle(0.1412, 1.7840, 10.4853, 77,115,88);
    fillCircle(0.1412, 1.5433, 10.6295, 56, 108, 55);
    fillCircle(0.1412, 1.7199, 10.6295, 77,115,88);
    fillCircle(0.1412, 1.6316, 10.6565, 77,115,88);

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(5.5080, 10.4339);
    glVertex2f(5.5608, 10.4339);
    glVertex2f(5.5608, 10.1905);
    glVertex2f(5.5080, 10.1905);
    glEnd();

    fillCircle(0.1412, 5.3962, 10.4947, 56, 108, 55);
    fillCircle(0.1412, 5.5185, 10.5305, 56, 108, 55);
    fillCircle(0.1412, 5.6788, 10.4853, 77,115,88);
    fillCircle(0.1412, 5.4381, 10.6295, 56, 108, 55);
    fillCircle(0.1412, 5.6147, 10.6295, 77,115,88);
    fillCircle(0.1412, 5.5264, 10.6565, 77,115,88);

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(9.7087, 10.4339);
    glVertex2f(9.7616, 10.4339);
    glVertex2f(9.7616, 10.1905);
    glVertex2f(9.7087, 10.1905);
    glEnd();

    fillCircle(0.1412, 9.5969, 10.4947, 56, 108, 55);
    fillCircle(0.1412, 9.7193, 10.5305, 56, 108, 55);
    fillCircle(0.1412, 9.8796, 10.4853, 77,115,88);
    fillCircle(0.1412, 9.6389, 10.6295, 56, 108, 55);
    fillCircle(0.1412, 9.8154, 10.6295, 77,115,88);
    fillCircle(0.1412, 9.7272, 10.6565, 77,115,88);

    ///4
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(14.0253, 10.4339);
    glVertex2f(14.0781, 10.4339);
    glVertex2f(14.0781, 10.1905);
    glVertex2f(14.0253, 10.1905);
    glEnd();

    fillCircle(0.1412, 13.9135, 10.4947, 56, 108, 55);
    fillCircle(0.1412, 14.0358, 10.5305, 56, 108, 55);
    fillCircle(0.1412, 14.1961, 10.4853, 77,115,88);
    fillCircle(0.1412, 13.9555, 10.6295, 56, 108, 55);
    fillCircle(0.1412, 14.1320, 10.6295, 77,115,88);
    fillCircle(0.1412, 14.0437, 10.6565, 77,115,88);

    ///5
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(18.3246, 10.4339);
    glVertex2f(18.3774, 10.4339);
    glVertex2f(18.3774, 10.1905);
    glVertex2f(18.3246, 10.1905);
    glEnd();

    fillCircle(0.1412, 18.2128, 10.4947, 56, 108, 55);
    fillCircle(0.1412, 18.3351, 10.5305, 56, 108, 55);
    fillCircle(0.1412, 18.4954, 10.4853, 77,115,88);
    fillCircle(0.1412, 18.2547, 10.6295, 56, 108, 55);
    fillCircle(0.1412, 18.4312, 10.6295, 77,115,88);
    fillCircle(0.1412, 18.3430, 10.6565, 77,115,88);

    ///6
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(22.4859, 10.4339);
    glVertex2f(22.5387, 10.4339);
    glVertex2f(22.5387, 10.1905);
    glVertex2f(22.4859, 10.1905);
    glEnd();

    fillCircle(0.1412, 22.3741, 10.4947, 56, 108, 55);
    fillCircle(0.1412, 22.4964, 10.5305, 56, 108, 55);
    fillCircle(0.1412, 22.6567, 10.4853, 77,115,88);
    fillCircle(0.1412, 22.4160, 10.6295, 56, 108, 55);
    fillCircle(0.1412, 22.5926, 10.6295, 77,115,88);
    fillCircle(0.1412, 22.5043, 10.6565, 77,115,88);

    ///7
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(26.4270, 10.4339);
    glVertex2f(26.4799, 10.4339);
    glVertex2f(26.4799, 10.1905);
    glVertex2f(26.4270, 10.1905);
    glEnd();

    fillCircle(0.1412, 26.3152, 10.4947, 56, 108, 55);
    fillCircle(0.1412, 26.4376, 10.5305, 56, 108, 55);
    fillCircle(0.1412, 26.5979, 10.4853, 77,115,88);
    fillCircle(0.1412, 26.3572, 10.6295, 56, 108, 55);
    fillCircle(0.1412, 26.5337, 10.6295, 77,115,88);
    fillCircle(0.1412, 26.4455, 10.6565, 77,115,88);
}
void shop()
{
    ///1
    ///top
    glBegin(GL_POLYGON);
    glColor3ub(210,180,140);
    glVertex2f(7.8611, 1.9339);
    glVertex2f(6.8936, 1.3339);
    glVertex2f(8.7501, 1.3339);
    glEnd();

    ///mid
    glBegin(GL_POLYGON);
    glColor3ub(139,115,85);
    glVertex2f(6.8936, 1.3339);
    glVertex2f(8.7501, 1.3339);
    glVertex2f(8.7501, 1.2747);
    glVertex2f(6.8936, 1.2747);
    glEnd();

    ///stick
    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(7.0448, 0.6012);
    glVertex2f(7.0881, 0.6012);
    glVertex2f(7.0881, 1.2747);
    glVertex2f(7.0448, 1.2747);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(7.1230, 0.6012);
    glVertex2f(7.1662, 0.6012);
    glVertex2f(7.1662, 1.2747);
    glVertex2f(7.1230, 1.2747);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(8.5560, 0.6012);
    glVertex2f(8.5993, 0.6012);
    glVertex2f(8.5993, 1.2747);
    glVertex2f(8.5560, 1.2747);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(8.4715, 0.6012);
    glVertex2f(8.5147, 0.6012);
    glVertex2f(8.5147, 1.2747);
    glVertex2f(8.4715, 1.2747);
    glEnd();

    ///ground
    glBegin(GL_POLYGON);
    glColor3ub(91,37,47);
    glVertex2f(6.9904, 0.6012);
    glVertex2f(8.6532, 0.6083);
    glVertex2f(8.6532, 0.3030);
    glVertex2f(6.9904, 0.3030);
    glEnd();

    ///2
    ///top
    glBegin(GL_POLYGON);
    glColor3ub(162,134,143);
    glVertex2f(15.5876, 1.9339);
    glVertex2f(14.6201, 1.3339);
    glVertex2f(16.4766, 1.3339);
    glEnd();

    ///mid
    glBegin(GL_POLYGON);
    glColor3ub(143,109,127);
    glVertex2f(14.6201, 1.3339);
    glVertex2f(16.4766, 1.3339);
    glVertex2f(16.4766, 1.2747);
    glVertex2f(14.6201, 1.2747);
    glEnd();

    ///stick
    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(14.7713, 0.6012);
    glVertex2f(14.8046, 0.6012);
    glVertex2f(14.8046, 1.2747);
    glVertex2f(14.7713, 1.2747);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(14.8494, 0.6012);
    glVertex2f(14.8827, 0.6012);
    glVertex2f(14.8827, 1.2747);
    glVertex2f(14.8494, 1.2747);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(16.2080, 0.6012);
    glVertex2f(16.2412, 0.6012);
    glVertex2f(16.2412, 1.2747);
    glVertex2f(16.2080, 1.2747);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(16.2825, 0.6012);
    glVertex2f(16.3258, 0.6012);
    glVertex2f(16.3258, 1.2747);
    glVertex2f(16.2825, 1.2747);
    glEnd();

    ///ground
    glBegin(GL_POLYGON);
    glColor3ub(91,37,47);
    glVertex2f(14.7169, 0.6012);
    glVertex2f(16.3797, 0.6083);
    glVertex2f(16.3797, 0.3030);
    glVertex2f(14.7169, 0.3030);
    glEnd();

    ///3
    ///top
    glBegin(GL_POLYGON);
    glColor3ub(188,143,143);
    glVertex2f(23.6968, 1.9339);
    glVertex2f(22.7293, 1.3339);
    glVertex2f(24.5858, 1.3339);
    glEnd();

    ///mid
    glBegin(GL_POLYGON);
    glColor3ub(233,150,122);
    glVertex2f(22.7293, 1.3339);
    glVertex2f(24.5858, 1.3339);
    glVertex2f(24.5858, 1.2747);
    glVertex2f(22.7293, 1.2747);
    glEnd();

    ///stick
    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(22.8805, 0.6012);
    glVertex2f(22.9138, 0.6012);
    glVertex2f(22.9138, 1.2747);
    glVertex2f(22.8805, 1.2747);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(22.9586, 0.6012);
    glVertex2f(22.9919, 0.6012);
    glVertex2f(22.9919, 1.2747);
    glVertex2f(22.9586, 1.2747);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(24.3072, 0.6012);
    glVertex2f(24.3504, 0.6012);
    glVertex2f(24.3504, 1.2747);
    glVertex2f(24.3072, 1.2747);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(24.3917, 0.6012);
    glVertex2f(24.4350, 0.6012);
    glVertex2f(24.4350, 1.2747);
    glVertex2f(24.3917, 1.2747);
    glEnd();

    ///ground
    glBegin(GL_POLYGON);
    glColor3ub(91,37,47);
    glVertex2f(22.8261, 0.6012);
    glVertex2f(24.4903, 0.6083);
    glVertex2f(24.4903, 0.3030);
    glVertex2f(22.8261, 0.3030);
    glEnd();
}

void bench()
{
    ///1
    ///sit
    glBegin(GL_POLYGON);
    glColor3ub(131,84,12);
    glVertex2f(10.5490, 0.8031);
    glVertex2f(12.5820, 0.8031);
    glVertex2f(12.6510, 0.6731);
    glVertex2f(10.4443, 0.6731);
    glEnd();

    ///legs
    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(10.7008, 0.4107);
    glVertex2f(10.7670, 0.4107);
    glVertex2f(10.7670, 0.6731);
    glVertex2f(10.7008, 0.6731);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(10.7872, 0.5460);
    glVertex2f(10.8434, 0.5460);
    glVertex2f(10.8434, 0.6731);
    glVertex2f(10.7872, 0.6731);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(12.2645, 0.5460);
    glVertex2f(12.3207, 0.5460);
    glVertex2f(12.3207, 0.6731);
    glVertex2f(12.2645, 0.6731);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(12.3419, 0.4107);
    glVertex2f(12.4081, 0.4107);
    glVertex2f(12.4081, 0.6731);
    glVertex2f(12.3419, 0.6731);
    glEnd();

    ///2
    ///sit
    glBegin(GL_POLYGON);
    glColor3ub(131,84,12);
    glVertex2f(18.6578, 0.8031);
    glVertex2f(20.6908, 0.8031);
    glVertex2f(20.7598, 0.6731);
    glVertex2f(18.5532, 0.6731);
    glEnd();

    ///legs
    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(18.8097, 0.4107);
    glVertex2f(18.8758, 0.4107);
    glVertex2f(18.8758, 0.6731);
    glVertex2f(18.8097, 0.6731);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(18.8961, 0.5460);
    glVertex2f(18.9522, 0.5460);
    glVertex2f(18.9522, 0.6731);
    glVertex2f(18.8961, 0.6731);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(20.3734, 0.5460);
    glVertex2f(20.4295, 0.5460);
    glVertex2f(20.4295, 0.6731);
    glVertex2f(20.3734, 0.6731);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(62,48,65);
    glVertex2f(20.4508, 0.4107);
    glVertex2f(20.5169, 0.4107);
    glVertex2f(20.5169, 0.6731);
    glVertex2f(20.4508, 0.6731);
    glEnd();
}

void tree3()
{
    ///1
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(2.4003, 0.9757);
    glVertex2f(2.4654, 0.9757);
    glVertex2f(2.4654, 0.5139);
    glVertex2f(2.4003, 0.5139);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(139, 146, 22);
    glVertex2f(1.9611, 0.9759);
    glVertex2f(2.8942, 0.9759);
    glVertex2f(2.4103, 1.2771);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(167, 159, 15);
    glVertex2f(2.0548, 1.1438);
    glVertex2f(2.7632, 1.1438);
    glVertex2f(2.4102, 1.4449);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(167, 159, 15);
    glVertex2f(2.1928, 1.3115);
    glVertex2f(2.6203, 1.3115);
    glVertex2f(2.4102, 1.6127);
    glEnd();

    ///2
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(5.2079, 0.9757);
    glVertex2f(5.2730, 0.9757);
    glVertex2f(5.2730, 0.5139);
    glVertex2f(5.2079, 0.5139);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(139, 146, 22);
    glVertex2f(4.7687, 0.9759);
    glVertex2f(5.7018, 0.9759);
    glVertex2f(5.2179, 1.2771);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(167, 159, 15);
    glVertex2f(4.8623, 1.1438);
    glVertex2f(5.5708, 1.1438);
    glVertex2f(5.2178, 1.4449);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(167, 159, 15);
    glVertex2f(5.0004, 1.3115);
    glVertex2f(5.4279, 1.3115);
    glVertex2f(5.2178, 1.6127);
    glEnd();

    ///3
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(26.2950, 0.9757);
    glVertex2f(26.3570, 0.9757);
    glVertex2f(26.3570, 0.5139);
    glVertex2f(26.2950, 0.5139);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(139, 146, 22);
    glVertex2f(25.8567, 0.9759);
    glVertex2f(26.7898, 0.9759);
    glVertex2f(26.3059, 1.2771);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(167, 159, 15);
    glVertex2f(25.9504, 1.1438);
    glVertex2f(26.6588, 1.1438);
    glVertex2f(26.3058, 1.4449);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(167, 159, 15);
    glVertex2f(26.0884, 1.3115);
    glVertex2f(26.5159, 1.3115);
    glVertex2f(26.3058, 1.6127);
    glEnd();

    ///4
    glBegin(GL_POLYGON);
    glColor3ub(105,75,55);
    glVertex2f(29.0389, 0.9757);
    glVertex2f(29.1039, 0.9757);
    glVertex2f(29.1039, 0.5139);
    glVertex2f(29.0389, 0.5139);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(139, 146, 22);
    glVertex2f(28.5996, 0.9759);
    glVertex2f(29.5327, 0.9759);
    glVertex2f(29.0488, 1.2771);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(167, 159, 15);
    glVertex2f(28.6933, 1.1438);
    glVertex2f(29.4018, 1.1438);
    glVertex2f(29.0487, 1.4449);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(167, 159, 15);
    glVertex2f(28.8313, 1.3115);
    glVertex2f(29.2588, 1.3115);
    glVertex2f(29.0487, 1.6127);
    glEnd();
}

void raining(int value)
{
    if (rainyDay)
    {
        rain += 5;

        glBegin(GL_LINES);

        for (int i = 1; i <=100; i++)
        {
            int x = rand() % 35;
            int y = rand() % 25;

            glColor3ub(255, 255, 255);
            glVertex2f(x, y);
            glVertex2f(x - 0.1, y - 0.2);
        }
        glEnd();
        glutPostRedisplay();
        glutTimerFunc(15, raining, 0);
        glFlush();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'D':
        case 'd':
            day = true;
            break;

        case 'N':
        case 'n':
            day = false;
            break;

        case 'Q':
        case 'q':
            scene1 = true;
            break;

        case 'W':
        case 'w':
            scene1 = false;
            break;

        case 'F':
        case 'f':
            shipForward = true;
            break;

        case 'B':
        case 'b':
            shipForward = false;
            shipBackward = true;
            break;

        case 'Z':
        case 'z':
            shipForward = false;
            shipBackward = false;
            break;

        case 'S':
        case 's':
            sndPlaySound(NULL, SND_ASYNC);
            break;

        case 'R':
        case 'r':
            ///rainyDay = !rainyDay;
            rainyDay = true;
            raining(0);
            sndPlaySound("Rain sound.wav", SND_ASYNC);
            break;

        case 'T':
        case 't':
            rainyDay = false;
            sndPlaySound("Riverside Road Sound.wav", SND_ASYNC);
            break;

        default:
            break;
    }

    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    ///Scene 1
    if(scene1)
    {
        sky();

    if(day)
    {
        if(rainyDay)
        {
            cloud();
        }
        else
        {
            sun();
            cloud();
        }
    }
    else
    {
        if(rainyDay)
        {
            moon();
        }
        else
        {
            stars();
            moon();
        }
    }
    grass1();
    building1();
    building2();
    building3();
    building4();
    building5();
    building6();
    building7();
    building8();
    building9();
    building10();
    building11();
    building12();
    building13();
    roadSide();
    elevator();
    human();
    mainRoad();
    bus1();
    car1();
    cableCarPillar1();
    cableCar();
    tree1();
    roadLight1();
    tunnnel();
    tunnelRoad();
    tunnelCar1();
    tunnelCar2();
    tunnelBus1();
    tunnelBus2();
    tree2();
    roadLight2();
    tunnelX();
    car2();
    bus2();
    tree3();
    shop();
    bench();
    train();
    }

    ///Scene 2
    else
    {
        sky();

    if(day)
    {
        if(rainyDay)
        {
            cloud();
        }
        else
        {
            sun();
            cloud();
        }
    }
    else
    {
        if(rainyDay)
        {
            moon();
        }
        else
        {
            stars();
            moon();
        }
    }
    grass2();
    river();
    mountain();
    grass1();
    mountainTree();
    boat1();
    boat2();
    ship();
    ghat();
    roadSide();
    elevator();
    human();
    mainRoad();
    bus1();
    car1();
    cableCarPillar2();
    cableCar();
    tree1();
    roadLight1();
    tunnelRoadX();
    tunnelRoad();
    tunnelCar1();
    tunnelCar2();
    tunnelBus1();
    tunnelBus2();
    tree2();
    roadLight2();
    car2();
    bus2();
    tree3();
    shop();
    bench();
    train();
    }

    glutSwapBuffers();
    glFlush();
}

int main(int argc, char** argv)
{
    cout <<"Simulating Sustainable Traffic Solutions for Urban Communication" << endl << endl;
    cout << "Key D/d : Day Mode" << endl << endl;
    cout << "Key N/n : Night Mode" << endl << endl;
    cout << "Key Q/q : First Scene" << endl << endl;
    cout << "Key W/w : Second Scene" << endl << endl;
    cout << "Key F/f : Ship Forward" << endl << endl;
    cout << "Key B/b : Ship Backward" << endl << endl;
    cout << "Key Z/z : Ship Stop" << endl << endl;
    cout << "Key R/r : Rain Start" << endl << endl;
    cout << "Key T/t : Rain Stop" << endl << endl;
    cout << "Key S/s : Sound Off"<<endl;

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1400, 800);
    glutInitWindowPosition (50, 50);
    glutCreateWindow("Simulating Sustainable Traffic Solutions for Urban Communication");
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);

    gluOrtho2D(0, 30, 0, 15);
    glutTimerFunc(10, moveCloud, 0);
    glutTimerFunc(10, moveWater, 0);
    glutTimerFunc(10, moveBoat1, 0);
    glutTimerFunc(10, moveBoat2, 0);
    glutTimerFunc(10, moveShip, 0);
    glutTimerFunc(15, moveElevator, 0);
    glutTimerFunc(10, moveHuman, 0);
    glutTimerFunc(10, moveBus1, 0);
    glutTimerFunc(10, moveCar1, 0);
    glutTimerFunc(20, moveCableCar, 0);
    glutTimerFunc(10, moveTunnelCar1, 0);
    glutTimerFunc(10, moveTunnelBus1, 0);
    glutTimerFunc(10, movetunnelCar2, 0);
    glutTimerFunc(10, movetunnelBus2, 0);
    glutTimerFunc(10, moveCar2, 0);
    glutTimerFunc(10, moveBus2, 0);
    glutTimerFunc(20, moveTrain, 0);

    sndPlaySound("Riverside Road Sound.wav", SND_ASYNC);

    glMatrixMode(GL_PROJECTION);
    glClearColor(0.0, 0.5, 0.8, 1.0);
    glLoadIdentity();
    glutMainLoop();

    return 0;
}
