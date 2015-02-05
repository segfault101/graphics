#include <iostream>
using namespace std;
#include "vgl.h"
#include "LoadShaders.h"

// global vars
enum VAO_IDs { Triangles, NumVAOs=2 };
enum Buffer_IDs { ArrayBuffer, NumBuffers =2 };
enum Attrib_IDs { vPosition };

GLuint VAOs[NumVAOs];
GLuint Buffers[2];
GLuint rainbow_triangle_points = 0;
const GLuint NumVertices = 6; 

int key_pressed = 0;

//toggles
int x = 1;	//toggle for display of 2 triangles
int y = 1;	//toggle for display of the single triangle
int z = 0;	//toggle for display of circle


//---------------------------------------------------------------------
//
// init	-	all values that will be constant over the execution of the program are set in init
//

void init(void)
{
		//image info
		GLfloat Two_Triangles_vertices[NumVertices][2] = {
			{ -0.90, -0.90 }, // Triangle 1
			{ 0.85, -0.90 },
			{ -0.90, 0.85 },
			{ 0.90, -0.85 }, // Triangle 2
			{ 0.90, 0.90 },
			{ -0.85, 0.90 }
		};

		GLfloat rainbow_triangle[3][2] = {
			{ -0.30, -0.30 }, //rainbow triangle
			{ 0.30, -0.30 },
			{ 0.0, 0.30 }
		};
		//end of image info

		//returns 1 vertex array object 'names' in arrays. The 'names' here are just integer values starting from 1 - should be distinct
		glGenVertexArrays(NumVAOs, VAOs);		//numvaos = 1 and VAOs[NumVAOs] = VAOs[1] 
		cout <<"Name returned by glGenVertexArrays: "<< VAOs [0] <<", "<< VAOs[1]<< endl;

		glGenBuffers(2, Buffers);	//parameters: num of buffers, array
		cout << "Name returned by glGenBuffers: " << Buffers[0] << ", " << Buffers[1] << endl;

		
		// first 2 triangles
		glBindVertexArray(VAOs[0]);		//the 'name' previously returned will be bound to current context
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Two_Triangles_vertices), Two_Triangles_vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		

		//rainbow triangle
		glBindVertexArray(VAOs[1]);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rainbow_triangle), rainbow_triangle, GL_STATIC_DRAW);
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


		//shader info
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "triangles.vert" },
			{ GL_FRAGMENT_SHADER, "triangles.frag" },
			{ GL_NONE, NULL }
		};
	
		GLuint program = LoadShaders(shaders);
		glUseProgram(program);

		glClearColor(0, 0, 0, 0);
	
}


//---------------------------------------------------------------------
//
// display - virtually same in all opengl applications
//
void display( void )
{
	glClearColor(0, 0, 0, 0);			//<---moved it back from init
	glClear(GL_COLOR_BUFFER_BIT);		//<----'

	if (x == 1)
	{
		glBindVertexArray(VAOs[0]);			//to select the vertex array that we want to use as vertex data	
		glDrawArrays(GL_TRIANGLES, 0, 6); //send the vertex data to opengl pipeline


		glBindVertexArray(VAOs[1]);			//to select the vertex array that we want to use as vertex data	
		glDrawArrays(GL_TRIANGLES, 0, 3); //send the vertex data to opengl pipeline

	}


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	//cout << x << endl;
	glFlush();	//requests that any pending opengl calls are flushed to the opengl server and processed
	
}

void processNormalKeys(unsigned char key, int _x, int _y) {

	if (key == 27 || key==113)					//27 is  ascii value for ESC
		exit(0);


	if (key)
	{
		key_pressed = key;	
	}


	if (key_pressed == 119)		//wireframe on
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(5);

	}

	if (key_pressed == 115)		//wireframe off i.e. solid surface
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (key_pressed == 120)	    // toggle the two triangles
		x = !x;

	glutPostRedisplay();
		
}

//---------------------------------------------------------------------
//
// main
//

int main(int argc, char** argv)
{

	glewExperimental = GL_TRUE; //********* added

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);
	
	if (glewInit()) 
	{
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit(EXIT_FAILURE);
	}

	
	init();
	glutDisplayFunc(display);	//<-- called the 'callback' function
	glutKeyboardFunc(processNormalKeys);//<--'
	glutMainLoop();
}
