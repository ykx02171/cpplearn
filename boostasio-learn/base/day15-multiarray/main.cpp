#include <iostream>

int main() {
    {
        //数组长度为3，它的每一个元素是长度为4的int类型数组
        int ia[3][4] = {
                //第一行的初始值
                {0, 1, 2, 3},
                //第二行初始值
                {4, 5, 6, 7},
                //第三行初始值
                {8, 9, 10, 11}
        };
    }

    {
        int ia[3][4] = {0, 1, 2, 3, 4, 5,
                        6, 7, 8, 9, 10, 11};
        //初始化每一行的首元素
        int ia2[3][4] = {{0},
                         {4},
                         {8}};
        //值初始化第一i行
        int ix[3][4] = {0, 3, 5, 9};
    }

    {
        int ia[3][4] = {{1, 2,  3,  4},
                        {5, 6,  7,  8},
                        {9, 10, 11, 12}};
        int arr[1][1][1] = {{{1}}};
        // 用arr的首元素为ia的最后一个元素赋值
        ia[2][3] = arr[0][0][0];
        //row是一个4维数组的引用,将row绑定到ia的第二个元素(4维数组)上
        int (&row)[4] = ia[1];
    }

    {
        constexpr size_t rowCnt = 3, colCnt = 4;
        //12 个未初始化的元素
        int ia[rowCnt][colCnt];
        //对于每一行
        for (size_t i = 0; i != rowCnt; ++i) {
            //对于行内的每一列
            for (size_t j = 0; j != colCnt; ++j) {
                ia[i][j] = i * colCnt + j;
            }
        }
    }

    {
        constexpr size_t rowCnt = 3, colCnt = 4;
        //12 个未初始化的元素
        int ia[rowCnt][colCnt];
        size_t cnt = 0;
        for (auto &row: ia) {
            for (auto &col: row) {
                col = cnt;
                ++cnt;
            }
        }

        for (const auto &row: ia) {
            for (auto col: row) {
                std::cout << col << " ";
            }
            std::cout << std::endl;
        }
    }

    {
        //大小为3的数组，每个元素是含有4个整数的数组
        int ia[3][4];
        //p指向含有4个整数的数组
        int(*p)[4] = ia;
        //将p修改为指向ia数组的尾部
        p = &ia[2];
    }

    {
        // ia数组
        int ia[3][4] = {{1, 2,  3,  4},
                        {5, 6,  7,  8},
                        {9, 10, 11, 12}};
        //输出ia中每个元素的值,每个内存数组各占一行
        //p指向含有4个整数的数组
        for (auto p = ia; p != ia + 3; ++p) {
            //q指向4个整数的数组的首元素
            for (auto q = *p; q != *p + 4; ++q) {
                std::cout << *q << ' ';
            }
            std::cout << std::endl;
        }
    }

    {
        // ia数组
        int ia[3][4] = {{1, 2,  3,  4},
                        {5, 6,  7,  8},
                        {9, 10, 11, 12}};

        // p指向ia的第一个数组
        for (auto p = std::begin(ia); p != std::end(ia); ++p) {
            // q指向内存数组的首元素
            for (auto q = std::begin(*p); q != std::end(*p); ++q) {
                // 输出q所指的整数值
                std::cout << *q << ' ';
            }
            std::cout << std::endl;
        }
    }

    {
        // ia数组
        int ia[3][4] = {{1, 2,  3,  4},
                        {5, 6,  7,  8},
                        {9, 10, 11, 12}};

        using int_array = int[4];
        typedef int int_array_t[4];

        for (int_array_t *p = ia; p != ia + 3; ++p) {
            for (int *q = *p; q != *p + 4; ++q) {
                std::cout << *q << " ";
            }

            std::cout << std::endl;
        }

        for (int_array_t *p = ia; p != ia + 3; ++p) {
            for (int *q = *p; q != *p + 4; ++q) {
                std::cout << *q << " ";
            }

            std::cout << std::endl;
        }


    }

    return 0;
}
