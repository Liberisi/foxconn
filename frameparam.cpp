#include "frameparam.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace std;

FrameParam::FrameParam()
{

}

void FrameParam::read_param(const string& path)
{
    ifstream file(path);
    if (!file.is_open())
        return;

    string line;

    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> x_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> y_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> w_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> h_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> magic_w_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> magic_h_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> lx_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> ly_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> lw_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> lh_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> side_hand_magic_w_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> rx_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> ry_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> rw_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> rh_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> side_hand_magic_h_;
    }
}

void FrameParam::write_param(const string& path)
{
    ofstream file(path);
    file << x_ << endl
         << y_ << endl
         << w_ << endl
         << h_ << endl
         << magic_w_ << endl
         << magic_h_ << endl
         << lx_ << endl
         << ly_ << endl
         << lw_ << endl
         << lh_ << endl
         << side_hand_magic_w_ << endl
         << rx_ << endl
         << ry_ << endl
         << rw_ << endl
         << rh_ << endl
         << side_hand_magic_h_ << endl;
}

void FrameParam::set_x(int x)
{
    x_ = x;
}
void FrameParam::set_y(int y)
{
    y_ = y;
}
void FrameParam::set_w(int w)
{
    w_ = w;
}
void FrameParam::set_h(int h)
{
    h_ = h;
}
void FrameParam::set_magic_w(int magic_w)
{
    magic_w_ = magic_w;
}
void FrameParam::set_magic_h(int magic_h)
{
    magic_h_ = magic_h;
}
