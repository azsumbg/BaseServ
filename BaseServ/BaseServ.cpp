#include "pch.h"
#include "BaseServ.h"

// RANDIT ***********************

dll::RANDIT::RANDIT()
{
	sq = new std::seed_seq{ rd(),rd(), rd(), rd(), rd(), rd(), rd(), rd() };
	twister = new std::mt19937(*sq);
}
dll::RANDIT::~RANDIT()
{
	if (sq)delete sq;
	if (twister)delete twister;
}
int dll::RANDIT::operator()(int min, int max)
{
	std::uniform_int_distribution distrib(min, max);
	return distrib(*twister);
}

/////////////////////////////////

// PROTON ***********************

dll::PROTON::PROTON(float _x, float _y, float _width, float _height)
{
	start.x = _x;
	start.y = _y;

	width = _width;
	height = _height;

	end.x = start.x + width;
	end.y = start.y + height;

	center.x = start.x + width / 2;
	center.y = start.y + height / 2;
}
dll::PROTON::PROTON()
{
	start.x = 0;
	start.y = 0;

	width = 1.0f;
	height = 1.0f;

	end.x = start.x + width;
	end.y = start.y + height;

	center.x = start.x + width / 2;
	center.y = start.y + height / 2;
}
void dll::PROTON::SetEdges()
{
	end.x = start.x + width;
	end.y = start.y + height;

	center.x = start.x + width / 2;
	center.y = start.y + height / 2;
}
void dll::PROTON::NewDims(float _width, float _height)
{
	width = _width;
	height = _height;

	end.x = start.x + width;
	end.y = start.y + height;

	center.x = start.x + width / 2;
	center.y = start.y + height / 2;
}
void dll::PROTON::SetWidth(float _width)
{
	width = _width;
	
	end.x = start.x + width;
	
	center.x = start.x + width / 2;
}
void dll::PROTON::SetHeight(float _height)
{
	height = _height;

	end.y = start.y + height;

	center.y = start.y + height / 2;
}
float dll::PROTON::GetWidth() const
{
	return width;
}
float dll::PROTON::GetHeight() const
{
	return height;
}

/////////////////////////////////