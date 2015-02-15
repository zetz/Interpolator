//
//  Interpolator.hpp
//  Interpolator
//
//  Created by 정광일 on 2015. 2. 15..
//  Copyright (c) 2015년 kwang-il Jung. All rights reserved.
//

#pragma once

#include <math.h>

namespace Interpolator {
    
    template<class T>
    struct type_tag {
        typedef T value_type;
    };
    
    // N'th function
    template<class T>
    struct Linear : public type_tag<T> {
        T operator () (float t, const T& v0, const T& v1) {
            return v0 + (v1- v0) * (t);
        }
    };
    
    template<class T>
    struct Quad : public type_tag<T> {
        T operator() (float t, const T& v0, const T& v1) {
            return v0 + (v1- v0) * (t* t);
        }
    };
    
    template<class T>
    struct Cubic : public type_tag<T> {
        T operator() (float t, const T& v0, const T& v1) {
            return v0 + (v1- v0) * (t* t* t);
        }
    };
    
    template<class T>
    struct Quart : public type_tag<T> {
        T operator() (float t, const T& v0, const T& v1) {
            return v0 + (v1- v0) * (t* t* t* t);
        }
    };
    
    template<class T>
    struct Quint : public type_tag<T> {
        T operator() (float t, const T& v0, const T& v1) {
            return v0 + (v1- v0) * (t* t* t* t* t);
        }
    };
    
    template<class T>
    struct Exponent : public type_tag<T> {
        T operator() (float t, const T& v0, const T& v1) {
            return v0 + (v1- v0) * (powf(2.f, t- 1.f));
        }
    };
    
    // @todo : bug
    template<class T>
    struct Circle : public type_tag<T> {
        T operator() (float t, const T& v0, const T& v1) {
            return v0 + (v1- v0) * (sqrt(1.f- t* t)- 1.f);
        }
    };
    
    
    // @todo : bug
    template<class T>
    struct Sine : public type_tag<T> {
        T operator() (float t, const T& v0, const T& v1) {
            return v0 + (v1- v0) * (cos(t * M_PI_2)) + (v1- v0);
        }
    };
    
    
    // etc function
    template<class T>
    struct Bounce : public type_tag<T> {
        T operator() (float t, const T& v0, const T& v1) {
            for(int a = 0, b = 1; 1; a += b, b /= 2) {
                if (t >= (7 - 4 * a) / 11) {
                    return -powf((float)(11- 6 * a - 11 * t)/ 4, 2.f) + powf((float)(b), 2.f);
                }
            }
        }
    };
    
    template<class T>
    struct BackBow : public type_tag<T> {
        BackBow() : coe_(1.5f) {}
        BackBow(float coe) : coe_(coe) {}
        T operator() (float t, const T& v0, const T& v1) {
            return powf(t, 2.f) * (coe_ + 1.f) * t - coe_;
        }
        float coe_; // coefficient
    };
    
    //
    
    template<class F, class T = typename F::value_type>
    struct ReverseFunc {
        ReverseFunc() {}
        ReverseFunc(F& f) : func(f) {};
        T operator() (float t, const T& v0, const T& v1) {
            return (v0 + v1) - func(1.f - t, v0, v1);
        }
        F   func;
    };
    
    template<class F, class T = typename F::value_type>
    struct InOutFunc {
        InOutFunc() {};
        InOutFunc(F& f) : func(f) {};
        T operator() (float t, const T& v0, const T& v1) {
            if (t < 0.5f) {
                return func(t* 2, v0, v1) * 0.5f;
            } else {
                return (v0 + v1) - func(2* (1.f- t), v0, v1) * 0.5f;
            }
        }
        F   func;
    };
    
    
    
    template<class F>
    ReverseFunc<F> makeReverse(F& func) {
        return ReverseFunc<F>(func);
    }
    
    template<class F>
    InOutFunc<F> makeInOutFunc(F& func) {
        return InOutFunc<F>(func);
    }
    
    
    template<class T>
    struct CatmulRom : public type_tag<T> {
        T operator() (float t, const T& t0, const T& v0, const T& v1, const T& t1) {
            /*
                                            [  0  2  0  0 ]   [t0]
             q(t) = 0.5 * (1, t, tt, ttt) * [ -1  0  1  0 ] * [v0]
                                            [  2 -5  4  0 ]   [v1]
                                            [ -1  3 -3  1 ]   [t0]
             */
            return t0;
        }
    };
    
    
    template<class T>
    struct Bezier : public type_tag<T> {
        T operator() (float t, const T& t0, const T& v0, const T& v1, const T& t1) {
            /*
                                            [ -1  3 -3  1 ]   [t0]
             q(t) = 0.5 * (1, t, tt, ttt) * [  3 -6  3  0 ] * [v0]
                                            [ -3 -3  0  0 ]   [v1]
                                            [  1  0  0  0 ]   [t0]
             
             */
            
            return t0;
        }
    };
    
    
} // Interpolator