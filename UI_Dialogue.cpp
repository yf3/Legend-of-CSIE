#include "UI_Dialogue.h"

UI_Dialogue::UI_Dialogue()
{
/******************************************************************************
                              MAP1
******************************************************************************/
    dial["emptyStr"]="";
    dial["defaultHint"]="\
--Hint:Press ENTER when you are near an NPC to invoke interactions--\n\
--NPC info:--\n\
S: SalesPerson\n\
G: Pawn Shop\n\
J: Seems like someone who knows your future...";
	dial["map1Fight"] = "\
Sir 87: 艮，有怪！";

    dial["saleStart"]="商人: 嘿!年輕人，我這裡有些好東西，不看嗎?";
	dial["saleEq"] = "\
商人:裝備缺貨喔!\nSir 87:是作者還沒做好吧...";
    dial["saleFinish"]="\
Salesperson: Always open ~~~~~~\n\
Sir 87: 艮，好貴";
    dial["saleCancel"]="\
商人: 乞丐欸!\n\
Sir 87: 屁, 我是土豪 (To-How)";
    dial["gayStart"]="\
森森: 這裡是當舖,揪咪,\n\
沒錢的話可以賣東西換錢呦^.<";
    dial["gayFinish1"]="森森: 這樣夠嗎? <3 不夠的話你可以選擇賣ㄆㄍ (y/n)?";
    dial["gayFinish2"]="\
Sir 87: 艮，不要，快滾\n\
森森: ^.^ <3\n\
Sir 87:.........................";
    dial["gayCancel"]="森森：這麼快就要走了嗎?想來隨時可以來喔，每天都等你喔<3";

    dial["jamesStart"]="\
占卜師: 你好，我叫詹姆斯，我是占卜師\n我會依你的等級預測你的未來喔，要算命嗎?";
    dial["jamesUnder"]="\
姆斯: ... 嘖嘖嘖...好可憐哪\n\
晚景淒涼、結局潦倒，我看你還是先別去了吧，要送頭也不是這樣的。\n\
\n\
Sir 87: WTF...";
    dial["jamesAbout"]="\
姆斯:嗯...就算撐這麼久，還是功虧一簣啊。\n\
少年，你還不夠強啊，把小宇宙再增強一些再去吧。";
    dial["jamesOver"]="\
姆斯: 不會吧?難道你就是新的救世主嗎?\n\
不會有錯了，你的願望必可達成，上吧孩子!";
    dial["jamesCancel"]=
"姆斯:免費還不算，傻傻的...";
/******************************************************************************
                              MAP2
******************************************************************************/
    dial["map2Start"]="\
Sir 87: 上吧!";
    dial["map2Hint"]="\
--Hint: Press Arrow LEFT/RIGHT to move around--\n\
When you are on stairs(###), press Arrow UP/DOWN to get up/down.\n\
Find the Boss!";

	dial["meetSorryHint"] = "\
Sir 87:咦？你哪位?...(Press Enter to continue)";
	dial["meetSorryBegin"] = "\
Sir 87:你...難道就是大魔王嗎?沒想到出場方式這麼新穎啊。";
	dial["meetSorry1"] = "\
可疑人士:等...等等，我不是壞人，我是一個善良的死老百姓啊!";
	dial["meetSorry2"] = "\
Sir 87:死老百姓怎麼可能在裡面，看來你就是魔王了，我的觀察啦(掏武器)";
	dial["meetSorry3"] = "\
可疑人士:冷靜啊，我是曾經想討伐魔王的人之一啊。";
	dial["meetSorry4"] = "\
可疑人士:I'm Sorry.";
	dial["meetSorry5"] = "\
Sir 87:道歉有用的話就不用警察啦...\n還有道歉時露出XX是常識吧?";
	dial["meetSorry6"] = "\
Mr.Sorry:我其實是說我的名字叫Sorry...";
	dial["meetSorry7"] = "\
Sir 87:怎麼這邊的人名字都用這種爛梗...好像還有什麼姆斯的...";
	dial["meetSorry8"] = "\
Mr.Sorry:你應該也有看到一路上的墓碑吧?那都是以前的勇者啊。\n\
我原本是決定要跟魔王拼了，啊可是看到路上的墓碑我就怕了，\n\
可是又無顏見江東父老、不敢回家，所以只好待在這裡了。";
	dial["meetSorry9"] = "\
Sir 87: 遇到一個俗辣...好啦，那我現在要去打魔王，你要一起來嗎?";
	dial["meetSorry10"] = "\
Mr.Sorry:你腦袋不好喔?他是魔王耶。";
	dial["meetSorry11"] = "\
Sir 87:可是我也想回家啊，打敗他就可以回去了，故事不都是這樣寫的嗎?";
	dial["meetSorry12"] = "\
Mr.Sorry:好吧，我就姑且相信你一次，我先說好，打不過我會跑喔。";
	dial["meetSorry13"] = "\
Sir 87:老子在，安啦。";
	dial["meetSorry14"] = "\
Mr.Sorry:真的假的啊，有病耶...";
	dial["meetSorryEnd"] = "\
--Mr.Sorry加入隊伍!--";

}
	

string UI_Dialogue::GetDialogue(const string& diaName)
{
    return dial[diaName];
}
