#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <sstream>
#include <fstream>
#include "AuditLog.h"

AuditLog::AuditLog() {
	/* Get the current date and time, format as desired and create file name
	Source: http://stackoverflow.com/a/17223443/6050866 */
	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::stringstream ss;
	/* Generate file name based on date and time (to the minute). This way we're going
	to generate a new txtfile each time the application is run. This makes the monitoring
	program a bit easier to work with. */
	ss << std::put_time(std::localtime(&now), "%Y-%m-%d_%H-%M");
	m_fileName = "Logs\\log_" + ss.str() + ".LOG";
}

void AuditLog::addToLog(const std::string &inString) {
	std::ofstream file;
	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::stringstream ss;
	ss << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S");

	/* Open file in output and append mode. ".open()" will create the file 
	if it doesn't already exist */
	file.open(m_fileName, std::ofstream::out | std::ofstream::app);
	if (file.is_open()) {
		file << ss.str() + ": " + inString + "\n";
		file.close();
	}
	else std::cout << "File could not be opened, log not updated.";
}