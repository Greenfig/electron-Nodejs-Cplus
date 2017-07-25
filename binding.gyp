{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "./src_cpp/hello.cpp" ],
      'conditions':
      [
        ['OS=="win"',
            {
              'cflags': ["/O2", "/openmp"]
            }
        ]
      ]
    }
    ]
}