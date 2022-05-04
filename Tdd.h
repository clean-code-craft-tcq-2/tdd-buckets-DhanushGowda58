#define MAX_NUMBER_OF_RANGES_AND_READINGS 100

void printRangesAndReadings(int *buffer, int totalRanges);

int getRangesAndReadings(int *samples, int sampleSize, int *rangesAndReadingsFound);

int convert12BitSensorToAmps(int bitValue);

int convert10BitSensorToAmps(int bitValue);

int get12BitSensorReadingStub(void);

int get10BitSensorReadingStub(void);
