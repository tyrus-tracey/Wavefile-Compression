#include "myWaveFile.h"
#include "wx/wx.h"
#include "intrin.h"

// Using base class constructor, open the wave file in binary mode
myWaveFile::myWaveFile(wxString filepath)
	: wxFFile(filepath, "rb")
{
	filesize = 0; 

	chunk1Size = 0;
	audioFormat = 0;
	channels = 0;
	sampleRate = 0;
	byteRate = 0;
	blockAlign = 0; 
	bitsPerSample = 0;
	numberOfSamples = 0;
	chunk2Size = 0;
	maxAmplitude = 0;
}

myWaveFile::~myWaveFile() {
}

// Check that selected file is indeed a wave file.
bool myWaveFile::readHeader() {
	char buffer4B[5];

	Read(buffer4B, 4);
	buffer4B[4] = '\0';
	if (strcmp(buffer4B, "RIFF")) {
		return false;
	}

	Read(&filesize, sizeof(filesize));

	Read(buffer4B, 4);
	buffer4B[4] = '\0';
	if (strcmp(buffer4B, "WAVE")) {
		return false;
	}

	return true;
}

// Read subchunk 1 to myWaveFile member variables
void myWaveFile::readSubChunk1() {
	//verify fmt
	char charBuffer[5];

	Read(charBuffer, 4);
	charBuffer[4] = '\0';
	if (strcmp(charBuffer, "fmt ")) {
		wxMessageBox("Error: fmt missing");
		return;
	}

	Read(&chunk1Size, 4);
	Read(&audioFormat, 2);
	Read(&channels, 2);
	Read(&sampleRate, 4);
	Read(&byteRate, 4);
	Read(&blockAlign, 2);
	Read(&bitsPerSample, 2);
}

// Read subchunk 2 to myWaveFile member variables.
void myWaveFile::readSubChunk2() {
	char charBuffer[5];

	Read(charBuffer, 4);
	charBuffer[4] = '\0';
	if (strcmp(charBuffer, "data")) {
		wxMessageBox("Error: Unable to locate data subchunk");
		return;
	}

	Read(&chunk2Size, sizeof(chunk2Size));

	numberOfSamples = (chunk2Size / channels) / (bitsPerSample / 8);

	int i = 0;
	long max = 0;
	//Begin reading audio data
	if (bitsPerSample == 8) {
		dataArray8b = new uint8_t[numberOfSamples];
		uint8_t* ptr = dataArray8b;
		for (i = 0; i < numberOfSamples; i++) {
			Read(ptr, 1);
			if (abs(*ptr) > max) { max = *ptr; }
			ptr++;
		}
	}
	else if (bitsPerSample == 16) {
		dataArray16b = new short[numberOfSamples];
		short* ptr = dataArray16b;
		for (i = 0; i < numberOfSamples; i++) {
			Read(ptr, 2);
			if (abs(*ptr) > max) { max = *ptr; }
			ptr++;
		}
	}
	maxAmplitude = max;
	Close(); // Indicate successful read
}

unsigned short myWaveFile::getAudioFormat() const
{
	return audioFormat;
}

unsigned short myWaveFile::getChannels() const
{
	return channels;
}

uint32_t myWaveFile::getSampleRate() const
{
	return sampleRate;
}

uint32_t myWaveFile::getByteRate() const
{
	return byteRate;
}

unsigned short myWaveFile::getBitsPerSample() const
{
	return bitsPerSample;
}

int myWaveFile::getNumberOfSamples() const
{
	return numberOfSamples;
}

long myWaveFile::getMaxAmplitude() const
{
	return maxAmplitude;
}

