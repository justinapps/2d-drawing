#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

/*
To compile: 	gcc img21.c -o img21 glut32.lib -lopengl32 -lglu32
To run: 		img21

What is implemented:
- Shapes: Point, line, triangle, rectangle.
- Colours: Can select colours from a submenu or a palette.
- Clear screen.
- Transparency.

*/


GLfloat x1, x2, x3, y10, y2, y3;
GLfloat hh;
float r, g, b, a = 1.0;
GLint scrn;
GLfloat array[3];

void display(void){

	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(3.0);
	r = 1.0;
	g = 0.0;
	b = 0.0;
	glColor4f(r, g, b, a);

	glFlush();
	return;
}

//making the colour palette
void Pallete(void){

	glBegin(GL_QUADS);
	   glColor3f(0.6f, 0.0f, 1.0f);
	   glVertex2f(-1, 1);
	   glColor3f(1.0f, 0.0f, 0.0f);
	   glVertex2f(-1, -1);
	   glColor3f(0.0f, 1.0f, 0.0f);
	   glVertex2f(1, -1);
	   glColor3f(1.0f, 1.0f, 0.0f);
	   glVertex2f(1, 1);
   glEnd();
   glutSwapBuffers();
   glFlush();
   return;
}

void ColourPicker(GLint button, GLint state, GLint x, GLint y){
	
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
		glReadPixels(x, 480-y, 1, 1, GL_RGB, GL_FLOAT, array);
	}
	
	glutSetWindow(scrn);
		r = array[0];
		g = array[1];
		b = array[2];

	glColor4f(r, g, b , a);
	
	return;
}

//rectangles
void SelectRectangle(){

	glBegin(GL_POLYGON);
		glVertex2f(x1,y10);
		glVertex2f(x1,y2);
		glVertex2f(x2,y2);
		glVertex2f(x2,y10);
	glEnd();

	glFlush();
	return;	
}

void CallRectangle(GLint button, GLint state, GLint x, GLint y){
	static int first = 1;

	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){

		if (first){
			x1 = x; 
			y10 = hh - y;
		}

		else{
			x2 = x;
			y2 = hh - y;
			SelectRectangle();
		}
		first = !first;
	}

	return;
}

//lines
void SelectLine(){
	
	glBegin(GL_LINES);
		glVertex2f(x1, y10);
		glVertex2f(x2, y2);
	glEnd();
	glFlush();
	return;	
	
}

void CallLine(GLint button, GLint state, GLint x, GLint y){
	static int first=1;

	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){

		if (first == 1){

			x1 = x; 
			y10 = hh - y;
			first++;
		}

		else if(first == 2){

			x2 = x;
			y2 = hh - y;
			first = 1;
			glLineWidth(3.0);
			SelectLine();
		}

	}

	return;
}

//points
void SelectPoint(){

	glPointSize(3.0);
	glBegin(GL_POINTS);
		glVertex2f(x1, y10);
	 glEnd();
	 
	 glFlush();
	 return;
}


void CallPoint(GLint button, GLint state, GLint x, GLint y){

	static int first=1;
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){

			x1 = x; 
			y10 = hh - y;
			SelectPoint();	
	}
	
	return;
}

//triangles
void SelectTriangle(){

	glBegin(GL_TRIANGLES);
		glVertex2f(x1,y10);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
	glEnd();

	glFlush();
	return;	
}


void CallTriangle(GLint button, GLint state, GLint x, GLint y){

	static int first=1;
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){

		if (first == 1){

			x1 = x; 
			y10 = hh - y;
			first++;
		}

		else if(first == 2){

			x2 = x;
			y2 = hh - y;
			first++;
		}

		else{

			x3 = x;
			y3 = hh - y;
			first = 1;
			SelectTriangle();
		}	
	}

	return;
}

//choose colour from a submenu
void pickColour(int option){
	
	switch(option){
		case 0:{
			r = 1.0, g = 0.0, b = 0.0;
			glColor4f(r, g, b, a);
		} break;
		case 1:{
			r = 0.0, g = 1.0, b = 0.0;
			glColor4f(r, g, b, a);
		} break;
		case 2:{
			r = 0.0, g = 0.0, b = 1.0;
			glColor4f(r, g, b, a);
		} break;
		case 3:{
			r = 0.0, g = 0.0, b = 0.0;
			glColor4f(r, g, b, a);
		} break;
		case 4:{
			r = 1.0, g = 1.0, b = 0.0;
			glColor4f(r, g, b, a);
		} break;
		case 5:{
			r = 1.0, g = 0.5, b = 0.0;
			glColor4f(r, g, b, a);
		} break;
		default: {} break;
	}

	return;
}


void SelectShape(int option){

	switch (option){
		case 1 :
			glutMouseFunc(CallPoint);
			break;
		case 2 :
			glutMouseFunc(CallLine);
			break;
		case 3 :
			glutMouseFunc(CallTriangle);
			 break;
		case 4 :
			glutMouseFunc(CallRectangle);
			break;
		case 5 :
			//polygon
			break;
	}

	return;
}

void Transparency(int option){
	switch(option){
		case 0:{
			a += 0.1;
			glColor4f(r,g,b,a);

		}break;
		
		case 1:{
			a -= 0.1;
			glColor4f(r,g,b,a);
		}break;

		default: {}break;
	}

	return;
}


void MainMenu(int option){

	switch (option){

		case 0:

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glFlush();
			break;
	}

	return;
}

void MyReshape(GLsizei w, GLsizei h){

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLfloat)w, 0.0, (GLfloat)h);
	glViewport(0, 0, w, h);
	hh=h;

	return;
}


int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 200);
	scrn = glutCreateWindow("Draw");
	glutDisplayFunc(display);
	
	//enables transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutReshapeFunc(MyReshape);
	glutMouseFunc(CallPoint);
	
	
	int colourSubMenu = glutCreateMenu(pickColour);
	glutAddMenuEntry("Red", 0);
	glutAddMenuEntry("Green", 1);
	glutAddMenuEntry("Blue", 2);
	glutAddMenuEntry("Black", 3);
	glutAddMenuEntry("Yellow", 4);
	glutAddMenuEntry("Orange", 5);
	
	int shapeSubMenu = glutCreateMenu(SelectShape);
	glutAddMenuEntry("Point", 1);
	glutAddMenuEntry("Line", 2);
	glutAddMenuEntry("Triangle", 3);
	glutAddMenuEntry("Square", 4);
	glutAddMenuEntry("Polygon", 5); //not implemented
	
	int transparencySubMenu = glutCreateMenu(Transparency);
	glutAddMenuEntry("+", 0);
	glutAddMenuEntry("-", 1);
	
	int menu = glutCreateMenu(MainMenu);
	glutAddMenuEntry("Clear Screen", 0);
	
	glutAddSubMenu("Colours", colourSubMenu);
	glutAddSubMenu("Transparency", transparencySubMenu);
	

	glutAddSubMenu("Shapes", shapeSubMenu);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutInitWindowSize(480, 480);
	glutInitWindowPosition(0, 200);
	glutCreateWindow("Palette");
	glutMouseFunc(ColourPicker);
	glutDisplayFunc(Pallete);
	
	
	glutMainLoop();
}