#include <stdafx.h>





bool ModelComponent::isValid(char * extension)
{



	//Check if valid extension


	std::vector<std::string> valid_extensions;
	valid_extensions.push_back(".aao");

	for (GLuint i = 0; i < valid_extensions.size(); i++)
		if (!std::string(extension).compare(valid_extensions[i]))
			return true;

		return false;


}



void ModelComponent::Load(char * path, char * extension)
{



	//Load acordingly


	if (!std::string(extension).compare(".aao"))
	{
		Aa_model * md = new Aa_model();
		md->Load(AString::char_to_str(path));
		model = static_cast<AModel*>(md);
	}


}
