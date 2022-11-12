//! \brief A more generic binary search using C++ templates and iterators
//! \param begin Iterator pointing to the first element
//! \param end Iterator pointing to one past the last element
//! \param key The value to be searched for
//! \return An iterator pointing to the location of the value in the given
//! vector, or one past the end if the value was not found.
template<typename Iterator, typename T, typename _Pr>
Iterator find_iterator_binary_search(Iterator& begin, Iterator& end, const T& key, _Pr _Pred)
{
	// Keep halving the search space until we reach the end of the vector
	const Iterator NotFound = end;

	while (begin < end)
	{
		// Find the median value between the iterators
		const Iterator Middle = begin + (std::distance(begin, end) / 2);

		// Re-adjust the iterators based on the median value
		if (_Pred(*Middle, key))
			begin = Middle + 1;
		else if (_Pred(key, *Middle))
			end = Middle;
		else
			return Middle;
		/*
		if (*Middle == key)
			return Middle;
		else if (*Middle > key)
			end = Middle;
		else
			begin = Middle + 1;
		*/
	}

	return NotFound;
}