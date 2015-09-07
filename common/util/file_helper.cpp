#include <stdafx.h>





namespace AFile
{


	bool copyDir(
		boost::filesystem::path const & source,
		boost::filesystem::path const & destination
		)
	{
		namespace fs = boost::filesystem;
		try
		{
			// Check whether the function call is valid
			if (
				!fs::exists(source) ||
				!fs::is_directory(source)
				)
			{
				std::cerr << "Source directory " << source.string()
					<< " does not exist or is not a directory." << '\n'
					;
				return false;
			}
			if (fs::exists(destination))
			{
				std::cerr << "Destination directory " << destination.string()
					<< " already exists." << '\n'
					;
				return false;
			}
			// Create the destination directory
			if (!fs::create_directory(destination))
			{
				std::cerr << "Unable to create destination directory"
					<< destination.string() << '\n'
					;
				return false;
			}
		}
		catch (fs::filesystem_error const & e)
		{
			std::cerr << e.what() << '\n';
			return false;
		}
		// Iterate through the source directory
		for (
			fs::directory_iterator file(source);
			file != fs::directory_iterator(); ++file
			)
		{
			try
			{
				fs::path current(file->path());
				if (fs::is_directory(current))
				{
					// Found directory: Recursion
					if (
						!copyDir(
						current,
						destination / current.filename()
						)
						)
					{
						return false;
					}
				}
				else
				{
					// Found file: Copy
					fs::copy_file(
						current,
						destination / current.filename()
						);
				}
			}
			catch (fs::filesystem_error const & e)
			{
				std::cerr << e.what() << '\n';
			}
		}
		return true;
	}



	std::string GetFileWithExtension(std::string path, std::string extension)
	{


		boost::filesystem::directory_iterator iterator(path);
		for (; iterator != boost::filesystem::directory_iterator(); ++iterator)
			if (boost::filesystem::is_regular_file(iterator->path()))
			{
			std::string file_extension = boost::filesystem::extension(iterator->path());
			std::transform(file_extension.begin(), file_extension.end(), file_extension.begin(), ::tolower);
			if (!extension.compare(file_extension))
				return iterator->path().string();
			}

		return STRING_ERROR;


	}



	std::string GetFileWithExtensionList(std::string path, std::vector<std::string>extensions)
	{

		for (GLuint i = 0; i < extensions.size(); i++)
			if (GetFileWithExtension(path, extensions[i]).compare(STRING_ERROR) != 0)
			return GetFileWithExtension(path, extensions[i]);


		return STRING_ERROR;

	}



	long GetFileSize(const char* filePath)
	{
		FILE* pFile = fopen(filePath, "rb");

		if (pFile == NULL)
			exit(1);

		fseek(pFile, 0, SEEK_END);
		long lSize = ftell(pFile);
		rewind(pFile);
		fclose(pFile);

		return lSize;
	}



	unsigned char * ReadFile(const char * filePath)
	{
		FILE * pFile;
		long lSize;
		unsigned char * buffer;
		size_t result;

		pFile = fopen(filePath, "rb");
		if (pFile == NULL) { fputs("File error", stderr); exit(1); }

		// obtain file size:
		fseek(pFile, 0, SEEK_END);
		lSize = ftell(pFile);
		rewind(pFile);

		// allocate memory to contain the whole file:
		buffer = (unsigned char*)malloc(sizeof(unsigned char)*lSize);
		if (buffer == NULL) { fputs("Memory error", stderr); exit(1); }

		// copy the file into the buffer:
		result = fread(buffer, 1, lSize, pFile);
		if (result != lSize) { fputs("Reading error", stderr); exit(1); }

		// terminate
		fclose(pFile);

		// the whole file is now loaded in the memory buffer. Return pointer to data.
		return buffer;
	}




	void BlowfishEncryptFile(const char * path)
	{

 
		long multiple_of_eight_size;
		long file_size = GetFileSize(path);
		if (double(file_size / 8.0) != long(file_size / 8))
			multiple_of_eight_size = (file_size / 8 + 1) * 8;
		else
			multiple_of_eight_size = file_size;




		int byte_pad = multiple_of_eight_size - file_size;
		unsigned char * file = ReadFile(path);
		unsigned char * buffer = (unsigned char*)malloc(multiple_of_eight_size);
		unsigned char * buffer2 = (unsigned char*)malloc(multiple_of_eight_size);
		memcpy(buffer, file, file_size);



		for (int i = 0; i < byte_pad; i++)
			buffer[file_size + i] = '\0';




		try
		{


			CBlowFish oBlowFish((unsigned char*)"abcdefgh", 8);
			oBlowFish.Encrypt((unsigned char*)buffer, (unsigned char*)buffer2, multiple_of_eight_size);
			std::ofstream fout(path, std::ios::binary);
			fout.write((const char*)(buffer2), multiple_of_eight_size);
			fout.close();



		}
		catch (std::exception& roException)
		{
			std::cout << roException.what() << std::endl;
		}

	}



	std::string BlowfishDecryptFile(const char * path)
	{



		long multiple_of_eight_size;
		long file_size = GetFileSize(path);
		if (double(file_size / 8.0) != long(file_size / 8))
			multiple_of_eight_size = (file_size / 8 + 1) * 8;
		else
			multiple_of_eight_size = file_size;






		unsigned char * file = ReadFile(path);
		unsigned char * buffer = (unsigned char*)malloc(multiple_of_eight_size);
		unsigned char * buffer2 = (unsigned char*)malloc(multiple_of_eight_size);
		memcpy(buffer, file, file_size);



		std::string string_cypher;




		try
		{


			CBlowFish oBlowFish((unsigned char*)"abcdefgh", 8);
			oBlowFish.Decrypt((unsigned char*)buffer, (unsigned char*)buffer2, multiple_of_eight_size);


			file_size--;
			while (buffer2[file_size - 1] == 0)
				file_size--;


			string_cypher.resize(file_size);
			memcpy(&string_cypher[0], buffer2, file_size);




		}
		catch (std::exception& roException)
		{
			std::cout << roException.what() << std::endl;
		}


		return string_cypher;

	}



}