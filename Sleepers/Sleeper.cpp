#include "Header.h"

Sleeper::Sleeper()
{
	man = (rand() % 2 == 0) ? TRUE : FALSE;
	down = (rand() % 2 == 0) ? TRUE : FALSE;
}

void	Sleeper::move(int MapWidth, int MapHeight, float fElapsedTime, int i)
{
	srand(time(0) + (unsigned int)i);
	int rnd = rand() % 4;

	if (rnd == 0)
		change_pos(0, 1, MapWidth, MapHeight, fElapsedTime / 2);
	else if (rnd == 1)
		change_pos(0, -1, MapWidth, MapHeight, fElapsedTime / 2);
	else if (rnd == 2)
		change_pos(1, 0, MapWidth, MapHeight, fElapsedTime / 2);
	else if (rnd == 3)
		change_pos(-1, 0, MapWidth, MapHeight, fElapsedTime / 2);
}

bool	Sleeper::isDown()
{
	return down;
}

bool	Sleeper::isMale()
{
	return man;
}

void	Sleeper::changeDown()
{
	down = (rand() % 2 == 0) ? TRUE : FALSE;
}

TSleeper::TSleeper()
{
	head = new Node();
	head->next = NULL;
}

TSleeper::~TSleeper()
{
	Node* tmp = head->next;
	while (tmp != NULL)
	{
		delete head;
		head = tmp;
		tmp = tmp->next;
	}
	delete head;
}

bool	TSleeper::isEmpty()
{
	return head->next == NULL;
}

void	TSleeper::moveAll(int MapWidth, int MapHeight, float fElapsedTime)
{
	Node* curr = head->next;
	int i = 1;

	while (curr != NULL)
	{
		curr->curr.changeDown();
		curr->curr.move(MapWidth, MapHeight, fElapsedTime, i++);
		curr = curr->next;
	}
}

void	TSleeper::del_after(Node* node)
{
	Node* tmp;

	if (node->next != NULL && node != NULL)
	{
		tmp = node->next;
		node->next = node->next->next;
		delete tmp;
	}
}

void	TSleeper::kill(float x, float y)
{
	Node* curr = head;

	while (curr != NULL && curr->next != NULL)
	{
		if (abs(curr->next->curr.getX() - x) < 1
			&& abs(curr->next->curr.getY() - y) < 1
			&& !curr->next->curr.isDown())
			del_after(curr);
		curr = curr->next;
	}
}

void	TSleeper::displayAll(wchar_t* screen, int ScreenWidth)
{
	Node*	tmp = head->next;
	int		i = 1;

	srand(time(0));
	while (tmp != NULL)
	{
		if (!tmp->curr.isDown())
			screen[((int)tmp->curr.getX() + 1) * ScreenWidth + (int)tmp->curr.getY()] = 'S';
		tmp = tmp->next;

	}
}

void	TSleeper::add_end(Sleeper sleeper)
{
	Node* n;
	Node* curr;

	n = new Node();
	curr = head;
	while (curr->next != NULL)
		curr = curr->next;
	n->curr = sleeper;
	n->next = NULL;
	curr->next = n;
}

Node* TSleeper::getHead()
{
	return head;
}

void	TSleeper::add_end(TSleeper sleepers)
{
	Node* curr;
	Node* tmp;

	curr = head;
	while (curr->next != NULL)
		curr = curr->next;
	tmp = sleepers.getHead();
	curr->next = tmp->next;
	tmp->next = NULL;
}

void	TSleeper::add_start(Sleeper sleeper)
{
	Node* n;
	Node* tmp;

	n = new Node();
	tmp = head->next;
	head->next = n;
	n->curr = sleeper;
	n->next = tmp;
}

void	TSleeper::eat(Carrot*& carr, int nCarrots)
{
	Node* curr = head->next;

	while (curr != NULL)
	{
		for (int i = 0; i < nCarrots; i++)
			if (abs(curr->curr.getX() - carr[i].getX()) < 1
				&& abs(curr->curr.getY() - carr[i].getY()) < 1)
				carr[i].set_pos(-1, -1);
		curr = curr->next;
	}
}

void	TSleeper::newSleeper()
{
	Node*	l1 = head->next;
	Node*	l2 = l1;
	Sleeper	tmp;

	while (l1 != NULL)
	{
		l2 = l1->next;
		while (l2 != NULL)
		{
			if (fabs(l1->curr.getX() - l2->curr.getX()) < 1
				&& fabs(l1->curr.getY() - l2->curr.getY()) < 1
				&& l1 != l2)
			{
				tmp.set_pos(l1->curr.getX(), l1->curr.getY());
				add_start(tmp);
			}
			l2 = l2->next;
		}
		l1 = l1->next;
	}
}

int		TSleeper::count()
{
	int i = 0;
	Node* curr = head->next;

	while (curr != NULL)
	{
		i++;
		curr = curr->next;
	}
	return i;
}
