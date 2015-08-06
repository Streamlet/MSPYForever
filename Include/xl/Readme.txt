Directories Instruction

Common:
	Dependent on and only on C++ complie.
	The using of CRT header files or STL header files is forbidden.
	Platform related code is forbidden.
	Direct input and output of predefined information is forbiddin.

Windows:
	Dependent on C++ compile, files from Common, and Windows header files.
	The using of CRT header files or STL header files is forbidden.
	Direct input and output of predefined information is forbiddin.

Linux:
	Dependent on C++ compile, files from Common, and Linux header files.
	The using of CRT header files or STL header files is forbidden.
	Direct input and output of predefined information is forbiddin.

CrossPlatform:
	Dependent on C++ compile, files from Common/Windows/Linux, CRT header files, STL header files.
	Direct input and output of predefined information is forbiddin.

AppHelper:
	Dependent on C++ compile, files from Common/Windows/Linux/CrossPlatform, CRT header files, STL header files.
