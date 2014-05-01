#ifndef CASE_HPP
# define CASE_HPP

enum Case_type
	{
	Outline = 0,
	Block = 1,
	Bot = 2,
	Character = 3
};

class Case
{
public:
	Case(const int&, const int&, const Case_type&);
	~Case();
	int				getPosx();
	int				getPosy();
	Case_type		getTypeCase();

private:
	int			pos_x;
	int			pos_y;
	Case_type	_type;
};

#endif /* !CASE_HPP */