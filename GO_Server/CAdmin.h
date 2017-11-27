#ifndef CADMIN_H
#define CADMIN_H

//GO Admin interface
class CAdmin
{
public:
	CAdmin();
	~CAdmin();

	void HandleAdminCommand(CPlayer* player, RakString command);
};

#endif //CADMIN_H