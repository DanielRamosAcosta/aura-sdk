#include "AuraSdkWrapper.h"

Napi::FunctionReference AuraSdkWrapper::constructor;

Napi::Object AuraSdkWrapper::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "AuraSdk", {
    InstanceMethod("destroy", &AuraSdkWrapper::Destroy),
    InstanceMethod("getDeviceCount", &AuraSdkWrapper::GetDeviceCount),
    InstanceMethod("getDeviceLightsCount", &AuraSdkWrapper::GetDeviceLightsCount),
    InstanceMethod("setLightColor", &AuraSdkWrapper::SetLightColor),
    InstanceMethod("apply", &AuraSdkWrapper::Apply),
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("AuraSdk", func);
  return exports;
}

AuraSdkWrapper::AuraSdkWrapper(const Napi::CallbackInfo& info) : Napi::ObjectWrap<AuraSdkWrapper>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  this->auraSdk = new AuraSdk();
}

Napi::Value AuraSdkWrapper::GetDeviceCount(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 1) {
    Napi::TypeError::New(env, "[GetDeviceCount] Expected 1 parameter").ThrowAsJavaScriptException();
  }

  if (!info[0].IsNumber()) {
    Napi::TypeError::New(env, "[GetDeviceCount] Expected first argument to be a number").ThrowAsJavaScriptException();
  }

  Napi::Number deviceType = info[0].As<Napi::Number>();

  uint32_t num = this->auraSdk->getDeviceCount(deviceType.Uint32Value());
  return Napi::Number::New(env, num);
}

Napi::Value AuraSdkWrapper::GetDeviceLightsCount(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 2) {
    Napi::TypeError::New(env, "[GetDeviceLightsCount] Expected 2 parameters").ThrowAsJavaScriptException();
  }

  if (!info[0].IsNumber()) {
    Napi::TypeError::New(env, "[GetDeviceLightsCount] Expected first argument to be a number").ThrowAsJavaScriptException();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "[GetDeviceLightsCount] Expected second argument to be a number").ThrowAsJavaScriptException();
  }

  Napi::Number deviceType = info[0].As<Napi::Number>();
  Napi::Number deviceIndex = info[1].As<Napi::Number>();

  uint32_t count = this->auraSdk->getDeviceLightsCount(deviceType.Uint32Value(), deviceIndex.Uint32Value());
  return Napi::Number::New(env, count);
}

void AuraSdkWrapper::Destroy(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  std::cout << "Deleting AuraSdkWrapper" << std::endl;
  delete this->auraSdk;
}

void AuraSdkWrapper::SetLightColor(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 4) {
    Napi::TypeError::New(env, "[GetDeviceLightsCount] Expected 4 parameters").ThrowAsJavaScriptException();
  }

  if (!info[0].IsNumber()) {
    Napi::TypeError::New(env, "[GetDeviceLightsCount] Expected first argument to be a number").ThrowAsJavaScriptException();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "[GetDeviceLightsCount] Expected second argument to be a number").ThrowAsJavaScriptException();
  }

  if (!info[2].IsNumber()) {
    Napi::TypeError::New(env, "[GetDeviceLightsCount] Expected third argument to be a number").ThrowAsJavaScriptException();
  }

  if (!info[3].IsNumber()) {
    Napi::TypeError::New(env, "[GetDeviceLightsCount] Expected fourth argument to be a number").ThrowAsJavaScriptException();
  }

  Napi::Number deviceType = info[0].As<Napi::Number>();
  Napi::Number deviceIndex = info[1].As<Napi::Number>();
  Napi::Number lightIndex = info[2].As<Napi::Number>();
  Napi::Number color = info[3].As<Napi::Number>();

  this->auraSdk->setLightColor(deviceType.Uint32Value(), deviceIndex.Uint32Value(), lightIndex.Uint32Value(), color.Uint32Value());
}

void AuraSdkWrapper::Apply(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 2) {
    Napi::TypeError::New(env, "[GetDeviceLightsCount] Expected 2 parameters").ThrowAsJavaScriptException();
  }

  if (!info[0].IsNumber()) {
    Napi::TypeError::New(env, "[GetDeviceLightsCount] Expected first argument to be a number").ThrowAsJavaScriptException();
  }

  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "[GetDeviceLightsCount] Expected second argument to be a number").ThrowAsJavaScriptException();
  }

  Napi::Number deviceType = info[0].As<Napi::Number>();
  Napi::Number deviceIndex = info[1].As<Napi::Number>();

  this->auraSdk->apply(deviceType.Uint32Value(), deviceIndex.Uint32Value());
}
