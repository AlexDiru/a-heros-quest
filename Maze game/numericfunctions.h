//===================================
//include guard
#ifndef NUMERICFUNCTIONS_H
#define NUMERICFUNCTIONS_H

//this function is to average the levels
template <class T>
T getAverage(T *arr, int size)
{
	T sum = 0;
	//use a pointer for array access
	for (T *i = &arr[0]; i<(arr+size);i++)
		sum += *i;
	return sum/size;
}

//this function rounds a number to the nearest integer
template <class T>
int round(T num)
{
	float ceilNum = (int)num;
	
	if (num < ceilNum + 0.5)
		return (int)num;
	else
		return (int)num+1;
}

#endif