#include <stdafx.h>




namespace Math
{



	glm::mat4 Translation(glm::vec3 t_vec)
	{


		glm::mat4 tr_matrix(1.0f);
		tr_matrix[3] = glm::vec4(t_vec, 1.0);
		return tr_matrix;


	}




	glm::mat4 Scale(glm::vec3 t_vec)
	{



		glm::mat4 tr_matrix(1.0f);
		tr_matrix[0][0] = t_vec.x;
		tr_matrix[1][1] = t_vec.y;
		tr_matrix[2][2] = t_vec.z;
		return tr_matrix;



	}






	void print_matrix(glm::mat4 m)
	{


		printf("%1.2f, %1.2f, %1.2f, %1.2f,\n%1.2f, %1.2f, %1.2f, %1.2f,\n%1.2f, %1.2f, %1.2f, %1.2f,\n%1.2f, %1.2f, %1.2f, %1.2f\n\n",
			m[0][0], m[0][1], m[0][2], m[0][3],
			m[1][0], m[1][1], m[1][2], m[1][3],
			m[2][0], m[2][1], m[2][2], m[2][3],
			m[3][0], m[3][1], m[3][2], m[3][3]
			);

	}





	void print_vec3(glm::vec3 v)
	{


		printf("%4.4f, %4.4f, %4.4f\n\n", v.x, v.y, v.z);


	}







	void print_ivec2(glm::ivec2 v)


	{


		printf("%i, %i\n", v.x, v.y);


	}



	GLuint SphereInFrustum(Frustum *frustum, glm::vec3 pos, GLfloat radius)
	{


		GLuint p;
		GLuint c = 0;
		GLfloat d;


		for (p = 0; p < 4; p++)
		{


			d = glm::dot(frustum->getPlanes()[p].normal, pos) + frustum->getPlanes()[p].distance;
			if (d <= -radius)
				return 0;
			if (d > radius)
				c++;

		}


		return (c == 4) ? 2 : 1;



	}









	glm::vec3 GetVecFromString(std::string str)
	{


		float values[3];
		char begin = 0;


		for (GLuint i = 0; i < 2; i++)
		{
			values[i] = std::stof(str.substr(begin, str.find_first_of(", ", begin)));
			begin = str.find_first_of(", ", begin) + 1;
		}
		values[2] = std::stof(str.substr(str.find_last_of(", ")));


		glm::vec3 v;
		memcpy(&v[0], &values[0], sizeof(glm::vec3));
		return v;


	}



	std::string GetStringFromVec(glm::vec3 v)
	{

		std::ostringstream stream;
		stream << v.x << ", " << v.y << ", " << v.z;
		return stream.str();

	}







}

