#include "fidparser.h"

FidParser::FidParser()
{
    data_size_ = 0;
    memset(buffer_, 0, sizeof(buffer_)/sizeof(buffer_[0]));
}

int FidParser::empty_buffer_size()
{
    int buffer_size = sizeof(buffer_)/sizeof(buffer_[0]);
    return buffer_size - data_size_;
}

void FidParser::push_data(const char* data, int length)
{
    int buffer_size = sizeof(buffer_)/sizeof(buffer_[0]);
    int push_count = 0;
    for (int i = data_size_; i < buffer_size; ++i)
    {
        if (push_count < length)
        {
            buffer_[i] = data[push_count++];
        }
        else
            break;
    }
    data_size_ += push_count;
}

string FidParser::shift_fid()
{
    bool find_return = false;
    unsigned int fid_length = 0;
    for(int i = 0; i < data_size_; ++i)
    {
        if (buffer_[i] == '\r')
        {
            find_return = true;
            break;
        }
        fid_length++;
    }

    if (find_return)
    {
        string fid;
        if (fid_length < 6)
        {
            for (unsigned int i = 0; i < fid_length; ++i)
            {
                fid.push_back(buffer_[i]);
            }
        }
        else
        {
            for (unsigned int i = fid_length - 6; i < fid_length; ++i)
            {
                fid.push_back(buffer_[i]);
            }
        }

        // 以防出现连续的 '\r'
        int next_fid_start = fid_length + 1;
        for (int i = next_fid_start; i < data_size_; ++i)
        {
            if (buffer_[i] == '\r')
                next_fid_start++;
            else
                break;
        }
        int move_count = 0;
        for (int i = next_fid_start; i < data_size_; ++i)
        {
            buffer_[move_count++] = buffer_[i];
        }
        data_size_ = move_count;
        return fid;
    }
    else
        return "";
}
