template <class T>
void StreamContainer(Stream& s, T& cont)
{
	int n = cont.GetCount();
	s / n;
	if(n < 0) {
		s.LoadError();
		return;
	}
	if(s.IsLoading())
	{
		cont.Clear();
		cont.Reserve(min(n, int(256*1024 / sizeof(T)))); // protect against invalid streams...
		while(n--)
			s % cont.Add();
	}
	else
	{
		for(auto ptr = cont.begin(); n--; ++ptr)
			s % *ptr;
	}
}

template <class T>
dword HashBySerialize(const T& cont)
{
	TimeStop tm;
	xxHashStream xxh;
	const_cast<T&>(cont).Serialize(xxh);
	return xxh.Finish();
}

template <class T>
bool IsEqualBySerialize(const T& a, const T& b)
{
	StringStream sa, sb;
	const_cast<T&>(a).Serialize(sa);
	const_cast<T&>(b).Serialize(sb);
	return sa.GetResult() == sb.GetResult();
}

void VectorReAlloc_(void *vector_, int newalloc, int sizeofT);
void VectorReAllocF_(void *vector_, int newalloc, int sizeofT);
void VectorGrow_(void *vector_, int sizeofT);
void VectorGrowF_(void *vector_, int sizeofT);

template <class T>
T * Vector<T>::RawAlloc(int& n)
{
	size_t sz0 = n * sizeof(T);
	size_t sz = sz0;
	void *q = MemoryAllocSz(sz);
	n += (int)((sz - sz0) / sizeof(T));
	return (T *)q;
}

template <class T>
void Vector<T>::ReAlloc(int newalloc)
{
	VectorReAlloc_(this, newalloc, sizeof(T));
}

template <class T>
void Vector<T>::ReAllocF(int newalloc)
{
	VectorReAllocF_(this, newalloc, sizeof(T));
}

template <class T>
void Vector<T>::Grow()
{
	VectorGrow_(this, sizeof(T));
}

template <class T>
void Vector<T>::GrowF()
{
	VectorGrowF_(this, sizeof(T));
}

template <class T>
void Vector<T>::Pick(Vector<T>&& v)
{
	vector = v.vector;
	items = v.items;
	alloc = v.alloc;
	v.Zero();
}

template <class T>
int  Vector<T>::GetIndex(const T& item) const
{
	if(vector == NULL) return -1;
	int n = &item - vector;
	return n >= 0 && n < items ? n : -1;
}

template <class T>
void Vector<T>::Reserve(int n)
{
	if(n > alloc)
		ReAllocF(n);
}

template <class T>
void Vector<T>::Free() {
	if(vector && items >= 0)
		Destroy((T *)vector, (T *)vector + items);
	RawFree(vector);
}

template <class T>
void Vector<T>::Clear() {
	Free();
	alloc = items = 0;
	vector = NULL;
}

template <class T>
void Vector<T>::__DeepCopy(const Vector& src) {
	items = alloc = src.items;
	if(src.vector) {
		vector = RawAlloc(alloc);
		DeepCopyConstruct(vector, src.vector, src.vector + items);
	}
	else
		vector = NULL;
}

template <class T>
T& Vector<T>::GrowAdd(const T& x) {
	T *prev = vector;
	Grow();
	T *q = new(Rdd()) T(clone(x));
	RawFree(prev);
	return *q;
}

template <class T>
T& Vector<T>::GrowAddPick(T&& x) {
	T *prev = vector;
	Grow();
	T *q = ::new(Rdd()) T(pick(x));
	RawFree(prev);
	return *q;
}

template <class T> inline
void Vector<T>::AddN(int n)
{
	ASSERT(n >= 0);
	if(items + n <= alloc) {
		Construct(vector + items, vector + items + n);
		items += n;
	}
	else
		SetCountR(items + n);
}

template <class T>
void Vector<T>::Trim(int n)
{
	ASSERT(n >= 0 && n <= items);
	Destroy(vector + n, vector + items);
	items = n;
}

template <class T>
void Vector<T>::SetCount(int n) {
	ASSERT(n >= 0);
	if(n == items) return;
	if(n < items)
		Trim(n);
	else {
		if(n > alloc) ReAllocF(n);
		Construct(vector + items, vector + n);
		items = n;
	}
}

template <class T>
void Vector<T>::SetCount(int n, const T& init) {
	ASSERT(n >= 0);
	if(n == items) return;
	if(n < items)
		Destroy(vector + n, vector + items);
	else {
		if(n > alloc) {
			T *prev = vector;
			ReAlloc(n);
			DeepCopyConstructFill(vector + items, vector + n, init);
			RawFree(prev);
		}
		else
			DeepCopyConstructFill(vector + items, vector + n, init);
	}
	items = n;
}

template <class T>
void Vector<T>::SetCountR(int n) {
	if(n > alloc)
		ReAllocF(alloc + max(alloc, n - items));
	SetCount(n);
}

template <class T>
void Vector<T>::SetCountR(int n, const T& init) {
	ASSERT(n >= 0);
	if(n == items) return;
	if(n < items)
		Destroy(vector + n, vector + items);
	else
		if(n > alloc) {
			T *prev = vector;
			ReAlloc(alloc + max(alloc, n - items));
			DeepCopyConstructFill(vector + items, vector + n, init);
			RawFree(prev);
		}
		else
			DeepCopyConstructFill(vector + items, vector + n, init);
	items = n;
}

template <class T>
void Vector<T>::Remove(int q, int count) {
	ASSERT(q >= 0 && q <= items - count && count >= 0);
	if(count == 0) return;
	Destroy(vector + q, vector + q + count);
	memmove(vector + q, vector + q + count, (items - q - count) * sizeof(T));
	items -= count;
}

template <class T>
void Vector<T>::Remove(const int *sorted_list, int n)
{
	if(!n) return;
	int pos = *sorted_list;
	int npos = pos;
	for(;;) {
		ASSERT(pos < items);
		if(pos == *sorted_list) {
			(vector + pos)->T::~T();
			pos++;
			sorted_list++;
			if(--n == 0) break;
			ASSERT(*sorted_list >= pos);
		}
		else
			*((Data_S_<sizeof(T)>*)vector + npos++)
				= *((Data_S_<sizeof(T)>*)vector + pos++);
	}
	while(pos < items)
		*((Data_S_<sizeof(T)>*)vector + npos++) = *((Data_S_<sizeof(T)>*)vector + pos++);
	items = npos;
}

template <class T>
void Vector<T>::Remove(const Vector<int>& v)
{
	Remove(v, v.GetCount());
}

template <class T>
void Vector<T>::RawInsert(int q, int count)
{
	ASSERT(count >= 0);
	ASSERT(q >= 0 && q <= items);
	if(!count) return;
	if(items + count > alloc) {
		T *newvector = RawAlloc(alloc = max(alloc + count, int(alloc + ((unsigned)alloc >> 1))));
		if(vector) {
			memcpy(newvector, vector, q * sizeof(T));
			memcpy(newvector + q + count, vector + q, (items - q) * sizeof(T));
			RawFree(vector);
		}
		vector = newvector;
	}
	else
		memmove(vector + q + count, vector + q, (items - q) * sizeof(T));
	items += count;
}

template <class T>
void Vector<T>::InsertN(int q, int count) {
	ASSERT(count >= 0);
	ASSERT(q >= 0 && q <= items);
	RawInsert(q, count);
	Construct(vector + q, vector + q + count);
}

template <class T>
void Vector<T>::Insert(int q, const T& x, int count) {
	if(!count) return;
	ASSERT(!(&x >= vector && &x < vector + items));
	RawInsert(q, count);
	DeepCopyConstructFill(vector + q, vector + q + count, x);
}

template <class T>
T& Vector<T>::Insert(int q, T&& x)
{
	ASSERT(&x < vector || &x > vector + items);
	RawInsert(q, 1);
	::new(vector + q) T(pick(x));
	return Get(q);
}

template <class T>
void Vector<T>::Insert(int q, const Vector& x, int offset, int count) {
	ASSERT(offset >= 0 && count >= 0 && offset + count <= x.GetCount());
	ASSERT(!vector || x.vector != vector);
	RawInsert(q, count);
	DeepCopyConstruct(vector + q, x.vector + offset, x.vector + offset + count);
}

template <class T>
void Vector<T>::Insert(int i, std::initializer_list<T> init)
{
	RawInsert(i, (int)init.size());
	T *t = vector + i;
	for(auto q : init)
		new(t++) T(clone(q));
}

template <class T>
template <class Range>
void Vector<T>::InsertRange(int i, const Range& r)
{
	RawInsert(i, r.GetCount());
	T *t = vector + i;
	for(auto q : r)
		new(t++) T(clone(q));
}

template <class T>
void Vector<T>::Insert(int q, const Vector& x) {
	if(!x.GetCount()) return;
	Insert(q, x, 0, x.GetCount());
}

template <class T>
void Vector<T>::Insert(int i, Vector<T>&& v) {
	ASSERT(!vector || v.vector != vector);
	if(v.items) {
		RawInsert(i, v.items);
		memcpy(vector + i, v.vector, sizeof(T) * v.items);
	}
	RawFree(v.vector);
	v.Zero();
}

template <class T>
void Vector<T>::InsertSplit(int i, Vector<T>& v, int from)
{
	ASSERT(!vector || v.vector != vector && from <= v.GetCount());
	int n = v.GetCount() - from;
	if(n) {
		RawInsert(i, n);
		memcpy(vector + i, v.vector + from, sizeof(T) * n);
		v.items = from;
	}
}

template <class T>
void Vector<T>::Set(int i, const T& x, int count) {
	ASSERT(i >= 0 && count >= 0);
	if(count == 0) return;
	if(&x >= vector && &x < vector + items) {
		T copy = x;
		At(i + count - 1);
		Fill(vector + i, vector + i + count, copy);
	}
	else {
		At(i + count - 1);
		Fill(vector + i, vector + i + count, x);
	}
}

template <class T>
template <class Range>
void Vector<T>::SetRange(int i, const Range& r)
{
	int count = r.GetCount();
	ASSERT(i >= 0 && count >= 0);
	if(count == 0) return;
	At(i + count - 1);
	count += i;
	for(; i < count; i++)
		vector[i] = clone(r[i]);
}

#ifdef UPP
template <class T>
void Vector<T>::Xmlize(XmlIO& xio, const char *itemtag)
{
	XmlizeContainer(xio, itemtag, *this);
}

template <class T>
void Vector<T>::Jsonize(JsonIO& jio)
{
	JsonizeArray<Vector<T>, T>(jio, *this);
}

template <class C>
String AsStringArray(const C& v)
{
	String r;
	r << '[';
	for(int i = 0; i < v.GetCount(); i++) {
		if(i)
			r << ", ";
		r << v[i];
	}
	r << ']';
	return r;
}

template <class T>
String Vector<T>::ToString() const
{
	return AsStringArray(*this);
}

#endif

// ------------------

template <class T>
void Array<T>::Free() {
	for(int i = 0; i < vector.GetCount(); i++)
		delete (T *) vector[i];
}

template <class T>
void Array<T>::__DeepCopy(const Array<T>& v) {
	int n = v.GetCount();
	vector.SetCount(n);
	for(int i = 0; i < n; i++)
		vector[i] = new T(clone(v[i]));
}

template <class T>
void  Array<T>::Trim(int n)
{
	ASSERT(n >= 0 && n <= GetCount());
	Del(vector.Begin() + n, vector.End());
	vector.Trim(n);
}

template <class T>
void Array<T>::SetCount(int n) {
	ASSERT(n >= 0);
	int  lc = vector.GetCount();
	Del(vector.Begin() + n, vector.End());
	vector.SetCount(n);
	Init(vector.Begin() + lc, vector.Begin() + n);
}

template <class T>
void Array<T>::SetCount(int n, const T& init) {
	ASSERT(n >= 0);
	int  lc = vector.GetCount();
	Del(vector.Begin() + n, vector.End());
	vector.SetCount(n);
	Init(vector.Begin() + lc, vector.Begin() + n, init);
}

template <class T>
void Array<T>::SetCountR(int n) {
	ASSERT(n >= 0);
	int  lc = vector.GetCount();
	Del(vector.Begin() + n, vector.End());
	vector.SetCountR(n);
	Init(vector.Begin() + lc, vector.Begin() + n);
}

template <class T>
void Array<T>::SetCountR(int n, const T& init) {
	ASSERT(n >= 0);
	int  lc = vector.GetCount();
	Del(vector.Begin() + n, vector.End());
	vector.SetCountR(n);
	Init(vector.Begin() + lc, vector.Begin() + n, init);
}

template <class T>
int  Array<T>::GetIndex(const T& item) const {
	for(PointerType const *ptr = vector.Begin(); ptr < vector.End(); ptr++)
		if(*ptr == (PointerType)&item) return (int)(ptr - vector.Begin());
	return -1;
}

template <class T>
void Array<T>::Move(int i1, int i2) {
	PointerType q = vector[i1];
	vector.Remove(i1);
	vector.Insert(i2 - (i2 > i1)) = (T*)q;
}

template <class T>
void Array<T>::Remove(int i, int count) {
	ASSERT(i + count <= GetCount() && count >= 0 && i >= 0);
	Del(vector.Begin() + i, vector.Begin() + i + count);
	vector.Remove(i, count);
}

template <class T>
void Array<T>::Remove(const int *sorted_list, int n)
{
	const int *q = sorted_list;
	const int *e = sorted_list + n;
	while(q < e) {
		ASSERT(*q >= 0 && *q < GetCount());
		delete (T *)vector[*q++];
	}
	vector.Remove(sorted_list, n);
}

template <class T>
void Array<T>::Remove(const Vector<int>& sorted_list)
{
	Remove(sorted_list, sorted_list.GetCount());
}

template <class T>
void Array<T>::Set(int i, const T& x, int count) {
	ASSERT(i >= 0 && count >= 0);
	if(i + count >= GetCount())
		SetCountR(i + count);
	for(PointerType *ptr = vector.Begin() + i; ptr < vector.Begin() + i + count; ptr++) {
		delete (T *) *ptr;
		*ptr = new T(x);
	}
}

template <class T>
void Array<T>::InsertN(int i, int count) {
	ASSERT(i >= 0 && count >= 0);
	vector.InsertN(i, count);
	Init(vector.Begin() + i, vector.Begin() + i + count);
}

template <class T>
void Array<T>::Insert(int i, const T& x, int count) {
	vector.InsertN(i, count);
	Init(vector.Begin() + i, vector.Begin() + i + count, x);
}

template <class T>
template <class Range>
void Array<T>::InsertRange(int i, const Range& r)
{
	vector.InsertN(i, r.GetCount());
	T **t = GetPtr(i);
	for(const auto& x : r)
		*t++ = new T(clone(x));
}

template <class T>
T& Array<T>::Insert(int i, T&& x)
{
	vector.InsertN(i, 1);
	vector[i] = new T(pick(x));
	return Get(i);
}

template <class T>
T& Array<T>::Insert(int i, T *newt) {
	vector.InsertN(i, 1);
	vector[i] = newt;
	return *newt;
}

template <class T>
void Array<T>::Insert(int i, const Array& x) {
	Insert(i, x, 0, x.GetCount());
}

template <class T>
void Array<T>::Insert(int i, const Array& x, int offset, int count) {
	vector.InsertN(i, count);
	for(int q = 0; q < count; q++)
		vector[q + i] = new T(x[q + offset]);
}

template <class T>
void Array<T>::Insert(int i, std::initializer_list<T> init)
{
	vector.InsertN(i, (int)init.size());
	for(auto q : init)
		vector[i++] = new T(q);
}

#ifdef UPP
template <class T>
void Array<T>::Xmlize(XmlIO& xio, const char *itemtag)
{
	XmlizeContainer(xio, itemtag, *this);
}

template <class T>
void Array<T>::Jsonize(JsonIO& jio)
{
	JsonizeArray<Array<T>, T>(jio, *this);
}

template <class T>
String Array<T>::ToString() const
{
	return AsStringArray(*this);
}

#endif

// ------------------

template <class T>
void BiVector<T>::ReAlloc(int newalloc) {
	ASSERT(items <= newalloc && items >= 0);
	T *newvector = newalloc ? (T *) new byte[newalloc * sizeof(T)] : NULL;
	if(items) {
		int end = start + items;
		if(end <= alloc)
			memcpy(newvector, vector + start, (end - start) * sizeof(T));
		else {
			memcpy(newvector, vector + start, (alloc - start) * sizeof(T));
			memcpy(newvector + alloc - start, vector, (end - alloc) * sizeof(T));
		}
		delete[] (byte *)vector;
	}
	vector = newvector;
	alloc = newalloc;
	start = 0;
}

template <class T>
void BiVector<T>::DeepCopy0(const BiVector& src) {
	alloc = items = src.items;
	vector = alloc ? (T *) new byte[alloc * sizeof(T)] : NULL;
	if(items) {
		int end = src.start + src.items;
		if(end <= src.alloc)
			DeepCopyConstruct(vector, src.vector + src.start, src.vector + end);
		else {
			DeepCopyConstruct(vector, src.vector + src.start, src.vector + src.alloc);
			DeepCopyConstruct(vector + src.alloc - src.start, src.vector,
				              src.vector + end - src.alloc);
		}
	}
	start = 0;
}

template <class T>
void BiVector<T>::Clear() {
	Free();
	start = items = alloc = 0;
	vector = NULL;
}

template <class T>
void BiVector<T>::Add0() {
	ASSERT(items >= 0);
	if(items >= alloc)
		ReAlloc(max(2 * items, 4));
	items++;
}

template <class T>
void BiVector<T>::Shrink() {
	ASSERT(items >= 0);
	if(items < alloc)
		ReAlloc(items);
}

template <class T>
void BiVector<T>::Reserve(int n) {
	ASSERT(items >= 0);
	n += items;
	if(n > alloc)
		ReAlloc(n);
}

template <class T>
void BiVector<T>::Free() {
	if(vector && items >= 0) {
		int end = start + items;
		if(end <= alloc)
			Destroy(vector + start, vector + end);
		else {
			Destroy(vector + start, vector + alloc);
			Destroy(vector, vector + end - alloc);
		}
		delete[] (byte *)vector;
	}
}

#ifdef UPP
template <class T>
void BiVector<T>::Serialize(Stream& s) {
	int n = items;
	s / n;
	if(s.IsLoading()) {
		Clear();
		while(n--)
			s % AddTail();
	}
	else
		for(int i = 0; i < items; i++)
			s % operator[](i);
}

template <class T>
String BiVector<T>::ToString() const
{
	return AsStringArray(*this);
}

#endif

template <class T>
BiVector<T>::BiVector(std::initializer_list<T> init)
{
	start = items = alloc = 0; vector = NULL;

	start = 0;
	alloc = items = (int)init.size();
	if(!alloc) {
		vector = NULL;
		return;
	}
	vector = (T *) new byte[alloc * sizeof(T)];
	T *t = vector;
	for(const auto& q : init)
		new (t++) T(q);
}

// ------------------

template <class T>
void BiArray<T>::Free() {
	for(int i = 0; i < GetCount(); i++)
		delete (T *) bv[i];
}

template <class T>
void BiArray<T>::DeepCopy0(const BiArray<T>& v) {
	int n = v.GetCount();
	bv.Clear();
	bv.Reserve(v.GetCount());
	for(int i = 0; i < n; i++)
		bv.AddTail() = new T(clone(v[i]));
}

#ifdef UPP
template <class T>
void BiArray<T>::Serialize(Stream& s) {
	int n = bv.GetCount();
	s / n;
	if(s.IsLoading()) {
		Clear();
		while(n--)
			s % AddTail();
	}
	else
		for(int i = 0; i < bv.GetCount(); i++)
			s % operator[](i);
}

template <class T>
String BiArray<T>::ToString() const
{
	return AsStringArray(*this);
}

template <class T>
BiArray<T>::BiArray(std::initializer_list<T> init)
{
	for(const auto& q : init)
		AddTail(q);
}

#endif
