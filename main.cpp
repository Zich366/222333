#include "number.h"
#pragma once
#include <cinttypes>
#include <iostream>

uint2022_t from_uint(uint32_t i){
    uint2022_t number;
    number.digit[0]=i%kBill;
    number.digit[1]=i/kBill;
    return number;
}

uint2022_t from_string(const char* buff){
    uint2022_t p;
    std::string y;
    std::string sub;
    y= std::string(buff);
    uint16_t numbers;
    int k=0;
    numbers = y.length()/kRank+(y.length()%kRank>0);
    if (y.length()<kRank){
        p.digit[0] = std::stoi(y);
    } else {
        for (int i=0;i<numbers-1;++i){
            sub = y.substr(y.length()-kRank*(i+1),kRank);
            k=std::stoi(sub);
            p.digit[i] = k;
        }
        sub = y.substr(0,y.length()-kRank*(numbers-1));
        k=std::stoi(sub);
        p.digit[numbers-1] = k;
    }
    return p;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs){
    uint2022_t p;
    uint8_t k=0;
    for (int i=0;i<kSize;++i){
        p.digit[i]=(lhs.digit[i]+rhs.digit[i]+k)%kBill;
        k=0;
        if (lhs.digit[i]+rhs.digit[i]>kBill){
            k=1;
        }
    }
    return p;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs){
    uint2022_t p;
    uint32_t k=0;
    for (uint32_t i=0;i<kSize;++i){
        p.digit[i]=(lhs.digit[i]-rhs.digit[i]-k+kBill)%kBill;
        k=0;
        if (lhs.digit[i]<rhs.digit[i]){
            k=1;
        }
    }
    return p;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs){
    uint2022_t p,q;
    uint64_t c;
    uint8_t l=0;
    uint8_t r=0;
    std::string s;
    const char* s1;
    p = from_uint(0);
    for (int i = kSize-1; i>=0; --i) {
        if (lhs.digit[i]>0){
            l=i;
            break;
        }
    }
    for (int i = kSize-1; i>=0; --i) {
        if (rhs.digit[i]>0){
            r=i;
            break;
        }
    }

    if (l+r<=kSize){
        for (int i=0;i<=l;++i){
            for (int j=0;j<=r;++j){
                c = (uint64_t)lhs.digit[i]*(uint64_t)rhs.digit[j];
                s = std::to_string(c);
                for (int k=0; k<i+j;++k){
                    s = s + "000000000";
                }
                s1 = s.c_str();
                q = from_string(s1);
                p = p + q;
            }
        }
    }
    return p;
};
bool operator<(const uint2022_t& lhs, const uint2022_t& rhs){
    bool t = true;
    for (int i=kSize-1;i>=0;--i){
        if (lhs.digit[i]>rhs.digit[i]){
            t = false;
            break;
        } else if (lhs.digit[i]<rhs.digit[i]) {
            t = true;
            break;
        }
    }
    return t;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs){
    uint2022_t rrhs,delitel,delimoe,result,preresult,ten;
    const char* s;
    std::string q;
    uint16_t k = 0;
    uint16_t y = 0;
    ten = from_uint(10);
    delimoe = lhs;
    while (true){
        y = 0;
        k = 0;
        delitel = rhs;

        if (delimoe<delitel){
            break;
        }

        for (int i = 0; i < 609; ++i) {
            rrhs = delitel * ten;
            if (rrhs < delimoe) {
                delitel = rrhs;
                ++y;
            } else {
                break;
            }
        }
        for (int i=0;i<9;++i){
            if (delitel < delimoe) {
                delimoe = delimoe - delitel;
                ++k;
            } else {
                break;
            }
        }
        q = std::to_string(k);
        for (int i = 0; i < y; ++i) {
            q = q + "0";
        }

        s = q.c_str();
        preresult = from_string(s);
        result = result + preresult;
    }
    return result;
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs){
    bool k = true;
    for (uint32_t i=0;i<kSize;++i){
        if (lhs.digit[i]!=rhs.digit[i]){
            k = false;
        }
    }
    return k;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs){
    bool k = false;
    for (uint32_t i=0;i<kSize;++i){
        if (lhs.digit[i]!=rhs.digit[i]){
            k = true;
        }
    }
    return k;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value){
    std::string y;
    int k = 0;
    for (int i=kSize-1;i>=0;--i) {
        if (value.digit[i]>0){
            k=i;
            break;
        }
    }
    stream<<value.digit[k];
    for (int i=k-1;i>=0;--i){
        y=std::to_string(value.digit[i]);
        if (value.digit[i]==0){
            stream<<"000000000";
        } else {
            for (uint32_t j = 0; j < kRank - y.length(); ++j) {
                stream << "0";
            }
            stream<<value.digit[i];
        }

    }

}
int main(){

}