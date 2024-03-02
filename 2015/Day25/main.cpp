#include <iostream>

int main(int argc, char **argv)
{
    const int row{2978};
    const int col{3083};
    unsigned long long int code{20151125};
    int r = 2; 
    int c = 1;
    while(true) 
    {
        code = (code * 252533) % 33554393;
        if(r == row && c == col) break;
        --r;
        ++c;
        
        if(r == 0) 
        {
            r = c;
            c = 1;
        }
    }
    std::cout << code << std::endl;
}