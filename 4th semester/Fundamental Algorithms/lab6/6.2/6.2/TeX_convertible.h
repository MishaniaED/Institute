#pragma once

#include <iostream>
#include <string.h>

class TeX_convertible {

    public:
        virtual std::string convert() const = 0;
};