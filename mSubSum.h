#pragma once
#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

int maxSubSum1(const vector<int> &a);

int maxSubSum2(const vector<int> &a);

int maxSumRec(const vector<int> &a, int left, int right);

int maxSubSum3(const vector<int> &a);

int max3(int maxLeft, int maxRight, int maxBorder);

int maxSubSum4(const vector<int> &a);