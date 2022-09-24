#include <iostream>
#include <Windows.h>
#include <codecvt>


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

int main()
{
    // Set the console output to support UTF-8 Unicode
    if (IsValidCodePage(CP_UTF8)) {
	    SetConsoleOutputCP(CP_UTF8);
    }
	//SetConsoleOutputCP(CP_UTF8);

    get_clipboard_text();
	return 0;
}
