#include <stdafx.h>





void QuadNode::Create(glm::ivec2 sq_points[4],
	GLuint chunk_height, GLuint chunk_width,
	GLuint width,
	glm::vec3 *heightData)

{


	
	for (GLuint i = 0; i < 4; i++)
		h_points[i] = heightData[sq_points[i].y*(chunk_height - 1)*width + sq_points[i].x*(chunk_width - 1)];



	center = h_points[0] + (h_points[3] - h_points[0]) / 2.0f;
	radius = glm::distance(h_points[0], h_points[3]) / 2.0f;




	if (sq_points[3].x - sq_points[0].x > 1 && sq_points[3].y - sq_points[0].y > 1)
	{





		glm::ivec2 new_points[4];
		glm::ivec2 new_points2[4];




		new_points[0].x = sq_points[0].x;
		new_points[0].y = sq_points[0].y;

		new_points[1].x = (sq_points[3].x - sq_points[0].x) / 2 + sq_points[0].x;
		new_points[1].y = sq_points[1].y;

		new_points[2].x = sq_points[2].x;
		new_points[2].y = (sq_points[3].y - sq_points[0].y) / 2 + sq_points[0].y;

		new_points[3].x = (sq_points[3].x - sq_points[0].x) / 2 + sq_points[0].x;
		new_points[3].y = (sq_points[3].y - sq_points[0].y) / 2 + sq_points[0].y;




		for (GLuint i = 0; i < 4; i++)
		{



			for (GLuint j = 0; j < 4; j++)
				new_points2[j] = new_points[j] + (new_points[i]-sq_points[0]);


			boost::shared_ptr<QuadNode> new_node(new QuadNode);
			new_node.get()->Create(new_points2, chunk_height, chunk_width, width, heightData);
			nodes.push_back(new_node);


		}




	}



}


void QuadNode::Save(std::ofstream *fout, GLuint width, GLuint chunk_height, GLuint chunk_width,
	glm::vec3 *heightData,
	glm::vec2 *uvData,
	glm::vec3 *normalData,
	glm::vec3 *tangentData,
	GLfloat min_x,
	GLfloat min_z)
{




	fout->write((const char*)&h_points, 4 * sizeof(glm::vec3));
	fout->write((const char*)&center, sizeof(glm::vec3));
	fout->write((const char*)&radius, sizeof(GLfloat));





	if (nodes.size() > 0)
	for (GLuint i = 0; i < 4; i++)
			nodes[i]->Save(fout,
			width,
			chunk_height,chunk_width,
			heightData,
			uvData,
			normalData,
			tangentData,
			min_x,
			min_z);
	else
	{



		ind = (h_points[0].z / min_z)*((width - 1) / (chunk_width - 1)) + (h_points[0].x / min_x);
		fout->write((const char*)&(this->ind), sizeof(GLuint));






		GLuint offset1 = ((h_points[0].z / min_z)*width*(chunk_height - 1) + (h_points[0].x / min_x) * (chunk_width - 1));




		for (GLuint z1 = 0; z1 < chunk_height; z1++)
		{

			GLuint offset2 = z1*width;



			fout->write((const char*)&heightData[0] + (offset1 + offset2) * sizeof(glm::vec3),
				chunk_width * sizeof(glm::vec3));

			fout->write((const char*)&uvData[0] + (offset1 + offset2) * sizeof(glm::vec2),
				chunk_width * sizeof(glm::vec2));

			fout->write((const char*)&normalData[0] + (offset1 + offset2) * sizeof(glm::vec3),
				chunk_width * sizeof(glm::vec3));

			fout->write((const char*)&tangentData[0] + (offset1 + offset2) * sizeof(glm::vec3),
				chunk_width * sizeof(glm::vec3));


		}


	}




}



void QuadNode::Load(std::ifstream *fin,
	GLuint chunk_width, GLuint chunk_height,
	glm::vec3 * heightData,
	glm::vec2 * uvData,
	glm::vec3 * normalData,
	glm::vec3 * tangentData,
	GLuint *index_buffer,
	GLuint index_size,
	GLuint *mip_start_buffer,
	GLuint *mip_count_buffer,
	GLuint mipmaps,
	GLfloat min_x,
	GLfloat min_z)

{


	   fin->read((char*)&h_points, 4 * sizeof(glm::vec3));
	   fin->read((char*)&center, sizeof(glm::vec3));
	   fin->read((char*)&radius, sizeof(GLfloat));





	   if ((h_points[3] - h_points[0]).x > min_x && (h_points[3] - h_points[0]).z > min_z)
	   {




		   for (GLuint i = 0; i < 4; i++)
		   {



			   boost::shared_ptr<QuadNode> new_node(new QuadNode);
               new_node.get()->Load(fin,
				   chunk_width,
				   chunk_height,
				   heightData,
				   uvData,
				   normalData,
				   tangentData,
				   index_buffer,
				   index_size,
				   mip_start_buffer,
				   mip_count_buffer,
				   mipmaps,
				   min_x,
				   min_z);



			   nodes.push_back(new_node);


		   }


	   }
	   else

	   {

		 
		   fin->read((char*)&(this->ind), sizeof(GLuint));
           visible = false;



		   for (GLuint z1 = 0; z1 < chunk_height; z1++)
		   {

			   fin->read((char*)&heightData[0] + z1*chunk_width*sizeof(glm::vec3), chunk_width * sizeof(glm::vec3));
			   fin->read((char*)&uvData[0] + z1*chunk_width*sizeof(glm::vec2), chunk_width * sizeof(glm::vec2));
			   fin->read((char*)&normalData[0] + z1*chunk_width*sizeof(glm::vec3), chunk_width * sizeof(glm::vec3));
			   fin->read((char*)&tangentData[0] + z1*chunk_width*sizeof(glm::vec3), chunk_width * sizeof(glm::vec3));

		   }


		   chunk.reset(new TerrainStrip);
		   chunk->Create(chunk_width, chunk_height,
			   heightData,
			   uvData,
			   normalData,
			   tangentData,
			   index_buffer,
			   index_size,
			   mip_start_buffer,
			   mip_count_buffer,
			   mipmaps);


	   }




}











void QuadTree::Create(GLuint quad_height, GLuint quad_width,
	GLuint chunk_height, GLuint chunk_width,
	GLuint width,
	glm::vec3 *heightData)
{


	glm::ivec2 points[4];




	points[0].x = 0;
	points[0].y = 0;

	points[1].x = quad_width - 1;
	points[1].y = 0;

	points[2].x = 0;
	points[2].y = quad_height - 1;

	points[3].x = quad_width - 1;
	points[3].y = quad_height - 1;



	tree_width = quad_width-1;
	tree_height = quad_height-1;
	start_node->Create(points, chunk_height, chunk_width, width, heightData);


}



void QuadTree::Save(std::ofstream *fout, GLuint width, GLuint chunk_height, GLuint chunk_width,
	glm::vec3 *heightData,
	glm::vec2 *uvData,
	glm::vec3 *normalData,
	glm::vec3 *tangentData,
	GLfloat min_x,
	GLfloat min_z)
{




	AFile::WriteToFile(*fout, tree_width);
	AFile::WriteToFile(*fout, tree_height);
	



	start_node->Save(fout,
		width,
		chunk_height,
		chunk_width,
		heightData,
		uvData,
		normalData,
		tangentData,
		min_x,
		min_z);


}


void QuadTree::Load(std::ifstream *fin,
	GLuint chunk_width, GLuint chunk_height,
	glm::vec3 * heightData,
	glm::vec2 * uvData,
	glm::vec3 * normalData,
	glm::vec3 * tangentData,
	GLuint *index_buffer,
	GLuint index_size,
	GLuint *mip_start_buffer,
	GLuint *mip_count_buffer,
	GLuint mipmaps,
	GLfloat min_x,
	GLfloat min_z)
{




	this->min_x = min_x;
	this->min_z = min_z;
	AFile::ReadFromFile(*fin,tree_width);
	AFile::ReadFromFile(*fin, tree_height);
	
	


	start_node->Load(fin,
		chunk_width,
		chunk_height,
		heightData,
		uvData,
		normalData,
		tangentData,
		index_buffer,
		index_size,
		mip_start_buffer,
		mip_count_buffer,
		mipmaps,
		min_x,
		min_z);




}














