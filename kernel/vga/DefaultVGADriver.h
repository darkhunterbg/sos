#pragma once

#include "IVGADriver.h"

namespace vga
{
	/*
	PALETTE:
	0		Black		|	0+8=8		Dark Gray
	1		Blue		|	1+8=9		Light Blue
	2		Green		|	2+8=A		Light Green
	3		Cyan		|	3+8=B		Light Cyan
	4		Red			|	4+8=C		Light Red
	5		Magenta		|	5+8=D		Light Magenta
	6		Brown		|	6+8=E		Yellow
	7		Light Gray	|	7+8=F		White
	*/
	
class DefaultVGADriver : public IVGADriver
{
  private:
    volatile byte* videoMemory;
	
	VGAParameters parameters;
	VGAPalette palette;
	static  const uint VIDEO_MEMORY;
  public:
    DefaultVGADriver();
    ~DefaultVGADriver();

    virtual void Print(char symbol, uint x, uint y, byte color) override;
	virtual const VGAPalette& GetPalette()  const override;
	virtual const VGAParameters& GetParameters() const override;
	virtual void ClearScreen(byte color) override;
};
}
