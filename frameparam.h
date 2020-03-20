#ifndef FRAMEPARAM_H
#define FRAMEPARAM_H

#include <string>

using namespace std;

class FrameParam
{
public:
    FrameParam();

    void read_param(const string& path);
    void write_param(const string& path);

    void set_x(int x);
    void set_y(int y);
    void set_w(int w);
    void set_h(int h);
    void set_magic_w(int magic_w);
    void set_magic_h(int magic_h);

    void set_lx(int x) { lx_ = x;}
    void set_ly(int y) { ly_ = y;}
    void set_lw(int w) { lw_ = w;}
    void set_lh(int h) { lh_ = h;}

    void set_rx(int x) { rx_ = x;}
    void set_ry(int y) { ry_ = y;}
    void set_rw(int w) { rw_ = w;}
    void set_rh(int h) { rh_ = h;}
    void set_side_hand_magic_h(int t) { side_hand_magic_h_ = t;}
    void set_side_hand_magic_w(int t) { side_hand_magic_w_ = t;}

    int x() {return x_;}
    int y() {return y_;}
    int w() {return w_;}
    int h() {return h_;}
    int magic_w() {return magic_w_;}
    int magic_h() {return magic_h_;}

    int lx() {return lx_;}
    int ly() {return ly_;}
    int lw() {return lw_;}
    int lh() {return lh_;}

    int rx() {return rx_;}
    int ry() {return ry_;}
    int rw() {return rw_;}
    int rh() {return rh_;}
    int side_hand_magic_h() {return side_hand_magic_h_;}
    int side_hand_magic_w() {return side_hand_magic_w_;}

private:
    int x_;
    int y_;
    int w_;
    int h_;
    int magic_w_;
    int magic_h_;

    int lx_;
    int ly_;
    int lw_;
    int lh_;
    int side_hand_magic_w_;

    int rx_;
    int ry_;
    int rw_;
    int rh_;
    int side_hand_magic_h_;
};

#endif // FRAMEPARAM_H
