#include <stdafx.h>





void ui_LightingRoot::Init(Environment * env, CEGUI::Window * Root)
{


	this->env = env;
	this->Root = Root;



}




void ui_LightingRoot::Reset()
{


	std::string def = "Frame/Settings/Tab1/ScrollablePane/__auto_container__/";


	static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner")))->setCurrentValue(env->model_ambient);
	static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner2")))->setCurrentValue(env->model_diffuse);
	static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner3")))->setCurrentValue(env->terrain_ambient);
	static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner4")))->setCurrentValue(env->terrain_diffuse);
	static_cast<CEGUI::ColourPicker*>((Root->getChild(def + "ColourPicker")))->setColour(UI_UTIL::GetCEGUIColour(env->sun_color));
	static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner5")))->setCurrentValue(env->fog_density);
	static_cast<CEGUI::ColourPicker*>((Root->getChild(def + "ColourPicker2")))->setColour(UI_UTIL::GetCEGUIColour(env->fog_color));


}




void ui_LightingRoot::Clean()
{






}





void ui_LightingRoot::SyncUI()
{



	if (env->ShouldReset())
	{
		Reset();
		env->SetShouldReset(false);
	}



	if (Root->getChild("Frame/Settings/Tab1")->isVisible())
	{


		std::string def = "Frame/Settings/Tab1/ScrollablePane/__auto_container__/";


		env->model_ambient = static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner")))->getCurrentValue();
		env->model_diffuse = static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner2")))->getCurrentValue();
		env->terrain_ambient = static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner3")))->getCurrentValue();
		env->terrain_diffuse = static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner4")))->getCurrentValue();
		env->sun_color = glm::vec3(UI_UTIL::GetGLMColour(static_cast<CEGUI::ColourPicker*>((Root->getChild(def + "ColourPicker")))->getColour()));
		env->fog_density = static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner5")))->getCurrentValue();
		env->fog_color = glm::vec3(UI_UTIL::GetGLMColour(static_cast<CEGUI::ColourPicker*>((Root->getChild(def + "ColourPicker2")))->getColour()));



	}


}


