/****************************************************************

   Solution : NovaTend

   Project : z-licenseman-01.dll

   Module : LicenseDataDef.h

   Description :  this module defines structure of
                  main license containers

*****************************************************************/

#ifndef LICENSE_DATA_DEF_H
#define LICENSE_DATA_DEF_H

// Values types

// Integer value
#define LPV_TYPE_INTEGER			1

// String value
#define LPV_TYPE_STRING				2

// Datetime value
#define LPV_TYPE_DATETIME			3


// License points types

// The value is checked for an exact match
#define LP_EXACT_MATCH				1

// The value is tested for more or less
#define LP_MORE_LESS				2

// The point stores the specified value
#define LP_SPECIFIED				3


// Value relations types

// Equal
#define REL_TYPE_EQUAL				0

// More
#define REL_TYPE_MORE				1

// Less
#define REL_TYPE_LESS				2


// Restrictions definition

// Values count
#define VALUES_COUNT				256

// Maximum value length
#define MAX_VALUE_LEN				256



// Length of IP address
#define IP_ADDRESS_LEN				16

// Length of domain name
#define DOMAIN_NAME_LEN				64



// License point value descriptor
typedef struct _licensePointValue
{
	// License point value type
	int valueType;
	
	// Value
	char value[MAX_VALUE_LEN];

	// TRUE - if that value is accessible
	bool accessible;

}LICENSE_POINT_VALUE, * PLICENSE_POINT_VALUE;


#endif
