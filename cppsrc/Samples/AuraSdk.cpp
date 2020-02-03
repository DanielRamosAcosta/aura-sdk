#include "AuraSdk.h"

AuraSdk::AuraSdk() {
  std::cout << "Initializing..." << std::endl;
  HRESULT hr;
  // Initialize COM
  hr = ::CoInitialize(nullptr);
  if (SUCCEEDED(hr)) {
    hr = this->sdk.CreateInstance(__uuidof(AuraServiceLib::AuraSdk), nullptr, CLSCTX_INPROC_SERVER);

    if (SUCCEEDED(hr)) {
        this->sdk->SwitchMode();
        this->sdk->Enumerate(0);
    }
  }
}

AuraSdk::~AuraSdk() {
  std::cout << "::CoUninitialize();" << std::endl;
  ::CoUninitialize();
}

void AuraSdk::setLightColor(uint32_t deviceType, uint32_t deviceIndex, uint32_t lightIndex, uint32_t color) {
  AuraServiceLib::IAuraSyncDeviceCollectionPtr devices = this->sdk->Enumerate(0);
  uint32_t deviceGlobalIndex = findDeviceGlobalIndex(devices, deviceType, deviceIndex);
  AuraServiceLib::IAuraSyncDevicePtr dev = devices->Item[deviceGlobalIndex];

  dev->Lights->Item[lightIndex]->Color = color;
}

void AuraSdk::apply(uint32_t deviceType, uint32_t deviceIndex) {
  AuraServiceLib::IAuraSyncDeviceCollectionPtr devices = this->sdk->Enumerate(0);
  uint32_t deviceGlobalIndex = findDeviceGlobalIndex(devices, deviceType, deviceIndex);
  AuraServiceLib::IAuraSyncDevicePtr dev = devices->Item[deviceGlobalIndex];

  dev->Apply();
}

uint32_t AuraSdk::getDeviceCount(uint32_t deviceType) {
  AuraServiceLib::IAuraSyncDeviceCollectionPtr devices = this->sdk->Enumerate(0);
  uint32_t count = 0;

  for (int i = 0; i < devices->Count; i++) {
    AuraServiceLib::IAuraSyncDevicePtr dev = devices->Item[i];
    if (dev->Type == deviceType) {
      count++;
    }
  }

  return count;
}

uint32_t AuraSdk::getDeviceLightsCount(uint32_t deviceType, uint32_t deviceIndex) {
  AuraServiceLib::IAuraSyncDeviceCollectionPtr devices = this->sdk->Enumerate(0);
  uint32_t deviceGlobalIndex = findDeviceGlobalIndex(devices, deviceType, deviceIndex);
  AuraServiceLib::IAuraSyncDevicePtr dev = devices->Item[deviceGlobalIndex];
  return dev->Lights->Count;
}

uint32_t AuraSdk::findDeviceGlobalIndex(AuraServiceLib::IAuraSyncDeviceCollectionPtr devices, uint32_t deviceType, uint32_t localIndex) {
  uint32_t currentDeviceIndex = 0;

  for (int i = 0; i < devices->Count; i++) {
    AuraServiceLib::IAuraSyncDevicePtr dev = devices->Item[i];

    if (dev->Type == deviceType) {
      if (currentDeviceIndex == localIndex) {
        return i;
      }
      currentDeviceIndex++;
    }
  }

  // TODO: throw exception
  return -1;
}
