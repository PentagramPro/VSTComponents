#include "DSPDelay.h"
#include <cmath>

void CDSPDelay::Reset(double sampleRate, double transferTime, double startValue)
  {
	mRate = 1 / sampleRate;
      SetTransferTime(transferTime);
	mLast = 0;
  }

  double CDSPDelay::Next(double input)
  {
	  mLast = (1 - mT * mRate)*mLast + mT * mRate*input;
	  return mLast;
  }

void CDSPDelay::SetTransferTime(double transferTime) {
    mT = -std::log(0.01) / transferTime;
}
