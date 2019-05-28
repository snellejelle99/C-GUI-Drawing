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
#include "Rectangle.h"
#include "Ellipse.h"

//commands
#include "Command.h"
#include "ChangeColorCommand.h"
#include "AddRectangleCommand.h"
#include "AddEllipseCommand.h"
#include "DeleteCommand.h"
#include "GroupCommand.h"

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

enum SelectedElem { rectangle, ellipse, cssingle, csgroup, group, del };

DrawPage::DrawPage()
{
	InitializeComponent();
}

// global initialization of required variables for creating shapes
Windows::UI::Input::PointerPoint ^startPoint;
Windows::UI::Xaml::Shapes::Rectangle ^rect;
Windows::UI::Xaml::Shapes::Ellipse ^ellip;
Shape* selectedShape = nullptr;

Windows::UI::Color selectedColor; // currently selected color
SelectedElem sElem = rectangle; // currently selected shape (default rectangle)

//list of shapes
std::vector<Shape*> shapes;

//commandstack
CMDStack commandStack = CMDStack();

void c___GUI_Drawing::DrawPage::canvas_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	// returns if shape is not selected
	if (sElem == cssingle || sElem== csgroup || sElem == group || sElem == del) return;

	startPoint = e->GetCurrentPoint(canvas);

	// create shape with selected variables
	if (sElem == rectangle)
	{
		rect = ref new Shapes::Rectangle();
		rect->AddHandler(UIElement::TappedEvent, ref new TappedEventHandler(this, &DrawPage::SelectHandler), true);
		rect->Fill = ref new SolidColorBrush(selectedColor);
		canvas->SetLeft(rect, startPoint->Position.X);
		canvas->SetTop(rect, startPoint->Position.Y);
		canvas->Children->Append(rect);
	}
	else if (sElem == ellipse)
	{
		ellip = ref new Shapes::Ellipse();
		ellip->AddHandler(UIElement::TappedEvent, ref new TappedEventHandler(this, &DrawPage::SelectHandler), true);
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

	if (sElem == rectangle)
	{
		rect->Width = w;
		rect->Height = h;

		canvas->SetLeft(rect, x);
		canvas->SetTop(rect, y);
	}
	else if (sElem == ellipse)
	{
		ellip->Width = w;
		ellip->Height = h;

		canvas->SetLeft(ellip, x);
		canvas->SetTop(ellip, y);
	}
}

void c___GUI_Drawing::DrawPage::canvas_PointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	// returns if shape is not selected
	if (sElem == cssingle || sElem == csgroup || sElem == group || sElem == del) return;

	// define cmd object and add it to the commandstack
	Command* cmd = nullptr;

	if (sElem == rectangle)
	{
		cmd = new AddRectangleCommand(canvas, shapes, rect, selectedColor);
	}
	else if (sElem == ellipse)
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
	DrawPage::RectangleSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::LightGray);
	DrawPage::EllipseSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::LightGray);
	DrawPage::ColorSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::LightGray);
	DrawPage::GroupSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::LightGray);
	DrawPage::DeleteSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::LightGray);

	if (sender->Equals(RectangleSelect))
	{
		sElem = rectangle;
		DrawPage::RectangleSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkGray);
	}
	else if (sender->Equals(EllipseSelect))
	{
		sElem = ellipse;
		DrawPage::EllipseSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkGray);
	}
	else if (sender->Equals(CSSingle))
	{
		sElem = cssingle;
		DrawPage::ColorSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkGray);
	}
	else if (sender->Equals(CSGroup))
	{
		sElem = csgroup;
		DrawPage::ColorSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkGray);
	}
	else if (sender->Equals(GroupSelect))
	{
		sElem = group;
		DrawPage::GroupSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkGray);
	}
	else if (sender->Equals(DeleteSelect))
	{
		sElem = del;
		DrawPage::DeleteSelect->Background = ref new SolidColorBrush(Windows::UI::Colors::DarkGray);
	}
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

void c___GUI_Drawing::DrawPage::SelectHandler(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	//returns if shape is selected
	if (sElem == rectangle || sElem == ellipse) return;

	if (sElem == cssingle)
	{
		Windows::UI::Xaml::Shapes::Shape^ shape = safe_cast<Windows::UI::Xaml::Shapes::Shape^>(sender);

		for (Shape* s : shapes)
		{
			if (s->CheckShape(shape) == true)
			{
				Command* cmd = new ChangeColorCommand(s, selectedColor);
				commandStack.Add(cmd);
				return;
			}
			else
			{
				std::vector<Shape*> sshapes = s->GetSubShapes();
				for (Shape* s : sshapes)
				{
					if (s->CheckShape(shape) == true)
					{
						Command* cmd = new ChangeColorCommand(s, selectedColor);
						commandStack.Add(cmd);
						return;
					}
				}
			}
		}
	}
	if (sElem == csgroup)
	{
		Windows::UI::Xaml::Shapes::Shape^ shape = safe_cast<Windows::UI::Xaml::Shapes::Shape^>(sender);

		for (Shape* s : shapes)
		{
			if (s->CheckShape(shape) == true)
			{
				Command* cmd = new ChangeColorCommand(s, selectedColor);
				commandStack.Add(cmd);
				return;
			}
			else
			{
				std::vector<Shape*> sshapes = s->GetSubShapes();
				for (Shape* s : sshapes)
				{
					if (s->CheckShape(shape) == true)
					{
						Command* cmd = new ChangeColorCommand(s, selectedColor);
						commandStack.Add(cmd);
						return;
					}
				}
			}
		}
	}
	else if (sElem == group)
	{
		Windows::UI::Xaml::Shapes::Shape^ shape = safe_cast<Windows::UI::Xaml::Shapes::Shape^>(sender);

		for (Shape* s : shapes)
		{
			if (s->CheckShape(shape) == true)
			{
				if (selectedShape != nullptr)
				{
					Command* cmd = new GroupCommand(s, selectedShape, shapes);
					commandStack.Add(cmd);
					selectedShape = nullptr;
				}
				else selectedShape = s;
				return;
			}
			else
			{
				std::vector<Shape*> sshapes = s->GetSubShapes();
				for (Shape* s : sshapes)
				{
					if (s->CheckShape(shape) == true)
					{
						if (selectedShape != nullptr)
						{
							Command* cmd = new GroupCommand(s, selectedShape, shapes);
							commandStack.Add(cmd);
							selectedShape = nullptr;
						}
						else selectedShape = s;
						return;
					}
				}
			}
		}
	}
	else if (sElem == del)
	{
		Windows::UI::Xaml::Shapes::Shape^ shape = safe_cast<Windows::UI::Xaml::Shapes::Shape^>(sender);

		for (Shape* s : shapes)
		{
			if (s->CheckShape(shape) == true)
			{
				Command* cmd = new DeleteCommand(canvas, s, shapes);
				commandStack.Add(cmd);
				return;
			}
			else
			{
				std::vector<Shape*> sshapes = s->GetSubShapes();
				for (Shape* s : sshapes)
				{
					if (s->CheckShape(shape) == true)
					{
						Command* cmd = new DeleteCommand(canvas, s, shapes);
						commandStack.Add(cmd);
						return;
					}
				}
			}
		}
	}
}

void c___GUI_Drawing::DrawPage::SaveHandler(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Saver::GetSaver()->SaveCanvas(shapes);
}
