//
// Created by secon on 2024/11/21.
//

#include "WrapperC.h"

std::ostream& operator << (std::ostream &out, const DefaultClass &defaultClass) {
    out << "DefaultClass num is " << defaultClass._num << std::endl;
    return out;
}