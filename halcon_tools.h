/**
 * 注意：像素格式需要是 gray8
 */

#ifndef HALCON_TOOLS_H
#define HALCON_TOOLS_H

#include <string>
#include <vector>
#include <halconcpp/HalconCpp.h>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/ml.hpp>

using namespace std;
using namespace HalconCpp;
using namespace cv;

namespace halcontools {

/**
 * 系统支持的所有条码类型
 */
vector<string> all_bar_code_names();
/**
 * 系统支持的所有二维码类型
 */
vector<string> all_2d_code_names();

cv::Mat HImageToIplImage(HImage &himg);
void write_image(void* data, int width, int height, const string& image_path);
void write_image(const HImage& img, const string& image_path);
void write_location_image_ng(void* data, int width, int height,
                             bool draw_rect,
                             double x, double y, double phi, double l1, double l2,
                             string ok_ng,
                             const string& image_path);
void write_location_image_ng(cv::Mat image,
                             bool draw_rect,
                             double x, double y, double phi, double l1, double l2,
                             string ok_ng,
                             const string& image_path);
void write_frame_image_ng(void* data, int width, int height,
                             bool disk_ok,
                             double x, double y, double w, double h,
                             bool left_found,
                             double left_x, double left_y, double left_l1, double left_l2,
                             bool right_found,
                             double right_x, double right_y, double right_l1, double right_l2,
                             const string& image_path);
void write_frame_image_ng(cv::Mat image,
                          bool disk_ok,
                          double x, double y, double w, double h,
                          bool left_found,
                          double left_x, double left_y, double left_l1, double left_l2,
                          bool right_found,
                          double right_x, double right_y, double right_l1, double right_l2,
                          const string& image_path);
void write_reading_code_image_ng(void* data, int width, int height,
                             bool draw_region_1, HRegion region_1,
                             bool draw_region_2, HRegion region_2,
                             bool draw_xld, HXLD xld,
                             string tid, string sn,
                             const string& image_path);
void write_reading_code_image_ng(cv::Mat image,
                                 bool draw_region_1, HRegion region_1,
                                 bool draw_region_2, HRegion region_2,
                                 bool draw_xld, HXLD xld,
                                 string tid, string sn,
                                 const string& image_path);

void read_bar_code(const HImage& img, const string& code_name, vector<string>& codes, vector<HRegion>& code_regions, int& duration_ms);
void read_bar_code(void* data, int width, int height, const string& code_name, vector<string>& codes, vector<HRegion>& code_regions, int& duration_ms);

void read_2d_code(const HImage& img, const string& code_name, vector<string>& codes, vector<HXLD>& code_regions, int& duration_ms);
void read_2d_code(void* data, int width, int height, const string& code_name, vector<string>& codes, vector<HXLD>& code_regions, int& duration_ms);

void read_2d_code_complex(const HImage& img, const string& code_name, vector<string>& codes, vector<HXLD>& code_regions, int& duration_ms);
void read_2d_code_complex(void* data, int width, int height, const string& code_name, vector<string>& codes, vector<HXLD>& code_regions, int& duration_ms);

void extract_rect(const HImage& img, int* x, int* y, double* phi, int* length1, int* length2, bool *find, int black_region_threshold);
void extract_rect(void* data, int width, int height, int* x, int* y, double* phi, int* length1, int* length2, bool *find, int black_region_threshold);
bool check_rect_size(int x, int y, double phi, int l1, int l2, HHomMat2D mat, int w, int h, int var);

void extract_ellipse(const HImage& img, int roi_x, int roi_y, int roi_r, float *x, float *y, float *r1, float *r2, float *angle, bool *found);

void detect_horizental_rough_edge(const HImage&img, int x, int y, int w_2, int h_2, bool& found, double& x1, double& y1, double& x2, double& y2, HXLDCont& edges );
void detect_white_area(const HImage& img, int x, int y, int w_2, int h_2, int area_threshold, bool& found, HRegion& white_area);
void detect_horizental_rough_edge(void* data, int width, int height, int x, int y, int w_2, int h_2, bool& found, double& x1, double& y1, double& x2, double& y2, HXLDCont& edges );
void detect_white_area(void* data, int width, int height, int x, int y, int w_2, int h_2, int area_threshold, bool& found, HRegion& white_area);

void detect_frame_disk(void* data, int width, int height,
                       HOGDescriptor& hog,
                       int roi_x, int roi_y, int roi_w, int roi_h,
                       int magic_w, int magic_h,
                       bool &disk_ok);
void detect_frame_disk(cv::Mat image,
                       HOGDescriptor& hog,
                       int roi_x, int roi_y, int roi_w, int roi_h,
                       int magic_w, int magic_h,
                       bool &disk_ok);
void detect_frame_side_hand(void* data, int width, int height,
                       HOGDescriptor& hog,
                       int roi_x, int roi_y, int roi_w, int roi_h,
                       int magic_w, int magic_h,
                       bool &found_hand);
void detect_frame_side_hand(cv::Mat image,
                       HOGDescriptor& hog,
                       int roi_x, int roi_y, int roi_w, int roi_h,
                       int magic_w, int magic_h,
                       bool &found_hand);

void draw_circle(const HWindow& window, float x, float y, float r, const char* color, float line_width, bool fill);
void draw_rect(const HWindow& window, float x, float y, float phi, int l1, int l2, const char* color, float line_width, bool fill);
void draw_region(const HWindow& window, const HRegion& region, const char* color, float line_width, bool fill);
void draw_xld(const HWindow& window, const HXLD& xld, const char* color, float line_width, bool fill);
void draw_cross(const HWindow& window, float x, float y, float r, const char* color, float angle, float line_width);
void draw_line(const HWindow& window, float x1, float y1, float x2, float y2, const char* color, float line_width = 1);

void transform_point(HHomMat2D mat, float px, float py, float &qx, float &qy);

extern const char* const kHalconColorBlack;// "black",
extern const char* const kHalconColorWhite;// "white",
extern const char* const kHalconColorRed;// "red",
extern const char* const kHalconColorGreen;// "green",
extern const char* const kHalconColorBlue;// "blue",
extern const char* const kHalconColorCyan;// "cyan",
extern const char* const kHalconColorMagenta;// "magenta",
extern const char* const kHalconColorYellow;// "yellow",
extern const char* const kHalconColorDimGray;// "dim gray",
extern const char* const kHalconColorGray;// "gray",
extern const char* const kHalconColorLightGray;// "light gray",
extern const char* const kHalconColorMediumSlateBlue;// "medium slate blue", 
//"coral", "slate blue", 
extern const char* const kHalconColorSpringGreen;// "spring green", 
//"orange red", "orange", "dark olive green", "pink", "cadet blue", "#003075", "#e53019", "#ffb529", "#f28d26bb"

}


#endif // HALCON_TOOLS_H
