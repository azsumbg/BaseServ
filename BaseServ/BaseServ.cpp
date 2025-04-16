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

// BASE **************************

dll::BASE::BASE(unsigned char _what_type, float _put_x, float _put_y)
	:PROTON(_put_x, _put_y, 1.0f, 1.0f)
{
	type = _what_type;

	switch (type)
	{
	case hero:
		NewDims(80.0f, 105.0f);
		state = states::stand;
		lifes = 100;
		speed = 2.0f;
		strenght = 20;
		attack_chance = 3;
		max_frames = 5;
		frame_delay = 15;
		break;

	case zombie1:
		NewDims(69.0f, 100.0f);
		state = states::run;
		lifes = 100;
		speed = 0.8f;
		strenght = 10;
		attack_chance = 5;
		max_frames = 9;
		frame_delay = 8;
		break;

	case zombie2:
		NewDims(63.0f, 100.0f);
		state = states::run;
		lifes = 80;
		speed = 1.0f;
		strenght = 8;
		attack_chance = 6;
		max_frames = 10;
		frame_delay = 7;
		break;

	case zombie3:
		NewDims(102.0f, 120.0f);
		state = states::run;
		lifes = 150;
		speed = 0.5f;
		strenght = 15;
		attack_chance = 8;
		max_frames = 3;
		frame_delay = 22;
		break;

	case zombie4:
		NewDims(120.0f, 120.0f);
		state = states::run;
		lifes = 180;
		speed = 0.4f;
		strenght = 18;
		attack_chance = 9;
		max_frames = 36;
		frame_delay = 2;
		break;

	case soul:
		NewDims(65.0f, 100.0f);
		state = states::stand;
		lifes = 20;
		speed = 0;
		max_frames = 120;
		frame_delay = 0;
		break;
	}
}
int dll::BASE::GetFrame()
{
	--frame_delay;
	if (frame_delay <= 0)
	{
		switch (type)
		{
		case hero:
			switch (state)
			{
			case states::stand:
				frame_delay = 15;
				break;

			case states::punch:
				frame_delay = 3;
				break;

			case states::kick1:
				frame_delay = 1;
				break;

			case states::kick2:
				frame_delay = 10;
				break;
			}
			break;

		case zombie1:
			frame_delay = 8;
			break;

		case zombie2:
			frame_delay = 7;
			break;

		case zombie3:
			frame_delay = 22;
			break;

		case zombie4:
			frame_delay = 2;
			break;

		case soul:
			frame_delay = 0;
			break;
		}

		--frame;
		if (frame > max_frames)frame = 0;
	}

	return frame;
}
void dll::BASE::ChangeState(states _to_what)
{
	state = _to_what;
	frame = 0;

	if (type == hero)
	{
		switch (state)
		{
		case states::stand:
			max_frames = 5;
			break;

		case states::punch:
			max_frames = 22;
			break;

		case states::kick1:
			max_frames = 47;
			break;

		case states::kick2:
			max_frames = 7;
			break;
		}
	}
}
states dll::BASE::GetState() const
{
	return state;
}

///////////////////////////////////