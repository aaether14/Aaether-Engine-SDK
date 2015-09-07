#ifndef TERRAIN_STRIP_HPP
#define TERRAIN_STRIP_HPP





#include <stdafx.h>





#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define TANGENT_LOCATION     3





/**


Used to store terrain chunks


*/
class TerrainStrip
{



	/**
	In order to allocate OpenGL memory for vertex data
	*/
		enum VB_TYPES {
			INDEX_BUFFER,
			POS_VB,
			NORMAL_VB,
			TEXCOORD_VB,
			TANGENT_VB,
			NUM_VBs
		};


		GLuint m_VAO;
		GLuint m_Buffers[NUM_VBs];
		GLuint width, height;

     

		GLuint mipmaps;
		GLuint *mip_start_buffer;
		GLuint *mip_count_buffer;


	public:



		/**
		Initializes data
		*/
		void Init();
		/**
		Clears data
		*/
		void Clear();



		/**
		Calls Init()
		*/
		inline TerrainStrip() { this->Init(); }
		/**
		Calls Clear()
		*/
		inline ~TerrainStrip(){ this->Clear(); }



		/**
		Renders the given 'lod'
		*/
		void Render(GLuint lod);


		/**
		Create out of data
		*/
		void Create(GLuint strip_width, GLuint strip_height,
			glm::vec3 * heightData,
			glm::vec2 * uvData,
			glm::vec3 * normalData,
			glm::vec3 * tangentData,
			GLuint *index_buffer,
			GLuint index_size,
			GLuint *mip_start_buffer,
			GLuint *mip_count_buffer,
			GLuint mipmaps
			);


	};

	

#endif