/* cppsrc/main.cpp */
#include <napi.h>
#include "Samples/AuraSdkWrapper.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return AuraSdkWrapper::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)
