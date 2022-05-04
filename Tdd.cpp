#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "Tdd.h"

TEST_CASE("Test 1: Smallest possible test ")
{
    int chargingSamples[] = {4,5};
    int rangesAndReadings[MAX_NUMBER_OF_RANGES_AND_READINGS];
    int rangesFound = 0;
    rangesFound = getRangesAndReadings(chargingSamples, sizeof(chargingSamples)/sizeof(int), rangesAndReadings);
    REQUIRE(rangesFound == 1);
    REQUIRE(rangesAndReadings[0] == 4);
    REQUIRE(rangesAndReadings[1] == 5);
    REQUIRE(rangesAndReadings[2] == 2);

    printRangesAndReadings(rangesAndReadings, rangesFound);
}

TEST_CASE("Test 2: Multiple continuous numbers")
{
    int chargingSamples[] = {1,2,3,4,5,6,7,8,9,10};
    int rangesAndReadings[MAX_NUMBER_OF_RANGES_AND_READINGS];
    int rangesFound = 0;

    rangesFound = getRangesAndReadings(chargingSamples, sizeof(chargingSamples)/sizeof(int), rangesAndReadings);
    REQUIRE(rangesFound == 1);
    REQUIRE(rangesAndReadings[0] == 1);
    REQUIRE(rangesAndReadings[1] == 10);
    REQUIRE(rangesAndReadings[2] == 10);

    printRangesAndReadings(rangesAndReadings, rangesFound);
}

TEST_CASE("Test 3: Multiple uncontinuous numbers ")
{
    int chargingSamples[] = {3,7,1,10,2,4,9,6,5,8};
    int rangesAndReadings[MAX_NUMBER_OF_RANGES_AND_READINGS];
    int rangesFound = 0;

    rangesFound = getRangesAndReadings(chargingSamples, sizeof(chargingSamples)/sizeof(int), rangesAndReadings);
    REQUIRE(rangesFound == 1);
    REQUIRE(rangesAndReadings[0] == 1);
    REQUIRE(rangesAndReadings[1] == 10);
    REQUIRE(rangesAndReadings[2] == 10);

    printRangesAndReadings(rangesAndReadings, rangesFound);
}

TEST_CASE("Test 4: Multiple ranges")
{
    int chargingSamples[] = {1,22,3,4,11,23,14,2,13,12,21,24};
    int rangesAndReadings[MAX_NUMBER_OF_RANGES_AND_READINGS];
    int rangesFound = 0;

    rangesFound = getRangesAndReadings(chargingSamples, sizeof(chargingSamples)/sizeof(int), rangesAndReadings);
    REQUIRE(rangesFound == 3);
    REQUIRE(rangesAndReadings[0] == 1);
    REQUIRE(rangesAndReadings[1] == 4);
    REQUIRE(rangesAndReadings[2] == 4);
    REQUIRE(rangesAndReadings[3] == 11);
    REQUIRE(rangesAndReadings[4] == 14);
    REQUIRE(rangesAndReadings[5] == 4);
    REQUIRE(rangesAndReadings[6] == 21);
    REQUIRE(rangesAndReadings[7] == 24);
    REQUIRE(rangesAndReadings[8] == 4);

    printRangesAndReadings(rangesAndReadings, rangesFound);
}

TEST_CASE("Test 5: Repeated numbers")
{
    int chargingSamples[] = {1,2,3,3,3,4,5,20,20,20,20,8,9,9};
    int rangesAndReadings[MAX_NUMBER_OF_RANGES_AND_READINGS];
    int rangesFound = 0;

    rangesFound = getRangesAndReadings(chargingSamples, sizeof(chargingSamples)/sizeof(int), rangesAndReadings);
    REQUIRE(rangesFound == 2);
    REQUIRE(rangesAndReadings[0] == 1);
    REQUIRE(rangesAndReadings[1] == 5);
    REQUIRE(rangesAndReadings[2] == 7);
    REQUIRE(rangesAndReadings[3] == 8);
    REQUIRE(rangesAndReadings[4] == 9);
    REQUIRE(rangesAndReadings[5] == 3);

    printRangesAndReadings(rangesAndReadings, rangesFound);
}

TEST_CASE("Test 6: No ranges")
{
    int chargingSamples[] = {3,3,3,3,3,3,3,3,3,3,5,5,5,5,5};
    int rangesAndReadings[MAX_NUMBER_OF_RANGES_AND_READINGS];
    int rangesFound = 0;

    rangesFound = getRangesAndReadings(chargingSamples, sizeof(chargingSamples)/sizeof(int), rangesAndReadings);
    REQUIRE(rangesFound == 0);

    printRangesAndReadings(rangesAndReadings, rangesFound);
}

// Test Driven Extensions
TEST_CASE("Test 1: Test 12-bit conversion")
{
    int result = 0;
    result = convert12BitSensorToAmps(4094);
    REQUIRE(result == 10);
    result = convert12BitSensorToAmps(0);
    REQUIRE(result == 0);
    result = convert12BitSensorToAmps(1000);
    REQUIRE(result == 2);
    result = convert12BitSensorToAmps(2000);
    REQUIRE(result == 5);
    result = convert12BitSensorToAmps(3000);
    REQUIRE(result == 7);
}

TEST_CASE("Test 2: Test 10-bit conversion")
{
    int result = 0;
    result = convert10BitSensorToAmps(1022);
    REQUIRE(result == 15);
    result = convert10BitSensorToAmps(0);
    REQUIRE(result == 15);
    result = convert10BitSensorToAmps(300);
    REQUIRE(result == 6);
    result = convert10BitSensorToAmps(500);
    REQUIRE(result == 0);
    result = convert10BitSensorToAmps(750);
    REQUIRE(result == 7);
}

TEST_CASE("Test 3: Integrate 12-bit sensor readings into previous implementation")
{
    printf("> Test 3: Integrate 12-bit sensor readings into previous implementation\n");
    int chargingSamples[11] = {100, 400, 700, 2500, 2100, 1800, 4094, 3850, 1, 0, 100};
    int rangesAndReadings[MAX_NUMBER_OF_RANGES_AND_READINGS];
    int i;
    int rangesFound = 0;

    for (i = 0; i < 11; i++)
    {
        chargingSamples[i] = convert12BitSensorToAmps(chargingSamples[i]);
    }

    rangesFound = getRangesAndReadings(chargingSamples, sizeof(chargingSamples)/sizeof(int), rangesAndReadings);
    REQUIRE(rangesFound == 3);
    REQUIRE(rangesAndReadings[0] == 0);
    REQUIRE(rangesAndReadings[1] == 2);
    REQUIRE(rangesAndReadings[2] == 6);
    REQUIRE(rangesAndReadings[3] == 4);
    REQUIRE(rangesAndReadings[4] == 6);
    REQUIRE(rangesAndReadings[5] == 3);
    REQUIRE(rangesAndReadings[6] == 9);
    REQUIRE(rangesAndReadings[7] == 10);
    REQUIRE(rangesAndReadings[8] == 2);

    printRangesAndReadings(rangesAndReadings, rangesFound);
}

TEST_CASE("Test 4: Integrate 10-bit sensor readings into previous implementation")
{
    printf("> Test 4: Integrate 10-bit sensor readings into previous implementation\n");
    int chargingSamples[18] = {1000, 500, 100, 200, 150, 300, 0, 950, 550, 960, 600, 650, 700, 750, 800, 400, 450, 400};
    int rangesAndReadings[MAX_NUMBER_OF_RANGES_AND_READINGS];
    int i;
    int rangesFound = 0;

    for (i = 0; i < 18; i++)
    {
        chargingSamples[i] = convert10BitSensorToAmps(chargingSamples[i]);
    }

    rangesFound = getRangesAndReadings(chargingSamples, sizeof(chargingSamples)/sizeof(int), rangesAndReadings);
    REQUIRE(rangesFound == 3);
    REQUIRE(rangesAndReadings[0] == 0);
    REQUIRE(rangesAndReadings[1] == 4);
    REQUIRE(rangesAndReadings[2] == 7);
    REQUIRE(rangesAndReadings[3] == 6);
    REQUIRE(rangesAndReadings[4] == 9);
    REQUIRE(rangesAndReadings[5] == 5);
    REQUIRE(rangesAndReadings[6] == 11);
    REQUIRE(rangesAndReadings[7] == 15);
    REQUIRE(rangesAndReadings[8] == 6);

    printRangesAndReadings(rangesAndReadings, rangesFound);
}

TEST_CASE("Test 5: Try randomized 12-bit sensor readings (test 3 times)")
{
    printf("> Test 5: Try randomized 12-bit sensor readings (test 3 times)\n");
    int chargingSamples[10];
    int rangesAndReadings[MAX_NUMBER_OF_RANGES_AND_READINGS];
    int j;
    int i;
    int rangesFound = 0;
    srand(time(NULL));

    for (i = 0; i < 3; i++)
    {
        printf("> Test 5: Attempt #%i\n", i + 1);
        for (j = 0; j < 10; j++)
        {
            chargingSamples[j] = get12BitSensorReadingStub();
            if (chargingSamples[j] == 0xFFFF)
            {
                printf("Invalid reading found, ", chargingSamples[j]);
            }
            else
            {
                printf("%i-", chargingSamples[j]);
                chargingSamples[j] = convert12BitSensorToAmps(chargingSamples[j]);
                printf("%i, ", chargingSamples[j]);
            }
        }
        printf("\n");
        rangesFound = getRangesAndReadings(chargingSamples, sizeof(chargingSamples)/sizeof(int), rangesAndReadings);
        printRangesAndReadings(rangesAndReadings, rangesFound);
    }
}

TEST_CASE("Test 6: Try randomized 10-bit sensor readings (test 3 times)")
{
    printf("> Test 6: Try randomized 10-bit sensor readings (test 3 times)\n");
    int chargingSamples[10];
    int rangesAndReadings[MAX_NUMBER_OF_RANGES_AND_READINGS];
    int j;
    int i;
    int rangesFound = 0;
    srand(time(NULL));
    for (i = 0; i < 3; i++)
    {
        printf("> Test 6: Attempt #%i\n", i + 1);
        for (j = 0; j < 10; j++)
        {
            chargingSamples[j] = get10BitSensorReadingStub();
            if (chargingSamples[j] == 0xFFFF)
            {
                printf("Invalid reading found ", chargingSamples[j]);
            }
            else
            {
                printf("%i-", chargingSamples[j]);
                chargingSamples[j] = convert10BitSensorToAmps(chargingSamples[j]);
                printf("%i, ", chargingSamples[j]);
            }
        }
        printf("\n");
        rangesFound = getRangesAndReadings(chargingSamples, sizeof(chargingSamples)/sizeof(int), rangesAndReadings);
        printRangesAndReadings(rangesAndReadings, rangesFound);
    }
}

TEST_CASE("Test 7: Ensure randomized 12-bit sensor readings never yield 4095 as result (error-reading). Test 5000 random values")
{
    int i;
    int sample = 0;
    srand(time(NULL));
    for (i = 0; i < 5000; i++)
    {
        sample = get12BitSensorReadingStub();
        REQUIRE(((sample < 4095) || (sample == 0xFFFF)));
    }
}

TEST_CASE("Test 8: Ensure randomized 10-bit sensor readings never yield 1023 as result (error-reading). Test 5000 random values")
{
    int i;
    int sample = 0;
    srand(time(NULL));
    for (i = 0; i < 5000; i++)
    {
        sample = get10BitSensorReadingStub();
        REQUIRE(((sample < 1023) || (sample == 0xFFFF)));
    }
}
