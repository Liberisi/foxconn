#ifndef FIDPARSER_H
#define FIDPARSER_H

#include <string>

using namespace std;

class FidParser
{
public:
    FidParser();

    // 剩余buffer空间
    int empty_buffer_size();
    // 如果 length 大于剩余buffer空间，则多余数据会被丢弃
    void push_data(const char* data, int length);
    string shift_fid();

private:
    int data_size_;
    char buffer_[128];
};

#endif // FIDPARSER_H
