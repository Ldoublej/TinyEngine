//
// Created by ldoublej on 18-12-19.
//

#include "Camera.h"


namespace scene
{
    glm::mat4 Camera::GetViewMatrix()
    {
        glm::mat4 view;
        view = glm::lookAt(_world,_world + _target,_up);
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
}

