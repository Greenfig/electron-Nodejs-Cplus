npm start
node-gyp rebuild --target=1.6.11 --arch=x64 --dist-url=https://atom.io/download/electron
node-gyp build
node-gyp configure