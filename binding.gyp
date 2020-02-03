{
    "targets": [{
        "target_name": "testaddon",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "cppsrc/main.cpp",
            "cppsrc/Samples/AuraSdk.cpp",
            "cppsrc/Samples/AuraSdkWrapper.cpp"
        ],
        'msvs_settings': {
          'VCCLCompilerTool': {
            'AdditionalOptions!': [
              '/MP'
            ]
          }
        },
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}
