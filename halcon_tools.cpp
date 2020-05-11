#include "halcon_tools.h"
#include <time.h>
#include <ssvision/ssvision>
#include <algorithm>
#include "baojitai.h"


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

    void read_tid_bar_code(void* data, int width, int height, const string& code_name, vector<string>& codes, vector<HRegion>& code_regions, int& duration_ms)
    {
        HImage img("byte", width, height, data);
        read_tid_bar_code(img, code_name, codes, code_regions, duration_ms);
    }

    void read_bar_code(void* data, int width, int height, const string& code_name, vector<string>& codes, vector<HRegion>& code_regions, int& duration_ms)
	{
		HImage img("byte", width, height, data);
        read_bar_code(img, code_name, codes, code_regions, duration_ms);
	}
    void read_bar_code_second(void* data, int width, int height, const string& code_name, vector<string>& codes, vector<HRegion>& code_regions, int& duration_ms)
    {
        HImage img("byte", width, height, data);
        read_bar_code_second(img, code_name, codes, code_regions, duration_ms);
    }
    void read_bar_code_thrid(void* data, int width, int height, const string& code_name, vector<string>& codes, vector<HRegion>& code_regions, int& duration_ms)
    {
        HImage img("byte", width, height, data);
        read_bar_code_thrid(img, code_name, codes, code_regions, duration_ms);
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

    void read_2d_code_special(const HImage& img, const string& code_name, vector<string>& codes, vector<HXLD>& code_regions, int& duration_ms)
       {
           clock_t clock_begin = clock();
		   HObject  ho_ModelRegion, ho_ImageReduced1;
		   HObject  ho_ImageScaleMax, ho_ImageEmphasize, ho_ImageMedian;
		   HObject  ho_Edges, ho_SelectedXLD, ho_SelectedContours, ho_ObjectSelected;
           HObject  ho_Region, ho_ImageReduced, ho_SymbolXLDs1, ho_RegionDilation;

		   // Local control variables
		   HTuple  hv_BarCodeHandle, hv_Width;
		   HTuple  hv_Height, hv_i, hv_NumberRegions, hv_ResultHandles1;
		   HTuple  hv_DecodedDataStrings1;
		   HDataCode2D datacode;


		   //Image Acquisition 01: Do something

		   CreateBarCodeModel(HTuple(), HTuple(), &hv_BarCodeHandle);
		   SetBarCodeParam(hv_BarCodeHandle, "check_char", "present");
		   datacode.CreateDataCode2dModel(code_name.c_str(), "default_parameters", "enhanced_recognition");

		   //*** 指定了一个大概的区域
//		   img.GetImageSize(&hv_Width, &hv_Height);
//		   GenRectangle1(&ho_ModelRegion, 100, 0, 2800, hv_Width);
//		   ReduceDomain(img, ho_ModelRegion, &ho_ImageReduced1);

		   //*** 图像增强
           ScaleImageMax(img, &ho_ImageScaleMax);
		   Emphasize(ho_ImageScaleMax, &ho_ImageEmphasize, 7, 7, 1);
		   MedianImage(ho_ImageEmphasize, &ho_ImageMedian, "circle", 1, "mirrored");

		   //***边缘检测`
		   EdgesSubPix(ho_ImageMedian, &ho_Edges, "canny", 1.2, 5, 70);

		   //***筛选轮廓
		   SelectShapeXld(ho_Edges, &ho_SelectedXLD, "area", "and", 10000, 30000);
		   SelectContoursXld(ho_SelectedXLD, &ho_SelectedContours, "closed", 0.5, 5, -0.5,
			   0.5);

		   GenRegionContourXld(ho_SelectedContours, &ho_Region, "filled");
           DilationRectangle1(ho_Region, &ho_RegionDilation, 10, 10);
           CountObj(ho_RegionDilation, &hv_NumberRegions);
		   {
			   HTuple end_val36 = hv_NumberRegions;
			   HTuple step_val36 = 1;
			   for (hv_i = 1; hv_i.Continue(end_val36, step_val36); hv_i += step_val36)
			   {
                   SelectObj(ho_RegionDilation, &ho_ObjectSelected, hv_i);
				   ReduceDomain(img, ho_ObjectSelected, &ho_ImageReduced);

				   HXLD ho_SymbolXLDs1 = datacode.FindDataCode2d(ho_ImageReduced, "stop_after_result_num",
					   2, &hv_ResultHandles1, &hv_DecodedDataStrings1); 
//				   HTuple t = hv_DecodedDataStrings1[hv_i];
                   codes.push_back(hv_DecodedDataStrings1.ToString().Text());
				   code_regions.push_back(ho_SymbolXLDs1);
			   }
		   }

//           HDataCode2D datacode;
//           datacode.CreateDataCode2dModel(code_name.c_str(), "default_parameters", "enhanced_recognition");
//           HTuple readed_strings;
//           HTuple result_handles;
//
//           Hlong Width = 0;
//           Hlong Height = 0;
//           img.GetImageSize(&Width, &Height);
//           HRegion get_rectangle_region;
//           get_rectangle_region.GenRectangle1(800, 0, 2000,Width);
//           HImage image_reduce =img.ReduceDomain(get_rectangle_region);
//           HImage ScaleImage = image_reduce.ScaleImageMax();
//           HImage image_emphasize = ScaleImage.Emphasize(7,7,1);
//           HImage image_median = image_emphasize.MedianImage("circle", 1, "mirrored");
//
//           HXLDCont Edgexld = image_median.EdgesSubPix("canny", 1.2 , 5 , 70);
//
//           //HXLDCont HXLDCont::SelectShapeXld(const HTuple& Features, const HString& Operation, const HTuple& Min, const HTuple& Max) const
//           //	select_shape(ConnectedRegions2, SelectedRegions1, ['area', 'rectangularity'], 'and', [99999, 0.5], [9999999, 1])
//           HTuple features;
//           features.Append("area");
//           HTuple min, max;
//           min.Append(10000);
//           max.Append(30000);
//           HXLDCont SelectedXLD = Edgexld.SelectShapeXld(features, "and", min, max);
//           HXLDCont SelectedContours = SelectedXLD.SelectContoursXld("closed", 0.5, 5, -0.5, 0.5);
//           HRegion Target_region = SelectedContours.GenRegionContourXld("filled");
//           Hlong Target_region_numbers = Target_region.CountObj();
//           for(int i = 0; i<Target_region_numbers; ++i)
//           {
//               HRegion Selected_Target_region = Target_region.SelectObj(i+1);
//               HImage Reduce_Target_region = img.ReduceDomain(Selected_Target_region);
//               HXLDCont xld = datacode.FindDataCode2d(Reduce_Target_region, "stop_after_result_num", 2, &result_handles, &readed_strings);
////               for (int i = 0; i < readed_strings.Length(); ++i)
////               {
//                   //HString* str = readed_strings.ToSArr();
//                   HTuple t = readed_strings[i];
//                   codes.push_back(t.ToString().Text());
////                   HXLD region = xld.SelectObj(i + 1);
//                   code_regions.push_back(xld);
////               }
//           }
	       datacode.Clear();
           clock_t clock_end = clock();
           duration_ms = (clock_end - clock_begin) * 1000 / CLOCKS_PER_SEC;
       }

    void read_2d_code_special(void* data, int width, int height, const string& code_name, vector<string>& codes, vector<HXLD>& code_regions, int& duration_ms)
    {
        HImage img("byte", width, height, data);
        read_2d_code_special(img, code_name, codes, code_regions, duration_ms);
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

    void read_tid_bar_code(const HImage& img, const string& code_name, vector<string>& codes, vector<HRegion>& code_regions, int& duration_ms)
    {
        clock_t clock_begin = clock();
        HBarCode barcode;
        HTuple readed_strings;
        barcode.CreateBarCodeModel(HTuple(), HTuple());
        HTuple GenParamNames;
        HTuple GenParamValues;
        GenParamNames.Append("start_stop_tolerance");
        GenParamNames.Append("check_char");
        GenParamNames.Append("element_size_max");
        GenParamValues.Append("true");
//        GenParamValues.Append(high);
        GenParamValues.Append(16);
        barcode.SetBarCodeParam(GenParamNames,GenParamValues);
        img.Emphasize(7,7,1);
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

    void read_bar_code(const HImage& img, const string& code_name, vector<string>& codes, vector<HRegion>& code_regions, int& duration_ms)
    {
        clock_t clock_begin = clock();
		HBarCode barcode;
        HTuple readed_strings;
		barcode.CreateBarCodeModel(HTuple(), HTuple());
        HTuple GenParamNames;
        HTuple GenParamValues;
        GenParamNames.Append("element_size_min");
//        GenParamNames.Append("check_char");
		GenParamNames.Append("element_size_max");
//        GenParamValues.Append("true");
        GenParamValues.Append(1.2);
        GenParamValues.Append(16);
        barcode.SetBarCodeParam(GenParamNames,GenParamValues);
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

    void read_bar_code_second(const HImage& img, const string& code_name, vector<string>& codes, vector<HRegion>& code_regions, int& duration_ms)
    {
        clock_t clock_begin = clock();
        HBarCode barcode;
        HTuple readed_strings;
        barcode.CreateBarCodeModel(HTuple(), HTuple());
        HTuple GenParamNames;
        HTuple GenParamValues;
        GenParamNames.Append("element_size_min");
//        GenParamNames.Append("check_char");
        GenParamNames.Append("element_size_max");
        GenParamNames.Append("majority_voting");
//        GenParamValues.Append("true");
        GenParamValues.Append(1.2);
        GenParamValues.Append(16);
        GenParamValues.Append("true");
        barcode.SetBarCodeParam(GenParamNames,GenParamValues);
         img.ScaleImageMax();
         img.Emphasize(7,7,1);
         img.MedianImage("circle", 1, "mirrored");
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

    void read_bar_code_thrid(const HImage& img, const string& code_name, vector<string>& codes, vector<HRegion>& code_regions, int& duration_ms)
    {
        clock_t clock_begin = clock();
        HBarCode barcode;
        HTuple readed_strings;
        barcode.CreateBarCodeModel(HTuple(), HTuple());
        HTuple GenParamNames;
        HTuple GenParamValues;
        GenParamNames.Append("element_size_variable");
//        GenParamNames.Append("check_char");
//		GenParamNames.Append("element_size_max");
        GenParamNames.Append("majority_voting");
//        GenParamValues.Append("true");
//        GenParamValues.Append(1.2);
//        GenParamValues.Append(16);
        GenParamValues.Append("true");
        barcode.SetBarCodeParam(GenParamNames,GenParamValues);
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

    void read_bar_code_special(const HImage& img, const string& code_name, vector<string>& codes, vector<HRegion>& code_regions, int& duration_ms)
    {
//        clock_t clock_begin = clock();
//        HBarCode barcode;
//        HTuple readed_strings;
//        barcode.CreateBarCodeModel(HTuple(), HTuple());

//        HObject   ho_SymbolXLDs, ho_ImageScaledrange;
//        // Local control variables
//        HTuple  hv_DataCodeHandle;
//        HTuple  hv_Width, hv_Height, hv_codenum, hv_ok, hv_ResultHandles;
//        HTuple  hv_DecodedDataStrings, hv_findcodenum, hv_maxm;
//        HTuple  hv_minGray, hv_maxGray, hv_Selected, hv_SelectedString;
//        HTuple  hv_aStringsLength;







//          GetImageSize(img, &hv_Width, &hv_Height);
//          hv_codenum = 2;
//          hv_ok = 0;
//          FindDataCode2d(img, &ho_SymbolXLDs, hv_DataCodeHandle, "stop_after_result_num",
//              hv_codenum, &hv_ResultHandles, &hv_DecodedDataStrings);
//          TupleLength(hv_DecodedDataStrings, &hv_findcodenum);
//          if (0 != (hv_findcodenum>=hv_codenum))
//          {
//            //加判斷條碼規則,滿足ok=1   codenum
//            hv_ok = 1;
//          }
//          else
//          {

//            hv_maxm = 180;

//            for (hv_minGray=50; hv_minGray<=150; hv_minGray+=5)
//            {
//              {
//              HTuple end_val21 = hv_minGray+11;
//              HTuple step_val21 = -10;
//              for (hv_maxGray=hv_maxm; hv_maxGray.Continue(end_val21, step_val21); hv_maxGray += step_val21)
//              {
//                scale_image_range(img, &ho_ImageScaledrange, hv_minGray, hv_maxGray);
//                FindDataCode2d(ho_ImageScaledrange, &ho_SymbolXLDs, hv_DataCodeHandle,
//                    "stop_after_result_num", hv_codenum, &hv_ResultHandles, &hv_DecodedDataStrings);
//                TupleLength(hv_DecodedDataStrings, &hv_findcodenum);
//                if (0 != (hv_findcodenum>=1))
//                {
//                  {
//                  HTuple end_val26 = hv_findcodenum-1;
//                  HTuple step_val26 = 1;
//                  for (hv_Selected=0; hv_Selected.Continue(end_val26, step_val26); hv_Selected += step_val26)
//                  {

//                    TupleSelect(hv_DecodedDataStrings, hv_Selected, &hv_SelectedString);
//                    TupleStrlen(hv_SelectedString, &hv_aStringsLength);

//                    if (0 != (hv_aStringsLength==23))
//                    {

//                      //加判斷條碼規則，滿足ok=1
//                      hv_ok = 1;
//                      break;
//                    }
//                    if (0 != (hv_ok==1))
//                    {
//                      break;
//                    }
//                  }
//                  }


//                }
//                if (0 != (hv_ok==1))
//                {
//                  break;
//                }

//              }
//              }
//              if (0 != (hv_ok==1))
//              {
//                break;
//              }

//            }
//          }

//        barcode.Clear();
//        clock_t clock_end = clock();
//        duration_ms = (clock_end - clock_begin) * 1000 / CLOCKS_PER_SEC;
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

//    void extract_rect(const Himage& img, int* x, int* y, double* phi, int* length1, int* length2, bool *find, int black_region_threshold)
//	{
//        char file_name[128];
//        memset(file_name, 0, 128);
//        sprintf(file_name, "halcon_tool.log");
//        std::ofstream out_log(file_name);
////       halcon_tools_logger_->log(Logger::kLogLevelInfo,"extract_start");
////       HTuple Width;
////      HTuple Height;
////       img.GetImageSize(& Width, & Height);
////       HRegion region;
////	   8线
////       region.GenRectangle1(291, 70, 1613, 2140);
//		//3线
////       region.GenRectangle1(2, 344, 944, 1777);
//		//4线
////	   region.GenRectangle1(124, 181, 978, 1605);
//	   //5线
////	   region.GenRectangle1(155, 400, 1045, 1825);
//       //2线
////       region.GenRectangle2(529, 734, 1.34965, 716, 453);
////       img.ReduceDomain(region);
////        out_log << "start" << endl;
////       HImage dupImgae = img.CopyImage();
////        HMetrologyModel MetrologyHandle = Baojitai::instance()->image_to_MetrologyHandle();
////        ClearMetrologyModel(MetrologyHandle);
//        HObject white_region;
//        Threshold(img,&white_region,128, 255);
//		if (!white_region.IsInitialized() && find)
//		{
//			*find = false;
//			return;
//		}
//        ClosingCircle(white_region, &white_region,  20);
////        white_region = white_region.ClosingCircle(20);
//        Connection(white_region,&white_region);
////		white_region = white_region.Connection();
//		HTuple row, col;
//        HTuple region_area;
//        AreaCenter(white_region,&region_area,&row, &col);
//		HTuple region_area_sorted_idx = region_area.TupleSortIndex();
//		int area_max_idx = region_area_sorted_idx[region_area_sorted_idx.Length() - 1];
//		int area_max = region_area[area_max_idx ];
//        HTuple width, height;
//        //int width = img.Width();
//        //int height = img.Height();
//		HalconCpp::GetImageSize(img, &width, &height);
//        if (find && area_max < width * height * 0.5 * 0.5)
//		{
//			*find = false;
//			return;
//		}

//        HObject roi_region;
//        SelectObj(white_region,&roi_region,area_max_idx + 1);

//        FillUp(roi_region,&roi_region);
//        ErosionCircle(roi_region,&roi_region,60);
//        HObject roi;
//        ReduceDomain(img,roi_region,&roi);
//        HObject roi_mean;
//        MeanImage(roi,&roi_mean,53, 53);
//        ErosionCircle(roi_region,&roi_region,30);
//        ReduceDomain(roi_mean,roi_region,&roi_mean);

//        if (black_region_threshold < 30)
//        {
//            black_region_threshold = 30;
//        }
//        else if (black_region_threshold > 230)
//        {
//            black_region_threshold = 230;
//        }

//        HObject black_region;
//        Threshold(roi_mean,&black_region,0, black_region_threshold);
//		if (!black_region.IsInitialized() && find)
//		{
//			*find = false;
//			return;
//		}
//        OpeningCircle(black_region,&black_region,60);
//        Connection(black_region,&black_region);
//        FillUp(black_region,&black_region);
//        HTuple black_region_area;
//        AreaCenter(black_region,&black_region_area,&row, &col);
//		HTuple black_region_sorted_idx = black_region_area.TupleSortIndex();
//		int black_region_area_max_idx = black_region_sorted_idx[black_region_sorted_idx.Length() - 1];
//        SelectObj(black_region,&black_region,black_region_area_max_idx + 1);
//        //增加卡尺
//		out_log << " extract_rect_old_model" << endl;

//        HTuple Row, Column;
//        HTuple area;
//        AreaCenter(black_region,&area,&Row, &Column);
//        HObject SelectedRegions_black_region;
//        SelectShape(black_region,&SelectedRegions_black_region,"area","and", area, 9999999);
//        HObject RegionTrans_black_region;
//        ShapeTrans(SelectedRegions_black_region,&RegionTrans_black_region,"rectangle2");
//        HObject Contours1;
//        GenContourRegionXld(RegionTrans_black_region,&Contours1,"border");
//        HTuple Row1, Column1, Phi, Length1, Length2;
//        HTuple PointOrder;
//        FitRectangle2ContourXld(Contours1,"regression", -1, 0, 0, 3, 2,& Row1,& Column1,& Phi,& Length1,& Length2,& PointOrder);
//////        shapeParam = [Row1, Column1, Phi, Length1, Length2];

//        HTuple shapeParam;
//        shapeParam.Clear();
//        shapeParam.Append(Row1);
//        shapeParam.Append(Column1);
//        shapeParam.Append(Phi);
//        shapeParam.Append(Length1);
//        shapeParam.Append(Length2);

//////		double r, c, l1, l2;
//////		double theta;

//////        halcontools::Metrology(dupImgae, shapeParam, & r, & c, & theta, & l1, & l2);

////        HMetrologyModel MetrologyHandle = Baojitai::instance()->image_to_MetrologyHandle();
//		HTuple MetrologyHandle;
//		CreateMetrologyModel(&MetrologyHandle);
//		SetMetrologyModelImageSize(MetrologyHandle,width, height);
//////        out_log <<MetrologyHandle   << endl;


//        HTuple hv_Index;
//        AddMetrologyObjectGeneric(MetrologyHandle, "rectangle2", shapeParam, 20, 5, 1, 30, HTuple(), HTuple(), &hv_Index);
//		SetMetrologyObjectParam(MetrologyHandle,"all", "measure_length1", 60);
//		SetMetrologyObjectParam(MetrologyHandle,"all", "measure_interpolation", "bicubic");
//		SetMetrologyObjectParam(MetrologyHandle,"all", "measure_select", "all");
//		SetMetrologyObjectParam(MetrologyHandle,"all", "min_score", 0.65);

//        ApplyMetrologyModel(img, MetrologyHandle);
		
//		HObject Contours;
//		HTuple Parameter;
//		HObject Contour;
//		GetMetrologyObjectMeasures(&Contours,MetrologyHandle, "all", "all", &Row, &Column);
//		GetMetrologyObjectResult(MetrologyHandle, "all", "all", "result_type", "all_param", &Parameter);
//		GetMetrologyObjectResultContour(&Contour, MetrologyHandle, "all", "all", 1.5);



//		HTuple PointOrder1;
//		HTuple r, c, l1, l2;
//		HTuple theta;
//		FitRectangle2ContourXld(Contour,"regression", -1, 0, 0, 3, 2, &r, &c, &theta, &l1, &l2, &PointOrder1);
////        black_region.SmallestRectangle2(&r, &c, &theta, &l1, &l2);
//		out_log << " extract_rect_new_model" << endl;
//        ClearMetrologyModel(MetrologyHandle);
////        out_log <<MetrologyHandle   << endl;
////        Baojitai::instance()->set_image_to_MetrologyHandle(MetrologyHandle);

//		if (x)
//            *x = c.D();
//		if (y)
//			*y = r.D();
//		if (phi)
//			*phi = theta.D();
//		if (length1)
//			*length1 = l1.D();
//		if (length2)
//			*length2 = l2.D();
//		if (find)
//            *find = true;
////        halcon_tools_logger_->log(Logger::kLogLevelInfo,"extract_end");
//        out_log <<" extract_rect_end"   << endl;
////        ClearMetrologyModel(MetrologyHandle);
////		dupImgae.Clear();
////		HTuple gao, kuan;
////		img.GetImageSize(&gao
////			, &kuan);
////		out_log << gao.ToString() << endl;
////		out_log << kuan.ToString() << endl;
//	}

    //1期混合
        void extract_rect(const HImage& img, int* x, int* y, double* phi, int* length1, int* length2, bool *find, int black_region_threshold)
//        {
//        HRegion white_region = img.Threshold(128, 255);
//        if (!white_region.IsInitialized() && find)
//        {
//            *find = false;
//            return;
//        }
//        white_region = white_region.ClosingCircle(20);
//        white_region = white_region.Connection();
//        HTuple row, col;
//        HTuple region_area = white_region.AreaCenter(&row, &col);
//        HTuple region_area_sorted_idx = region_area.TupleSortIndex();
//        int area_max_idx = region_area_sorted_idx[region_area_sorted_idx.Length() - 1];
//        int area_max = region_area[area_max_idx ];
//        HTuple width, height;
//        //int width = img.Width();
//        //int height = img.Height();
//        HalconCpp::GetImageSize(img, &width, &height);
//        if (find && area_max < width * height * 0.5 * 0.5)
//        {
//            *find = false;
//            return;
//        }

//        HRegion roi_region = white_region.SelectObj(area_max_idx + 1);
//        roi_region = roi_region.FillUp();
//        roi_region = roi_region.ErosionCircle(60);
//        HImage roi = img.ReduceDomain(roi_region);
//        HImage roi_mean = roi.MeanImage(53, 53);
//        roi_region = roi_region.ErosionCircle(30);
//        roi_mean = roi_mean.ReduceDomain(roi_region);

//        if (black_region_threshold < 30)
//        {
//            black_region_threshold = 30;
//        }
//        else if (black_region_threshold > 230)
//        {
//            black_region_threshold = 230;
//        }

//        HRegion black_region = roi_mean.Threshold(0, black_region_threshold);
//        if (!black_region.IsInitialized() && find)
//        {
//            *find = false;
//            return;
//        }
//        black_region = black_region.OpeningCircle(60);
//        black_region = black_region.Connection();
//        black_region = black_region.FillUp();
//        HTuple black_region_area = black_region.AreaCenter(&row, &col);
//        HTuple black_region_sorted_idx = black_region_area.TupleSortIndex();
//        int black_region_area_max_idx = black_region_sorted_idx[black_region_sorted_idx.Length() - 1];
//        black_region = black_region.SelectObj(black_region_area_max_idx + 1);

//        double r, c,  l1, l2;
//        double theta;

////        HString point_order;
////        HXLDCont black_xld_cont = black_region.GenContourRegionXld("border");
////		black_xld_cont.FitRectangle2ContourXld("regression", -1, 0, 0, 3, 2, &r, &c, &theta, &l1, &l2, &point_order);

//        black_region.SmallestRectangle2(&r, &c, &theta, &l1, &l2);

//        if (x)
//            *x = c;
//        if (y)
//            *y = r;
//        if (phi)
//            *phi = theta;
//        if (length1)
//            *length1 = l1;
//        if (length2)
//            *length2 = l2;
//        if (find)
//            *find = true;
//    }
        {
            char file_name[128];
            memset(file_name, 0, 128);
            sprintf(file_name, "halcon_tool.log");
            std::ofstream out_log(file_name);
    //       halcon_tools_logger_->log(Logger::kLogLevelInfo,"extract_start");
    //       HTuple Width;
    //      HTuple Height;
    //       img.GetImageSize(& Width, & Height);
           HRegion region;
    //	   8线
    //       region.GenRectangle1(l, 70, 1613, 2140);
            //3线
    //       region.GenRectangle1(2, 344, 944, 1777);
            //4线
    //	   region.GenRectangle1(124, 181, 978, 1605);
           //5线
           region.GenRectangle1(155, 400, 1045, 1825);
           //2线
    //       region.GenRectangle2(529, 734, 1.34965, 716, 453);
          // 6线
          //   region.GenRectangle2(541.858, 926.5, 178.67, 711.192, 465.658);

           HImage img_reduce = img.ReduceDomain(region);
    //        out_log << "start" << endl;
    //       HImage dupImgae = img.CopyImage();
    //        HMetrologyModel MetrologyHandle = Baojitai::instance()->image_to_MetrologyHandle();
    //        ClearMetrologyModel(MetrologyHandle);

//           HRegion white_region = img_reduce.Threshold(128, 255);
//           if (!white_region.IsInitialized() && find)
//           {
//               *find = false;
//               return;
//           }
//           white_region = white_region.ClosingCircle(20);
//           white_region = white_region.Connection();
//           HTuple row, col;
//           HTuple region_area = white_region.AreaCenter(&row, &col);
//           HTuple region_area_sorted_idx = region_area.TupleSortIndex();
//           int area_max_idx = region_area_sorted_idx[region_area_sorted_idx.Length() - 1];
//           int area_max = region_area[area_max_idx ];

//           out_log<<area_max<<endl;

//           HTuple width, height;
//           //int width = img.Width();
//           //int height = img.Height();
//           HalconCpp::GetImageSize(img_reduce, &width, &height);

//           out_log <<width.D() << endl;
//           out_log << height.D() << endl;

//           if (find && area_max < width * height * 0.5 * 0.5)
//           {
//               *find = false;
//               return;
//           }

//           HRegion roi_region = white_region.SelectObj(area_max_idx + 1);
//           roi_region = roi_region.FillUp();
//           roi_region = roi_region.ErosionCircle(60);
//           HImage roi = img.ReduceDomain(roi_region);
//           HImage roi_mean = roi.MeanImage(53, 53);
//           roi_region = roi_region.ErosionCircle(30);
//           roi_mean = roi_mean.ReduceDomain(roi_region);



            HRegion black_region = img_reduce.Threshold(0, black_region_threshold);
            out_log<<black_region_threshold<<endl;
            if (!black_region.IsInitialized() && find)
            {
                *find = false;
                return;
            }

            black_region = black_region.OpeningCircle(30);
            black_region = black_region.Connection();
            black_region = black_region.FillUp();

			HTuple row, col;

                  /*HRegion region_opening = region_SelectShape.OpeningRectangle1(100, 20);*/
            HTuple black_region_area = black_region.AreaCenter(&row, &col);
//            HTuple black_region_sorted_idx = black_region_area.TupleSortIndex();
//            int black_region_area_max_idx = black_region_sorted_idx[black_region_sorted_idx.Length() - 1];
//            black_region = black_region.SelectObj(black_region_area_max_idx + 1);

            HTuple black_region_sorted_idx = black_region_area.TupleSortIndex();
            double black_region_area_max_idx = black_region_sorted_idx[black_region_sorted_idx.Length() - 1];
            double black_region_area_max = black_region_area[black_region_area_max_idx];
            black_region = black_region.SelectShape("area", "and", black_region_area_max, 9999999);

            out_log<<black_region_area_max<<endl;

            HTuple phi_noise = black_region.OrientationRegion();
            double phi_noise_ = phi_noise.D();

            HRegion Rectangle;
            Rectangle.GenRectangle2(200, 200, phi_noise_, 100, 50);
            black_region = black_region.Opening(Rectangle);

            double r, c, l1, l2;
            double theta;

            black_region.SmallestRectangle2(&r, &c, &theta, &l1, &l2);


                    out_log << r << endl;
                    out_log << c << endl;
                    out_log <<l1 << endl;
                    out_log << l2 << endl;
                    out_log << theta << endl;

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

//            out_log <<" extract_rect_end"   << endl;

        }

        //纯1
//    void extract_rect(const HImage& img, int* x, int* y, double* phi, int* length1, int* length2, bool *find, int black_region_threshold)
//    {
//        
//       //HTuple Width;
//       //HTuple Height;
//       //img.GetImageSize(& Width, & Height);
//       HRegion region;
////	   //8线
//////     region.GenRectangle1(291, 70, 1613, 2140);
////		   //		//3线
////		   ////       region.GenRectangle1(2, 344, 944, 1777);
////		   //		//4线
////		   ////	   region.GenRectangle1(124, 181, 978, 1605);
////		   //	   //5线
//	   region.GenRectangle1(153.111, 407.5, 1039.32, 1803.5);
////		   //       //2线
////		   ////       region.GenRectangle2(529, 734, 1.34965, 716, 453);
//	   HImage img_reduce = img.ReduceDomain(region);
////        out_log << "start" << endl;
////       HImage dupImgae = img.CopyImage();
//   //   HObject  ho_ROI_0, ho_ImageReduced;
//   //   HObject  ho_PowImage, ho_ImageScaled, ho_Region, ho_RegionFillUp;
//   //   HObject  ho_ConnectedRegions, ho_SelectedRegions, ho_Rectangle;
//   //   HObject  ho_RegionOpening;
//
//   //   // Local control variables
//   //   HTuple  hv_Width, hv_Height;
//   //   HTuple  hv_Min, hv_Max, hv_Range, hv_Area, hv_Row, hv_Column;
//   //   HTuple  hv_Phi, hv_Row1, hv_Column1, hv_Phi1, hv_Length1;
//   //   HTuple  hv_Length2;
//
//   //   GetImageSize(img, &hv_Width, &hv_Height);
//   //   GenRectangle1(&ho_ROI_0, 153.111, 407.5, 1039.32, 1803.5);
//   //   //gen_rectangle2 (ROI_0, 463, 1076.5, rad(-1.4688), 702.231, 444.052)
//   //   //gen_rectangle1 (ROI_0, 287.05, 35.95, 1615.45, 2166.25)
//   //   //gen_rectangle2 (ROI_0, 465.672, 1034.5, rad(176.35), 728.979, 433.912)
//   //   //gen_rectangle1 (ROI_0, 19.8984, 317.189, 938.484, 1787.13)
//   //   ReduceDomain(img, ho_ROI_0, &ho_ImageReduced);
//
//   //   MinMaxGray(ho_ROI_0, ho_ImageReduced, 0, &hv_Min, &hv_Max, &hv_Range);
//   //   PowImage(ho_ImageReduced, &ho_PowImage, 2);
//
//   //   ScaleImage(ho_PowImage, &ho_ImageScaled, 1 / hv_Max, 0);
//   //   Threshold(ho_ImageScaled, &ho_Region, 0, black_region_threshold);
//	  //
//   //   FillUp(ho_Region, &ho_RegionFillUp);
//   //   Connection(ho_RegionFillUp, &ho_ConnectedRegions);
//   //   AreaCenter(ho_ConnectedRegions, &hv_Area, &hv_Row, &hv_Column);
//
//	  //
//   //   SelectShape(ho_ConnectedRegions, &ho_SelectedRegions, "area", "and", hv_Area.TupleMax(),
//   //       9999999);
//   //   OrientationRegion(ho_SelectedRegions, &hv_Phi);
//   //   GenRectangle2(&ho_Rectangle, 960, 540, hv_Phi, 100, 50);
//   //   Opening(ho_SelectedRegions, ho_Rectangle, &ho_RegionOpening);
//   //   SmallestRectangle2(ho_RegionOpening, &hv_Row1, &hv_Column1, &hv_Phi1, &hv_Length1,
//   //       &hv_Length2);
//	  //if (x)
//		 // *x = hv_Row1.D();
//	  //if (y)
//		 // *y = hv_Column1.D();
//	  //if (phi)
//		 // *phi = hv_Phi1.D();
//	  //if (length1)
//		 // *length1 = hv_Length1.D();
//	  //if (length2)
//		 // *length2 = hv_Length2.D();
//	  //if (find)
//		 // *find = true;
//
//      double Min,Max,Range;
//	  region.MinMaxGray(img_reduce, 0, &Min, &Max, &Range);
//	  HImage Pow_img = img_reduce.PowImage(2);
//	  HImage Scale_img = Pow_img.ScaleImage(1 / Max, 0);
//	   HRegion region_Threshold = img_reduce.Threshold(0, black_region_threshold);
//      HRegion region_FillUp = region_Threshold.FillUp();
//      HRegion region_Connection= region_FillUp.Connection();
//      HTuple Row,Column;
//      HTuple region_area = region_Connection.AreaCenter(& Row, &Column);
//      HTuple region_area_sorted_idx = region_area.TupleSortIndex();
//      double area_max_idx = region_area_sorted_idx[region_area_sorted_idx.Length() - 1];
//	  double area_max = region_area[area_max_idx];
//	  HTuple width, height;
//	  HalconCpp::GetImageSize(img_reduce, &width, &height);
//      if (find && area_max < width * height * 0.5 * 0.5)
//       {
//          *find = false;
//          return;
//       }
//	  HRegion region_SelectShape = region_Connection.SelectShape("area","and", area_max, 9999999);
//	
//      HTuple phi_noise = region_SelectShape.OrientationRegion();
//	  double phi_noise_ = phi_noise.D();
//
//	  HRegion Rectangle;
//	  Rectangle.GenRectangle2(200, 200, phi_noise_, 100, 50);
//      HRegion region_opening = region_SelectShape.Opening(Rectangle);
//	  /*HRegion region_opening = region_SelectShape.OpeningRectangle1(100, 20);*/
//      double r, c, l1, l2;
//      double theta;
//      region_opening.SmallestRectangle2(&r, &c, &theta, &l1, &l2);
//
//                if (x)
//					*x = r;
//                if (y)
//					*y = c;
//                if (phi)
//					*phi = theta;
//                if (length1)
//					*length1 = l1;
//                if (length2)
//					*length2 = l2;
//                if (find)
//                    *find = true;
//      
//    }

//    void extract_rect(const HImage& img, int* x, int* y, double* phi, int* length1, int* length2, bool *find, int black_region_threshold)
//    {
//        char file_name[128];
//        memset(file_name, 0, 128);
//        sprintf(file_name, "halcon_tool.log");
//        std::ofstream out_log(file_name);
//       HTuple Width;
//       HTuple Height;
//       img.GetImageSize(& Width, & Height);
//       HRegion region;
//        //3线
////       region.GenRectangle1(2, 344, 944, 1777);
//        //4线
//	   region.GenRectangle1(124, 181, 978, 1605);
//      img.ReduceDomain(region);
//
//	  HRegion ho_ImageReduced = img.Threshold(0, black_region_threshold);
//      HRegion ho_ConnectedRegions = ho_ImageReduced.Connection();
//      HRegion ho_SelectedRegions= ho_ConnectedRegions.SelectShape("area", "and", 250000,
//          9999999);
//      if (!ho_SelectedRegions.IsInitialized() && find)
//              {
//                  *find = false;
//                  return;
//              }
//      HRegion ho_RegionFillUp = ho_SelectedRegions.FillUp();
//
//      HRegion ho_RegionOpening1 = ho_RegionFillUp.OpeningRectangle1(300, 3);
//      //partition_rectangle (RegionClosing1, Partitioned, Width, Width)
//
//      HRegion ho_ConnectedRegions1 = ho_RegionOpening1.Connection();
//      HTuple hv_Row3,hv_Column3;
//      HTuple hv_Area = ho_ConnectedRegions1.AreaCenter(&hv_Row3, &hv_Column3);
//	  HTuple region_area_sorted_idx = hv_Area.TupleSortIndex();
//	  		int area_max_idx = region_area_sorted_idx[region_area_sorted_idx.Length() - 1];
//			int area_max = hv_Area[area_max_idx];
//      //HTuple ho_RegionClosing = ho_ConnectedRegions1.ClosingRectangle1(Width, Height);
//
//			HRegion ho_SelectedRegions1 = ho_ConnectedRegions1.SelectShape("area", "and", area_max,
//          9999999);
//            if (!ho_SelectedRegions1.IsInitialized() && find)
//                    {
//                        *find = false;
//                        return;
//                    }
//      HRegion ho_RegionTrans = ho_SelectedRegions1.ShapeTrans("rectangle2");
//
//
//      HXLDCont ho_Contours1 = ho_RegionTrans.GenContourRegionXld("border");
// //     ho_Contours1.FitRectangle2ContourXld("regression", -1, 0, 0, 3, 2, &hv_Row1,
// //         &hv_Column1, &hv_Phi, &hv_Length1, &hv_Length2, &hv_PointOrder);
//
//
//                HTuple PointOrder1;
//                HTuple r, c, l1, l2;
//                HTuple theta;
//
//                ho_Contours1.FitRectangle2ContourXld("regression", -1, 0, 0, 3, 2, &r,
//                    &c, &theta, &l1, &l2, &PointOrder1);
////                FitRectangle2ContourXld(Contour,"regression", -1, 0, 0, 3, 2, &r, &c, &theta, &l1, &l2, &PointOrder1);
////               black_region.SmallestRectangle2(&r, &c, &theta, &l1, &l2);
////                out_log << " extract_rect_new_model" << endl;
////                out_log <<width.ToString()   << endl;
////                out_log <<height.ToString()   << endl;
////                ClearMetrologyModel(MetrologyHandle);
////        //        out_log <<MetrologyHandle   << endl;
////        //        Baojitai::instance()->set_image_to_MetrologyHandle(MetrologyHandle);
////                        HTuple gao, kuan;
////                        img.GetImageSize(&gao
////                            , &kuan);
////                        out_log << gao.ToString() << endl;
////                        out_log << kuan.ToString() << endl;
//                if (x)
//                    *x = c.D();
//                if (y)
//                    *y = r.D();
//                if (phi)
//                    *phi = theta.D();
//                if (length1)
//                    *length1 = l1.D();
//                if (length2)
//                    *length2 = l2.D();
//                if (find)
//                    *find = true;
//                out_log <<x   << endl;
//                out_log <<y   << endl;
//                out_log <<phi   << endl;
//                out_log <<length1   << endl;
//                out_log <<length2   << endl;
//        //        halcon_tools_logger_->log(Logger::kLogLevelInfo,"extract_end");
//                out_log <<" extract_rect_end"   << endl;
//        //        ClearMetrologyModel(MetrologyHandle);
//        //		dupImgae.Clear();
//        //		HTuple gao, kuan;
//        //		img.GetImageSize(&gao
//        //			, &kuan);
//        //		out_log << gao.ToString() << endl;
//        //		out_log << kuan.ToString() << endl;
//    }

    void scale_image_range (HObject ho_Image, HObject *ho_ImageScaled, HTuple hv_Min,
        HTuple hv_Max)
    {

      // Local iconic variables
      HObject  ho_SelectedChannel, ho_LowerRegion, ho_UpperRegion;

      // Local control variables
      HTuple  hv_LowerLimit, hv_UpperLimit, hv_Mult;
      HTuple  hv_Add, hv_Channels, hv_Index, hv_MinGray, hv_MaxGray;
      HTuple  hv_Range;

      //Convenience procedure to scale the gray values of the
      //input image Image from the interval [Min,Max]
      //to the interval [0,255] (default).
      //Gray values < 0 or > 255 (after scaling) are clipped.
      //
      //If the image shall be scaled to an interval different from [0,255],
      //this can be achieved by passing tuples with 2 values [From, To]
      //as Min and Max.
      //Example:
      //scale_image_range(Image:ImageScaled:[100,50],[200,250])
      //maps the gray values of Image from the interval [100,200] to [50,250].
      //All other gray values will be clipped.
      //
      //input parameters:
      //Image: the input image
      //Min: the minimum gray value which will be mapped to 0
      //     If a tuple with two values is given, the first value will
      //     be mapped to the second value.
      //Max: The maximum gray value which will be mapped to 255
      //     If a tuple with two values is given, the first value will
      //     be mapped to the second value.
      //
      //output parameter:
      //ImageScale: the resulting scaled image
      //
      if (0 != ((hv_Min.TupleLength())==2))
      {
        hv_LowerLimit = ((const HTuple&)hv_Min)[1];
        hv_Min = ((const HTuple&)hv_Min)[0];
      }
      else
      {
        hv_LowerLimit = 0.0;
      }
      if (0 != ((hv_Max.TupleLength())==2))
      {
        hv_UpperLimit = ((const HTuple&)hv_Max)[1];
        hv_Max = ((const HTuple&)hv_Max)[0];
      }
      else
      {
        hv_UpperLimit = 255.0;
      }
      //
      //Calculate scaling parameters
      hv_Mult = ((hv_UpperLimit-hv_LowerLimit).TupleReal())/(hv_Max-hv_Min);
      hv_Add = ((-hv_Mult)*hv_Min)+hv_LowerLimit;
      //
      //Scale image
      ScaleImage(ho_Image, &ho_Image, hv_Mult, hv_Add);
      //
      //Clip gray values if necessary
      //This must be done for each channel separately
      CountChannels(ho_Image, &hv_Channels);
      {
      HTuple end_val48 = hv_Channels;
      HTuple step_val48 = 1;
      for (hv_Index=1; hv_Index.Continue(end_val48, step_val48); hv_Index += step_val48)
      {
        AccessChannel(ho_Image, &ho_SelectedChannel, hv_Index);
        MinMaxGray(ho_SelectedChannel, ho_SelectedChannel, 0, &hv_MinGray, &hv_MaxGray,
            &hv_Range);
        Threshold(ho_SelectedChannel, &ho_LowerRegion, (hv_MinGray.TupleConcat(hv_LowerLimit)).TupleMin(),
            hv_LowerLimit);
        Threshold(ho_SelectedChannel, &ho_UpperRegion, hv_UpperLimit, (hv_UpperLimit.TupleConcat(hv_MaxGray)).TupleMax());
        PaintRegion(ho_LowerRegion, ho_SelectedChannel, &ho_SelectedChannel, hv_LowerLimit,
            "fill");
        PaintRegion(ho_UpperRegion, ho_SelectedChannel, &ho_SelectedChannel, hv_UpperLimit,
            "fill");
        if (0 != (hv_Index==1))
        {
          CopyObj(ho_SelectedChannel, &(*ho_ImageScaled), 1, 1);
        }
        else
        {
          AppendChannel((*ho_ImageScaled), ho_SelectedChannel, &(*ho_ImageScaled));
        }
      }
      }
      return;
    }

    void Metrology(const HImage& imgcopy, HTuple &shapeParam, double r, double c, double theta, double l1, double l2)
    {
        HMetrologyModel MetrologyHandle;
        MetrologyHandle.CreateMetrologyModel();
		HTuple width;
		HTuple height;
        MetrologyHandle.SetMetrologyModelImageSize(width,height);
//        out_log <<MetrologyHandle   << endl;
//        Hlong Index = MetrologyHandle.AddMetrologyObjectGeneric("rectangle2", shapeParam, 20, 5, 1, 30,y , );

        HTuple hv_Index;
        AddMetrologyObjectGeneric(MetrologyHandle, "rectangle2", shapeParam, 20, 5, 1, 30, HTuple(), HTuple(), &hv_Index);
        MetrologyHandle.SetMetrologyObjectParam("all", "measure_length1",30);
        MetrologyHandle.SetMetrologyObjectParam("all", "measure_interpolation","bicubic");
        MetrologyHandle.SetMetrologyObjectParam("all", "measure_select","all");
        MetrologyHandle.SetMetrologyObjectParam("all", "min_score",0.65);

        MetrologyHandle.ApplyMetrologyModel(imgcopy);

//        HXLDCont Contours = MetrologyHandle.GetMetrologyObjectMeasures("all", "all", &Row, &Column);
//        HTuple  Parameter = MetrologyHandle.GetMetrologyObjectResult("all", "all", "result_type", "all_param");
        HXLDCont Contour = MetrologyHandle.GetMetrologyObjectResultContour("all", "all", 1.5);


//        double r, c,  l1, l2;
//        double theta;

//        HString point_order;
//        HXLDCont black_xld_cont = black_region.GenContourRegionXld("border");
//		black_xld_cont.FitRectangle2ContourXld("regression", -1, 0, 0, 3, 2, &r, &c, &theta, &l1, &l2, &point_order);
		HString PointOrder1;
       Contour.FitRectangle2ContourXld("regression", -1, 0, 0, 3, 2, &r, &c, &theta, &l1, &l2, &PointOrder1);
//       black_region.SmallestRectangle2(&r, &c, &theta, &l1, &l2);
        ClearMetrologyModel(MetrologyHandle);
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
