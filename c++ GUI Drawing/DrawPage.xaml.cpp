//
// DrawPage.xaml.cpp
// Implementation of the DrawPage class
//

#include "pch.h"
#include "DrawPage.xaml.h"

//saver singleton
#include "Saver.h"

//shapes
#include "Shape.h"

//commands
#include "Command.h"
#include "ChangeColorCommand.h"
#include "AddRectangleCommand.h"
#include "AddEllipseCommand.h"

//commandstack
#include "CommandStack.h"

//#include <cmath>

using namespace c___GUI_Drawing;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
//using namespace Windows::UI::Xaml::Shapes;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

enum CShape { rectangle, ellipse };

DrawPage::DrawPage()
{
	InitializeComponent();
}

// global initialization of required variables for creating shapes
Windows::UI::Input::PointerPoint ^startPoint;
Windows::UI::Xaml::Shapes::Rectangle ^rect;
Windows::UI::Xaml::Shapes::Ellipse ^ellip;

Windows::UI::Color selectedColor; // currently selected color
CShape curShape = rectangle; // currently selected shape (default rectangle)

//list of shapes
std::vector<Shape*> shapes;

//commandstack
CMDStack commandStack = CMDStack();

void c___GUI_Drawing::DrawPage::canvas_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	startPoint = e->GetCurrentPoint(canvas);

	// create shape with selected variables
	if (curShape == rectangle)
	{
		rect = ref new Shapes::Rectangle();
		rect->Fill = ref new SolidColorBrush(selectedColor);
		canvas->SetLeft(rect, startPoint->Position.X);
		canvas->SetTop(rect, startPoint->Position.Y);
		canvas->Children->Append(rect);
	}
	else if (curShape == ellipse)
	{
		ellip = ref new Shapes::Ellipse();
		ellip->Fill = ref new SolidColorBrush(selectedColor);
		canvas->SetLeft(ellip, startPoint->Position.X);
		canvas->SetTop(ellip, startPoint->Position.Y);
		canvas->Children->Append(ellip);
	}
}

void c___GUI_Drawing::DrawPage::canvas_PointerMoved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	// returns when no modification to the shape needs to be done
	if (e->Pointer->IsInContact == false || (rect == nullptr && ellip == nullptr))
		return;

	// updates shape with new variables
	Windows::UI::Input::PointerPoint ^pos = e->GetCurrentPoint(canvas);

	double x = min(pos->Position.X, startPoint->Position.X);
	double y = min(pos->Position.Y, startPoint->Position.Y);

	double w = max(pos->Position.X, startPoint->Position.X) - x;
	double h = max(pos->Position.Y, startPoint->Position.Y) - y;

	if (curShape == rectangle)
	{
		rect->Width = w;
		rect->Height = h;

		canvas->SetLeft(rect, x);
		canvas->SetTop(rect, y);
	}
	else if (curShape == ellipse)
	{
		ellip->Width = w;
		ellip->Height = h;

		canvas->SetLeft(ellip, x);
		canvas->SetTop(ellip, y);
	}
}

void c___GUI_Drawing::DrawPage::canvas_PointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	// define cmd object and add it to the commandstack
	Command* cmd = nullptr;

	if (curShape == rectangle) 
	{
		cmd = new AddRectangleCommand(canvas, shapes, rect, selectedColor);
	}
	else if (curShape == ellipse)
	{
		cmd = new AddEllipseCommand(canvas, shapes, ellip, selectedColor);
	}

	commandStack.Add(cmd);
	cmd = nullptr;


	rect = nullptr;
	ellip = nullptr;
}

void c___GUI_Drawing::DrawPage::ObjectToggle(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (sender->Equals(RectangleObject))
		curShape = rectangle;
	else if (sender->Equals(EllipseObject))
		curShape = ellipse;
}

void c___GUI_Drawing::DrawPage::ColorPicker_ColorChanged(Windows::UI::Xaml::Controls::ColorPicker^ sender, Windows::UI::Xaml::Controls::ColorChangedEventArgs^ args)
{
	selectedColor = sender->Color;
}

void c___GUI_Drawing::DrawPage::UndoHandler(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	commandStack.Undo();
}

void c___GUI_Drawing::DrawPage::RedoHandler(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	commandStack.Redo();
}

void c___GUI_Drawing::DrawPage::SaveHandler(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Saver::GetSaver()->SaveCanvas(shapes);
}
