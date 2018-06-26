topic "Range";
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
[{_}%EN-US 
[ {{10000@(113.42.0) [s0; [*@7;4 Range]]}}&]
[s1;O_; &]
[s0; U`+`+ algorithms are designed to work on [*/ Ranges]. Range is 
a type that has (at minimum)&]
[s0; &]
[s0;i150;O0; Standard begin() / end() methods.&]
[s0;i150;O0; GetCount() that returns the number of elements in Range 
(can be implemented as end `- begin)&]
[s0;i150;O0; operator`[`] (can be implemented as begin()`[i`])&]
[s0; &]
[s0; Standard Ranges usually also implement ToString and comparisons 
(if it is possible).&]
[s0; &]
[s0; Usually, Range is either U`+`+ container or just some part of 
it.&]
[s0; &]
[s0; U`+`+ provides these Range related typedefs and template functions:&]
[s3; &]
[s4;%- &]
[s5;:Upp`:`:ValueTypeOf`:`:typedef:%- [@(0.0.255) template <class ][*@4 Range][@(0.0.255) >
 using]_[* ValueTypeOf];&]
[s2; Returns the type of elements of Range.&]
[s3;%- &]
[s4;%- &]
[s5;:Upp`:`:IteratorOf`:`:typedef:%- [@(0.0.255) template <class ][*@4 Range][@(0.0.255) > 
using]_[* IteratorOf];&]
[s5;:Upp`:`:ConstIteratorOf`:`:typedef:%- [@(0.0.255) template <class 
][*@4 Range][@(0.0.255) > using]_[* ConstIteratorOf]`'&]
[s2; Returns the type of Iterator / ConstIterator of range.&]
[s3; &]
[s4;%- &]
[s5;:Upp`:`:SubRange`(I`,I`):%- [@(0.0.255) template]_<[@(0.0.255) class]_[*@4 I]>_&]
[s5;:Upp`:`:SubRange`(I`,I`):%- [_^Upp`:`:SubRangeClass^ SubRangeClass]<[*@4 I]>_[* SubRang
e]([*@4 I]_[*@3 begin], [*@4 I]_[*@3 end])&]
[s2; Makes a Range based on begin/end iterators.&]
[s3; &]
[s4;%- &]
[s5;:Upp`:`:SubRange`(I`,int`):%- [@(0.0.255) template]_<[@(0.0.255) class]_[*@4 I]>_&]
[s5;:Upp`:`:SubRange`(I`,int`):%- [_^Upp`:`:SubRangeClass^ SubRangeClass]<[*@4 I]>_[* SubRa
nge]([*@4 I]_[*@3 begin], [@(0.0.255) int]_[*@3 count])&]
[s2; Makes a Range based on begin iterator and count.&]
[s3; &]
[s4;%- &]
[s5;:Upp`:`:SubRange`(C`&`,int`,int`):%- [@(0.0.255) template]_<[@(0.0.255) class]_[*@4 C]>
_&]
[s5;:Upp`:`:SubRange`(C`&`,int`,int`):%- [@(0.0.255) auto]_[* SubRange]([*@4 C][@(0.0.255) `&
]_[*@3 c], [@(0.0.255) int]_[*@3 pos], [@(0.0.255) int]_[*@3 count]);&]
[s5;:Upp`:`:SubRange`(const C`&`,int`,int`):%- [@(0.0.255) template]_<[@(0.0.255) class]_
[*@4 C]>_&]
[s5;:Upp`:`:SubRange`(const C`&`,int`,int`):%- [@(0.0.255) auto]_[* SubRange]([@(0.0.255) c
onst]_[*@4 C][@(0.0.255) `&]_[*@3 c], [@(0.0.255) int]_[*@3 pos], [@(0.0.255) int]_[*@3 count])
;&]
[s2; Makes a Range as subrange of some other Range (e.g. container).&]
[s3; &]
[s4;%- &]
[s5;:Upp`:`:SubRangeOf`:`:typedef:%- [@(0.0.255) template <class ][*@4 Range][@(0.0.255) > 
using]_[* SubRangeOf];&]
[s2; Returns the type of SubRange of some Range.&]
[s3; &]
[s4;%- &]
[s5;:Upp`:`:ConstRange`(const T`&`,int`):%- [@(0.0.255) template]_<[@(0.0.255) class]_[*@4 T
]>_&]
[s5;:Upp`:`:ConstRange`(const T`&`,int`):%- [_^Upp`:`:ConstRangeClass^ ConstRangeClass]<
[*@4 T]>_[* ConstRange]([@(0.0.255) const]_[*@4 T][@(0.0.255) `&]_[*@3 value], 
[@(0.0.255) int]_[*@3 count])&]
[s2; Creates a Range of [%-*@3 count] elements equal to [%-*@3 value].&]
[s3; &]
[s4;%- &]
[s5;:Upp`:`:ViewRange`(BaseRange`&`,Upp`:`:Vector`<int`>`&`&`):%- [@(0.0.255) template]_
<[@(0.0.255) class]_[*@4 BaseRange]>_&]
[s5;:Upp`:`:ViewRange`(BaseRange`&`,Upp`:`:Vector`<int`>`&`&`):%- [_^Upp`:`:ViewRangeClass^ V
iewRangeClass]<[*@4 BaseRange]>_[* ViewRange]([*@4 BaseRange][@(0.0.255) `&]_[*@3 r], 
[_^Upp`:`:Vector^ Vector]<[@(0.0.255) int]>`&`&_[*@3 ndx])&]
[s2; Creates a view of [%-*@4 BaseRange ][%-*@3 r] based on mapping [%-*@3 ndx]. 
Element at [%-*@3 ndx]`[0`] becomes a first element of a new Range, 
[%-*@3 ndx]`[1`] second etc..&]
[s3; &]
[s4;%- &]
[s5;:Upp`:`:FilterRange`(BaseRange`&`,Predicate`):%- [@(0.0.255) template]_<[@(0.0.255) c
lass]_[*@4 BaseRange], [@(0.0.255) class]_[*@4 Predicate]>_&]
[s5;:Upp`:`:FilterRange`(BaseRange`&`,Predicate`):%- [_^Upp`:`:ViewRangeClass^ ViewRang
eClass]<[*@4 BaseRange]>_[* FilterRange]([*@4 BaseRange][@(0.0.255) `&]_[*@3 r], 
[*@4 Predicate]_[*@3 p])&]
[s2; Same as ViewRangeClass<BaseRange>([%-*@3 r], FindAll([%-*@3 r], 
[%-*@3 p])). Creates a view of elements of master Range that satisfy 
condition [%-*@3 p].&]
[s3; &]
[s0; ]]