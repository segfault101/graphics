#include <iostream>
using namespace std;
#include "vgl.h"
#include "LoadShaders.h"

#define Pi 3.141592653589793238462

// global vars
enum VAO_IDs { Triangles, NumVAOs=3 };
enum Buffer_IDs { ArrayBuffer, NumBuffers = 6 };
enum Attrib_IDs { vPosition, vColorPosition };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint rainbow_triangle_points = 0;
const GLuint NumVertices = 6; 

//GLuint numberOfTrianglesInCircle = 0;

int key_pressed = 0;

//toggles
int x = 1;	//toggle for display of 2 triangles
int y = 1;	//toggle for display of the single triangle
int z = 0;	//toggle for display of circle

int c = 0;
int g = 0;

//misc
GLfloat inputColorsOfTwoTriangles[3] = {0,0,1};
GLfloat radiusOfCircle = 0;
GLint numberOfTriangles = 0;

//---------------------------------------------------------------------
//
// init	-	all values that will be constant over the execution of the program are set in init
//

GLuint useTheseShaders(char* vertexshader, char* fragmentshader)
{
	
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, vertexshader },
		{ GL_FRAGMENT_SHADER, fragmentshader },
		{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders(shaders);

	return program;

}

void init()
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

	/*
	
	*/

	//end of image info

	//color info [for the two triangles]
	GLfloat Two_Triangles_Color_Data[NumVertices][3] = {

			{ 0, 0, 1 },
			{ 0, 0, 1 },
			{ 0, 0, 1 },

			{ 0, 0, 1 },
			{ 0, 0, 1 },
			{ 0, 0, 1 },

					};

	GLfloat Rainbow_Triangle_Colors[NumVertices][3] = {
			{ 1.0, 0.0, 0.0 },
			{ 0.0, 1.0, 0.0 },
			{ 0.0, 0.0, 1.0 },
		};

	/*

	*/
	

	//end of color info


		//returns 1 vertex array object 'names' in arrays. The 'names' here are just integer values starting from 1 - will be unique
		glGenVertexArrays(NumVAOs, VAOs);
	
		glGenBuffers(NumBuffers, Buffers);
	
		
		// first 2 triangles
		glBindVertexArray(VAOs[0]);		//the 'name' previously returned will be bound to current context

		glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Two_Triangles_vertices), Two_Triangles_vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Two_Triangles_Color_Data), Two_Triangles_Color_Data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(vColorPosition);
		glVertexAttribPointer(vColorPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)); 

		
		//rainbow triangle
		glBindVertexArray(VAOs[1]);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(rainbow_triangle), rainbow_triangle, GL_STATIC_DRAW);
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		glBindBuffer(GL_ARRAY_BUFFER, Buffers[3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Rainbow_Triangle_Colors), Rainbow_Triangle_Colors, GL_STATIC_DRAW);
		glEnableVertexAttribArray(vColorPosition);
		glVertexAttribPointer(vColorPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		//circle
		/*
		 */

		
	
}


//---------------------------------------------------------------------
//
// display
//
void display( void )
{
	glClearColor(0, 0, 0, 0);			//<---moved it back from init
	glClear(GL_COLOR_BUFFER_BIT);		//<----'

	if (x == 1 && c==0)
	{	
		

		GLuint program = useTheseShaders("triangles.vert", "triangles.frag");
    	glUseProgram(program);
		

		glBindVertexArray(VAOs[0]);			//to select the vertex array that we want to use as vertex data	
		glDrawArrays(GL_TRIANGLES, 0, 6); //send the vertex data to opengl pipeline

	}

	if (x == 1 && c == 1)
	{
		GLfloat Two_Triangles_vertices[NumVertices][2] = {
			{ -0.90, -0.90 }, // Triangle 1
			{ 0.85, -0.90 },
			{ -0.90, 0.85 },
			{ 0.90, -0.85 }, // Triangle 2
			{ 0.90, 0.90 },
			{ -0.85, 0.90 }
		};

		GLfloat Two_Triangles_Color_Data[NumVertices][3] = {

			{ inputColorsOfTwoTriangles[0], inputColorsOfTwoTriangles[1], inputColorsOfTwoTriangles[2] },
			{ inputColorsOfTwoTriangles[0], inputColorsOfTwoTriangles[1], inputColorsOfTwoTriangles[2] },
			{ inputColorsOfTwoTriangles[0], inputColorsOfTwoTriangles[1], inputColorsOfTwoTriangles[2] },

			{ inputColorsOfTwoTriangles[0], inputColorsOfTwoTriangles[1], inputColorsOfTwoTriangles[2] },
			{ inputColorsOfTwoTriangles[0], inputColorsOfTwoTriangles[1], inputColorsOfTwoTriangles[2] },
			{ inputColorsOfTwoTriangles[0], inputColorsOfTwoTriangles[1], inputColorsOfTwoTriangles[2] }

		};

		glBindVertexArray(VAOs[0]);		//the 'name' previously returned will be bound to current context

/*		glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Two_Triangles_vertices), Two_Triangles_vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
*/
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Two_Triangles_Color_Data), Two_Triangles_Color_Data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(vColorPosition);
		glVertexAttribPointer(vColorPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		glBindVertexArray(VAOs[0]);			//to select the vertex array that we want to use as vertex data	
		glDrawArrays(GL_TRIANGLES, 0, 6); //send the vertex data to opengl pipeline
	}
	
	if (y == 1)
	{
		GLuint program = useTheseShaders("triangles.vert", "triangles.frag");
		glUseProgram(program);

		glBindVertexArray(VAOs[1]);			
		glDrawArrays(GL_TRIANGLES, 0, 3); 
	
	}


	if (z == 1 && g == 1)
	{
		GLint numberOfVertices = numberOfTriangles + 2;

		//image info
		GLfloat **circle_vertices;
		GLfloat *values;

		values = (GLfloat*)malloc(numberOfVertices * 2 * sizeof(GLfloat));
		circle_vertices = (GLfloat**)malloc(numberOfVertices * sizeof(GLfloat*));

		for (int i = 0; i < numberOfVertices; i++)
			circle_vertices[i] = &(values[i * 2]);

		circle_vertices[0][0] = 0.0f;
		circle_vertices[0][1] = 0.0f;

		int count = 1;
		for (GLdouble i = 0; i <= 360; i = i + GLdouble(360 / (GLdouble)numberOfTriangles))
		{
			circle_vertices[count][0] = radiusOfCircle * sin((GLdouble)i * ((GLdouble)Pi / 180));
			circle_vertices[count][1] = radiusOfCircle * cos((GLdouble)i * ((GLdouble)Pi / 180));

			cout << count << endl;
			count++;
		}

		//color info
		GLfloat** circle_vertex_colors;
		GLfloat *colorvalues;

		colorvalues = (GLfloat*)malloc(numberOfVertices * 3 * sizeof(GLfloat));
		circle_vertex_colors = (GLfloat**)malloc(numberOfVertices * sizeof(GLfloat*));

		for (int i = 0; i < numberOfVertices; i++)
			circle_vertex_colors[i] = &(colorvalues[i * 3]);

		circle_vertex_colors[0][0] = inputColorsOfTwoTriangles[0];
		circle_vertex_colors[0][1] = inputColorsOfTwoTriangles[1];
		circle_vertex_colors[0][2] = inputColorsOfTwoTriangles[2];

		count = 1;
		for (GLdouble i = 0; i <= 360; i = i + GLdouble(360 / (GLdouble)numberOfTriangles))
		{
			circle_vertex_colors[count][0] = inputColorsOfTwoTriangles[0];
			circle_vertex_colors[count][1] = inputColorsOfTwoTriangles[1];
			circle_vertex_colors[count][2] = inputColorsOfTwoTriangles[2];

			cout << circle_vertex_colors[count][0] << " " << circle_vertex_colors[count][1] << " " << circle_vertex_colors[count][2] << endl;


			count++;
		}

		glBindVertexArray(VAOs[2]);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[4]);
		glBufferData(GL_ARRAY_BUFFER, (numberOfVertices * 2 * sizeof(GLfloat)), *circle_vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

		glBindBuffer(GL_ARRAY_BUFFER, Buffers[5]);
		glBufferData(GL_ARRAY_BUFFER, numberOfVertices * 3 * sizeof(GLfloat), *circle_vertex_colors, GL_STATIC_DRAW);
		glEnableVertexAttribArray(vColorPosition);
		glVertexAttribPointer(vColorPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


		glBindVertexArray(VAOs[2]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);

		GLuint program = useTheseShaders("triangles.vert", "triangles.frag");
		glUseProgram(program);


	}

	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
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

	if (key_pressed == 121)		
		y = !y;
	
	if (key_pressed == 122)
		z = !z;

	if (key_pressed == 99)
	{
		c = 1;
		for (;;)
		{
			cout << "Enter the colors for the two triangles :" << endl;

			cout << "Red :";
			cin >> inputColorsOfTwoTriangles[0];

			cout << "Green :";
			cin >> inputColorsOfTwoTriangles[1];

			cout << "Blue :";
			cin >> inputColorsOfTwoTriangles[2];
			cout << endl;

			int flag = 1;

			for (int i = 0; i < 3; i++)
				if (inputColorsOfTwoTriangles[i] < 0 || inputColorsOfTwoTriangles[i]>1)
				{
					cout << "Invalid values. Enter values in the range [0,1]" << endl;
					flag = 0;
					break;
				}

			if (flag == 1)
				break;

		}
	}

	if (key_pressed == 103)
	{
		g = 1;

			cout << "Enter the radius for the circle :" << endl;
			cin >> radiusOfCircle;

			cout << "Enter the number of triangles" << endl;
			cin >> numberOfTriangles;

	}
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


	GLfloat radiusOfCircle;

	GLint numberOfTriangles;


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

	glutDisplayFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutMainLoop();
}

