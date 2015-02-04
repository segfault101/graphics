#include <iostream>
using namespace std;
#include "vgl.h"
#include "LoadShaders.h"

// global vars
enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
 
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
		glGenVertexArrays(NumVAOs, VAOs); //texbook pg 17

		glBindVertexArray(VAOs[Triangles]); //text book pg 17

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
			{ 0.30, 0.30 }
		};

		//below 3 lines: http://antongerdelan.net/opengl/vertexbuffers.html and http://www.swiftless.com/tutorials/opengl4/4-opengl-4-vao.html,
		// http://stackoverflow.com/questions/15821969/what-is-the-proper-way-to-modify-opengl-vertex-buffer or https://www.youtube.com/watch?v=6WJPvCCCoeg&list=PL5SguJ-P5eq7H0EEnKmfn_fQzstEy-RZr&index=2
		glGenBuffers(NumBuffers, Buffers);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Two_Triangles_vertices), Two_Triangles_vertices, GL_STATIC_DRAW);

		//shader info
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "triangles.vert" },
			{ GL_FRAGMENT_SHADER, "triangles.frag" },
			{ GL_NONE, NULL }
		};
	

		GLuint program = LoadShaders(shaders);
		glUseProgram(program);

		// below two functions deal speciifically with associating variables in a vertx shader with data that we've stored in buffer 
		//object ==> "shader plumbing" i.e you need to connect conduits between application and shader b/w various shader stages
		glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));//<---,		//page 25-26 marked
		glEnableVertexAttribArray(vPosition); //<------------- vposition variable that is used by the shader in triangles.vert

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
		glBindVertexArray(VAOs[Triangles]);			//to select the vertex array that we want to use as vertex data	
		glDrawArrays(GL_TRIANGLES, 0, NumVertices); //send the vertex data to opengl pipeline

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
