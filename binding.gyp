{
  "targets": [
    {
      "target_name": "asus-aura-sdk",
      "sources": [
        "./src/native-binding/asus-aura-sdk.hpp",
        "./src/native-binding/aura-sdk.hpp",
        "./src/native-binding/aura-sdk-interface.cpp"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "AuraSDK/sdk/"
      ],
      "copies": [
        {
          "destination": "build/Release",
          "files": [
            "src/native-binding/asus-aura-sdk.d.ts",
            "AuraSDK/sdk/AURA_SDK.dll",
            "AuraSDK/device dll/vga/LED_DLL_forMB.dll",
            "AuraSDK/device dll/vga/Vender.dll",
            "AuraSDK/device dll/vga/VGA_Extra.dll"
          ]
        }
      ],
      "msvs_settings": {
        "VCCLCompilerTool": {
          "ExceptionHandling": 1
        }
      },
      "conditions": [
        ["OS=='win'", {
          "defines": [
            "_HAS_EXCEPTIONS=1"
          ]
        }]
      ]
    }
  ]
}