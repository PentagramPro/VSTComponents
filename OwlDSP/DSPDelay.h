
#pragma once

class CDSPDelay {
public:
	CDSPDelay() {}

	void Reset(double sampleRate, double transferTime, double startValue = 0);
	void SetTransferTime(double transferTime);
	double Next(double input);
private:
	double mT = 1;
	double mRate = 1;
	double mLast = 0;
};