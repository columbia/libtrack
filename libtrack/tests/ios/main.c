#include <stdio.h>
#include <dlfcn.h>

extern void ctest1(int *);
extern void fff(void);

int main(int argc, char **argv) 
{
   void *lib_handle;
   void (*pctest1)(int *);
   void (*pfff)(void);

   int x;
   char *error;

//   lib_handle = dlopen("/usr/lib/libctest.dylib", RTLD_NOW | RTLD_LOCAL);
//   if (!lib_handle) 
//   {
//      fprintf(stderr, "dlopen: %s\n", dlerror());
//      return -1;
//   }
//
//   void *sym;
//   sym = dlsym(lib_handle, "main");
//   if ((error = dlerror()) != NULL)  
//   {
//     fprintf(stderr, "dlsym:%s\n", error);
//     return -1;
//   }
//   Dl_info wrapped_dli;
//   if ( !dladdr(sym, &wrapped_dli) )
//   {
//     fprintf(stderr, "dladdr:%s\n", error);
//     return -1;
//   }
//
//	// 0xde0 ----> fff
//	// 0xeb0 ----> ctest1
//   x=10;
//   pctest1 = wrapped_dli.dli_fbase + 0xeb0;
//   printf("going to invoke dynamically loaded symbol <ctest1>\n");
//   (*pctest1)(&x);
//   printf("Valx=%d\n",x);
// 
//   printf("-------------\n");
//
   x=10;
   printf("going to invoke dynamically linked symbol <ctest1>\n");
   ctest1(&x);
   printf("Valx=%d\n",x);
//	
//	printf("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n");
//
//   pfff = wrapped_dli.dli_fbase + 0xde0;
//   printf("going to invoke dynamically loaded symbol <fff>\n");
//   (*pfff)();
//
//   printf("-------------\n");

   x=10;
   printf("going to invoke dynamically linked symbol <fff>\n");
   fff();
   printf("Valx=%d\n",x);



   dlclose(lib_handle);
   return 0;
}
