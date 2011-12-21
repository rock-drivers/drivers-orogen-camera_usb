/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef CAMERA_USB_TASK_TASK_HPP
#define CAMERA_USB_TASK_TASK_HPP

#include "camera_usb/TaskBase.hpp"
#include "camera_base/TaskBase.hpp"
#include "frame_helper/FrameHelper.h"
#include "camera_interface/CamInterface.h"

#include "camera_usb/cam_usb.h" // Driver

namespace camera_usb {
class Task : public TaskBase
{
friend class TaskBase;
 protected:
    camera::CamInfo* mCamInfo;

 public:
    Task(std::string const& name = "orogen_camera_usb::Task");
    Task(std::string const& name, RTT::ExecutionEngine* engine);

    ~Task();

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
    bool configureHook() {
        RTT::log(RTT::Debug) << "Task: configureHook" << RTT::endlog();
        camera_base::Task::configureHook();
    }

    /** This hook is called by Orocos when the state machine transitions
     * from Stopped to Running. If it returns false, then the component will
     * stay in Stopped. Otherwise, it goes into Running and updateHook()
     * will be called.
     */
    bool startHook() {
        RTT::log(RTT::Debug) << "Task: startHook" << RTT::endlog();
        camera_base::Task::startHook();
    }


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
    void updateHook() {
        RTT::log(RTT::Debug) << "Task: updateHook" << RTT::endlog();
        camera_base::Task::updateHook();
    }

    /** This hook is called by Orocos when the component is in the
     * RunTimeError state, at each activity step. See the discussion in
     * updateHook() about triggering options.
     *
     * Call recover() to go back in the Runtime state.
     */
    void errorHook() {
        RTT::log(RTT::Debug) << "Task: errorHook" << RTT::endlog();
        camera_base::Task::errorHook();
    }

    /** This hook is called by Orocos when the state machine transitions
     * from Running to Stopped after stop() has been called.
     */
    void stopHook() {   
        RTT::log(RTT::Debug) << "Task: stopHook" << RTT::endlog();
        camera_base::Task::stopHook();
    }

    /** This hook is called by Orocos when the state machine transitions
     * from Stopped to PreOperational, requiring the call to configureHook()
     * before calling start() again.
     */
    void cleanupHook();
};
} // end namespace camera_usb

#endif

