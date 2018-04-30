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
