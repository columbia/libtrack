#
# The wrapper "white list"
#
my %_always_wrap = (
		    "mmap" => 1,
		    "bcopy" => 1,
		    "bzero" => 1,
		    "dlmalloc" => 1,
		    "dlcalloc" => 1,
		    "dlrealloc" => 1,
		    "dlrealloc_in_place" => 1,
		    "dlmemalign" => 1,
		    "dlposix_memalign" => 1,
		    "dlvalloc" => 1,
		    "dlpvalloc" => 1,
		    "dlfree" => 1,
		    "sigaction" => 1,
		    "fflush" => 1,
		    "fgetpos" => 1,
		    "fileno" => 1,
		    "ftell" => 1,
		    "ftello" => 1,
		    "_fwalk" => 1,
		    "__sflush" => 1,
		    "__sflush_locked" => 1,
		    "__sclose" => 1,
		    "fstatfs" => 1,
		    "statfs" => 1,
		    "closedir" => 1,
		    "getnetbyaddr" => 1,
		    "getnetbyname" => 1,
		    "getprotobyname" => 1,
		    "getprotobynumber" => 1,
		    "wait" => 1,
		    "wait3" => 1,
		    "waitpid" => 1,
		    "__wait4" => 1,
		    "fwprintf" => 1,
		    "wprintf" => 1,
		    "swprintf" => 1,
		    "vfwprintf" => 1,
		    "fwscanf" => 1,
		    "killpg" => 1,
);

sub always_wrap() {
	return %_always_wrap;
}

#
# The wrapper "black list"
# must be kept in-sync with wraplib.sh should_wrap_android_elf bash function
#

# regular expressions (keep this list short)
my %_never_wrap_re = ( '.*@plt.*' => 1,
		      '.*divmod.*' => 1,
		      '.*_(rd|rw|un|try)*lock[^a-zA-Z]*' => 1,
);
sub never_wrap_re() {
	return %_never_wrap_re;
}

# explicit symbols
my %_never_wrap = ( ".plt" => 1,
		   "__libc_init" => 1,
		   "__errno" => 1,
		   "__aeabi_atexit" => 1,
		   "__cxa_atexit" => 1,
		   "__cxa_finalize" => 1,
		   "__init_tls" => 1,
		   "__thread_entry" => 1,
		   "__set_tls" => 1,

		   # unwind functions
		   "_Unwind_Resume" => 1,
		   "___Unwind_Resume" => 1,
		   "_Unwind_Resume_or_Rethrow" => 1,
		   "___Unwind_Resume_or_Rethrow" => 1,
		   "_Unwind_Backtrace" => 1,
		   "___Unwind_Backtrace" => 1,
		   "_Unwind_GetDataRelBase" => 1,
		   "_Unwind_RaiseException" => 1,
		   "___Unwind_RaiseException" => 1,
		   "_Unwind_ForceUnwind" => 1,
		   "___Unwind_ForceUnwind" => 1,
		   "_Unwind_VRS_Set" => 1,
		   "_Unwind_VRS_Get" => 1,
		   "__gnu_Unwind_RaiseException" => 1,
		   "__gnu_Unwind_Backtrace" => 1,
		   "__gnu_unwind_execute" => 1,
		   "__gnu_unwind_frame" => 1,
		   "__gnu_Unwind_Find_exidx" => 1,
		   "__gnu_Unwind_Resume" => 1,
		   "__gnu_Unwind_Resume_or_Rethrow" => 1,
		   "__gnu_Unwind_ForceUnwind" => 1,
		   "__aeabi_unwind_cpp_pr0" => 1,
		   "__aeabi_unwind_cpp_pr1" => 1,

		   # memory allocation
		   "malloc" => 1,
		   "calloc" => 1,
		   "realloc" => 1,
		   "realloc_in_place" => 1,
		   "memalign" => 1,
		   "posix_memalign" => 1,
		   "valloc" => 1,
		   "pvalloc" => 1,
		   "free" => 1,

		   # memory manipulation
		   "memmove" => 1,
		   "memcpy" => 1,
		   "memset" => 1,
		   "memcmp" => 1,
		   "wmemmove" => 1,
		   "wmemcpy" => 1,
		   "wmemset" => 1,
		   "wmemcmp" => 1,

		   # string operations
		   "strlen" => 1,
		   "strnlen" => 1,
		   "strdup" => 1,
		   "strchr" => 1,
		   "strrchr" => 1,
		   "sprintf" => 1,
		   "vsprintf" => 1,
		   "snprintf" => 1,
		   "vsnprintf" => 1,
		   "__strncat_chk" => 1,
		   "sscanf" => 1,
		   "vscanf" => 1,
		   "vsscanf" => 1,
		   "__strcpy_chk" => 1,
		   "__strncpy_chk" => 1,
		   "__strlen_chk" => 1,
		   "__strnlen_chk" => 1,
		   "__strcpy_chk" => 1,
		   "__strncpy_chk" => 1,
		   "__strcat_chk" => 1,

		   # div
		   "__aeabi_idiv" => 1,
		   "__aeabi_uidiv" => 1,

		   # rand
		   "lrand48" => 1,

		   # clock
		   "clock_gettime" => 1,

		   # pthreads
		   "pthread_cond_broadcast" => 1,
		   "pthread_mutex_init" => 1,
		   "pthread_cond_signal" => 1,
);

sub never_wrap() {
	return %_never_wrap;
}

