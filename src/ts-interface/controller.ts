import Color from 'color'

export interface ISDKInjection {
  setup: () => number
  setColor: (index: number, r: number, g: number, b: number) => void
  updateColor: () => void
}

export class Controller {
  private auraSDK: ISDKInjection
  private deviceName: string
  private ledCount: number

  constructor (deviceName: string, auraSDK: ISDKInjection) {
    this.auraSDK = auraSDK
    this.deviceName = deviceName
    this.ledCount = this.auraSDK.setup()
  }

  /**
   * Joins multiple controllers into one array of callable functions
   * @param controllers array of controllers to join
   */
  static joinControllers (controllers: Controller[]) {
    const arr = []

    for(let controller of controllers) {
      for (let i = 0; i < controller.getLedCount(); i++) {
        arr.push({
          getDeviceName: () => controller.getDeviceName(),
          setColor: (color: string) => controller.setColor(i, color),
          setColorNow: (color: string) => controller.setColorNow(i, color)
        })
      }
    }

    return arr
  }

  /**
   * Get number of controllable leds in this controller
   */
  getLedCount () {
    return this.ledCount
  }

  /**
   * Get the device name (motherboard, GPU, DRAM)
   */
  getDeviceName () {
    return this.deviceName
  }

  /**
   * Sets the color of the LED at the given index
   * @param index index of the LED to change
   * @param color color of the LED. This uses [color](https://www.npmjs.com/package/color) package to convert the string to RGB.
   */
  setColor (index: number, color: string) {
    const [r, g, b] = Color(color).rgb().array()
    this.auraSDK.setColor(index, Math.floor(r), Math.floor(g), Math.floor(b))
  }

  /**
   * Sets the color of all the leds in the controller
   * @param color color of the LEDs. This uses [color](https://www.npmjs.com/package/color) package to convert the string to RGB.
   */
  setAllColor (color: string) {
    for (let i = 0; i < this.getLedCount(); i++) {
      this.setColor(i, color)
    }
  }

  /**
   * Sets the color of the LED at the given index and immediately updates them
   * @param index index of the LED to change
   * @param color color of the LED. This uses [color](https://www.npmjs.com/package/color) package to convert the string to RGB.
   */
  setColorNow (index: number, color: string) {
    this.setColor(index, color)
    this.updateColor()
  }

  /**
   * Sets the color of all the leds in the controller and immediately updates them
   * @param color color of the LEDs. This uses [color](https://www.npmjs.com/package/color) package to convert the string to RGB.
   */
  setAllColorNow (color: string) {
    this.setAllColor(color)
    this.updateColor()
  }

  /**
   * Updates the LEDs attached to the controller to reflect the current state
   */
  updateColor () {
    this.auraSDK.updateColor()
  }
}
