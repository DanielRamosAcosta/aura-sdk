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
      setcolor: (i, r, g, b) => this.auraSDKInterface.setMbcolor(i, r, g, b),
      updateColor: () => this.auraSDKInterface.updateMbColor()
    })
  }

  /**
   * Creates an instance of the GPU controller
   */
  createGPUController () {
    return new Controller('GPU', {
      setup: () => this.auraSDKInterface.setupGPU(),
      setcolor: (i, r, g, b) => this.auraSDKInterface.setGPUcolor(i, r, g, b),
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
      setcolor: (i, r, g, b) => this.auraSDKInterface.setDramcolor(i, r, g, b),
      updateColor: () => this.auraSDKInterface.updateDramColor()
    })
  }
}
