#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "Tdd.h"


int quickSortComparator(const void* p1, const void* p2)
{
	 return (*(int*)p1 - *(int*)p2);
}

void printRangesAndReadings(int *buffer, int totalRanges)
{
    int idx = 0;
    while (totalRanges--)
    {
        printf("%i-%i, %i\n", buffer[idx], buffer[idx + 1], buffer[idx + 2]);
        idx = idx + 3;
    }
}

int getRangesAndReadings(int *samples, int sampleSize, int *rangesAndReadingsFound)
{
    int currentRangeMinValue = 0;
    int currentRangeMaxValue = 0;
    int idx = 0;
    int numReadingsFoundInRange = 0;
    int rangeFound = 0;
    int totalRanges = 0;

    qsort(samples, sampleSize, sizeof(int), quickSortComparator);
    for (idx = 0; idx < sampleSize; idx++)
    {
        if (samples[idx] == (samples[idx + 1] - 1))
        {
            if (rangeFound == 0)
            {
                currentRangeMinValue = samples[idx];
                rangeFound = 1;
                numReadingsFoundInRange++;
            }
            currentRangeMaxValue = samples[idx + 1];
            numReadingsFoundInRange++;
        }
        else if (samples[idx] == samples[idx + 1])
        {
            numReadingsFoundInRange++;
        }
        else
        {
            if (rangeFound == 1)
            {
                *rangesAndReadingsFound++ = currentRangeMinValue;
                *rangesAndReadingsFound++ = currentRangeMaxValue;
                *rangesAndReadingsFound++ = numReadingsFoundInRange;
                totalRanges++;
            }
            rangeFound = 0;
            numReadingsFoundInRange = 0;
        }
    }
    return totalRanges;
}

int convert12BitSensorToAmps(int bitValue)
{
    return round((float)(bitValue * 10) / 4094);
}

int convert10BitSensorToAmps(int bitValue)
{
    return round(abs(((float)(bitValue * 30) / 1022) - 15));
}

int get12BitSensorReadingStub(void)
{
    int reading = rand() % 4096;
    if (reading == 4095)
    {
        reading = 0xFFFF;
    }
    return reading;
}

int get10BitSensorReadingStub(void)
{
    int reading = rand() % 1024;
    if (reading == 1023)
    {
        reading = 0xFFFF;
    }
    return reading;
}
