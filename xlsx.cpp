#include "xlsx.h"

xlsx::xlsx()
{

}
string xlsx(QDateTime &Datetime)
{
    QXlsx::Document xlsx("数据采集表.xlsx");/*打开一个book1的文件*/
    //第一排
//    QXlsx::Format format1;/*设置该单元的样式*/
//    format1.setFontColor(QColor(Qt::black));/*文字为黑色*/
//    //    format1.setPatternBackgroundColor(QColor(152,251,152));/*背景颜色*/
//    format1.setFontSize(16);/*设置字体大小*/
//    format1.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*横向居中*/
//    //    format1.setBorderStyle(QXlsx::Format::BorderDashDotDot);/*边框样式*/
//    xlsx.write("A1:I1", "设备信息采集表!", format1);/*写入文字，应该刚才设置的样式*/
//    //    QXlsx::Format format2;/
//    //    format2.setFontBold(true);/*设置加粗*/
//    //    format2.setFontColor(QColor(Qt::red));/*文字为黑色*/
//    ////    format1.setPatternBackgroundColor(QColor(152,251,152));/*背景颜色*/
//    //    format2.setFontSize(11);/*设置字体大小*/
//    //    format2.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*横向居中*/
//    ////    format2.setBorderStyle(QXlsx::Format::BorderDashDotDot);/*边框样式*/
//    //    xlsx.write("L1", "PLC实际使用地址", format2);/*写入文字，应该刚才设置的样式*/

        //第二排
//    QXlsx::Format format3;/*重新设置另一个单元的样式*/
//    format3.setFontBold(true);/*设置加粗*/
//    //    format2.setFontUnderline(QXlsx::Format::FontUnderlineDouble);/*下双划线*/
//    //    format2.setFillPattern(QXlsx::Format::PatternLightUp);/*填充方式*/
//    format3.setFontSize(14);/*设置字体大小*/
//    format3.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*横向居中*/
//    xlsx.write("A2", "序號", format3);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("B2:C2", "項目", format3);
//    xlsx.write("D2", "單位", format3);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("E2", "PLC地址分配", format3);
//    xlsx.write("F2", "PLC數據類型", format3);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("G2", "統計週期", format3);
//    xlsx.write("H2", "更新頻率", format3);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("I2", "可讀寫性", format3);

        //第三排
//    QXlsx::Format format4;/*设置该单元的样式*/
//    format4.setFontColor(QColor(Qt::red));/*文字为红色*/
//    format4.setFontSize(12);
//    format4.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*横向居中*/
    QXlsx::Format format5;
    format5.setFontColor(QColor(Qt::black));/*文字为黑色*/
    format5.setFontSize(12);
    format5.setHorizontalAlignment(QXlsx::Format::AlignHCenter);/*横向居中*/
//    xlsx.write("A3", "1", format4);
//    xlsx.write("B3:C3", "設備ID", format4);
//    xlsx.write("D3", "/", format5);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("E3", "D5000-D5003", format5);
//    xlsx.write("F3", "/", format5);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("G3", "/", format5);
//    xlsx.write("H3", "每班一次", format5);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("I3", "讀寫", format5);
//    xlsx.write("J3", "设置，开机清零时间", format5);

        //第四排
//    xlsx.write("A4", "2", format4);
//    xlsx.write("B4:C4", "設備白班開班時間", format4);
    int day_hour_value;
    int day_minute_value;
    plc_utltype_->GetDevice("D5004", day_hour_value);
    plc_utltype_->GetDevice("D5005", day_minute_value);
    xlsx.write("D4", day_hour_value+"H"+day_minute_value+"MIN", format5);/*写入文字，应该刚才设置的样式*/
    xlsx.write("E4", "D5004-D5005", format5);
//    xlsx.write("F4", "/", format5);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("G4", "/", format5);
//    xlsx.write("H4", "每班一次", format5);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("I4", "讀寫", format5);
//    xlsx.write("J4", "设置，开机清零时间", format5);

        //第五排
//    xlsx.write("A5", "3", format4);
//    xlsx.write("B5:C5", "設備晚班開班時間", format4);
    int night_hour_value;
    int night_minute_value;
    plc_utltype_->GetDevice("D5006", night_hour_value);
    plc_utltype_->GetDevice("D5007", night_minute_value);
    xlsx.write("D5", night_hour_value+"H"+night_minute_value+"MIN", format5);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("E5", "D5000-D5003", format5);
//    xlsx.write("F5", "/", format5);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("G5", "/", format5);
//    xlsx.write("H5", "每班一次", format5);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("I5", "讀寫", format5);
//    xlsx.write("J5", "设置，开机清零时间", format5);

    //第六排
//    xlsx.write("A6", "3", format4);
//    xlsx.write("B6:C6", "設備狀態(1待機、2工作、3報警等)", format4);
    int status;
    plc_utltype_->GetDevice("D5010", status);
    switch (status)
    {
    case 1 :
        xlsx.write("D6","待機", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 2 :
        xlsx.write("D6","工作", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 3 :
        xlsx.write("D6","報警", format5);/*写入文字，应该刚才设置的样式*/
        break;
    }
//    xlsx.write("E6", "D5010", format5);
//    xlsx.write("F6", "16位", format5);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("G6", "實時", format5);
//    xlsx.write("H6", "實時", format5);/*写入文字，应该刚才设置的样式*/
//    xlsx.write("I6", "只讀", format5);

    //第七排
    int currunt_code;
    plc_utltype_->GetDevice("D5011", currunt_code);
    switch (status)
    {
    case 110 :
        xlsx.write("D6","视觉定位反馈超时(M20，M21)", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 111 :
        xlsx.write("D6","视觉扫TID反馈超时(M60)", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 112 :
        xlsx.write("D6","视觉没set M63", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 122 :
        xlsx.write("D6","安全门被打开", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 225 :
        xlsx.write("D6","急停被按下", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 271 :
        xlsx.write("D6","掉真空报警", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 275 :
        xlsx.write("D6","FID刷卡失败，设备已暂停，请处理！", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 31 :
        xlsx.write("D6","机器人报警", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 43 :
        xlsx.write("D6","皮带异常", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 51 :
        xlsx.write("D6","支架转盘拍照NG", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 53 :
        xlsx.write("D6","支架挡杆拍照NG", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 601 :
        xlsx.write("D6","支架异常总数", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 380 :
        xlsx.write("D6","支架上有产品，请清理", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 381 :
        xlsx.write("D6","支架转盘偏位", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 382 :
        xlsx.write("D6","支架背靠未到位", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 653 :
        xlsx.write("D6","流水板气缸上限傳感器異常或流水板卡阻", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 654 :
        xlsx.write("D6","機器人放料完成信號異常", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 658 :
        xlsx.write("D6","升降機進料口傳感器X15異常", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 659 :
        xlsx.write("D6","升降线极限位傳感器X16異常", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 660 :
        xlsx.write("D6","机器人原点信号异常或流水板卡阻", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 661 :
        xlsx.write("D6","機器人放料完成信號異常", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 662 :
        xlsx.write("D6","检测气缸1收回到位信号異常", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 663 :
        xlsx.write("D6","检测气缸2收回到位信号X11異常", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 664 :
        xlsx.write("D6","检测气缸1伸出位傳感器X6", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 665 :
        xlsx.write("D6","气缸2伸出傳感器X10異常", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 670 :
        xlsx.write("D6","M670升降机正装气缸伸出异常", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 671 :
        xlsx.write("D6","M671升降机正装气缸缩回异常", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 672 :
        xlsx.write("D6","M672升降机倒装气缸伸出异常", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 673 :
        xlsx.write("D6","M673升降机倒装气缸缩回异常", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 674 :
        xlsx.write("D6","M674卡泡棉气缸伸出异常", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 675 :
        xlsx.write("D6","M675卡泡棉气缸缩回异常", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 676 :
        xlsx.write("D6","M676初始化条件不足", format5);/*写入文字，应该刚才设置的样式*/
        break;
    case 677 :
        xlsx.write("D6","M677感应器X16异常", format5);/*写入文字，应该刚才设置的样式*/
        break;

    //第七排
    double Cycle_Time;
    plc_utltype_->GetDevice("D5021", Cycle_Time);
    xlsx.write("D7",Cycle_Time+"S", format5);/*写入文字，应该刚才设置的样式*/

    //第八排
    int production_quantity;
    plc_utltype_->GetDevice("D5022", production_quantity);
    xlsx.write("D7",production_quantity+"個", format5);/*写入文字，应该刚才设置的样式*/

    //第九排
    int ng_number;
    plc_utltype_->GetDevice("D5024", ng_number);
    xlsx.write("D8",ng_number+"個", format5);

    //第十排
    double yield_rate;
    plc_utltype_->GetDevice("D5026", yield_rate);
    xlsx.write("D9",yield_rate+"%", format5);

    //第十一排
    int running_time;
    plc_utltype_->GetDevice("D5030", running_time);
    xlsx.write("D10",running_time+"分钟", format5);

    //第十二排
    int change_product;
    plc_utltype_->GetDevice("D5031", change_product);
    xlsx.write("D11",change_product+"次", format5);

    //第十三排
    int change_product_used_time;
    plc_utltype_->GetDevice("D5032", change_product_used_time);
    xlsx.write("D12",change_product_used_time+"S", format5);

    //第十四排
    double sleep;
    plc_utltype_->GetDevice("D5034", sleep);
    xlsx.write("D13",sleep+"S", format5);

    //第十五排
    double bug;
    plc_utltype_->GetDevice("D5036", bug);
    xlsx.write("D14",bug+"S", format5);

    //第十六排
    double wait;
    plc_utltype_->GetDevice("D5038", wait);
    xlsx.write("D15",wait+"S", format5);

    //第十七排
    double block;
    plc_utltype_->GetDevice("D5040", block);
    xlsx.write("D16",block+"S", format5);

    //第十八排
    double in_running_rate;
    plc_utltype_->GetDevice("D5046", in_running_rate);
    xlsx.write("D17",in_running_rate+"%", format5);

    //第十九排
    int all_ng_numbers;
    int pozition;
    int tid;
    int sn;
    int tid_cmc;
    int sn_cmc;
    int fid_cmc;
    int advance_product;
    plc_utltype_->GetDevice("D5100", pozition);
    plc_utltype_->GetDevice("D5102", tid);
    plc_utltype_->GetDevice("D5106", sn);
    plc_utltype_->GetDevice("D5108", tid_cmc);
    plc_utltype_->GetDevice("D5110", sn_cmc);
    plc_utltype_->GetDevice("D5112", fid_cmc);
    plc_utltype_->GetDevice("D5104", advance_product);
    all_ng_numbers = pozition + tid + sn + tid_cmc + sn_cmc + fid_cmc + advance_product;
    xlsx.write("D18",all_ng_numbers+"個", format5);

    //第二十排
    double shengjiaangji_maintain;
    plc_utltype_->GetDevice("D5160", shengjiaangji_maintain);
    xlsx.write("D19",shengjiaangji_maintain+"天", format5);
    double jixieshou_maintain;
    plc_utltype_->GetDevice("D5161", jixieshou_maintain);
    xlsx.write("D20",jixieshou_maintain+"天", format5);
    double haimian_maintain;
    plc_utltype_->GetDevice("D5162", haimian_maintain);
    xlsx.write("D21",haimian_maintain+"天", format5);
    double yunxingyixiang_maintain;
    plc_utltype_->GetDevice("D5163", yunxingyixiang_maintain);
    xlsx.write("D22",yunxingyixiang_maintain+"天", format5);
    double pidai_maintain;
    plc_utltype_->GetDevice("D5164", pidai_maintain);
    xlsx.write("D23",pidai_maintain+"天", format5);
    double diangui_maintain;
    plc_utltype_->GetDevice("D5165", diangui_maintain);
    xlsx.write("D24",diangui_maintain+"天", format5);
    double qiguan_maintain;
    plc_utltype_->GetDevice("D5166", qiguan_maintain);
    xlsx.write("D24",qiguan_maintain+"天", format5);
    double fengshan_maintain;
    plc_utltype_->GetDevice("D5167", fengshan_maintain);
    xlsx.write("D24",fengshan_maintain+"天", format5);
    double maintain9;
    plc_utltype_->GetDevice("D5168", maintain9);
    xlsx.write("D24",maintain9+"天", format5);
    double maintain10;
    plc_utltype_->GetDevice("D5169", maintain10);
    xlsx.write("D24",maintain10+"天", format5);

    //第二十一项
    double pozition_no_rec_num;
    double pozition_no_rec_time;
    plc_utltype_->GetDevice("D5400", pozition_no_rec_num);
    plc_utltype_->GetDevice("D5600", pozition_no_rec_time);
    xlsx.write("D25",pozition_no_rec_num+"次", format5);
    xlsx.write("D26",pozition_no_rec_time+"S", format5);

    double tid_no_rec_num;
    double tid_no_rec_time;
    plc_utltype_->GetDevice("D5402", tid_no_rec_num);
    plc_utltype_->GetDevice("D5602", tid_no_rec_time);
    xlsx.write("D25",tid_no_rec_num+"次", format5);
    xlsx.write("D26",tid_no_rec_time+"S", format5);

    double m63_not_set_num;
    double m63_not_set_time;
    plc_utltype_->GetDevice("D5404", m63_not_set_num);
    plc_utltype_->GetDevice("D5604", m63_not_set_time);
    xlsx.write("D25",m63_not_set_num+"次", format5);
    xlsx.write("D26",m63_not_set_time+"S", format5);

    double door_open_num;
    double door_open_time;
    plc_utltype_->GetDevice("D5406", door_open_num);
    plc_utltype_->GetDevice("D5606", door_open_time);
    xlsx.write("D25",door_open_num+"次", format5);
    xlsx.write("D26",door_open_time+"S", format5);

    double crash_stop_num;
    double crash_stop_time;
    plc_utltype_->GetDevice("D5408", crash_stop_num);
    plc_utltype_->GetDevice("D5608", crash_stop_time);
    xlsx.write("D25",crash_stop_num+"次", format5);
    xlsx.write("D26",crash_stop_time+"S", format5);

    double vacuum_num;
    double vacuum_time;
    plc_utltype_->GetDevice("D5410", vacuum_num);
    plc_utltype_->GetDevice("D5610", vacuum_time);
    xlsx.write("D25",vacuum_num+"次", format5);
    xlsx.write("D26",vacuum_time+"S", format5);

    double fid_failed_num;
    double fid_failed_time;
    plc_utltype_->GetDevice("D5412", fid_failed_num);
    plc_utltype_->GetDevice("D5612", fid_failed_time);
    xlsx.write("D25",fid_failed_num+"次", format5);
    xlsx.write("D26",fid_failed_time+"S", format5);

    double robot_warning_num;
    double robot_warning_time;
    plc_utltype_->GetDevice("D5414", robot_warning_num);
    plc_utltype_->GetDevice("D5614", robot_warning_time);
    xlsx.write("D25",robot_warning_num+"次", format5);
    xlsx.write("D26",robot_warning_time+"S", format5);

    double conveyer_belt_num;
    double conveyer_belt_time;
    plc_utltype_->GetDevice("D5416", conveyer_belt_num);
    plc_utltype_->GetDevice("D5616", conveyer_belt_time);
    xlsx.write("D25",conveyer_belt_num+"次", format5);
    xlsx.write("D26",conveyer_belt_time+"S", format5);

    double frame_disk_num;
    double frame_disk_time;
    plc_utltype_->GetDevice("D5418", frame_disk_num);
    plc_utltype_->GetDevice("D5618", frame_disk_time);
    xlsx.write("D25",frame_disk_num+"次", format5);
    xlsx.write("D26",frame_disk_time+"S", format5);

    double frame_hand_num;
    double frame_hand_time;
    plc_utltype_->GetDevice("D5420", frame_hand_num);
    plc_utltype_->GetDevice("D5620", frame_hand_time);
    xlsx.write("D25",frame_hand_num+"次", format5);
    xlsx.write("D26",frame_hand_time+"S", format5);

    double frame_ng_num;
    double frame_ng_time;
    plc_utltype_->GetDevice("D5422", frame_ng_num);
    plc_utltype_->GetDevice("D5622", frame_ng_time);
    xlsx.write("D25",frame_ng_num+"次", format5);
    xlsx.write("D26",frame_ng_time+"S", format5);

    double frame_product_ng_num;
    double frame_product_ng_time;
    plc_utltype_->GetDevice("D5424", frame_product_ng_num);
    plc_utltype_->GetDevice("D5624", frame_product_ng_time);
    xlsx.write("D25",frame_product_ng_num+"次", format5);
    xlsx.write("D26",frame_product_ng_time+"S", format5);

    double D5426;
    double D5626;
    plc_utltype_->GetDevice("D5426", D5426);
    plc_utltype_->GetDevice("D5626", D5626);


    double D5428;
    double D5628;
    plc_utltype_->GetDevice("D5400", D5428);
    plc_utltype_->GetDevice("D5600", D5628);
    xlsx.write("D25",pozition_no_rec_num+"次", format5);
    xlsx.write("D26",pozition_no_rec_time+"S", format5);

    double D5430;
    double D5630;
    plc_utltype_->GetDevice("D5430", D5430);
    plc_utltype_->GetDevice("D5630", D5630);


    double D5432;
    double D5632;
    plc_utltype_->GetDevice("D5432", D5432);
    plc_utltype_->GetDevice("D5632", D5632);

    double D5434;
    double D5634;
    plc_utltype_->GetDevice("D5434", D5434);
    plc_utltype_->GetDevice("D5634", D5634);

    double D5436;
    double D5636;
    plc_utltype_->GetDevice("D5436", D5436);
    plc_utltype_->GetDevice("D5636", D5636);

    double D5438;
    double D5638;
    plc_utltype_->GetDevice("D5438", D5438);
    plc_utltype_->GetDevice("D5638", D5638);

    double D5440;
    double D5640;
    plc_utltype_->GetDevice("D5440", D5440);
    plc_utltype_->GetDevice("D5640", D5640);

    double D5442;
    double D5642;
    plc_utltype_->GetDevice("D5442", D5442);
    plc_utltype_->GetDevice("D5642", D5642);

    double D5444;
    double D5644;
    plc_utltype_->GetDevice("D5444", D5444);
    plc_utltype_->GetDevice("D5644", D5644);

    double D5446;
    double D5646;
    plc_utltype_->GetDevice("D5446", D5446);
    plc_utltype_->GetDevice("D5646", D5646);

    double D5448;
    double D5648;
    plc_utltype_->GetDevice("D5448", D5448);
    plc_utltype_->GetDevice("D5648", D5648);

    double D5450;
    double D5650;
    plc_utltype_->GetDevice("D5450", D5450);
    plc_utltype_->GetDevice("D5650", D5650);

    double D5452;
    double D5652;
    plc_utltype_->GetDevice("D5452", D5452);
    plc_utltype_->GetDevice("D5652", D5652);

    double D5454;
    double D5654;
    plc_utltype_->GetDevice("D5454", D5454);
    plc_utltype_->GetDevice("D5654", D5654);

    double D5456;
    double D5656;
    plc_utltype_->GetDevice("D5456", D5456);
    plc_utltype_->GetDevice("D5656", D5656);

    double D5458;
    double D5658;
    plc_utltype_->GetDevice("D5458", D5458);
    plc_utltype_->GetDevice("D5658", D5658);

    double D5460;
    double D5660;
    plc_utltype_->GetDevice("D5460", D5460);
    plc_utltype_->GetDevice("D5660", D5660);

    double D5462;
    double D5662;
    plc_utltype_->GetDevice("D5462", D5462);
    plc_utltype_->GetDevice("D5662", D5662);

    double D5464;
    double D5664;
    plc_utltype_->GetDevice("D5464", D5464);
    plc_utltype_->GetDevice("D5664", D5664);

    xlsx.write("D25",pozition_no_rec_num+tid_no_rec_num+m63_not_set_num+"次", format5);
    xlsx.write("D26",pozition_no_rec_time+tid_no_rec_time+m63_not_set_time+"S", format5);
    }

    QXlsx::Document xlsx2("equipment_information_collection.xlsx");/*复制book1到book2*/
    xlsx2.saveAs("equipment_information_collection.xlsx");

    return 0;

}
