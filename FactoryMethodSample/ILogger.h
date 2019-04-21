
#ifndef ILOGGER_H
#define ILOGGER_H

typedef struct ILogger ILogger;

struct ILogger
{
	void *pImplicit;

	void (* WriteLog)();

	void (* Free)(ILogger **ppLogger);
};

#endif // !ILOGGER_H
