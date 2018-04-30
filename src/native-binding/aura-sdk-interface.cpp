#include <nan.h>
#include <Windows.h>
#include "AURALightingSDK.h"
#include <string>
#include <stdexcept>
#include <sstream>

#include "aura-sdk.hpp"

class AuraSDKInterface : public Nan::ObjectWrap {
  private:
  DRA::AuraSDK *auraSDK;

  public:
  static NAN_MODULE_INIT(Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("AuraSDKInterface").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "setupMb", setupMb);
    Nan::SetPrototypeMethod(tpl, "setMbcolor", setMbcolor);
    Nan::SetPrototypeMethod(tpl, "updateMbColor", updateMbColor);
    Nan::SetPrototypeMethod(tpl, "setupGPU", setupGPU);
    Nan::SetPrototypeMethod(tpl, "setGPUcolor", setGPUcolor);
    Nan::SetPrototypeMethod(tpl, "updateGPUColor", updateGPUColor);
    Nan::SetPrototypeMethod(tpl, "setupDram", setupDram);
    Nan::SetPrototypeMethod(tpl, "setDramcolor", setDramcolor);
    Nan::SetPrototypeMethod(tpl, "updateDramColor", updateDramColor);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("AuraSDKInterface").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
  }

  explicit AuraSDKInterface(std::string value) {
    auraSDK = new DRA::AuraSDK(value);
  }

  static NAN_METHOD(New) {
    if (info.IsConstructCall()) {
		v8::String::Utf8Value valuee(info[0]->ToString());
	  std::string value = std::string(*valuee);
      AuraSDKInterface *obj = new AuraSDKInterface(value);
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      const int argc = 1;
      v8::Local<v8::Value> argv[argc] = {info[0]};
      v8::Local<v8::Function> cons = Nan::New(constructor());
      info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    }
  }

  static NAN_METHOD(setupMb) {
    AuraSDKInterface* obj = Nan::ObjectWrap::Unwrap<AuraSDKInterface>(info.Holder());
    DRA::AuraSDK *auraSDK = obj->auraSDK;

    unsigned val = auraSDK->setupMb();
    info.GetReturnValue().Set(val);
  }

  static NAN_METHOD(setMbcolor) {
    AuraSDKInterface* obj = Nan::ObjectWrap::Unwrap<AuraSDKInterface>(info.Holder());
    DRA::AuraSDK *auraSDK = obj->auraSDK;

    auraSDK->setMbcolor(
      info[0]->Int32Value(),
      info[1]->Int32Value(),
      info[2]->Int32Value(),
      info[3]->Int32Value()
    );
  }

  static NAN_METHOD(updateMbColor) {
    AuraSDKInterface* obj = Nan::ObjectWrap::Unwrap<AuraSDKInterface>(info.Holder());
    DRA::AuraSDK *auraSDK = obj->auraSDK;

    auraSDK->updateMbColor(info[0]->Int32Value());
  }

  static NAN_METHOD(setupGPU) {
    AuraSDKInterface* obj = Nan::ObjectWrap::Unwrap<AuraSDKInterface>(info.Holder());
    DRA::AuraSDK *auraSDK = obj->auraSDK;

    unsigned val = auraSDK->setupGPU();
    info.GetReturnValue().Set(val);
  }

  static NAN_METHOD(setGPUcolor) {
    AuraSDKInterface* obj = Nan::ObjectWrap::Unwrap<AuraSDKInterface>(info.Holder());
    DRA::AuraSDK *auraSDK = obj->auraSDK;

    auraSDK->setGPUcolor(
      info[0]->Int32Value(),
      info[1]->Int32Value(),
      info[2]->Int32Value(),
      info[3]->Int32Value()
    );
  }

  static NAN_METHOD(updateGPUColor) {
    AuraSDKInterface* obj = Nan::ObjectWrap::Unwrap<AuraSDKInterface>(info.Holder());
    DRA::AuraSDK *auraSDK = obj->auraSDK;

    auraSDK->updateGPUColor(info[0]->Int32Value());
  }

  static NAN_METHOD(setupDram) {
    AuraSDKInterface* obj = Nan::ObjectWrap::Unwrap<AuraSDKInterface>(info.Holder());
    DRA::AuraSDK *auraSDK = obj->auraSDK;

    unsigned val = auraSDK->setupDram();
    info.GetReturnValue().Set(val);
  }

  static NAN_METHOD(setDramcolor) {
    AuraSDKInterface* obj = Nan::ObjectWrap::Unwrap<AuraSDKInterface>(info.Holder());
    DRA::AuraSDK *auraSDK = obj->auraSDK;

    auraSDK->setDramcolor(
      info[0]->Int32Value(),
      info[1]->Int32Value(),
      info[2]->Int32Value(),
      info[3]->Int32Value()
    );
  }

  static NAN_METHOD(updateDramColor) {
    AuraSDKInterface* obj = Nan::ObjectWrap::Unwrap<AuraSDKInterface>(info.Holder());
    DRA::AuraSDK *auraSDK = obj->auraSDK;

    auraSDK->updateDramColor(info[0]->Int32Value());
  }

  static inline Nan::Persistent<v8::Function> & constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }
};

NODE_MODULE(objectwrapper, AuraSDKInterface::Init)
