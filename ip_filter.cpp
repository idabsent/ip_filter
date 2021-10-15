#include "ip_filter.hpp"
#include <algorithm>
#include <iostream>

ip_filter::ip_filter(const std::vector<std::string>& ip_pool){
    for (const std::string& ip_str: ip_pool){
        std::array<int, 4> ip = split(ip_str, '.');
        this->ip_pool.push_back(ip);
    }
    pool_sort(this->ip_pool);
}

std::vector<std::array<int, 4>> ip_filter::filter(int first_byte){
    std::vector<std::array<int , 4>> filtered;
    std::for_each(ip_pool.cbegin(), ip_pool.cend(),
                  [&](std::array<int, 4> ip){
                      if (ip.at(0) == first_byte){
                          filtered.push_back(ip);
                      }
                  });
    return filtered;
}

std::vector<std::array<int, 4>> ip_filter::filter(int first_byte, int second_byte){
    std::vector<std::array<int, 4>> filtered;
    std::for_each(ip_pool.cbegin(), ip_pool.cend(),
                  [&](std::array<int, 4> ip){
                      if (ip.at(0) == first_byte && ip.at(1) == second_byte)
                          filtered.push_back(ip);
                  });
    return filtered;
}

std::vector<std::array<int, 4>> ip_filter::filter_any(int any_byte){
    std::vector<std::array<int, 4>> filtered;
    std::for_each(ip_pool.cbegin(), ip_pool.cend(),
                  [&](std::array<int, 4> ip){
                      bool maybe = false;
                      for(int i = 0; i < 4; i++)
                          if (ip.at(i) == any_byte)
                              maybe = true;
                      if (maybe){
                        filtered.push_back(ip);
                      }
                  });
    return filtered;
}

std::array<int, 4> ip_filter::split(const std::string& ip_str, char sym){
    std::array<int, 4> ip;
    int i = 0;
    std::string::size_type start = 0;
    std::string::size_type stop = ip_str.find_first_of(sym);
    while (stop != std::string::npos){
        auto ip_byte = ip_str.substr(start, stop-start);
        ip.at(i) = ip_byte == "" ? 0 : std::stoi(ip_byte);
        start = stop + 1;
        stop = ip_str.find_first_of(sym, start);
        i++;
    }
    auto ip_byte = ip_str.substr(start, stop-start);
    ip.at(i) = ip_byte == "" ? 0 : std::stoi(ip_byte);
    return ip;
}

void ip_filter::pool_sort(std::vector<std::array<int, 4>>& ip_pool){
    std::sort(ip_pool.begin(), ip_pool.end(),
              [](std::array<int, 4> ip_first, std::array<int, 4> ip_second)->bool{
                for (int i = 0; i < 4; i++)
                    if (ip_first.at(i) != ip_second.at(i)){
                        bool greater = ip_first.at(i) > ip_second.at(i);
                        return greater;
                    }
                return false;
              });
}