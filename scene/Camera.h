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
        Camera():_world(glm::vec3(0.0)),_target(glm::vec3(0.0,0.0,-1.0)),_up(glm::vec3(0.0,1.0,0.0))
        {

        };
        Camera(const  glm::vec3 & world,const glm::vec3 & target ,const glm::vec3 & up = glm::vec3(0.0,1.0,0.0)):
        _world(world),_target(target),_up(up)
        {
            _target = glm::normalize(_target);
            _up = glm::normalize(_up);
        }
        Camera(float pitch,float yaw,float roll):_pitch(pitch),_yaw(yaw),_roll(roll),
        _world(glm::vec3(0.0)),_target(glm::vec3(0.0,0.0,-1.0)),_up(glm::vec3(0.0,1.0,0.0))
        {
            UpdateVector();
        }

        void SetWorld(const glm::vec3 & world){_world = world;}
        glm::vec3 GetWorld(){return _world;}

        void SetTarget(const glm::vec3 & target){_target = glm::normalize(target);}
        glm::vec3 GetTarget(){return _target;}

        void SetUp(const glm::vec3 & up){_up = glm::normalize(up);}
        glm::vec3 GetUp(){return _up;}

        void SetPitch(float p){_pitch = p;}
        float GetPitch(){return _pitch;}

        void SetYaw(float y){_yaw = y;}
        float GetYaw(){return _yaw;}

        void SetRoll(float r){_roll = r;}
        float GetRoll(){return _roll;}



        glm::mat4 GetViewMatrix();
        void UpdateVector();
    };
}
#define SIMPLE_OGL_CAMERA_H

#endif //SIMPLE_OGL_CAMERA_H
