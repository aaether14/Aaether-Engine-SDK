#ifndef TERRAIN_HPP
#define TERRAIN_HPP





#include <stdafx.h>





#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))




#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define TANGENT_LOCATION     3



#define BASE_DIR "data/terrain_textures/"





/**


Terrain implementation
supporting splatting and bump-mapping


*/
class Terrain
{





	GLuint colormap_tex, texture_array, normal_texture_array;
	boost::shared_ptr<TerrainShader::TextureAttributes> tex_data;


	GLuint WIDTH, HEIGHT;
	GLfloat *heightField, fSizeX, fSizeZ;
	GLuint num_chunks;
	GLuint chunk_rows, chunk_cols;


	boost::shared_ptr<QuadTree> q_tree;
	GLuint max_mips;


	/**
	The engine is using a quad tree to render
	*/
	void RenderQuad(Frustum * frustum, QuadNode * node);



public:



	/**
	Calls Init()
	*/
	inline Terrain() { Init(); }
	/**
	Calls Clean()
	*/
	inline ~Terrain() { Clean(); }


	/**
	Initializes data
	*/
	void Init();
	/**
	Cleans Data
	*/
	void Clean();



	/**
	Returns width of heightmap
	*/
	inline GLint Width(){ return this->WIDTH; }
	/**
	Returns height of heightmap
	*/
	inline GLint Height(){ return this->HEIGHT; }
	/**
	Returns scale on X axis
	*/
	inline GLfloat ScaleX(){ return this->fSizeX; }
	/**
	Returns scale on Z axis
	*/
	inline GLfloat ScaleZ(){ return this->fSizeZ; }




	/**
	Get pointer to quad tree
	*/
	inline QuadTree * GetTree(){ return q_tree.get(); }
	/**
	Compute height at given (X,Z) point
	*/
	inline GLfloat getHeight(GLint x, GLint z) { return heightField[z*WIDTH + x]; }
	/**
	Get texture attributes data
	*/
	inline TerrainShader::TextureAttributes * GetTextureAttributes(){ return tex_data.get(); }

	/**
	Load splat map, splat textures and normal textures
	*/
	void LoadColorFiles(char*tile_path, char*texture_set_path, char*normal_set_path,
		char* texture_attributes_set);



	/**
	Create own's engine format of terrain from 8 or 16 bit heightmap (ch1) and export to 'path'
	*/
	void CreateTerra(char *path, 
		char*ch1,
		GLfloat fSizeX, GLfloat fSizeZ, GLfloat fSizeY1,
		GLuint chunk_height, GLuint chunk_width,
		GLuint mipmaps);


	/**
	Render terrain with frustum culling
	*/
	void Render(Frustum * frustum, bool wired = false);



	/**
	Save chunks of terrain
	*/
	void SaveChunks(char * path,
		BYTE * bits,
		GLfloat fSizeX, GLfloat fSizeZ, GLfloat fSizeY1,
		GLuint chunk_height, GLuint chunk_width,
		GLuint height, GLuint width,
		GLuint mipmaps
		);


	/**
	Load chunks of terrain
	*/
	void LoadChunks(char * path);
};


/**
Compute interpolated height at given (X,Z) point
*/
GLfloat HeightAt(Terrain*terrain, GLfloat x, GLfloat z);


#endif