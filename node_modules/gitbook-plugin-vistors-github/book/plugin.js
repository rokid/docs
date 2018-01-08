'use strict';

require(["gitbook"], function(gitbook) {
  var config = {
    repo: null,
    branch: 'master',
  };
  gitbook.events.bind("start", function(e, c) {
    config = Object.assign(config, c['vistors-github']);
  });
  gitbook.events.bind("page.change", function(e) {
    var img = document.createElement('img');
    img.style.display = 'none';
    img.src = 'https://github.com/' + config.repo + '/blob/' + config.branch
      + location.pathname.replace(/\.html$/, '.md');
    document.body.appendChild(img);
  });
});
