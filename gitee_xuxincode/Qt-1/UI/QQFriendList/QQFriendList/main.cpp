#include "FriendTree/FriendTree.h"
#include <QtWidgets/QApplication>
#include <algorithm>
#include <QTime>

using namespace qqfriendlist;

namespace
{
	// Ⱥ������
	std::vector < std::string > groups{ "�ҵļ���", "�ҵ�����", "����У��", "CSU", "����ѧԺ" };
	// ��������
	std::vector < std::string > familys{ "�ϰ�", "����", "���", "�ù�", "С��" };
	// ��������
	std::vector < std::string > friends{ "ΰ��", "����", "����", "�˰�", "С��" };
	// ����ͬѧ
	std::vector < std::string > highSchool{ "����", "���", "�Ŷ�", "��", "С��ת" };
	// CSU
	std::vector < std::string > csu{ "����ʦ", "����ʦ", "����ʦ", "����ʦ", "֣��ʦ" };
	// ����ѧԺ
	std::vector < std::string > csru{ "��ί", "ʤ��", "С�ɷ�", "���", "������" };

	// ��Ϣ�б�
	std::vector<std::vector < std::string >> contactBasicInfo{ familys , friends, highSchool, csu, csru };
}

// ���ɲ�������
auto createFriendDatas = [&]()
{
	static int qqNumber = 396396396; // ��ʼqq�� 
	std::vector<Group> groupList{};
	for (int i = 0; i < groups.size(); i++)
	{
		// ����5������
		Group group{};
		group.groupName = QString::fromLocal8Bit(groups[i].c_str());

		for (auto j = 0; j < contactBasicInfo[i].size(); j++)
		{
			Contact contact{};
			contact.name = contact.nickName = QString::fromLocal8Bit(contactBasicInfo[i][j].c_str());
			contact.id = QString::number(qqNumber++);
			contact.sex = ((j+1) % 2 == 0); // �����Ա�
			contact.isVip = (j % 2 == 0);
			contact.onlineState = OnlineState(j);
			group.contactList.emplace_back(std::move(contact));
		}

		groupList.emplace_back(std::move(group));
	}

	return groupList;
};


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FriendTree w;
	// ��������
	w.setValues(createFriendDatas());
	w.setMinimumWidth(276);
    w.setMaximumWidth(600);

	w.resize(276, 500);
	w.show();
	return a.exec();
}
