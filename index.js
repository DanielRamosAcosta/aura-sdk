//index.js
const { AuraSdk } = require('./build/Release/testaddon.node');

const classExample = new AuraSdk()

const sleep = ms => new Promise(r => setTimeout(r, ms))

const DeviceType = {
  ALL: 0x00000000,
  MOTHERBOARD: 0x00010000,
  MOTHERBOARD_LED_STRIP: 0x00011000,
  ALL_IN_ONE_PC: 0x00012000,
  VGA: 0x00020000,
  DISPLAY: 0x00030000,
  HEADSET: 0x00040000,
  MICROPHONE: 0x00050000,
  EXTERNAL_HDD: 0x00060000,
  EXTERNAL_BD_DRIVE: 0x00061000,
  DRAM: 0x00070000,
  KEYBOARD: 0x00080000,
  NOTEBOOK_KEYBOARD: 0x00081000,
  NOTEBOOK_KEYBOARD_4_ZONE_TYPE: 0x00081001,
  MOUSE: 0x00090000,
  CHASSIS: 0x000B0000,
  PROJECTOR: 0x000C0000,
}

async function main() {
  const deviceCount = classExample.getDeviceCount(DeviceType.MOTHERBOARD_LED_STRIP)
  console.log("DRAM", deviceCount)

  for (let index = 0; index < deviceCount; index++) {
    const numberOfLights = classExample.getDeviceLightsCount(DeviceType.MOTHERBOARD_LED_STRIP, index)
    console.log(numberOfLights)
  }

  classExample.setLightColor(DeviceType.DRAM, 0, 0, 0x00FF0000)
  classExample.apply(DeviceType.DRAM, 0)
  await sleep(1000)
  classExample.setLightColor(DeviceType.DRAM, 0, 0, 0x0000FF00)
  classExample.apply(DeviceType.DRAM, 0)
  await sleep(1000)
  classExample.setLightColor(DeviceType.DRAM, 0, 0, 0x000000FF)
  classExample.apply(DeviceType.DRAM, 0)
  await sleep(1000)
  classExample.setLightColor(DeviceType.DRAM, 0, 0, 0x00FF0000)
  classExample.apply(DeviceType.DRAM, 0)
  await sleep(1000)
}

main()
  .catch(error => {
    console.error(error)
    process.exit(1)
  })

function exitHandler() {
  console.log("I should be responsible and delete the memory")
  classExample.destroy()
}

process.on('exit', exitHandler);
process.on('SIGINT', exitHandler);
process.on('SIGUSR1', exitHandler);
process.on('SIGUSR2', exitHandler);
process.on('uncaughtException', exitHandler);
