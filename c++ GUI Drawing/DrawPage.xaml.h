﻿//
// DrawPage.xaml.h
// Declaration of the DrawPage class
//

#pragma once

#include "DrawPage.g.h"

namespace c___GUI_Drawing
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class DrawPage sealed
	{
	public:
		DrawPage();
	private:		
		void canvas_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void canvas_PointerMoved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void canvas_PointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void UndoHandler(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ObjectToggle(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ColorPicker_ColorChanged(Windows::UI::Xaml::Controls::ColorPicker^ sender, Windows::UI::Xaml::Controls::ColorChangedEventArgs^ args);
		void RedoHandler(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
