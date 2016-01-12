#include "dataeditor.h"

InventoryEditor::InventoryEditor(QWidget *parent) : QComboBox(parent)
{
	QStringList allItems = (QStringList() << "" << "Monster Candy" << "Croquet Roll" << "Stick" << "Bandage" << "Rock Candy" << "Pumpkin Rings" << "Spider Donut" << "Stoic Onion" << "Ghost Fruit" << "Spider Cider" << "Butterscotch Pie" << "Faded Ribbon" << "Toy Knife" << "Tough Glove" << "Manly Bandanna" << "Snowman Piece" << "Nice Cream" << "Puppydough Ice cream" << "Bisicle" << "Unisicle" << "Cinnamon Bun" << "Temmie Flakes" << "Abandoned Quiche" << "Old Tutu" << "Ballet Shoes" << "Punch Card" << "Annoying Dog" << "Dog Salad" << "Dog Residue" << "Dog Residue" << "Dog Residue" << "Dog Residue" << "Dog Residue" << "Dog Residue" << "Astronaut Food" << "Instant Noodles" << "Crab Apple" << "Hot Dog...?" << "Hot Cat" << "Glamburger" << "Sea Tea" << "Starfait" << "Legendary Hero" << "Cloudy Glasses" << "Torn Notebook" << "Stained Apron" << "Burnt Pan" << "Cowboy Hat" << "Empty Gun" << "Heart Locket" << "Worn Dagger" << "Real Knife" << "The Locket" << "Bad Memory" << "Dream" << "Undyne's Letter" << "Undyne Letter EX" << "Potato Chips" << "Junk Food" << "Mystery Key" << "Face Steak" << "Hush Puppy" << "Snail Pie" << "temy armor");
	QStandardItemModel *inventoryModel = new QStandardItemModel();
	foreach (QString var, allItems)
	{
		QStandardItem *newItem = new QStandardItem(var);
		inventoryModel->appendRow(newItem);
	}
	setModel(inventoryModel);
}

void InventoryEditor::processIndex(int index)
{
	setCurrentIndex(index);
}

PhoneEditor::PhoneEditor(QWidget *parent) : QComboBox(parent)
{
	QStringList allCalls = (QStringList() << "" << "Say Hello" << "Puzzle Help" << "About Yourself" << "Call Her \"Mom\"" << "Flirt" << "Toriel's Phone" << "Papyrus's Phone" << "Dimensional Box A" << "Dimensional Box B");
	QStandardItemModel *phoneModel = new QStandardItemModel();
	foreach (QString var, allCalls)
	{
		QStandardItem *newItem = new QStandardItem(var);
		phoneModel->appendRow(newItem);
	}
	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(processIndex(int)));
	setModel(phoneModel);
}

void PhoneEditor::processIndex(int num)
{
	switch(num)
	{
	case 0:
		setCurrentIndex(0);
		break;
	case 7:
		num = 210;
		break;
	case 8:
		num = 220;
		break;
	case 9:
		num = 221;
		break;
	case 210:
		setCurrentIndex(7);
		break;
	case 220:
		setCurrentIndex(8);
		break;
	case 221:
		setCurrentIndex(9);
		break;
	default:
		if(num < 200)
		{
			setCurrentIndex(num);
			num += 200;
		}
		else
		{
			setCurrentIndex(num - 200);
		}
		break;
	}
	emit transmitData(num);
}
