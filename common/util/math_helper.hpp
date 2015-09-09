#ifndef MATH_HELPER
#define MATH_HELPER




#include <stdafx.h>





#define LERP(a,b,c)  (((b) - (a)) * (c) + (a))
#define COUNT_OF(x) ((sizeof(x) / sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))





/**


Some useful math functions for matrix transformations


*/
namespace Math
{





/**
Basic rectangle class
*/
class Rectangle
{


public:



    glm::vec2 point;
    GLfloat width, height;


};





/**
Basic circle class
*/
class Circle
{




public:



    glm::vec2 point;
    GLfloat radius;




};





/**
Checks if sphere intersects with frustum
*/
GLuint SphereInFrustum(Frustum *frustum, glm::vec3 pos, GLfloat radius);



/**
Returns translation matrix from 't_vec'
*/
glm::mat4 Translation(glm::vec3 t_vec);
/**
Returns translation matrix from 3D vector(x,y,z)
*/
inline glm::mat4 Translation(GLfloat x, GLfloat y, GLfloat z)
{
    return Translation(glm::vec3(x, y, z));
}


/**
Returns scale matrix from 't_vec'
*/
glm::mat4 Scale(glm::vec3 t_vec);
/**
Returns scale matrix from 3D vector(x,y,z)
*/
inline glm::mat4 Scale(GLfloat x, GLfloat y, GLfloat z)
{
    return Scale(glm::vec3(x, y, z));
}
/**
Returns scale matrix from 3D vector(v,v,v)
*/
inline glm::mat4 Scale(GLfloat v)
{
    return Scale(v, v, v);
}


/**
Returns rotation matrix from euler angles x,y,z
*/
inline glm::mat4 Rotate(GLfloat x, GLfloat y, GLfloat z)
{
    return glm::mat4_cast(glm::fquat(glm::vec3(x, y, z)));
}
/**
Returns rotation matrix from euler angles v.x,v.y,v.z
*/
inline glm::mat4 Rotate(glm::vec3 v)
{
    return Rotate(v.x, v.y, v.z);
}



/**
Print matrix to console
*/
void print_matrix(glm::mat4 m);
/**
Print vec3 to console
*/
void print_vec3(glm::vec3 v);
/**
Print ivec2 to console
*/
void print_ivec2(glm::ivec2 v);




/**
Returns a random float number within the boundaries
*/
inline GLfloat randomf(GLfloat LO, GLfloat HI)
{
    return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
}


/**
Gets 3d vector from string
*/
glm::vec3 GetVecFromString(std::string str);
/**
Gets string from 3d vector
*/
std::string GetStringFromVec(glm::vec3 v);



/**
Bias matrix for shadow calculations
*/
inline glm::mat4 GetBiasMatrix()
{
    return glm::mat4(
               0.5, 0.0, 0.0, 0.0,
               0.0, 0.5, 0.0, 0.0,
               0.0, 0.0, 0.5, 0.0,
               0.5, 0.5, 0.5, 1.0
           );

}


}




#endif
