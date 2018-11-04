#ifndef TOOLS_H
#define TOOLS_H

#include "mainwindow.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QSpinBox>

class CustomLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	CustomLineEdit(int id, MainWindow *mainWindow, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateSave(QString text);
	void updateData();
private:
	int id;
	MainWindow *mw;
};

class CustomSpinBox : public QSpinBox
{
	Q_OBJECT
public:
	CustomSpinBox(int id, MainWindow *mainWindow, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateSave(QString text);
	void updateData();
private:
	int id;
	MainWindow *mw;
};

class CustomComboBox : public QComboBox
{
	Q_OBJECT
public:
	CustomComboBox(int id, MainWindow *mainWindow, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateSave(int i);
	void updateData();
private:
	int id;
	QList<double> values;
	QMap<double, int> indexes;
	MainWindow *mw;
};

class CustomCheckBox : public QCheckBox
{
	Q_OBJECT
public:
	CustomCheckBox(int id, MainWindow *mainWindow, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateSave(int i);
	void updateData();
private:
	int id;
	int values[3] = {0, 1, 1};
	QMap<int, Qt::CheckState> states{{0, Qt::Unchecked}, {1, Qt::Checked}};
	MainWindow *mw;
};

class CustomRadioButton : public QRadioButton
{
	Q_OBJECT
public:
	CustomRadioButton(int id, QString text, MainWindow *mainWindow, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateSave(bool checked);
	void updateData();
private:
	int id;
	MainWindow *mw;
};

class ItemComboBox : public QComboBox
{
	Q_OBJECT
public:
	ItemComboBox(int id, MainWindow *mainWindow, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateSave(int i);
	void updateData();
private:
	int id;
	MainWindow *mw;
};

class PhoneComboBox : public QComboBox
{
	Q_OBJECT
public:
	PhoneComboBox(int id, MainWindow *mainWindow, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateSave(int i);
	void updateData();
private:
	int id;
	int values[10] = {0, 201, 202, 203, 204, 205, 206, 210, 220, 221};
	QMap<int, int> indexes{{201, 1}, {202, 2}, {203, 3}, {204, 4}, {205, 5}, {206, 6}, {210, 7}, {220, 8}, {221, 9}};
	MainWindow *mw;
};

class WeaponComboBox : public QComboBox
{
	Q_OBJECT
public:
	WeaponComboBox(int id, MainWindow *mainWindow, CustomSpinBox *weaponAT, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateSave(int i);
	void updateData();
private:
	int id;
	int values[9] = {3, 13, 14, 25, 45, 47, 49, 51, 52};
	int atValues[9] = {0, 3, 5, 7, 2, 10, 12, 15, 99};
	QMap<int, int> indexes{{3, 0}, {13, 1}, {14, 2}, {25, 3}, {45, 4}, {47, 5}, {49, 6}, {51, 7}, {52, 8}};
	MainWindow *mw;
	CustomSpinBox *wat;
};

class ArmorComboBox : public QComboBox
{
	Q_OBJECT
public:
	ArmorComboBox(int id, MainWindow *mainWindow, CustomSpinBox *armorDF, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateSave(int i);
	void updateData();
private:
	int id;
	int values[10] = {4, 12, 15, 24, 44, 46, 48, 50, 53, 64};
	int dfValues[10] = {0, 3, 7, 10, 5, 11, 12, 15, 99, 20};
	QMap<int, int> indexes{{4, 0}, {12, 1}, {15, 2}, {24, 3}, {44, 4}, {46, 5}, {48, 6}, {50, 7}, {53, 8}, {64, 9}};
	MainWindow *mw;
	CustomSpinBox *adf;
};

class RoomComboBox : public QComboBox
{
	Q_OBJECT
public:
	RoomComboBox(int id, MainWindow *mainWindow, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateSave(int i);
	void updateData();
private:
	int id;
	int values[335] = {6, 12, 18, 31, 46, 56, 61, 68, 83, 86, 94, 110, 114, 116, 128, 134, 139, 145, 155, 164, 176, 183, 196, 210, 216, 219, 231, 232, 235, 236, 246, 251, 0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 47, 48, 49, 50, 51, 52, 53, 54, 55, 57, 58, 59, 60, 62, 63, 64, 65, 66, 67, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 84, 85, 87, 88, 89, 90, 91, 92, 93, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 111, 112, 113, 115, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 129, 130, 131, 132, 133, 135, 136, 137, 138, 140, 141, 142, 143, 144, 146, 147, 148, 149, 150, 151, 152, 153, 154, 156, 157, 158, 159, 160, 161, 162, 163, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 177, 178, 179, 180, 181, 182, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 211, 212, 213, 214, 215, 217, 218, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 233, 234, 237, 238, 239, 240, 241, 242, 243, 244, 245, 247, 248, 249, 250, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334};
	QMap<int, int> indexes{{6, 0}, {12, 1}, {18, 2}, {31, 3}, {46, 4}, {56, 5}, {61, 6}, {68, 7}, {83, 8}, {86, 9}, {94, 10}, {110, 11}, {114, 12}, {116, 13}, {128, 14}, {134, 15}, {139, 16}, {145, 17}, {155, 18}, {164, 19}, {176, 20}, {183, 21}, {196, 22}, {210, 23}, {216, 24}, {219, 25}, {231, 26}, {232, 27}, {235, 28}, {236, 29}, {246, 30}, {251, 31}, {0, 32}, {1, 33}, {2, 34}, {3, 35}, {4, 36}, {5, 37}, {7, 38}, {8, 39}, {9, 40}, {10, 41}, {11, 42}, {13, 43}, {14, 44}, {15, 45}, {16, 46}, {17, 47}, {19, 48}, {20, 49}, {21, 50}, {22, 51}, {23, 52}, {24, 53}, {25, 54}, {26, 55}, {27, 56}, {28, 57}, {29, 58}, {30, 59}, {32, 60}, {33, 61}, {34, 62}, {35, 63}, {36, 64}, {37, 65}, {38, 66}, {39, 67}, {40, 68}, {41, 69}, {42, 70}, {43, 71}, {44, 72}, {45, 73}, {47, 74}, {48, 75}, {49, 76}, {50, 77}, {51, 78}, {52, 79}, {53, 80}, {54, 81}, {55, 82}, {57, 83}, {58, 84}, {59, 85}, {60, 86}, {62, 87}, {63, 88}, {64, 89}, {65, 90}, {66, 91}, {67, 92}, {69, 93}, {70, 94}, {71, 95}, {72, 96}, {73, 97}, {74, 98}, {75, 99}, {76, 100}, {77, 101}, {78, 102}, {79, 103}, {80, 104}, {81, 105}, {82, 106}, {84, 107}, {85, 108}, {87, 109}, {88, 110}, {89, 111}, {90, 112}, {91, 113}, {92, 114}, {93, 115}, {95, 116}, {96, 117}, {97, 118}, {98, 119}, {99, 120}, {100, 121}, {101, 122}, {102, 123}, {103, 124}, {104, 125}, {105, 126}, {106, 127}, {107, 128}, {108, 129}, {109, 130}, {111, 131}, {112, 132}, {113, 133}, {115, 134}, {117, 135}, {118, 136}, {119, 137}, {120, 138}, {121, 139}, {122, 140}, {123, 141}, {124, 142}, {125, 143}, {126, 144}, {127, 145}, {129, 146}, {130, 147}, {131, 148}, {132, 149}, {133, 150}, {135, 151}, {136, 152}, {137, 153}, {138, 154}, {140, 155}, {141, 156}, {142, 157}, {143, 158}, {144, 159}, {146, 160}, {147, 161}, {148, 162}, {149, 163}, {150, 164}, {151, 165}, {152, 166}, {153, 167}, {154, 168}, {156, 169}, {157, 170}, {158, 171}, {159, 172}, {160, 173}, {161, 174}, {162, 175}, {163, 176}, {165, 177}, {166, 178}, {167, 179}, {168, 180}, {169, 181}, {170, 182}, {171, 183}, {172, 184}, {173, 185}, {174, 186}, {175, 187}, {177, 188}, {178, 189}, {179, 190}, {180, 191}, {181, 192}, {182, 193}, {184, 194}, {185, 195}, {186, 196}, {187, 197}, {188, 198}, {189, 199}, {190, 200}, {191, 201}, {192, 202}, {193, 203}, {194, 204}, {195, 205}, {197, 206}, {198, 207}, {199, 208}, {200, 209}, {201, 210}, {202, 211}, {203, 212}, {204, 213}, {205, 214}, {206, 215}, {207, 216}, {208, 217}, {209, 218}, {211, 219}, {212, 220}, {213, 221}, {214, 222}, {215, 223}, {217, 224}, {218, 225}, {220, 226}, {221, 227}, {222, 228}, {223, 229}, {224, 230}, {225, 231}, {226, 232}, {227, 233}, {228, 234}, {229, 235}, {230, 236}, {233, 237}, {234, 238}, {237, 239}, {238, 240}, {239, 241}, {240, 242}, {241, 243}, {242, 244}, {243, 245}, {244, 246}, {245, 247}, {247, 248}, {248, 249}, {249, 250}, {250, 251}, {252, 252}, {253, 253}, {254, 254}, {255, 255}, {256, 256}, {257, 257}, {258, 258}, {259, 259}, {260, 260}, {261, 261}, {262, 262}, {263, 263}, {264, 264}, {265, 265}, {266, 266}, {267, 267}, {268, 268}, {269, 269}, {270, 270}, {271, 271}, {272, 272}, {273, 273}, {274, 274}, {275, 275}, {276, 276}, {277, 277}, {278, 278}, {279, 279}, {280, 280}, {281, 281}, {282, 282}, {283, 283}, {284, 284}, {285, 285}, {286, 286}, {287, 287}, {288, 288}, {289, 289}, {290, 290}, {291, 291}, {292, 292}, {293, 293}, {294, 294}, {295, 295}, {296, 296}, {297, 297}, {298, 298}, {299, 299}, {300, 300}, {301, 301}, {302, 302}, {303, 303}, {304, 304}, {305, 305}, {306, 306}, {307, 307}, {308, 308}, {309, 309}, {310, 310}, {311, 311}, {312, 312}, {313, 313}, {314, 314}, {315, 315}, {316, 316}, {317, 317}, {318, 318}, {319, 319}, {320, 320}, {321, 321}, {322, 322}, {323, 323}, {324, 324}, {325, 325}, {326, 326}, {327, 327}, {328, 328}, {329, 329}, {330, 330}, {331, 331}, {332, 332}, {333, 333}, {334, 334}};
	MainWindow *mw;
};

class TimeEdit : public QWidget
{
	Q_OBJECT
public:
	TimeEdit(int id, MainWindow *mainWindow, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateSave(double d);
	void updateData();
private:
	int id;
	MainWindow *mw;
	QDoubleSpinBox *data;
	QLabel *label;
};

class PlotEdit : public QComboBox
{
	Q_OBJECT
public:
	PlotEdit(int id, MainWindow *mainWindow, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateSave(int i);
	void updateData();
private:
	int id;
	double values[120] = {0, 1, 2, 3, 4, 4.5, 5, 5.5, 6, 7, 7.5, 8, 8.5, 9, 9.2, 9.4, 9.6, 9.8, 10.3, 10.35, 10.4, 11, 12, 13, 14, 15, 16, 17, 18, 19, 19.1, 19.2, 19.3, 19.4, 19.9, 20, 21, 22, 23, 24, 25, 28, 30, 36, 37, 40, 41, 42, 43, 47, 49, 50, 51, 53, 54, 56, 57, 58, 60, 61, 63, 65, 67, 100, 101, 104, 106, 107, 108, 109, 110, 111, 112, 113, 115, 116, 117, 118, 119, 120, 121, 122, 126, 127, 130, 131, 132, 133, 133.5, 134, 135, 137, 139, 140, 143, 146, 160, 161, 162, 163, 164, 165, 167, 168, 176, 177, 179, 180, 181, 182, 183, 184, 185, 193, 199, 201, 206, 207, 208, 999};
	QMap<double, int> indexes{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {4.5, 5}, {5, 6}, {5.5, 7}, {6, 8}, {7, 9}, {7.5, 10}, {8, 11}, {8.5, 12}, {9, 13}, {9.2, 14}, {9.4, 15}, {9.6, 16}, {9.8, 17}, {10.3, 18}, {10.35, 19}, {10.4, 20}, {11, 21}, {12, 22}, {13, 23}, {14, 24}, {15, 25}, {16, 26}, {17, 27}, {18, 28}, {19, 29}, {19.1, 30}, {19.2, 31}, {19.3, 32}, {19.4, 33}, {19.9, 34}, {20, 35}, {21, 36}, {22, 37}, {23, 38}, {24, 39}, {25, 40}, {28, 41}, {30, 42}, {36, 43}, {37, 44}, {40, 45}, {41, 46}, {42, 47}, {43, 48}, {47, 49}, {49, 50}, {50, 51}, {51, 52}, {53, 53}, {54, 54}, {56, 55}, {57, 56}, {58, 57}, {60, 58}, {61, 59}, {63, 60}, {65, 61}, {67, 62}, {100, 63}, {101, 64}, {104, 65}, {106, 66}, {107, 67}, {108, 68}, {109, 69}, {110, 70}, {111, 71}, {112, 72}, {113, 73}, {115, 74}, {116, 75}, {117, 76}, {118, 77}, {119, 78}, {120, 79}, {121, 80}, {122, 81}, {126, 82}, {127, 83}, {130, 84}, {131, 85}, {132, 86}, {133, 87}, {133.5, 88}, {134, 89}, {135, 90}, {137, 91}, {139, 92}, {140, 93}, {143, 94}, {146, 95}, {160, 96}, {161, 97}, {162, 98}, {163, 99}, {164, 100}, {165, 101}, {167, 102}, {168, 103}, {176, 104}, {177, 105}, {179, 106}, {180, 107}, {181, 108}, {182, 109}, {183, 110}, {184, 111}, {185, 112}, {193, 113}, {199, 114}, {201, 115}, {206, 116}, {207, 117}, {208, 118}, {999, 119}};
	MainWindow *mw;
};

#endif // TOOLS_H
