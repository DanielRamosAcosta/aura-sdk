# aura-sdk

[![NPM Version](https://img.shields.io/npm/v/aura-sdk.svg)](https://www.npmjs.com/package/aura-sdk)

ASUS Aura's SDK Nodejs C++ bindings. This package provides an high-level API
to manage your rig led show!

![RGB Stepper Demo](https://raw.githubusercontent.com/DanielRamosAcosta/aura-sdk/master/example/rgb-stepper.gif)

## Usage

```
npm install --save aura-sdk
```

You have to create an instance of the SDK, and then create an instanace for each
device. This examples creates an RGB stepper

```javascript
const { sleep } = require('./sleep')
const { AuraSDK, Controller } = require('..')

async function main() {
  const auraSDK = new AuraSDK()

  const leds = Controller.joinControllers([
    auraSDK.createMbController(),
    auraSDK.createGPUController(),
    auraSDK.createDramController()
  ])

  while (true) {
    for (color of ['red', 'green', 'blue']) {
      for (let led of leds) {
        led.setColorNow(color)
        await sleep(1000)
      }
    }
  }
}

main()
  .catch(err => console.error(err))
```

## API

### AuraSDK

This is the main SDK entrypoint. It creates instances for the different devices types.

* **`AuraSDK#createMbController()`**: Creates an instance of the motherboard controller
* **`AuraSDK#createGPUController()`**: Creates an instance of the GPU controller
* **`AuraSDK#createDramController()`**: Creates an instance of the DRAM controller

### Controller

* **`Controller.joinControllers(controllers: Controller[])`**: Joins multiple controllers into one array of callable functions. See the the example for usage.
* **`Controller#getLedCount()`**: Get number of controllable leds in this controller.
* **`Controller#getDeviceName()`**: Get the device name (motherboard, GPU, DRAM).
* **`Controller#setColor(index: number, color: string)`**: Set the color of the LED at the given index.
* **`Controller#setAllColor(color: string)`**: Sets the color of all the leds in the controller.
* **`Controller#setColorNow(index: number, color: string)`**: Sets the color of the LED at the given index and immediately updates them.
* **`Controller#setAllColorNow(color: string)`**: Sets the color of all the leds in the controller and immediately updates them.
* **`Controller#updateColor()`**: Updates the LEDs attached to the controller to reflect the current state.
