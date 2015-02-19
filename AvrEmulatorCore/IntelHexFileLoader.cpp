#include "IntelHexFileLoader.h"

using namespace avremu;

IntelHexFileLoader::IntelHexFileLoader(const char * file_path)
{
	u32 fpath_size = strlen(file_path);
    _file_path = new char[fpath_size + 1];
    strcpy_s(_file_path, fpath_size + 1, file_path);
	_file_path[fpath_size] = 0;
}

IntelHexFileLoader::~IntelHexFileLoader()
{
    delete[] _file_path;
}

u8 IntelHexFileLoader::writeMemory(u8 *pointer, u32 max_size)
{
    std::fstream in_file(_file_path,std::ios::in);
    if(!in_file)
    {
        TRACE_PRT("Can't read file: %s",_file_path);
        return Error;
    }

    in_file.seekg(0,std::ios::end);
    u32 fsize = u32(in_file.tellg());
    in_file.seekg(0,std::ios::beg);

    char* file_data = new char[fsize];
    in_file.read(file_data,fsize);

    in_file.close();
    while(true)
    {
        if(file_data[fsize-1] == 'F') break;
        fsize--;
    }
    u32 data_ptr = 0;
    u32 addr_offset = 0; //seted by rec. type 02
    while(true)
    {
        if(data_ptr >= fsize) break;
        // interp. start
        if(file_data[data_ptr] != ':')
        {
            TRACE_STRING("Expected a ':' char !");
            delete[] file_data;
            return Error;
        }
        data_ptr++;
        // reading data_length
        char byte_count_ar[3] = {0,0,0};
        byte_count_ar[0] = file_data[data_ptr];
        byte_count_ar[1] = file_data[data_ptr + 1];

        data_ptr+=2;
        u32 byte_count = (u32)strtol(byte_count_ar,0,16);

        // reading addr
        char addr_chars[5] = {0,0,0,0,0};

        addr_chars[0] = file_data[data_ptr];
        addr_chars[1] = file_data[data_ptr + 1];
        addr_chars[2] = file_data[data_ptr + 2];
        addr_chars[3] = file_data[data_ptr + 3];
        u32 addr = (u32)strtol(addr_chars,0,16);
        data_ptr += 4;

        // reading record type
        data_ptr++; //skip first (always 0)
        u8  rec_type = (u8)(file_data[data_ptr] - '0');
        data_ptr++;

        // reading data bytes (size = byte_count)
        u8 *data_bytes = new u8[byte_count];
        for(u32 i=0;i<byte_count;i++)
        {
            char data_byte_pair[3] = {0,0,0};
            data_byte_pair[0] = file_data[data_ptr + i*2];
            data_byte_pair[1] = file_data[data_ptr + i*2+1];
            data_bytes[i] = (u8)strtol(data_byte_pair,0,16);
        }
        data_ptr+=byte_count*2;

        // reading controll sum
        char ctr_bytes[3] = {0,0,0};
        ctr_bytes[0] = file_data[data_ptr];
        ctr_bytes[1] = file_data[data_ptr + 1];
        u8 control_number = (u8)strtol(ctr_bytes,0,16);
        data_ptr+=2;

        //execute line
        switch(rec_type)
        {
            case 0:
            if(addr + addr_offset + byte_count >= max_size)
            {
                TRACE_STRING("Can't write data to memory: (addr + addr_offset + byte_count >= max_size)");
            }
            else
            {
                memcpy(pointer + addr + addr_offset,data_bytes,byte_count);
            }
            break;
            case 1:
                // eof;
            break;
            case 2:
                if(byte_count != 2)
                {
                    TRACE_PRT("Record type 2, byte count shuld by 2 but is %d",
                              byte_count);
                    break;
                }
                addr_offset = data_bytes[0] | data_bytes[1] << 8;
            break;
            case 3: case 4: case 5:
                TRACE_STRING("Record types 3,4 and 5 not suported jet !");
            break;
        };
        delete[] data_bytes;

        data_ptr++; //new line char
    }
    delete[] file_data;
    return Success;
}
