#ifndef TRANSFORM_UI_HPP
#define TRANSFORM_UI_HPP




#include <stdafx.h>




/**


Gathering transform info from ui


*/
class ui_TransformTab
{


	CEGUI::Window * FrameRoot;



	/**
	Called when Radio button group switched to 'Position'
	*/
	bool RadioPositionChanged(const CEGUI::EventArgs& e);
	/**
	Called when Radio button group switched to 'Rotation'
	*/
	bool RadioRotationChanged(const CEGUI::EventArgs& e);
	/**
	Called when Radio button group switched to 'Scale'
	*/
	bool RadioScaleChanged(const CEGUI::EventArgs& e);



	/**
	Called when 'X' Spinner changes value
	*/
	bool SpinnerXChanged(const CEGUI::EventArgs& e);
	/**
	Called when 'Y' Spinner changes value
	*/
	bool SpinnerYChanged(const CEGUI::EventArgs& e);
	/**
	Called when 'Z' Spinner changes value
	*/
	bool SpinnerZChanged(const CEGUI::EventArgs& e);



	/**
	Called when 'close button' is clicked
	*/
	inline bool CloseWindow(const CEGUI::EventArgs& e){ FrameRoot->hide(); return 1; }




	/**
	Transformation info to placeable entity
	*/
	class PaletteInfo
	{


	public:


		glm::mat3 trans;
		inline void Reset(){ trans[0] = glm::vec3(0.0); trans[1] = glm::vec3(0.0); trans[2] = glm::vec3(1.0); }


	}*p_info;


	GLuint update_id;



public:



	/**
	Calls Init()
	*/
	inline ui_TransformTab(){ this->Init(); }
	/**
	Initializes data
	*/
	void Init();



	/**
	Calls Clean()
	*/
	inline ~ui_TransformTab(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();


	/**
	Get pointer to transformation info
	*/
	inline PaletteInfo * GetPInfo(){ return p_info; }


	/**
    Update data UI wise
	*/
	void UpdateData();
	/**
	Update the step value spinners use to modify their value
	*/
	void UpdateStepData(GLfloat step_size);


};



#endif