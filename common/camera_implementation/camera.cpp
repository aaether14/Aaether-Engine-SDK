#include <stdafx.h>




void Camera::Init()
{


    //Initialising


    verticalAngle = -M_PI / 24;
    horizontalAngle = 3.14f;
    base_speed = this->speed = 20.0f;
    mouse_speed = 0.0025f;
    rotation_speed = M_PI;



    view_3rd = new View();
    info = new ViewInfo();
    frustum = new Frustum();



}



void Camera::Clean()
{


    //Cleaning up...



    if (view_3rd)
        delete view_3rd;


    if (info)
        delete info;


    if (frustum)
        delete frustum;


}



void Camera::ProcessInput(ControllerSource * source)
{




    if (source->GetKey(GLFW_KEY_LEFT_SHIFT))
        speed = 3 * base_speed;
    else
        speed = base_speed;



    if (source->GetKey(GLFW_KEY_W))
        info->SetCameraPos(info->getCameraPos() +
                           glm::normalize(glm::vec3(info->getDirection().x, 0.0, info->getDirection().z))
                           * GLfloat(source->GetFpsPointer()->Delta()) * speed);



    if (source->GetKey(GLFW_KEY_S))
        info->SetCameraPos(info->getCameraPos() -
                           glm::normalize(glm::vec3(info->getDirection().x, 0.0, info->getDirection().z))
                           * GLfloat(source->GetFpsPointer()->Delta()) * speed);





    if (source->GetKey(GLFW_KEY_A))
        horizontalAngle += source->GetFpsPointer()->Delta()*rotation_speed;



    if (source->GetKey(GLFW_KEY_D))
        horizontalAngle -= source->GetFpsPointer()->Delta()*rotation_speed;




    info->SetDistance(std::max(info->getDistance() - source->GetWheelOffset(), 1.0));
    source->ResetWheelOffset();



}





void Camera::ComputeAngles(ControllerSource * source)
{



    //Preparing mouse input for world movement


    GLdouble delta_x, delta_y;



    if (glfwGetMouseButton(source->GetWindow(), GLFW_MOUSE_BUTTON_RIGHT))
    {


        glfwGetCursorPos(source->GetWindow(), &delta_x, &delta_y);
        glfwSetCursorPos(source->GetWindow(), last_x, last_y);



        delta_x = mouse_speed * GLdouble(last_x - delta_x);
        delta_y = mouse_speed * GLdouble(last_y - delta_y);


        horizontalAngle += delta_x;
        verticalAngle += delta_y;

        if (verticalAngle > -M_PI / 24)
            verticalAngle = -M_PI / 24;
        if (verticalAngle < -M_PI / 2)
            verticalAngle = -M_PI / 2;


    }
    else
    {
        glfwGetCursorPos(source->GetWindow(), &last_x, &last_y);
    }


    SetInfo(source);


    glfwSetInputMode(source->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);



}





void Camera::SetInfo(ControllerSource * source)
{


    //converting mouse movement to spherical coodrs to view direction


    info->setDirection(glm::vec3(
                           cos(verticalAngle) * sin(horizontalAngle),
                           sin(verticalAngle),
                           cos(verticalAngle) * cos(horizontalAngle)
                       ));

    glm::vec3 right = glm::vec3(
                          sin(horizontalAngle - 3.14f / 2.0f),
                          0,
                          cos(horizontalAngle - 3.14f / 2.0f)
                      );


    info->setUpVec(glm::cross(right, info->getDirection()));


    info->setRatio(GLfloat(source->GetWindowWidth()) / GLfloat(source->GetWindowHeight()));
    info->setNear(1.0f);


    glm::vec3 old = info->getCameraPos();
    info->SetCameraPos
    (
        old +
        2.0f*glm::normalize(glm::vec3(info->getDirection().x, 0, info->getDirection().z)
                            + glm::vec3(0, 1, 0)
                           ));



    //Computing the view state


    view_3rd->Create3rd(info);
    info->SetCameraPos(old);



}
