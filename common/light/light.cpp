#include <stdafx.h>




void Light::InitDirectionalLight()
{

    this->shader->AddVariable("InternalDirectionalLight.Base.color");
    this->shader->AddVariable("InternalDirectionalLight.Base.ambient_intensity");
    this->shader->AddVariable("InternalDirectionalLight.direction");
    this->shader->AddVariable("InternalDirectionalLight.Base.diffuse_intensity");

}




void Light::InitPointLights()
{



    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        char name[128];
        sprintf(name, "InternalPointLights[%d].Base.color", i);
        this->shader->AddVariable(name);
        sprintf(name, "InternalPointLights[%d].Base.ambient_intensity", i);
        this->shader->AddVariable(name);
        sprintf(name, "InternalPointLights[%d].Base.diffuse_intensity", i);
        this->shader->AddVariable(name);
        sprintf(name, "InternalPointLights[%d].position", i);
        this->shader->AddVariable(name);
        sprintf(name, "InternalPointLights[%d].Atten.Constant", i);
        this->shader->AddVariable(name);
        sprintf(name, "InternalPointLights[%d].Atten.Linear", i);
        this->shader->AddVariable(name);
        sprintf(name, "InternalPointLights[%d].Atten.Exp", i);
        this->shader->AddVariable(name);


    }



}




void Light::InitSpotLights()
{

    for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
    {
        char name[128];
        sprintf(name, "InternalSpotLights[%d].Base_point_light.Base.color", i);
        this->shader->AddVariable(name);
        sprintf(name, "InternalSpotLights[%d].Base_point_light.Base.ambient_intensity", i);
        this->shader->AddVariable(name);
        sprintf(name, "InternalSpotLights[%d].Base_point_light.Base.diffuse_intensity", i);
        this->shader->AddVariable(name);
        sprintf(name, "InternalSpotLights[%d].Base_point_light.position", i);
        this->shader->AddVariable(name);
        sprintf(name, "InternalSpotLights[%d].Base_point_light.Atten.Constant", i);
        this->shader->AddVariable(name);
        sprintf(name, "InternalSpotLights[%d].Base_point_light.Atten.Linear", i);
        this->shader->AddVariable(name);
        sprintf(name, "InternalSpotLights[%d].Base_point_light.Atten.Exp", i);
        this->shader->AddVariable(name);
        sprintf(name, "InternalSpotLights[%d].direction", i);
        this->shader->AddVariable(name);
        sprintf(name, "InternalSpotLights[%d].Cutoff", i);
        this->shader->AddVariable(name);


    }




}



void Light::InitFog()
{


    this->shader->AddVariable("fog.color");
    this->shader->AddVariable("fog.density");



}



void Light::Init(Shader * shader)
{

    this->shader = shader;

    this->InitDirectionalLight();
    this->InitPointLights();
    this->InitSpotLights();
    this->InitFog();


}



void Light::Clean()
{




}



Light::Light(Shader * shader)
{


    Init(shader);


}



void Light::SetDirectionalLight(glm::vec3 color, glm::vec3 direction, float a_intensity, float d_intensity)
{


    this->shader->Set("InternalDirectionalLight.Base.color", color);
    this->shader->Set("InternalDirectionalLight.Base.ambient_intensity", a_intensity);
    this->shader->Set("InternalDirectionalLight.direction", direction);
    this->shader->Set("InternalDirectionalLight.Base.diffuse_intensity", d_intensity);



}

void Light::SetPointLights(int Index,glm::vec3 color,glm::vec3 position,float a_intensity,float d_intensity,float constant,float linear,float exp)
{

    char name[128];
    sprintf(name, "InternalPointLights[%d].Base.color", Index);
    this->shader->Set(name, color);
    sprintf(name, "InternalPointLights[%d].Base.ambient_intensity", Index);
    this->shader->Set(name, a_intensity);
    sprintf(name, "InternalPointLights[%d].Base.diffuse_intensity", Index);
    this->shader->Set(name, d_intensity);
    sprintf(name, "InternalPointLights[%d].position", Index);
    this->shader->Set(name, position);
    sprintf(name, "InternalPointLights[%d].Atten.Constant", Index);
    this->shader->Set(name, constant);
    sprintf(name, "InternalPointLights[%d].Atten.Linear", Index);
    this->shader->Set(name, linear);
    sprintf(name, "InternalPointLights[%d].Atten.Exp", Index);
    this->shader->Set(name, exp);




}


void Light::SetSpotLights(int Index, glm::vec3 color, glm::vec3 position, float a_intensity, float d_intensity, float constant, float linear, float exp, glm::vec3 direction, float Cutoff)
{


    char name[128];
    sprintf(name, "InternalSpotLights[%d].Base_point_light.Base.color", Index);
    this->shader->Set(name, color);
    sprintf(name, "InternalSpotLights[%d].Base_point_light.Base.ambient_intensity", Index);
    this->shader->Set(name, a_intensity);
    sprintf(name, "InternalSpotLights[%d].Base_point_light.Base.diffuse_intensity", Index);
    this->shader->Set(name, d_intensity);
    sprintf(name, "InternalSpotLights[%d].Base_point_light.position", Index);
    this->shader->Set(name, position);
    sprintf(name, "InternalSpotLights[%d].Base_point_light.Atten.Constant", Index);
    this->shader->Set(name, constant);
    sprintf(name, "InternalSpotLights[%d].Base_point_light.Atten.Linear", Index);
    this->shader->Set(name, linear);
    sprintf(name, "InternalSpotLights[%d].Base_point_light.Atten.Exp", Index);
    this->shader->Set(name, exp);
    sprintf(name, "InternalSpotLights[%d].direction", Index);
    this->shader->Set(name, direction);
    sprintf(name, "InternalSpotLights[%d].Cutoff", Index);
    this->shader->Set(name, Cutoff);


}




void Light::SetFog(glm::vec3 color, GLfloat density)
{


    this->shader->Set("fog.color", color);
    this->shader->Set("fog.density", density);


}

