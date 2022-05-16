#include <Windows.h>
#include <Pdh.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

static PDH_HQUERY   cpuQuery;
static PDH_HCOUNTER cpuTotal;
static PDH_HCOUNTER coreStatuses;

void init()
{
  PdhOpenQueryA(NULL, NULL, &cpuQuery);
  // You can also use L"\\Processor(*)\\% Processor Time" and get individual CPU values with PdhGetFormattedCounterArray()
  PdhAddEnglishCounterA(cpuQuery, "\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);
  PdhAddEnglishCounterA(cpuQuery, "\\Processor(*)\\% Processor Time", NULL, &coreStatuses);
  PdhCollectQueryData(cpuQuery);
}

double getCurrentValue()
{
  PDH_FMT_COUNTERVALUE                     counterVal;
  std::vector<PDH_FMT_COUNTERVALUE_ITEM_A> stat;
  DWORD                                    bufferSz = 0;
  DWORD                                    itemCount;

  PdhCollectQueryData(cpuQuery);

  auto arret = PdhGetFormattedCounterArrayA(coreStatuses, PDH_FMT_DOUBLE, &bufferSz, &itemCount, NULL);
  stat.resize(itemCount);
  PdhGetFormattedCounterArrayA(coreStatuses, PDH_FMT_DOUBLE, &bufferSz, &itemCount, stat.data());

  auto dbret = PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
  return counterVal.doubleValue;
}

int main(int, char**)
{
  init();
  auto d = getCurrentValue();
}