#ifndef CAMERA_HPP
#define CAMERA_HPP




#include <stdafx.h>





/**


Basic camera implementation
Can support 1st and 3rd person views
Also has frustum functionality for frustum culling


*/
class Camera : public AModule
{


	/**
	Variable used by the camera controller
	*/
	GLfloat speed, mouse_speed, rotation_speed, base_speed;
	/**
	Angles to compute spherical coords
	*/
	GLdouble horizontalAngle, verticalAngle;
	/**
	Used to compute mouse move
	*/
	GLdouble last_x, last_y;


	/**
	Pointer to class that can create World and Camera matrices out of ViewInfo
	*/
	View *view_3rd;
	/**
	Info that View can use to create World and Camera matrices
	*/
	ViewInfo *info;
	/**
	Stores the 6 frustum planes
	*/
	Frustum * frustum;







public:



	/**
	Initializes data
	*/
	void Init();



	/**
	Cleans data
	*/
	void Clean();



	/**
	Get pointer to View
	*/
	inline View * GetView() { return this->view_3rd; };
	/**
	Get pointer to ViewInfo
	*/
	inline ViewInfo *GetInfo() { return this->info; }
	/**
	Get pointer to Frustum
	*/
	inline Frustum *GetFrustum() { return this->frustum; }


	/**
	Get base speed of camera controller
	*/
	inline GLfloat GetBaseSpeed(){ return this->base_speed; }
	/**
	Set base speed of camera controller
	*/
	inline void SetBaseSpeed(GLfloat base_speed){ this->base_speed = base_speed; }


	/**
	Create frustum out of Projection*View
	*/
	inline void SetFrustum(glm::mat4 MV) { this->frustum->Create(MV); }



	/**
	Matches interface
	*/
	inline void Enable(){}


	/**
	Process input to get ViewInfo
	*/
	void ProcessInput(ControllerSource * source);
	/**
	Compute angles out of mouse movement
	*/
	void ComputeAngles(ControllerSource * source);
	/**
	Fill ViewInfo
	*/
	void SetInfo(ControllerSource * source);




	/**
	Set horizontal angle of camera
	*/
	inline void setHorizontalAngle(GLfloat angle){ this->horizontalAngle = angle; }
	/**
	Set vertical angle of camera
	*/
	inline void setVerticalAngle(GLfloat angle){ this->verticalAngle = angle; }
	/**
	Get horizontal angle of camera
	*/
	inline GLdouble getHorizontalAngle() { return this->horizontalAngle; };
	/**
	Get veritcal angle of camera
	*/
	inline GLdouble getVerticalAngle() { return this->verticalAngle; }




};


#endif