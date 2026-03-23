//
// Created by secon on 2024/9/21.
//

#ifndef DAY08_CONST_GLOBAL_H
#define DAY08_CONST_GLOBAL_H
const int bufSize = 100;
extern const int bufSize2;
//打印bufSize地址和bufSize2地址
extern void PrintBufAddress();
extern int GetSize();
inline constexpr int GetSizeConst() {
    return 1;
}
#endif //DAY08_CONST_GLOBAL_H
