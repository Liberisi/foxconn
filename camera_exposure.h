#ifndef CAMERA_EXPOSURE_H
#define CAMERA_EXPOSURE_H

#include<string>

using namespace std;
class camera_exposure
{
public:
    camera_exposure();

    void read_param(const string& path);
    void write_param(const string& path);

    void set_location_camera_exposure(int location_camera_exposure);
    void set_read_code_camera_exposure(int read_code_camera_exposure);
    void set_frame_camera_exposure(int frame_camera_exposure);

    int location_camera_exposure() {return location_camera_exposure_;}
    int read_code_camera_exposure() {return read_code_camera_exposure_;}
    int frame_camera_exposure() {return frame_camera_exposure_;}

private:
    int location_camera_exposure_;
    int read_code_camera_exposure_;
    int frame_camera_exposure_;
};

#endif // CAMERA_EXPOSURE_H
