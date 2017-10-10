#include "stdafx.h"
#include "CppUnitTest.h"
#include "Poco/Path.h"
#include "Poco/File.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(test_poco_file)
	{
	public:
		TEST_METHOD(Test_Path)
		{
			Poco::Path path("../log/0/log.txt");
			Assert::AreEqual("..\\log\\0\\log.txt", path.toString().c_str());
			Assert::AreEqual("log", path.getBaseName().c_str());
			Assert::AreEqual("log.txt", path.getFileName().c_str());
			Assert::AreEqual("txt", path.getExtension().c_str());

			auto parent = path.makeParent();
			Assert::AreEqual("..\\log\\0\\", parent.toString().c_str());
			Assert::AreEqual("..\\log\\0\\", path.toString().c_str());
		}

		TEST_METHOD(Test_File)
		{
			Poco::File file("../0/log.txt");
			Assert::AreEqual("../0/log.txt", file.path().c_str());
			Poco::File dir(Poco::Path(file.path().c_str()).parent());
			Assert::AreEqual("..\\0", dir.path().c_str());
			if (!dir.exists())
				dir.createDirectory();
			Assert::IsTrue(dir.exists());
			if (!file.exists())
				Assert::IsTrue(file.createFile());
			Assert::IsTrue(file.isFile());
		}
	};
}