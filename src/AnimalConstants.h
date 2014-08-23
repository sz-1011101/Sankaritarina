#include "AnimalEnumeration.h"

namespace AnimalConstants
{
	//These are the standard values for various animals, look in "AnimalConstants.h" for the meaning of the indices
	static const int ANIMAL_VALUES[AnimalEnumeration::ANIMALS_TOTAL][AnimalEnumeration::ANIMAL_ATTRIBUTES_TOTAL] = {
			{ 16, 8, 10, 5, 1},
			{ 32, 16, 4, 10, 5}
	};
}