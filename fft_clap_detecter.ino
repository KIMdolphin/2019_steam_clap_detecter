/* arduino 1.8.9 작동 확인 */

#include "arduinoFFT.h"

arduinoFFT FFT = arduinoFFT();
 
const uint16_t samples = 128;
double signalFrequency = 1000;
double samplingFrequency = 5000;
uint8_t amplitude = 100;

double vReal[samples];
double vImag[samples];

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02

#define Theta 6.2831

void setup()
{
  Serial.begin(115200);
//  Serial.println("Ready");
}

void loop()
{
  for (uint8_t i = 0; i < samples; i++)
  {
    vReal[i] = analogRead(A0); // 마이크 센서 부착 위치 
    delayMicroseconds(100);
    vImag[i] = 0;
  }
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD); 
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD); 
  FFT.ComplexToMagnitude(vReal, vImag, samples); 
  PrintVector(vReal, (samples >> 1), SCL_FREQUENCY);
}

void PrintVector(double *vData, uint8_t bufferSize, uint8_t scaleType)
{
  for (uint16_t i = 2; i < bufferSize; i++)
  {
    uint8_t val_temp = map(vData[i],0,1000,0,255);
    for(int j=0; j<(val_temp/10); j++){
      if((val_temp/(11))>5){
        tone(5, 400, 20);
        digitalWrite(11, HIGH);
      }
      Serial.write("-");
    }
  }
  Serial.write('\n');
}
