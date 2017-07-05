#include "RNDSeeder.h"
#include "DBGDebug.h"
#include <ctime>
#include <cmath>



using namespace std;



double RNDSeeder::generateSeed(int sources){
	double sourceSum   = 0.0;
	int    sourceCount = 0;

	if(GENERATION_OF_1000 & sources){
		static int   generationCount          = 500;
		const int    GENERATION_COUNT_MODULUS = 1000;
		const double SOURCE                   = double(generationCount) / double(GENERATION_COUNT_MODULUS);
		DBGAssert((0.0 <= SOURCE) && (SOURCE < 1.0));
		sourceSum       = sourceSum + SOURCE;
		generationCount = (generationCount + 1) % GENERATION_COUNT_MODULUS;
		sourceCount++;
	}

	if(FRACTION_OF_SECOND & sources){
		const time_t CLOCK            = clock();
		if(CLOCK < 0){
			DBGError("CPU clock not available.");
		}
		const double CLOCK_OF_SECOND  = double(CLOCK % CLOCKS_PER_SEC);
		const double CLOCKS_IN_SECOND = double(CLOCKS_PER_SEC);
		const double SOURCE           = CLOCK_OF_SECOND / CLOCKS_IN_SECOND;
		DBGAssert((0.0 <= SOURCE) && (SOURCE < 1.0));
		sourceSum = sourceSum + SOURCE;
		sourceCount++;
	}

	const bool localTimeUsed = 
		0 != 
		(
		sources &
		(
		SECOND_OF_MINUTE |
		MINUTE_OF_HOUR |
		HOUR_OF_DAY |
		DAY_OF_WEEK |
		DAY_OF_MONTH |
		DAY_OF_YEAR |
		MONTH_OF_YEAR |
		YEAR_OF_DECENNIUM
		)
		);
	if(localTimeUsed){
		const time_t TIME              = time(NULL);
		const tm     *localTimePointer = localtime(&TIME);
		if(NULL == localTimePointer){
			DBGError("Time not available.");
		}
		const tm localTime = *localTimePointer;

		if(SECOND_OF_MINUTE & sources){
			const int    SECONDS_IN_MINUTE = 60;
			const int    SECOND_OF_MINUTE  = (localTime.tm_sec % SECONDS_IN_MINUTE);
			const double SOURCE            = double(SECOND_OF_MINUTE) / double(SECONDS_IN_MINUTE);
			DBGAssert((0.0 <= SOURCE) && (SOURCE < 1.0));
			sourceSum = sourceSum + SOURCE;
			sourceCount++;		
		}

		if(MINUTE_OF_HOUR & sources){
			const int    MINUTES_IN_HOUR = 60;
			const int    MINUTE_OF_HOUR  = (localTime.tm_min % MINUTES_IN_HOUR);
			const double SOURCE          = double(MINUTE_OF_HOUR) / double(MINUTES_IN_HOUR);
			DBGAssert((0.0 <= SOURCE) && (SOURCE < 1.0));
			sourceSum = sourceSum + SOURCE;
			sourceCount++;		
		}

		if(HOUR_OF_DAY & sources){
			const int    HOURS_IN_DAY = 24;
			const int    HOUR_OF_DAY  = (localTime.tm_hour % HOURS_IN_DAY);
			const double SOURCE       = double(HOUR_OF_DAY) / double(HOURS_IN_DAY);
			DBGAssert((0.0 <= SOURCE) && (SOURCE < 1.0));
			sourceSum = sourceSum + SOURCE;
			sourceCount++;		
		}

		if(DAY_OF_WEEK & sources){
			const int    DAYS_IN_WEEK = 7;
			const int    DAY_OF_WEEK  = (localTime.tm_wday % DAYS_IN_WEEK);
			const double SOURCE       = double(DAY_OF_WEEK) / double(DAYS_IN_WEEK);
			DBGAssert((0.0 <= SOURCE) && (SOURCE < 1.0));
			sourceSum = sourceSum + SOURCE;
			sourceCount++;		
		}

		if(DAY_OF_MONTH & sources){
			const int    MAX_DAYS_IN_MONTH = 31;
			const int    DAY_OF_MONTH      = (localTime.tm_mday % MAX_DAYS_IN_MONTH);
			const double SOURCE            = double(DAY_OF_MONTH) / double(MAX_DAYS_IN_MONTH);
			DBGAssert((0.0 <= SOURCE) && (SOURCE < 1.0));
			sourceSum = sourceSum + SOURCE;
			sourceCount++;		
		}

		if(DAY_OF_YEAR & sources){
			const int    MAX_DAYS_IN_YEAR = 366;
			const int    DAY_OF_YEAR      = (localTime.tm_yday % MAX_DAYS_IN_YEAR);
			const double SOURCE           = double(DAY_OF_YEAR) / double(MAX_DAYS_IN_YEAR);
			DBGAssert((0.0 <= SOURCE) && (SOURCE < 1.0));
			sourceSum = sourceSum + SOURCE;
			sourceCount++;		
		}

		if(MONTH_OF_YEAR & sources){
			const int    MONTHS_IN_YEAR = 12;
			const int    MONTH_OF_YEAR  = (localTime.tm_mon % MONTHS_IN_YEAR);
			const double SOURCE         = double(MONTH_OF_YEAR) / double(MONTHS_IN_YEAR);
			DBGAssert((0.0 <= SOURCE) && (SOURCE < 1.0));
			sourceSum = sourceSum + SOURCE;
			sourceCount++;		
		}

		if(YEAR_OF_DECENNIUM & sources){
			const int    YEARS_IN_DECENNIUM = 10;
			const int    YEAR_OF_DECENNIUM  = (localTime.tm_year % YEARS_IN_DECENNIUM);
			const double SOURCE             = double(YEAR_OF_DECENNIUM) / double(YEARS_IN_DECENNIUM);
			DBGAssert((0.0 <= SOURCE) && (SOURCE < 1.0));
			sourceSum = sourceSum + SOURCE;
			sourceCount++;		
		}
	}

	double seed = 0.0;
	if(0 < sourceCount){
		seed = sourceSum / sourceCount;	
	}
	DBGAssert((0.0 <= seed) && (seed <= 1.0));
	return seed;
}