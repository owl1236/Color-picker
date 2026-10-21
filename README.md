# RGB+MOUSE

A small Windows desktop app that samples the color of the pixel under the mouse cursor in real time and shows it in a window: the X/Y coordinates, the R/G/B values, a filled rectangle in that color, and the closest named color from a built-in color database (~300 entries).

Press **F6** to freeze/unfreeze the current color.

## How to compile

Requirements: Visual Studio (with MSVC `cl`) and the Windows SDK.

1. Open a **Developer Command Prompt** (x64 Native Tools Command Prompt for VS).
2. Navigate to the source folder:

   ```bat
   cd RGB&MOUSE_EXTENDED\RGB&MOUSE_EXTENDED
   ```

3. Compile into a single executable:

   ```bat
   cl /EHsc /O2 /DUNICODE /D_UNICODE RGB&MOUSE_EXTENDED.cpp /link user32.lib gdi32.lib /SUBSYSTEM:WINDOWS /OUT:RGB+MOUSE.exe
   ```

- `/EHsc` enables C++ exception handling
- `/O2` enables optimizations
- `/SUBSYSTEM:WINDOWS` makes it a GUI app (no console window)
- `user32.lib` / `gdi32.lib` are linked for the Win32 GUI and drawing calls

Run `RGB+MOUSE.exe` — move the mouse around the screen and the window follows the color under the cursor.
