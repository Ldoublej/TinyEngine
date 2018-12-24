//
// Created by ldoublej on 18-12-19.
//

#include "Camera.h"


namespace scene
{
    Camera::Camera(const glm::vec3 &world, const glm::vec3 &target, const glm::vec3 &up):
            _world(world),_target(target),_up(up)
    {
        _target = glm::normalize(_target);
        _up = glm::normalize(_up);
    }

    Camera::Camera(float pitch, float yaw, float roll):_pitch(pitch),_yaw(yaw),_roll(roll),
                                                       _world(glm::vec3(0.0)),_target(glm::vec3(0.0,0.0,-1.0)),_up(glm::vec3(0.0,1.0,0.0))
    {
        UpdateVector();
    }
    glm::mat4 Camera::GetViewMatrix()
    {
        glm::mat4 view;
        view = glm::lookAt(_world,_world + _target,_up);
        return view;
    }
    glm::mat4 Camera::GetViewMatrixWithoutLocation()
    {
        glm::mat4 view;
        view = glm::lookAt(glm::vec3(0.0), _target,_up);
        return view;
    }
    void Camera::UpdateVector()
    {
        _target.x = cosf(glm::radians(_pitch)) * cosf(glm::radians(_yaw));
        _target.y = sinf(glm::radians(_pitch));
        _target.z = cosf(glm::radians(_pitch)) * sinf(glm::radians(_yaw));

        _up.x = cosf(glm::radians(_pitch+90)) * cosf(glm::radians(_yaw));
        _up.y = sinf(glm::radians(_pitch+90));
        _up.z = cosf(glm::radians(_pitch+90)) * sinf(glm::radians(_yaw));

        _target = glm::normalize(_target);
        _up = glm::normalize(_up);
    }

    void Camera::SetWorld(const glm::vec3 &world)
    {
        _world = world;
    }

    glm::vec3 Camera::GetWorld() const
    {
        return _world;
    }

    void Camera::SetTarget(const glm::vec3 &target)
    {
        _target = glm::normalize(target);
    }

    glm::vec3 Camera::GetTarget() const
    {
        return _target;
    }

    void Camera::SetUp(const glm::vec3 &up)
    {
        _up = glm::normalize(up);
    }

    glm::vec3 Camera::GetUp() const
    {
        return _up;
    }

    void Camera::SetPitch(float p)
    {
        _pitch = p;
    }

    float Camera::GetPitch() const
    {
        return _pitch;
    }

    void Camera::SetYaw(float y)
    {
        _yaw = y;
    }

    float Camera::GetYaw() const
    {
        return _yaw;
    }

    void Camera::SetRoll(float r)
    {
        _roll = r;
    }

    float Camera::GetRoll() const
    {
        return _roll;
    }


}

