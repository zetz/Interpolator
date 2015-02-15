//
//  main.cpp
//  Interpolator
//
//  Created by 정광일 on 2015. 2. 15..
//  Copyright (c) 2015년 kwang-il Jung. All rights reserved.
//

#include <iostream>

#include "Interpolator.hpp"


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    using namespace Interpolator;
    
    Sine<uint> quad;
    auto quad_out   = makeReverse(quad);
    auto quad_inout = makeInOutFunc(quad);
    
    
    uint beg = 1;
    uint end = 100;
    
    
    for (int i= 0; i< 11; ++i) {
        float t = (float)i / 10.f;
        
        uint v0 = quad(t, beg, end);
        uint v1 = quad_out(t, beg, end);
        uint v2 = quad_inout(t, beg, end);
        
        std::cout<< "t: " << t << ", v0: "<< v0<< ", v1: "<< v1<< ", v2: " << v2<< std::endl;
        
    }
    
    std::cout<< sqrt(1.f)<< std::endl;
    Circle<float> cir;
    auto v = cir(1.f, 1.f, 100.f);
    std::cout<< v << std::endl;
    
    
    return 0;
}
