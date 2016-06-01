#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "AtlBase.h"
#include "AtlConv.h"

// Sources for a lot of the inspiration behind this function:
// - http://stackoverflow.com/q/6851339/6050866
// - https://developersarea.wordpress.com/2014/09/26/win32-file-watcher-api-to-monitor-directory-changes/
// - http://www.codeguru.com/cpp/w-p/files/article.php/c4467/Spying-a-File-System.htm
// As well as MSDN docs referenced in code.
void watchDir() {
	// To convert LPTSTR to std::string. Not sure if using this macro is best practice, but it works
	// Source: http://www.dreamincode.net/forums/topic/51457-can-someone-help-me-on-converting-from-tchar-to-char/
	USES_CONVERSION;
	// Set the path to the folder that the logs will be kept
	LPTSTR watchFolderPath = _T("..\\CSP2104-Assignment\\Logs");
	BOOL result = TRUE;

	/* Reading and loading watchlist. I am assuming here that the watchlist is a
	txtfile of words placed in the AuditLogApp project directory. I am also assuming
	that the words are separated by either line or space. */
	const std::string WATCHLISTFN = "watchlist.txt";
	std::vector<std::string> watchList;
	std::string tempString;
	std::ifstream file(WATCHLISTFN, std::ifstream::in);
	if (file.is_open()) {
		while (file >> tempString) {
			watchList.push_back(tempString);
		}
		file.close();
	} else {
		std::cout << "Watchlist file could not be opened!" << std::endl;
		return;
	}
	int wordsRead = 0;
	
	// Create handle for directory to be watched, granting read permissions
	// Source: https://msdn.microsoft.com/en-us/library/windows/desktop/aa363874(v=vs.85).aspx
	HANDLE watchDirHandle = CreateFile(
		watchFolderPath,
		GENERIC_READ |
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ |		// Allows other processes to Read/Write/Delete files in the folder
		FILE_SHARE_WRITE |
		FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS |
		FILE_FLAG_OVERLAPPED,
		NULL
	);

	if (watchDirHandle == INVALID_HANDLE_VALUE) {
		std::cout << "Failed to open directory!" << std::endl;
		return;
	}

	// Setup an IO Completion Port
	// Source: https://msdn.microsoft.com/en-us/library/windows/desktop/aa365198(v=vs.85).aspx
	HANDLE ioCP = CreateIoCompletionPort(
		watchDirHandle,
		NULL,
		NULL,
		1
	);

	std::cout << "Watching log file for words..." << std::endl;
	while (true) {
		char buffer[2048];
		DWORD bytesReturned;
		OVERLAPPED overlapped = { 0 };
		// Allows us to obtain the directory change notifications
		// Source: https://msdn.microsoft.com/en-us/library/aa365465(v=vs.85).aspx
		result = ReadDirectoryChangesW(
			watchDirHandle,
			&buffer,
			sizeof(buffer),
			FALSE,
			FILE_NOTIFY_CHANGE_CREATION |
			FILE_NOTIFY_CHANGE_LAST_WRITE,
			&bytesReturned,
			&overlapped,
			NULL
		);

		if (!result) {
			std::cout << "ReadDirectoryChangesW failed! Error: " << GetLastError() << std::endl;
			return;
		}

		ULONG_PTR key;
		LPOVERLAPPED overlappedResult;

		// Waits for IO queue to complete, this should help avoid file lock issues
		// Source: https://msdn.microsoft.com/en-us/library/windows/desktop/aa364986(v=vs.85).aspx
		result = GetQueuedCompletionStatus(
			ioCP,
			&bytesReturned,
			&key,
			&overlappedResult,
			// After 10 mins (600,000ms) of no changes to the log file the application will time out and close
			600000
		);

		if (!result) {
			std::cout << "Application has timed out!" << std::endl;
			return;
		}

		FILE_NOTIFY_INFORMATION *fileNotifyInfo;
		int offset = 0;

		do {
			fileNotifyInfo = (FILE_NOTIFY_INFORMATION*)((char*)buffer + offset);
			
			std::string fileName(fileNotifyInfo->FileName, 
				fileNotifyInfo->FileName + fileNotifyInfo->FileNameLength / 2);
			std::string folderPath = T2A(watchFolderPath);
			std::string filePath = folderPath + "\\" + fileName;
			std::ifstream file(filePath, std::ifstream::in);
			int wordIndex = 0;
			std::string tempLogString;
			if (file.is_open()) {
				while (file >> tempLogString) {
					wordIndex++;
					/* There are 3 "words" per line - date, time and the word we're looking for,
					so only search the vector if the we're on the 3rd word. Also check that we aren't
					searching for words we've already processed - this isn't the most efficient way
					to do that, but in this situation it's fine. */
					if (wordIndex % 3 == 0 && wordIndex > wordsRead) {
						// Search for word in our list of watchlist words
						if (std::find(watchList.begin(), watchList.end(), tempLogString) != watchList.end()) {
							std::string messageString = "Word found: " + tempLogString;
							// Display a messagebox when a word on the word list is entered
							MessageBoxA(NULL, messageString.c_str(), "Message", MB_OK | MB_ICONWARNING);
						}
					}
				}
				wordsRead = wordIndex;
				file.close();
			} else {
				std::cout << "Log file could not be opened!" << std::endl;
				return;
			}

			offset += fileNotifyInfo->NextEntryOffset;
		} while (fileNotifyInfo->NextEntryOffset);

	}
}

void main() {
	watchDir();
	system("pause");
}