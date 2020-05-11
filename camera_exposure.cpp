#include "camera_exposure.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

camera_exposure::camera_exposure()
{

}



void camera_exposure::read_param(const string& path)
{
    ifstream file(path);
    if (!file.is_open())
        return;

    string line;

    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> location_camera_exposure_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> read_code_camera_exposure_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> frame_camera_exposure_;
    }
}

void camera_exposure::write_param(const string& path)
{
    ofstream file(path);
    file << location_camera_exposure_ << endl
         << read_code_camera_exposure_ << endl
         << frame_camera_exposure_ << endl;
}

void camera_exposure::set_location_camera_exposure(int location_camera_exposure)
{
    location_camera_exposure_ = location_camera_exposure;
}
void camera_exposure::set_read_code_camera_exposure(int read_code_camera_exposure)
{
    read_code_camera_exposure_ = read_code_camera_exposure;
}
void camera_exposure::set_frame_camera_exposure(int frame_camera_exposure)
{
    frame_camera_exposure_ = frame_camera_exposure;
}

