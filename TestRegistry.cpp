/*
 * Copyright (C) 2008  Remko Troncon
 * Licensed under the MIT license.
 * See COPYING for license details.
 */

#include "QtTestUtil/TestRegistry.h"

#include <QtTest/QtTest>

#include <cstdlib>
#include <iostream>

namespace QtTestUtil {

TestRegistry* TestRegistry::getInstance() {
	static TestRegistry registry;
	return &registry;
}

void TestRegistry::registerTest(QObject* test) {
	tests_ += test;
}

int TestRegistry::runTests(int argc, char* argv[]) {
	int result = 0;
	int runCount = 0;
	char buffer[100];
	foreach(QObject* test, tests_) {
		runCount++;
		sprintf(buffer, "Test_%d.xml", runCount);
		freopen(buffer, "w", stdout);
		result |= QTest::qExec(test, argc, argv);
	}
	return result;
}

}
