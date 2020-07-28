# node-gtk-icon-lookup

A native Node.js module for looking up GTK3+ icons.

## Installation
```
npm install --save node-gtk-icon-lookup
```

## Usage
```javascript
import GtkIcons from 'node-gtk-icon-lookup';

if (await GtkIcons.isIconLookupSupported()) {
  const iconFilePath = GtkIcons.getIconFilePath('avatar-default', 32);
  console.log(iconFilePath); 
}
```

Example output (depends on the current icon theme):
```
/usr/share/icons/Papirus-Dark/32x32/status/avatar-default.svg
```

## Running Tests
This package uses Mocha for tests. Tests will fail if run on a machine that doesn't have GTK3+ installed.

```
npm run test
```
