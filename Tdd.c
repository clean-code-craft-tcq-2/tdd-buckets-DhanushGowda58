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

int main() 
{
    // Test 1: Smallest possible test 
    int chargingSamples[] = {4,5};
    int rangesAndReadings[MAX_NUMBER_OF_RANGES_AND_READINGS];
    int rangesFound = 0;
    rangesFound = getRangesAndReadings(chargingSamples, sizeof(chargingSamples)/sizeof(int), rangesAndReadings);
    assert(rangesFound == 1);
    assert(rangesAndReadings[0] == 4);
    assert(rangesAndReadings[1] == 5);
    assert(rangesAndReadings[2] == 2);

    printRangesAndReadings(rangesAndReadings, rangesFound);

    // Test 2: Multiple continuous numbers 
    int chargingSamples2[] = {1,2,3,4,5,6,7,8,9,10};
    int rangesAndReadings2[MAX_NUMBER_OF_RANGES_AND_READINGS];

    rangesFound = getRangesAndReadings(chargingSamples2, sizeof(chargingSamples2)/sizeof(int), rangesAndReadings2);
    assert(rangesFound == 1);
    assert(rangesAndReadings2[0] == 1);
    assert(rangesAndReadings2[1] == 10);
    assert(rangesAndReadings2[2] == 10);

    printRangesAndReadings(rangesAndReadings2, rangesFound);

    // Test 3: Multiple uncontinuous numbers 
    int chargingSamples3[] = {3,7,1,10,2,4,9,6,5,8};
    int rangesAndReadings3[MAX_NUMBER_OF_RANGES_AND_READINGS];

    rangesFound = getRangesAndReadings(chargingSamples3, sizeof(chargingSamples3)/sizeof(int), rangesAndReadings3);
    assert(rangesFound == 1);
    assert(rangesAndReadings3[0] == 1);
    assert(rangesAndReadings3[1] == 10);
    assert(rangesAndReadings3[2] == 10);

    printRangesAndReadings(rangesAndReadings3, rangesFound);

    // Test 4: Multiple ranges
    int chargingSamples4[] = {1,22,3,4,11,23,14,2,13,12,21,24};
    int rangesAndReadings4[MAX_NUMBER_OF_RANGES_AND_READINGS];

    rangesFound = getRangesAndReadings(chargingSamples4, sizeof(chargingSamples4)/sizeof(int), rangesAndReadings4);
    assert(rangesFound == 3);
    assert(rangesAndReadings4[0] == 1);
    assert(rangesAndReadings4[1] == 4);
    assert(rangesAndReadings4[2] == 4);
    assert(rangesAndReadings4[3] == 11);
    assert(rangesAndReadings4[4] == 14);
    assert(rangesAndReadings4[5] == 4);
    assert(rangesAndReadings4[6] == 21);
    assert(rangesAndReadings4[7] == 24);
    assert(rangesAndReadings4[8] == 4);

    printRangesAndReadings(rangesAndReadings4, rangesFound);

    // Test 5: Repeated numbers
    int chargingSamples5[] = {1,2,3,3,3,4,5,20,20,20,20,8,9,9};
    int rangesAndReadings5[MAX_NUMBER_OF_RANGES_AND_READINGS];

    rangesFound = getRangesAndReadings(chargingSamples5, sizeof(chargingSamples5)/sizeof(int), rangesAndReadings5);
    assert(rangesFound == 2);
    assert(rangesAndReadings5[0] == 1);
    assert(rangesAndReadings5[1] == 5);
    assert(rangesAndReadings5[2] == 7);
    assert(rangesAndReadings5[3] == 8);
    assert(rangesAndReadings5[4] == 9);
    assert(rangesAndReadings5[5] == 3);

    printRangesAndReadings(rangesAndReadings5, rangesFound);

    // Test 6: No ranges
    int chargingSamples6[] = {3,3,3,3,3,3,3,3,3,3,5,5,5,5,5};
    int rangesAndReadings6[MAX_NUMBER_OF_RANGES_AND_READINGS];

    rangesFound = getRangesAndReadings(chargingSamples6, sizeof(chargingSamples6)/sizeof(int), rangesAndReadings6);
    assert(rangesFound == 0);

    printRangesAndReadings(rangesAndReadings6, rangesFound);

    // Test Driven Extensions
    int result = 0;

    // Test 1: Test 12-bit conversion
    result = convert12BitSensorToAmps(4094);
    assert(result == 10);
    result = convert12BitSensorToAmps(0);
    assert(result == 0);
    result = convert12BitSensorToAmps(1000);
    assert(result == 2);
    result = convert12BitSensorToAmps(2000);
    assert(result == 5);
    result = convert12BitSensorToAmps(3000);
    assert(result == 7);

    // Test 2: Test 10-bit conversion
    result = convert10BitSensorToAmps(1022);
    assert(result == 15);
    result = convert10BitSensorToAmps(0);
    assert(result == 15);
    result = convert10BitSensorToAmps(300);
    assert(result == 6);
    result = convert10BitSensorToAmps(500);
    assert(result == 0);
    result = convert10BitSensorToAmps(750);
    assert(result == 7);

    // Test 3: Integrate 12-bit sensor readings into previous implementation
    printf("> Test 3: Integrate 12-bit sensor readings into previous implementation\n");
    int chargingSamples7[10] = {100, 400, 700, 2500, 2100, 1800, 4094, 3850, 1, 0};
    int rangesAndReadings7[MAX_NUMBER_OF_RANGES_AND_READINGS];
    int i;

    for (i = 0; i < 10; i++)
    {
        chargingSamples7[i] = convert12BitSensorToAmps(chargingSamples7[i]);
    }

    rangesFound = getRangesAndReadings(chargingSamples7, sizeof(chargingSamples7)/sizeof(int), rangesAndReadings7);
    assert(rangesFound == 3);
    assert(rangesAndReadings7[0] == 0);
    assert(rangesAndReadings7[1] == 2);
    assert(rangesAndReadings7[2] == 5);
    assert(rangesAndReadings7[3] == 4);
    assert(rangesAndReadings7[4] == 6);
    assert(rangesAndReadings7[5] == 3);
    assert(rangesAndReadings7[6] == 9);
    assert(rangesAndReadings7[7] == 10);
    assert(rangesAndReadings7[8] == 2);

    printRangesAndReadings(rangesAndReadings7, rangesFound);

    // Test 4: Integrate 10-bit sensor readings into previous implementation
    printf("> Test 3: Integrate 10-bit sensor readings into previous implementation\n");
    int chargingSamples8[10] = {1000, 500, 100, 200, 150, 300, 0, 0, 550, 950};
    int rangesAndReadings8[MAX_NUMBER_OF_RANGES_AND_READINGS];

    for (i = 0; i < 10; i++)
    {
        chargingSamples8[i] = convert10BitSensorToAmps(chargingSamples8[i]);
    }

    rangesFound = getRangesAndReadings(chargingSamples8, sizeof(chargingSamples8)/sizeof(int), rangesAndReadings8);
    assert(rangesFound == 3);
    assert(rangesAndReadings8[0] == 0);
    assert(rangesAndReadings8[1] == 1);
    assert(rangesAndReadings8[2] == 2);
    assert(rangesAndReadings8[3] == 9);
    assert(rangesAndReadings8[4] == 10);
    assert(rangesAndReadings8[5] == 2);
    assert(rangesAndReadings8[6] == 14);
    assert(rangesAndReadings8[7] == 15);
    assert(rangesAndReadings8[8] == 3);

    printRangesAndReadings(rangesAndReadings8, rangesFound);

    // Test 5: Try randomized 12-bit sensor readings (test 3 times)
    printf("> Test 5: Try randomized 12-bit sensor readings (test 3 times)\n");
    int chargingSamples9[10];
    int rangesAndReadings9[MAX_NUMBER_OF_RANGES_AND_READINGS];
    int j;
    srand(time(NULL));

    for (i = 0; i < 3; i++)
    {
        printf("> Test 5: Attempt #%i\n", i + 1);
        for (j = 0; j < 10; j++)
        {
            chargingSamples9[j] = get12BitSensorReadingStub();
            printf("%i-", chargingSamples9[j]);
            chargingSamples9[j] = convert12BitSensorToAmps(chargingSamples9[j]);
            printf("%i, ", chargingSamples9[j]);
        }
        printf("\n");
        rangesFound = getRangesAndReadings(chargingSamples9, sizeof(chargingSamples9)/sizeof(int), rangesAndReadings9);
        printRangesAndReadings(rangesAndReadings9, rangesFound);
    }

    // Test 6: Try randomized 10-bit sensor readings (test 3 times)
    printf("> Test 6: Try randomized 10-bit sensor readings (test 3 times)\n");
    for (i = 0; i < 3; i++)
    {
        printf("> Test 6: Attempt #%i\n", i + 1);
        for (j = 0; j < 10; j++)
        {
            chargingSamples9[j] = get12BitSensorReadingStub();
            printf("%i-", chargingSamples9[j]);
            chargingSamples9[j] = convert12BitSensorToAmps(chargingSamples9[j]);
            printf("%i, ", chargingSamples9[j]);
        }
        printf("\n");
        rangesFound = getRangesAndReadings(chargingSamples9, sizeof(chargingSamples9)/sizeof(int), rangesAndReadings9);
        printRangesAndReadings(rangesAndReadings9, rangesFound);
    }

   return 0;
}
