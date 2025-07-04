# Signtool GUI

This is a [Qt](https://www.qt.io) GUI that wraps [signtool.exe](https://docs.microsoft.com/en-us/dotnet/framework/tools/signtool-exe) with an easy drag &amp; drop approach.

Manually signing your binaries on Windows (automating it would be even better tho) was never as pleasant as dragging and dropping them into a visual user interface and selecting the code signing certificate + password and hit a button. Isn't that smooth af?

**Before using this, make sure to have [signtool.exe](https://docs.microsoft.com/en-us/dotnet/framework/tools/signtool-exe) installed on your system and available in your `$PATH`**

There is also a "verify" tab: in there you can drag &amp; drop binaries into the list field and verify their signatures (instead of using `signtool.exe verify /pa {FILE_PATH}` or, even worse, executing them and checking if the Windows SmartScreen goes brr...).

---

![Signtool GUI Screenshots](https://api-files.glitchedpolygons.com/api/v1/files/2porakb5izmfdtx3)

---

This GUI's source code is [GPL-3.0 licensed](https://github.com/GlitchedPolygons/SigntoolGUI/blob/main/LICENSE) and available on [github.com/GlitchedPolygons/SigntoolGUI](https://github.com/GlitchedPolygons/SigntoolGUI) - but also available for purchase on [glitchedpolygons.com](https://glitchedpolygons.com) (ships with some cool, additional stuff, PDF files/manual, etc...). 

Please consider buying it from there to support the development of nifty tools like this :)

---

Check out the official tutorial video on YouTube:

https://youtube.com/watch?v=s-rts-YK9uM
