#include <napi.h>
#include "AuraSdk.h"

class AuraSdkWrapper : public Napi::ObjectWrap<AuraSdkWrapper> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  AuraSdkWrapper(const Napi::CallbackInfo& info);

 private:
  static Napi::FunctionReference constructor;
  void Destroy(const Napi::CallbackInfo& info);

  Napi::Value GetDeviceCount(const Napi::CallbackInfo& info);
  Napi::Value GetDeviceLightsCount(const Napi::CallbackInfo& info);

  void SetLightColor(const Napi::CallbackInfo& info);
  void Apply(const Napi::CallbackInfo& info);

  AuraSdk *auraSdk;
};
