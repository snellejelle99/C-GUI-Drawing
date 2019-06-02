#pragma once

#include "DrawPage.g.h"
#include "DrawPage.xaml.h"
#include "pch.h"


#include "Shape.h"
#include "Rectangle.h"
#include "Ellipse.h"

#include <string>


using namespace concurrency;
using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;


class Loader
{
public:
	Loader(c___GUI_Drawing::DrawPage ^ drawpage,Windows::UI::Xaml::Controls::Canvas ^ canvas, std::vector<Shape*> & shapes);
	~Loader();
	void LoadFile();	

private:
	std::string ConvertString(String^ string);
	std::vector<std::string> StringSplitOnChar(std::string string, char token);

	//build from the loadedstring
	void Build(std::string loadedstring);

	c___GUI_Drawing::DrawPage ^ drawpage;
	Windows::UI::Xaml::Controls::Canvas ^ canvas;
	std::vector<Shape*> & shapes;

};

