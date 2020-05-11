#ifndef SUPPORT_LOCATION_SELECT_REGION_H
#define SUPPORT_LOCATION_SELECT_REGION_H

#include<string>

using namespace std;
class support_location_select_region
{
public:
    support_location_select_region();

    void read_param(const string& path);
    void write_param(const string& path);

    void set_row(int row);
    void set_col(int col);
    void set_phi(int phi);
    void set_depth(int depth);
    void set_width(int width);

    int row() {return row_;}
    int col() {return col_;}
    int phi() {return phi_;}
    int depth() {return depth_;}
    int width() {return width_;}

private:
    int row_;
    int col_;
    int phi_;
    int depth_;
    int width_;
};

#endif // SUPPORT_LOCATION_SELECT_REGION_H
