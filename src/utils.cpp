#include "utils.h"

using namespace std;

// ---------------------
//  3d Math
// \/-------------------

float* rotate_3d_x(vec3 p, float angle){
    mat3 mat = {
     {1,0          ,0           }
    ,{0,cosf(angle),-sinf(angle)}
    ,{0,sinf(angle), cosf(angle)}
    };
    float* rp = new vec3;
    glm_mat3_mulv(mat,p,rp);
    return rp;
}

float* rotate_3d_y(vec3 p, float angle){
    mat3 mat = {
     {cosf(angle) ,0,sinf(angle)}
    ,{0           ,1,0}
    ,{-sinf(angle),0,cosf(angle)}
    };
    float* rp = new vec3;
    glm_mat3_mulv(mat,p,rp);
    return rp;
}

float* rotate_3d_z(vec3 p, float angle){
    mat3 mat = {
     {cosf(angle),-sinf(angle),0}
    ,{sinf(angle),cosf(angle) ,0}
    ,{0          ,0           ,1}
    };
    float* rp = new vec3;
    glm_mat3_mulv(mat,p,rp);
    return rp;
}

// ---------------------
//  Logging
// \/-------------------

void error(string msg){
    cout << "ERROR: " << msg << endl;
    exit(1);
}

void warning(string msg){
    cout << "WARNING: " << msg << endl;
}

void todo(string msg){
    cout << "TODO: " << msg << endl;
    exit(1);
}