#include <stdafx.h>





void View::Create3rd(GLfloat FoV, GLfloat ratio, GLfloat z_near, GLfloat z_far, GLfloat distance, glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{

    ProjectionMatrix = glm::perspective(FoV, ratio, z_near, z_far);
    ViewMatrix = glm::lookAt(position-direction*distance, position, up);


}



void View::Create3rd(ViewInfo*info)
{

    this->Create3rd(info->getFoV(),
                    info->getRatio(),
                    info->getNear(),
                    info->getRenderDistance(),
                    info->getDistance(),
                    info->getCameraPos(),
                    info->getDirection(),
                    info->getUpVec()
                   );


}

void View::Create1st(GLfloat FoV, GLfloat ratio, GLfloat z_near, GLfloat z_far, glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{


    ProjectionMatrix = glm::perspective(FoV, ratio, z_near, z_far);
    ViewMatrix = glm::lookAt(position, position + direction, up);


}


void View::Create1st(ViewInfo * info)
{


    this->Create1st(info->getFoV(),
                    info->getRatio(),
                    info->getNear(),
                    info->getRenderDistance(),
                    info->getCameraPos(),
                    info->getDirection(),
                    info->getUpVec()
                   );


}


void ViewInfo::Init()
{


    /*EVEN MORE INFO*/

    this->FoV = 60.0;
    this->direction = glm::vec3(0, 0, 0);
    this->distance = 50.0f;
    this->render_distance = RENDER_DISTANCE;
    this->position = glm::vec3(200, 0, 200);

    /*END OF EVEN MORE INFO*/

}



void Plane::Normalize()

{


    GLfloat temp = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    normal /= temp;
    distance /= temp;

}



void Frustum::Create(glm::mat4 MVP)
{


    //LEFT


    planes[0].normal.x = MVP[0].w - MVP[0].x;
    planes[0].normal.y = MVP[1].w - MVP[1].x;
    planes[0].normal.z = MVP[2].w - MVP[2].x;
    planes[0].distance = MVP[3].w - MVP[3].x;

    planes[0].Normalize();


    //RIGHT

    planes[1].normal.x = MVP[0].w + MVP[0].x;
    planes[1].normal.y = MVP[1].w + MVP[1].x;
    planes[1].normal.z = MVP[2].w + MVP[2].x;
    planes[1].distance = MVP[3].w + MVP[3].x;



    planes[1].Normalize();


    //TOP


    planes[4].normal.x = MVP[0].w + MVP[0].y;
    planes[4].normal.y = MVP[1].w + MVP[1].y;
    planes[4].normal.z = MVP[2].w + MVP[2].y;
    planes[4].distance = MVP[3].w + MVP[3].y;



    planes[4].Normalize();



    //BOTTOM

    planes[5].normal.x = MVP[0].w - MVP[0].y;
    planes[5].normal.y = MVP[1].w - MVP[1].y;
    planes[5].normal.z = MVP[2].w - MVP[2].y;
    planes[5].distance = MVP[3].w - MVP[3].y;


    planes[5].Normalize();


    //FAR

    planes[2].normal.x = MVP[0].w - MVP[0].z;
    planes[2].normal.y = MVP[1].w - MVP[1].z;
    planes[2].normal.z = MVP[2].w - MVP[2].z;
    planes[2].distance = MVP[3].w - MVP[3].z;



    planes[2].Normalize();


    //NEAR


    planes[3].normal.x = MVP[0].w + MVP[0].z;
    planes[3].normal.y = MVP[1].w + MVP[1].z;
    planes[3].normal.z = MVP[2].w + MVP[2].z;
    planes[3].distance = MVP[3].w + MVP[3].z;



    planes[3].Normalize();




}






