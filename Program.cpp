/*
 * Copyright (C) 2008  Remko Troncon
 * Licensed under the MIT license.
 * See COPYING for license details.
 */

#include <QCoreApplication>
#include <cstdlib>
#include <iostream>

#include "Test/TestBase.h"
#include "QtTestUtil/TestRegistry.h"

/**
 * Runs all tests registered with the QtTestUtil registry.
 */
int main(int argc, char* argv[]) {
    char *tcpApiServer(getenv("TCP_API_SERVER"));
	BaseUrl = tcpApiServer;
    if (tcpApiServer == NULL)
    {
        std::cout << "$TCP_API_SERVER is not set!" << std::endl;
    }
    else
    {
        std::cout << "$TCP_API_SERVER is set to '" << tcpApiServer << "'" << std::endl;
    }

	QCoreApplication application(argc, argv);
	return QtTestUtil::TestRegistry::getInstance()->runTests(argc, argv);
}
