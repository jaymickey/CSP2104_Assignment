#ifndef AUDITLOG_H
#define AUDITLOG_H
#include <string>

class AuditLog {
	private:
		std::string m_fileName;
	public:
		AuditLog();
		void addToLog(const std::string &);
};

#endif // AUDITLOG_H