#ifndef MENU_HPP

# define MENU_HPP

class Menu
{
	private:
		static bool	_enableMouse;

	private:
		Menu(void);
		~Menu(void);

	public:
		static bool getEnableMouse();
		static void setEnableMouse(bool n);
};


#endif