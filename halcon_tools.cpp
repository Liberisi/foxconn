#include "halcon_tools.h"
#include <time.h>
#include <ssvision/ssvision>

namespace halcontools
{
	static inline void set_color_fill_line_width(const HWindow& window, const char* color, bool fill, float line_width)
	{
		if (fill)
			window.SetDraw("fill");
		else
			window.SetDraw("margin");
		if (color)
			window.SetColor(color);
		line_width = line_width < 1 ? 1 : line_width;
		line_width = line_width > 2000 ? 2000 : line_width;
		window.SetLineWidth(line_width);
	}

    cv::Mat HImageToIplImage(HImage &himg)
    {
        cv::Mat pImage;
        //Hlong htChannels;
        //char cType[MAX_STRING];
        Hlong width = 0;
        Hlong height = 0;
        //width = height = 0;
        //转换图像格式
        //convert_image_type(Hobj, &Hobj, "byte");

        HString type;
            unsigned char *ptr = (unsigned char *)himg.GetImagePointer1(&type, &width, &height);
            pImage = cv::Mat(height, width, CV_8UC1);
            memcpy(pImage.data, ptr, width * height);

        return pImage;
    }

    void detect_frame_disk(cv::Mat src_image,
                           HOGDescriptor& hog,
                           int roi_x, int roi_y, int roi_w, int roi_h,
                           int magic_w, int magic_h,
                           bool &disk_ok)
    {
        cv::Rect rect(roi_x, roi_y, roi_w, roi_h);
        cv::Mat image = src_image(rect);
        cv::resize(image, image, cv::Size(magic_w, magic_h));

        vector<Point> found_locations;
        hog.detect(image, found_locations);
        if (found_locations.size() > 0)
        {
            disk_ok = true;
        }
        else
        {
            disk_ok = false;
        }
    }
    void detect_frame_disk(void* data, int width, int height,
                           HOGDescriptor& hog,
                           int roi_x, int roi_y, int roi_w, int roi_h,
                           int magic_w, int magic_h,
                           bool &disk_ok)
    {
        cv::Mat src_image(height, width, CV_8UC1, data);
        detect_frame_disk(src_image, hog, roi_x, roi_y, roi_w, roi_h, magic_w, magic_h, disk_ok);
    }
    void detect_frame_side_hand(void* data, int width, int height,
                           HOGDescriptor& hog,
                           int roi_x, int roi_y, int roi_w, int roi_h,
                           int magic_w, int magic_h,
                           bool &found_hand)
    {
        cv::Mat src_image(height, width, CV_8UC1, data);
        detect_frame_side_hand(src_image, hog, roi_x, roi_y, roi_w, roi_h, magic_w, magic_h, found_hand);
    }
    void detect_frame_side_hand(cv::Mat src_image,
                           HOGDescriptor& hog,
                           int roi_x, int roi_y, int roi_w, int roi_h,
                           int magic_w, int magic_h,
                           bool &found_hand)
    {
        cv::Rect rect(roi_x, roi_y, roi_w, roi_h);
        cv::Mat image = src_image(rect);
        cv::resize(image, image, cv::Size(magic_w, magic_h));

        vector<Point> found_locations;
        hog.detect(image, found_locations);
        if (found_locations.size() > 0)
        {
            found_hand = true;
        }
        else
        {
            found_hand = false;
        }
    }
    void write_image(void* data, int width, int height, const string& image_path)
    {
        if (!data || width <= 0 || height <= 0 || image_path.length() == 0)
            return;
        HImage img("byte", width, height, data);
        write_image(img, image_path);
    }
    void write_image(const HImage& image, const string& image_path)
    {
        HalconCpp::WriteImage(image, "bmp", 0, image_path.c_str());
    }
    void read_bar_code(void* data, int width, int height, const string& code_name, vector<string>& codes, vector<HRegion>& code_regions, int& duration_ms)
	{
		HImage img("byte", width, height, data);
        read_bar_code(img, code_name, codes, code_regions, duration_ms);
	}
    vector<string> all_2d_code_names()
    {
        vector<string> code_names;
        code_names.push_back(ssvision::k2DCodeDataMatrixECC200);
        return code_names;
    }

    void read_2d_code_complex(const HImage& img, const string& code_name, vector<string>& codes, vector<HXLD>& code_regions, int& duration_ms)
    {
        clock_t clock_begin = clock();
        HDataCode2D datacode;
        datacode.CreateDataCode2dModel(code_name.c_str(), "default_parameters", "enhanced_recognition");
        HTuple readed_strings;
        HTuple result_handles;


		HImage image = img.ScaleImageMax();
		image = image.Emphasize(7, 7, 1);
		image = image.MedianImage("circle", 1, "mirrored");
		HImage image_invert = image.InvertImage();
        HImage image_result = image_invert.GrayRangeRect(10, 10);

        HRegion white_region = image_result.FastThreshold(128, 255, 10);
        white_region = white_region.Connection();
        white_region = white_region.FillUp();

        //	select_shape(ConnectedRegions2, SelectedRegions1, ['area', 'rectangularity'], 'and', [99999, 0.5], [9999999, 1])
        HTuple features;
        features.Append("area");
        features.Append("rectangularity");
        HTuple min, max;
        min.Append(8999);
        min.Append(0.5);
        max.Append(29999);
        max.Append(1);
        white_region = white_region.SelectShape(features, "and", min, max);
        white_region = white_region.DilationRectangle1(25, 25);
        white_region = white_region.Union1();
        image_invert = image_invert.ReduceDomain(white_region);

		HXLDCont xld = datacode.FindDataCode2d(image_invert, "stop_after_result_num", 2, &result_handles, &readed_strings);
        for (int i = 0; i < readed_strings.Length(); ++i)
        {
            //HString* str = readed_strings.ToSArr();
            HTuple t = readed_strings[i];
            codes.push_back(t.ToString().Text());
            HXLD region = xld.SelectObj(i + 1);
            code_regions.push_back(region);
        }
        datacode.Clear();
        clock_t clock_end = clock();
        duration_ms = (clock_end - clock_begin) * 1000 / CLOCKS_PER_SEC;
    }

    void read_2d_code_complex(void* data, int width, int height, const string& code_name, vector<string>& codes, vector<HXLD>& code_regions, int& duration_ms)
    {
        HImage img("byte", width, height, data);
        read_2d_code_complex(img, code_name, codes, code_regions, duration_ms);
    }

    void read_2d_code(void* data, int width, int height, const string& code_name, vector<string>& codes, vector<HXLD>& code_regions, int& duration_ms)
    {
        HImage img("byte", width, height, data);
        read_2d_code(img, code_name, codes, code_regions, duration_ms);
    }
    void read_2d_code(const HImage& img, const string& code_name, vector<string>& codes, vector<HXLD>& code_regions, int& duration_ms)
	{
        clock_t clock_begin = clock();
		HDataCode2D datacode;
		datacode.CreateDataCode2dModel(code_name.c_str(), "default_parameters", "enhanced_recognition");
		HTuple readed_strings;
		HTuple result_handles;
		HXLDCont xld = datacode.FindDataCode2d(img, "stop_after_result_num", 2, &result_handles, &readed_strings);
		for (int i = 0; i < readed_strings.Length(); ++i)
		{
            //HString* str = readed_strings.ToSArr();
			HTuple t = readed_strings[i];
			codes.push_back(t.ToString().Text());
			HXLD region = xld.SelectObj(i + 1);
			code_regions.push_back(region);
		}
		datacode.Clear();
        clock_t clock_end = clock();
        duration_ms = (clock_end - clock_begin) * 1000 / CLOCKS_PER_SEC;
	}

    vector<string> all_bar_code_names()
    {
        vector<string> code_names;
        code_names.push_back(ssvision::kBarCodeCode128);
        return code_names;
    }

    void read_bar_code(const HImage& img, const string& code_name, vector<string>& codes, vector<HRegion>& code_regions, int& duration_ms)
    {
        clock_t clock_begin = clock();
		HBarCode barcode;
        HTuple readed_strings;
		barcode.CreateBarCodeModel(HTuple(), HTuple());
		HRegion regions = barcode.FindBarCode(img, code_name.c_str(), &readed_strings);
		for (int i = 0; i < readed_strings.Length(); ++i)
		{
			HTuple t = readed_strings[i];
			codes.push_back(t.ToString().Text());
			HRegion region = regions.SelectObj(i + 1);
			code_regions.push_back(region);
		}
		barcode.Clear();
        clock_t clock_end = clock();
        duration_ms = (clock_end - clock_begin) * 1000 / CLOCKS_PER_SEC;
    }
	void extract_ellipse(const HImage& img, int roi_x, int roi_y, int roi_r, float *x, float *y, float *r1, float *r2, float *angle, bool *found)
	{
		HRegion circle;
		circle.GenCircle(roi_y, roi_x, roi_r);
		HImage roi = img.ReduceDomain(circle);
        HImage roi_mean = roi.MeanImage(13, 13);
        HRegion black_region = roi_mean.Threshold(0, 128);
        if (!black_region.IsInitialized() && found)
        {
            *found = false;
            return;
        }
        black_region = black_region.Connection();
        black_region = black_region.FillUp();
        HXLDCont black_xld_cont = black_region.GenContourRegionXld("border");


//		HXLDCont edges = roi.EdgesSubPix("canny", 1, 20, 40);
//		HXLDCont segmented = edges.SegmentContoursXld("lines_ellipses", 5, 4, 2);
//		HXLDCont circles;
//		circles.GenEmptyObj();
//		for (int i = 0; i < segmented.CountObj(); ++i)
//		{
//			HXLDCont c = segmented.SelectObj(i + 1);
//			HTuple type = c.GetContourGlobalAttribXld("cont_approx");
//			if (type == 0)
//			{
//				circles = circles.ConcatObj(c);
//			}
//		}
//		if (circles.CountObj() > 0)
//		{
//			int c_count = circles.CountObj();
		    HTuple row, col, phi, radius_1, radius_2, start_phi, end_phi, clockwise;
            HalconCpp::FitEllipseContourXld(black_xld_cont, "fitzgibbon", -1, 2, 0, 200, 3, 2.0, &row, &col, &phi, &radius_1, &radius_2, &start_phi, &end_phi, &clockwise);
			if (found)
				*found = true;
			if (y)
				*y = (double)row;
			if (x)
				*x = col;
			if (angle)
				*angle = phi;
			if (r1)
				*r1 = radius_1;
			if (r2)
				*r2 = radius_2;
//		}
//		else
//		{
//			if (found)
//				*found = false;
//		}
    }

    bool check_rect_size(int x, int y, double phi, int length1, int length2, HHomMat2D mat, int w, int h, int var)
    {
        float x1 = x + length1 * cos(phi);
        float y1 = y - length1 * sin(phi);
        float x2 = x - length1 * cos(phi);
        float y2 = y + length1 * sin(phi);
        halcontools::transform_point(mat, x1, y1, x1, y1);
        halcontools::transform_point(mat, x2, y2, x2, y2);
        float pi_2 = 3.14159f * 0.5;
        float x3 = x + length2 * cos(pi_2 + phi);
        float y3 = y - length2 * sin(pi_2 + phi);
        float x4 = x - length2 * cos(pi_2 + phi);
        float y4 = y + length2 * sin(pi_2 + phi);
        halcontools::transform_point(mat, x3, y3, x3, y3);
        halcontools::transform_point(mat, x4, y4, x4, y4);
        float dx = x1 - x2;
        float dy = y1 - y2;
        float width_mm = sqrt(dx * dx + dy * dy);
        dx = x3 - x4;
        dy = y3 - y4;
        float height_mm = sqrt(dx * dx + dy * dy);
        if (width_mm > w - var && width_mm < w + var && height_mm > h - var && height_mm < h + var)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void extract_rect(const HImage& img, int* x, int* y, double* phi, int* length1, int* length2, bool *find, int black_region_threshold)
	{
		HRegion white_region = img.Threshold(128, 255);
		if (!white_region.IsInitialized() && find)
		{
			*find = false;
			return;
		}
        white_region = white_region.ClosingCircle(20);
		white_region = white_region.Connection();
		HTuple row, col;
		HTuple region_area = white_region.AreaCenter(&row, &col);
		HTuple region_area_sorted_idx = region_area.TupleSortIndex();
		int area_max_idx = region_area_sorted_idx[region_area_sorted_idx.Length() - 1];
		int area_max = region_area[area_max_idx ];
        HTuple width, height;
        //int width = img.Width();
        //int height = img.Height();
        HalconCpp::GetImageSize(img, &width, &height);
        if (find && area_max < width * height * 0.5 * 0.5)
		{
			*find = false;
			return;
		}

		HRegion roi_region = white_region.SelectObj(area_max_idx + 1);
		roi_region = roi_region.FillUp();
		roi_region = roi_region.ErosionCircle(60);
		HImage roi = img.ReduceDomain(roi_region);
		HImage roi_mean = roi.MeanImage(53, 53);
		roi_region = roi_region.ErosionCircle(30);
		roi_mean = roi_mean.ReduceDomain(roi_region);

        if (black_region_threshold < 30)
        {
            black_region_threshold = 30;
        }
        else if (black_region_threshold > 230)
        {
            black_region_threshold = 230;
        }

        HRegion black_region = roi_mean.Threshold(0, black_region_threshold);
		if (!black_region.IsInitialized() && find)
		{
			*find = false;
			return;
		}
        black_region = black_region.OpeningCircle(30);
		black_region = black_region.Connection();
		black_region = black_region.FillUp();
		HTuple black_region_area = black_region.AreaCenter(&row, &col);
		HTuple black_region_sorted_idx = black_region_area.TupleSortIndex();
		int black_region_area_max_idx = black_region_sorted_idx[black_region_sorted_idx.Length() - 1];
		black_region = black_region.SelectObj(black_region_area_max_idx + 1);

		double r, c,  l1, l2;
		double theta;

//        HString point_order;
//        HXLDCont black_xld_cont = black_region.GenContourRegionXld("border");
//		black_xld_cont.FitRectangle2ContourXld("regression", -1, 0, 0, 3, 2, &r, &c, &theta, &l1, &l2, &point_order);

        black_region.SmallestRectangle2(&r, &c, &theta, &l1, &l2);

		if (x)
			*x = c;
		if (y)
			*y = r;
		if (phi)
			*phi = theta;
		if (length1)
			*length1 = l1;
		if (length2)
			*length2 = l2;
		if (find)
			*find = true;
	}

    void extract_rect(void* data, int width, int height, int* x, int* y, double* phi, int* length1, int* length2, bool *find, int black_region_threshold)
    {
        if (!data || width <= 0 || height <= 0)
        {
            if (find)
                *find = false;
            return;
        }
        HImage img("byte", width, height, data);
        extract_rect(img, x, y, phi, length1, length2, find, black_region_threshold);
    }

	void detect_horizental_rough_edge(const HImage&img, int x, int y, int w_2, int h_2, bool& found, double& x1, double& y1, double& x2, double& y2, HXLDCont& out_edges)
    {
        found = false;
		HRegion rect;
		rect.GenRectangle1(y - h_2, x - w_2, y + h_2, x + w_2);
        HImage reduced_mean = img.MeanImage(25, 25).ReduceDomain(rect);
        HXLDCont edges = reduced_mean.EdgesSubPix("canny", 7, 20, 40);
        if (edges.CountObj() == 0)
            return;

		int point_num_max = 0;
		int idx = -1;
        for (int i = 0; i < edges.CountObj(); ++i)
        {
            HXLDCont edge = edges.SelectObj(i + 1);
			int point_num = edge.ContourPointNumXld();
			if (point_num > point_num_max)
            {
				idx = i;
                point_num_max = point_num;
            }
        }

		double width = w_2 * 2;
        if (idx != -1 && point_num_max > width * 0.8 && point_num_max < width * 1.2)
		{
			found = true;
			HXLDCont horizental_line = edges.SelectObj(1 + idx);
			double r1, c1, r2, c2, nr, nc, dist;
			horizental_line.FitLineContourXld("tukey", -1, 0, 5, 2,
				&r1, &c1,
				&r2, &c2,
				&nr, &nc, &dist);
			x1 = c1;
			y1 = r1;
			x2 = c2;
			y2 = r2;
		}
    }

    void detect_white_area(const HImage& img, int x, int y, int w_2, int h_2, int area_threshold, bool& found, HRegion& white_area)
    {
        HRegion rect;
        rect.GenRectangle1(y - h_2, x - w_2, y + h_2, x + w_2);
        HImage reduced_mean = img.MeanImage(25, 25).ReduceDomain(rect);
        HRegion regions = reduced_mean.Threshold(168, 255);
		if (regions.CountObj() > 0)
		{
			white_area = regions.SelectShape("area", "and", area_threshold, w_2 * h_2 * 4);
			found = white_area.CountObj() > 0 ? true : false;
		}
		else
		{
			found = false;
		}
    }

    void detect_horizental_rough_edge(void* data, int width, int height, int x, int y, int w_2, int h_2, bool& found, double& x1, double& y1, double& x2, double& y2, HXLDCont& edges )
    {
        HImage img("byte", width, height, data);
        detect_horizental_rough_edge(img, x, y, w_2, h_2, found, x1, y1, x2, y2, edges);
    }

    void detect_white_area(void* data, int width, int height, int x, int y, int w_2, int h_2, int area_threshold, bool& found, HRegion& white_area)
    {
        HImage img("byte", width, height, data);
        detect_white_area(img, x, y, w_2, h_2, area_threshold, found, white_area);
    }

    void transform_point(HHomMat2D mat, float px, float py, float &qx, float &qy)
    {
        HTuple x, y, w;
        ProjectiveTransPoint2d(mat, (double)px, (double)py, 1, &x, &y, &w);
        double xx = x;
        double yy = y;
        double ww = w;
        qx = xx/ww;
        qy = yy/ww;
    }

	void draw_circle(const HWindow& window, float x, float y, float r, const char* color, float line_width, bool fill)
	{
		if (!window.IsHandleValid())
			return;
		set_color_fill_line_width(window, color, fill, line_width);
		window.DispCircle(y + 0.5, x + 0.5, r);
	}
	void draw_rect(const HWindow& window, float x, float y, float phi, int l1, int l2, const char* color, float line_width, bool fill)
	{
		if (!window.IsHandleValid())
			return;
        set_color_fill_line_width(window, color, fill, line_width);
		window.DispRectangle2(y + 0.5, x + 0.5, phi, l1, l2);
	}
    void draw_cross(const HWindow& window, float x, float y, float r, const char* color, float angle, float line_width)
    {
        if (!window.IsHandleValid())
            return;
        set_color_fill_line_width(window, color, false, line_width);
        window.DispCross(y + 0.5, x + 0.5, r, angle);
    }
	void draw_region(const HWindow& window, const HRegion& region, const char* color, float line_width, bool fill)
	{
		if (!window.IsHandleValid())
			return;

        set_color_fill_line_width(window, color, fill, line_width);

		if (region.IsInitialized())
			window.DispRegion(region);
	}
	void draw_xld(const HWindow& window, const HXLD& xld, const char* color, float line_width, bool fill)
	{
		if (!window.IsHandleValid())
			return;

        set_color_fill_line_width(window, color, fill, line_width);

		if (xld.IsInitialized())
			window.DispXld(xld);
	}
    void draw_line(const HWindow& window, float x1, float y1, float x2, float y2, const char* color, float line_width)
    {
        if (!window.IsHandleValid())
            return;
        set_color_fill_line_width(window, color, false, line_width);
        window.DispLine(y1, x1, y2, x2);
    }

	const char* const kHalconColorBlack = "black";
	const char* const kHalconColorWhite = "white";
	const char* const kHalconColorRed = "red";
	const char* const kHalconColorGreen = "green";
	const char* const kHalconColorBlue = "blue";
	const char* const kHalconColorCyan = "cyan";
	const char* const kHalconColorMagenta = "magenta";
	const char* const kHalconColorYellow = "yellow";
	const char* const kHalconColorDimGray = "dim gray";
	const char* const kHalconColorGray = "gray";
	const char* const kHalconColorLightGray = "light gray";
	const char* const kHalconColorMediumSlateBlue = "medium slate blue";

	const char* const kHalconColorSpringGreen = "spring green";

    void write_location_image_ng(cv::Mat image,
                                 bool draw_rect,
                                 double x, double y, double phi, double l1, double l2,
                                 string ok_ng,
                                 const string& image_path)
    {
        int width = image.cols;
        int height = image.rows;
        cv::resize(image, image, cv::Size(width * 0.5, height * 0.5));
        cv::Mat result_image;
        cv::cvtColor(image, result_image, CV_GRAY2RGB);
        x *= 0.5;
        y *= 0.5;
        phi *= 0.5;
        l1 *= 0.5;
        l2 *= 0.5;

        float x1 = x + l1 * cos(phi);
        float y1 = y - l1 * sin(phi);
        float x2 = x - l1 * cos(phi);
        float y2 = y + l1 * sin(phi);
        float pi_2 = 3.14159f * 0.5;
        float x3 = x + l2 * cos(pi_2 + phi);
        float y3 = y - l2 * sin(pi_2 + phi);
        float x4 = x - l2 * cos(pi_2 + phi);
        float y4 = y + l2 * sin(pi_2 + phi);

        float c1_x = x1 + x3 - x;
        float c1_y = y1 + y3 - y;
        float c2_x = x2 + x3 - x;
        float c2_y = y2 + y3 - y;
        float c3_x = x2 + x4 - x;
        float c3_y = y2 + y4 - y;
        float c4_x = x1 + x4 - x;
        float c4_y = y1 + y4 - y;

        float verts[8];
        verts[0] = c1_x; verts[1] = c1_y;
        verts[2] = c2_x; verts[3] = c2_y;
        verts[4] = c3_x; verts[5] = c3_y;
        verts[6] = c4_x; verts[7] = c4_y;
        for (int i = 0; i < 4; ++i)
        {
            int idx_1 = i;
            int idx_2 = (i+1)%4;
            cv::line(result_image,
                     cv::Point(verts[idx_1 * 2], verts[idx_1 * 2 + 1]) ,
                     cv::Point(verts[idx_2 * 2], verts[idx_2 * 2 + 1]),
                     cv::Scalar(0, 0, 255));
        }

        if (ok_ng.length() > 0)
        {
            cv::putText(result_image, ok_ng.c_str(), cv::Point(10, 40), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        }

        cv::imwrite(image_path, result_image);
    }

    void write_location_image_ng(void* data, int width, int height,
                                 bool draw_rect,
                                 double x, double y, double phi, double l1, double l2,
                                 string ok_ng,
                                 const string& image_path)
    {
        cv::Mat image(height, width, CV_8UC1, data);
        write_location_image_ng(image, draw_rect, x, y, phi, l1, l2, ok_ng, image_path);
    }
    void write_frame_image_ng(void* data, int width, int height,
                                 bool disk_ok,
                                 double x, double y, double w, double h,
                                 bool left_found,
                                 double left_x, double left_y, double left_l1, double left_l2,
                                 bool right_found,
                                 double right_x, double right_y, double right_l1, double right_l2,
                                 const string& image_path)
    {
        cv::Mat image(height, width, CV_8UC1, data);
        write_frame_image_ng(image,
                             disk_ok,
                             x, y, w, h,
                             left_found,
                             left_x, left_y, left_l1, left_l2,
                             right_found,
                             right_x, right_y, right_l1, right_l2,
                             image_path);
    }
    void write_frame_image_ng(cv::Mat image,
                              bool disk_ok,
                              double x, double y, double w, double h,
                              bool left_found,
                              double left_x, double left_y, double left_l1, double left_l2,
                              bool right_found,
                              double right_x, double right_y, double right_l1, double right_l2,
                              const string& image_path)
    {
        int width = image.cols;
        int height = image.rows;
        cv::resize(image, image, cv::Size(width * 0.5, height * 0.5));
        cv::Mat result_image;
        cv::cvtColor(image, result_image, CV_GRAY2RGB);

        x *= 0.5; y *= 0.5; w *= 0.5; h *= 0.5;
        left_x *= 0.5; left_y *= 0.5; left_l1 *= 0.5; left_l2 *= 0.5;
        right_x *= 0.5; right_y *= 0.5; right_l1 *= 0.5; right_l2 *= 0.5;

        if (disk_ok)
        {
            cv::rectangle(result_image, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 255, 0), 2);
        }
        else
        {
            cv::rectangle(result_image, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 0, 255), 2);
        }

        if (left_found)
        {
            cv::rectangle(result_image,
                          cv::Point(left_x - left_l1, left_y - left_l2),
                          cv::Point(left_x + left_l1, left_y + left_l2),
                          cv::Scalar(0, 0, 255), 2);

        }
        else
        {
            cv::rectangle(result_image,
                          cv::Point(left_x - left_l1, left_y - left_l2),
                          cv::Point(left_x + left_l1, left_y + left_l2),
                          cv::Scalar(0, 255, 0), 2);

        }

        if (right_found)
        {
                cv::rectangle(result_image,
                              cv::Point(right_x - right_l1, right_y - right_l2),
                              cv::Point(right_x + right_l1, right_y + right_l2),
                              cv::Scalar(0, 0, 255), 2);
        }
        else
        {
            cv::rectangle(result_image,
                          cv::Point(right_x - right_l1, right_y - right_l2),
                          cv::Point(right_x + right_l1, right_y + right_l2),
                          cv::Scalar(0, 255, 0), 2);
        }
        cv::imwrite(image_path, result_image);
    }
    void write_reading_code_image_ng(cv::Mat image,
                                     bool draw_region_1, HRegion region_1,
                                     bool draw_region_2, HRegion region_2,
                                     bool draw_xld, HXLD xld,
                                     string tid, string sn,
                                     const string& image_path)
    {
        int width = image.cols;
        int height = image.rows;
        cv::resize(image, image, cv::Size(width * 0.5, height * 0.5));
        cv::Mat result_image;
        cv::cvtColor(image, result_image, CV_GRAY2RGB);

        if (draw_region_1 && region_1.IsInitialized())
        {
            HTuple rows, cols;
            region_1.GetRegionPolygon(5, &rows, &cols);
            int count = rows.Length();
            cv::Point* pts = new cv::Point[count];
            if (pts)
            {
                for (int i = 0; i < count; ++i)
                {
                    pts[i] = cv::Point((double)cols[i] * 0.5, (double)rows[i] * 0.5);
                }
                int npts = count;
                cv::polylines(result_image, &pts, &npts, 1, true, cv::Scalar(0, 0, 255), 5);
                delete[] pts;
            }
        }

        if (draw_region_2 && region_2.IsInitialized())
        {
            HTuple rows, cols;
            region_2.GetRegionPolygon(5, &rows, &cols);
            int count = rows.Length();
            cv::Point* pts = new cv::Point[count];
            if (pts)
            {
                for (int i = 0; i < count; ++i)
                {
                    pts[i] = cv::Point((double)cols[i] * 0.5, (double)rows[i] * 0.5);
                }
                int npts = count;
                cv::polylines(result_image, &pts, &npts, 1, true, cv::Scalar(0, 0, 255), 5);
                delete[] pts;
            }
        }

        if (draw_xld && xld.IsInitialized())
        {
            double r1, c1, r2, c2;
            xld.SmallestRectangle1Xld(&r1, &c1, &r2, &c2);
            cv::rectangle(result_image,
                          cv::Point(c1 * 0.5, r1 * 0.5),
                          cv::Point(c2 * 0.5, r2 * 0.5),
                          cv::Scalar(0, 0, 255), 5);
        }

        if (tid.length() > 0)
        {
            cv::putText(result_image, tid.c_str(), cv::Point(10, 40), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        }

        if (sn.length() > 0)
        {
            cv::putText(result_image, sn.c_str(), cv::Point(10, 90), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        }

        cv::imwrite(image_path, result_image);
    }

    void write_reading_code_image_ng(void* data, int width, int height,
                                 bool draw_region_1, HRegion region_1,
                                 bool draw_region_2, HRegion region_2,
                                 bool draw_xld, HXLD xld,
                                 string tid, string sn,
                                 const string& image_path)
    {
        cv::Mat image(height, width, CV_8UC1, data);
        write_reading_code_image_ng(image,
                                    draw_region_1, region_1,
                                    draw_region_2, region_2,
                                    draw_xld, xld,
                                    tid, sn,
                                    image_path);
    }

}
