#ifndef VIEW_HPP
#define VIEW_HPP




#include <stdafx.h>





#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif




#define RENDER_DISTANCE 256





/**
Storing info that can ve used by View to create view projection matrix
*/
class ViewInfo

{

	/*SOME INFO*/

	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;
	GLfloat distance;
	GLfloat render_distance;
	GLfloat z_near;
	GLfloat FoV;
	GLfloat ratio;


public:

	inline ViewInfo() { this->Init(); }
	void Init();


	/*SOME MORE INFO*/


	/**
	Gets values of another ViewInfo
	*/
	inline void SetFromOther(ViewInfo * other)
	{
		this->position = other->getCameraPos();
		this->direction = other->getDirection();
		this->up = other->getUpVec();
		this->distance = other->getDistance();
		this->render_distance = other->getRenderDistance();
		this->z_near = other->getNear();
		this->FoV = other->getFoV();
		this->ratio = other->getRatio();

	}

	/*
	Setters and getters
	*/
	inline glm::vec3 getCameraPos() { return position; }
	inline void setUpVec(glm::vec3 t_vec) { this->up = t_vec; }
	inline glm::vec3 getDirection() { return direction; }
	inline GLfloat getRatio(){ return this->ratio; }
	inline void setRatio(GLfloat ratio) { this->ratio = ratio; }
	inline glm::vec3 getUpVec() { return this->up; }
	inline GLfloat getNear() { return this->z_near; }
	inline void setNear(GLfloat _near) { this->z_near = _near; }
	inline void SetRenderDistance(GLfloat r_d) { this->render_distance = r_d; }
	inline void SetCameraPos(glm::vec3 pos) { this->position = pos; }
	inline void SetCameraY(GLfloat y) { this->position.y = y; }
	inline void SetDistance(GLfloat new_distance) { this->distance = new_distance; }
	inline void setDirection(glm::vec3 dir) { this->direction = dir; }
	inline GLfloat getFoV() { return this->FoV; }
	inline GLfloat getTanHalfFov(){ return tanf((FoV / 2.0f) * M_PI / 180.0); }
	inline void setFov(GLfloat FoV) { this->FoV = FoV; }
	inline GLfloat getRenderDistance() { return this->render_distance; }
	inline GLfloat getDistance() { return this->distance; };


	/*END OF MORE INFO*/



};





/**
Using information from ViewInfo, this class creates a view projection matrix for world to camera to clipspace transformation
*/
class View
{


	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;



	/**
	Creates a 3rd person view from parameters
	*/
	void Create3rd(GLfloat FoV, GLfloat ratio, GLfloat z_near, GLfloat z_far, GLfloat distance, glm::vec3 position, glm::vec3 direction, glm::vec3 up);
	/**
	Creates a 1st person view from parameters
	*/
	void Create1st(GLfloat FoV, GLfloat ratio, GLfloat z_near, GLfloat z_far, glm::vec3 position, glm::vec3 direction, glm::vec3 up);



public:



	/**
	Creates a 3rd person view from a ViewInfo
	*/
	void Create3rd(ViewInfo *info);
	/**
	Creates a 1st person view from a ViewInfo
	*/
	void Create1st(ViewInfo *info);
	/**
	Returns view matrix aka world matrix
	*/
	inline glm::mat4 getViewMatrix() { return ViewMatrix; };
	/**
	Returns projection matrix aka camera matrix
	*/
	inline glm::mat4 getProjectionMatrix() { return ProjectionMatrix; }
	/**
	Returns view projection matrix
	*/
	inline glm::mat4 getCamera(){ return ProjectionMatrix*ViewMatrix; }
	/**
	Set projection
	*/
	inline void SetProjection(glm::mat4 ProjectionMatrix){ this->ProjectionMatrix = ProjectionMatrix; }
	/**
	Set view matrix
	*/
	inline void SetView(glm::mat4 ViewMatrix){ this->ViewMatrix = ViewMatrix; }



};



/**
Class storing plane equation ax + by + cz + d = 0
*/
class Plane

{


public:

	
	glm::vec3 normal;
	GLfloat distance;


	/**
	Normalizes plane
	*/
	void Normalize();


};



/**
Camera model consiting of 6 planes, resembles how human eye does projection
*/
class Frustum
{


	
	Plane*planes;



public:



	/**
	Initialize planes
	*/
	inline Frustum() { planes = new Plane[6]; }
	/**
	Delete planes
	*/
	inline ~Frustum() { delete planes; }

    
	/**
	Pointer to plane array
	*/
	inline Plane*getPlanes(){ return planes; }


	/**
	Create out of matrix
	*/
	void Create(glm::mat4 MVP);





};





#endif