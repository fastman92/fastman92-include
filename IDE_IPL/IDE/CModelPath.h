/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

namespace File
{
	namespace IDE
	{
		class CModelPath : public CModelBaseInfo
		{
		public:
			// Constructor
			CModelPath() : CModelBaseInfo(SECTION_IDE_PATH) { this->InitValues(); }

			// Clone
			virtual CModelPath* clone() const { return new CModelPath(*this); };

			// Types
			virtual const CModelPath* ToModelPath()    const { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
			virtual CModelPath* ToModelPath() { return this; } ///< Cast to a more defined type. Will return null if not of the requested type.
		};
	}
}