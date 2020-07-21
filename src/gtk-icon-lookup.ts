import os from 'os';

declare type IconLookupFunction = (iconName: string, size?: number) => string | undefined;
declare type IconLookupNativeModule = {
  getIconFileName: IconLookupFunction;
};

const nativeModule = require('bindings')('gtk_icon_lookup_native') as IconLookupNativeModule;

export const getIconFileName: IconLookupFunction = (iconName: string, size?: number) => {
  return nativeModule.getIconFileName(iconName, size);
}

export const isIconLookupSupported = () => {
  return os.platform() === 'linux';
}

export default {
  getIconFileName,
  isIconLookupSupported,
};
