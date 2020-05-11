#include "support_location_select_region.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace std;

support_location_select_region::support_location_select_region()
{

}

void support_location_select_region::read_param(const string& path)
{
    ifstream file(path);
    if (!file.is_open())
        return;

    string line;

    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> row_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> col_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> phi_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> depth_;
    }
    if (getline(file, line))
    {
        stringstream ss(line);
        ss >> width_;
    }
}

void support_location_select_region::write_param(const string& path)
{
    ofstream file(path);
    file << row_ << endl
         << col_ << endl
         << phi_ << endl
         << depth_ << endl
         << width_ << endl;
}

void support_location_select_region::set_row(int row)
{
    row_ = row;
}
void support_location_select_region::set_col(int col)
{
    col_ = col;
}
void support_location_select_region::set_phi(int phi)
{
    phi_ = phi;
}
void support_location_select_region::set_depth(int depth)
{
    depth_ = depth;
}
void support_location_select_region::set_width(int width)
{
    width_ = width;
}
