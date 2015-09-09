#ifndef SCENE_INFO_HPP
#define SCENE_INFO_HPP





#include <stdafx.h>




#define OBJECT_FOLDER "data\\objects\\"





/**



Entity data is stored here



*/
class SceneInfo : public AStateSaver
{


private:




    std::map<std::string, boost::shared_ptr<EntityInstance> > instance_map;
    std::map<std::string, boost::shared_ptr<Entity> > entity_map;





    /**
    Function for adding components to entity
    */
    void CreateComponentInstance(boost::filesystem::directory_iterator iterator, AComponent * new_component, Entity * new_entity);
    /**
    Based on the files in path you provide ScenInfo adds specific components to the given entity
    */
    void AddComponentsToEntity(char * path, Entity * new_entity);
    /**
    Adds entity to the entity map
    */
    void AddEntity(Entity* new_entity);



public:


    /**
    Sets path of the file the class will affect
    */
    inline SceneInfo(char * path)
    {
        SetPath(path);
    }




    /**
    Load data from file
    */
    void Load();
    /**
    Save data to file
    */
    void Save();
    /**
    Reset data
    */
    void Reset();








    /**
    Get how many instances are in scene
    */
    inline GLuint GetNumberOfInstances()
    {
        return instance_map.size();
    }
    /**
    Get instance at position 'index'
    */
    inline EntityInstance * GetInstance(std::string name)
    {
        return instance_map[name].get();
    }
    /**
    Add instance to scene
    */
    inline void AddInstance(std::string name, EntityInstance * new_instance)
    {
        instance_map.insert(std::pair<std::string, boost::shared_ptr<EntityInstance> >(name, boost::shared_ptr<EntityInstance>(new_instance)));
    }
    /**
    Clear instances
    */
    inline void ClearInstances()
    {
        instance_map.clear();
    }
    /**
    Get first adress of map
    */
    inline std::map<std::string, boost::shared_ptr<EntityInstance> >::iterator GetFirstInstance()
    {
        return instance_map.begin();
    }
    /**
    Get last adress of map
    */
    inline std::map<std::string, boost::shared_ptr<EntityInstance> >::iterator GetLastInstance()
    {
        return instance_map.end();
    }
    /**
    See if instance with 'name' exists
    */
    inline GLboolean InstanceExists(std::string name)
    {
        return instance_map.count(name);
    }







    /**
    Get entity with provided key
    */
    inline Entity* GetEntity(std::string name)
    {
        return entity_map[name].get();
    }
    /**
    Get entity with provided index
    */
    inline Entity* GetEntity(GLuint counter)
    {
        std::map<std::string, boost::shared_ptr<Entity> >::iterator it(entity_map.begin());
        std::advance(it, counter);
        return it->second.get();
    }
    /**
    Get number of entities in map
    */
    inline GLuint GetNumberOfEntities()
    {
        return entity_map.size();
    }

    /**
    Insert new entity from given folder
    */
    void InsertNewEntity(std::string path);
    /**
    Clear entity map
    */
    inline void ClearEntities()
    {
        entity_map.clear();
    }


};




#endif
