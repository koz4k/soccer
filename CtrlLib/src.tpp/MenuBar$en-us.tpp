topic "MenuBar";
[2 $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9;2 $$1,0#37138531426314131252341829483380:class]
[l288;2 $$2,0#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[H6;0 $$4,0#05600065144404261032431302351956:begin]
[i448;a25;kKO9;2 $$5,0#37138531426314131252341829483370:item]
[l288;a4;*@5;1 $$6,6#70004532496200323422659154056402:requirement]
[l288;i1121;b17;O9;~~~.1408;2 $$7,0#10431211400427159095818037425705:param]
[i448;b42;O9;2 $$8,8#61672508125594000341940100500538:tparam]
[b42;2 $$9,9#13035079074754324216151401829390:normal]
[{_}%EN-US 
[ {{10000@3 [s0; [*@(229)4 MenuBar]]}}&]
[s3;%- &]
[s1;:MenuBar`:`:class:%- [@(0.0.255)3 class][3 _][*3 MenuBar][3 _:_][@(0.0.255)3 public][3 _][*@3;3 B
arCtrl]&]
[s2; &]
[s2; 
@@image:831&643
����瀀�����������������Ƿ�����ެ؋�����������ꥅ���Ѫ��􃔃��둬���Ā���
ۊ⥅�����â��������������²���﮾�ޘ����������ۓ�������㿺�����͎�µ��������
�坁���������������ؙ𰲹�����ʜ�ⴌ��ר��Ē�ƛ���҅���ބ��Η��֚����������㣏
Ĝ����𨕬���������ֲۿ������������啺����ϵÑ����힣�����䞟���ôƽ
������ᘌ���̑��ʀ���ȸ�˅����������Ï��ۈ���Ů�ƆƐ�Ϥܷ��������ԯ�һ�����
�����탖���㋀㢍�ؙ������ƛ�����ሡ���Ӿ������ʟ��Ǣ���̶������ʒ�Ǡ�ǧ����
�������������遇���泹��������������ҌɃ�������������䅑��ԭ��������������
�ĸ������������������������������ڽ�ާ����櫴������ř�����ڢ�ߺʹ����
���Ŗ����ؒ���Ҏ���ݣǈ�Ͷ������ǜ�����ܑ�������ǫ�⊿����֩�����������Ɓ�
�������Å��Ȏֆ�����ؙ���ϝ�ߖ���Ҳ����剃��؀�ێ�И�����������������ુ����
��������ו��ж������쎑����ǉ��һ���廤�����ҳ��ňò��ؙ�����ښ�����͸�ӭ�
���θ������뇭������ݬ���ҝ��ߦؤ���Ö������ݻ������ܛ����������ŝ����ƫ����
���ߝ����Ҝ������������ӳ�����������������������������߹��ᖃ�������������
������ʍ����ࠕ�尒����ɮ�㏳����ǜӅɎ��������ń�������요���ӽ���ﭚі�����
�����ܻʤ����������ϡ�������ɒ�������ة���͡������ɸ�������쀀�ځ�������̈��
��ü���ރ�������������ϋ���������냉���ܟ΀ݾ�����ĥ��������˿����Çյ��������
��������Ғ����ԯ߬̀������ɧ��������Ά��������蜕�����я������������������ٳ�
�ږ��ۚ���ȋ��ԍ���������������ە�������ǧ�����Þ���
&]
[s0; &]
[s9; This class provides the menu hierarchy. It can be used either 
as Frame or as regular Ctrl (in that case it represents top`-level 
menu), or be pop`-up as local menu (PopUp or Execute).&]
[s3; &]
[s0;%- &]
[ {{10000F(128)G(128)@1 [s0; [* Public Method List]]}}&]
[s3;%- &]
[s5;:MenuBar`:`:GetStdHeight`(Font`):%- [@(0.0.255) static] [@(0.0.255) int]_[* GetStdHeigh
t]([_^Font^ Font]_[*@3 font]_`=_StdFont())&]
[s2; The height of top`-level menu using the [%-*@3 font].&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:CloseMenu`(`):%- [@(0.0.255) void]_[* CloseMenu]()&]
[s2; Forces closing any open sub`-menus.&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:Set`(Callback1`<Bar`&`>`):%- [@(0.0.255) void]_[* Set]([_^Callback1^ Callba
ck1][@(0.0.255) <]Bar[@(0.0.255) `&>]_[*@3 menu])&]
[s2; Sets the top`-level [%-*@3 menu]. Use for top`-level menu bars 
only.&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:Post`(Callback1`<Bar`&`>`):%- [@(0.0.255) void]_[* Post]([_^Callback1^ Call
back1][@(0.0.255) <]Bar[@(0.0.255) `&>]_[*@3 bar])&]
[s2; Deprecated `- do not use.&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:PopUp`(Ctrl`*`,Point`,Size`):%- [@(0.0.255) void]_[* PopUp]([_^Ctrl^ Ctrl]_
`*[*@3 owner], [_^Point^ Point]_[*@3 p], [_^Size^ Size]_[*@3 rsz]_`=_[_^Size^ Size]([@3 0], 
[@3 0]))&]
[s2; Pop`-ups the menu at [%-*@3 p ]in the [%-*@3 owner] view area. [%-*@3 sz] 
is the size of menu, if zero, needed size is computed. Menu can 
be defined by issuing individual Add methods before calling PopUp.&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:PopUp`(Point`):%- [@(0.0.255) void]_[* PopUp]([_^Point^ Point]_[*@3 p])&]
[s2; Same as PopUp(GetActiveWindow(), p).&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:PopUp`(`):%- [@(0.0.255) void]_[* PopUp]()&]
[s2; Same as previous method, with p set to the current mouse position.&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:Execute`(Ctrl`*`,Point`):%- [@(0.0.255) void]_[* Execute]([_^Ctrl^ Ctrl]_`*
[*@3 owner], [_^Point^ Point]_[*@3 p])&]
[s2; Pop`-ups the menu at [%-*@3 p ]in the [%-*@3 owner] view area and 
performs the modal loop for it.&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:Execute`(Point`):%- [@(0.0.255) void]_[* Execute]([_^Point^ Point]_[*@3 p])&]
[s2; Same as Execute(GetActiveWindow(), [%-*@3 p]).&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:Execute`(`):%- [@(0.0.255) void]_[* Execute]()&]
[s2; Same as previous method, with p set to the current mouse position.&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:Execute`(Ctrl`*`,Callback1`<Bar`&`>`,Point`):%- [@(0.0.255) static] 
[@(0.0.255) void]_[* Execute]([_^Ctrl^ Ctrl]_`*[*@3 owner], [_^Callback1^ Callback1][@(0.0.255) <
]Bar[@(0.0.255) `&>]_[*@3 proc], [_^Point^ Point]_[*@3 p])&]
[s2; Pop`-ups the menu based on [%-*@3 proc].&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:Execute`(Callback1`<Bar`&`>`,Point`):%- [@(0.0.255) static] 
[@(0.0.255) void]_[* Execute]([_^Callback1^ Callback1][@(0.0.255) <]Bar[@(0.0.255) `&>]_[*@3 p
roc], [_^Point^ Point]_[*@3 p])&]
[s2; Same as previous method, using GetActiveWindow() as owner.&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:Execute`(Callback1`<Bar`&`>`):%- [@(0.0.255) static] 
[@(0.0.255) void]_[* Execute]([_^Callback1^ Callback1][@(0.0.255) <]Bar[@(0.0.255) `&>]_[*@3 p
roc])&]
[s2; Same as previous method, using current mouse position.&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:IsEmpty`(`):%- [@(0.0.255) bool]_[* IsEmpty]()&]
[s2; Returns true if MenuBar has no items.&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:Clear`(`):%- [@(0.0.255) virtual] [@(0.0.255) void]_[* Clear]()&]
[s2; Removes all items from MenuBar.&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:LeftGap`(int`):%- [_^MenuBar^ MenuBar][@(0.0.255) `&]_[* LeftGap]([@(0.0.255) i
nt]_[*@3 cx])&]
[s2; Minimum size reserved on the left side of menu items for icons 
in pixels. Default value is 16. Returns `*this.&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:SetFont`(Font`):%- [_^MenuBar^ MenuBar][@(0.0.255) `&]_[* SetFont]([_^Font^ F
ont]_[*@3 f])&]
[s2; Sets the font to be used in MenuBar. Default is standard GUI 
font. Returns `*this.&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:GetFont`(`)const:%- [_^Font^ Font]_[* GetFont]()_[@(0.0.255) const]&]
[s2; Returns the font used in MenuBar.&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:MaxIconSize`(Size`):%- [_^MenuBar^ MenuBar][@(0.0.255) `&]_[* MaxIconSize](
[_^Size^ Size]_[*@3 sz])&]
[s2; Sets the maximum size of an iconn displaye inside a menu item 
to [%-*@3 sz].&]
[s3; &]
[s4;%- &]
[s5;:MenuBar`:`:GetMaxIconSize`(`)const:%- [_^Size^ Size]_[* GetMaxIconSize]()_[@(0.0.255) c
onst]&]
[s2; Returns the maximum icons size.&]
[s3;%- &]
[s0; ]]