#pragma once

#include <vector>
#include <array>
#include <string>
#include <cstdint>

class ip_filter{
    private:
        std::vector<std::array<int, 4>> ip_pool;

    public:
        /*
        ** Initialize list of ip with a string vector
        */
        ip_filter(const std::vector<std::string>& ip_pool);

        /*
        ** Filter by first byte and output
        ** Example for first_byte=1:
        **  Output:
        **   1.70.44.170
        **   1.29.168.152
        **   1.1.234.8
        */
        std::vector<std::array<int, 4>> filter(int first_byte);

        /*
        ** Filter by first and seecond bytes and output
        ** Example for first_byte=46 and second_byte=70
        **  Output:
        **   46.70.225.39
        **   46.70.147.26
        **   46.70.113.73
        **   29.46.70.76
        */
        std::vector<std::array<int, 4>> filter(int first_byte, int second_byte);

        /*
        ** Filter by any byte and output
        ** Example for byte=46
        **  Output:
        **   186.204.34.46
        **   186.46.222.194
        **   185.46.87.231
        **   185.46.86.132
        **   185.46.86.131
        **   185.46.86.131
        **   185.46.86.22
        **   185.46.85.204
        **   185.46.85.78
        **   68.46.218.208
        **   46.251.197.23
        **   46.223.254.56
        **   46.223.254.56
        **   46.182.19.219
        **   46.161.63.66
        **   46.161.61.51
        **   46.161.60.92
        **   46.161.60.35
        **   46.161.58.202
        **   46.161.56.241
        **   46.161.56.203
        **   46.161.56.174
        **   46.161.56.106
        **   46.161.56.106
        **   46.101.163.119
        **   46.101.127.145
        **   46.70.225.39
        **   46.70.147.26
        **   46.70.113.73
        **   46.70.29.76
        **   46.55.46.98
        **   46.49.43.85
        **   39.46.86.85
        **   5.189.203.46
        */
        std::vector<std::array<int, 4>> filter_any(int byte);

        /*
        ** Split string with the ip on vector of byte
        ** Example:
        ** (".11",   '.') -> [0,  11]
        ** ("..",    '.') -> [0,  0]
        ** ("11.",   '.') -> [11, 0]
        ** ("11.22", '.') -> [11, 22]
        */
        static std::array<int, 4> split(const std::string& ip_str, char sym);
};
