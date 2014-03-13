#ifndef MACHINE_H__
#define MACHINE_H__

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	std::string& Name() const;
	int	Id() const;
private:
	std::string m_sName;
	int			m_iId;
};

#endif // MACHINE_H__
