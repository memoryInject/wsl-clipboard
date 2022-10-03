
# wsl-clipboard 📋

Blazingly fast Windows clipboard utility for WSL applications and Neovim running under WSL.     
Build using Microsoft Visual Studio Community 
2019 Version 16.11.19 on Windows 10 Version 21H2 (OS Build 19044.2006).

## Features

- Get and set windows clipboard
- Support Unicode characters
- Additional shell script for WSL for removing CR end of a line
- Support Neovim 


## Installation

Install wsl-clipboard by download Windows executable and shell scripts from [release page](https://github.com/memoryInject/wsl-clipboard/releases/tag/v0.1.0)

```bash
  wget https://github.com/memoryInject/wsl-clipboard/releases/download/v0.1.0/wclip.exe
  wget https://github.com/memoryInject/wsl-clipboard/releases/download/v0.1.0/wcopy
  wget https://github.com/memoryInject/wsl-clipboard/releases/download/v0.1.0/wpaste
```

After downloading `wclip.exe, wcopy and wpaste`:  
Move wclip.exe into `C:\Windows\System32\` or any other Windows file system location that is on system `PATH`.

**NOTE: do not copy wclip.exe in WSL file system location, it will slow down the executaion of Windows applications).   

Next move `wcopy and wpaste` into WSL file system location `/usr/bin/`.
## Usage/Examples
### wclip.exe usage:
Execute wclip.exe under WSL bash terminal.  
To get all the help run `wclip.exe --help`:

```bash
~
❯ wclip.exe --help
usage: wclip.exe [<flags>]

WSL-Clipboard Utility

Blazingly fast Windows clipboard utility for WSL applications and Neovim running under WSL



Flags:
  -h, --help                  Show help
  -o, --output                Output clipboard contents
  -i, --input <input-text>    Input clipboard contents

```

Set clipboard content `wclip.exe -i "Hello world 😀"`

```bash
~                                                                                         ✘ INT
❯ wclip.exe -i "你好 😀"
```

Get clipboard content `wclip.exe -o` or exetute without any flags `wclip.exe`
```bash
❯ wclip.exe --output
你好 😀  
```

It also support pips `echo "Hello world!" | wclip.exe -i`
```bash
~
❯ echo "Hello World! 😎" | wclip.exe -i
~
❯ wclip.exe
Hello World! 😎
```

### wcopy and wpaste usage:
`wcopy and wpaste` are shell script for easy usage in WSL, `wpaste` also remove `CR` at the end of the line which is came from Windows side.

`wcopy` usage, it only support pipes.
`wpaste` will output contents from clipboard, both of them do not support any flags.
```bash
~
❯ echo "Hello" | wcopy
~
❯ wpaste
Hello
```

The main reason these sctipts exists is, it is easy to use with Neovim when we use system clipboard.

### Neovim integration
If you are running Neovim under WSL and want to use system clipboard, add the lua script into your configuration:
```lua
vim.opt.clipboard = "unnamedplus"               -- allows neovim to access the system clipboard

-- Set wsl-clipboard for vim clipboard if running WSL
-- Check if the current linux kernal is microsoft WSL version
local function is_wsl()
  local version_file = io.open("/proc/version", "rb")
  if version_file ~= nil and string.find(version_file:read("*a"), "microsoft") then
    version_file:close()
    return true
  end
  return false
end

-- If current linux is under WSL then use wclip.exe
-- More info: https://github.com/memoryInject/wsl-clipboard
if is_wsl() then
  vim.g.clipboard = {
    name = "wsl-clipboard",
    copy = {
      ["+"] = "wcopy",
      ["*"] = "wcopy"
    },
    paste = {
      ["+"] = "wpaste",
      ["*"] = "wpaste"
    },
    cache_enabled = true
  }
end

```
## Screenshots

<img src="https://user-images.githubusercontent.com/72661846/193530685-24a11425-5dcf-474a-b763-cb98325f2845.jpg" width="600">


## Alternatives
If you find that wsl-clipboard doesn't quite satisfy your requirements, these may be a better fit:
- [win32yank](https://github.com/equalsraf/win32yank)


## Contributing

Contributions are always welcome!

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.



## License

[MIT](https://choosealicense.com/licenses/mit/)


## Support

For support, email msmahesh@live.com.  

More info: www.memoryinject.io
