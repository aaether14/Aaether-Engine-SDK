#include <stdafx.h>





void TransformInfo::Load(boost::property_tree::ptree::value_type const& v, std::string info_name)
{


	if (v.first == info_name)
	{





		std::string base_position;
		std::string base_rotation;
		std::string base_scale;


		base_position = v.second.get<std::string>("Position");
		base_rotation = v.second.get<std::string>("Rotation");
		base_scale = v.second.get<std::string>("Scale");



		pos = Math::GetVecFromString(base_position);
		rot = Math::GetVecFromString(base_rotation);
		scale = Math::GetVecFromString(base_scale);


		matrix = Math::Translation(pos)*
			Math::Rotate(rot)*
			Math::Scale(scale);



	}



}




boost::property_tree::ptree TransformInfo::Save()
{



	boost::property_tree::ptree ptree_transform_info;
	ptree_transform_info.push_back(boost::property_tree::ptree::value_type("Position", boost::property_tree::ptree(Math::GetStringFromVec(pos))));
	ptree_transform_info.push_back(boost::property_tree::ptree::value_type("Rotation", boost::property_tree::ptree(Math::GetStringFromVec(rot))));
	ptree_transform_info.push_back(boost::property_tree::ptree::value_type("Scale", boost::property_tree::ptree(Math::GetStringFromVec(scale))));



	return ptree_transform_info;


}






