{
  'targets': [
    {
      'target_name': 'person',
      'sources': [
        "person-module.cc",
        "Person.cc",
        "SayWorkerCallback.cc",
        "SayWorker.cc"
      ],
      'include_dirs' : [
        "<!(node -e \"require('nan')\")"
      ],
      'xcode_settings': {
        'MACOSX_DEPLOYMENT_TARGET': '10.9',
      },
      'cflags_cc': [
        '-fexceptions'
      ],
      'libraries': [
      ],
    }
  ]
}
