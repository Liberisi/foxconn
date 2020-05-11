#include "camera.h"
#include <opencv2/opencv.hpp>

namespace ssvision {

static const char* kCameraConfigKeyName = "kCameraConfigKeyName";
static const char* kCameraConfigKeyExposure = "kCameraConfigKeyExposure";
static const char* kCameraConfigKeyGain = "kCameraConfigKeyGain";

static void ReadCameraConfigFile(Camera* camera, cv::FileStorage& fs);
static void WriteCameraConfigFile(Camera* camera, cv::FileStorage& fs);

Camera::Camera(string sn, CameraInterface interface) :sn_(sn), exposure_(0.0), gain_(0.0)
{
    delegate_ = NULL;
    interface_ = interface;
}

void Camera::set_config_path(string config_path)
{
    config_path_ = config_path;
}

void Camera::load_config()
{
    load_config(config_path_);
}

void Camera::save_config()
{
    save_config(config_path_);
}

void Camera::load_config(string config_path)
{
    if (config_path.length() == 0)
    {
        return;
    }
    if (config_path.length() == 0)
    {
        return;
    }
    cv::FileStorage fs(config_path.c_str(), cv::FileStorage::READ | cv::FileStorage::FORMAT_XML);
    ReadCameraConfigFile(this, fs);
}

void Camera::save_config(string config_path)
{
    if (config_path.length() == 0)
    {
        return;
    }
    cv::FileStorage fs(config_path.c_str(), cv::FileStorage::WRITE | cv::FileStorage::FORMAT_XML);
    WriteCameraConfigFile(this, fs);
}

void Camera::open()
{
}
bool Camera::is_open()
{
    return false;
}
bool Camera::is_connected()
{
	return false;
}
void Camera::close()
{
}
void Camera::detach()
{
}
bool Camera::trigger()
{
    return false;
}
bool Camera::start(float)
{
    return false;
}
bool Camera::is_grabbing()
{
    return true;
}
void Camera::stop()
{

}

void WriteCameraConfigFile(Camera* camera, cv::FileStorage& fs)
{
    if (!camera)
        return;
    if (camera->name().length() > 0)
        fs << kCameraConfigKeyName << camera->name();
    fs << kCameraConfigKeyExposure << camera->exposure();
    fs << kCameraConfigKeyGain << camera->gain();
}

void ReadCameraConfigFile(Camera* camera, cv::FileStorage& fs)
{
    if (!camera)
        return;
    string camera_name;
    fs[kCameraConfigKeyName] >> camera_name;
    camera->set_name(camera_name);
    float exposure;
    fs[kCameraConfigKeyExposure] >> exposure;
    camera->set_exposure(exposure);
    float gain;
    fs[kCameraConfigKeyGain] >> gain;
    camera->set_gain(gain);
}

}
