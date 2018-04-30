export class AuraSDKInterface {
  constructor (path: string)

  setupMb(): number
  setMbcolor(index: number, r: number, g: number, b: number): void
  updateMbColor(): void

  setupGPU(): number
  setGPUcolor(index: number, r: number, g: number, b: number): void
  updateGPUColor(): void

  setupDram(): number
  setDramcolor(index: number, r: number, g: number, b: number): void
  updateDramColor(): void
}

