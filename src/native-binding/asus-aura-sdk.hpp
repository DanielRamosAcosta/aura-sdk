#pragma once

#include <Windows.h>
#include <string>
#include <exception>
#include <sstream>

#include "AURALightingSDK.h"

namespace AsusAuraSDK {
  HMODULE hLib;

  EnumerateMbControllerFunc EnumerateMbController;
  SetMbModeFunc SetMbMode;
  GetMbLedCountFunc GetMbLedCount;
  GetMbColorFunc GetMbColor;
  SetMbColorFunc SetMbColor;

  EnumerateGPUFunc EnumerateGPU;
  SetGPUModeFunc SetGPUMode;
  GetGPULedCountFunc GetGPULedCount;
  SetGPUColorFunc SetGPUColor;

  CreateClaymoreKeyboardFunc CreateClaymoreKeyboard;
  SetClaymoreKeyboardModeFunc SetClaymoreKeyboardMode;
  GetClaymoreKeyboardLedCountFunc GetClaymoreKeyboardLedCount;
  SetClaymoreKeyboardColorFunc SetClaymoreKeyboardColor;

  CreateRogMouseFunc CreateRogMouse;
  SetRogMouseModeFunc SetRogMouseMode;
  RogMouseLedCountFunc RogMouseLedCount;
  SetRogMouseColorFunc SetRogMouseColor;

  // TODO
  // EnumerateDramFunc EnumerateDram;
  // SetDramModeFunc SetDramMode;
  // GetDramLedCountFunc GetDramLedCount;
  // GetDramColorFunc GetDramColor;
  // SetDramColorFunc SetDramColor;

  DWORD checkDllIsLoaded () {
    if (hLib == nullptr) {
      throw std::runtime_error("AURA_SDK.dll not found");
    }
  }

  DWORD loadDll (std::string dllPath) {
    if (hLib == nullptr) {
      std::stringstream sdkDllPath;
      sdkDllPath << dllPath << "\\AURA_SDK.dll";
      hLib = LoadLibraryA(sdkDllPath.str().c_str());

      AsusAuraSDK::checkDllIsLoaded();

      (FARPROC&)EnumerateMbController = GetProcAddress(hLib, "EnumerateMbController");
      (FARPROC&)SetMbMode = GetProcAddress(hLib, "SetMbMode");
      (FARPROC&)GetMbLedCount = GetProcAddress(hLib, "GetMbLedCount");
      (FARPROC&)GetMbColor = GetProcAddress(hLib, "GetMbColor");
      (FARPROC&)SetMbColor = GetProcAddress(hLib, "SetMbColor");

      (FARPROC&)EnumerateGPU = GetProcAddress(hLib, "EnumerateGPU");
      (FARPROC&)SetGPUMode = GetProcAddress(hLib, "SetGPUMode");
      (FARPROC&)GetGPULedCount = GetProcAddress(hLib, "GetGPULedCount");
      (FARPROC&)SetGPUColor = GetProcAddress(hLib, "SetGPUColor");

      (FARPROC&)CreateClaymoreKeyboard = GetProcAddress(hLib, "CreateClaymoreKeyboard");
      (FARPROC&)SetClaymoreKeyboardMode = GetProcAddress(hLib, "SetClaymoreKeyboardMode");
      (FARPROC&)GetClaymoreKeyboardLedCount = GetProcAddress(hLib, "GetClaymoreKeyboardLedCount");
      (FARPROC&)SetClaymoreKeyboardColor = GetProcAddress(hLib, "SetClaymoreKeyboardColor");

      (FARPROC&)CreateRogMouse = GetProcAddress(hLib, "CreateRogMouse");
      (FARPROC&)SetRogMouseMode = GetProcAddress(hLib, "SetRogMouseMode");
      (FARPROC&)RogMouseLedCount = GetProcAddress(hLib, "RogMouseLedCount");
      (FARPROC&)SetRogMouseColor = GetProcAddress(hLib, "SetRogMouseColor");

      // TODO: Wait until ASUS updates their SDK for Dram support
      // (FARPROC&)EnumerateDram = GetProcAddress(hLib, "EnumerateDram");
      // (FARPROC&)SetDramMode = GetProcAddress(hLib, "SetDramMode");
      // (FARPROC&)GetDramLedCount = GetProcAddress(hLib, "GetDramLedCount");
      // (FARPROC&)GetDramColor = GetProcAddress(hLib, "GetDramColor");
      // (FARPROC&)SetDramColor = GetProcAddress(hLib, "SetDramColor");
    }
  }

  DWORD enumerateMbController (MbLightControl handles[], DWORD size) {
    return EnumerateMbController(handles, size);
  }

  DWORD setMbMode (MbLightControl handle, DWORD mode) {
    return SetMbMode(handle, mode);
  }

  DWORD getMbLedCount (MbLightControl handle) {
    return GetMbLedCount(handle);
  }

  DWORD getMbColor () {
    // TODO
  }

  DWORD setMbColor (MbLightControl handle, BYTE* color, DWORD size) {
    return SetMbColor(handle, color, size);
  }

  DWORD enumerateGPU (GPULightControl handles[], DWORD size) {
    return EnumerateGPU(handles, size);
  }

  DWORD setGPUMode (GPULightControl handle, DWORD mode) {
    return SetGPUMode(handle, mode);
  }

  DWORD getGPULedCount (GPULightControl handle) {
    return GetGPULedCount(handle);
  }

  DWORD setGPUColor (GPULightControl handle, BYTE* color, DWORD size) {
    return SetGPUColor(handle, color, size);
  }

  DWORD createClaymoreKeyboard (ClaymoreKeyboardLightControl* handle) {
    return CreateClaymoreKeyboard(handle);
  }

  DWORD setClaymoreKeyboardMode (ClaymoreKeyboardLightControl handle, DWORD mode) {
    return SetClaymoreKeyboardMode(handle, mode);
  }

  DWORD getClaymoreKeyboardLedCount (ClaymoreKeyboardLightControl handle) {
    return GetClaymoreKeyboardLedCount(handle);
  }

  DWORD setClaymoreKeyboardColor (ClaymoreKeyboardLightControl handle, BYTE* color, DWORD size) {
    return SetClaymoreKeyboardColor(handle, color, size);
  }

  DWORD createRogMouse (RogMouseLightControl* handle) {
    return CreateRogMouse(handle);
  }

  DWORD setRogMouseMode (RogMouseLightControl* handle, DWORD mode) {
    return SetRogMouseMode(handle, mode);
  }

  DWORD rogMouseLedCount (RogMouseLightControl* handle) {
    return RogMouseLedCount(handle);
  }

  DWORD setRogMouseColor (RogMouseLightControl* handle, BYTE* color, DWORD size) {
    return SetRogMouseColor(handle, color, size);
  }

  // TODO: Wait until ASUS updates their SDK for Dram support
  /*
  DWORD enumerateDram (DramLightControl handles[], DWORD size) {
    return EnumerateDram(handles, size);
  }

  DWORD setDramMode (DramLightControl handle, DWORD mode) {
    return SetDramMode(handle, mode);
  }

  DWORD getDramLedCount (DramLightControl handle) {
    return GetDramLedCount(handle);
  }

  DWORD getDramColor (DramLightControl handle, BYTE* color, DWORD size) {
    return GetDramColor(handle, color, size);
  }

  DWORD setDramColor (DramLightControl handle, BYTE* color, DWORD size) {
    return SetDramColor(handle, color, size);
  }
  */
};
