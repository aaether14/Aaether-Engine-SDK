#pragma once




#ifdef _MSC_VER
#define NOMINMAX
#endif




//---------------------------------------------//

#include <GL/glew.h>
#include <glfw3.h>


//---------------------------------------------//


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

//---------------------------------------------//

#include <boost/filesystem.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <boost/functional/hash/hash.hpp>

//---------------------------------------------//

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <exception>
#include <time.h>
#include <typeinfo>

//---------------------------------------------//

#include <crypt/Blowfish.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/CommonDialogs/ColourPicker/ColourPicker.h>
#include <CEGUI/CEGUI.h>
#include <FreeImage.h>

//---------------------------------------------//

#include <assimp/Importer.hpp>   
#include <assimp/scene.h>    
#include <assimp/postprocess.h> 
#include <assimp/Exporter.hpp>

//---------------------------------------------//

#include <util/view.hpp>
#include <util/math_helper.hpp>
#include <util/string_helper.hpp>
#include <util/file_helper.hpp>
#include <util/utils.hpp>

//---------------------------------------------//

#include <texture/texture.hpp>

//---------------------------------------------//

#include <base/base_component.hpp>
#include <base/base_model_loader.hpp>
#include <base/base_module.hpp>
#include <base/base_state_saver.hpp>
#include <base/base_resource_loader.hpp>
#include <base/base_instance_info.hpp>
#include <base/base_entity_instance.hpp>

//---------------------------------------------//

#include <settings/environment.hpp>
#include <settings/filter_settings.hpp>

//---------------------------------------------//

#include <shader/shader.hpp>

//---------------------------------------------//

#include <screen_render.hpp>

//---------------------------------------------//

#include <light/light.hpp>

//---------------------------------------------//

#include <terrain/terrain_strip.hpp>
#include <terrain/quad_tree.hpp>
#include <terrain_implementation/terrain_shader.hpp>
#include <terrain/terrain.hpp>

//---------------------------------------------//

#include <mesh_implementation/mesh_shader.hpp>

//---------------------------------------------//

#include <filters/basic_filter.hpp>
#include <filters/blur.hpp>
#include <filters/dof.hpp>
#include <filters/exponential_shadow_map.hpp>
#include <filters/fxaa.hpp>
#include <filters/g_buffer.hpp>
#include <filters/hdr.hpp>
#include <filters/ssao.hpp>

//---------------------------------------------//

#include <model_loaders/aaether_loader.hpp>
#include <converter/assimp_converter.hpp>

//---------------------------------------------//

#include <entity_info/transform_info.hpp>
#include <components/general_entity_info_component.hpp>
#include <components/model_component.hpp>

//---------------------------------------------//

#include <ui/ui_util.hpp>
#include <controller/controls_source.hpp>
#include <ui/ui_manager.hpp>
#include <camera_implementation/camera.hpp>
#include <controls.hpp>

//---------------------------------------------//

#include <entity/entity.hpp>
#include <entity/ui/ui_transform_tab.hpp>
#include <entity/ui/scene_outliner.hpp>

//---------------------------------------------//

#include <entity_instance/entity_instance.hpp>

//---------------------------------------------//

#include <settings/scene_info.hpp>
#include <resource_loader.hpp>
#include <technique.hpp>

//---------------------------------------------//

#include <data_manager.hpp>

//---------------------------------------------//

#include <ui_implementation/filter_root.hpp>
#include <ui_implementation/lighting_root.hpp>
#include <ui_implementation/settings_root.hpp>
#include <ui_implementation/project_root.hpp>
#include <ui_implementation/view_root.hpp>
#include <ui_implementation/top_root.hpp>
#include <ui_implementation/ui_root.hpp>

//---------------------------------------------//

#include <sky_implementation/sky_render.hpp>
#include <sky_implementation/sky_wrapper.hpp>

//---------------------------------------------//

#include <entity/palette/entity_palette.hpp>
#include <entity/entity_manager.hpp>

//---------------------------------------------//

#include <terrain_implementation/terrain_wrapper.hpp>

//---------------------------------------------//

#include <mesh_implementation/mesh_drawer.hpp>
#include <mesh_implementation/mesh_wrapper.hpp>

//---------------------------------------------//

#include <pipeline.hpp>
#include <application.hpp>

//---------------------------------------------//