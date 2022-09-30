#include <iostream>
#include <Windows.h>
#include <codecvt>
#include <unordered_set>
#include <string>

bool set_clipboard_text(std::wstring textToclipboard) {
	if (OpenClipboard(NULL)) {
		EmptyClipboard();
		HGLOBAL hClipboardData;
		size_t size = (textToclipboard.length() + 1) * sizeof(wchar_t);
		hClipboardData = GlobalAlloc(NULL, size);
		wchar_t* pchData = (wchar_t*)GlobalLock(hClipboardData);

		memcpy(pchData, textToclipboard.c_str(), size);
		SetClipboardData(CF_UNICODETEXT, hClipboardData);
		GlobalUnlock(hClipboardData);
		CloseClipboard();
		return true;
	}
	return false;
}


void get_clipboard_text() {
    // Try to Open clipboard
    if (!OpenClipboard(nullptr)) {
        return;
    }

    // Get handle of clipboard object for ANSI text
    HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
    if (hClipboardData == nullptr) {
        CloseClipboard();
        return;
    }

    // Lock the handle to get the actual text pointer
    wchar_t* clip_text = static_cast<wchar_t*>(GlobalLock(hClipboardData));//
    if (clip_text == nullptr) {
        CloseClipboard();
        return;
    }

    // Store the text into wstring
    std::wstring strText = clip_text;
	std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> convert;
	auto p = reinterpret_cast<const int16_t*>(strText.data());

    // convert wstring to basic string for console output
    // printf("%s", convert.to_bytes(p, p + strText.size()));
    std::cout << convert.to_bytes(p, p + strText.size());


    // Release the lock
    GlobalUnlock(hClipboardData);

    // Release the clipboard/
    CloseClipboard();
}

std::unordered_set<std::wstring> output_args({ L"-o", L"--output" });
std::unordered_set<std::wstring> input_args({ L"-i", L"--input" });
std::unordered_set<std::wstring> help_args({ L"-h", L"--help" });

int wmain(int argc, wchar_t* argv[])
{
    // Set the console output to support UTF-8 Unicode
    if (IsValidCodePage(CP_UTF8)) {
	    SetConsoleOutputCP(CP_UTF8);
    }

    // If we don't pass any argument when executing `./wclip.exe`
    // output the contents from clipboard
    if (argc == 1) {
        get_clipboard_text();
        return 0;
    }

    // If we pass argument like './wclip.exe -o' or 'wclip.exe --output' 
    // output the contents from clipboard
    if (argc == 2 && (output_args.find(argv[1]) != output_args.end())) {
        get_clipboard_text();
        return 0;
    }

    // If we pass argument like './wclip.exe -i "Hello World!"' or 'wclip.exe --input "Hello World!"' 
    // set the clipboard content to passed 3rd argument: "Hello World!"
    if (argc == 3 && (input_args.find(argv[1]) != input_args.end())) {
        set_clipboard_text(argv[2]);
        return 0;
    }

	// else use it as a pipe e.g., echo "Hello world!" | setClip.exe -i
    if (argc == 2 && (input_args.find(argv[1]) != input_args.end())) {
		std::string txt;
		bool first_line = true;
		while (!std::cin.eof())
		{
			std::string line;
			std::getline(std::cin, line);
			if (first_line) {
				txt += line;
				first_line = false;
				continue;
			}
			txt += '\n' + line;
		}
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wide = converter.from_bytes(txt);
		set_clipboard_text(wide);
        return 0;
    }

    // Help argument: `wclip.exe -h` or `wclip.exe --help`
    if (argc == 2 && (help_args.find(argv[1]) != help_args.end())) {
        std::cout 
            << "usage: wclip.exe [<flags>]\n\n" 
            << "WSL-Clipboard Utility\n\n"
			<< "Blazingly fast Windows clipboard utility for WSL applications and Neovim running under WSL\n\n"
            << "\n\n"
            << "Flags:\n"
            << "  -h, --help                  Show help\n"
            << "  -o, --output                Output clipboard contents\n"
            << "  -i, --input <input-text>    Input clipboard contents\n"
            << std::endl;
        return 0;
    }

	return 0;
}
