#include <fstream>
#include <vector>
#include <map>
#include <cstdint>
#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
#include <algorithm>

std::map<std::string, std::string> table = 
{
    {"01110111", "1"},
    {"01111011", "2"},
    {"01111101", "3"},
    {"01111110", "F"},
    {"10110111", "4"},
    {"10111011", "5"},
    {"10111101", "6"},
    {"10111110", "E"},
    {"11010111", "7"},
    {"11011011", "8"},
    {"11011101", "9"},
    {"11011110", "D"},
    {"11100111", "A"},
    {"11101011", "0"},
    {"11101101", "B"},
    {"11101110", "C"}
};
std::map<std::string, std::string> table2 = 
{
    {"01110111", "1"},
    {"10110111", "2"},
    {"11010111", "3"},
    {"11100111", "F"},
    {"01111011", "4"},
    {"10111011", "5"},
    {"11011011", "6"},
    {"11101011", "E"},
    {"01111101", "7"},
    {"10111101", "8"},
    {"11011101", "9"},
    {"11101101", "D"},
    {"01111110", "A"},
    {"10111110", "0"},
    {"11011110", "B"},
    {"11101110", "C"}
};

uint16_t mirror(uint16_t word12b)
{
    uint16_t temp = 0;
    for (int i=0; i<12; i++)
    {
        temp |= ((word12b>>i)&1) << (12-(i+1));
    }
    return temp;
}

uint8_t mirror4b(uint16_t word4b)
{
    uint8_t temp = 0;
    for (int i=0; i<4; i++)
    {
        temp |= ((word4b>>i)&1) << (4-(i+1));
    }
    return temp;
}

uint8_t get_bit(uint8_t byte, uint8_t bitno)
{
    return (byte>>bitno)&1;
}

void set_bit(uint8_t byte, uint8_t bitno, uint8_t value)
{
    if(value==1)
    {
        byte |= value<<bitno;
    }
    else if(value==0)
    {
        byte &= ~(value<<bitno);
    }
}

uint8_t remap(uint8_t byte)
{
    // return ((byte&0xF)<<4) + ((byte&0xF0)>>4);
    return byte;
}

void bytify(std::ifstream& file, std::vector<std::string>& vec)
{
    std::string line;
    while(std::getline(file,line))
    {
        std::cout << line << std::endl;
        std::reverse(line.begin(), line.end());
        vec.push_back(line);
    }
}

void lsb_msb(const std::vector<std::string>& before, std::vector<std::string>& after)
{
    uint16_t word;
    std::string lsb, msb;
    for(auto it=before.begin(); it != before.end(); ++it)
    {
		msb = (*it).substr(0,4);
		lsb = (*it).substr(4,4);
        after.push_back(lsb+msb);
    }
}

void rlsb_msb(const std::vector<std::string>& before, std::vector<std::string>& after)
{
    uint16_t word;
    std::string lsb, msb;
    for(auto it=before.begin(); it != before.end(); ++it)
    {
		msb = (*it).substr(0,4);
		lsb = (*it).substr(4,4);
		std::reverse(lsb.begin(),lsb.end());
        after.push_back(lsb+msb);
    }
}
void lsb_rmsb(const std::vector<std::string>& before, std::vector<std::string>& after)
{
    uint16_t word;
    std::string lsb, msb;
    for(auto it=before.begin(); it != before.end(); ++it)
    {
		msb = (*it).substr(0,4);
		lsb = (*it).substr(4,4);
		std::reverse(msb.begin(),msb.end());
        after.push_back(lsb+msb);
    }
}
void rlsb_rmsb(const std::vector<std::string>& before, std::vector<std::string>& after)
{
    uint16_t word;
    std::string lsb, msb;
    for(auto it=before.begin(); it != before.end(); ++it)
    {
		msb = (*it).substr(0,4);
		lsb = (*it).substr(4,4);
		std::reverse(msb.begin(),msb.end());
		std::reverse(lsb.begin(),lsb.end());
        after.push_back(lsb+msb);
    }
}

void msb_lsb(const std::vector<std::string>& before, std::vector<std::string>& after)
{
    uint16_t word;
    std::string lsb, msb;
    for(auto it=before.begin(); it != before.end(); ++it)
    {
		msb = (*it).substr(0,4);
		lsb = (*it).substr(4,4);
        after.push_back(msb+lsb);
    }
}

void msb_rlsb(const std::vector<std::string>& before, std::vector<std::string>& after)
{
    uint16_t word;
    std::string lsb, msb;
    for(auto it=before.begin(); it != before.end(); ++it)
    {
		msb = (*it).substr(0,4);
		lsb = (*it).substr(4,4);
		std::reverse(lsb.begin(),lsb.end());
        after.push_back(msb+lsb);
    }
}
void rmsb_lsb(const std::vector<std::string>& before, std::vector<std::string>& after)
{
    uint16_t word;
    std::string lsb, msb;
    for(auto it=before.begin(); it != before.end(); ++it)
    {
		msb = (*it).substr(0,4);
		lsb = (*it).substr(4,4);
		std::reverse(msb.begin(),msb.end());
        after.push_back(msb+lsb);
    }
}
void rmsb_rlsb(const std::vector<std::string>& before, std::vector<std::string>& after)
{
    uint16_t word;
    std::string lsb, msb;
    for(auto it=before.begin(); it != before.end(); ++it)
    {
		msb = (*it).substr(0,4);
		lsb = (*it).substr(4,4);
		std::reverse(msb.begin(),msb.end());
        std::reverse(lsb.begin(),lsb.end());
        after.push_back(msb+lsb);
    }
}

// A308F9164DE7C5DB
// F7E6A9182B03C5BD

void print_results(const std::vector<std::string>& vec)
{
	std::cout << "DGSESIEE{";
    for(auto it=vec.begin(); it != vec.end(); ++it)
    {
        std::cout << table[(*it)];
    }
    std::cout << "}" << std::endl;
    std::cout << "DGSESIEE{";
    for(auto it=vec.begin(); it != vec.end(); ++it)
    {
        std::cout << table2[(*it)];
    }
    std::cout << "}" << std::endl;
}

int main()
{
    std::ifstream ifs("filtered");
    std::vector<std::string> before, after;

    bytify(ifs, before);

    std::cout << "============" << std::endl;
    
    lsb_msb(before, after);
    print_results(after);
	after.clear();
	
    rlsb_msb(before, after);
    print_results(after);
	after.clear();
	
    lsb_rmsb(before, after);
    print_results(after);
    after.clear();
    
    rlsb_rmsb(before, after);
    print_results(after);
    after.clear();
    
    msb_lsb(before, after);
    print_results(after);
    after.clear();
    
    rmsb_lsb(before, after);
    print_results(after);
	after.clear();
	
    msb_rlsb(before, after);
    print_results(after);
	after.clear();
	
	rmsb_rlsb(before, after);
    print_results(after);
	after.clear();
	
    return 0;
}
