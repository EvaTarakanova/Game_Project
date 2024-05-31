
class Target
{
public:
	float max_hp;
	float current_hp;
	float defense;

	Target(float max_hp, float defense);
	inline bool is_dead() { return current_hp <= 0; } //�������� ����� inline ��������� ����������� �������� ������ ���� ������� ��������������� ����� �������

	//�������
	float take_damage(Character* owner, float damage);
	virtual void die(Character* owner);
};