#ifndef BASLERCAMERA_H
#define BASLERCAMERA_H

#include <string>
#include <vector>
#include <camera.h>
#include <pylon/PylonIncludes.h>

using namespace Pylon;

using namespace std;

namespace ssvision {

class BaslerCamera : public Camera, public CConfigurationEventHandler, public CImageEventHandler
{
public:
    static void start_basler_camera();
    static void stop_basler_camera();
    // 返回能够获取的basler相机列表
    static vector<string> camera_list();

public:
    BaslerCamera(string sn, Camera::CameraInterface camera_interface = Camera::kUnknown);
    virtual ~BaslerCamera();

public:
    // configuration event
    virtual void OnOpened(CInstantCamera& camera) ;
    // image event
    virtual void OnImageGrabbed(CInstantCamera &camera, const CGrabResultPtr &grab_result);

public:
    virtual float exposure();
    virtual void set_exposure(float exposure);
    // Basler 品牌的不同相机型号，对 gain 的设置方式不同，暂时不开放增益设置功能
//    virtual float gain();
//    virtual void set_gain(float gain);
    virtual void open();
    virtual bool is_open();
	virtual bool is_connected();
    virtual void close();
	virtual void detach();
    virtual bool trigger();
    // 硬触发延时: 0 ~ 1000000 us 即最多可延时 1s
    virtual bool start(float trigger_delay_us = 0.0f);
    virtual bool is_grabbing();
    virtual void stop();

private:
    CInstantCamera* pylon_camera_;
};

}
#endif // BASLERCAMERA_H
