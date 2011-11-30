/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef CAMERA_USB_CAMERATASK_TASK_HPP
#define CAMERA_USB_CAMERATASK_TASK_HPP

#include "camera_usb/CameraTaskBase.hpp"

#include "camera_base/TaskBase.hpp"
#include "frame_helper/FrameHelper.h"
#include "camera_interface/CamInterface.h"

#include "camera_usb/cam_usb.h" // Driver

namespace camera_usb {
class CameraTask : public CameraTaskBase
{
friend class CameraTaskBase;
 protected:
    camera::CamInfo* mCamInfo;

 public:
    CameraTask(std::string const& name = "orogen_camera_usb::CameraTask");
    CameraTask(std::string const& name, RTT::ExecutionEngine* engine);

    ~CameraTask();

    void configureCamera();

    /** This hook is called by Orocos when the state machine transitions
     * from PreOperational to Stopped. If it returns false, then the
     * component will stay in PreOperational. Otherwise, it goes into
     * Stopped.
     *
     * It is meaningful only if the #needs_configuration has been specified
     * in the task context definition with (for example):
     *
     *   task_context "TaskName" do
     *     needs_configuration
     *     ...
     *   end
     */
    #if PRINT_DEBUG
    bool configureHook() {
        std::cout << "CameraTask: configureHook" << std::endl;
        camera_base::Task::configureHook();
    }
    #endif

    /** This hook is called by Orocos when the state machine transitions
     * from Stopped to Running. If it returns false, then the component will
     * stay in Stopped. Otherwise, it goes into Running and updateHook()
     * will be called.
     */
    #if PRINT_DEBUG
    bool startHook() {
        std::cout << "CameraTask: startHook" << std::endl;
        camera_base::Task::startHook();
    }
    #endif

    /** This hook is called by Orocos when the component is in the Running
     * state, at each activity step. Here, the activity gives the "ticks"
     * when the hook should be called.
     *
     * The error(), exception() and fatal() calls, when called in this hook,
     * allow to get into the associated RunTimeError, Exception and
     * FatalError states. 
     *
     * In the first case, updateHook() is still called, and recover() allows
     * you to go back into the Running state.  In the second case, the
     * errorHook() will be called instead of updateHook(). In Exception, the
     * component is stopped and recover() needs to be called before starting
     * it again. Finally, FatalError cannot be recovered.
     */
    #if PRINT_DEBUG
    void updateHook() {
        std::cout << "CameraTask: updateHook" << std::endl;
        camera_base::Task::updateHook();
    }
    #endif

    /** This hook is called by Orocos when the component is in the
     * RunTimeError state, at each activity step. See the discussion in
     * updateHook() about triggering options.
     *
     * Call recover() to go back in the Runtime state.
     */
    #if PRINT_DEBUG
    void errorHook() {
        std::cout << "CameraTask: errorHook" << std::endl;
        camera_base::Task::errorHook();
    }
    #endif
    /** This hook is called by Orocos when the state machine transitions
     * from Running to Stopped after stop() has been called.
     */
    #if PRINT_DEBUG
    void stopHook() {   
        std::cout << "CameraTask: stopHook" << std::endl;
        camera_base::Task::stopHook();
    }
    #endif

    /** This hook is called by Orocos when the state machine transitions
     * from Stopped to PreOperational, requiring the call to configureHook()
     * before calling start() again.
     */
    void cleanupHook();
};
} // end namespace camera_usb

#endif

