#ifndef CAMERA_H
#define CAMERA_H

#include <string>

using namespace std;

namespace ssvision {

	typedef enum
	{
		kPixelFormatGray8,
		kPixelFormatRGB8,
		kPixelFormatUnknown
	} PixelFormat;

class Camera;
class CameraDelegate
{
public:
    virtual void on_camera_open(Camera* camera) = NULL;
    virtual void on_camera_close(Camera* camera) = NULL;
	virtual void on_camera_capture(Camera* camera, int width, int height, void* data, PixelFormat pixel_format) = NULL;
};

/**
 * 相机抽象类
 * 具体拍照功能在子类实现,本抽象类主要实现读写设备配置，写相机工作日志(将来?)
 */
class Camera
{
public:

    typedef struct
    {
        float exposure;
        float gain;
	} CaptureConfig;

    typedef enum
    {
        kUnknown,
        kGigE,
        kUSB,
        kCameraLink,
        k1394,
    } CameraInterface;



    /**
     * TODO: 用户
     */
    typedef void (*CameraCaptureCallback)(Camera* camera, void* data, int width, int height, PixelFormat pixel_format);

protected:
    Camera(string sn, CameraInterface type = Camera::kUnknown);
public:
    virtual ~Camera(){}

private:
    Camera(){}

public:
    const string serial_number() {return sn_;}
	CameraInterface camera_interface(){ return interface_; }

    virtual void open();
    virtual bool is_open();
    virtual void close();
    virtual bool trigger();

    // 开始接收硬触发
    virtual bool start(float trigger_delay_us = 0.0f);
    virtual bool is_grabbing();
    virtual void stop();

    // 可设置属性，
    const string name(){return name_;}
    void set_name(const string name) {name_ = name;}
    virtual float exposure(){return exposure_;}
    virtual void set_exposure(float exposure){exposure_ = exposure;}
    virtual float gain(){return gain_;}
    virtual void set_gain(float gain){gain_ = gain;}

    // 配置文件
    void set_config_path(string config_path);
    void load_config();
    void save_config();
    void load_config(string config_path);
    void save_config(string config_path);

    void set_delegate(CameraDelegate* delegate) {delegate_ = delegate;}

protected:
    string name_;
    const string sn_;
    CameraInterface interface_;
    float exposure_;
    float gain_;
    string config_path_;
    CameraDelegate* delegate_;
};

}
#endif // CAMERA_H
