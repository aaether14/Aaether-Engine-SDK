#include <stdafx.h>




void Quad::Init()
{

	glGenVertexArrays(1, &this->m_VAO);
	glBindVertexArray(m_VAO);


	GLfloat buffer[] =
	{
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		-1.0f, 1.0f,
		1.0f, -1.0f,
		1.0f, 1.0f
	};


	glGenBuffers(1, &this->m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), &buffer, GL_STATIC_DRAW);



	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);
	glBindVertexArray(0);

}



void Quad::Render()
{


	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);



}




void Quad::Clean()
{


	if (m_VAO != 0)
		glDeleteVertexArrays(1, &m_VAO);
		

}




