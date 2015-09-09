#ifndef RESOURCE_LOADER_HPP
#define RESOURCE_LOADER_HPP






#include <stdafx.h>




class ResourceLoader : public BaseResourceLoader
{



    std::string terrain_file;
    std::string color_file;
    std::string t_file;
    std::string n_file;
    std::string a_file;


    std::string env_file;
    std::string fsettings_file;
    std::string scene_file;



public:




    /**
    Initialize state savers and resource paths
    */
    void Init();



    /**
    Cleans scene data
    */
    void Clean();



    inline char* GetTerrainFile()
    {
        return AString::char_to_str(terrain_file);
    }
    inline char* GetColorFile()
    {
        return AString::char_to_str(color_file);
    }
    inline char* GetEnvFile()
    {
        return AString::char_to_str(env_file);
    }
    inline char* GetFSettingsFile()
    {
        return AString::char_to_str(fsettings_file);
    }
    inline char* GetSceneFile()
    {
        return AString::char_to_str(scene_file);
    }
    inline char* GetTFile()
    {
        return AString::char_to_str(t_file);
    }
    inline char* GetNFile()
    {
        return AString::char_to_str(n_file);
    }
    inline char* GetAFile()
    {
        return AString::char_to_str(a_file);
    }


    /**
    Loads all resrouce paths
    */
    void LoadResourcePaths(char *path);


};





#endif
