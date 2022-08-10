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
Sir 87: ��A���ǡI";

    dial["saleStart"]="�ӤH: �K!�~���H�A�ڳo�̦��Ǧn�F��A���ݶ�?";
	dial["saleEq"] = "\
�ӤH:�˳Ưʳf��!\nSir 87:�O�@���٨S���n�a...";
    dial["saleFinish"]="\
Salesperson: Always open ~~~~~~\n\
Sir 87: ��A�n�Q";
    dial["saleCancel"]="\
�ӤH: �^����!\n\
Sir 87: ��, �ڬO�g�� (To-How)";
    dial["gayStart"]="\
�˴�: �o�̬O���E,���},\n\
�S�����ܥi�H��F�贫����^.<";
    dial["gayFinish1"]="�˴�: �o�˰���? <3 �������ܧA�i�H��ܽ�u�| (y/n)?";
    dial["gayFinish2"]="\
Sir 87: ��A���n�A�ֺu\n\
�˴�: ^.^ <3\n\
Sir 87:.........................";
    dial["gayCancel"]="�˴ˡG�o��ִN�n���F��?�Q���H�ɥi�H�ӳ�A�C�ѳ����A��<3";

    dial["jamesStart"]="\
�e�R�v: �A�n�A�ڥs��i���A�ڬO�e�R�v\n�ڷ|�̧A�����Źw���A�����ӳ�A�n��R��?";
    dial["jamesUnder"]="\
�i��: ... �ɹɹ�...�n�i����\n\
�ߴ��Y�D�B������ˡA�ڬݧA�٬O���O�h�F�a�A�n�e�Y�]���O�o�˪��C\n\
\n\
Sir 87: WTF...";
    dial["jamesAbout"]="\
�i��:��...�N�⼵�o��[�A�٬O�\���@±�ڡC\n\
�֦~�A�A�٤����j�ڡA��p�t�z�A�W�j�@�ǦA�h�a�C";
    dial["jamesOver"]="\
�i��: ���|�a?���D�A�N�O�s���ϥ@�D��?\n\
���|�����F�A�A���@�楲�i�F���A�W�a�Ĥl!";
    dial["jamesCancel"]=
"�i��:�K�O�٤���A�̶̪�...";
/******************************************************************************
                              MAP2
******************************************************************************/
    dial["map2Start"]="\
Sir 87: �W�a!";
    dial["map2Hint"]="\
--Hint: Press Arrow LEFT/RIGHT to move around--\n\
When you are on stairs(###), press Arrow UP/DOWN to get up/down.\n\
Find the Boss!";

	dial["meetSorryHint"] = "\
Sir 87:�x�H�A����?...(Press Enter to continue)";
	dial["meetSorryBegin"] = "\
Sir 87:�A...���D�N�O�j�]����?�S�Q��X���覡�o��s�o�ڡC";
	dial["meetSorry1"] = "\
�i�äH�h:��...�����A�ڤ��O�a�H�A�ڬO�@�ӵ��}�����Ѧʩm��!";
	dial["meetSorry2"] = "\
Sir 87:���Ѧʩm���i��b�̭��A�ݨӧA�N�O�]���F�A�ڪ��[���(�ǪZ��)";
	dial["meetSorry3"] = "\
�i�äH�h:�N�R�ڡA�ڬO���g�Q�Q���]�����H���@�ڡC";
	dial["meetSorry4"] = "\
�i�äH�h:I'm Sorry.";
	dial["meetSorry5"] = "\
Sir 87:�D�p���Ϊ��ܴN����ĵ���...\n�٦��D�p���S�XXX�O�`�ѧa?";
	dial["meetSorry6"] = "\
Mr.Sorry:�ڨ��O���ڪ��W�r�sSorry...";
	dial["meetSorry7"] = "\
Sir 87:���o�䪺�H�W�r���γo�����...�n���٦�����i����...";
	dial["meetSorry8"] = "\
Mr.Sorry:�A���Ӥ]���ݨ�@���W���ӸO�a?�����O�H�e���i�̰ڡC\n\
�ڭ쥻�O�M�w�n���]�����F�A�ڥi�O�ݨ���W���ӸO�ڴN�ȤF�A\n\
�i�O�S�L�C�����F���ѡB�����^�a�A�ҥH�u�n�ݦb�o�̤F�C";
	dial["meetSorry9"] = "\
Sir 87: �J��@�ӫU��...�n�աA���ڲ{�b�n�h���]���A�A�n�@�_�Ӷ�?";
	dial["meetSorry10"] = "\
Mr.Sorry:�A���U���n��?�L�O�]���C�C";
	dial["meetSorry11"] = "\
Sir 87:�i�O�ڤ]�Q�^�a�ڡA���ѥL�N�i�H�^�h�F�A�G�Ƥ����O�o�˼g����?";
	dial["meetSorry12"] = "\
Mr.Sorry:�n�a�A�ڴN�h�B�۫H�A�@���A�ڥ����n�A�����L�ڷ|�]��C";
	dial["meetSorry13"] = "\
Sir 87:�Ѥl�b�A�w�աC";
	dial["meetSorry14"] = "\
Mr.Sorry:�u�������ڡA���f�C...";
	dial["meetSorryEnd"] = "\
--Mr.Sorry�[�J����!--";

}
	

string UI_Dialogue::GetDialogue(const string& diaName)
{
    return dial[diaName];
}
