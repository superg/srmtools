#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>



using namespace std;



void srm2sav(const filesystem::path &in_fn, const filesystem::path &out_fn)
{
    ifstream ifs(in_fn, ifstream::binary);
    if(!ifs.is_open())
        throw runtime_error("unable to open input file");

    auto data_size(filesystem::file_size(in_fn));
    if(data_size & 1)
        throw runtime_error("file is not SRM file");

    std::vector<uint16_t> data(data_size / sizeof(uint16_t));
    ifs.read((char *)data.data(), data_size);

    ofstream ofs(out_fn, ofstream::binary);
    if(!ofs.is_open())
        throw runtime_error("unable to create output file");

    for(auto const &e : data)
    {
        uint8_t d = e >> 8 & 0xff;
        ofs.write((char *)&d, sizeof(d));
    }
}



int main(int argc, char *argv[])
{
    int exit_code(0);

    try
    {
        if(argc == 2)
        {
            filesystem::path in_fn(argv[1]);
            filesystem::path out_fn(argv[1]);
            out_fn.replace_extension(".sav");

            if(in_fn == out_fn)
                throw runtime_error("overwriting input file");

            srm2sav(in_fn, out_fn);
        }
        else
        {
            cout << "usage: srm2sav <SRM-file>" << endl;
            exit_code = 1;
        }
    }
    catch(const exception &e)
    {
        cerr << "error: " << e.what() << endl;
        exit_code = 2;
    }
    catch(...)
    {
        cerr << "error: unhandled exception" << endl;
        exit_code = 3;
    }

    return exit_code;
}
