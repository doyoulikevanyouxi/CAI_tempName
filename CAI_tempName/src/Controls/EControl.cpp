#include "caipch.h"
#include "EControl.h"
#include "Datas/ControlStyle.h"
#include "Datas/Coordinate.h"
#include "UI/PaintDeivces/PaintDevice.h"
Control::Control() noexcept 
{
	horizontAlalignment.set(Defualt);
	verticalAlignment.set(Defualt);
	marginL.set(0);
	marginR.set(0);
	marginT.set(0);
	marginB.set(0);
}

Control::~Control() noexcept
{
	//if(border!=nullptr)
	//	delete border;
}

void Control::setMargin(float left, float top, float right, float bottom) noexcept
{
	Size& size = vData.AreaSize();
	float x = size.X();
	float y = size.Y();
	size.SetX(x+left-right);
	size.SetY(y+top-bottom);
	marginL.set(left);
	marginR.set(right);
	marginT.set(top);
	marginB.set(bottom);
}

void Control::setHorizontalAlignment(RelativeLocation value)
{
	horizontAlalignment.set(value);
}

void Control::setVerticalAlignment(RelativeLocation value)
{
	verticalAlignment.set(value);
}

Size Control::Measure(const Size& size) noexcept
{
	UIElement::Measure(size);
	RelativeLocation hor = horizontAlalignment.get();
	RelativeLocation ver = verticalAlignment.get();
	float x = 0;
	float y = 0;
	
	if (actualWidth >= size.Height()) {
		x = 0;
	}
	else {
		switch (hor)
		{
		case Center:
			x = (size.Width() - actualWidth) / 2;
			break;
		case Left:
			x = 0;
			break;
		case Right:
			x = size.Width() - actualWidth;
			break;
		default:
			break;
		}
	}
	

	if (actualHeight >= size.Height()) {
		y = 0;
	}
	else {
		switch (ver)
		{
		case Center:
			y = (size.Height() - actualHeight) / 2;
			break;
		case Top:
			y = 0;
			break;
		case Bottom:
			y = size.Height() - actualHeight;
			break;
		default:
			break;
		}
	}
	Size& sz = vData.AreaSize();
	float xz = sz.X();
	float yz = sz.Y();
	vData.SetPoint(xz + x, yz + y, sz.Z());
	pDevice->UpdateVertex(vData.VertexData());
	return vData.ContentSize();
}

