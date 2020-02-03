#include "./AuraSdk_x86.tlh" /* <-- Add this */
#include <iostream>

class AuraSdk {
 public:
  AuraSdk();
  ~AuraSdk();
  uint32_t getDeviceCount(uint32_t deviceType);
  uint32_t getDeviceLightsCount(uint32_t deviceType, uint32_t deviceIndex);
  void setLightColor(uint32_t deviceType, uint32_t deviceIndex, uint32_t lightIndex, uint32_t color);
  void apply(uint32_t deviceType, uint32_t deviceIndex);
 private:
  AuraServiceLib::IAuraSdkPtr sdk;
  uint32_t findDeviceGlobalIndex(AuraServiceLib::IAuraSyncDeviceCollectionPtr devices, uint32_t deviceType, uint32_t localIndex);
};
