#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "ip_filter.hpp"

const std::string file_name = "ip_filter.tsv";

void clear_cin();
std::string ip_to_str(std::array<int, 4> ip);

int main(int argc, char const *argv[])
{
        try
        {
                std::cout << "\t\tIP ADDRESS FILTER";
                std::vector<std::string> ip_pool;
                std::ifstream file(file_name);

                for (std::string line;std::getline(file, line);){
                        std::cout << "line: " << line << std::endl;
                        std::string::size_type ip_end_pos = line.find_first_of('\t');
                        std::string ip = line.substr(0, ip_end_pos);
                        std::cout << ip << std::endl;
                        ip_pool.push_back(ip);
                }

                ip_filter ip_filtr(ip_pool);

                int first_byte;
                std::cout << "Filter by first byte\n first_byte=";
                std::cin  >> first_byte;
                std::cout<<first_byte<<"\n";
                clear_cin();
                for (std::array<int,4> ip: ip_filtr.filter(first_byte))
                        std::cout << " " << ip_to_str(ip) << std::endl;

                int second_byte;
                std::cout << "Filter by first byte and second byte\n second_byte=";
                std::cin  >> second_byte;
                std::cout<<second_byte<<"\n";
                clear_cin();
                for (std::array<int,4> ip: ip_filtr.filter(first_byte, second_byte))
                        std::cout << " " << ip_to_str(ip) << std::endl;

                int any_byte;
                std::cout << "Filter by any byte\n any_byte=";
                std::cin  >> any_byte;
                std::cout<<any_byte<<"\n";
                clear_cin();
                for (std::array<int,4> ip: ip_filtr.filter_any(any_byte))
                        std::cout << " " << ip_to_str(ip) << std::endl;
        }
        catch(std::exception& e)
        {
                std::cout << e.what();
        }
}

std::string ip_to_str(std::array<int, 4> ip){
        std::string ip_str;
        for(int i = 0; i < 3; i++){
                ip_str.append(std::to_string(ip.at(i)));
                ip_str.append(".");
        }
        ip_str.append(std::to_string(ip.at(3)));
        return ip_str;
}

void clear_cin(){
        if (std::cin.fail())
                std::cin.clear();
        std::cin.ignore(32767, '\n');
}
