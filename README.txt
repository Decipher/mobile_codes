
Mobile Codes generates Datamatrix or QR Code mobile barcodes that can be read by
many camera phones. The codes can contain URLs, Text or Phone Numbers, making it
easy to pass data directly to a mobile phone.

Mobile Codes was written and is maintained by Stuart Clark (deciphered).
- http://stuar.tc/lark


Features
---------

* Input filter.
* CCK/Views formatter.
* Drupal API Theme() call.
* Configurable Presets.


Usage
---------

* via Input Filter:
  [mobilecodes type="type" data="data type" size="size" name="name" tinyurl="tinyurl"]content[/mobilecode]
  [mobilecodes profile="profile"]content[/mobilecode]

* via CCK/Views formatter:
  Select a Mobile Codes preset in a text field display options.

* via theme_mobilecode():
  Use the theme_mobilecode() function at the theme/module level with the
  following format:
  theme('mobilecode', 'content', array(arguments))


Arguments
---------

Arguments to be used by Input Filter and theme_mobilecode().

* preset - Mobile Codes Preset:
  * Default - (module default)
  * User defined

* data - Mobile barcode data type:
  * link - URL (module default)
  * phone - Phone Number
  * text - Text

* type - Mobile barcode type:
  * dm - Datamatrix (module default)
  * qr - QR Code

* data - Mobile barcode data type:
  * link - URL (module default)
  * phone - Phone Number
  * text - Text

* size - Size of mobile barcode:
  * small  - Small
  * medium - Medium (module default)
  * large  - Large

* name - Name of your mobile barcode
  * User defined

* tinyurl - TinyURL behaviour (for URLs only)
  * 0 - Only convert to TinyURL if URL is longer than 60 characters (module default)
  * 1 - Always convert to TinyURL

* content - Data to embed into mobile code (required)
  * User defined

Note: The only required argument is content as all others will default to either
a user defined default or the module defined default, or in the Dev build it
will default to the Default profile.

