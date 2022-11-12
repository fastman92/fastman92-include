/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once
#include "../eGame.h"

#include "../SectionFile/CSectionFileReaderEx.h"

namespace File
{

	template <class Treader> class IPLorIDEfileReaderEx : public Treader
	{
	public:

		// Updates all lines
		virtual void cUpdateAllLines()
		{
			this->Treader::UpdateAllLines();
		}
	};
}