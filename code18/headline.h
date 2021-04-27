#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <fstream>
#include <ctime>
using namespace std;

#include "speaker.h"
#include "speechManager.h"

//头文件引用一般遇到自己的头文件就不会再往下引用了
//把using namespace std;写在speechManage的头文件前面就不会出错了
//这样speechManager也能引用到标准库