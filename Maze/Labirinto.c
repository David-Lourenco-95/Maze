#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define LINHAS 30
#define COLUNAS 30
#define false 0
#define true 1

typedef struct				
{
	GLubyte	*imageData;		
	GLuint	bpp;			
	GLuint	width;			
	GLuint	height;			
	GLuint	texID;			// Texture ID Used To Select A Texture
} TextureImage;	

TextureImage texture[1000];

double cx = 1.0, cy = 0.0, cz = 2.0;

GLint mapa[LINHAS][COLUNAS] ={
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
{1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1},
{1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1},
{1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
{1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
{1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1},
{1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
{1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1},
{1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1},
{1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
{1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1},
{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1},
{1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
{1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1},
{1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1},
{1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
{1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
{1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
{1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1},
{1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1}

};

void drawGrid() {
  int i;	

  for (i = 0; i < 60; i++)
    {
	  glPushMatrix ();
	  if (i < 30)
	    {
	      glTranslatef (0, 0, i);
	    }
	  if (i >= 30)
	    {
	      glTranslatef (i - 30, 0, 0);
	      glRotatef (-90, 0, 1, 0);
	    }

	glEnable(GL_TEXTURE_2D);
	 
	 glBindTexture(GL_TEXTURE_2D, texture[1].texID);

          glBegin (GL_LINES);

  	glTexCoord2f(0.0f, 1.0f);
  	glVertex3f (0, 0, 0);
  	glTexCoord2f(1.0f, 0.0f);
   	glVertex3f (29, 0, 0);
	 glEnd();
	  
	  glPopMatrix ();

	}
}


void imprimirLabirinto() {	

  for (int i = 0; i < LINHAS; i++)
    {
	
      for (int j = 0; j < COLUNAS; j++)
	{

	glPushMatrix ();

	  if (mapa[i][j] == 1)

	    {

		glTranslatef (i,0, j);

		glBindTexture(GL_TEXTURE_2D, texture[0].texID);


		glBegin(GL_QUADS);		

		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(0.5f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(0.5f, 0.5f); glVertex3f( 0.5f,  0.5f,  0.5f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 0.5f); glVertex3f(-0.5f,  0.5f,  0.5f);	// Top Left Of The Texture and Quad

		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);	// Bottom Left Of The Texture and Quad

		// Top Face
		glTexCoord2f(0.5f, 1.0f); glVertex3f(-0.5F,  0.5f, -0.5f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.5f, 0.5f); glVertex3f(-0.5f,  0.5f, 0.5f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.5f); glVertex3f( 0.5f,  0.5f,  0.5f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5F,  0.5f, -0.5f);	// Top Right Of The Texture and Quad

		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f, -0.5f, -0.5f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);	// Bottom Right Of The Texture and Quad

		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, -0.5f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  0.5f);	// Bottom Left Of The Texture and Quad

		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  0.5f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, -0.5f);
	glEnd();

	      
	    }
	glPopMatrix ();


	}
	
  
   }
 glutSwapBuffers ();
 glFlush();
	
}

void theCube (){

glEnable(GL_TEXTURE_2D);

  glPushMatrix ();

  glTranslatef (cx, cy, cz);

  glBindTexture(GL_TEXTURE_2D, texture[2].texID);

	glBegin(GL_QUADS);		

		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3f, -0.3f,  0.3f);	
		glTexCoord2f(0.5f, 0.0f); glVertex3f( 0.3f, -0.3f,  0.3f);	
		glTexCoord2f(0.5f, 0.5f); glVertex3f( 0.3f,  0.3f,  0.3f);	
		glTexCoord2f(0.0f, 0.5f); glVertex3f(-0.3f,  0.3f,  0.3f);	

		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.3f, -0.3f, -0.3f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.3f,  0.3f, -0.3f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.3f,  0.3f, -0.3f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.3f, -0.3f, -0.3f);	

		// Top Face
		glTexCoord2f(0.5f, 1.0f); glVertex3f(-0.3F,  0.3f, -0.3f);	
		glTexCoord2f(0.5f, 0.5f); glVertex3f(-0.3f,  0.3f, 0.3f);	
		glTexCoord2f(1.0f, 0.5f); glVertex3f( 0.3f,  0.3f,  0.3f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.3F,  0.3f, -0.3f);	

		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.3f, -0.3f, -0.3f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.3f, -0.3f, -0.3f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.3f, -0.3f,  0.3f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.3f, -0.3f,  0.3f);	

		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.3f, -0.3f, -0.3f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.3f,  0.3, -0.3f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.3f,  0.3f,  0.3f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.3f, -0.3f,  0.3f);	

		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3f, -0.3f, -0.3f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.3f, -0.3f,  0.3f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.3f,  0.3f,  0.3f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3f,  0.3f, -0.3f);

	glEnd();
  glPopMatrix ();

}

void init() {


  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (60, 1.5f, 1.5f,100);
  glMatrixMode (GL_MODELVIEW);
  glEnable (GL_DEPTH_TEST);
  glClearColor (0.1, 0.1, 0.1, 1);

}

GLvoid ReSizeGLScene(int Width, int Height)
{
    glViewport (0, 0, (GLsizei) Width, (GLsizei) Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(62.0, (GLfloat) Width / (GLfloat) Height, 0.5, 100.0);
   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int LoadTGA(TextureImage *texture, char *filename) {     

	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	
	GLubyte		TGAcompare[12];								
	GLubyte		header[6];									
	GLuint		bytesPerPixel;								
	GLuint		imageSize;									
	GLuint		temp;										
	GLuint		type=GL_RGBA;								
	GLuint		i;
	
	FILE *file = fopen(filename, "rb");						

	if(	file==NULL ||										
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||		
		fread(header,1,sizeof(header),file)!=sizeof(header))				
	{
		fclose(file);										
		return false;										
	}

	texture->width  = header[1] * 256 + header[0];			
	texture->height = header[3] * 256 + header[2];			
    
 	if(	texture->width	<=0	||								
		texture->height	<=0	||								
		(header[4]!=24 && header[4]!=32))					
	{
		fclose(file);										
		return false;										
	}

	texture->bpp	= header[4];							
	bytesPerPixel	= texture->bpp/8;						
	imageSize		= texture->width*texture->height*bytesPerPixel;	

	texture->imageData=(GLubyte *)malloc(imageSize);		

	if(	texture->imageData==NULL ||							
		fread(texture->imageData, 1, imageSize, file)!=imageSize)	
	{
		if(texture->imageData!=NULL)						
			free(texture->imageData);						

		fclose(file);										
		return false;										
	}

	for ( i=0; i<imageSize; i+=bytesPerPixel)		
	{														
		temp=texture->imageData[i];							
		texture->imageData[i] = texture->imageData[i + 2];	
		texture->imageData[i + 2] = temp;					
	}

	fclose (file);											

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].texID);					

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	
	if (texture[0].bpp==24)									
	{
		type=GL_RGB;										
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;											
}


GLvoid LoadGLTextures(GLvoid)
{
	LoadTGA(&texture[0], "parede.tga");
	LoadTGA(&texture[1], "verde1.tga");
	LoadTGA(&texture[2], "azul.tga");
}

GLvoid InitGL(GLvoid)
{
	
	LoadGLTextures();					// Load The Texture(s)
	glEnable(GL_TEXTURE_2D);			  // Enable Texture Mapping
	
	glClearColor(0.9f, 0.9f, 0.9f, 0.0f);		
	glClearDepth(1.0);							
				                
    glDepthFunc(GL_LEQUAL);                        
    glEnable(GL_DEPTH_TEST);                        
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);          
    glEnable(GL_BLEND);                            
    glEnable(GL_TEXTURE_2D);                       
    glEnable(GL_CULL_FACE);                     

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();																	// Calculate The Aspect Ratio Of The 

	glMatrixMode(GL_MODELVIEW);
}



void display (){

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity ();
  glTranslatef (-15, 15, -32);
  glRotatef (70, 20, 1, 0);
 // gluLookAt(10.0,0.0,10.0,5.0,5.0,0.0,5.0,0.0,0.0);
  // glOrtho(0.0,3.0,-3.0,3.0,0.0,0.0);
  drawGrid();
  imprimirLabirinto();
  theCube();
  
  glutSwapBuffers ();
  glFlush();

}

void keyboard (unsigned char key, int x, int y){

   if (key == 'w')
    {
      cz -= 1;			// frente / tras
    }
  else if (key == 's')
    {
      cz += 1;
    }				
 else if (key == 'a')		// esquerda/direita
    {
      cx -= 1;
    }
  else if (key == 'd')
    {
      cx += 1;
    } 

 else if (key == 27)
    {
      exit(0);
    }
				
  glutPostRedisplay ();
}


int main (int argc, char **argv)
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE);
  glutInitWindowSize (800, 600);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("Labirinto 3D");
  InitGL();
  init ();
  glutDisplayFunc (display);
  glutReshapeFunc(ReSizeGLScene);
  glutKeyboardFunc (keyboard);
  
  glutMainLoop ();
  return 0;
} 
