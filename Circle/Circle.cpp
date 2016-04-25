// Circle.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//

#include <Windows.h>
#include <time.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <conio.h>

#define width 1000
#define height 1000
bool flag = false;

void DrawField(float x0, float y0){
	//set color of circle
	glColor3f(1.0, 1.0, 0.0);
	//set size of point
	glPointSize(4);
	//Drawing
	glBegin(GL_POINTS);
	int num_segments = 5000;
	for (int i = 0; i < num_segments; ++i){
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
		float x = 2 * cosf(theta);//calculate the x component 
		float y = 2 * sinf(theta);//calculate the y component 
		glVertex2f(x + x0, y + y0);//output vertex 
	}
	glEnd();
}

void Tick(float k = 0){
	//Clear color buffer bit
	glClear(GL_COLOR_BUFFER_BIT);
	//Remember state of matrix
	glPushMatrix();
	for (int j = 0; j < 8; ++j){
		DrawField(k, 0);
		//rotate circle
		glRotatef(-45 * (j+1), 0, 0, 1);
	}
	//Restore transformation
	glPopMatrix();
	//Clear stack after drawing
	glFlush();
	//System sleep for 100 mls
	Sleep(100);
}

void display()
{
	glClearColor(0, 0, 0, 0); 
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1, 1, 1);
	glFlush();
}

void timer(int = 0){
	Sleep(1000);
	if (!flag){
		//draw circles
		for (float i = 0.f; i <= 1.65f; i += 0.2f){
			Tick(i);
		}
	}
	else{
		//draw circles
		for (float i = 1.65f; i >= 0.f; i -= 0.2f){
			Tick(i);
		}
	}
	flag ? flag = false : flag = true;
	glutTimerFunc(50, timer, 0);
}

int main(int argc, char **argv)
{
	srand((unsigned)time(NULL));//randomize random
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("Circle");
	glClearColor(0.0, 0.0, 0.0, 0.0);//set bachground's color 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5, 5, -5, 5);

	glutDisplayFunc(display);
	glutTimerFunc(50, timer, 0);

	glutMainLoop();
	return 0;
}

