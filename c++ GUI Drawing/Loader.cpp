#include "Loader.h"

Loader::Loader(Windows::UI::Xaml::Controls::Canvas ^ canvas, std::vector<Shape*>& shapes) : canvas(canvas), shapes(shapes)
{
}

Loader::~Loader()
{
}

void Loader::LoadFile()
{
	FileOpenPicker^ openPicker = ref new FileOpenPicker();
	openPicker->ViewMode = PickerViewMode::Thumbnail;
	openPicker->SuggestedStartLocation = PickerLocationId::PicturesLibrary;
	openPicker->FileTypeFilter->Append(".TXT");
	openPicker->FileTypeFilter->Append(".txt");


	create_task(openPicker->PickSingleFileAsync()).then([this](StorageFile^ file)
	{
		if (file)
		{
			create_task(FileIO::ReadTextAsync(file)).then([this, file](task<String^> task)
			{
				try
				{
					String^ fileContent = task.get();
					Build(StringToLines(ConvertString(fileContent)));
					//rootPage->NotifyUser("The following text was read from '" + file->Name + "':\n" + fileContent, NotifyType::StatusMessage);
				}
				catch (COMException^ ex)
				{
					if (ex->HResult == HRESULT_FROM_WIN32(ERROR_NO_UNICODE_TRANSLATION))
					{
						//rootPage->NotifyUser("File could not be decoded as Unicode.", NotifyType::ErrorMessage);
					}
					else
					{
						//rootPage->HandleIoException(ex, "Error reading from '" + file->Name + "'");
					}
				}
			});
		}
		else
		{
			//OutputTextBlock->Text = "Operation cancelled.";
		}
	});
}


std::string Loader::ConvertString(String ^ winString)
{
	
	std::wstring fooW(winString->Begin());
	std::string fooA(fooW.begin(), fooW.end());
	return fooA;
}

std::vector<std::string> Loader::StringToLines(std::string string)
{
	std::vector<std::string> result;
	std::string temp;
	int markbegin = 0;
	int markend = 0;

	for (int i = 0; i < string.length(); ++i) {		
		if (string[i] == '\n') {
			markend = i;
			result.push_back(string.substr(markbegin, markend - markbegin));
			markbegin = (i + 1);
		}
	}
	return result;
}

void Loader::Build(std::vector<std::string> lines)
{

}
