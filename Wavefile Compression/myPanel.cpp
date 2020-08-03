#include "myPanel.h"

//Bind paint events to this panel
wxBEGIN_EVENT_TABLE(myPanel, wxPanel)
EVT_PAINT(myPanel::paintEvent)
END_EVENT_TABLE()

myPanel::myPanel(wxFrame* parent, const wxString filepath) 
	: wxPanel(parent, wxID_ANY, wxPoint(0,0), parent->GetSize())
{
	wavFile = new myWaveFile(filepath);
	if(wavFile == NULL) {
		wxMessageBox("Error: Could not find associated WAVE file.");
	}
	maxSize = parent->GetSize();
	SetSize(maxSize);
	midHeight	= maxSize.y / 2;
	maxHeight	= maxSize.y;
	midWidth	= maxSize.x / 2;
	maxWidth	= maxSize.x;
	SetBackgroundStyle(wxBG_STYLE_PAINT);
}

myPanel::~myPanel()
{
	delete wavFile; //required to delete manually allocated elements of myWaveFile
}

// 'dc' is a device context (the screen) that is used for drawing on the panel
void myPanel::paintEvent(wxPaintEvent& event)
{
	wxBufferedPaintDC dc(this);
	PrepareDC(dc);
	drawBackground(dc);
	displayCompression(dc);
}

// Prepare a clean background to draw on.
void myPanel::drawBackground(wxDC& dc)
{
	wxBrush brush = dc.GetBrush();	// Rectangle body 
	wxPen pen = dc.GetPen();		// Rectangle border
	pen.SetStyle(wxPENSTYLE_SOLID);
	pen.SetColour(wxColour(100,150,200));
	dc.SetPen(pen);
	dc.SetBrush(brush);
	dc.DrawRectangle(wxRect(maxSize));
	return;
}

// Performs compression and displays compression ratios
void myPanel::displayCompression(wxDC& dc) {

	// Read wave file
	if (wavFile->IsOpened()) {
		if (!wavFile->readHeader()) {
			wxMessageBox("Error: Unable to parse header");
		}
		else {
			wavFile->readSubChunk1();
			wavFile->readSubChunk2();
		}
	}
	if (!wavFile->IsOpened()) {
		int lzwSize = wavFile->lzwCompression();
		int hufSize = wavFile->huffmanCompression();
		double lzwComp = double(wavFile->fileSize()) / lzwSize;
		double hufComp = double(wavFile->fileSize()) / hufSize;
		wxString hufTxt = "Huffman Compression Ratio: " + wxString::Format(wxT("%f"), hufComp);
		wxString lzwTxt = "LZW Compression Ratio: " + wxString::Format(wxT("%f"), lzwComp);
		dc.DrawText(lzwTxt, wxPoint(10, 5));
		dc.DrawText(hufTxt, wxPoint(10, 25));
	}
}

myWaveFile* myPanel::getFile()
{
	return wavFile;
}