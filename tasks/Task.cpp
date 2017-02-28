/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"

#include "camera_base/TaskBase.hpp"
#include "frame_helper/FrameHelper.h"
#include "camera_interface/CamInterface.h"

#include "camera_usb/cam_usb.h" // Driver

using namespace camera_usb;

Task::Task(std::string const& name)
    : TaskBase(name)
{
    RTT::log(RTT::Debug) << "Task: condtructor 1" << RTT::endlog();
    _camera_format.set(base::samples::frame::MODE_JPEG);
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
{
    RTT::log(RTT::Debug) << "Task: constructor 2" << RTT::endlog();
    _camera_format.set(base::samples::frame::MODE_JPEG);
}

Task::~Task()
{
    RTT::log(RTT::Debug) << "Task: destructor" << RTT::endlog();
    if(cam_interface != NULL) {
        delete cam_interface;
        cam_interface = NULL;
    }
}

bool Task::configureCamera() 
{
    RTT::log(RTT::Debug) << "Task: configureCamera" << RTT::endlog();
    using namespace camera;  
    
    CamUsb* cam_usb = new CamUsb(_camera_device);
    cam_interface = (CamInterface*)cam_usb;

    // Open camera.
    std::vector<CamInfo> cam_infos;
    try {
        if(cam_interface->listCameras(cam_infos) > 0) 
        {
            // open() activates the V4L2 configuration mode.
            // In this mode all camera infos are requested and write operations
            // are performed to detect non-writeable controls.
            if(cam_interface->open(cam_infos[0])) 
            {
                mCamInfo = (camera::CamInfo*)cam_interface->getCameraInfo();
            } else {
                RTT::log(RTT::Error) << "Could not open camera " << RTT::endlog();
                return false;
            }
        } else {
            RTT::log(RTT::Error) << "No camera-configuration available. " << RTT::endlog();
            return false;
        }
    } catch (std::runtime_error& e) {
        RTT::log(RTT::Error) << "Failed to open camera for configuration: " << e.what() << RTT::endlog();
        return false;
    }
    if (!camera_base::Task::configureCamera()) { // calls cam_interface->setFrameSettings(*camera_frame); as well.
        return false;
    }

    // FPS is already set.

    // Set properties if attributes/controls are available.
    // INTs
    // Set brightness.
    if(_brightness.get() <= 0) {
        RTT::log(RTT::Info) << "Property brightness not set, using the default value of the camera." << RTT::endlog();
    } else {
        if(cam_interface->isAttribAvail(int_attrib::BrightnessValue))
            cam_interface->setAttrib(camera::int_attrib::BrightnessValue,_brightness);
        else
            RTT::log(RTT::Info) << "BrightnessValue is not supported by the camera" << RTT::endlog();
    }

    // Set contrast.
    if(_contrast.get() <= 0) {
        RTT::log(RTT::Info) << "Property contrast not set, using the default value of the camera." << RTT::endlog();
    } else {
        if(cam_interface->isAttribAvail(int_attrib::ContrastValue))
            cam_interface->setAttrib(camera::int_attrib::ContrastValue,_contrast);
        else
            RTT::log(RTT::Info) << "ContrastValue is not supported by the camera" << RTT::endlog();
    }

    // Set saturation.
    if(_saturation.get() <= 0) {
        RTT::log(RTT::Info) << "Property saturation not set, using the default value of the camera." << RTT::endlog();
    } else {     
        if(cam_interface->isAttribAvail(int_attrib::SaturationValue))
            cam_interface->setAttrib(camera::int_attrib::SaturationValue,_saturation);
        else
            RTT::log(RTT::Info) << "SaturationValue is not supported by the camera" << RTT::endlog();
    }

    // Set sharpness.
    if(_sharpness.get() <= 0) {
        RTT::log(RTT::Info) << "Property sharpness not set, using the default value of the camera." << RTT::endlog();
    } else { 
        if(cam_interface->isAttribAvail(int_attrib::SharpnessValue))
            cam_interface->setAttrib(camera::int_attrib::SharpnessValue,_sharpness);
        else
            RTT::log(RTT::Info) << "SharpnessValue is not supported by the camera" << RTT::endlog();
    }

    // Set backlight compensation.
    if(_backlight_compensation.get() <= 0) {
        RTT::log(RTT::Info) << "Property backlight_compensation not set, using the default value of the camera." << RTT::endlog();
    } else { 
        if(cam_interface->isAttribAvail(int_attrib::BacklightCompensation) && _backlight_compensation.get() >= 0)
            cam_interface->setAttrib(camera::int_attrib::BacklightCompensation,_backlight_compensation);
        else
            RTT::log(RTT::Info) << "BacklightCompensation is not supported by the camera" << RTT::endlog();
    }

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
    else if(_power_line_frequency.value() == "none" || _power_line_frequency.value().empty())
    {
        //do nothing
    }
    else
    {
        RTT::log(RTT::Error) << "Power Line Frequency "+ _power_line_frequency.value() + " is not supported!" << RTT::endlog();
        report(UNKOWN_PARAMETER);
        return false;
    }

    // V4L2s (not part of the camera interface yet)

    // FOCUS
    // Set focus to 'auto', otherwise to 'manual' and to the defined value (if 
    // both control IDs are available).
    if(cam_usb->isV4L2AttribAvail(V4L2_CID_FOCUS_AUTO) && !_focus_mode.value().empty()) {
        if(_focus_mode.value() == "auto") 
        {
            cam_usb->setV4L2Attrib(V4L2_CID_FOCUS_AUTO, 1);
        }
        else if(_focus_mode.value() == "manual") 
        {
            if(cam_usb->isV4L2AttribAvail(V4L2_CID_FOCUS_ABSOLUTE) &&
                    cam_usb->setV4L2Attrib(V4L2_CID_FOCUS_AUTO, 0) &&
                    _focus.value() >= 0) {
                cam_usb->setV4L2Attrib(V4L2_CID_FOCUS_ABSOLUTE, _focus.value());
            }
        }
    }
    
    // WHITE BALANCE
    if(_whitebalance_mode.value() == "manual") {
        if(cam_usb->isV4L2AttribAvail(V4L2_CID_WHITE_BALANCE_TEMPERATURE) &&
                _white_balance_temperature.value() >= 0) {
            cam_usb->setV4L2Attrib(V4L2_CID_WHITE_BALANCE_TEMPERATURE, _white_balance_temperature.value());
        }
    }
    
    // GAIN
    if(cam_usb->isV4L2AttribAvail(V4L2_CID_AUTOGAIN)) {
        if(_gain_mode_auto.value()) 
            cam_usb->setV4L2Attrib(V4L2_CID_AUTOGAIN, 1); // auto
        else
            cam_usb->setV4L2Attrib(V4L2_CID_AUTOGAIN, 0);
    }
    
    if(cam_usb->isV4L2AttribAvail(V4L2_CID_GAIN) && !_gain_mode_auto.value()) {
        cam_usb->setV4L2Attrib(V4L2_CID_GAIN, _gain.value());
    }
    
    // FLIP
    if(cam_usb->isV4L2AttribAvail(V4L2_CID_HFLIP) && _horizontal_flip.value() >= 0)
        cam_usb->setV4L2Attrib(V4L2_CID_HFLIP, _horizontal_flip.value());
    if(cam_usb->isV4L2AttribAvail(V4L2_CID_VFLIP) && _vertical_flip.value() >= 0)
        cam_usb->setV4L2Attrib(V4L2_CID_VFLIP, _vertical_flip.value());

    // ZOOM
    if(cam_usb->isV4L2AttribAvail(V4L2_CID_ZOOM_ABSOLUTE) && _zoom.value() >= 0)
        cam_usb->setV4L2Attrib(V4L2_CID_ZOOM_ABSOLUTE, _zoom.value());

    // SPECIAL E-CAM32 CONTROLS
    if(cam_usb->isV4L2AttribAvail(V4L2_SENS_TRIG_FOCUS, "Single Auto focus") && _single_auto_focus.value() >= 0)
        cam_usb->setV4L2Attrib(V4L2_SENS_TRIG_FOCUS, _single_auto_focus.value());
    if(cam_usb->isV4L2AttribAvail(V4L2_SENS_FCS_OLAY, "Focus Overlay") && _focus_overlay.value() >= 0)
        cam_usb->setV4L2Attrib(V4L2_SENS_FCS_OLAY, _focus_overlay.value());
    if(cam_usb->isV4L2AttribAvail(V4L2_SENS_EFFECTS, "effects") && _effects.value() >= 0)
        cam_usb->setV4L2Attrib(V4L2_SENS_EFFECTS, _effects.value());
    if(cam_usb->isV4L2AttribAvail(V4L2_SENS_FOCUS_DISABLE, "Focus complete") && _focus_complete.value() >= 0)
        cam_usb->setV4L2Attrib(V4L2_SENS_FOCUS_DISABLE, _focus_complete.value());
    if(cam_usb->isV4L2AttribAvail(V4L2_SENS_TEST_PATTERN, "Test pattern") && _test_pattern.value() >= 0)
        cam_usb->setV4L2Attrib(V4L2_SENS_TEST_PATTERN, _test_pattern.value());
    
    // It is possible that we receive another image format than requested (e.g. 1280x720 instead of 1280x768).
    // In this case camera_frame and output_frame size would differ which would
    // require a continuous rescaling. To avoid this we adapt the size of the frames here.
    base::samples::frame::frame_size_t size;
    base::samples::frame::frame_mode_t mode;
    uint8_t color_depth;
    cam_usb->getFrameSettings(size, mode, color_depth);    
    
    using namespace base::samples::frame;
    frame_mode_t output_frame_mode = _output_format.value();
    if(output_frame_mode == MODE_UNDEFINED) {
        output_frame_mode = _camera_format.value();
    }
    
    Frame* frame = new Frame(size.width, size.height, _channel_data_depth, _camera_format.value()); 
    camera_frame.reset(frame);

    frame = new Frame(size.width * _scale_x, size.height * _scale_y, _channel_data_depth, output_frame_mode); 
    output_frame.reset(frame);	
    frame = NULL;
    
    cam_usb->printCameraInformations();
    
    return true;
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

void Task::cleanupHook() 
{
    RTT::log(RTT::Debug) << "Task: cleanupHook" << RTT::endlog();
    TaskBase::cleanupHook();
    if(cam_interface != NULL) 
    {
        delete cam_interface;
        cam_interface = NULL;
    }
}
