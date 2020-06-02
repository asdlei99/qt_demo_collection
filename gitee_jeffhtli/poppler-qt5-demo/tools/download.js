/**
 * https://gist.github.com/falkolab/f160f446d0bda8a69172
 */

function download(fileUrl, apiPath, callback) {
  var url = require('url'),
    http = require('http'),
    p = url.parse(fileUrl),
    fs = require('fs'),
    timeout = 10000;

  var file = fs.createWriteStream(apiPath);

  var timeout_wrapper = function( req ) {
    return function() {
      console.log('abort');
      req.abort();
      callback("File transfer timeout!");
    };
  };


  var request = http.get(fileUrl).on('response', function(res) {
    var len = parseInt(res.headers['content-length'], 10);
    var downloaded = 0;

    res.on('data', function(chunk) {
      file.write(chunk);
      downloaded += chunk.length;
      process.stdout.write("Downloading " + (100.0 * downloaded / len).toFixed(2) + "% " + downloaded + " bytes \r");
      // reset timeout
      clearTimeout( timeoutId );
      timeoutId = setTimeout( fn, timeout );
    }).on('end', function () {
      // clear timeout
      clearTimeout( timeoutId );
      file.end();
      console.log(' downloaded to: ' + apiPath);
      callback(null);
    }).on('error', function (err) {
      // clear timeout
      clearTimeout( timeoutId );
      callback(err.message);
    });
  });

  // generate timeout handler
  var fn = timeout_wrapper( request );

  // set initial timeout
  var timeoutId = setTimeout( fn, timeout );
}

module.exports = download;
