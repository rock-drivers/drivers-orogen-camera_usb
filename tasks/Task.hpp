/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef CAMERA_USB_TASK_TASK_HPP
#define CAMERA_USB_TASK_TASK_HPP

#include "camera_usb/TaskBase.hpp"
#include "base/Timeout.hpp"

namespace camera
{
    class CamInfo;
}

namespace camera_usb {
/**
 * If a not valid image size is set, the driver will choose valid values which will lead
 * to a resize of the JPEG data which will lead to a corrupted JPEG-file. So, take sure
 * to set a valid 'width' and 'height'.  
 */
class Task : public TaskBase
{
friend class TaskBase;
 protected:
    camera::CamInfo* mCamInfo;
    base::Timeout timeout;

 public:
    Task(std::string const& name = "orogen_camera_usb::Task");
    Task(std::string const& name, RTT::ExecutionEngine* engine);

    ~Task();

    /** 
     * Starts and configure the camera. At the end the image width/height are
     * adapted regarding to the real image size.
     */
    bool configureCamera();

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
     *
     * Creates and opens the camera-usb connection. After the camera has been opened
     * it can be configured.
     */
    bool configureHook() {
        RTT::log(RTT::Debug) << "Task: configureHook" << RTT::endlog();
        return camera_base::Task::configureHook();
    }

    /** This hook is called by Orocos when the state machine transitions
     * from Stopped to Running. If it returns false, then the component will
     * stay in Stopped. Otherwise, it goes into Running and updateHook()
     * will be called.
     */
    bool startHook();


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
    void updateHook();

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
    
    /**
     * Can be used to set the default parameters of the camera.
     */
    void setControlsToDefault();
};
} // end namespace camera_usb

#endif
