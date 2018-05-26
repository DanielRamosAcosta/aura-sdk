if (process.arch !== 'ia32') {
  throw new Error(`Only 32 bit nodejs binary is supported. Curren arch: ${process.arch}`)
}
