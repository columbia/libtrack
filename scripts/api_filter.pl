#
# The wrapper "white list"
#

require "scripts/posix_api.pl";

my %_always_wrap = (
		    # Android specific routines
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
		    "_fwalk" => 1,
		    "__sflush" => 1,
		    "__sflush_locked" => 1,
		    "__sclose" => 1,
		    "statfs" => 1,
		    "fstatfs" => 1,
		    "wait3" => 1,
		    "__wait4" => 1,
);


sub always_wrap() {
	my %h;
	# POSIX API
	%h = posix_alg();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_arg();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_fs();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_ipc();
	@_always_wrap{ keys %h } = values %h;
	# skip posix_math
	%h = posix_mem();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_misc();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_net();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_proc();
	@_always_wrap{ keys %h } = values %h;
	# skip posix_string
	%h = posix_term();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_thread();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_time();
	@_always_wrap{ keys %h } = values %h;
	%h = posix_users();
	@_always_wrap{ keys %h } = values %h;
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
my %_never_wrap = (
		   ".plt" => 1,
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

		   # string operations
		   "__strncat_chk" => 1,
		   "__strcpy_chk" => 1,
		   "__strncpy_chk" => 1,
		   "__strlen_chk" => 1,
		   "__strnlen_chk" => 1,
		   "__strcat_chk" => 1,
		   "__sprintf_chk" => 1,
		   "__strchr_chk" => 1,
		   "__strrchr_chk" => 1,

		   # math
		   "__aeabi_idiv" => 1,
		   "__aeabi_uidiv" => 1,

		   # pthread functions that can be expensive
		   # (to be removed)
		   "pthread_self" => 1,
		   "pthread_getspecific" => 1,
		   "pthread_setspecific" => 1,

		   # memory allocation functions
		   # (to be removed)
		   "memset" => 1,
		   "memcpy" => 1,
		   "free" => 1,
		   "malloc" => 1,
		   "calloc" => 1,
		   "memcmp" => 1,
		   "memmove" => 1,
		   "realloc" => 1,
		   "__memcpy_chk" => 1,
		   "__memmove_chk" => 1,

		   # clock
		   "clock_gettime" => 1,
);

sub never_wrap() {
	my %h;
	%h = posix_string();
	@_never_wrap{ keys %h } = values %h;
	%h = posix_math();
	@_never_wrap{ keys %h } = values %h;
	return %_never_wrap;
}

