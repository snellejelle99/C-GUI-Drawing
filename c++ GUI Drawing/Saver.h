#ifndef SAVER
#define SAVER

#include "pch.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <collection.h>

#include "Shape.h"

using namespace concurrency;
using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Provider;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;

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

	StorageFile^ saveFile = nullptr;
};



#endif