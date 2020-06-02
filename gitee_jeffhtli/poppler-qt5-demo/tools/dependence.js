var fs = require('fs-extra');
var extract = require('extract-zip');
var download = require('./download');

const url = `http://gradle.mynimble.cn/libpoppler-0.39.0-${process.argv[2]}.zip`;
const libsPath = './libs';
const fileName = 'libpoppler.zip';

fs.emptyDirSync(libsPath);
download(url, `${libsPath}/${fileName}`, function (error) {
  console.log(error ? error : 'Download finish');
  if (error) {
    console.log(`Download failed: ${error}`);
  } else {
    console.log(`unzip to ${libsPath}`);
    extract(`${libsPath}/${fileName}`, {dir: libsPath}, function (error) {
      console.log(error ? `unzip failed: ${error}` : 'Get dependence finish!');
    })

  }
});
