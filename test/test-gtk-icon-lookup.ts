import assert from 'assert';
import GtkIconLookup from '../src/gtk-icon-lookup';

describe('icon-lookup', () => {
  it('should succeed on known icons', () => {
    assert.notEqual(GtkIconLookup.getIconFilePath('avatar-default'), undefined);
    assert.notEqual(GtkIconLookup.getIconFilePath('state-information'), undefined);
  });

  it('should fail on uknown icons', () => {
    assert.equal(GtkIconLookup.getIconFilePath('____abc____'), undefined);
    assert.equal(GtkIconLookup.getIconFilePath('____abc____2'), undefined);
  });
});
