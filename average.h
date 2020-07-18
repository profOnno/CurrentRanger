#ifndef Average_h
#define Average_h

#include "Arduino.h"

class Average
{
  public:
    Average(float *buffer, int size);
    void push(float);
    float mean();
    float stdev();
    float correctedMean();

  private:
    int _bufferSize;
    int _headPtr;
    float _lastMean;
    float _lastStdev;
    float *_samples;    
};
#endif
