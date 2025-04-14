#pragma once

#ifdef BASESERV_EXPORTS
#define BASE_API __declspec(dllexport)
#else
#define BASE_API __declspec(dllimport)
#endif

#include <random>

constexpr float scr_width{ 1000.0f };
constexpr float scr_height{ 800.0f };

constexpr float sky{ 50.0f };
constexpr float ground{ 750.0f };
constexpr float up_ground_boundary{ 295.0f };

enum class dirs { up = 0, down = 1, left = 2, right = 3, stop = 4 };
enum class states { stand = 0, run = 1, fight = 2, punch = 3, kick1 = 4, kick2 = 5 };

constexpr unsigned char no_type{ 0 };
constexpr unsigned char hero{ 1 };
constexpr unsigned char zombie1{ 2 };
constexpr unsigned char zombie2{ 4 };
constexpr unsigned char zombie3{ 8 };
constexpr unsigned char zombie4{ 16 };
constexpr unsigned char soul{ 32 };

struct BASE_API FPOINT
{
	float x{ 0 };
	float y{ 0 };
};

namespace dll
{
	class BASE_API RANDIT
	{
	private:
		std::random_device rd{};
		std::seed_seq* sq{ nullptr };
		std::mt19937* twister{ nullptr };

	public:
		RANDIT();
		~RANDIT();

		int operator()(int min, int max);
	};

	template<typename T> class BASE_API BAG
	{
	private:
		T* m_ptr{ nullptr };
		size_t m_size{ 0 };
		size_t m_pos{ 0 };

		bool in_valid_state = false;

		float Distance(FPOINT my_point, FPOINT target)
		{
			float a = powf(abs(my_point.x - target.x), 2);
			float b = powf(abs(my_point.y - target.y), 2);

			return sqrt(a + b);
		}

	public:
		BAG(size_t max_size) :m_size{ max_size }, m_ptr{ static_cast<T*>(calloc(max_size, sizeof(T))) } 
		{
			in_valid_state = true;
		};
		~BAG()
		{
			if (m_ptr)free(m_ptr);
		}

		void push_back(T& element)
		{
			if (m_pos < m_size)
			{
				*(m_ptr + m_pos) = element;
				++m_pos;
			}
			else
			{
				T* temp_m_ptr = reinterpret_cast<T*>(calloc(m_size + 1, sizeof(T)));
				for (size_t count = 0; count < m_size; ++count)*(temp_m_ptr + count) = *(m_ptr + count);
				*(temp_m_ptr + m_size) = element;
				++m_size;
				++m_pos;
				free(m_ptr);
				m_ptr = temp_m_ptr;
			}
		}
		void push_front(T& element)
		{
			*m_ptr = element;
		}

		size_t size() const
		{
			return m_size;
		}

		FPOINT sort(T& cont)
		{

		}

		T operator[](size_t index)
		{
			T ret{};
			if (index >= m_pos || ||index < 0 || !in_valid_state)return ret;

			return *(m_ptr + index);
		}

		void operator()(size_t index, T& element)
		{
			if (index < 0 || index >= m_size)return;
			*(m_ptr + index) = element;
		}
	};

	class BASE_API PROTON
	{
	protected:
		float width{ 0 };
		float height{ 0 };

	public:
		FPOINT start{};
		FPOINT end{};
		FPOINT center{};

		PROTON(float _x, float _y, float _width, float _height);
		PROTON();
		virtual ~PROTON() {};

		void SetEdges();
		void NewDims(float _width, float _height);
		void SetWidth(float _width);
		void SetHeight(float _height);

		float GetWidth() const;
		float GetHeight() const;
	};

	class BASE_API BASE :public PROTON
	{
	protected:
		
		float move_sx = 0;
		float move_sy = 0;
		float move_ex = 0;
		float move_ey = 0;
		float slope = 0;
		float intercept = 0;

		int strenght{ 0 };
		int attack_chance{ 0 };

		int frame{ 0 };
		int max_frames{ 0 };
		int frame_delay{ 0 };

		void SetPath(float __to_x, float __to_y);

	public:

		unsigned char type = no_type;
		dirs dir = dirs::stop;
		states state = states::stand;

		int lifes{ 0 };

		BASE(unsigned char _what_type, float _put_x, float _put_y);
		virtual ~BASE() {};

		int GetFrame() const;
		int Attack();

		virtual void NextMove(BAG<FPOINT> _targets) = 0;
		virtual void Move(float _where_x, float _where_y) = 0;
		virtual void Release() = 0;


	};

}