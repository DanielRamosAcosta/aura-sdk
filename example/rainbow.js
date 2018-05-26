const { sleep } = require('./sleep')
const { AuraSDK } = require('..')

const auraSDK = new AuraSDK()

async function main() {
  const mbController = auraSDK.createMbController()
  const gpuController = auraSDK.createGPUController()
  const dramController = auraSDK.createDramController()
  const keyboardController = auraSDK.createKeyboardController()

  while (true) {
    for(let i = 0; i < 360; i++) {
      mbController.setAllColorNow(`hsl(${i}, 100%, 50%)`)
      gpuController.setAllColorNow(`hsl(${i}, 100%, 50%)`)
      dramController.setAllColorNow(`hsl(${i}, 100%, 50%)`)
      keyboardController.setAllColorNow(`hsl(${i}, 100%, 50%)`)
      await sleep(50)
    }
  }
}

main()
  .catch(err => console.error(err))
