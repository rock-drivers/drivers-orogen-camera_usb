/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"

using namespace orogen_camera_usb;

Task::Task(std::string const& name)
    : TaskBase(name), mCamInfo(NULL)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
{
}

Task::~Task()
{
}

void Task::configureCamera() {
    using namespace camera;

    cam_interface = (camera::CamInterface*)new camera::CamUsb(_camera_device.value());
    std::vector<camera::CamInfo> cam_infos;
    try {
        if(cam_interface->listCameras(cam_infos) > 0) {
            if(cam_interface->open(cam_infos[0])) {
                mCamInfo = (camera::CamInfo*)cam_interface->getCameraInfo();
            } else {
                RTT::log(RTT::Error) << "Could not open camera " << RTT::endlog();
            }
        } else {
            RTT::log(RTT::Error) << "No camera-configuration available. " << RTT::endlog();
        }
    } catch (std::runtime_error& e) {
        RTT::log(RTT::Error) << "Faild to configure camera: " << e.what() << RTT::endlog();
    }

    // Set properties if attributes/controls are available.
    // INTs
    // Set brightness.
    if(cam_interface->isAttribAvail(int_attrib::BrightnessValue))
        cam_interface->setAttrib(camera::int_attrib::BrightnessValue,_brightness);
    else
        RTT::log(RTT::Info) << "BrightnessValue is not supported by the camera" << RTT::endlog();

    // Set contrast.
    if(cam_interface->isAttribAvail(int_attrib::ContrastValue))
        cam_interface->setAttrib(camera::int_attrib::ContrastValue,_contrast);
    else
        RTT::log(RTT::Info) << "BrightnessValue is not supported by the camera" << RTT::endlog();

    // Set saturation.
    if(cam_interface->isAttribAvail(int_attrib::SaturationValue))
        cam_interface->setAttrib(camera::int_attrib::SaturationValue,_saturation);
    else
        RTT::log(RTT::Info) << "BrightnessValue is not supported by the camera" << RTT::endlog();

    // Set sharpness.
    if(cam_interface->isAttribAvail(int_attrib::SharpnessValue))
        cam_interface->setAttrib(camera::int_attrib::SharpnessValue,_sharpness);
    else
        RTT::log(RTT::Info) << "BrightnessValue is not supported by the camera" << RTT::endlog();

    // Set backlight compensation.
    if(cam_interface->isAttribAvail(int_attrib::BacklightCompensation))
        cam_interface->setAttrib(camera::int_attrib::BacklightCompensation,_backlight_compensation);
    else
        RTT::log(RTT::Info) << "BrightnessValue is not supported by the camera" << RTT::endlog();

    // ENUMs
    //setting _power_line_frequency
    if(_power_line_frequency.value() == "disabled")
    {
        if(cam_interface->isAttribAvail(camera::enum_attrib::PowerLineFrequencyDisabled))
            cam_interface->setAttrib(camera::enum_attrib::PowerLineFrequencyDisabled);
        else
            RTT::log(RTT::Info) << "PowerLineFrequencyDisabled is not supported by the camera" << RTT::endlog();
    }
    else if (_power_line_frequency.value() == "50Hz")
    {
        if(cam_interface->isAttribAvail(camera::enum_attrib::PowerLineFrequencyTo50))
            cam_interface->setAttrib(camera::enum_attrib::PowerLineFrequencyTo50);
        else
            RTT::log(RTT::Info) << "PowerLineFrequencyTo50 is not supported by the camera" << RTT::endlog();
    }
    else if (_power_line_frequency.value() == "60Hz")
    {
        if(cam_interface->isAttribAvail(camera::enum_attrib::PowerLineFrequencyTo60))
            cam_interface->setAttrib(camera::enum_attrib::PowerLineFrequencyTo60);
        else
            RTT::log(RTT::Info) << "PowerLineFrequencyTo60 is not supported by the camera" << RTT::endlog();
    }
    else if(_power_line_frequency.value() == "none")
    {
        //do nothing
    }
    else
    {
        RTT::log(RTT::Error) << "Power Line Frequency "+ _power_line_frequency.value() + " is not supported!" << RTT::endlog();
        error(UNKOWN_PARAMETER);
        return;
    }

    camera_base::Task::configureCamera();
}

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

// bool Task::configureHook()
// {
//     if (! TaskBase::configureHook())
//         return false;
//     return true;
// }
// bool Task::startHook()
// {
//     if (! TaskBase::startHook())
//         return false;
//     return true;
// }
// void Task::updateHook()
// {
//     TaskBase::updateHook();
// }
// void Task::errorHook()
// {
//     TaskBase::errorHook();
// }
// void Task::stopHook()
// {
//     TaskBase::stopHook();
// }
// void Task::cleanupHook()
// {
//     TaskBase::cleanupHook();
// }

