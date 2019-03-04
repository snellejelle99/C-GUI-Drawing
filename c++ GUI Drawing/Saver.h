#ifndef SAVER
#define SAVER

#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <collection.h>

#include "Shape.h"


class Saver
{
public:	
	~Saver();
	static Saver* GetSaver();

	void SetPath();

	int SaveCanvas(std::vector<Shape*>);

private:
	Saver();							  // default constructor is private
	Saver(Saver const&) {};             // copy constructor is private
	Saver& operator=(Saver const&) {};  // assignment operator is private

	static Saver * instance;
	std::experimental::filesystem::path savePath;
};



#endif