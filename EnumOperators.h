/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

#define DEFINE_ENUM_OPERATORS(type) \
		/* Prefix increment */ \
		inline type& operator++(type& game) \
				{ \
			game = static_cast<type>(game + 1); \
			return game; \
				} \
		\
		/* Postfix increment */ \
		inline type operator++(type& game, int) \
				{ \
			type copy = game; \
			++game; \
			return copy; \
				} \
		\
		/* Prefix decrement */ \
		inline type& operator--(type& game) \
				{ \
			game = static_cast<type>(game - 1); \
			return game; \
				} \
		\
		/* Postfix decrement */ \
		inline type operator--(type& game, int) \
				{ \
			type copy = game; \
			--game; \
			return copy; \
				} \
		\
		/* Addition operator */ \
		inline type operator+(const type &first, const int &second) \
		{ \
			return static_cast<type>((int)first + second); \
		} \
		\
		/* Subtraction operator */ \
		inline type operator-(const type &first, const int &second) \
		{ \
			return static_cast<type>((int)first + second); \
		}