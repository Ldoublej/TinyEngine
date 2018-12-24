//
// Created by ldoublej on 18-12-19.
//

#ifndef SIMPLE_OGL_CAMERA_H

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
namespace scene
{
    class Camera
    {
    private:
        glm::vec3 _world;
        glm::vec3 _target;
        glm::vec3 _up;

        float _pitch = 0.0;
        float _yaw = -90.0f;
        float _roll = 0.0;
    public:
        Camera():_world(glm::vec3(0.0)),_target(glm::vec3(0.0,0.0,-1.0)),_up(glm::vec3(0.0,1.0,0.0)){}
        Camera(const  glm::vec3 & world,const glm::vec3 & target ,const glm::vec3 & up = glm::vec3(0.0,1.0,0.0));
        Camera(float pitch,float yaw,float roll);

        void SetWorld(const glm::vec3 & world);
        glm::vec3 GetWorld() const;

        void SetTarget(const glm::vec3 & target);
        glm::vec3 GetTarget()const;

        void SetUp(const glm::vec3 & up);
        glm::vec3 GetUp() const;

        void SetPitch(float p);
        float GetPitch() const;

        void SetYaw(float y);
        float GetYaw() const;

        void SetRoll(float r);
        float GetRoll() const;



        glm::mat4 GetViewMatrix();
        glm::mat4 GetViewMatrixWithoutLocation();
        void UpdateVector();
    };
}
#define SIMPLE_OGL_CAMERA_H

#endif //SIMPLE_OGL_CAMERA_H
