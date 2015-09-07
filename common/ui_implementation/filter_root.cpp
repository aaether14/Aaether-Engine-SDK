#include <stdafx.h>




void ui_FilterRoot::Init(FilterSettings * filter_settings, CEGUI::Window * Root)
{



	this->filter_settings = filter_settings;
	this->Root = Root;


}




void ui_FilterRoot::Reset()
{



	std::string def = "Frame/Settings/";


	ResetSSAO(def + "Tab2/");
	ResetHDR(def + "Tab3/");
	ResetFXAA(def + "Tab4/");
	ResetDoF(def + "Tab5/");



}



void ui_FilterRoot::ResetSSAO(std::string def)
{


	static_cast<CEGUI::ToggleButton*>((Root->getChild(def + "Checkbox")))->setSelected(filter_settings->SSAO.Enabled);
	static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner")))->setCurrentValue(filter_settings->SSAO.Radius);
	static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner2")))->setCurrentValue(filter_settings->SSAO.Power);
	static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner3")))->setCurrentValue(filter_settings->SSAO.NumSamples);


}




void ui_FilterRoot::ResetHDR(std::string def)
{


	static_cast<CEGUI::ToggleButton*>((Root->getChild(def + "Checkbox")))->setSelected(filter_settings->HDR.Bloom.Enabled);
	static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner")))->setCurrentValue(filter_settings->HDR.Bloom.Whitepoint);


}



void ui_FilterRoot::ResetFXAA(std::string def)
{


	static_cast<CEGUI::ToggleButton*>((Root->getChild(def + "Checkbox")))->setSelected(filter_settings->FXAA.Enabled);
	static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner")))->setCurrentValue(filter_settings->FXAA.span_max);
	static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner2")))->setCurrentValue(filter_settings->FXAA.reduce_min);
	static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner3")))->setCurrentValue(filter_settings->FXAA.reduce_mul);



}




void ui_FilterRoot::ResetDoF(std::string def)
{


	static_cast<CEGUI::ToggleButton*>((Root->getChild(def + "Checkbox")))->setSelected(filter_settings->DoF.Enabled);


}



void ui_FilterRoot::Clean()
{





}




void ui_FilterRoot::SyncUI()
{


	if (filter_settings->ShouldReset())
	{
		Reset();
		filter_settings->SetShouldReset(false);
	}



	std::string def = "Frame/Settings/";


	SyncSSAO(def + "Tab2/");
	SyncHDR(def + "Tab3/");
	SyncFXAA(def + "Tab4/");
	SyncDoF(def + "Tab5/");


}




void ui_FilterRoot::SyncSSAO(std::string def)
{


	if (Root->getChild(def.substr(0, def.length() - 1))->isVisible())
	{



		filter_settings->SSAO.Enabled = static_cast<CEGUI::ToggleButton*>((Root->getChild(def + "Checkbox")))->isSelected();
		filter_settings->SSAO.Radius = static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner")))->getCurrentValue();
		filter_settings->SSAO.Power = static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner2")))->getCurrentValue();
		filter_settings->SSAO.NumSamples = static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner3")))->getCurrentValue();


	}

}



void ui_FilterRoot::SyncHDR(std::string def)
{


	if (Root->getChild(def.substr(0, def.length() - 1))->isVisible())
	{


		filter_settings->HDR.Bloom.Enabled = static_cast<CEGUI::ToggleButton*>((Root->getChild(def + "Checkbox")))->isSelected();
		filter_settings->HDR.Bloom.Whitepoint = static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner")))->getCurrentValue();


	}

}



void ui_FilterRoot::SyncFXAA(std::string def)
{


	if (Root->getChild(def.substr(0, def.length() - 1))->isVisible())
	{


		filter_settings->FXAA.Enabled = static_cast<CEGUI::ToggleButton*>((Root->getChild(def + "Checkbox")))->isSelected();
		filter_settings->FXAA.span_max = static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner")))->getCurrentValue();
		filter_settings->FXAA.reduce_min = static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner2")))->getCurrentValue();
		filter_settings->FXAA.reduce_mul = static_cast<CEGUI::Spinner*>((Root->getChild(def + "Spinner3")))->getCurrentValue();


	}


}




void ui_FilterRoot::SyncDoF(std::string def)
{

	if (Root->getChild(def.substr(0, def.length() - 1))->isVisible())
	{


		filter_settings->DoF.Enabled = static_cast<CEGUI::ToggleButton*>((Root->getChild(def + "Checkbox")))->isSelected();



	}
}



