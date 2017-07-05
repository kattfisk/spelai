#ifndef INCLUDED_RNDSEEDER
#define INCLUDED_RNDSEEDER




/******************************************************************************

This component implements a function computeSeed() that is used to compute
seed values in the range [0.0, 1.0]. 

The seed value depends on one or more sources (combined by bitwise or) as
defined below. Combination is achieved by computing the average of each 
individual source. 

For example this function can be used too generate a seed that is unique for
each day of the year (DAY_OF_YEAR). That is, each call to the generation
function will give the same seed during the same day but different seeds are
generated on different days.

*******************************************************************************/




struct RNDSeeder{
	
	/* public data */
	static const int GENERATION_OF_1000 = 0x00000001; 
	static const int FRACTION_OF_SECOND = 0x00000002;
	static const int SECOND_OF_MINUTE   = 0x00000004;
	static const int MINUTE_OF_HOUR     = 0x00000008;
	static const int HOUR_OF_DAY        = 0x00000010;
	static const int DAY_OF_WEEK        = 0x00000020;
	static const int DAY_OF_MONTH       = 0x00000040;
	static const int DAY_OF_YEAR        = 0x00000080;
	static const int MONTH_OF_YEAR      = 0x00000100;
	static const int YEAR_OF_DECENNIUM  = 0x00000200;
	static const int ALL_SOURCES        = 0x000003ff;  //Combines all sources by computing their average

	/* Public functions */
	static double generateSeed(int sources);
};



#endif