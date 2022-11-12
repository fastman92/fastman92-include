#include "CSarrus.h"

float CSarrus::GetDeterminant(
	const CVector& a,
	const CVector& b,
	const CVector& c)
{
	// Set up variables
	float a11 = a.x;
	float a12 = a.y;
	float a13 = a.z;

	float a21 = b.x;
	float a22 = b.y;
	float a23 = b.z;

	float a31 = c.x;
	float a32 = c.y;
	float a33 = c.z;

	return
		
		(a11 * a22 * a33
			+ a12 * a23 * a31
			+ a13 * a21 * a32)
		-
			
		(a13 * a22 * a31
		+ a11 * a23 * a32
		+ a12 * a21 * a33);
}