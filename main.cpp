#include <iostream>
#include <fstream>
#include <string>
#include "src/sowa.cpp"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Please specify input file" << endl;
		return 1;
	}

	fstream in;
	in.open(argv[1], ios::in);

	string temp, src = "";
	if (in.good())
	{
		while (!in.eof())
		{
			getline(in, temp);
			src += temp;
		}
		in.close();
	}
	else
	{
		cout << "Error" << endl;
	}

	src += "\0";

	// cout<<src;
	sowa_compile(src);

	return 0;
}