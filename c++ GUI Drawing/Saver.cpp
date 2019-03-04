#include "Saver.h"

#include "pch.h"

using namespace concurrency;
using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Provider;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;

// Global static pointer used to ensure a single instance of the class.
Saver* Saver::instance = nullptr;

Saver::Saver()
{
}

Saver::~Saver()
{
}

Saver * Saver::GetSaver()
{
	if (!instance) instance = new Saver();
	return instance;
}

void Saver::SetPath()
{

}

int Saver::SaveCanvas(std::vector<Shape*>shapes)
{

	//get data that needs saving
	Platform::String saveData;
	
	for (Shape* sh : shapes)
	{
		std::string data = sh->ToString();
		for (char ch : data)
		{
			saveData += (char16_t)ch;
		}
	}

	FileSavePicker^ savePicker = ref new FileSavePicker();
	savePicker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;

	auto plainTextExtensions = ref new Platform::Collections::Vector<String^>();
	plainTextExtensions->Append(".txt");
	savePicker->FileTypeChoices->Insert("Plain Text", plainTextExtensions);
	savePicker->SuggestedFileName = "New Document";

	create_task(savePicker->PickSaveFileAsync()).then([this](StorageFile^ file)
	{
		if (file != nullptr)
		{
			// Prevent updates to the remote version of the file until we finish making changes and call CompleteUpdatesAsync.
			CachedFileManager::DeferUpdates(file);
			// write to file
			create_task(FileIO::WriteTextAsync(file,"")).then([this, file]()
			{
				// Let Windows know that we're finished changing the file so the other app can update the remote version of the file.
				// Completing updates may require Windows to ask for user input.
				create_task(CachedFileManager::CompleteUpdatesAsync(file)).then([this, file](FileUpdateStatus status)
				{
					if (status == FileUpdateStatus::Complete)
					{
						//OutputTextBlock->Text = "File " + file->Name + " was saved.";
					}
					else
					{
						//OutputTextBlock->Text = "File " + file->Name + " couldn't be saved.";
					}
				});
			});
		}
		else
		{
			//OutputTextBlock->Text = "Operation cancelled.";
		}
	});

	return 1;
}
