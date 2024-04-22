#ifndef HELPERS_H
#define HELPERS_H

#include <QtGlobal>

// NOLINTNEXTLINE
namespace
{
// ##### Credits #####
#define Project_Credits				QStringLiteral("chaoskagami,Araraura,hax4dazy,EpicSpieler,donlon")
#define Project_Author				QStringLiteral("Cofeiini")

// ##### Project link #####
#define GitHub_Url					QStringLiteral("https://github.com/Cofeiini/UndertaleSaveEditor")

// ##### Character Names #####
// Bosses
#define Str_Flowey					QStringLiteral("Flowey")
#define Str_Toriel					QStringLiteral("Toriel")
#define Str_sans					QStringLiteral("sans")
#define Str_Papyrus					QStringLiteral("Papyrus")
#define Str_Undyne					QStringLiteral("Undyne")
#define Str_Alphys					QStringLiteral("Alphys")
#define Str_Mettaton				QStringLiteral("Mettaton")
#define Str_Mettaton_EX				QStringLiteral("Mettaton EX")
#define Str_Asgore					QStringLiteral("Asgore")
#define Str_Asriel					QStringLiteral("Asriel")
// Special
#define Str_Napstablook				QStringLiteral("Napstablook")
#define Str_NAPSTABLOOK22			QStringLiteral("NAPSTABLOOK22")
#define Str_Snowman					QStringLiteral("Snowman")
#define Str_Glyde					QStringLiteral("Glyde")
#define Str_Grillby					QStringLiteral("Grillby")
#define Str_Monster_Kid				QStringLiteral("Monster Kid")
#define Str_Annoying_Dog			QStringLiteral("The Annoying Dog")
#define Str_Temmie					QStringLiteral("Temmie")
// NOTE: Might be unused
#define Str_River_Person			QStringLiteral("River Person")
#define Str_Onionsan				QStringLiteral("Onionsan")
#define Str_Gerson					QStringLiteral("Gerson")
#define Str_So_Sorry				QStringLiteral("So Sorry")
#define Str_Muffet					QStringLiteral("Muffet")
#define Str_Burger_Pants			QStringLiteral("Burger Pants")
// NOTE: Might be unused
#define Str_Bratty					QStringLiteral("Bratty")
#define Str_Bratty_and_Catty		QStringLiteral("Bratty and Catty")
#define Str_Catty					QStringLiteral("Catty")
// Regular
#define Str_Froggit					QStringLiteral("Froggit")
#define Str_Whimsun					QStringLiteral("Whimsun")
#define Str_Moldsmal				QStringLiteral("Moldsmal")
#define Str_Loox					QStringLiteral("Loox")
#define Str_Vegetoid				QStringLiteral("Vegetoid")
#define Str_Migosp					QStringLiteral("Migosp")
#define Str_Snowdrake				QStringLiteral("Snowdrake")
#define Str_Ice_Cap					QStringLiteral("Ice Cap")
#define Str_Gyftrot					QStringLiteral("Gyftrot")
#define Str_Doggo					QStringLiteral("Doggo")
#define Str_Dogamy_and_Dogaressa	QStringLiteral("Dogamy and Dogaressa")
#define Str_Lesser_Dog				QStringLiteral("Lesser Dog")
#define Str_Greater_Dog				QStringLiteral("Greater Dog")
#define Str_Moldbygg				QStringLiteral("Moldbygg")
#define Str_Woshua					QStringLiteral("Woshua")
#define Str_Aaron_and_Woshua		QStringLiteral("Aaron and Woshua")
#define Str_Aaron					QStringLiteral("Aaron")
#define Str_Mad_Dummy				QStringLiteral("Mad Dummy")
#define Str_Shyren					QStringLiteral("Shyren")
#define Str_Vulkin					QStringLiteral("Vulkin")
#define Str_Tsunderplane			QStringLiteral("Tsunderplane")
#define Str_Pyrope					QStringLiteral("Pyrope")
#define Str_Royal_Guards			QStringLiteral("The Royal Guards")
#define Str_Final_Froggit			QStringLiteral("Final Froggit")
#define Str_Whimsalot				QStringLiteral("Whimsalot")
#define Str_Astigmatism				QStringLiteral("Astigmatism")
#define Str_Knight_Knight			QStringLiteral("Knight Knight")
#define Str_Madjick					QStringLiteral("Madjick")
// True Lab
#define Str_Reaper_Bird				QStringLiteral("Reaper Bird")
#define Str_Lemon_Bread				QStringLiteral("Lemon Bread")
#define Str_Memoryhead				QStringLiteral("Memoryhead")
#define Str_Amalgamates				QStringLiteral("Amalgamates")
#define Str_Endogeny				QStringLiteral("Endogeny")
// Genocide
#define Str_Undyne_the_Undying		QStringLiteral("Undyne The Undying")
#define Str_Glad_Dummy				QStringLiteral("Glad Dummy")

// ##### Items #####
#define Str_Undyne_Letter			QStringLiteral("Undyne's Letter")
#define Str_Undyne_Letter_EX		QStringLiteral("Undyne's Letter EX")

// ##### Locations #####
#define Str_Ruins					QStringLiteral("Ruins")
#define Str_Snowdin					QStringLiteral("Snowdin")
#define Str_Waterfall				QStringLiteral("Waterfall")
#define Str_Hotland					QStringLiteral("Hotland")
#define Str_MTT_Resort				QStringLiteral("MTT Resort")
#define Str_Core					QStringLiteral("Core")
#define Str_Castle					QStringLiteral("Castle")
#define Str_True_Lab				QStringLiteral("True Lab")

// ##### Functions #####
template<typename T>
constexpr void bitChange(T &var, const T value, const T bit)
{
	const T size = sizeof(var) * 8;
	for (T i = 0; i < size; ++i)
	{
		if ((1 << i) > bit)
		{
			break;
		}

		var = (var & ~bit) | ((value << i) & bit);
	}
}

constexpr auto bitCheck(const auto var, const quint64 bit) -> bool
{
	return (var & bit) > 0;
}

} // namespace

#endif // HELPERS_H
