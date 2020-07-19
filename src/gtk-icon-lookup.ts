const nativeModule = require('bindings')('gtk_icon_lookup_native');
console.log('Google Icon: ' + nativeModule.getIconFileName('google'));
console.log('Twitch Icon: ' + nativeModule.getIconFileName('twitch-indicator'));
console.log('Unknown Icon: ' + nativeModule.getIconFileName('asdqwdasdasd@@asdasdasd'));

