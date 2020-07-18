#include "Arduino.h"
#include "average.h"

Average::Average(float *buffer, int size)
{
  //float *_bamples;
  //Serial.print(" float size: ");
  //Serial.println(sizeof(float));
  _samples = buffer;
  _headPtr = 0;
  _bufferSize = size;
  _lastMean = 0;
  _lastStdev = 0;
}

void Average::push(float value) {
  /*
  Serial.print("push: ");
  Serial.print(_headPtr);
  Serial.print(", ");
  Serial.println(value);*/
  _samples[_headPtr++] = value;
  if (_headPtr >= _bufferSize) {_headPtr = 0;}
}

float Average::mean() {

  float sum=0;
  int i;
  for (i=0; i < _bufferSize; i++) {
    sum+=_samples[i];
  }
  _lastMean = sum/_bufferSize;
  return _lastMean;
}

float Average::stdev() {
  float sum=0;
  int i;
  
  for (i=0; i < _bufferSize; i++) {
    sum+=pow(_samples[i]-_lastMean,2);
  }

  _lastStdev = sqrt(sum/(_bufferSize-1));

  return _lastStdev;
}

float Average::correctedMean() {
  float sum=0;
  int i;
  int n = 0;

  for (i=0; i < _bufferSize; i++) {
    if ( _samples[i] > (_lastMean - _lastStdev) 
      && _samples[i] < (_lastMean + _lastStdev)  ) {
        
      sum += _samples[i];
      n++;
    }
  }
  return sum/n;
}
