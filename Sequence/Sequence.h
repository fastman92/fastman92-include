/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include <vector>

// Returns a container with the sequence of items
template<typename T>
std::vector<T> sequence(T v) {
	std::vector<T> vec;
	vec.push_back(v);
	return vec;
}

template<typename T, typename... Args>
std::vector<T> sequence(T first, Args... args) {
	std::vector<T> vec;
	vec = sequence(args...);

	vec.insert(vec.begin(), first);

	return vec;
}