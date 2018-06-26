topic "IdCtrls";
[2 $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9;2 $$1,0#37138531426314131252341829483380:class]
[l288;2 $$2,2#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[H6;0 $$4,0#05600065144404261032431302351956:begin]
[i448;a25;kKO9;2 $$5,0#37138531426314131252341829483370:item]
[l288;a4;*@5;1 $$6,6#70004532496200323422659154056402:requirement]
[l288;i1121;b17;O9;~~~.1408;2 $$7,0#10431211400427159095818037425705:param]
[i448;b42;O9;2 $$8,8#61672508125594000341940100500538:tparam]
[b42;2 $$9,9#13035079074754324216151401829390:normal]
[{_} 
[ {{10000@(113.42.0) [s0;%% [*@7;4 IdCtrls]]}}&]
[s3; &]
[s1;:IdCtrls`:`:class: [@(0.0.255)3 class][3 _][*3 IdCtrls]&]
[s2;%% IdCtrls utility class is useful in situation when there is 
some relation between widgets and text identifiers. IdCtrls is 
basically a simple mapping between identifiers and widgets.&]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s3; &]
[s5;:IdCtrls`:`:Reset`(`): [@(0.0.255) void]_[* Reset]()&]
[s2;%% Removes all entries from IdCtrls.&]
[s3; &]
[s4; &]
[s5;:IdCtrls`:`:Add`(Id`,Ctrl`&`): [@(0.0.255) void]_[* Add]([_^Id^ Id]_[*@3 id], 
[_^Ctrl^ Ctrl][@(0.0.255) `&]_[*@3 ctrl])&]
[s5;:IdCtrls`:`:operator`(`)`(Id`,Ctrl`&`): [_^IdCtrls^ IdCtrls][@(0.0.255) `&]_[* operator
()]([_^Id^ Id]_[*@3 id], [_^Ctrl^ Ctrl][@(0.0.255) `&]_[*@3 ctrl])&]
[s2;%% Adds a new entry of widget reference and identifier.&]
[s3;%% &]
[s4;%% &]
[s5;:IdCtrls`:`:GetCount`(`)const: [@(0.0.255) int]_[* GetCount]()_[@(0.0.255) const]&]
[s2;%% Returns a number of entries.&]
[s3;%% &]
[s4;%% &]
[s5;:IdCtrls`:`:operator`[`]`(int`): [_^Ctrl^ Ctrl][@(0.0.255) `&]_[* operator`[`]]([@(0.0.255) i
nt]_[*@3 i])&]
[s5;:IdCtrls`:`:operator`[`]`(int`)const: [@(0.0.255) const]_[_^Ctrl^ Ctrl][@(0.0.255) `&]_
[* operator`[`]]([@(0.0.255) int]_[*@3 i])_[@(0.0.255) const]&]
[s2;%% Returns the widget of entry [%-*@3 i]. .&]
[s3;%% &]
[s4; &]
[s5;:IdCtrls`:`:GetKey`(int`)const: [_^Id^ Id]_[* GetKey]([@(0.0.255) int]_[*@3 i])_[@(0.0.255) c
onst]&]
[s5;:IdCtrls`:`:operator`(`)`(int`)const: [_^Id^ Id]_[* operator()]([@(0.0.255) int]_[*@3 i])
_[@(0.0.255) const]&]
[s2;%% Returns the identifier of entry [%-*@3 i].&]
[s3;%% &]
[s4;%% &]
[s5;:IdCtrls`:`:Get`(`)const: [_^ValueMap^ ValueMap]_[* Get]()_[@(0.0.255) const]&]
[s2;%% Creates a map, where keys are identifiers of entries and values 
are obtained from respective widgets using GetData method.&]
[s3;%% &]
[s4;%% &]
[s5;:IdCtrls`:`:Set`(const ValueMap`&`): [@(0.0.255) void]_[* Set]([@(0.0.255) const]_[_^ValueMap^ V
alueMap][@(0.0.255) `&]_[*@3 m])&]
[s2;%% Sets value of widgets using SetData to values in map, using 
keys of map to identify the target widgets.&]
[s0;%% ]]