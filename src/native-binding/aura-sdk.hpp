#pragma once

#include <nan.h>
#include <Windows.h>
#include <string>
#include <stdexcept>
#include <sstream>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "AURALightingSDK.h"
#include "asus-aura-sdk.hpp"

namespace DRA {
  enum LIGHT_CONTROLLER_MODES {
    /**
     * Sets the controller to the EC mode and in turn to set the lights to
     * perform the default lighting effect. The default effect varies from
     * motherboard to motherboard.
     **/
    EC_MODE = 0,
    /**
     * Sets the controller to the software mode. The behavior of the lights
     * belonging to the controller can be totally determined by the
     * software itself.
     **/
    SOFTWARE_MODE = 1
  };

  static const unsigned RGB_COUNT = 3;

  class AuraSDK {
    private:
    std::string dllPath_;

    uint32_t controllerCountMb;
    MbLightControl* controllersMb;
    uint32_t ledCountMb;
    BYTE* ledsMb;

    uint32_t controllerCountGPU;
    MbLightControl* controllersGPU;
    uint32_t ledCountGPU;
    BYTE* ledsGPU;

    uint32_t controllerCountDram;
    MbLightControl* controllersDram;
    uint32_t ledCountDram;
    BYTE* ledsDram;

    uint32_t controllerCountKeyboard;
    ClaymoreKeyboardLightControl* controllersKeyboard;
    uint32_t ledCountKeyboard;
    BYTE* ledsKeyboard;

    public:

    AuraSDK(std::string dllPath):
    dllPath_(dllPath) {
      AsusAuraSDK::loadDll(dllPath);
    }

    ~AuraSDK() {
      if (controllersMb != nullptr) {
        for(size_t i = 0; i < controllerCountMb; i++) {
          AsusAuraSDK::setMbMode(controllersMb[i], LIGHT_CONTROLLER_MODES::EC_MODE);
        }

        delete[] controllersMb;
      }

      if (ledsMb != nullptr) {
        delete[] ledsMb;
      }
    }

    unsigned setupMb () {
      controllerCountMb = AsusAuraSDK::enumerateMbController(NULL, 0);
      if (controllerCountMb < 1) {
        printf("warning: controllerCountMb < 1\n");
        fflush(stdout);
        return 0;
      }
      controllersMb = new MbLightControl[controllerCountMb];
      AsusAuraSDK::enumerateMbController(controllersMb, controllerCountMb);
      AsusAuraSDK::setMbMode(controllersMb[0], LIGHT_CONTROLLER_MODES::SOFTWARE_MODE);

      ledCountMb = AsusAuraSDK::getMbLedCount(controllersMb[0]);
      ledsMb = new BYTE[(ledCountMb) * RGB_COUNT];

      ZeroMemory(ledsMb, (ledCountMb) * RGB_COUNT);
      return ledCountMb;
    }

    void setMbColor(unsigned index, unsigned r, unsigned g, unsigned b) {
      ledsMb[(index * RGB_COUNT) + 0] = r;
      ledsMb[(index * RGB_COUNT) + 1] = b;
      ledsMb[(index * RGB_COUNT) + 2] = g;
    }

    void updateMbColor (unsigned controller) {
      AsusAuraSDK::setMbColor(controllersMb[0], ledsMb, (ledCountMb) * RGB_COUNT);
    }

    unsigned setupGPU () {
      std::string currentDir = std::string(_getcwd( NULL, 0 ));
      _chdir(dllPath_.c_str());
      controllerCountGPU = AsusAuraSDK::enumerateGPU(NULL, 0);
      if (controllerCountGPU < 1) {
        printf("warning: controllerCountGPU < 1\n");
        fflush(stdout);
        return 0;
      }
      controllersGPU = new GPULightControl[controllerCountGPU];
      AsusAuraSDK::enumerateGPU(controllersGPU, controllerCountGPU);
      AsusAuraSDK::setGPUMode(controllersGPU[0], LIGHT_CONTROLLER_MODES::SOFTWARE_MODE);

      ledCountGPU = AsusAuraSDK::getGPULedCount(controllersGPU[0]);
      ledsGPU = new BYTE[(ledCountGPU) * RGB_COUNT];

      ZeroMemory(ledsGPU, (ledCountGPU) * RGB_COUNT);
      _chdir(currentDir.c_str());
      return ledCountGPU;
    }

    void setGPUColor(unsigned index, unsigned r, unsigned g, unsigned b) {
      ledsGPU[(index * RGB_COUNT) + 0] = r;
      ledsGPU[(index * RGB_COUNT) + 1] = g;
      ledsGPU[(index * RGB_COUNT) + 2] = b;
    }

    void updateGPUColor (unsigned controller) {
      AsusAuraSDK::setGPUColor(controllersGPU[0], ledsGPU, (ledCountGPU) * RGB_COUNT);
    }

    unsigned setupDram () {
      // TODO: Wait until ASUS updates their SDK for Dram support
      return 0;
    }

    void setDramColor(unsigned index, unsigned r, unsigned g, unsigned b) {
      // TODO: Wait until ASUS updates their SDK for Dram support
    }

    void updateDramColor (unsigned controller) {
      // TODO: Wait until ASUS updates their SDK for Dram support
    }

    unsigned setupKeyboard () {
      std::string currentDir = std::string(_getcwd( NULL, 0 ));
      _chdir(dllPath_.c_str());
      controllersKeyboard = new ClaymoreKeyboardLightControl;
      controllerCountKeyboard = AsusAuraSDK::createClaymoreKeyboard(controllersKeyboard);
      if (controllerCountKeyboard < 1) {
        printf("warning: controllerCountKeyboard < 1\n");
        fflush(stdout);
        return 0;
      }
      ledCountKeyboard =  AsusAuraSDK::getClaymoreKeyboardLedCount(*controllersKeyboard);
      AsusAuraSDK::setClaymoreKeyboardMode(*controllersKeyboard, LIGHT_CONTROLLER_MODES::SOFTWARE_MODE);
      ledsKeyboard = new BYTE[(ledCountKeyboard) * RGB_COUNT];
      ZeroMemory(ledsKeyboard, (ledCountKeyboard) * RGB_COUNT);
      _chdir(currentDir.c_str());
      return ledCountKeyboard;
    }

    void setKeyboardColor(unsigned index, unsigned r, unsigned g, unsigned b) {
      ledsKeyboard[(index * RGB_COUNT) + 0] = r;
      ledsKeyboard[(index * RGB_COUNT) + 1] = b;
      ledsKeyboard[(index * RGB_COUNT) + 2] = g;
    }

    void updateKeyboardColor () {
      AsusAuraSDK::setClaymoreKeyboardColor(controllersKeyboard, ledsKeyboard, (ledCountKeyboard) * RGB_COUNT);
    }
  };
}
