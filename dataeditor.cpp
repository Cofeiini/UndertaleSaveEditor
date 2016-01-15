#include "dataeditor.h"

DataEditor::DataEditor(QWidget *parent, int index) : QComboBox(parent)
{
	if(index == 0)
	{
		InventoryEditor();
	}
	else
	{
		StatusEditor(index);
	}
}

void DataEditor::InventoryEditor()
{
	id = 0;
	QStringList allItems = (QStringList() << "" << "Monster Candy" << "Croquet Roll" << "Stick" << "Bandage" << "Rock Candy" << "Pumpkin Rings" << "Spider Donut" << "Stoic Onion" << "Ghost Fruit" << "Spider Cider" << "Butterscotch Pie" << "Faded Ribbon" << "Toy Knife" << "Tough Glove" << "Manly Bandanna" << "Snowman Piece" << "Nice Cream" << "Puppydough Ice cream" << "Bisicle" << "Unisicle" << "Cinnamon Bun" << "Temmie Flakes" << "Abandoned Quiche" << "Old Tutu" << "Ballet Shoes" << "Punch Card" << "Annoying Dog" << "Dog Salad" << "Dog Residue" << "Dog Residue" << "Dog Residue" << "Dog Residue" << "Dog Residue" << "Dog Residue" << "Astronaut Food" << "Instant Noodles" << "Crab Apple" << "Hot Dog...?" << "Hot Cat" << "Glamburger" << "Sea Tea" << "Starfait" << "Legendary Hero" << "Cloudy Glasses" << "Torn Notebook" << "Stained Apron" << "Burnt Pan" << "Cowboy Hat" << "Empty Gun" << "Heart Locket" << "Worn Dagger" << "Real Knife" << "The Locket" << "Bad Memory" << "Dream" << "Undyne's Letter" << "Undyne Letter EX" << "Potato Chips" << "Junk Food" << "Mystery Key" << "Face Steak" << "Hush Puppy" << "Snail Pie" << "temy armor");
	QStandardItemModel *inventoryModel = new QStandardItemModel();
	foreach (QString var, allItems)
	{
		QStandardItem *newItem = new QStandardItem(var);
		inventoryModel->appendRow(newItem);
	}
	setModel(inventoryModel);
}

void DataEditor::recieveValue(int num)
{
	switch(id)
	{
	case 98:
		switch(num)
		{
		case -3:
			num = 0;
			break;
		case -2:
			num = 1;
			break;
		case -1:
			num = 2;
			break;
		case 0:
			num = 3;
			break;
		case 1:
			num = 4;
			break;
		}
		break;
	case 231:
		num -= 202;
		break;
	case 548:
		QRegExp rx(QString::number(num) + ".*");
		num = rooms.indexOf(rx);
		break;
	}
	setCurrentIndex(num);
}

void DataEditor::trueIndexValue(int num)
{
	switch(id)
	{
	case 98:
		switch(num)
		{
		case 0:
			num = -3;
			break;
		case 1:
			num = -2;
			break;
		case 2:
			num = -1;
			break;
		case 3:
			num = 0;
			break;
		case 4:
			num = 1;
			break;
		}
		break;
	case 231:
		switch(num)
		{
		case 0:
			num = 202;
			break;
		case 1:
			num = 203;
			break;
		case 2:
			num = 204;
			break;
		case 3:
			num = 205;
			break;
		}
		break;
	case 548:
		QString dummy = rooms.value(num);
		num = dummy.section("#", 0, 0).toInt();
		break;
	}

	emit transmitData(num);
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
	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(recieveValue(int)));
	setModel(phoneModel);
}

void PhoneEditor::recieveValue(int num)
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

void DataEditor::StatusEditor(int index)
{
	id = index;
	QStringList statusList;
	switch(index)
	{
	case 45:
		statusList << "Flee" << "Kill" << "Talk" << "Bored";
		break;
	case 53:
		statusList << "Yellow names" << "White names" << "Pink names";
		break;
	case 76:
		statusList << "1st time visiting Home" << "Disobey" << "?2?" << "Fight" << "Kill" << "Spare";
		break;
	case 77:
		statusList << "" << "Butterscotch" << "Cinnamon";
		break;
	case 83:
		statusList << "Spare" << "Kill" << "Used Stick";
		break;
	case 84:
		statusList << "Spare" << "Kill" << "Used Stick";
		break;
	case 85:
		statusList << "Spare" << "Kill" << "Used Stick" << "Bored";
		break;
	case 86:
		statusList << "Spare" << "Kill" << "Maximum petting";
		break;
	case 87:
		statusList << "" << "Got a piece" << "Got another piece" << "???" << "The Snowman saw you eat the piece" << "Tried to talk after being spotted eating snow";
		break;
	case 88:
		statusList << "Spare" << "Laugh at joke" << "Kill";
		break;
	case 89:
		statusList << "Junior Jumble" << "Crosswords";
		break;
	case 93:
		statusList << "" << "Ate it" << "Left it";
		break;
	case 98:
		statusList << "Skip fight" << "Captured, 2nd time" << "Captured, 1st time" << "Spare" << "Kill";
		break;
	case 103:
		statusList << "" << "Stayed at the inn" << "Not enough GOLD";
		break;
	case 107:
		statusList << "Told the truth" << "Lied about clothes";
		break;
	case 112:
		statusList << "" << "Kill" << "Musical career";
		break;
	case 119:
		statusList << "" << "Outside the house" << "Inside the house" << "Unlock room" << "Date complete";
		break;
	case 120:
		statusList << "" << "Begin date" << "Date complete";
		break;
	case 121:
		statusList << "" << "Met without an umbrella" << "Went back to get an umbrella" << "Went back again to get rid of the umbrella";
		break;
	case 123:
		statusList << "" << "It's a horse stable." << "Do you want to go inside?" << "You jostle the door." << "It's locked.";
		break;
	case 124:
		statusList << "" << "Talk" << "?2?" << "Lie on the ground" << "?4?" << "?5?" << "?6?" << "?7?" << "?8?" << "Don't lie on the ground";
		break;
	case 125:
		statusList << "" << "Spooktunes" << "Spookwave" << "Ghouliday Music";
		break;
	case 127:
		statusList << "" << "\"That Emblem\"" << "\"Emblem's meaning\"" << "\"The Prophecy\"";
		break;
	case 129:
		statusList << "Walked away" << "Waited for Undyne to do something" << "Helped the kid";
		break;
//	case 134:
//		statusList << "" << "Cinnamon Pie" << "Butterscotch Pie";
//		break;
	case 231:
		statusList << "The Ruins" << "Snowdin" << "Waterfall" << "Hotlands";
		break;
	case 296:
		statusList << "" << "Special sale" << "Sell 1 more for special" << "Sell 2 more for special" << "Sell 3 more for special" << "Sell 4 more for special" << "Sell 5 more for special" << "Sell 6 more for special" << "Sell 7 more for special";
		break;
	case 298:
		statusList << "" << "Stayed at the hotel"  << "Stayed at the hotel, again";
		break;
	case 306:
		statusList << "" << "Walked past it"  << "It gets snapped";
		break;
	case 312:
		statusList << "Not encountered" << "Kill" << "Spare";
		break;
//	case 313:
//		statusList << "Not encountered" << "Spare" << "Kill";
//		break;
	case 381:
		statusList << "Spare" << "Kill" << "Spare, but no water";
		break;
	case 386:
		statusList << "Don't interact"  << "Interact -> Punch" << "Interact -> Don't punch";
		break;
	case 416:
		statusList << "Not available" << "Available" << "Button pressed";
		break;
	case 420:
		statusList << "" << "?1?" << "?2?" << "?3?" << "House is on fire";
		break;
	case 422:
		statusList << "" << "Fries" << "Burger";
		break;
	case 444:
		statusList << "" << "Begin date" << "Date complete";
		break;
	case 455:
		statusList << "" << "Can be exposed" << "Already exposed";
		break;
	case 465:
		statusList << "" << "Remebered the name" << "Forgot the name";
		break;
	case 466:
		statusList << "" << "Buy" << "Talk";
		break;
	case 490:
		statusList << "" << "Snowdin" << "Waterfall" << "Hotland";
		break;
//	case 492:
//		statusList << "Regular" << "Temmie";
//		break;
	case 524:
		statusList << "" << "?1?" << "?2?" << "?3?" << "?4?" << "?5?" << "?6?" << "?7?" << "?8?" << "?9?" << "?10?" << "?11?" << "Exited the True Lab";
		break;
	case 525:
		statusList << "" << "?1?" << "Regular Letter" << "Letter EX";
		break;
	case 527:
		statusList << "\"I'm Onionsan!\"" << "?1?" << "?2?" << "?3?" << "?4?" << "?5?" << "\"I got nothing else...\"" << "?7?";
		break;
	case 541:
		statusList << "" << "Talked with Asriel at Ruins" << "Completed the Dreamer Battle";
		break;
	case 548:
		{
		QFile file(":/strings/roomfile");
		QTextStream buff(&file);
		if(!file.open(QFile::ReadOnly | QFile::Text))
		{
			statusList << "0#room_start" << "1#room_introstory" << "2#room_introimage" << "3#room_intromenu" << "4#room_area1" << "5#room_area1_2" << "6#room_ruins1" << "7#room_ruins2" << "8#room_ruins3" << "9#room_ruins4" << "10#room_ruins5" << "11#room_ruins6" << "12#room_ruins7" << "13#room_ruins7A" << "14#room_ruins8" << "15#room_ruins9" << "16#room_ruins10" << "17#room_ruins11" << "18#room_ruins12A" << "19#room_ruins12" << "20#room_ruins12B" << "21#room_ruins13" << "22#room_ruins14" << "23#room_ruins15A" << "24#room_ruins15B" << "25#room_ruins15C" << "26#room_ruins15D" << "27#room_ruins15E" << "28#room_ruins16" << "29#room_ruins17" << "30#room_ruins18OLD" << "31#room_ruins19" << "32#room_torhouse1" << "33#room_torhouse2" << "34#room_torhouse3" << "35#room_torielroom" << "36#room_asrielroom" << "37#room_kitchen" << "38#room_basement1" << "39#room_basement2" << "40#room_basement3" << "41#room_basement4" << "42#room_basement5" << "43#room_ruinsexit" << "44#room_tundra1" << "45#room_tundra2" << "46#room_tundra3" << "47#room_tundra3A" << "48#room_tundra4" << "49#room_tundra5" << "50#room_tundra6" << "51#room_tundra6A" << "52#room_tundra7" << "53#room_tundra8" << "54#room_tundra8A" << "55#room_tundra9" << "56#room_tundra_spaghetti" << "57#room_tundra_snowpuzz" << "58#room_tundra_xoxosmall" << "59#room_tundra_xoxopuzz" << "60#room_tundra_randoblock" << "61#room_tundra_lesserdog" << "62#room_tundra_icehole" << "63#room_tundra_iceentrance" << "64#room_tundra_iceexit_new" << "65#room_tundra_iceexit" << "66#room_tundra_poffzone" << "67#room_tundra_dangerbridge" << "68#room_tundra_town" << "69#room_tundra_town2" << "70#room_tundra_dock" << "71#room_tundra_inn" << "72#room_tundra_inn_2f" << "73#room_tundra_grillby" << "74#room_tundra_library" << "75#room_tundra_garage" << "76#room_tundra_sanshouse" << "77#room_tundra_paproom" << "78#room_tundra_sansroom" << "79#room_tundra_sansroom_dark" << "80#room_tundra_sansbasement" << "81#room_fogroom" << "82#room_water1" << "83#room_water2" << "84#room_water3" << "85#room_water3A" << "86#room_water4" << "87#room_water_bridgepuzz1" << "88#room_water5" << "89#room_water5A" << "90#room_water6" << "91#room_water7" << "92#room_water8" << "93#room_water9" << "94#room_water_savepoint1" << "95#room_water11" << "96#room_water_nicecream" << "97#room_water12" << "98#room_water_shoe" << "99#room_water_bird" << "100#room_water_onionsan" << "101#room_water14" << "102#room_water_piano" << "103#room_water_dogroom" << "104#room_water_statue" << "105#room_water_prewaterfall" << "106#room_water_waterfall" << "107#room_water_waterfall2" << "108#room_water_waterfall3" << "109#room_water_waterfall4" << "110#room_water_preundyne" << "111#room_water_undynebridge" << "112#room_water_undynebridgeend" << "113#room_water_trashzone1" << "114#room_water_trashsavepoint" << "115#room_water_trashzone2" << "116#room_water_friendlyhub" << "117#room_water_undyneyard" << "118#room_water_undynehouse" << "119#room_water_blookyard" << "120#room_water_blookhouse" << "121#room_water_hapstablook" << "122#room_water_farm" << "123#room_water_prebird" << "124#room_water_shop" << "125#room_water_dock" << "126#room_water15" << "127#room_water16" << "128#room_water_temvillage" << "129#room_water17" << "130#room_water18" << "131#room_water19" << "132#room_water20" << "133#room_water21" << "134#room_water_undynefinal" << "135#room_water_undynefinal2" << "136#room_water_undynefinal3" << "137#room_fire1" << "138#room_fire2" << "139#room_fire_prelab" << "140#room_fire_dock" << "141#room_fire_lab1" << "142#room_fire_lab2" << "143#room_fire3" << "144#room_fire5" << "145#room_fire6" << "146#room_fire6A" << "147#room_fire_lasers1" << "148#room_fire7" << "149#room_fire8" << "150#room_fire_shootguy_2" << "151#room_fire9" << "152#room_fire_shootguy_1" << "153#room_fire_turn" << "154#room_fire_cookingshow" << "155#room_fire_savepoint1" << "156#room_fire_elevator_r1" << "157#room_fire_elevator_r2" << "158#room_fire_hotdog" << "159#room_fire_walkandbranch" << "160#room_fire_sorry" << "161#room_fire_apron" << "162#room_fire10" << "163#room_fire_rpuzzle" << "164#room_fire_mewmew2" << "165#room_fire_boysnightout" << "166#room_fire_newsreport" << "167#room_fire_coreview2" << "168#room_fire_elevator_l2" << "169#room_fire_elevator_l3" << "170#room_fire_spidershop" << "171#room_fire_walkandbranch2" << "172#room_fire_conveyorlaser" << "173#room_fire_shootguy_3" << "174#room_fire_preshootguy4" << "175#room_fire_shootguy_4" << "176#room_fire_savepoint2" << "177#room_fire_spider" << "178#room_fire_pacing" << "179#room_fire_operatest" << "180#room_fire_multitile" << "181#room_fire_hotelfront_1" << "182#room_fire_hotelfront_2" << "183#room_fire_hotellobby" << "184#room_fire_restaurant" << "185#room_fire_hoteldoors" << "186#room_fire_hotelbed" << "187#room_fire_elevator_r3" << "188#room_fire_precore" << "189#room_fire_core1" << "190#room_fire_core2" << "191#room_fire_core3" << "192#room_fire_core4" << "193#room_fire_core5" << "194#room_fire_core_freebattle" << "195#room_fire_core_laserfun" << "196#room_fire_core_branch" << "197#room_fire_core_bottomleft" << "198#room_fire_core_left" << "199#room_fire_core_topleft" << "200#room_fire_core_top" << "201#room_fire_core_topright" << "202#room_fire_core_right" << "203#room_fire_core_bottomright" << "204#room_fire_core_center" << "205#room_fire_shootguy_5" << "206#room_fire_core_treasureleft" << "207#room_fire_core_treasureright" << "208#room_fire_core_warrior" << "209#room_fire_core_bridge" << "210#room_fire_core_premett" << "211#room_fire_core_metttest" << "212#room_fire_core_final" << "213#room_fire_elevator" << "214#room_fire_elevator_l1" << "215#room_fire_finalelevator" << "216#room_castle_elevatorout" << "217#room_castle_precastle" << "218#room_castle_hook" << "219#room_castle_front" << "220#room_asghouse1" << "221#room_asghouse2" << "222#room_asghouse3" << "223#room_asgoreroom" << "224#room_asrielroom_final" << "225#room_kitchen_final" << "226#room_basement1_final" << "227#room_basement2_final" << "228#room_basement3_final" << "229#room_basement4_final" << "230#room_lastruins_corridor" << "231#room_sanscorridor" << "232#room_castle_finalshoehorn" << "233#room_castle_coffins1" << "234#room_castle_coffins2" << "235#room_castle_throneroom" << "236#room_castle_prebarrier" << "237#room_castle_barrier" << "238#room_castle_exit" << "239#room_undertale_end" << "240#room_castle_trueexit" << "241#room_outsideworld" << "242#room_fire_labelevator" << "243#room_truelab_elevatorinside" << "244#room_truelab_elevator" << "245#room_truelab_hall1" << "246#room_truelab_hub" << "247#room_truelab_hall2" << "248#room_truelab_operatingroom" << "249#room_truelab_redlever" << "250#room_truelab_prebed" << "251#room_truelab_bedroom" << "252#room_truelab_mirror" << "253#room_truelab_bluelever" << "254#room_truelab_hall3" << "255#room_truelab_shower" << "256#room_truelab_determination" << "257#room_truelab_tv" << "258#room_truelab_cooler" << "259#room_truelab_greenlever" << "260#room_truelab_fan" << "261#room_truelab_castle_elevator" << "262#room_truelab_prepower" << "263#room_truelab_power" << "264#room_gaster" << "265#room_icecave1" << "266#room_ice_dog" << "267#room2" << "268#room_water_fakehallway" << "269#room_mysteryman" << "270#room_soundtest" << "271#TESTROOM" << "272#room_water_redacted" << "273#room_water13" << "274#room_overworld" << "275#room_overworld3" << "276#bullettest" << "277#room_water16A" << "278#room_end_castroll" << "279#room_end_highway" << "280#room_end_beach" << "281#room_end_metta" << "282#room_end_school" << "283#room_end_mtebott" << "284#room_creditsdodger" << "285#room_end_myroom" << "286#room_end_theend" << "287#room_spritecheck" << "288#room_joyconfig" << "289#room_controltest" << "290#room_f_start" << "291#room_f_intro" << "292#room_f_menu" << "293#room_f_room" << "294#room_floweyx" << "295#room_f_phrase" << "296#room_fire4" << "297#room_fire10_old" << "298#room_fire10A_old" << "299#room_tundra_placeholder" << "300#room_ruins12B_old" << "301#room_tundra_rollsnow" << "302#room_water7_older" << "303#room_meetundyne_old" << "304#room_water_mushroom" << "305#room_monsteralign_test" << "306#room_battle" << "307#room_floweybattle" << "308#room_fastbattle" << "309#room_storybattle" << "310#room_gameover" << "311#room_shop1" << "312#room_shop2" << "313#room_shop3" << "314#room_shop4" << "315#room_shop5" << "316#room_riverman_transition" << "317#room_papdate" << "318#room_adate" << "319#room_flowey_endchoice" << "320#room_flowey_regret" << "321#room_empty" << "322#room_emptywhite" << "323#room_emptyblack" << "324#room_nothingness" << "325#room_undertale" << "326#room_of_dog" << "327#room_quizholder" << "328#room_friendtest" << "329#room_bringitinguys" << "330#room_asrielappears" << "331#room_goodbyeasriel" << "332#room_asrielmemory" << "333#room_asrieltest" << "334#room_afinaltest";
		}
		else
		{
			while(!buff.atEnd())
			{
				QString dummy = "";
				buff.readLineInto(&dummy);
				rooms << dummy;
				dummy = dummy.section("#", -1);
				statusList << dummy;
			}
		}
		}
		break;
	}
	QStandardItemModel *statusModel = new QStandardItemModel();
	foreach (QString var, statusList)
	{
		QStandardItem *newItem = new QStandardItem(var);
		statusModel->appendRow(newItem);
	}
	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(trueIndexValue(int)));
	setModel(statusModel);
}
