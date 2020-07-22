import os from 'os';
import child_process from 'child_process';

let gtkSupported: boolean | null = null;

declare type IconLookupFunction = (iconName: string, size?: number) => string | undefined;
declare type IconLookupNativeModule = {
  getIconFileName: IconLookupFunction;
};

let nativeModule: IconLookupNativeModule | undefined;
function getNativeModule() : IconLookupNativeModule {
  if (nativeModule) {
    return nativeModule;
  }

  if (isIconLookupSupported()) {
    nativeModule = require('bindings')('gtk_icon_lookup_native') as IconLookupNativeModule;
    return nativeModule;
  }

  throw new Error('Icon lookup is not supported in this environment');
}

/**
 * Looks up the file path for a GTK icon.
 * @param iconName The name of the icon to lookup
 * @param size Optionally, the size of the icon to request. The returned icon may be smaller than this size.
 * @returns The full path to the icon, or `undefined` if the icon does not exist
 */
export const getIconFilePath: IconLookupFunction = (iconName: string, size?: number) => {
  return getNativeModule().getIconFileName(iconName, size);
}

/**
 * Returns whether or not icon lookup is supported in the current environment. The following conditions must be met:
 * - The current platform is Linux
 * - GTK3+ is installed and available
 */
export const isIconLookupSupported = async () => {
  if (gtkSupported != null) {
    return gtkSupported;
  }

  if (os.platform() !== 'linux') {
    gtkSupported = false;
  }
  else {
    const result = child_process.spawnSync('/sbin/ldconfig', ['-p']);
    if (result.status === 0) {
      for (const data of result.output) {

        // Weird hack - the output data may be a Buffer even though the typings say
        // it is always a string
        let line: string;
        if (data != null && data as any instanceof Buffer) {
          line = (data as any as Buffer).toString()
        } else {
          line = data;
        }
        
        if (line != null && line.includes('libgtk-3.so')) {
          gtkSupported = true;
          break;
        }
      }
    }

    gtkSupported = false;
  }

  return gtkSupported;
}

export default {
  getIconFilePath,
  isIconLookupSupported,
};
