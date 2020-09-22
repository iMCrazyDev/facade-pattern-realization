#include <iostream>


class RAR {
public:
	bool Decompress(std::string filename1, std::string filename2,int rardepth, int decodetyper)
	{
		return true;
	}

	bool Compress(std::string filename1, std::string filename2, int rardepth, int decodetyper)
	{
		return true;
	}
};
/**
 * Некоторые фасады могут работать с разными подсистемами одновременно.
 */
class ZIP {
public:
	bool Decompress(std::string filename1, std::string filename2, int ziplevels)
	{
		return true;
	}

	bool Compress(std::string filename1, std::string filename2, int ziplevels)
	{
		return true;
	}
};

class Facade {
protected:
	RAR* rar;
	ZIP* zip;

public:
	
	Facade(
		RAR* subsystem1 = nullptr,
		ZIP* subsystem2 = nullptr) {
		this->rar = subsystem1 ? nullptr : new RAR;
		this->zip = subsystem2 ? nullptr : new ZIP;
	}
	~Facade() {
		delete rar;
		delete zip;
	}
	
	bool Compress(std::string filename1, std::string filename2) {
		auto fname = filename1.substr(filename2.size() - 4, 3);
		if (fname == "zip")
		{
			zip->Compress(filename1, filename2, 2);
		}
		else if (fname == "rar")
		{
			rar->Compress(filename1, filename2, 1, 17);
		}
		return false;
	}

	bool Decompress(std::string filename1, std::string filename2) {
		auto fname = filename1.substr(filename1.size() - 4, 3);
		if (fname == "zip")
		{
			zip->Decompress(filename1, filename2, 2);
		}
		else if (fname == "rar")
		{
			rar->Decompress(filename1, filename2, 1, 17);
		}
		return false;
	}
};



int main() {
	RAR* subsystem1 = new RAR;
	ZIP* subsystem2 = new ZIP;
	Facade* facade = new Facade(subsystem1, subsystem2);
	
	facade->Compress("inp.exe", "out.rar");
	facade->Decompress("out.rar", "res.exe");

	delete facade;

	return 0;
}
