import path from 'path'
import fs from 'fs'
import Color from 'color'
import { AuraSDKInterface } from '../../build/Release/asus-aura-sdk'
import { Controller } from './controller'

export { Controller } from './controller'

export class AuraSDK {
  private auraSDKInterface: AuraSDKInterface

  constructor () {
    if (process.arch !== 'ia32') {
      throw new Error("Only 32 bit nodejs binary is supported")
    }
    const dllPath = path.resolve(__dirname, '../../build/Release')
    this.auraSDKInterface = new AuraSDKInterface(dllPath);
  }

  /**
   * Creates an instance of the motherboard controller
   */
  createMbController () {
    return new Controller('motherboard', {
      setup: () => this.auraSDKInterface.setupMb(),
      setColor: (i, r, g, b) => this.auraSDKInterface.setMbColor(i, r, g, b),
      updateColor: () => this.auraSDKInterface.updateMbColor()
    })
  }

  /**
   * Creates an instance of the GPU controller
   */
  createGPUController () {
    return new Controller('GPU', {
      setup: () => this.auraSDKInterface.setupGPU(),
      setColor: (i, r, g, b) => this.auraSDKInterface.setGPUColor(i, r, g, b),
      updateColor: () => this.auraSDKInterface.updateGPUColor()
    })
  }

  /**
   * Creates an instance of the DRAM controller
   */
  createDramController () {
    console.warn("DRAM controller isn't supported")
    return new Controller('DRAM', {
      setup: () => this.auraSDKInterface.setupDram(),
      setColor: (i, r, g, b) => this.auraSDKInterface.setDramColor(i, r, g, b),
      updateColor: () => this.auraSDKInterface.updateDramColor()
    })
  }

  /**
   * Creates an instance of the Keyboard controller
   */
  createKeyboardController () {
    return new Controller('Keyboard', {
      setup: () => this.auraSDKInterface.setupKeyboard(),
      setColor: (i, r, g, b) => this.auraSDKInterface.setKeyboardColor(i, r, g, b),
      updateColor: () => this.auraSDKInterface.updateKeyboardColor()
    })
  }
}

