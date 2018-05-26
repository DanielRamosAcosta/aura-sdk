export class AuraSDKInterface {
  constructor (path: string)

  setupMb(): number
  setMbColor(index: number, r: number, g: number, b: number): void
  updateMbColor(): void

  setupGPU(): number
  setGPUColor(index: number, r: number, g: number, b: number): void
  updateGPUColor(): void

  setupDram(): number
  setDramColor(index: number, r: number, g: number, b: number): void
  updateDramColor(): void

  setupKeyboard(): number
  setKeyboardColor(index: number, r: number, g: number, b: number): void
  updateKeyboardColor(): void
}

