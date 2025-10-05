#include "utils.h"

// ---------------------
//  3d Math
// \/-------------------

float* rotate_3d_x(vec3 p, float angle){
    mat3 mat = {
     {1,0          ,0           }
    ,{0,cosf(angle),-sinf(angle)}
    ,{0,sinf(angle), cosf(angle)}
    };
    float* rp = malloc(sizeof(vec3));
    glm_mat3_mulv(mat,p,rp);
    return rp;
}

float* rotate_3d_y(vec3 p, float angle){
    mat3 mat = {
     {cosf(angle) ,0,sinf(angle)}
    ,{0           ,1,0}
    ,{-sinf(angle),0,cosf(angle)}
    };
    float* rp = malloc(sizeof(vec3));
    glm_mat3_mulv(mat,p,rp);
    return rp;
}

float* rotate_3d_z(vec3 p, float angle){
    mat3 mat = {
     {cosf(angle),-sinf(angle),0}
    ,{sinf(angle),cosf(angle) ,0}
    ,{0          ,0           ,1}
    };
    float* rp = malloc(sizeof(vec3));
    glm_mat3_mulv(mat,p,rp);
    return rp;
}

// ---------------------
//  Logging
// \/-------------------

void error(const char* msg){
    printf("ERROR: %s\n",msg);
    exit(1);
}

void warning(const char* msg){
    printf("WARNING: %s\n",msg);
}

void todo(const char* msg){
    printf("TODO: %s\n",msg);
    exit(1);
}