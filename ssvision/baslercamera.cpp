#include "baslercamera.h"

namespace  ssvision {

void BaslerCamera::start_basler_camera()
{
    PylonInitialize();
}
void BaslerCamera::stop_basler_camera()
{
    PylonTerminate();
}
vector<string> BaslerCamera::camera_list()
{
    vector<string> sn_list;
    DeviceInfoList info_list;
    int camera_count = CTlFactory::GetInstance().EnumerateDevices(info_list);
    for (int i = 0; i < camera_count; i++)
    {
        CDeviceInfo deviceinfo = info_list[i];
        string sn = deviceinfo.GetSerialNumber();
        sn_list.push_back(sn);
    }
    return sn_list;
}

BaslerCamera::BaslerCamera(string sn, Camera::CameraInterface type):Camera(sn, type)
{
    pylon_camera_ = NULL;
    DeviceInfoList info_list;
    int camera_count = CTlFactory::GetInstance().EnumerateDevices(info_list);
    for (int i = 0; i < camera_count; i++)
    {
        CDeviceInfo deviceinfo = info_list[i];
        string serial_number = deviceinfo.GetSerialNumber();
        if (serial_number.compare(sn) == 0)
        {
            IPylonDevice* pylon_device = CTlFactory::GetInstance().CreateDevice(deviceinfo);
            pylon_camera_ = new CInstantCamera(pylon_device, ECleanup::Cleanup_Delete);
            if (pylon_camera_)
            {
                pylon_camera_->RegisterConfiguration(this, ERegistrationMode::RegistrationMode_ReplaceAll, ECleanup::Cleanup_None);
                pylon_camera_->RegisterImageEventHandler(this, ERegistrationMode::RegistrationMode_ReplaceAll, ECleanup::Cleanup_None);
            }
            break;
        }
    }
}

BaslerCamera::~BaslerCamera()
{
    if (pylon_camera_)
    {
        pylon_camera_->Close();
        delete pylon_camera_;
        pylon_camera_ = NULL;
    }
}
float BaslerCamera::exposure()
{
    if (pylon_camera_ && pylon_camera_->IsOpen())
    {
        GenApi::INodeMap& nodemap = pylon_camera_->GetNodeMap();
        return GenApi::CFloatPtr(nodemap.GetNode("ExposureTimeAbs"))->GetValue();
    }
    else
        return 0;
}
void BaslerCamera::set_exposure(float exposure)
{
    if (pylon_camera_ && pylon_camera_->IsOpen())
    {
        GenApi::INodeMap& nodemap = pylon_camera_->GetNodeMap();
        GenApi::CEnumerationPtr(nodemap.GetNode("ExposureTimeMode"))->FromString("Standard");
        GenApi::CFloatPtr(nodemap.GetNode("ExposureTimeAbs"))->SetValue(exposure);
    }
}
//float BaslerCamera::gain()
//{
//    // 3800 33~255
//    // 2500 0~63
//}
//void BaslerCamera::set_gain(float gain)
//{

//}
void BaslerCamera::open()
{
    if (pylon_camera_)
    {
		if (!pylon_camera_->IsOpen())
		{
			try
			{
				pylon_camera_->Open();
			}
			catch ( GenICam::RuntimeException )
			{
				//GenICam_3_0_Basler_pylon_v5_0::RuntimeException
			}
		}
    }
}
bool BaslerCamera::is_open()
{
    if (pylon_camera_)
        return pylon_camera_->IsOpen();
    else
        return false;
}
void BaslerCamera::close()
{
    if (pylon_camera_)
        pylon_camera_->Close();
}
bool BaslerCamera::trigger()
{
	if (pylon_camera_ && pylon_camera_->CanWaitForFrameTriggerReady())
    {
		pylon_camera_->StartGrabbing(1, GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);
		try
		{
			if (pylon_camera_->WaitForFrameTriggerReady(500, TimeoutHandling_Return))
			{
				pylon_camera_->ExecuteSoftwareTrigger();
				return true;
			}
		}
		catch (Pylon::TimeoutException)
		{
			return false;
		}
    }
    return false;
}
bool BaslerCamera::start(float trigger_delay_us)
{
    if (is_open() && !is_grabbing())
    {
        GenApi::INodeMap& nodemap = pylon_camera_->GetNodeMap();
        GenApi::CEnumerationPtr(nodemap.GetNode("TriggerSelector"))->FromString("FrameStart");
        GenApi::CEnumerationPtr(nodemap.GetNode("TriggerMode"))->FromString("On");
        // 硬编码参数依据来自于 pylon viewer
        if (trigger_delay_us >= 0.0f && trigger_delay_us <= 1000000.0f)
        {
              GenApi::CFloatPtr(nodemap.GetNode("TriggerDelayAbs"))->SetValue(trigger_delay_us);
        }
        GenApi::CEnumerationPtr(nodemap.GetNode("TriggerSelector"))->FromString("AcquisitionStart");
        GenApi::CEnumerationPtr(nodemap.GetNode("TriggerMode"))->FromString("Off");
        pylon_camera_->StartGrabbing(GrabStrategy_OneByOne, GrabLoop_ProvidedByInstantCamera);
        return true;
    }else
    {
        return false;
    }
}
bool BaslerCamera::is_grabbing()
{
    if (pylon_camera_)
    {
        return pylon_camera_->IsGrabbing();
    }
    else
        return false;
}
void BaslerCamera::stop()
{
    if (pylon_camera_ && pylon_camera_->IsGrabbing())
		pylon_camera_->StopGrabbing();
    GenApi::INodeMap& nodemap = pylon_camera_->GetNodeMap();
    GenApi::CEnumerationPtr(nodemap.GetNode("TriggerSelector"))->FromString("FrameStart");
    GenApi::CEnumerationPtr(nodemap.GetNode("TriggerMode"))->FromString("Off");
    GenApi::CEnumerationPtr(nodemap.GetNode("TriggerSelector"))->FromString("AcquisitionStart");
    GenApi::CEnumerationPtr(nodemap.GetNode("TriggerMode"))->FromString("Off");
}
void BaslerCamera::OnOpened(CInstantCamera&)
{
    if (delegate_)
        delegate_->on_camera_open(this);
}
void BaslerCamera::OnImageGrabbed(CInstantCamera&, const CGrabResultPtr &grab_result)
{
	if (delegate_ && grab_result.IsValid())
	{
		int width = grab_result->GetWidth();
        int height = grab_result->GetHeight();
		EPixelType pixel_type = grab_result->GetPixelType();
		PixelFormat pixel_format = kPixelFormatUnknown;
		switch (pixel_type)
		{
		case EPixelType::PixelType_Mono8:
		{
		    pixel_format = kPixelFormatGray8;
		}
			break;
		default:
			break;
		}
		delegate_->on_camera_capture(this, width, height, grab_result->GetBuffer(), pixel_format);
	}
}

}
