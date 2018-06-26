#include "SSL.h"

#define LLOG(x) // DLOG(x)

namespace Upp {

static int64 UPP_SSL_alloc = 0;

static void *SslAlloc(size_t size)
{
	LLOG("Alloc " << size);
	size_t alloc = size + sizeof(int64);
	int64 *aptr = (int64 *)MemoryAllocSz(alloc);
	*aptr++ = (int64)alloc;
	UPP_SSL_alloc += alloc;
	LLOG("UPP_SSL_MALLOC(" << (int64)size << ", alloc " << alloc << ") -> " << FormatIntHex(aptr) << ", total = " << UPP_SSL_alloc);
	return aptr;
}

static void SslFree(void *ptr)
{
	if(!ptr)
		return;
	int64 *aptr = (int64 *)ptr - 1;
	UPP_SSL_alloc -= *aptr;
	LLOG("UPP_SSL_FREE(" << ptr << ", alloc " << *aptr << "), total = " << UPP_SSL_alloc);
	MemoryFree(aptr);
}

static void *SslRealloc(void *ptr, size_t size)
{
	if(!ptr)
		return NULL;
	int64 *aptr = (int64 *)ptr - 1;
	if((int64)(size + sizeof(int64)) <= *aptr) {
		LLOG("UPP_SSL_REALLOC(" << ptr << ", " << (int64)size << ", alloc " << *aptr << ") -> keep same block");
		return ptr;
	}
	size_t newalloc = size + sizeof(int64);
	int64 *newaptr = (int64 *)MemoryAllocSz(newalloc);
	if(!newaptr) {
		LLOG("UPP_SSL_REALLOC(" << ptr << ", " << (int64)size << ", alloc " << newalloc << ") -> fail");
		return NULL;
	}
	*newaptr++ = newalloc;
	memcpy(newaptr, ptr, min<int>((int)(*aptr - sizeof(int64)), (int)size));
	UPP_SSL_alloc += newalloc - *aptr;
	LLOG("UPP_SSL_REALLOC(" << ptr << ", " << (int64)size << ", alloc " << newalloc << ") -> "
		<< FormatIntHex(newaptr) << ", total = " << UPP_SSL_alloc);
	MemoryFree(aptr);
	return newaptr;
}

void TcpSocketInit();

INITIALIZER(SSL)
{
	LLOG("SSL init");
	TcpSocketInit();
	MemoryIgnoreLeaksBlock __;
	CRYPTO_set_mem_functions(SslAlloc, SslRealloc, SslFree);
	SSL_library_init();
	SSL_load_error_strings();
}

EXITBLOCK
{
	CONF_modules_unload(1);
	EVP_cleanup();
	ENGINE_cleanup();
	CRYPTO_cleanup_all_ex_data();
	ERR_remove_state(0);
	ERR_free_strings();
	
	STACK_OF(SSL_COMP) *pCOMP = SSL_COMP_get_compression_methods();
	if(pCOMP)
		sk_SSL_COMP_free( pCOMP );
}

#ifdef _MULTITHREADED

static thread__ bool sThreadInit;
static thread__ void (*sPrevExit)();

static void sslExitThread()
{
	ERR_remove_state(0);
	if(sPrevExit)
		(*sPrevExit)();
}

void SslInitThread()
{
	if(sThreadInit || Thread::IsMain())
		return;
	sThreadInit = true;
	sPrevExit = Thread::AtExit(sslExitThread);
}

#else

void SslInitThread() {}

#endif

}
