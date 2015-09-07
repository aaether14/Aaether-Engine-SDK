#include <stdafx.h>





void Shader::Add(char * path, GLenum type)
{


	GLuint ShaderID = glCreateShader(type);
	std::string ShaderCode = AString::LoadFileToString(path);




	std::string sub = "#include";
	std::string sub2 = "\"";
	std::string s_path = std::string(path);
	size_t pos = ShaderCode.find(sub, 0);


	while (pos != std::string::npos)
	{


		size_t f_pos = pos;
		size_t t_pos = ShaderCode.find(sub2, pos + 1);
		pos = ShaderCode.find(sub2, t_pos + 1);

		std::string t_file = s_path.substr(0, s_path.find_last_of("//") + 1) + ShaderCode.substr(t_pos + 1, pos - (t_pos + 1));
		ShaderCode.erase(f_pos, pos - f_pos + 1);
		ShaderCode.insert(f_pos, AString::LoadFileToString(AString::char_to_str(t_file)));
		pos = ShaderCode.find(sub, f_pos + 1);


	}




	GLint Result = GL_FALSE;
	int InfoLogLength;



	printf("Compiling shader : %s\n", path);
	char const * SourcePointer = ShaderCode.c_str();
	glShaderSource(ShaderID, 1, &SourcePointer, NULL);
	glCompileShader(ShaderID);




	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		printf("%s\n", &ShaderErrorMessage[0]);
	}



	glAttachShader(this->program, ShaderID);
	glDeleteShader(ShaderID);




}



void Shader::Link()
{

	GLint Result = GL_FALSE;
	int InfoLogLength;


	printf("Linking program\n");
	glLinkProgram(this->program);



	glGetProgramiv(this->program, GL_LINK_STATUS, &Result);
	glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &InfoLogLength);



	if (InfoLogLength > 0)
	{


		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(this->program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);



	}


}