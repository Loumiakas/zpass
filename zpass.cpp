#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <bitset>


#define SEED_LGTH   12
#define MGC_NUM_1   0x10F0A563L
#define MGC_NUM_2   7

void ror( unsigned long &b, unsigned long c )
{

    std::string b_bin = std::bitset<32>(b).to_string();
    std::string temp = b_bin.substr( b_bin.size() - c ) + 
                       b_bin.substr( 0, b_bin.size() - c );
    b = std::bitset<32>(temp).to_ulong();
}
std::string to_upper(unsigned long x)  
{
    std::stringstream sstream;
    sstream << std::hex << x;
    std::string s = sstream.str();
    std::transform( s.begin(), s.end(), s.begin(), toupper);
    return s;
}

int main(int argc, char *argv[])
{
    if ( argc != 2 ) {
        std::cout << "ATSE Seed based unlock for Eircom's Zyxel routers" << std::endl;
        std::cout << "- Usage: zypass <seed>" << std::endl;
        return 1;
    }

    if ( strlen( argv[ 1 ] ) != SEED_LGTH ) {
        std::cout << "Error: Invalid seed length" << std::endl;
        return 1;
    }

    std::string seed = argv[ 1 ];
    unsigned long a;
    unsigned long b;
    unsigned long c;
    unsigned long pass;

    std::istringstream( seed.substr( 0, 6 ) ) >> std::hex >> a;
    b = a + MGC_NUM_1;
    std::istringstream( seed.substr( 10, 12 ) ) >> std::hex >> c;
    c = c & MGC_NUM_2;
    ror( b, c );
    pass = b ^ a;

    std::cout << "PASSWORD: " << std::hex
              << to_upper( pass ) << std::endl;
    return 0;
}
